# Consistent Response and Error Envelope

## The problem with inconsistent shapes

Across Phases 1 to 3, different routes returned data in slightly different shapes without a fixed rule: a raw array here, a raw object there, `{ error: "..." }` from one route, a bare string from another. Each is fine on its own, but a frontend consuming the whole API has to handle every route as a special case.

```ts
// GET /problems      -> [ {...}, {...} ]              (raw array)
// GET /problems/:id  -> { id, title, ... }             (raw object)
// POST /auth/login    -> { token, user }                (custom shape)
// 404 responses        -> { error: "Problem not found" } (sometimes)
// 500 responses         -> just crashes, no JSON at all  (sometimes)
```

⚠️ **Pitfall**: inconsistent shapes push complexity onto every client of your API. Each frontend call site needs its own guesswork about whether the response is an array, an object, wrapped or unwrapped. This is exactly the "frontend hell" pitfall named in [`06-apis.md`](../0%20Concepts/06-apis.md).

## The envelope pattern

Wrap every response in the same outer shape, success or failure.

```ts
{ success: true, data: <the actual payload> }
{ success: false, error: { message: string, details?: unknown } }
```

```
Every response
      |
      v
┌─────────────────────────────┐
│ success: true / false        │
│ data (only if success)       │
│ error (only if failure)      │
└─────────────────────────────┘
```

A client can now check `response.success` once, and know exactly where to find the payload or the error, regardless of which route it called.

## Typing the envelope with generics

This is exactly the `ApiResponse<T>` example from the Generics file in the TypeScript notes, now put to real use.

```ts
interface ApiSuccess<T> {
  success: true;
  data: T;
}

interface ApiError {
  success: false;
  error: {
    message: string;
    details?: unknown;
  };
}

type ApiResponse<T> = ApiSuccess<T> | ApiError;
```

```ts
const response: ApiResponse<Problem> = { success: true, data: problem };
const errorResponse: ApiResponse<never> = {
  success: false,
  error: { message: "Problem not found" },
};
```

## A small response helper (keeps every route consistent, without repeating the shape by hand)

```ts
// src/utils/response.ts
import { Response } from "express";

export function sendSuccess<T>(res: Response, data: T, statusCode = 200) {
  res.status(statusCode).json({ success: true, data });
}
```

```ts
export const problemsController = {
  async getAll(req: Request, res: Response) {
    const problems = await problemService.getAll();
    sendSuccess(res, problems);
  },

  async create(req: Request, res: Response) {
    const problem = await problemService.create(req.body);
    sendSuccess(res, problem, 201);
  },
};
```

## Updating the central error handler to match

The error-handling middleware built in Phase 1 already turns thrown errors into a response, it now emits the same envelope shape used everywhere else.

```ts
function errorHandler(err: Error, req: Request, res: Response, next: NextFunction) {
  if (err instanceof AppError) {
    res.status(err.statusCode).json({
      success: false,
      error: { message: err.message },
    });
    return;
  }

  console.error(err);
  res.status(500).json({
    success: false,
    error: { message: "Internal server error" },
  });
}
```

Every failure, whether it is a `404` thrown from a controller or an unexpected `500`, now comes back in exactly the same shape as every success, only `success` flips.

## Including validation details in the error shape

Zod's validation errors (from Phase 3) fit naturally into the `details` field.

```ts
if (!result.success) {
  res.status(400).json({
    success: false,
    error: { message: "Invalid input", details: result.error.issues },
  });
  return;
}
```

The client always finds the human-readable message at `error.message`, and can optionally dig into `error.details` for field-by-field validation feedback, without needing to guess the shape per route.

## Before and after, side by side

| | Before (Phases 1 to 3) | After (Phase 4 envelope) |
|---|---|---|
| `GET /problems` success | `[ {...}, {...} ]` | `{ success: true, data: [ {...}, {...} ] }` |
| `GET /problems/:id` not found | `{ error: "Not found" }` | `{ success: false, error: { message: "Not found" } }` |
| Unexpected server crash | Whatever Express's default handler sends, may not even be JSON | `{ success: false, error: { message: "Internal server error" } }` |

## Key takeaways

- Every response, success or failure, should share one outer shape (`success`, then `data` or `error`), so a frontend never has to guess the structure per route.
- `ApiResponse<T>`, a union of a success type and an error type, is a direct real-world use of the generics covered in the TypeScript notes.
- The central error handler is the one place that guarantees every failure, expected or not, comes back in the same shape as every success.
- A small `sendSuccess` helper keeps every controller consistent without retyping the envelope by hand in every route.
