# Middleware

Middleware is the single most important concept in Express. Almost everything Express does (parsing JSON, logging, authentication, error handling) is built using it.

## The idea

A middleware function sits between the incoming request and the final route handler. It can inspect or change the request, then either pass control forward or stop the chain entirely.

```
Request
   |
   v
Middleware 1  (e.g. logging)
   |
   v
Middleware 2  (e.g. parse JSON body)
   |
   v
Middleware 3  (e.g. check auth token)
   |
   v
Route handler (sends the response)
```

Each middleware decides what happens next. It can:

- Do something, then call `next()` to pass control to the next middleware in line.
- Do something and end the response itself (`res.json()`, `res.status().send()`), stopping the chain.
- Throw or pass an error to `next(err)`, jumping straight to error-handling middleware.

## The middleware function signature

```ts
import { Request, Response, NextFunction } from "express";

function logger(req: Request, res: Response, next: NextFunction) {
  console.log(`${req.method} ${req.url} - ${new Date().toISOString()}`);
  next(); // pass control to the next middleware/handler
}
```

Every middleware takes `(req, res, next)`. `next` is a function, calling it moves to the next step in the chain. **Forgetting to call `next()`** (when you are not ending the response yourself) leaves the request hanging forever, the client will just wait until it times out.

## Registering middleware

```ts
app.use(logger); // runs for every request, on every route
```

```ts
app.get("/problems", logger, (req, res) => {
  // logger runs first, then this handler
});
```

Middleware runs in the exact order it is registered. Order matters a lot.

```ts
app.use(express.json());   // must come before routes that read req.body
app.use(logger);

app.get("/problems", (req, res) => {
  // by the time we get here, JSON has been parsed and the request has been logged
});
```

## Built-in and third-party middleware

| Middleware | What it does |
|---|---|
| `express.json()` | Parses JSON request bodies into `req.body` |
| `express.urlencoded()` | Parses form-submitted data into `req.body` |
| `express.static(folder)` | Serves static files (images, CSS) directly from a folder |
| `cors()` (third-party, from the `cors` package) | Adds headers that allow requests from other origins, covered in Phase 3 |
| `helmet()` (third-party) | Adds security-related HTTP headers |

These are all just functions matching the same `(req, res, next)` shape, Express does not treat built-in middleware specially.

## Writing your own middleware: a request logger

```ts
function requestLogger(req: Request, res: Response, next: NextFunction) {
  const start = Date.now();
  console.log(`--> ${req.method} ${req.url}`);

  res.on("finish", () => {
    const duration = Date.now() - start;
    console.log(`<-- ${req.method} ${req.url} ${res.statusCode} (${duration}ms)`);
  });

  next();
}

app.use(requestLogger);
```

## Writing your own middleware: a simple auth check (preview)

Full JWT handling comes in Phase 3, but the middleware shape is worth seeing now.

```ts
function requireAuth(req: Request, res: Response, next: NextFunction) {
  const token = req.headers.authorization;

  if (!token) {
    res.status(401).json({ error: "Missing authorization token" });
    return; // stop here, do not call next()
  }

  next(); // token exists (not yet verified here), continue
}

app.post("/submissions", requireAuth, (req, res) => {
  // only reached if requireAuth called next()
});
```

This shows the two branches clearly: if the check fails, respond and stop (never call `next()` after sending a response). If it passes, call `next()` and let the request continue.

## Route-specific vs global middleware

| Style | Example | Runs on |
|---|---|---|
| Global | `app.use(logger)` | Every single request |
| Route-specific | `app.get("/x", requireAuth, handler)` | Only that one route |
| Router-level | applied to an entire `express.Router()` | Every route inside that router |

## Middleware pipeline as layers

```
        every request passes through
┌───────────────────────────────────────┐
│  express.json()   (parse body)        │
├───────────────────────────────────────┤
│  requestLogger     (log the request)  │
├───────────────────────────────────────┤
│  requireAuth        (only some routes)│
├───────────────────────────────────────┤
│  route handler       (send response)  │
├───────────────────────────────────────┤
│  error handler   (only if next(err))  │
└───────────────────────────────────────┘
```

Each layer either passes the request down, or stops it right there.

## Key takeaways

- Middleware is any function shaped `(req, res, next)`, run in the exact order it is registered.
- Call `next()` to continue the chain, or end the response yourself to stop it, never both.
- `express.json()`, auth checks, logging and error handling are all middleware, there is no separate mechanism for each.
- Global middleware (`app.use`) runs on every request, route-specific middleware runs only where you attach it.
