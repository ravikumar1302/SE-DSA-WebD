# Practice: Debugging

Like the frontend debugging practice file, these are scenarios, not code-writing tasks. For each one, work out which tool from this folder you would reach for and in what order, before checking the hint.

---

### 1. A route returns 404 that should exist

`GET /problems/featured` returns "not found," even though the route is clearly defined in the code.

**Think through**: what order are routes checked in, and could an earlier route be capturing this request first.

**Hint**: check for a `/problems/:id` route registered above it, route order and parameter matching, from file 2.

---

### 2. `req.body` is always empty

A POST route logs `req.body` as `{}` no matter what the client actually sent.

**Think through**: is this a client problem or a server problem, and what single piece of middleware is almost always the cause.

**Hint**: `express.json()` missing, or registered after this route, confirm with the request-logging middleware from file 2 first.

---

### 3. The server crashes overnight with no clear cause in the request logs

The process dies a few hours after starting, with no specific failing request visible right before the crash.

**Think through**: what failure mode surfaces later, disconnected from the code that actually caused it.

**Hint**: an unhandled promise rejection, an async call somewhere with no `await`, `.catch`, or error-handling wrapper, from file 3.

---

### 4. One specific endpoint is slow, others are fine

`GET /problems` takes three seconds, every other endpoint responds normally.

**Think through**: what is the first thing to check on a typical CRUD backend before assuming anything else.

**Hint**: turn on Prisma's query log, file 5, count the queries, check for an N+1 pattern before suspecting anything else.

---

### 5. Auth works locally, fails immediately after deploying

Login and protected routes work fine on `localhost`, every protected route returns 401 once deployed.

**Think through**: what environment difference commonly explains exactly this symptom.

**Hint**: `JWT_SECRET` not set, or set to a different value, in the deployed environment, file 6 and file 7.

---

### 6. Everything gets slower under real traffic, not when tested alone

The API feels fine when tested by itself, noticeably slower once several real users are active at the same time.

**Think through**: what kind of problem only shows up under concurrent load, and how would you measure it directly rather than guessing.

**Hint**: a blocking synchronous call, or event loop delay, measure directly with `monitorEventLoopDelay` rather than assuming it is any one specific route, file 8.

---

### 7. Build a minimal repro for a real bug

Pick a real bug you have hit in your own backend code (or intentionally introduce one). Write the smallest possible `curl` command or standalone script that reliably reproduces it, with nothing unrelated left in.

**Think through**: how much of the original request, headers, auth, unrelated fields, turned out to be unnecessary to trigger the bug.

**Hint**: this is the minimal reproduction exercise from file 9, applied for real once is a different skill than reading about it.
