# 09 - CI/CD & DevOps

Writing code is half the job; **getting it to users reliably and repeatedly** is the other half. This chapter covers the automation and practices that carry code from your machine to production safely - CI/CD, containers, deployment strategies and the observability that tells you it's actually working.

💡 **The core idea - automate the path to production.** Manual deploys ("SSH in, pull code, restart, pray") are slow, error-prone and unrepeatable. Automating build → test → deploy makes shipping boring, frequent and safe. Boring deploys are *good* deploys.

---

## Part A - What "DevOps" means

**DevOps** is a culture/practice that merges **Dev**elopment and **Op**erations - the people who *write* software and the people who *run* it - so the same team owns code from commit to production and beyond.

💡 **Why:** historically, devs "threw code over the wall" to ops, who struggled to run it ("works on my machine!"). DevOps removes that wall: shared ownership, heavy automation, fast feedback. The goals are **speed** (ship often) *and* **stability** (without breaking things) - which sound opposed but automation delivers both.

---

## Part B - CI/CD explained

### CI - Continuous Integration
Developers **merge their changes into the shared main branch frequently** (ideally many times a day), and **every merge triggers an automated build + test run**.

💡 **The problem it solves:** if everyone works in isolation for weeks and merges at the end, integration is a nightmare of conflicts and surprises ("integration hell"). Integrating constantly keeps each merge small and catches conflicts/breakages *immediately*, while they're cheap to fix.

**A CI pipeline typically runs on each push:**
1. **Checkout** the code
2. **Install** dependencies
3. **Lint / format check** - style and static analysis
4. **Build / compile** - (e.g., TypeScript → JavaScript)
5. **Run tests** - unit + integration (file 08)
6. **Report** - pass = mergeable; fail = blocked

⚠️ If any step fails, the merge is blocked - broken code never reaches main. This is CI's superpower: **main branch stays always-working.**

### CD - Continuous Delivery vs Continuous Deployment
The acronym hides *two* related but distinct practices:

- **Continuous Delivery** - every change that passes CI is **automatically prepared and ready** to deploy, but a **human clicks "deploy"** to release. You're always *deployable*; releasing is a decision.
- **Continuous Deployment** - goes one step further: every change that passes all checks is **automatically deployed to production**, no human gate.

⚖️ **Delivery vs Deployment:**

| | Continuous Delivery | Continuous Deployment |
|---|---|---|
| After passing tests | Ready to deploy | Deployed automatically |
| Human approval | Yes (manual release) | No (fully automatic) |
| Control | More | Less (but faster) |
| Requires | Good tests | *Excellent* tests + monitoring |

📌 Most teams do continuous **delivery** (safety of a human gate) and graduate to continuous **deployment** once their tests and monitoring are trustworthy enough to remove the gate.

### The whole flow
```
commit → CI (build + test) → artifact → CD (deploy to staging → prod) → monitor
```

---

## Part C - Environments

Code moves through **environments** - separate copies of your app for different purposes:

- **Development (dev)** - your local machine, fast iteration
- **Staging** - a production-like environment for final testing (same config shape, test data)
- **Production (prod)** - the real thing, real users

💡 **Why staging matters:** it catches "works locally, breaks in prod" issues *before* users hit them, in an environment that mirrors production. Same code runs in all environments; only **configuration** (via env vars - file 07) differs. **Never test in production** by accident because you skipped staging.

---

## Part D - Containers & Docker

### The problem: "works on my machine"
Your app runs on your laptop but breaks on the server - different OS, library versions, configs. Environment drift is a classic source of pain.

### The solution: containers
A **container** packages your app *with everything it needs to run* - code, runtime, libraries, dependencies - into one portable, isolated unit that runs **identically anywhere**.

- **Docker** - the dominant containerization tool.
- **Image** - the blueprint/template (built from a `Dockerfile` that lists the steps to assemble it).
- **Container** - a running instance of an image.
- **Registry** - where images are stored/shared (Docker Hub, GitHub Container Registry).

⚖️ **Containers vs Virtual Machines:**

| | Container | Virtual Machine |
|---|---|---|
| Contains | App + dependencies | Full guest OS + app |
| Weight | Lightweight (MBs) | Heavy (GBs) |
| Startup | Seconds | Minutes |
| Isolation | Process-level (shares host kernel) | Full (own OS) |
| Density | Many per host | Few per host |

💡 Containers give you *most* of a VM's isolation at a fraction of the weight, because they share the host OS kernel instead of each bundling a full OS. This is why they revolutionized deployment - reproducible, portable, fast, dense.

### Orchestration (Kubernetes)
Running *one* container is easy. Running *hundreds* across many machines - scaling them, restarting crashed ones, load-balancing, rolling out updates - needs an **orchestrator**.
- **Kubernetes (K8s)** - the industry-standard container orchestrator: auto-scaling, self-healing, rolling deployments, service discovery.
- ⚠️ **Powerful but complex.** For a beginner or a small app, K8s is massive overkill - managed platforms (file 10) handle orchestration for you. Know *what* it is and *why* it exists; you likely won't run it yourself for a long time.

---

## Part E - Deployment strategies

*How* you roll out a new version matters - a naive "stop old, start new" causes downtime and risks a bad release hitting everyone at once. Safer strategies:

- **Recreate** - stop old, start new. Simple but causes **downtime**. Fine for dev, not prod.
- **Rolling deployment** - replace instances gradually, a few at a time. No downtime; old and new run together briefly.
- **Blue-Green** - run two identical environments (Blue = current, Green = new). Deploy to Green, test it, then switch all traffic to Green instantly. **Instant rollback** - just switch back to Blue if something's wrong.
- **Canary** - release the new version to a **small % of users** first; watch metrics; if healthy, gradually roll out to everyone; if not, roll back with minimal blast radius. Named after "canary in a coal mine."

