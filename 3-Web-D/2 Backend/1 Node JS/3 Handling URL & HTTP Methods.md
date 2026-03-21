# Handling URL and HTTP Methods

- Handling URL and HTTP methods is part of building an HTTP server
- Conceptually separated as:
    - URL → resource
    - Method → action
- Combined → **routing layer**
- Frameworks automate this abstraction
- Think: **HTTP Server (transport) → Routing (decision) → Business Logic (execution)**

## 1. URL Handling (Path Parsing)

#### What it is

- Extracting and understanding **which resource is being requested**
- Comes from: `req.url`

#### Example

```
const url = req.url;

if (url === "/users") {
    // handle users route
}
```

#### Better Parsing (important)

```
const { URL } = require("url");
const myUrl = new URL(req.url, `http://${req.headers.host}`);

console.log(myUrl.pathname); // "/users"
console.log(myUrl.searchParams.get("id")); // query param

if (myUrl.pathname.startsWith("/users/")) {
    const id = myUrl.pathname.split("/")[2];
}
```

### Key Concepts

- **Pathname** → `/users`
- **Query Params** → `/users?id=10`
- **Dynamic Routes** (manual handling)

---

## 2. HTTP Method Handling

#### What it is

- Determines **what action to perform on the resource**
- Comes from: `req.method`

#### Common Methods

- GET → Read data
- POST → Create
- PUT → Update (full)
- PATCH → Update (partial)
- DELETE → Remove

## 3. Combining URL + Method (Routing)

This is the **real-world usage**

```
if (req.url === "/users" && req.method === "GET") {
    res.end("Get all users");
} else if (req.url === "/users" && req.method === "POST") {
    res.end("Create user");
}
```

**Insight** : **RESTful design** → Same URL, different methods → different behavior

---

## 4. Handling URL vs HTTP Method

| Concern         | Responsibility                |
| --------------- | ----------------------------- |
| HTTP Server     | Accept request, send response |
| URL Handling    | Identify resource             |
| Method Handling | Identify action               |
| Routing         | Combine both → decide handler |

---

## 5. What frameworks do

Instead of:

```
if (...) {}
```

Framework-style like Express.js : It abstracts routing into clean, declarative APIs

```
app.get("/users", handler);
app.post("/users", handler);
```

Example from Express JS,

```
const express = require('express');
const app = express();

app.get('/users', (req, res) => {
res.send('Get users');
});

app.post('/users', (req, res) => {
res.send('Create user');
});
```

Internally: Matches **URL** + Matches **method** → Calls correct handler

---

## 6. Common Mistakes

- Ignoring method → all requests treated same
- Parsing URL manually without handling query params
- Mixing routing with business logic
- Not handling unknown routes → missing 404
