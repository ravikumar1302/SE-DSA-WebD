# 04 - Scalability & Performance

**Scalability** = the ability to handle *more* (users, requests, data) by adding resources, without a rewrite. **Performance** = how fast/efficient the system is for a *given* load. Related but distinct: a fast system can fail to scale; a scalable system can be individually slow. You want both.

💡 **Why it matters:** success is a scaling problem. The architecture that serves 100 users can collapse at 100,000. Knowing the levers *before* you need them means you build in the right places from the start - and, just as importantly, know which optimizations to *skip* until you actually need them.

⚠️ **The golden rule of performance: measure first.** "Premature optimization is the root of all evil." Guessing where the slowness is wastes effort on the wrong thing. Profile, find the real bottleneck, fix *that*. Intuition about performance is famously wrong.

---

## Vertical vs Horizontal scaling - the two fundamental directions

### Vertical scaling (scaling **up**)
Make one machine more powerful - more CPU, RAM, faster disk.

- ✅ **Simple** - no code changes, just a bigger box
- ✅ No distributed-systems complexity
- ❌ **Hard ceiling** - there's a limit to how big one machine gets
- ❌ **Expensive** - top-end hardware costs disproportionately more
- ❌ **Single point of failure** - that one machine dies, you're down

### Horizontal scaling (scaling **out**)
Add more machines and spread the load across them.

- ✅ **Near-limitless** - just keep adding nodes
- ✅ **Resilient** - one node dies, others carry on
- ✅ **Cost-effective** - many commodity machines vs one supercomputer
- ❌ **Complex** - needs load balancing, and your app must be *stateless* (see below)
- ❌ Introduces distributed-systems problems (consistency, coordination)

⚖️ **Quick comparison:**

| | Vertical (up) | Horizontal (out) |
|---|---|---|
| How | Bigger machine | More machines |
| Ceiling | Limited by hardware | Practically unlimited |
| Failure | Single point | Redundant |
| Complexity | Low | Higher |
| App changes | None | Must be stateless |

📌 **Rule of thumb:** vertical scaling is the easy first move (bump the server size). But real growth demands horizontal - so **design for horizontal from the start** (be stateless), even if you scale vertically at first. Retrofitting statelessness later is painful.

---

## The enabler: Statelessness

A **stateless** server keeps *no* per-user memory between requests. Everything needed is either in the request itself or in shared storage (DB/cache). Any server can handle any request.

💡 **Why it's the linchpin of horizontal scaling:** if server A remembers your login in its local memory, your next request *must* go back to A. That breaks load balancing. If session state lives in a shared store (Redis/DB) instead, any server can serve you - now you can add servers freely.

⚠️ **Pitfall:** storing sessions, uploaded files, or caches in a single server's local memory/disk. It works with one server and silently breaks the moment you add a second. Push state to shared services.

---

## Load Balancing

A **load balancer** sits in front of your servers and distributes incoming requests across them.

