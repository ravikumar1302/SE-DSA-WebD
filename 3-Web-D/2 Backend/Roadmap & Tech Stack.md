# Backend Learning Roadmap - Node + TypeScript (Option A)

> One spine project (**AlgoRift** backend) that grows feature-by-feature. Each phase adds concepts + builds real stuff. Concept first in the simple version, *then* the real tool - so tools never hide the concept.

---

## Locked Stack - don't shop around while learning

| Layer | Pick | Why |
|---|---|---|
| Runtime | **Node + TypeScript** | TS from day 1. Your React already primed you for types. |
| Framework | **Express** (now) → **Hono** (later) | Express = most material/jobs. Hono later uses Web-standard `Request`/`Response` - literally how Next route handlers work, closes your Next.js gap. |
| Database | **PostgreSQL** | SQLite knowledge transfers; Postgres is the prod jump. |
| DB host | **Neon** | Serverless Postgres, generous free tier, zero setup. |
| ORM | **Prisma** | Type-safe, great DX, teaches schema thinking. |
| Validation | **Zod** | Validates input *and* infers TS types. |
| Auth | Hand-roll once → library | bcrypt + JWT manually once to understand, then never again. |
| Deploy | **Railway** | Push-to-deploy, hosts Node + Postgres together. |

---

## The Spine Project - AlgoRift backend

Not a throwaway TODO app. AlgoRift naturally needs every core primitive:

- **users** → auth
- **problems, tags** → CRUD + many-to-many relations
- **submissions** → 1-to-many, writes, validation
- **leaderboard** → aggregation queries, indexes, caching

You build the thing you actually want, and it *happens* to teach the whole syllabus.

---

## Phase Overview (the whole plan at a glance)

| Phase | Focus | Maps to | Time | You'll have built |
|---|---|---|---|---|
| **0** | Setup & TS refresh | - | ~2 days | A `GET /health` endpoint that returns JSON |
| **1** | HTTP + Express fundamentals | Parts 1+2 | ~1 wk | Full CRUD for `problems` (in-memory) |
| **2** | Postgres + Prisma | Part 3 | ~1.5 wk | `problems` + `tags` + `submissions` in a real DB |
| **3** | Auth + validation + security | Parts 4+5 | ~1.5 wk | Register/login, protected routes, ownership |
| **4** | API polish | Part 5 | ~1 wk | Paginated, sorted `GET /leaderboard` |
| **5** | Deploy | Part 7 | ~3 days | Live public API wired to a Next.js frontend |
| **6** | "Know they exist" | Part 6 | on demand | Redis/jobs/uploads/WebSockets - added only when needed |

**Total to shippable (Phases 0-5): ~6-7 weeks** at a steady student pace. Phase 6 + testing + Docker = depth you bolt on later, on demand.

**The one rule:** simple/fake version first, real tool second. In-memory CRUD before Prisma. Manual JWT before a library. That's exactly how you avoid the "hands-on but not first-principles" trap you flagged in your own Next.js notes.

---
---

# Detailed Breakdown

---

## Phase 0 - Setup & TS Refresh
**~2 days · Goal: prove the pipeline works end-to-end**

### Concepts
- Node project init, `package.json`, scripts
- TypeScript config (`tsconfig.json`) - `strict: true` from the start
- `tsx` (or `ts-node`) for running TS directly in dev
- TS essentials for backend: types vs interfaces, generics *basics*, typing `async/await`

### Do-this checklist
- `npm init -y`
- Install: `typescript tsx @types/node` (dev deps)
- `npx tsc --init` → set `strict: true`, `moduleResolution`, `outDir`
- Add script: `"dev": "tsx watch src/index.ts"`
- Write `src/index.ts` with a bare Node HTTP server (no Express yet) returning `{ status: "ok" }` on `/health`
- Confirm it runs + auto-reloads on save

### Traps
- Don't skip `strict` - loose TS teaches bad habits.
- Don't reach for Express yet. See the raw request/response *once* so you appreciate what Express abstracts.

### Done when
You hit `localhost:3000/health` in the browser and get JSON back.

---

## Phase 1 - HTTP + Express Fundamentals
**~1 week · Maps to Parts 1+2 · Goal: own the request → response loop**

