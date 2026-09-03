# 03 - System Architecture

If design patterns (file 02) are about structuring *code*, architecture is about structuring the *whole system* - how big the pieces are, whether they run together or separately and how they communicate. This is the level where "should this be one app or twenty?" gets decided.

💡 **Why it matters:** architecture decisions are the *expensive* ones. A bad variable name is a 30-second fix; splitting a monolith into microservices too early can cost a team months. Getting the shape right - for *your* actual scale and team - is one of the highest-leverage skills.

---

## Part A - Internal architecture (how one app is layered)

Even a single app needs internal structure. The dominant idea is **layering**: separate code by *concern*, with each layer only talking to the one below it.

### Layered (N-tier) architecture

```
┌─────────────────────────────────────┐
│  Presentation  (controllers/routes) │  ← HTTP in/out, no business logic
├─────────────────────────────────────┤
│  Business/Service   (the logic)     │  ← rules, workflows, decisions
├─────────────────────────────────────┤
│  Data Access   (repositories/ORM)   │  ← talking to the database
├─────────────────────────────────────┤
│  Database                           │
└─────────────────────────────────────┘
```

💡 This is **Separation of Concerns** made physical. A request flows down; data flows up. Each layer is swappable and testable in isolation. This is the default, and you should reach for it first - it's the concrete form of the Controller → Service → Repository pattern from file 02.

### Hexagonal architecture (Ports & Adapters)

A refinement: put your **business logic in the center**, completely ignorant of the outside world. It defines **ports** (interfaces) for what it needs. **Adapters** connect real things (a database, an email API, a web framework) to those ports.

💡 **Why:** your core logic depends on *nothing external* - not your web framework, not your DB. You can swap Postgres for MongoDB, or Express for something else, by writing a new adapter - the core never changes. It's Dependency Inversion taken to the architectural level. Also called "Clean Architecture" / "Onion Architecture" in close variants.

```
            ┌──────────────────────────────┐
            │        Web adapter            │  (Express routes)
            └──────────────┬───────────────┘
                           │  port (interface)
            ┌──────────────▼───────────────┐
            │                              │
            │        Core business          │  knows nothing about
            │        logic, pure            │  Express, Postgres or email
            │                              │
            └──────┬────────────────┬──────┘
                   │ port           │ port
      ┌────────────▼─────┐   ┌──────▼─────────────┐
      │ Database adapter │   │  Email adapter      │
      │ (Prisma)         │   │  (SMTP or an API)   │
      └──────────────────┘   └────────────────────┘
```

Swapping Prisma for something else means writing one new adapter. The core never changes, because it only ever knew the port, not the tool behind it.

⚠️ **Pitfall:** overkill for small apps. The indirection pays off in large, long-lived systems; in a weekend project it's just extra files. Start layered; adopt hexagonal when the core logic is valuable enough to protect.

---

## Part B - Deployment architecture (how many pieces, running where)

This is the famous **monolith vs microservices** debate - plus the options in between and around it.

### Monolithic architecture

The entire application - all features - is **one codebase, one deployable unit, one process**. Users, orders, payments, notifications: all in one app, sharing one database.

**Strengths:**
- ✅ **Simple to build, run and deploy** - one thing to reason about
- ✅ **Easy local development** - clone, run, done
- ✅ **Fast internal calls** - functions calling functions, no network
- ✅ **Simple transactions/consistency** - one database, ACID is easy
- ✅ **Easier debugging** - one log stream, one process to trace

**Weaknesses:**
- ❌ **Scales as a whole** - must scale everything even if only one part is hot
- ❌ **Tight coupling risk** - without discipline it becomes a "big ball of mud"
- ❌ **Big blast radius** - one bad deploy can take the whole app down
- ❌ **Tech lock-in** - the whole thing is one language/framework
- ❌ **Slower for large teams** - everyone editing one codebase creates friction

### Modular Monolith (the underrated middle)

A monolith, but **internally split into well-bounded modules** with strict boundaries - as if they *could* be separate services, but they deploy together.

💡 **Why it's often the sweet spot:** you get the operational simplicity of a monolith with much of the organizational clarity of microservices - and if you ever *do* need to split out a service, the boundaries are already drawn. Many teams that "should do microservices" are actually best served here.

📌 **Rule of thumb:** **Start with a (modular) monolith.** Almost always the right first answer.

### Microservices architecture

The application is split into **many small, independent services**, each owning one business capability, each **separately deployable**, usually with **its own database**, communicating over the network (HTTP/gRPC/messaging).

**Strengths:**
- ✅ **Independent scaling** - scale only the hot service
- ✅ **Independent deployment** - ship one service without redeploying everything
- ✅ **Team autonomy** - each team owns a service end-to-end
- ✅ **Tech flexibility** - each service can use a different language/DB
- ✅ **Fault isolation** - one service down doesn't necessarily kill the rest

**Weaknesses (this is the crucial part beginners underestimate):**
- ❌ **Massive operational complexity** - now you run, monitor and deploy *many* systems
- ❌ **The network is unreliable** - calls fail, lag, retry; you must design for it
- ❌ **Distributed data is hard** - no easy cross-service transactions; consistency becomes a project (Saga patterns, eventual consistency)
- ❌ **Hard to debug** - a request spans many services; you need distributed tracing
- ❌ **Infrastructure overhead** - service discovery, API gateways, message brokers, orchestration

⚖️ **Monolith vs Microservices, head to head:**