⚖️ **Quick guide:**

| Strategy | Downtime | Rollback | Risk control | Complexity |
|---|---|---|---|---|
| Recreate | Yes | Slow | Low | Lowest |
| Rolling | No | Medium | Medium | Low |
| Blue-Green | No | Instant | Good | Medium (2x resources) |
| Canary | No | Fast | Best | Higher |

💡 **Feature flags** complement these: wrap new features in on/off switches so you can deploy code "dark" and enable it for specific users later, or kill it instantly without a redeploy. Decouples *deploying* from *releasing*.

📌 As a beginner on a managed platform, you get **rolling/zero-downtime** deploys mostly for free. Understand blue-green and canary as concepts you'll adopt as stakes rise.

---

## Part F - Infrastructure as Code (IaC)

Instead of manually clicking around a cloud console to set up servers/databases, you **describe your infrastructure in code/config files** and apply them automatically.

- **Tools:** Terraform (cloud-agnostic), AWS CloudFormation, Pulumi.
- ✅ **Reproducible** (recreate your whole setup from a file), **version-controlled** (infra changes reviewed like code), **consistent** (no manual drift), **documented** (the code *is* the documentation).

💡 **Why it matters:** manually-configured servers are unrepeatable snowflakes - when one dies or you need a second, you can't reliably recreate it. IaC makes infrastructure reliable and reviewable. (Advanced for a beginner, but know the concept.)

---

## Part G - Observability: Logging, Metrics, Tracing

Once your code runs on servers you can't see, **observability** is how you understand what it's doing. Three pillars:

### 1. Logging
Timestamped records of events ("user 123 logged in", "payment failed: reason"). Your primary debugging tool in production.
- 📌 Use **structured logging** (JSON with fields) so logs are searchable/filterable, not just plain strings.
- Use **log levels** (DEBUG, INFO, WARN, ERROR) to control verbosity.
- ⚠️ **Never log secrets or sensitive data** (passwords, tokens, card numbers) - logs leak.
- **Centralize** logs from all servers in one place (ELK stack, Loki, Datadog) - grepping individual machines doesn't scale.

### 2. Metrics
Numeric measurements over time: request rate, error rate, latency (p95/p99 - file 04), CPU/memory, queue depth. Visualized on **dashboards** (Prometheus + Grafana, Datadog).
- 💡 Metrics tell you *that* something's wrong and *how* the system is trending; logs tell you *what* happened in detail.

### 3. Tracing
Follows a single request as it flows through the system (especially across microservices), showing where time is spent. **Distributed tracing** (OpenTelemetry, Jaeger) is essential once one request touches many services - otherwise you can't tell *which* service is slow.

### Alerting & Monitoring
- **Monitoring** = watching metrics/logs for problems.
- **Alerting** = getting notified (Slack/PagerDuty) when something crosses a threshold (error rate spikes, server down) - *before* users complain, ideally.
- **Error tracking** - tools like **Sentry** capture exceptions with full context (stack trace, request, user) so you fix real bugs fast.
- **Health checks** - an endpoint (`/health`) that load balancers/orchestrators ping to know if an instance is alive.
- **Uptime monitoring** - external services that ping your app and alert if it's down.

💡 **The point of observability:** you *will* have incidents. The difference between a 2-minute blip and a 2-hour outage is whether you can *see* what's happening. Build visibility in before you need it.

---

## A realistic beginner pipeline

You don't need enterprise DevOps to get the benefits. A solid starter setup:
1. **Git + GitHub** - version control, pull requests
2. **GitHub Actions** - on every push: lint, build, run tests (that's CI)
3. **A managed host** (Railway/Render/Fly - file 10) - auto-deploys on merge to main (that's CD), gives you zero-downtime rolling deploys for free
4. **Sentry** - error tracking
5. **The host's built-in logs/metrics** - basic observability

📌 This gives you real CI/CD and observability with almost no ops burden - perfect while learning. Add Docker, IaC and heavier monitoring as needs grow.

---

## Key takeaways

- **DevOps** = dev + ops sharing ownership, powered by automation, for speed *and* stability.
- **CI** = merge often, auto-build-and-test every change → main always works.
- **CD** = continuous *delivery* (ready to ship, human clicks) vs *deployment* (auto to prod). Most start with delivery.
- **Containers/Docker** = "works everywhere" via portable, reproducible packages; **Kubernetes** orchestrates many (but is overkill early).
- Deploy safely with **rolling / blue-green / canary**; decouple release from deploy with **feature flags**.
- **IaC** makes infrastructure reproducible and reviewable.
- **Observability** (logs + metrics + tracing + alerting) is how you survive production. Build it in early.

---

## Where this shows up in the build

| Idea here | Where it becomes real |
|---|---|
| Environments, dev versus production config | [Env Vars and Config](../4%20Express%20Fundamentals/5%20Env%20Vars%20and%20Config.md) |
| Build and start, compiled output | [Preparing for Production](../8%20Deploy/1%20Preparing%20for%20Production.md) |
| Deploying, and reading production logs | [Deploying to Railway](../8%20Deploy/2%20Deploying%20to%20Railway.md) |
| Containers | [Docker](../9%20Advanced%20Topics/5%20Docker.md) |
| Orchestration, when a platform is not enough | [Kubernetes](../10%20Microservices%20and%20Distributed%20Systems/1%20Kubernetes.md) |

➡️ Next: [`10-tools-and-ecosystem.md`](10-tools-and-ecosystem.md) - the concrete tools and services that implement all of this.
