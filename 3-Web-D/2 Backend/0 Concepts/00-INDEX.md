# Backend Software Engineering - Concept Handbook

A **tech-stack-agnostic** guide to the engineering ideas *underneath* backend development. Your Node/TS roadmap teaches you *how to build*; this handbook teaches you *why things are built the way they are* - the concepts that stay true whether you use Node, Python, Go or Java.

Written beginner-first: every concept comes with **what it is → why it exists → comparison/tradeoffs → pitfalls.**

---

## How to read this

You don't need to read in order, but this order builds cleanly:

| # | File | What it covers | Read when |
|---|---|---|---|
| 01 | [`01-foundations.md`](01-foundations.md) | Software engineering principles: modularity, coupling/cohesion, SOLID, DRY/KISS/YAGNI, abstraction, SDLC | First. Everything else assumes these. |
| 02 | [`02-design-patterns.md`](02-design-patterns.md) | Reusable solutions: creational/structural/behavioral patterns, + the backend-specific ones (Repository, DI, MVC, Middleware) | After 01. |
| 03 | [`03-architecture.md`](03-architecture.md) | How whole systems are shaped: monolith, modular monolith, microservices, serverless, layered, hexagonal, event-driven | After 02. |
| 04 | [`04-scalability.md`](04-scalability.md) | Handling load: vertical vs horizontal scaling, load balancing, caching, CDNs, statelessness, DB scaling | After 03. |
| 05 | [`05-databases-and-storage.md`](05-databases-and-storage.md) | Data: SQL vs NoSQL, ACID, CAP, indexing, transactions, ORMs and cloud storage types (block/object/file) | Anytime; core. |
| 06 | [`06-apis.md`](06-apis.md) | The interface: REST, GraphQL, gRPC, versioning, API gateways, docs (OpenAPI), Postman & tooling | After 05. |
| 07 | [`07-security.md`](07-security.md) | Not getting owned: authN/authZ, hashing, JWT/OAuth, OWASP Top 10, encryption, secrets | Core; revisit often. |
| 08 | [`08-testing.md`](08-testing.md) | Confidence: the testing pyramid - unit, integration, system, e2e - TDD, mocking, coverage | After you can build a thing. |
| 09 | [`09-cicd-devops.md`](09-cicd-devops.md) | Shipping: CI/CD pipelines, Docker, orchestration, deployment strategies, monitoring & observability | After 08. |
| 10 | [`10-tools-and-ecosystem.md`](10-tools-and-ecosystem.md) | The landscape: hosting (Railway/Render/Fly/cloud), DB hosts, CI tools, Postman, queues, Redis, monitoring | Reference; dip in anytime. |

---

## The mental model to hold onto

Backend engineering is really about managing **four tensions**:

1. **Change** - code will change; structure it so change is cheap (→ 01, 02, 03)
2. **Load** - more users will come; handle growth without rewrites (→ 04, 05)
3. **Trust** - the internet is hostile; assume attackers (→ 07)
4. **Confidence** - you must ship without fear of breaking things (→ 08, 09)

Almost every concept in here is a tool for one of those four. When something feels abstract, ask: *which tension is this solving?*

---

## Conventions used

- **💡 Why it matters** - the reasoning, never just the *what*
- **⚖️ Comparison** - side-by-side tradeoffs (usually a table)
- **⚠️ Pitfall** - the beginner mistake to dodge
- **📌 Rule of thumb** - a practical default when you're unsure

---

*Companion to the [Node + TypeScript backend roadmap](../Roadmap%20&%20Tech%20Stack.md). That's the "how"; this is the "why."*
