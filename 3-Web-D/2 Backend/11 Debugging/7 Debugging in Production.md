# Debugging in Production

Once deployed, `node --inspect`, an attached debugger, and freely restarting the process to test a theory are usually all gone. Debugging a live server is a different skill, built almost entirely around reading what already got logged, and being careful about what you change while real users are affected.

## The debugger is (usually) not an option

A production server is typically not reachable with a local debugger attached, and even where it technically could be, pausing a live process on a breakpoint freezes it for every real request currently in flight, an acceptable cost locally, not on a server handling real traffic. Production debugging leans almost entirely on logs, written before the bug happened, plus deliberately reproducing the issue in a safer environment once you have a lead.

## Read the platform's logs first

Covered briefly in the [Troubleshooting Index](../Troubleshooting%20Index.md): "health route works, every other route returns 500, read the platform logs, the actual error is there." Every deploy platform (Railway, Render, Fly.io and similar) has a logs view, usually the actual stack trace from the crash is sitting there, unread, while the same information gets guessed at instead.

```
Client sees:            Internal Server Error (generic, no detail, on purpose)
Platform logs actually show:
  TypeError: Cannot read properties of undefined (reading 'email')
      at authService.register (authService.js:22:15)
```

📌 The generic error a client receives is deliberately vague, for security, real detail belongs only in server-side logs, never sent back to the client directly. This is why checking logs first, not the client response, is always the right first move in production.

## Reproduce the same failure locally

Once the platform logs show roughly what happened, the fastest next step is usually reproducing that exact same request locally, where a full debugger is available again. Copy the request (method, headers, body) from the platform's request logs if available, or reconstruct it from what you know about what the failing client sent, then run it against a local copy of the server.

```
Production: crash, stack trace in logs, no debugger attached
      |
      v
Reproduce the same request locally
      |
      v
Local: full debugger available, breakpoints, step through, same code
```

## Environment differences that commonly explain "works locally, not in production"

| Difference | What breaks |
|---|---|
| A missing or different environment variable | A feature silently misbehaves, or the app crashes at startup |
| A production database that has different data than local | A query that assumed a value always exists finds a real null |
| A dependency installed as dev-only | Missing in a production build that does not install dev dependencies |
| `NODE_ENV` set differently | Some libraries change behavior (stricter errors, different logging) based on it |

## Fail fast on startup, catching config problems early

A missing required environment variable is easier to debug the moment the server starts than three requests later, deep inside unrelated code that happened to touch it first.

```ts
const requiredEnv = ["DATABASE_URL", "JWT_SECRET"];
for (const key of requiredEnv) {
  if (!process.env[key]) {
    throw new Error(`Missing required environment variable: ${key}`);
  }
}
```

This turns a confusing runtime failure, somewhere deep in a request, into an immediate, obvious startup crash with a clear message, exactly the config problem named in the [Env Vars and Config](../4%20Express%20Fundamentals/5%20Env%20Vars%20and%20Config.md) notes.

## Health checks as an early signal

A `/health` route that checks the database connection (not just "the process is running") often catches a problem before real users hit it, a failing health check appearing in a platform's monitoring is frequently the first sign of trouble, well before a wave of user-facing 500s.

## Being careful while debugging live

⚠️ **Pitfall**: adding a temporary, very verbose log statement directly to a production deploy to chase a bug is sometimes necessary, but remember to remove it afterward, and never log full request bodies (passwords, tokens) even temporarily, the same rule from the logging file applies with more consequence here, since it is now real user data.

## Key takeaways

- A debugger is rarely available in production, logs written ahead of time, plus reproducing the same failure locally, replace it.
- Read the platform's logs first, the actual stack trace is usually already there, the client only sees a deliberately vague generic error.
- Environment differences (missing env vars, different data, dev-only dependencies) explain most "works locally, not in production" bugs.
- Failing fast on missing configuration at startup turns a confusing mid-request bug into an obvious, immediate one.
