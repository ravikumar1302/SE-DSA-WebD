# Getting Started with Express + Node.js (Why + How)

## 1. Why **Express.js** is needed

**Problem with Node `http`:**

- Manual routing → `if (req.url && req.method)`
- No middleware system
- Manual body parsing
- Boilerplate grows fast

**Express solves:**

- Clean routing (`app.get`, `app.post`)
- Middleware support (core strength)
- Request/response utilities
- Faster development, cleaner code

👉 Think:

- > Node `http` = low-level engine
- > Express = developer-friendly layer

---

## 2. Minimal Setup

```
npm init -y
npm install express
```

```
const express = require("express");
const app = express();

app.listen(3000, () => {
    console.log("Server running");
});
```

## 3. Basic Routing

```
app.get("/", (req, res) => {
    res.send("Home");
});

app.post("/users", (req, res) => {
    res.send("Create user");
});
```

- Method + path → handler
- No manual `if-else`

---

## 4. Middleware (Core Concept)

Middleware = function that runs **before final handler**

```
app.use((req, res, next) => {
    console.log("Request received");
    next();
});
```

- Every request passes through a **chain of middleware functions**
- Each middleware:
    - Can modify `req/res`
    - Must call `next()` to continue

👉 Flow:

```
Request → Middleware1 → Middleware2 → Route → Response
```

- If `next()` not called → request hangs

### Use cases:

- Logging
- Authentication
- Validation
- Parsing

---

## 5. Parsing JSON Body

```
app.use(express.json());
```

```
app.post("/data", (req, res) => {
    console.log(req.body);
});
```

- `express.json()` is a **built-in middleware** that parses incoming JSON request body
- Without it, `req.body` is `undefined` for POST/PUT requests

👉 Runs before routes → attaches parsed data to `req.body`

## 6. Route Params vs Query

```
app.get("/users/:id", (req, res) => {
    console.log(req.params.id);
});
```

```
app.get("/users", (req, res) => {
    console.log(req.query.age);
});
```

- **Route Params (`req.params`)**
    - Part of URL path → used to identify a specific resource
    - Example: `/users/:id` → `/users/10`

- **Query Params (`req.query`)**
    - Optional modifiers → filtering, pagination
    - Example: `/users?age=25`

👉 Rule:
`params = identity` • `query = filters/options`

## 7. Response Helpers

```
res.send("text");
res.json({ success: true });
res.status(404).send("Not Found");
```

- Express wraps Node response to simplify sending data:
    - `res.send()` → auto handles content-type
    - `res.json()` → sends JSON + sets header
    - `res.status()` → chainable status setter

👉 Removes need for manual `writeHead` + `end`

## 8. Folder Structure (Basic)

```
project/
 ├── server.js
 ├── routes/
 ├── controllers/
 ├── middleware/
```

- Separates concerns:
    - `routes/` → defines endpoints
    - `controllers/` → business logic
    - `middleware/` → reusable logic (auth, logging)

👉 Prevents “everything in one file” problem → improves scalability

## 9. Mental Model

```
Request → Middleware → Route Match → Handler → Response
```

## 10. When to Use Express

Use Express when:

- Building APIs
- Handling multiple routes
- Need middleware (auth, logging, etc.)

Avoid raw Node unless:

- Learning internals
- Building ultra-light service

## TL;DR

- Express removes boilerplate of Node `http`
- Adds routing + middleware + utilities
- Makes backend scalable and maintainable
- Industry standard for basic Node backend
