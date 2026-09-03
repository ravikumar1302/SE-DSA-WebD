# Deploying to Railway

This file walks through the actual deployment steps, matching Phase 5's checklist exactly.

## Step 1: push the repo to GitHub

```bash
git init                          # if not already a repo
git add .
git commit -m "Ready for deployment"
git remote add origin <your-repo-url>
git push -u origin main
```

Railway deploys directly from a GitHub repository, this is the source it builds and redeploys from on every future push.

## Step 2: create a Railway project

1. Sign in to Railway, create a new project.
2. Choose "Deploy from GitHub repo", select your repository.
3. Railway detects it is a Node project (from `package.json`) and prepares a build automatically.

```
GitHub repo  ────(Railway watches this)────>  Railway build & deploy
```

## Step 3: set environment variables

In the Railway project's settings, add every variable your app needs, matching what is in your local `.env`.

```
DATABASE_URL   = <your Neon connection string>
JWT_SECRET     = <a real, long, random production secret, different from dev>
NODE_ENV       = production
```

⚠️ Use a **different** `JWT_SECRET` in production than in development. If your dev secret ever leaked (a screenshot, a shared terminal, an old commit), production stays unaffected only if the secrets are actually different.

📌 `NODE_ENV=production` is a convention many libraries (including Express itself) check internally to enable production-optimized behavior, worth setting explicitly even if your own code does not read it directly.

## Step 4: configure the build and start commands

Railway usually detects these from `package.json` automatically (`npm run build`, `npm start`), confirm they match what you set up in [Preparing for Production](1%20Preparing%20for%20Production.md):

```
Build command: npm run build
Start command: npm start
```

## Step 5: run migrations against the production database

This is a one-time (per deployment with new migrations) manual step, distinct from the automatic build/start cycle.

```bash
npx prisma migrate deploy
```

Run this from your local machine with `DATABASE_URL` pointed at production (Railway also supports running one-off commands directly through its own CLI, `railway run npx prisma migrate deploy`, which reads the environment variables already configured in the project, avoiding the need to paste the production connection string locally at all).

⚠️ Confirm you are running this against the correct database before running it, `migrate deploy` changes real, live schema.

## Step 6: deploy and watch the logs

Once pushed and configured, Railway builds and starts your app automatically. Its dashboard shows real-time logs, exactly what your app prints with `console.log`, plus build output.

```
Build logs:  npm install -> npm run build -> success
Deploy logs: npm start -> "Server running on port 8080" (or whatever PORT Railway assigned)
```

📌 This is your primary debugging tool once deployed, there is no terminal attached the way there is locally, the platform's log viewer is where you look when something breaks.

## Step 7: hit the live URL

Railway assigns a public URL to your deployed app.

```bash
curl https://your-app.up.railway.app/health
# { "success": true, "data": { "status": "ok" } }
```

If this works, your `/health` route (built all the way back in Phase 0) is now genuinely reachable from anywhere on the internet, not just `localhost`.

## Debugging a failed deploy, a checklist

| Symptom | Likely cause |
|---|---|
| Build fails | A TypeScript error not caught locally, or a missing dependency in `package.json` |
| App starts, then immediately crashes | Missing required env var (check your `requireEnv` checks from [Env Vars and Config](../4%20Express%20Fundamentals/5%20Env%20Vars%20and%20Config.md)) |
| App runs, but every database call fails | `DATABASE_URL` not set correctly, or migrations not yet applied |
| `/health` works, but every other route 500s | Check the logs for the actual thrown error, likely a specific missing env var or a real bug only triggered by a real request |

## Redeploying after future changes

Every push to your repo's main branch (or whichever branch Railway is watching) triggers a new automatic build and deploy. Database migrations do not run automatically as part of this, run `prisma migrate deploy` yourself whenever a new migration was added since the last deploy.

## Key takeaways

- Railway builds and deploys directly from your GitHub repo, environment variables are set once in its dashboard, not committed anywhere.
- `prisma migrate deploy` against the production database is a distinct, manual step, separate from the automatic build/deploy cycle, run it whenever new migrations exist.
- Railway's log viewer is your primary debugging tool once deployed, there is no local terminal attached to a running production server.
- Hitting your `/health` endpoint on the live URL is the simplest, fastest confirmation that the whole deploy pipeline actually worked end to end.
