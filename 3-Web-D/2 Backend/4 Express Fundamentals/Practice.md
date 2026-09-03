# Practice: Express Fundamentals

These build directly toward the Phase 1 deliverable. Do them in order, each one leaves working code the next one extends.

---

### 1. Raw Node first, no Express

Build a server with only the `http` module that returns JSON on `/health` and a 404 on everything else.

**Done when**: the browser shows JSON at `/health`, and you can name two things Express would do for you here.

---

### 2. Same thing in Express

Rewrite exercise 1 using Express.

**Done when**: it behaves identically, in noticeably fewer lines, and you did not write `writeHead` once.

---

### 3. Pick the right status code

For each case, write the route and return the correct code: a created problem, a successful list, a missing problem, a bad request body, a successful delete.

**Hint**: 201, 200, 404, 400, 204.

**Done when**: no route returns 200 for everything, and `curl -i` confirms each one.

---

### 4. Read data from all four places

Build `POST /problems/:id/submissions?draft=true` that reads the route param, the query param, the body and the `Authorization` header, then echoes all four back.

**Done when**: the id comes back as a number, not a string, and a missing header does not crash the route.

---

### 5. Write a logging middleware

Log method, path and how long the request took, for every request.

**Hint**: record the time at the start, listen for `res.on("finish")`.

**Done when**: every request prints one line, and no request hangs because `next()` was forgotten.

---

### 6. Break the middleware order on purpose

Register `express.json()` *after* a POST route, hit that route, and observe what happens. Then fix it.

**Done when**: you can explain exactly why `req.body` was undefined, without guessing.

---

### 7. Centralize error handling

Add an `AppError` class with a status code, a `NotFoundError` subclass, and one error middleware that turns them into responses.

**Done when**: no route handler writes a 404 response by hand, they only `throw`.

---

### 8. Move config into the environment

Move the port and any other constant into `.env`, load it with `dotenv`, and make the app fail loudly at startup if a required variable is missing.

**Done when**: deleting a variable from `.env` produces a clear crash on start, not a confusing error later.

---

### 9. Split one file into three layers

Take the CRUD code you have and split it into `routes/`, `controllers/` and `services/`.

**Done when**: the service file imports nothing from Express, and you could test it without starting a server.

---

### 10. Full CRUD, in memory

Finish all five routes for `problems` against an array, with correct status codes and the layered structure.

**Done when**: every row of the status code table in [Building the Problems CRUD API](7%20Building%20the%20Problems%20CRUD%20API.md) passes when tested with curl.

---

## Stretch

Write a middleware that rejects any request with a body larger than a set size, returning 413. It forces you to think about middleware order, streams and what happens before your handler ever runs.
