# Node.js Runtime and the Event Loop

Express (covered earlier in this folder) sits on top of Node. This file covers what Node itself actually is and how it manages to handle many requests using a single thread, the mechanics underneath every route handler built so far.

## What Node.js is

Node.js is a runtime that executes JavaScript outside a browser, built on Chrome's V8 engine plus a C++ layer that gives JavaScript access to OS-level capabilities: the file system, networking, processes. Before Node (2009), JavaScript only ran inside browsers, Node made backend development in JavaScript possible.

```
Browser JavaScript:  runs inside a browser, limited to browser APIs
Node.js JavaScript:  runs on a machine directly, full OS access (files, network, processes)
```

## Core features, in short

| Feature | What it means |
|---|---|
| Single-threaded | JavaScript itself runs on one thread |
| Non-blocking, event-driven | Handles many requests concurrently without waiting on each one |
| V8 engine | Compiles JavaScript to machine code quickly |
| npm ecosystem | A huge library of reusable packages |
| Good fit | APIs, real-time apps (chat, WebSockets), streaming, I/O-heavy work |
| Poor fit | CPU-heavy work (video encoding, ML inference), better suited to Go, Rust or native code |

## The event loop, how one thread handles many requests

Traditional servers often spin up a new thread per incoming request. Node does not, every request is placed into a queue, and one thread (the event loop) processes them.

```
Many requests arrive
      |
      v
 ┌─────────────┐
 │ Event queue │   (FIFO, first in first out)
 └─────────────┘
      |
      v
 ┌──────────────┐
 │  Event loop   │   picks the next item, runs its callback, repeat
 │ (single thread)│
 └──────────────┘
```

The event loop must never sit and wait, if it blocks on one request, every other request stalls behind it. This is the single most important rule of writing correct Node code: never block the main thread.

## Non-blocking (async) work, the normal case

Network calls, async file reads and async database queries do not block the event loop. Node hands the actual work off, moves on to the next item in the queue immediately and comes back to run the callback once the work finishes.

```ts
fs.readFile("file.txt", (err, data) => {
  // runs later, once the read finishes, the event loop kept working in the meantime
});
```

```
Event loop delegates the operation (to the OS or a background thread)
      |
      v
Event loop immediately moves to the next queued request
      |
      v
When the operation finishes, its callback is placed back on the queue
      |
      v
Event loop picks it up when it gets there, runs the callback
```

This is why Node handles thousands of concurrent connections on a single thread, it is never sitting idle waiting for I/O, it is always working on whatever is ready next.

## Blocking (synchronous) work, the case to avoid

Some operations run directly on the main thread and hold it until they finish.

```ts
const data = fs.readFileSync("file.txt"); // blocks the event loop until the read completes
```

While this line runs, no other request can be processed, at all. ⚠️ This is the most common way to accidentally destroy Node's whole concurrency advantage, one blocking call in a hot code path stalls every concurrent user.

| | Async (non-blocking) | Sync (blocking) |
|---|---|---|
| Example | `fs.readFile(...)` | `fs.readFileSync(...)` |
| Event loop behavior | Delegates, moves on immediately | Waits, does nothing else until done |
| Other requests during the operation | Still processed normally | Stall until this one finishes |
| Correct use | Almost always, in a server |
| When sync is acceptable | Startup scripts, one-off CLI tools, never inside a request handler |

## libuv and the thread pool

Some work genuinely needs a real background thread, not just delegation to the OS, examples: certain file system operations, crypto, compression. Node hands these to `libuv`, its C++ core library, which runs them on a small thread pool (4 threads by default, configurable).

```
JavaScript execution:  always single-threaded
Heavy/OS-level tasks:  handled by libuv's thread pool, in the background
```

The distinction matters: your own JavaScript code never runs on more than one thread at a time, but Node itself uses background threads to keep that one JS thread from ever blocking on slow work.

## When something CPU-heavy genuinely blocks the loop

Large JSON parsing, image processing, heavy computation done directly in your JavaScript code, not delegated to libuv or the OS, blocks the event loop the same way a synchronous file read does, since it is just JavaScript running on the one thread.

📌 **Fix**: move genuinely CPU-heavy work either to Node's `worker_threads` module (a real, separate thread for JS execution) or to an entirely separate service or background job (the queue pattern covered in the Advanced Topics folder).

## Scaling past one thread: the cluster module

Node's single-threaded event loop is excellent for I/O-heavy work, but it only uses one CPU core. On a multi-core machine, the `cluster` module forks multiple copies of the app, each with its own event loop, sharing the same port.

```
             ┌── Worker 1 (event loop, core 1)
Incoming ────┼── Worker 2 (event loop, core 2)
requests     ├── Worker 3 (event loop, core 3)
             └── Worker 4 (event loop, core 4)
```

📌 A managed platform like Railway (Phase 5) often handles this kind of horizontal scaling for you, by running multiple instances of the whole app rather than you manually configuring `cluster` yourself, worth knowing the module exists, rarely something to reach for directly on a project at this scale.

## Mental model to hold onto

```
Queue -> Event loop -> delegate (OS/libuv/thread pool) -> callback -> response
```

One thread orchestrates everything, it does not personally execute every slow operation itself.

## Key takeaways

- Node handles many concurrent requests with one JavaScript thread, by delegating slow work and never sitting idle waiting on it.
- Synchronous, blocking calls (`readFileSync` and similar) freeze the entire server for every user while they run, avoid them inside request handlers.
- `libuv`'s thread pool handles genuinely blocking OS-level work in the background, JavaScript itself still only ever runs on one thread at a time.
- CPU-heavy JavaScript (not I/O) is the one thing that truly blocks the event loop, worker threads or a separate background job are the fix, not synchronous code.
