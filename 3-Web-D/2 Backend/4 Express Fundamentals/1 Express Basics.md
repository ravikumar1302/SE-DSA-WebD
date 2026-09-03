# Express Basics

## What Express actually is

Express is a small library that sits on top of Node's built-in `http` module. It does not replace Node, it makes working with raw requests and responses much less repetitive.

Compare building the same route with plain Node vs Express.

**Plain Node:**

```ts
import http from "http";

const server = http.createServer((req, res) => {
  if (req.method === "GET" && req.url === "/problems") {
    res.writeHead(200, { "Content-Type": "application/json" });
    res.end(JSON.stringify([{ id: 1, title: "Two Sum" }]));
    return;
  }
  res.writeHead(404);
  res.end();
});

server.listen(3000);
```

**With Express:**

```ts
import express from "express";

const app = express();

app.get("/problems", (req, res) => {
  res.json([{ id: 1, title: "Two Sum" }]);
});

app.listen(3000);
```

Express handles the URL matching, the method checking, the header setting and the JSON conversion for you. Everything Express does, plain Node could also do, just with a lot more manual code. Seeing the raw version first (in the TypeScript project setup file) makes this clear instead of magical.

## Installing Express with TypeScript

```bash
npm install express
npm install -D @types/express
```

Express itself is written in plain JavaScript. `@types/express` is a separate package that adds the TypeScript type definitions for it, the same pattern as `@types/node`.

## The `app` object

```ts
import express from "express";

const app = express();
```

`app` represents your whole application. You attach routes, middleware and settings to it, then start it listening on a port.

## Basic routing

```ts
app.get("/problems", (req, res) => { /* ... */ });
app.post("/problems", (req, res) => { /* ... */ });
app.put("/problems/:id", (req, res) => { /* ... */ });
app.patch("/problems/:id", (req, res) => { /* ... */ });
app.delete("/problems/:id", (req, res) => { /* ... */ });
```

Each line registers a route: an HTTP method plus a path, paired with a handler function that runs when a matching request arrives.

## The `req` and `res` objects

Every route handler receives two objects.

| Object | Represents | Common uses |
|---|---|---|
| `req` (request) | The incoming request | `req.params`, `req.query`, `req.body`, `req.headers` |
| `res` (response) | The outgoing response | `res.json()`, `res.status()`, `res.send()` |

```ts
app.get("/problems/:id", (req, res) => {
  const id = req.params.id;         // reading data from the request
  res.status(200).json({ id });     // sending data back in the response
});
```

### Common `res` methods

| Method | What it does |
|---|---|
| `res.json(data)` | Sends `data` as JSON, sets `Content-Type` automatically |
| `res.status(code)` | Sets the status code, chainable: `res.status(201).json(data)` |
| `res.send(data)` | Sends a response, works for text, HTML or objects, less explicit than `res.json` |
| `res.end()` | Ends the response with no body, used for `204 No Content` |

📌 **Rule of thumb**: use `res.status(code).json(data)` for APIs. It is explicit about both the status code and the content type, which matters for the consistent response shapes covered later in Phase 4 of the roadmap.

## Starting the server

```ts
const PORT = 3000;

app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
```

`app.listen` starts the server and keeps the process running, waiting for incoming requests. The callback runs once, when the server successfully starts.

## Parsing JSON request bodies

By default, Express does not read the body of incoming requests. You must explicitly tell it to.

```ts
app.use(express.json());
```

This line adds a piece of middleware (explained in detail in the next file) that reads the raw request body, parses it as JSON and makes the result available on `req.body`. Without this line, `req.body` is `undefined` even if the client sent a JSON body.

```ts
app.use(express.json());

app.post("/problems", (req, res) => {
  console.log(req.body); // { title: "Two Sum", difficulty: "easy" }
});
```

⚠️ **Pitfall**: forgetting `app.use(express.json())` is one of the most common early Express bugs. Symptoms: `req.body` is `undefined`, or trying to read `req.body.title` throws a "cannot read property of undefined" error.

## A minimal complete Express app

```ts
import express from "express";

const app = express();

app.use(express.json());

app.get("/health", (req, res) => {
  res.status(200).json({ status: "ok" });
});

app.get("/problems", (req, res) => {
  res.status(200).json([{ id: 1, title: "Two Sum" }]);
});

app.listen(3000, () => {
  console.log("Server running on http://localhost:3000");
});
```

## Key takeaways

- Express is a thin, convenient layer over Node's `http` module, not a separate technology.
- `req` holds everything about the incoming request, `res` is used to build and send the response.
- `express.json()` must be added explicitly before `req.body` will work.
- `res.status(code).json(data)` is the standard pattern for sending API responses.
