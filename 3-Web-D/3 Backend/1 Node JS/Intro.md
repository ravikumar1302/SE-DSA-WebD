# Basics of Node JS

- Node.js is an open-source, cross-platform JavaScript runtime built on Chrome's V8 engine
- It enables developers to run JavaScript outside the browser to build fast, scalable server-side applications
- JavaScript was initially frontend-only, then Node.js (2009) enabled backend development as well

#### Features of Node JS

- Server-Side JavaScript: Runs JavaScript outside the browser for backend development
- Asynchronous & Non-Blocking: Handles multiple requests efficiently using an event-driven model
- Single-Threaded Event Loop: operates on a single thread but efficiently handles multiple concurrent requests using an event loop
- V8 Engine: Uses Google’s high-performance engine to execute JavaScript quickly
- Scalable & Lightweight: Suitable for microservices and high-traffic applications
- Supports the creation of REST APIs, real-time applications & microservices
- Rich NPM Ecosystem: Provides access to thousands of reusable open-source packages and Comes with a rich library of modules through npm (Node Package Manager)
- Efficient for scalable network applications

Example code

```
// Import the http module
const http = require("http");

// Create a server
const server = http.createServer((req, res) => {
    res.statusCode = 200;
    res.setHeader("Content-Type", "text/plain");
    res.end("Welcome to the Node.js Tutorial");
});

// Listen on port 3000
server.listen(3000, () => {
    console.log(
        "Server is running on http://localhost:3000");
});
```

### Need of Node.js

- Allows developers to build fast, scalable server-side applications using JavaScript
- Enables full-stack development with a single language
- Ideal for real-time apps like chat & gaming servers
- Handles I/O-intensive tasks efficiently with non-blocking architecture
- Supported by a large community and vast npm ecosystem
