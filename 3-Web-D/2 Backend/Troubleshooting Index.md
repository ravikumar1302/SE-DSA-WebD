# Troubleshooting Index

Organized by **symptom**, not by topic, so it works when something is broken and the cause is not obvious yet. Find the symptom, read the cause, open the linked file if the one-line fix is not enough.

## TypeScript and setup

| Symptom | Likely cause | Fix | More |
|---|---|---|---|
| `Cannot find module 'express'` or no autocomplete for it | Type definitions not installed | `npm install -D @types/express` | [Project Setup](3%20TypeScript/1%20Project%20Setup.md) |
| Everything compiles but bugs slip through at runtime | `strict` is off in `tsconfig.json` | Set `"strict": true` and fix what it reports | [Project Setup](3%20TypeScript/1%20Project%20Setup.md) |
| `'error' is of type 'unknown'` inside a catch block | Correct behavior under strict mode | Narrow it: `if (error instanceof Error)` | [Async Code](3%20TypeScript/7%20Async%20Code.md) |
| A value is typed `any` and nothing is checked | An untyped parameter, or an explicit `any` | Type it properly, or use `unknown` and narrow | [Common Mistakes](3%20TypeScript/9%20Common%20Mistakes.md) |
| Type looks correct but the real data is wrong at runtime | Types are compile-time only, they cannot validate incoming data | Validate at the boundary with Zod | [Validation with Zod](6%20Auth%20Validation%20and%20Security/0%20Validation%20with%20Zod.md) |

## Express and routing

| Symptom | Likely cause | Fix | More |
|---|---|---|---|
| `req.body` is `undefined` | `express.json()` missing or registered after the route | Add `app.use(express.json())` before routes | [Express Basics](4%20Express%20Fundamentals/1%20Express%20Basics.md) |
| Request hangs, no response ever arrives | Middleware neither called `next()` nor ended the response | Call `next()`, or send a response, never neither | [Middleware](4%20Express%20Fundamentals/3%20Middleware.md) |
| `Cannot set headers after they are sent` | A response was sent twice, usually a missing `return` after `res.json()` | `return` immediately after sending | [Middleware](4%20Express%20Fundamentals/3%20Middleware.md) |
| A protected route is reachable without a token | Auth middleware registered after the route it should protect | Move it before, order decides everything | [Auth Middleware](6%20Auth%20Validation%20and%20Security/4%20Auth%20Middleware%20and%20Route%20Protection.md) |
| `req.headers.Authorization` is always undefined | Express lowercases header names | Use `req.headers.authorization` | [Where Data Lives in a Request](4%20Express%20Fundamentals/2%20Where%20Data%20Lives%20in%20a%20Request.md) |
| Comparing an id fails even though the ids look equal | `req.params.id` is a string, not a number | `Number(req.params.id)`, and check for `NaN` | [Where Data Lives in a Request](4%20Express%20Fundamentals/2%20Where%20Data%20Lives%20in%20a%20Request.md) |
| A thrown error crashes the process instead of returning 500 | Async handler error never reached the error middleware | Wrap with `asyncHandler`, or use Express 5 | [Centralized Error Handling](4%20Express%20Fundamentals/4%20Centralized%20Error%20Handling.md) |
| Error handler never runs | It is registered before the routes, or has three parameters instead of four | Register it last, signature `(err, req, res, next)` | [Centralized Error Handling](4%20Express%20Fundamentals/4%20Centralized%20Error%20Handling.md) |
| Server accepts requests but is slow for everyone at once | A blocking, synchronous call in a request path | Use the async version, never `readFileSync` in a handler | [Node.js Runtime and the Event Loop](4%20Express%20Fundamentals/8%20Node.js%20Runtime%20and%20the%20Event%20Loop.md) |

## Prisma and the database

| Symptom | Likely cause | Fix | More |
|---|---|---|---|
| TypeScript says a field does not exist, but it is in `schema.prisma` | Prisma Client not regenerated after the schema changed | `npx prisma generate` | [Migrations](5%20Postgres%20and%20Prisma/5%20Migrations.md) |
| `res.json()` returns `{}` instead of real data | A missing `await`, so a Promise was sent instead of the result | Add `await`, mark the function `async` | [Prisma CRUD](5%20Postgres%20and%20Prisma/2%20Prisma%20CRUD.md) |
| `update` or `delete` throws instead of returning null | That is their behavior on no match, unlike `findUnique` | Check existence first, or catch the error | [Prisma CRUD](5%20Postgres%20and%20Prisma/2%20Prisma%20CRUD.md) |
| Related data (tags, submissions) is missing from the response | Relations are not fetched unless asked for | Add `include: { tags: true }` | [Relations in Prisma](5%20Postgres%20and%20Prisma/3%20Relations%20in%20Prisma.md) |
| One page load fires hundreds of queries | Fetching relations in a loop, the N+1 problem | Fetch once with `include` | [Relations in Prisma](5%20Postgres%20and%20Prisma/3%20Relations%20in%20Prisma.md) |
| Queries get slower as the table grows | Filtering or sorting on a column with no index | Add `@@index([field])` for that column | [Indexes and Query Performance](5%20Postgres%20and%20Prisma/6%20Indexes%20and%20Query%20Performance.md) |
| Database and `schema.prisma` disagree | The database was edited by hand instead of through a migration | Bring changes back into the schema, migrate forward | [Migrations](5%20Postgres%20and%20Prisma/5%20Migrations.md) |
| A list endpoint returns thousands of rows | No `take` limit on the query | Always cap `limit`, with a maximum | [Filtering Sorting and Pagination](5%20Postgres%20and%20Prisma/4%20Filtering%20Sorting%20and%20Pagination.md) |

