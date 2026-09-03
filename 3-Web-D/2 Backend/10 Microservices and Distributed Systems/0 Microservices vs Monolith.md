# Microservices vs Monolith

📌 Lighter reference notes, matching Phase 7's "know it exists, don't pre-learn" philosophy. [`03-architecture.md`](../0%20Concepts/03-architecture.md) covers this theory in more depth, this file is the practical, AlgoRift-specific version.

## What AlgoRift already is

Every phase you have built so far produces one thing: a single Express application, talking to one Postgres database, deployed as one process on Railway.

```
┌─────────────────────────────┐
│      AlgoRift (monolith)     │
│  ┌─────────┐  ┌───────────┐ │
│  │  Auth    │  │  Problems  │ │
│  ├─────────┤  ├───────────┤ │
│  │Submissions│ │ Leaderboard│ │
│  └─────────┘  └───────────┘ │
│       all in one codebase,   │
│       one deploy, one DB     │
└─────────────────────────────┘
```

This is a **monolith**: one deployable unit containing every feature. It is not a beginner mistake or a stepping stone to something "more real", it is the correct architecture for a project at this scale, and for most projects, full stop.

## What microservices actually means

Splitting that one application into several independent services, each with its own codebase, its own deployment and often its own database, communicating over the network instead of through normal function calls.

```
┌──────────┐   ┌──────────┐   ┌────────────┐   ┌─────────────┐
│   Auth    │   │ Problems  │   │ Submissions│   │ Leaderboard │
│ service   │   │ service   │   │ service    │   │ service     │
│ own DB    │   │ own DB    │   │ own DB     │   │ own DB      │
└──────────┘   └──────────┘   └────────────┘   └─────────────┘
      \              |               |                /
       \             |               |               /
        \____________|_______network calls__________/
```

A request that used to be one function call inside one process (`submissionService.create()` calling `problemService.getById()` directly) now becomes an actual network request between two separately running services.

## Why this trades one set of problems for another

| | Monolith | Microservices |
|---|---|---|
| Deploying one change | One deploy | Must know which service owns the change, deploy that one |
| Calling another feature's logic | A normal function call | A network request, can fail, can be slow, needs its own error handling |
| Data consistency across features | One database, one transaction can span features | Each service's own database, cross-service consistency becomes genuinely hard |
| Debugging one request | One process, one log stream, one stack trace | The request may touch several services, tracing it across all of them needs extra tooling |
| Team scaling | Fine for one person or a small team | Shines when many teams need to work and deploy independently, without stepping on each other |
| Operational complexity | Low, one thing to run and monitor | High, many things to run, deploy, monitor and keep talking to each other correctly |

⚠️ **The trap named directly in the roadmap**: reaching for microservices before a single service is even under real load. Nearly every real "we moved to microservices too early" story starts with a team solving an organizational problem (many teams stepping on each other) or a scale problem they did not actually have yet, and paying the full operational cost upfront regardless.

## When it actually makes sense

- Multiple, genuinely separate teams need to deploy independently, without coordinating releases.
- One specific part of the system has wildly different scaling needs than the rest (a video encoding service handling occasional huge spikes, next to a simple CRUD API with steady, low traffic).
- A part of the system needs a genuinely different technology (a machine learning service in Python, next to your Node API), and splitting it out is cleaner than forcing everything into one stack.

None of these describe AlgoRift as built. One developer, one team, one deploy, no wildly different scaling needs between "create a problem" and "submit code."

## The middle ground: modular monolith

Covered in [`03-architecture.md`](../0%20Concepts/03-architecture.md), worth restating here directly: you can get most of microservices' *organizational* benefit (clear boundaries between `auth`, `problems`, `submissions`) while staying one deployable unit, one database, one simple deploy. Your existing routes/controllers/services folder structure, split by feature, already is this, informally.

```
src/
├── auth/        (routes, controller, service, all auth-related)
├── problems/
├── submissions/
└── leaderboard/
```

📌 If you ever feel real pain from AlgoRift's structure at its current scale, reorganizing into this modular-monolith shape almost always solves it, long before an actual microservices split would be justified.

## Key takeaways

- AlgoRift, as built through your whole roadmap, is a monolith, correctly, not a limitation to grow out of by default.
- Microservices trade simple function calls and one shared database for independent deployability, at the real cost of network calls, cross-service consistency and much higher operational complexity.
- The justification for microservices is almost always organizational (independent teams) or a specific, uneven scaling need, not "this is what real companies do."
- A modular monolith (feature-based folders, still one deploy) captures most of the organizational clarity without paying the distributed-systems cost, worth reaching for first.
