# Redis Caching

📌 These notes are intentionally lighter than the earlier phase folders. The roadmap's own rule for Phase 6: add each thing only when the project genuinely demands it. This file gives you enough to recognize the moment and get started, not a full deep dive done ahead of time.

## What Redis is

Redis is an in-memory data store. Unlike Postgres, which writes to disk and is built for structured, relational data, Redis keeps data in memory (RAM), making reads and writes extremely fast, at the cost of being less durable and not relational.

```
Postgres: disk-backed, structured, relational, the source of truth
Redis:    memory-backed, simple key-value, very fast, a cache in front of the source of truth
```

| | Postgres | Redis |
|---|---|---|
| Where data lives | Disk (durable) | Memory (fast, volatile) |
| Data shape | Tables, relations | Key-value, simple structures |
| Speed | Fast, but disk-bound | Much faster, memory-bound |
| Survives a restart | Yes | Only if configured to persist, not the default use case |
| Role here | Source of truth | Cache in front of the source of truth |

## When to reach for it

The leaderboard, built in [Building the Leaderboard](../7%20API%20Polish/2%20Building%20the%20Leaderboard.md) (Phase 4), is the roadmap's own named first candidate. It is expensive to compute (aggregating across many submissions) and does not need to be perfectly accurate to the second, "read-often, change-rarely" data, exactly the caching case described in [`04-scalability.md`](../0%20Concepts/04-scalability.md).

📌 **Rule of thumb, restated**: cache things that are read often and change rarely. Do not cache data that changes on every request, you would spend effort keeping the cache in sync for no real benefit.

## The basic pattern: cache-aside

```
Request comes in for the leaderboard
      |
      v
Check Redis: is "leaderboard" cached?
      |
   yes -----> return cached data, done, fast
      |
   no
      v
Query Postgres (the expensive aggregation)
      |
      v
Store the result in Redis, with an expiry
      |
      v
Return the result
```

```ts
import Redis from "ioredis";
const redis = new Redis(process.env.REDIS_URL!);

async function getLeaderboard() {
  const cached = await redis.get("leaderboard");
  if (cached) return JSON.parse(cached);

  const leaderboard = await computeLeaderboardFromDatabase(); // the expensive groupBy query
  await redis.set("leaderboard", JSON.stringify(leaderboard), "EX", 60); // expires in 60 seconds

  return leaderboard;
}
```

`"EX", 60` sets a time-to-live, after 60 seconds the cached value expires automatically, and the next request recomputes and re-caches it. This bounds how stale the leaderboard can ever get.

## Cache invalidation, the hard part

⚠️ The famous saying: "there are only two hard things in computer science, cache invalidation and naming things." A cache with an expiry (as above) is the simple, forgiving version, since staleness self-heals within a fixed time window. A trickier version: explicitly clearing a cache entry the moment underlying data changes (a new accepted submission should probably invalidate "leaderboard" immediately, not wait up to 60 seconds).

```ts
async function recordAcceptedSubmission(userId: number, problemId: number) {
  await submissionService.markAccepted(userId, problemId);
  await redis.del("leaderboard"); // invalidate, next request recomputes fresh
}
```

📌 Start with a simple time-based expiry. Add explicit invalidation only once you have felt the actual staleness problem in practice, not preemptively.

## Where Redis fits in your deployed stack

Managed Redis hosts (Upstash has a serverless, free-tier-friendly option, matching the "generous free tier" spirit of your Neon choice) work the same way Neon does for Postgres, a `REDIS_URL` in your environment variables, no server to manage yourself.

## Key takeaways

- Redis is a fast, in-memory cache, sitting in front of Postgres, not a replacement for it.
- The cache-aside pattern (check cache, fall back to the real query, store the result with an expiry) is the standard approach, and enough for AlgoRift's leaderboard.
- Time-based expiry is the simple, safe default for cache invalidation, explicit invalidation on write is a real upgrade, only reach for it once actually needed.