| Dimension | Monolith | Microservices |
|---|---|---|
| Initial speed | Fast | Slow (lots of setup) |
| Operational complexity | Low | High |
| Scaling granularity | Whole app | Per service |
| Deployment | One unit | Many independent |
| Data consistency | Easy (one DB, ACID) | Hard (distributed) |
| Debugging | Straightforward | Needs tracing |
| Team fit | Small-medium teams | Many autonomous teams |
| Failure blast radius | Whole app | Isolated (ideally) |
| Best when | Starting out, unclear domain | Large scale, large org, clear boundaries |

💡 **The honest truth:** microservices solve an *organizational and scale* problem, not a code-quality one. You adopt them when your **team size** and **scale** make a monolith painful - not because they're "modern." Most famous microservice architectures started as monoliths and split *later*, once they understood their domain. Splitting a domain you don't yet understand just draws the boundaries in the wrong places.

⚠️ **The #1 architecture mistake:** starting a new project with microservices. You pay all the complexity costs upfront while still figuring out what you're even building. **Monolith first.**

---

## Part C - Other important styles

### Service-Oriented Architecture (SOA)
The older enterprise ancestor of microservices - larger services, often sharing infrastructure and a central "enterprise service bus." Microservices are essentially SOA's leaner, more independent descendant. Worth knowing as context.

### Serverless / Functions-as-a-Service (FaaS)
You write individual **functions**; the cloud provider runs them **on demand**, auto-scales them and you pay **only when they run**. No servers to manage.

**Strengths:** ✅ zero server management, ✅ auto-scaling, ✅ pay-per-use (cheap at low volume), ✅ fast to ship small things.
**Weaknesses:** ❌ **cold starts** (first call after idle is slow), ❌ vendor lock-in, ❌ time/resource limits per function, ❌ can get *expensive* and hard to trace at high scale, ❌ awkward for long-running or stateful work.

💡 Great for event-driven tasks, glue code, APIs with spiky/low traffic and side jobs. Note: your Next.js route handlers deployed on Vercel are essentially serverless functions - you've likely used this without naming it.

### Event-Driven Architecture (EDA)
Components communicate by **emitting and reacting to events** rather than calling each other directly. A service publishes "OrderPlaced"; other services react (charge payment, reserve stock, send email) - the publisher doesn't know who's listening.

- **Strengths:** ✅ extreme decoupling, ✅ great for async workflows, ✅ easy to add new reactors without touching producers, ✅ naturally resilient (events can queue and retry).
- **Weaknesses:** ❌ harder to follow the overall flow ("where did this happen?"), ❌ eventual consistency, ❌ needs a message broker (Kafka, RabbitMQ, etc.).

💡 It's the **Observer pattern** (file 02) at system scale, usually built on a **message queue/broker** (file 10). Often used *within* or *alongside* microservices to decouple them.

### Message Queues & Brokers (the plumbing under EDA and microservices)
A **queue** holds messages between a producer and consumer so they don't have to be available at the same time.

💡 **Why:** decouples services (producer fires and forgets), smooths load spikes (work piles up in the queue instead of crashing you), enables retries and background processing. Tools: RabbitMQ, Apache Kafka, AWS SQS, Redis-based queues. (More in file 10.)

---

## Part D - Cross-cutting architectural concerns

Regardless of style, these apply:

- **Statelessness** - servers shouldn't store per-user session state in memory; keep it in a DB/cache so any server can handle any request. This is what makes horizontal scaling possible (file 04).
- **API Gateway** - a single entry point in front of many services: routing, auth, rate limiting, aggregation (file 06).
- **Configuration** - externalize config/secrets (env vars), never hardcode; same code runs in dev/staging/prod with different config.
- **Observability** - you can't fix what you can't see: logging, metrics, tracing (file 09).

---

## Choosing an architecture - a practical decision guide

📌 Ask, in order:
1. **How big is the team?** Small → monolith. Many autonomous teams → consider splitting.
2. **Do you understand the domain?** Unclear → monolith (don't draw boundaries blind).
3. **What's the real scale?** Modest/unknown → monolith. Proven massive, uneven load → selective microservices.
4. **What's your ops maturity?** Can't monitor/deploy one service well → you're not ready for twenty.

**Default answer for you, today:** modular monolith, layered internally, deployed as one unit. It'll take you *very* far. Split out a service only when a specific, real pain demands it.

---

## Key takeaways

- **Internal** structure: layer by concern (Presentation → Service → Data). Upgrade to hexagonal when the core is worth protecting.
- **Deployment** structure: **monolith first**, modular monolith as it grows, microservices only when team + scale force it.
- Microservices trade code simplicity for operational complexity - that trade only pays at large scale/org.
- **Serverless, event-driven, queues** are tools for specific problems (spiky load, async decoupling), not defaults.
- The recurring theme: **decouple by clear boundaries, defer the expensive splits until you have real reason.**

---

## Where this shows up in the build

| Idea here | Where it becomes real |
|---|---|
| Layered architecture | [Folder Structure: Routes, Controllers, Services](../4%20Express%20Fundamentals/6%20Folder%20Structure%20-%20Routes%20Controllers%20Services.md) |
| Monolith versus microservices | [Microservices vs Monolith](../10%20Microservices%20and%20Distributed%20Systems/0%20Microservices%20vs%20Monolith.md) |
| Serverless versus containers versus VPS | [Where Backends Run](../8%20Deploy/0%20Where%20Backends%20Run.md) |
| Event-driven work, queues | [Background Jobs and Queues](../9%20Advanced%20Topics/1%20Background%20Jobs%20and%20Queues.md) |
| Orchestration | [Kubernetes](../10%20Microservices%20and%20Distributed%20Systems/1%20Kubernetes.md) |

➡️ Next: [`04-scalability.md`](04-scalability.md) - what happens when the users actually arrive.
