# Centralized Error Handling

## The problem with `try/catch` everywhere

A tempting first instinct is to wrap every route handler in its own `try/catch`.

```ts
app.get("/problems/:id", (req, res) => {
  try {
    const problem = findProblem(req.params.id);
    if (!problem) {
      res.status(404).json({ error: "Not found" });
      return;
    }
    res.json(problem);
  } catch (error) {
    res.status(500).json({ error: "Something went wrong" });
  }
});
```

Repeated across every route, this gets noisy fast, and the error response format can drift, one route returns `{ error: "..." }`, another returns just a string, another forgets to catch at all. Express provides a better way: **error-handling middleware**, defined once, used everywhere.

## Error-handling middleware

An error-handling middleware function looks like normal middleware, but with **four** parameters instead of three. Express recognizes it as an error handler specifically because of that fourth parameter.

```ts
import { Request, Response, NextFunction } from "express";

function errorHandler(err: Error, req: Request, res: Response, next: NextFunction) {
  console.error(err);
  res.status(500).json({ error: "Internal server error" });
}
```

It must be registered **last**, after every route and every other middleware.

```ts
app.use(express.json());
app.use(requestLogger);

app.get("/problems", getProblems);
app.post("/problems", createProblem);

app.use(errorHandler); // always last
```

## Reaching the error handler: `next(err)`

Calling `next()` with no argument continues to the next normal middleware. Calling `next(err)` with an argument skips straight to the nearest error-handling middleware, bypassing everything else in between.

```ts
app.get("/problems/:id", (req, res, next) => {
  const problem = findProblem(req.params.id);
  if (!problem) {
    next(new Error("Problem not found")); // jumps straight to errorHandler
    return;
  }
  res.json(problem);
});
```

⚠️ **Pitfall**: throwing inside an `async` route handler does **not** automatically reach `next()` in older Express versions (before Express 5). An unhandled rejected promise silently hangs the request instead of triggering your error handler. Two common fixes:

```ts
// Option 1: catch manually and call next(err)
app.get("/problems/:id", async (req, res, next) => {
  try {
    const problem = await findProblem(req.params.id);
    res.json(problem);
  } catch (err) {
    next(err);
  }
});

// Option 2: a small wrapper that does this automatically for every async handler
function asyncHandler(fn: RequestHandler) {
  return (req: Request, res: Response, next: NextFunction) => {
    Promise.resolve(fn(req, res, next)).catch(next);
  };
}

app.get("/problems/:id", asyncHandler(async (req, res) => {
  const problem = await findProblem(req.params.id);
  res.json(problem);
}));
```

📌 Express 5 (released as the new default in newer setups) fixes this automatically, async errors reach the error handler without a wrapper. Check which major version your project uses.

## Custom error classes

Plain `Error` objects do not carry a status code. A custom error class lets you throw meaningful, typed errors that the central handler can read.

```ts
class AppError extends Error {
  constructor(public statusCode: number, message: string) {
    super(message);
  }
}

class NotFoundError extends AppError {
  constructor(message = "Resource not found") {
    super(404, message);
  }
}

class ValidationError extends AppError {
  constructor(message = "Invalid input") {
    super(400, message);
  }
}
```

```ts
app.get("/problems/:id", asyncHandler(async (req, res) => {
  const problem = await findProblem(req.params.id);
  if (!problem) {
    throw new NotFoundError(`Problem with id ${req.params.id} not found`);
  }
  res.json(problem);
}));
```

## A complete central error handler using the custom classes

```ts
function errorHandler(err: Error, req: Request, res: Response, next: NextFunction) {
  if (err instanceof AppError) {
    res.status(err.statusCode).json({ error: err.message });
    return;
  }

  console.error(err); // unexpected error, log full details for debugging
  res.status(500).json({ error: "Internal server error" });
}
```

Now every route can simply `throw` a specific, meaningful error, and one place decides how to turn it into a response.

```
Route throws NotFoundError(404)
      |
      v
errorHandler checks: is it an AppError? yes
      |
      v
res.status(404).json({ error: "..." })
```

```
Route throws a raw, unexpected Error (a real bug)
      |
      v
errorHandler checks: is it an AppError? no
      |
      v
Logs full error, sends generic 500, never leaks internal details to the client
```

## Why this matters for security too

Sending raw internal error messages (stack traces, database error text) back to the client can leak details about your system. The central handler is also the single place that decides exactly what error information is safe to expose, matching the "fail safely, do not leak internals" habit from [`07-security.md`](../0%20Concepts/07-security.md).

## Key takeaways

- Error-handling middleware has four parameters `(err, req, res, next)` and must be registered last.
- `next(err)` jumps straight to the error handler, skipping the rest of the normal chain.
- Async route handlers need either a manual `try/catch` with `next(err)`, a wrapper, or Express 5, to reach the error handler correctly.
- Custom error classes (`AppError` and subclasses) let one central handler produce consistent, correct status codes and messages everywhere.
