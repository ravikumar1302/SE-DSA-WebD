# Performance Debugging

"The API feels slow" needs the same treatment as the frontend equivalent, turning a vague feeling into a specific, measured cause, rather than guessing at what to optimize.

## Where server-side slowness usually comes from

```
Slow request, possible causes, roughly in order of likelihood:
1. A slow database query (missing index, N+1, no LIMIT)
2. A blocking synchronous call on the main thread
3. An external API call with no timeout, waiting far too long
4. Genuinely heavy computation (rare, on a typical CRUD backend)
```

📌 On a typical backend like AlgoRift, the database is almost always the first suspect, checking Prisma's query log (previous file) before reaching for a Node profiler usually finds the answer faster.

## Timing a request end to end

A simple first check, before any profiler, times each major step directly.

```ts
app.post("/submissions", async (req, res) => {
  console.time("validate");
  const data = SubmissionSchema.parse(req.body);
  console.timeEnd("validate");

  console.time("db-query");
  const problem = await prisma.problem.findUnique({ where: { id: data.problemId } });
  console.timeEnd("db-query");

  console.time("create");
  const submission = await submissionService.create(data);
  console.timeEnd("create");

  res.status(201).json(submission);
});
```

The printed timings immediately show which step is disproportionately slow, often the database query, without needing a full profiling session for what turns out to be an obvious answer.

## The event loop and blocking the main thread

Node is single-threaded for JavaScript execution, a genuinely slow synchronous operation blocks that one thread entirely, every other request waiting on the same process stalls until it finishes, not just the request that triggered it.

```ts
app.get("/report", (req, res) => {
  const data = fs.readFileSync("large-file.json"); // blocks EVERY request, not just this one
  res.json(JSON.parse(data));
});
```

```
readFileSync blocking:
Request A arrives -> starts reading file synchronously -----> finishes -> responds
Request B arrives during this time -> waits, cannot be handled at all until A's blocking call finishes

Async version (readFile, not readFileSync):
Request A arrives -> starts reading (non-blocking) -> Node handles Request B meanwhile -> A finishes, responds
```

Fix: the async, non-blocking version of any such call (`fs.readFile` instead of `fs.readFileSync`, an async database driver, and so on), the async version hands control back to Node's event loop while waiting, instead of freezing it.

## Measuring event loop lag directly

A more precise signal than "requests feel slow" is measuring how delayed the event loop itself has become.

```ts
import { monitorEventLoopDelay } from "perf_hooks";

const histogram = monitorEventLoopDelay();
histogram.enable();

setInterval(() => {
  console.log("event loop delay (ms):", histogram.mean / 1e6);
}, 5000);
```

A consistently rising number here, independent of any single request, points directly at something blocking the event loop somewhere in the app, not at any one specific slow query.

## Node's built-in profiler, for genuinely heavy computation

For the rarer case of actual CPU-heavy work (not I/O, not a database), Node's `--prof` flag records a CPU profile.

```bash
node --prof index.js
# generate some load against the running server
node --prof-process isolate-0001-v8.log > profile.txt
```

The output ranks functions by how much CPU time they consumed, pointing at the actual heavy computation, rather than the database or network calls covered elsewhere in this file, which this profiler will not show as the bottleneck since they spend most of their time waiting, not computing.

## A quick decision guide

| Symptom | Check first |
|---|---|
| One specific endpoint is slow | Prisma query log for that route, file 5 |
| Everything feels slow at once, even unrelated routes | A blocking synchronous call somewhere, or event loop delay |
| Slowness only under real concurrent load, not alone | Event loop delay monitoring, or connection pool limits |
| Genuinely CPU-heavy work (image processing, complex calculation) | Node's `--prof` profiler |

## Key takeaways

- On a typical CRUD backend, a slow database query is the most common cause of a slow endpoint, check that before reaching for a profiler.
- A blocking synchronous call freezes the entire process for every request, not only the one that triggered it, the async version of the same call fixes this.
- `monitorEventLoopDelay` measures event loop health directly, useful when slowness affects unrelated routes at once.
- Node's `--prof` flag is for genuinely CPU-heavy computation, not for diagnosing slow database or network calls, which spend their time waiting, not computing.
