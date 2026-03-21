# Building HTTP Server in NodeJS

### 1. Core Concept

- Node.js uses an event-driven, non-blocking I/O model
- HTTP server is built on top of TCP using the `http` core module.
- Single-threaded event loop handles concurrent requests efficiently

### 2. Minimal Server

```
const http = require("http");

const server = http.createServer((req, res) => {
    console.log("New request received);
    res.writeHead(200, { "Content-Type": "text/plain" });
    res.end("Hello World");
});

server.listen(3000, () => {
    console.log("Server running on port 3000");
});
```

Key points:

- `createServer(callback)` → callback runs on every request
- `req` → readable stream (incoming request) i.e., metadata of user like IP, reuqest made etc
- `res` → writable stream (outgoing response)

---

### 3. Request Object (`req`)

- Contains:
    - `req.method` → GET, POST, etc.
    - `req.url` → route/path
    - `req.headers`

- For POST/PUT body:

```
let body = "";
req.on("data", (chunk) => (body += chunk));
req.on("end", () => {
    console.log(body);
});
```

---

### 4. Response Object (`res`)

- Methods:
    - `res.writeHead(statusCode, headers)`
    - `res.write(data)` (optional)
    - `res.end(data)`

- Example:

```
res.writeHead(200, { "Content-Type": "application/json" });
res.end(JSON.stringify({ success: true }));
```

---

### 5. Routing (Manual)

```
if (req.url === "/" && req.method === "GET") {
    res.end("Home");
} else if (req.url === "/about") {
    res.end("About");
} else {
    res.writeHead(404);
    res.end("Not Found");
}
```

**Insight:**
**Manual routing becomes messy → frameworks like Express abstract this**

---

### 6. Handling JSON Requests

```
req.on("end", () => {
    const data = JSON.parse(body);
});
```

- Always validate JSON → wrap in try-catch

---

### 7. Streaming (Important)

- Node treats req/res as streams → efficient for large data

```
const fs = require("fs");
fs.createReadStream("file.txt").pipe(res);
```

### 8. Headers & Status Codes

- Common headers:
    - `Content-Type`
    - `Authorization`

- Status codes:
    - `200` OK
    - `201` Created
    - `400` Bad Request
    - `404` Not Found
    - `500` Server Error

---

### 9. Async Operations

- Never block event loop:
- **BAD** : `const data = fs.readFileSync("file.txt");`
- **GOOD** : `fs.readFile("file.txt", (err, data) => {});`

### 10. Server Lifecycle

- Start: `server.listen(port);`
- Stop: `server.close();`

### 11. Error Handling

```
server.on("error", (err) => {
    console.error(err);
});
```

---

### 12. Scaling Considerations

- Node is single-threaded → use:
    - `cluster` module
    - Reverse proxy (Nginx)
    - Load balancer

- Handle:
    - Backpressure (streams)
    - Timeouts
    - Rate limiting

### 13. When to Use Frameworks

Use core `http` when:

- Learning internals
- Building minimal services

Use frameworks (e.g., Express) when:

- Routing complexity increases
- Middleware needed
- Faster development required

---

### 14. Mental Model (Important)

- Each request = event
- No thread per request
- Event loop delegates I/O to system
- Callback executes when ready

### 15. Common Pitfalls

- Blocking code (CPU-heavy tasks)
- Not ending response (`res.end`)
- Improper error handling
- Ignoring streams for large data
- Parsing request body incorrectly

---

### TL;DR

- `http.createServer()` → entry point
- `req` (input stream), `res` (output stream)
- Event loop handles concurrency
- Keep everything async and non-blocking
- Use streams for efficiency
- Move to frameworks for real-world apps