**Common strategies:**
- **Round-robin** - each server in turn
- **Least connections** - send to the least-busy server
- **IP hash** - same client always to the same server (use only if you can't be stateless)

💡 It also provides **health checks** (stop sending traffic to a dead server) and is the thing that makes horizontal scaling actually usable. Tools/services: Nginx, HAProxy and cloud load balancers (AWS ELB, etc.).

---

## Caching - the single biggest performance lever

**Caching** = storing the results of expensive work so you can reuse them instead of recomputing/refetching.

💡 **Why it's so powerful:** the fastest work is the work you *don't do*. A database query taking 200ms, cached, becomes a 1ms lookup. Reads usually vastly outnumber writes, so caching reads is enormous leverage.

**Where caching happens (layers, outermost to innermost):**
1. **Client/browser cache** - the user's device stores responses
2. **CDN cache** - edge servers near users cache static assets (see below)
3. **Application cache** - your server caches computed results in memory or Redis
4. **Database cache** - the DB caches query results/pages internally

**Key concepts:**
- **TTL (Time To Live)** - how long a cached item stays valid before expiring
- **Cache invalidation** - removing/updating stale entries when the underlying data changes. *("There are only two hard things in computer science: cache invalidation and naming things.")* It's genuinely hard: serve stale data and users see wrong info; invalidate too aggressively and you lose the benefit.
- **Cache hit/miss** - found in cache (fast) vs not (fall through to the source)

**Common strategies:**
- **Cache-aside** - app checks cache; on miss, loads from DB and populates cache. Most common.
- **Write-through** - writes go to cache *and* DB together (cache always fresh, writes slower).
- **Write-back** - write to cache now, DB later (fast writes, risk of loss).

⚠️ **Pitfall:** caching data that changes constantly, or forgetting to invalidate - users see stale results and you'll spend hours confused. Cache things that are read-often and change-rarely first.

Tool: **Redis** is the default in-memory cache/store (file 10).

---

## CDN (Content Delivery Network)

A network of servers spread **geographically**, caching your static content (images, CSS, JS, videos) close to users.

💡 **Why:** physics. A user in Mumbai hitting a server in Virginia waits for data to cross the planet. A CDN serves them from a nearby edge node - dramatically faster, and it offloads traffic from your origin server. Examples: Cloudflare, AWS CloudFront, Fastly.

📌 Static assets → CDN, always. Increasingly, CDNs also cache/serve dynamic content and run edge functions.

---

## Database scaling - usually the real bottleneck

The database is where most apps hit their limit first (one DB, many app servers all hammering it). Levers, roughly in order of reach-for:

### 1. Indexing
Add indexes so the DB can *find* rows without scanning the whole table. Often a 100x win from one line. (Details in file 05.) **Do this first** - most "slow database" problems are missing indexes.

### 2. Read replicas (replication)
Copy the database to one or more **read-only replicas**. Send reads to replicas, writes to the primary.

💡 **Why:** most apps read far more than they write. Spreading reads across replicas relieves the primary. ⚠️ Replicas lag slightly behind (**replication lag**) - you might read data a moment after writing it and not see your own change ("read-after-write" issues). Design for it.

### 3. Partitioning
Splitting a large table into smaller pieces for manageability/performance.
- **Vertical partitioning** - split *columns* (rarely-used columns into a separate table).
- **Horizontal partitioning** - split *rows* (e.g., orders by date range) into partitions.

### 4. Sharding (horizontal partitioning across machines)
Split the data across **multiple database servers** by some key (e.g., users A-M on shard 1, N-Z on shard 2). Each shard holds a subset.

- ✅ Scales writes and storage beyond one machine.
- ❌ **Very complex** - cross-shard queries are painful, rebalancing is hard, transactions across shards are brutal. Choosing the shard key wrong is expensive to fix.

📌 **Order of operations for a slow DB:** index → cache → read replicas → (much later, if truly forced) sharding. Sharding is a last resort; most apps never need it.

### SQL vs NoSQL scaling note
Relational DBs traditionally scale reads well (replicas) but writes are harder (sharding). Many NoSQL stores were *designed* for horizontal scaling/sharding from the start - a key reason to choose them at massive scale (file 05).

---

## Asynchronous processing & queues

Not everything must happen *during* the request. If a user signs up and you send a welcome email synchronously, they wait for the email server. Instead: respond immediately, drop the email task on a **queue**, a **background worker** handles it later.

💡 **Why it helps scaling & UX:** keeps request/response fast, smooths load spikes (the queue buffers bursts) and isolates slow/unreliable work (email, image processing, reports) from the user-facing path. (Queues also power event-driven architecture - file 03.)

---

## Measuring performance - the vocabulary

You can't improve what you don't measure. Key metrics:

- **Latency** - time for a single request (how *slow*). Often reported as percentiles: **p50** (median), **p95**, **p99** (the slow tail most users eventually hit). Averages lie; watch p95/p99.
- **Throughput** - requests handled per second (how *much*).
- **Response time** vs **processing time** - total time seen by user vs time your code spent.
- **Utilization** - how busy CPU/memory/disk/network are.
- **Error rate** - % of requests failing under load.

**Load testing** - simulate many users to find where you break *before* real users do. Tools: k6, JMeter, Locust, Artillery.

📌 Set targets (e.g., "p95 under 200ms"), measure against them and let *data* drive optimization - not hunches.

---

## A practical scaling ladder (what to actually do, in order)

For a growing app, you typically climb this ladder - don't jump ahead:

1. **Optimize what you have** - fix N+1 queries, add DB indexes, remove obvious waste. (Cheapest wins.)
2. **Add caching** - cache hot reads (Redis) and static assets (CDN).
3. **Scale vertically** - bump the server/DB size. Buys time cheaply.
4. **Go stateless + scale horizontally** - multiple app servers behind a load balancer.
5. **Scale the database** - read replicas, then partitioning.
6. **Async/queues** - move slow work off the request path.
7. **Shard / go distributed** - only at genuinely massive scale.

⚠️ **The meta-pitfall:** building step 7 infrastructure for a step-1 problem. Solve the load you *have* (plus a little headroom), not the load you fantasize about. Most apps live happily on steps 1-3 for a long time.

---

## Key takeaways

- **Vertical** = bigger machine (simple, capped). **Horizontal** = more machines (unlimited, needs statelessness).
- **Statelessness** is the enabler of horizontal scaling - design for it early.
- **Caching** (app + CDN) is the biggest, cheapest performance lever - but invalidation is hard.
- The **database** is usually the first real bottleneck: **index → cache → replicas → shard (last resort).**
- **Measure first**, optimize the proven bottleneck and climb the scaling ladder in order.

➡️ Next: [`05-databases-and-storage.md`](05-databases-and-storage.md) - the data layer in depth.
