# Basics of Node JS

## What Node.js is

A server-side runtime environment that executes JavaScript outside the browser, built on the V8 JavaScript engine and C++. JavaScript can now talk to native machine due to C++ and has OS-level capabilities (file system, networking, processes) via a non-blocking API

- Node.js is an open-source, cross-platform JavaScript runtime built on Chrome's V8 engine
- It enables developers to run JavaScript outside the browser to build fast, scalable server-side applications
- JavaScript was initially frontend-only, then Node.js (2009) enabled backend development as well

#### Concise history

- 2009 — Created by Ryan Dahl to address C10K problem using event-driven I/O
- 2010 — Package ecosystem begins with npm
- 2011–2014 — Rapid adoption for real-time apps. Governance issues → fork io.js
- 2015 — Reunification under Node.js Foundation; LTS model introduced
- 2019+ — Merged into OpenJS Foundation. Stable, enterprise-grade runtime with ES module support, async/await, worker threads

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

## When to use Node.js (strong fit)

1. Real-time systems
    - WebSockets, chat, multiplayer
    - Example: using Socket.IO
2. API layer / BFF
    - REST/GraphQL gateway aggregating microservices
    - Low latency, high concurrency
3. I/O-bound microservices
    - DB calls, external APIs, message queues
4. Streaming / pipelines
    - Log processing, media streaming, ETL
5. Serverless
    - AWS Lambda / edge functions (fast cold starts vs JVM)

## When not to use Node.js

1. CPU-bound workloads
    - Heavy computation (ML inference, video encoding)
    - In such cases prefer: Go, Rust, Native C++ addons
2. Strong multi-threading requirements
    - Complex parallelism → Java / Go
3. Large monolith with strict type guarantees
    - Node + TypeScript helps, but ecosystems like Java/Spring still dominate here
