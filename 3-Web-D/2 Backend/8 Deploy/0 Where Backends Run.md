# Where Backends Run

A backend on your laptop, reachable only at `localhost`, is not a backend anyone else can use. Deploying means putting it somewhere reachable over the internet, running continuously. This file covers the main options at a practical level, [`03-architecture.md`](../0%20Concepts/03-architecture.md) and [`10-tools-and-ecosystem.md`](../0%20Concepts/10-tools-and-ecosystem.md) cover the same ground in more theoretical depth.

## The three broad options

```
VPS                    Container platform          Serverless
(you manage the OS)    (you manage the app)        (you manage nothing)
```

### VPS (Virtual Private Server)

A VPS (like a plain AWS EC2 instance or a DigitalOcean Droplet) gives you a full virtual machine: you install Node yourself, configure the OS, set up a process manager, manage security updates, everything.

```
You are responsible for:
OS updates -> Node install -> process management -> restarts on crash -> logs -> monitoring
```

Maximum control, maximum responsibility. Right choice when you need very specific infrastructure control, overkill for a learning project.

### Container platforms (PaaS-style, container-based)

You package your app (often with a `Dockerfile`), the platform runs it, handles restarts, scaling and networking for you. Railway, Render and Fly.io fall into this category.

```
You provide: your code + a Dockerfile (or the platform builds one for you)
Platform handles: running it, restarting on crash, giving you a public URL, logs
```

This is the middle ground: much less operational burden than a VPS, more control than serverless functions.

### Serverless (Functions-as-a-Service)

Your code runs only in response to a request, as an individual function, and the platform manages absolutely everything about the server itself. Vercel functions and AWS Lambda are the common examples.

```
Request comes in -> platform spins up your function -> runs it -> returns response -> shuts down
```

📌 Your Next.js API routes, if deployed on Vercel, are already an example of this, you have used serverless without necessarily naming it that way.

## Comparison

| | VPS | Container platform (Railway) | Serverless |
|---|---|---|---|
| Setup effort | High | Low | Very low |
| Ops responsibility | You manage everything | Platform manages most of it | Platform manages all of it |
| Good fit for | Full custom infrastructure needs | A learning project or small production app with a real, persistent server | Spiky, infrequent traffic, event-driven tasks |
| Persistent server process (e.g. a WebSocket connection staying open) | Yes | Yes | Harder, functions are short-lived by design |
| Cost model | Pay for the server, running or not | Pay for usage, often has a free tier | Pay per invocation, often near-free for low traffic |

## Why the roadmap picks Railway

Your Express app, as built across Phases 1 to 4, is a normal, persistent server process, it listens on a port and stays running. This fits a container platform naturally. Railway specifically also hosts Node apps and can provision or connect a Postgres database in the same place, matching the "hosts Node + Postgres together" convenience the roadmap calls out directly.

```
Railway project
├── your Express app (built from your GitHub repo)
└── connects to Neon (your existing Postgres, from Phase 2)
```

## Why not serverless for this project, specifically

Express apps are built around a long-running server object (`app.listen(...)`), holding things like the Prisma client connection across requests. Serverless functions restart fresh far more often, which fights against that model unless you specifically adapt for it (a real, common pattern, but genuinely extra complexity not needed for AlgoRift right now). The roadmap deliberately keeps this simple: one platform, one running server, matching everything you already built.

## Key takeaways

- A VPS gives full control at the cost of managing the OS yourself, a container platform (Railway) manages the OS for you and runs your app as a persistent process, serverless runs your code only per-request with the platform managing everything.
- Your Express app is a normal, persistent server, which fits a container platform far more naturally than a serverless function model.
- Railway is chosen specifically because it hosts a persistent Node process and connects cleanly to your existing Neon database, minimal extra setup beyond what you already built.
