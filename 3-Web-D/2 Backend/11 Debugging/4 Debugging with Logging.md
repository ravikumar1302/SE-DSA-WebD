# Debugging with Logging

`console.log` works locally, on a deployed server it becomes the only window into what happened, since there is no attached debugger and no browser DevTools. This file covers turning ad hoc logging into something that actually helps once real requests, from real users, are involved.

## Why `console.log` alone falls short in production

- No log levels, an important error and a routine debug message look identical.
- No structure, parsing "user 5 created problem 12 at some point" back out of free text later is painful.
- No way to tell which logs belong to the same request, once many requests are happening at once, their logs interleave in the terminal.

## Log levels

A real logger (Pino and Winston are common choices for a Node backend) supports levels, letting you filter by severity instead of seeing everything or nothing.

| Level | Use for |
|---|---|
| `error` | Something failed, needs attention |
| `warn` | Something unexpected, not fatal |
| `info` | Normal events worth recording, "user registered," "submission created" |
| `debug` | Detailed, verbose, usually off in production |

```ts
import pino from "pino";
const logger = pino();

logger.info({ userId: 5 }, "user registered");
logger.error({ err, userId: 5 }, "failed to create submission");
```

📌 In production, set the minimum level to `info` or higher, `debug` logs stay available for local development without flooding production logs with detail nobody needs day to day.

## Structured logging, objects instead of strings

```
Unstructured:
"User 5 created problem 12 at 2024-01-01"

Structured:
{ "userId": 5, "action": "create_problem", "problemId": 12, "timestamp": "2024-01-01T10:00:00Z" }
```

A structured log is a JSON object, not a sentence. This looks like more typing at first, but it means logs can be searched, filtered and aggregated by field later, "show me every log where `userId` is 5," a query that a plain string log cannot answer without fragile text parsing.

## Correlation IDs, tracing one request through many logs

A single request can produce several log lines across different functions, middleware, a service call, a database query. Without something tying them together, those lines look unrelated once mixed in with logs from other simultaneous requests.

```ts
app.use((req, res, next) => {
  req.requestId = crypto.randomUUID();
  next();
});

app.post("/submissions", (req, res) => {
  logger.info({ requestId: req.requestId }, "submission received");
  // ...
  logger.info({ requestId: req.requestId }, "submission validated");
});
```

Every log line from this one request carries the same `requestId`, filtering logs by that id reconstructs the full story of exactly this request, cleanly separated from every other request happening at the same time.

```
Without a requestId, mixed together:
submission received
GET /leaderboard hit
submission validated
leaderboard cache hit
submission saved

With a requestId, filtered to one value:
[req-abc] submission received
[req-abc] submission validated
[req-abc] submission saved
```

## What to actually log

⚠️ **Pitfall**: logging every single request and response body in full detail creates enormous, mostly useless log volume, and can accidentally log sensitive data (passwords, tokens) if not careful. Log intent and outcome ("submission created, id 42"), not the entire raw payload, and explicitly avoid logging passwords, tokens or full card numbers, even by accident through a generic "log the whole request body" habit.

## Logging as a debugging strategy, not just an operations tool

The same log-driven approach from the async debugging file, one log per meaningful step, works as a deliberate debugging technique, not only as permanent production logging. Temporarily raising the log level, or adding a few `logger.debug` calls around a suspect code path, then reading through the sequence, is often faster than attaching a debugger for a bug that only reproduces under real, hard-to-simulate traffic.

## Key takeaways

- A real logger with levels (`error`, `warn`, `info`, `debug`) replaces plain `console.log` once code runs where you cannot attach a debugger.
- Structured (object-shaped) logs can be filtered and searched later, plain sentence logs cannot.
- A correlation/request id on every log line from one request lets you reconstruct that request's full story even with many requests happening at once.
- Log intent and outcome, never passwords or tokens, and avoid logging entire raw request bodies as a default habit.
