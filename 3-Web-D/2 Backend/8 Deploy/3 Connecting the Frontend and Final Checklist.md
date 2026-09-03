# Connecting the Frontend and Final Checklist

The last step of Phase 5, and of the whole roadmap up to this point: wiring your live, deployed API to an actual Next.js frontend.

## Update CORS for the real frontend URL

[CORS](../6%20Auth%20Validation%20and%20Security/6%20CORS.md) (Phase 3) set `origin` to `http://localhost:3001` for local development. Production needs the real, deployed frontend URL added too.

```ts
const allowedOrigins = [
  "http://localhost:3001",           // local dev
  "https://algorift.vercel.app",     // deployed Next.js frontend
];

app.use(cors({
  origin: (origin, callback) => {
    if (!origin || allowedOrigins.includes(origin)) callback(null, true);
    else callback(new Error("Not allowed by CORS"));
  },
  credentials: true,
}));
```

⚠️ **Pitfall**: forgetting to add the production frontend's real URL here means every request from your deployed frontend gets silently blocked by the browser, even though the API itself works fine when tested directly with `curl`. This is exactly why "it works in Postman/curl" does not guarantee "it works from the real frontend", covered in the CORS file.

## Pointing the Next.js frontend at the deployed API

On the frontend side, the API's base URL should itself be an environment variable, not hardcoded, the same discipline covered in [Env Vars and Config](../4%20Express%20Fundamentals/5%20Env%20Vars%20and%20Config.md) applies to frontend projects too.

```
# Next.js .env.local (development)
NEXT_PUBLIC_API_URL=http://localhost:3000

# Vercel environment variables (production)
NEXT_PUBLIC_API_URL=https://your-app.up.railway.app
```

```ts
// a fetch call in the Next.js app
const res = await fetch(`${process.env.NEXT_PUBLIC_API_URL}/problems`);
const { data } = await res.json();
```

The `NEXT_PUBLIC_` prefix is a Next.js convention, it makes the variable available in browser-side code, not just on the server, needed here since this `fetch` call runs in the user's browser.

## The full request path, end to end

```
Browser (Next.js frontend, deployed on Vercel)
      |
      |  fetch(`${NEXT_PUBLIC_API_URL}/problems`)
      v
Railway (your Express API)
      |
      |  Prisma query
      v
Neon (Postgres database)
```

Every piece of this path was built across the whole roadmap: the frontend calls, CORS allows it through, Express routes and controllers handle it, Prisma queries the real database, the response comes back in the consistent envelope shape from Phase 4.

## Testing the whole loop manually

1. Open the deployed frontend in a browser.
2. Trigger an action that calls the API (viewing the problems list, logging in).
3. Open the browser's network tab, confirm the request goes to the Railway URL, returns a `200`, and the response matches the expected `{ success, data }` shape.
4. Try logging in, confirm a JWT comes back and a subsequent authenticated request (creating a submission) works correctly.

## A full pre-launch checklist

```
[ ] Backend deployed on Railway, /health reachable at the public URL
[ ] All required env vars set correctly in Railway's dashboard
[ ] prisma migrate deploy run against the production database
[ ] CORS allowedOrigins includes the real, deployed frontend URL
[ ] Frontend's API base URL points at the Railway URL in production
[ ] Register, login and at least one protected action (create a submission) tested end to end, live
[ ] Railway logs checked, no unexpected errors on startup or on the tested requests
```

## What you have built, by the end of this phase

Every earlier phase's folder in this repo, TypeScript fundamentals, Express and HTTP, Postgres and Prisma, auth and security, API polish, comes together here as one real, live, working system, callable from a real deployed frontend, matching the roadmap's own words exactly: **"You now own the entire stack, frontend to database, no AI crutch."**

## What comes next

Phase 6 of the roadmap is "know they exist": Redis caching (the leaderboard is the named first candidate), background jobs, file uploads, WebSockets, testing and Docker, added only when a real, specific need for each comes up, not pre-learned speculatively. When you are ready to actually reach for one of those, say which, and notes for that folder start then.

## Key takeaways

- Production CORS needs the real, deployed frontend URL added to the allowlist, not just the local development one.
- The frontend's API base URL should be an environment variable (`NEXT_PUBLIC_API_URL`), switched between local and deployed values the same way the backend's own env vars work.
- Testing the full loop live (register, login, a protected action) in a real browser is the only way to confirm CORS, env vars and deployment are all actually correct together.
- Reaching this point completes the roadmap's core spine, everything after is added deliberately, only when a real project need calls for it.