## Auth and security

| Symptom | Likely cause | Fix | More |
|---|---|---|---|
| Every protected request returns 401 with a valid-looking token | Wrong `JWT_SECRET`, or the token expired | Confirm the secret matches the one used to sign, check expiry | [JWT in Practice](6%20Auth%20Validation%20and%20Security/3%20JWT%20in%20Practice.md) |
| Login always fails even with the right password | Comparing a plain password to a hash directly | Use `bcrypt.compare`, never `===` | [Password Hashing](6%20Auth%20Validation%20and%20Security/1%20Password%20Hashing.md) |
| `req.userId` is undefined inside a handler | The route did not run the auth middleware first | Add `requireAuth` before the handler | [Auth Middleware](6%20Auth%20Validation%20and%20Security/4%20Auth%20Middleware%20and%20Route%20Protection.md) |
| TypeScript rejects `req.userId = ...` | Express's `Request` type has no such field yet | Add it via declaration merging in a `.d.ts` file | [Auth Middleware](6%20Auth%20Validation%20and%20Security/4%20Auth%20Middleware%20and%20Route%20Protection.md) |
| A user can edit another user's data | Authentication passed, but no ownership check ran | Compare the record's `userId` to `req.userId`, return 403 | [Ownership and Authorization Checks](6%20Auth%20Validation%20and%20Security/5%20Ownership%20and%20Authorization%20Checks.md) |
| Works in Postman or curl, fails from the browser | CORS, the browser blocked the response | Add the frontend origin to the allowlist | [CORS](6%20Auth%20Validation%20and%20Security/6%20CORS.md) |
| Browser console shows a CORS error only on POST | The preflight `OPTIONS` request is being rejected | Let the `cors` middleware handle preflight, register it before routes | [CORS](6%20Auth%20Validation%20and%20Security/6%20CORS.md) |
| Login route is being hammered by repeated attempts | No rate limiting on auth routes | Add `express-rate-limit` to `/auth` | [Rate Limiting and Security Basics](6%20Auth%20Validation%20and%20Security/7%20Rate%20Limiting%20and%20Security%20Basics.md) |

## Deployment

| Symptom | Likely cause | Fix | More |
|---|---|---|---|
| Build fails on the platform but works locally | A type error, or a dependency listed only as a dev dependency | Run `npm run build` locally first, check dependency placement | [Preparing for Production](8%20Deploy/1%20Preparing%20for%20Production.md) |
| App builds, then crashes immediately on start | A required environment variable is missing | Set it in the platform dashboard, fail fast at startup to see it clearly | [Env Vars and Config](4%20Express%20Fundamentals/5%20Env%20Vars%20and%20Config.md) |
| App runs but every database call fails | `DATABASE_URL` wrong, or migrations never applied to production | Check the variable, run `npx prisma migrate deploy` | [Deploying to Railway](8%20Deploy/2%20Deploying%20to%20Railway.md) |
| Health route works, every other route returns 500 | A runtime error only real requests trigger | Read the platform logs, the actual error is there | [Deploying to Railway](8%20Deploy/2%20Deploying%20to%20Railway.md) |
| Port binding error on the platform | Hardcoded port instead of the one the platform assigns | `Number(process.env.PORT) || 3000` | [Preparing for Production](8%20Deploy/1%20Preparing%20for%20Production.md) |
| Deployed frontend cannot reach the deployed API | Production frontend URL missing from the CORS allowlist | Add it, redeploy | [Connecting the Frontend](8%20Deploy/3%20Connecting%20the%20Frontend%20and%20Final%20Checklist.md) |
| Secrets accidentally committed | `.env` was not gitignored before the first commit | Rotate every leaked secret, then gitignore properly | [Env Vars and Config](4%20Express%20Fundamentals/5%20Env%20Vars%20and%20Config.md) |

## When nothing here matches

Work through it in this order:

1. Read the actual error message fully, including the stack trace, not just the first line.
2. Confirm where the failure happens: the request never arrives, arrives and fails or succeeds with wrong data.
3. Log the value you believe is correct at that point, it is often the assumption that is wrong, not the code.
4. Check the boundary closest to the failure: request body, environment variable, database row, response shape.