### Concepts
- **HTTP anatomy:** method, path, headers, body
- **Methods:** GET / POST / PUT / PATCH / DELETE - and when each
- **Status codes** used *correctly*: 200/201/204, 400/401/403/404, 500
- **Where data lives in a request:** route params vs query params vs body vs headers
- **Express core:** app, routing, `req`/`res`
- **Middleware pipeline:** the `(req, res, next)` chain - logging, JSON parsing, custom middleware
- **Centralized error handling** (error middleware, don't `try/catch` everywhere)
- **Env vars:** `.env` + `dotenv`, never hardcode config
- **Folder structure:** `routes → controllers → services`

### Do-this checklist
- Install `express` + `@types/express`, `dotenv`
- `app.use(express.json())` - understand *why* (parses body)
- Write a logging middleware (method + path + timestamp)
- Build CRUD for `problems` against an **in-memory array** (no DB):
  - `POST /problems` → create (201)
  - `GET /problems` → list (200)
  - `GET /problems/:id` → one, or 404
  - `PUT /problems/:id` → update, or 404
  - `DELETE /problems/:id` → 204, or 404
- Split into `routes/` (URL→handler), `controllers/` (req/res logic), `services/` (business logic on the array)
- Add a central error handler as the *last* middleware
- Move port + config into `.env`

### Traps
- Returning 200 for everything. Use the right code - this is API hygiene.
- Fat controllers. Keep controllers thin; logic goes in services.
- Forgetting `next(err)` - errors won't reach your handler otherwise.

### Next.js hook
This *is* what an `app/api/.../route.ts` handler does. After this phase you'll never fear route handlers again.

### Done when
All 5 CRUD routes work via a REST client (Thunder Client / Postman / `curl`), each returning correct status codes, cleanly split across routes/controllers/services.

---

## Phase 2 - Postgres + Prisma
**~1.5 weeks · Maps to Part 3 · Goal: swap the fake array for a real database - biggest chunk**

### Concepts
- **SQL vs NoSQL** - when each (you're going SQL/relational)
- **Relational modeling:** primary keys, foreign keys, relations - 1:1, 1:many, many:many
- **Neon setup:** spin up serverless Postgres, get connection string
- **Prisma:** `schema.prisma`, `prisma generate`, `prisma migrate`
- **Prisma CRUD:** `create`, `findMany`, `findUnique`, `update`, `delete`
- **Relations in queries:** `include`, nested writes
- **Filtering:** `where`, operators
- **Migrations:** versioning your schema over time
- **Indexes:** why queries slow down, when to add one
- **Raw SQL escape hatch:** `$queryRaw` for when the ORM isn't enough

### Data model to build
```
Problem      id, title, description, difficulty, createdAt
Tag          id, name (unique)
Submission   id, code, status, createdAt, problemId (FK)
ProblemTag   (join table) → Problem many:many Tag
```
- `Problem` 1:many `Submission`
- `Problem` many:many `Tag`

### Do-this checklist
- Create a Neon project, copy the connection string into `.env` as `DATABASE_URL`
- Install `prisma` (dev) + `@prisma/client`
- `npx prisma init`
- Model `Problem` in `schema.prisma`, run first migration: `npx prisma migrate dev --name init`
- Rewrite the `problems` service to use Prisma instead of the array
- Add `Tag` + the many:many relation → migrate
- Add `Submission` + the 1:many relation → migrate
- Write a query that returns a problem *with* its tags and submissions (`include`)
- Add an index on something you'll filter/sort by, note the reason
- Explore data visually with `npx prisma studio`

### Traps
- Over-normalizing. Model for your actual queries, not theoretical purity.
- Editing the DB by hand instead of via migrations - migrations *are* your schema history.
- Forgetting to re-run `prisma generate` after schema changes (migrate does it, manual edits don't).

### Done when
All `problems` CRUD now persists to Neon, `tags` and `submissions` exist with correct relations and you can fetch a problem with its related data in one query.

---

## Phase 3 - Auth + Validation + Security
**~1.5 weeks · Maps to Parts 4 + part of 5 · Goal: the part tutorials fudge and real apps break**

### Concepts
- **Validation as boundary + security:** Zod on every input
- **Password hashing:** bcrypt/argon2 - never plaintext, understand salting
- **AuthN vs AuthZ:** who you are vs what you're allowed to do
- **JWT:** issue on login, verify on protected routes, what's *in* a token, expiry
- **Route protection:** auth middleware that attaches the user to `req`
- **Ownership:** a user can only edit/delete *their own* submissions
- **Starter threat list:** SQL injection (Prisma mostly handles), XSS awareness, rate limiting, secrets hygiene, **CORS done properly**

### Do-this checklist
- Install `zod`, `bcrypt`, `jsonwebtoken` (+ `@types/*`)
- Add a `User` model (email unique, hashed password) → migrate
- Zod schemas for every request body; validate in a middleware or at controller entry
- `POST /auth/register` → hash password, store user
- `POST /auth/login` → verify password, return a JWT
- Auth middleware → verify JWT, attach `req.user`, else 401
- Protect submission creation - must be logged in
- Tie `Submission` to `userId` (FK) → migrate
- Ownership check: editing someone else's submission → 403
- Add `JWT_SECRET` to `.env`; add basic rate limiting on auth routes
- Configure CORS explicitly (origins, methods, credentials)

### Traps
- Storing passwords reversibly or logging them. Hash only, ever.
- Putting secrets in the JWT payload - it's *signed, not encrypted*; anyone can read it.
- 401 vs 403 confusion: 401 = not authenticated, 403 = authenticated but not allowed.
- Skipping validation because "the frontend already validates" - never trust the client.

### Done when
A user can register, log in, get a token, create submissions tied to their account and is blocked (403) from touching others' data. Protected routes reject missing/invalid tokens (401).

---

## Phase 4 - API Polish
**~1 week · Maps to Part 5 · Goal: CRUD works; make it *good***

### Concepts
- **Consistent response shape** across the whole API (success + error envelope)
- **Consistent error format** (code, message, details)
- **Pagination** (limit/offset or cursor), **filtering**, **sorting**
- **Aggregation** for the leaderboard (count/rank submissions per user)

### Do-this checklist
- Define one response shape, e.g. `{ data, error }` - apply everywhere
- Define one error shape; make the central error handler emit it
- Add pagination to `GET /problems` and `GET /submissions` (`?page=&limit=`)
- Add filtering (e.g. problems by difficulty/tag) and sorting (`?sort=`)
- Build `GET /leaderboard` - aggregate submissions per user, rank, paginate, sort
- Return total counts / next-page info with paginated responses

### Traps
- Inconsistent shapes (some routes return arrays, some objects, some raw errors) - frontend hell.
- Unbounded list endpoints - always cap `limit`.
- Doing aggregation in JS after fetching everything. Push it into the DB query.

### Done when
Every endpoint returns a consistent shape, lists are paginated/filterable/sortable and `/leaderboard` computes rankings in the database.

---

## Phase 5 - Deploy
**~3 days · Maps to Part 7 · Goal: a backend on localhost isn't a backend**
> Do a *taste* of this earlier (deploy the `/health` endpoint after Phase 1) so prod isn't scary at the end.

### Concepts
- **Where backends run:** serverless vs container vs VPS (you'll use a managed platform)
- **Deploy target:** Railway (hosts Node + connects Neon)
- **Env management:** dev vs prod config, prod secrets
- **Prod logs + remote debugging**

### Do-this checklist
- Push repo to GitHub
- Create a Railway project from the repo
- Set prod env vars (`DATABASE_URL` → Neon, `JWT_SECRET`, etc.)
- Ensure a proper `build` + `start` script for prod (compile TS → run JS)
- Run migrations against prod DB (`prisma migrate deploy`)
- Hit the live URL, read prod logs, fix a real deploy bug
- Wire the live API to a small **Next.js** frontend (fetch problems, log in, submit)

### Traps
- Committing `.env` - never. Set secrets in the platform dashboard.
- Using `migrate dev` in prod - use `migrate deploy`.
- Running `tsx` in prod - compile to JS and run node, or use the right start command.

### Done when
Your API is live on a public URL, migrations applied and a Next.js frontend talks to it. **You now own the entire stack, frontend → DB, no AI crutch.**

---

## Phase 6 - "Know They Exist"
**On demand · Maps to Part 6 · Goal: recognize when to reach, don't pre-learn**

Add each *only* when the project genuinely demands it:

- **Redis caching** - leaderboard is the perfect first excuse (expensive query, cache it)
- **Background jobs / queues** - email, heavy async tasks
- **File uploads / object storage** (S3-style) - avatars, attachments
- **WebSockets / realtime** - live submission status updates
- **Testing** (unit + integration) - bolt on once the app is stable
- **Docker** - reproducible environments, powerful but later

### Deliberately skipped for now
Microservices, Kubernetes, GraphQL implementation, message brokers (Kafka), gRPC. All noise until you've shipped a real CRUD-plus-auth backend. Which, after Phase 5, you will have.

---

## Progress Tracker

- Phase 0 - Setup & TS refresh
- Phase 1 - HTTP + Express fundamentals
- Phase 2 - Postgres + Prisma
- Phase 3 - Auth + validation + security
- Phase 4 - API polish
- Phase 5 - Deploy
- Phase 6 - On-demand extras
