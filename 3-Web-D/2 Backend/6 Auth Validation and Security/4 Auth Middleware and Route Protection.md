# Auth Middleware and Route Protection

This file connects JWT verification (previous file) to the middleware pattern (Phase 1 notes), producing reusable route protection.

## The goal

```
Public route:      GET /problems           -> anyone can access
Protected route:   POST /submissions       -> must be logged in
Owner-only route:  DELETE /submissions/:id -> must be logged in AND own this submission
```

This file covers the first two. Ownership checks (the third) get their own file next.

## The auth middleware

```ts
import { Request, Response, NextFunction } from "express";
import jwt from "jsonwebtoken";

export function requireAuth(req: Request, res: Response, next: NextFunction) {
  const header = req.headers.authorization;

  if (!header?.startsWith("Bearer ")) {
    res.status(401).json({ error: "Missing or invalid authorization header" });
    return;
  }

  const token = header.slice(7);

  try {
    const payload = jwt.verify(token, process.env.JWT_SECRET!) as { userId: number };
    req.userId = payload.userId; // attach to the request, see typing below
    next();
  } catch (err) {
    res.status(401).json({ error: "Invalid or expired token" });
  }
}
```

Following the middleware pattern from Phase 1: check something, then either call `next()` to continue, or end the response and stop. No half-authenticated request continues to the route handler.

## Typing `req.userId`

Express's `Request` type does not know about a custom `userId` field by default, TypeScript will reject `req.userId = ...` without help. This is solved with **declaration merging**, the interface-only feature covered in the TypeScript notes.

```ts
// src/types/express.d.ts
declare global {
  namespace Express {
    interface Request {
      userId?: number;
    }
  }
}

export {};
```

This file adds a `userId` field to Express's own `Request` interface, merging into it rather than replacing it. Every `req: Request` in your project now correctly recognizes `req.userId` as `number | undefined`.

## Attaching to specific routes

```ts
router.post("/submissions", requireAuth, submissionsController.create);
```

Only routes with `requireAuth` in their middleware chain require a token. Others remain public.

```ts
router.get("/problems", problemsController.getAll);              // public
router.post("/submissions", requireAuth, submissionsController.create); // protected
```

## Using the authenticated user inside a controller

```ts
export const submissionsController = {
  async create(req: Request, res: Response) {
    const userId = req.userId!; // guaranteed to exist, requireAuth ran first
    const submission = await submissionService.create(userId, req.body);
    res.status(201).json(submission);
  },
};
```

The `!` (non-null assertion) here is a deliberate, narrow exception to "avoid overusing `as`/assertions" from the TypeScript notes, it is safe specifically because `requireAuth` runs before this handler and guarantees `req.userId` is set, enforced by route ordering, not by chance.

## Applying auth to a whole router at once

Rather than repeating `requireAuth` on every route, apply it once to an entire router.

```ts
const router = Router();
router.use(requireAuth); // every route below this line requires auth

router.post("/", submissionsController.create);
router.get("/:id", submissionsController.getById);
```

Useful when most or all routes in a file need protection, mixing this with per-route middleware for the few that do not (using a separate router for public ones) keeps things clear.

## Middleware order, a full picture

```
      every request
┌───────────────────────────┐
│  express.json()           │  parse body
├───────────────────────────┤
│  requestLogger             │  log it
├───────────────────────────┤
│  requireAuth (some routes) │  verify token, attach req.userId or stop with 401
├───────────────────────────┤
│  route handler             │  send the response
├───────────────────────────┤
│  errorHandler               │  catch anything thrown along the way
└───────────────────────────┘
```

## Testing protection manually

```bash
# no token, protected route -> 401
curl -X POST http://localhost:3000/submissions -d '{}'

# valid token -> passes through
curl -X POST http://localhost:3000/submissions \
  -H "Authorization: Bearer eyJhbGciOi..." \
  -H "Content-Type: application/json" \
  -d '{"problemId": 1, "code": "..."}'
```

## Common mistakes

| Mistake | Symptom | Fix |
|---|---|---|
| `requireAuth` registered after the route it should protect | Route is reachable without a token | Middleware order matters, place it before the route |
| Forgetting `return` after `res.status(401).json(...)` | Code after it still runs, `next()` may get called too, corrupting the response | Always `return` immediately after ending a response inside middleware |
| Reading `req.headers.Authorization` (capitalized) | Always `undefined` | Header keys are lowercased by Express, use `req.headers.authorization` |
| Trusting `req.userId` without running `requireAuth` first | `undefined` reaches business logic, crashes or behaves incorrectly | Always place `requireAuth` in the chain before any handler relying on it |

## Key takeaways

- `requireAuth` is one middleware function, verifies the JWT, attaches `req.userId` or stops the request with `401`.
- Declaration merging (`declare global { namespace Express { interface Request {...} } }`) is how you safely add custom fields to Express's `Request` type.
- Apply `requireAuth` per-route, or once for a whole router with `router.use(requireAuth)`, depending on how many routes in that file need protection.
- Route ordering matters, middleware only protects routes registered after it in the chain.
