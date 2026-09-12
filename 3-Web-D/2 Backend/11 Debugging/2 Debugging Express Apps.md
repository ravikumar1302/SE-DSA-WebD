# Debugging Express Apps

Most Express bugs fall into one of a small number of shapes: the request never reaches the handler you expect, middleware runs in the wrong order, or the response is not what you assumed. This file covers finding out which one is actually happening.

## Confirm the request even arrived

Before suspecting business logic, confirm the route is being hit at all.

```ts
app.use((req, res, next) => {
  console.log(`${req.method} ${req.path}`);
  next();
});
```

Placed before all routes, this logs every incoming request. If a request you are testing never shows up here, the problem is not in your Express app at all, it is the client never sending the request, a wrong URL, or a proxy/CORS issue stopping it earlier. This single log rules out an entire category of bug in seconds.

## Route order and matching

Express matches routes top to bottom, the first matching route wins, execution never automatically continues to a later matching route.

```ts
app.get("/problems/:id", getProblemById);
app.get("/problems/featured", getFeaturedProblems); // never reached
```

A request to `/problems/featured` matches the first route (`:id` matches anything, including the word "featured"), `getProblemById` runs with `id` set to the string `"featured"`, the second route never runs at all. Fix: put more specific routes before more general ones.

```
Request: GET /problems/featured
      |
      v
Checked against routes, top to bottom
      |
      v
/problems/:id  <- matches first, :id captures "featured"
      |
      v
getProblemById runs, wrong handler, /problems/featured route never reached
```

## Middleware order bugs

Covered briefly in the [Troubleshooting Index](../Troubleshooting%20Index.md), worth a deeper look here. Middleware runs in the exact order it is registered with `app.use`, not the order routes are defined, not alphabetical, exactly registration order.

```ts
app.use("/problems", problemRoutes);       // registered first
app.use(requireAuth);                       // registered second, too late
```

Any route inside `problemRoutes` is now reachable without authentication, `requireAuth` only protects routes registered after it. Fix: register global middleware (auth, body parsing, CORS) before the routes that depend on it.

## Inspecting `req` and `res` mid-request

The fastest low-effort check, before reaching for a breakpoint, log the specific pieces you actually suspect are wrong.

```ts
app.post("/problems", (req, res) => {
  console.log("body:", req.body);
  console.log("headers:", req.headers);
  console.log("params:", req.params);
  console.log("query:", req.query);
  // ...
});
```

📌 `req.body` being `undefined` almost always means `express.json()` is missing or was registered after this route, this is one of the single most common Express bugs beginners hit, and this log catches it immediately.

## Confirming what actually got sent back

A response can look wrong on the client for two very different reasons: the server sent the wrong thing, or the server sent the right thing and the client misread it. Logging the response body just before `res.json(...)` sends confirms which side the bug is actually on.

```ts
const payload = { success: true, data: problem };
console.log("sending:", payload);
res.json(payload);
```

If this log shows correct data but the client still displays something wrong, the bug has moved to the frontend, not here.

## A minimal repro route

For a bug that only appears in a large, real route, adding a tiny throwaway route that isolates just the suspected piece is often faster than adding breakpoints inside the real one.

```ts
app.get("/debug-test", async (req, res) => {
  const result = await problemService.findById(1); // test just this, nothing else
  res.json(result);
});
```

This is the backend version of the minimal reproduction idea from the frontend debugging notes, strip away everything except the one piece under suspicion.

## Key takeaways

- A request-logging middleware placed before all routes confirms in one step whether a request even reached your Express app.
- Express matches routes top to bottom, a more general route registered earlier can silently swallow requests meant for a more specific one below it.
- Middleware runs in registration order, not route-definition order, auth middleware registered after the routes it should protect does not protect them.
- Logging `req.body`, headers, params and the outgoing response body pinpoints which side, client or server, actually holds the bug.
