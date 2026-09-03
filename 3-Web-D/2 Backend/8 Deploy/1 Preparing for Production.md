# Preparing for Production

Before deploying, a few things need to change from how the app runs in development. Skipping these is where most first deployments break.

## Compile TypeScript, do not run it directly

`tsx` (used in development via `npm run dev`) recompiles your TypeScript on every run. That is fine locally, wasteful and slower in production, where the code does not change between restarts.

```json
{
  "scripts": {
    "dev": "tsx watch src/index.ts",
    "build": "tsc",
    "start": "node dist/index.js"
  }
}
```

```
Production flow:
npm run build   -> compiles src/*.ts into dist/*.js
npm start        -> runs plain Node on the compiled JS, no TypeScript involved at runtime
```

⚠️ **Pitfall**: running `tsx` in production works, technically, but recompiles TypeScript on every server start and adds unnecessary overhead, exactly the trap named in the roadmap. Always compile first, then run the compiled JavaScript.

## Confirm `tsconfig.json` points `dist` at the right place

```json
{
  "compilerOptions": {
    "outDir": "dist",
    "rootDir": "src"
  }
}
```

Running `npm run build` should produce `dist/index.js` (matching whatever `npm start` actually runs), double check this locally before deploying.

```bash
npm run build
node dist/index.js   # should start the server correctly, exactly like npm start will in production
```

## Environment variables, dev vs prod

Covered conceptually in [Env Vars and Config](../4%20Express%20Fundamentals/5%20Env%20Vars%20and%20Config.md) (Phase 1). In practice, for deployment:

| | Development | Production |
|---|---|---|
| Where variables live | `.env` file (gitignored, loaded by `dotenv`) | Set directly in Railway's dashboard |
| `DATABASE_URL` | Points at your dev/test Neon branch, if you use one | Points at your production Neon database |
| `JWT_SECRET` | Can be a simple placeholder | A real, long, random secret, different from dev |
| `PORT` | Usually `3000`, set by you | Often set automatically by the platform |

⚠️ `.env` never gets committed or uploaded anywhere, the platform's own dashboard is where production secrets are entered directly, never through a file in your repo.

### `PORT` on a hosting platform

Many platforms, including Railway, assign the port your app should listen on dynamically, through an environment variable, rather than always `3000`.

```ts
const PORT = Number(process.env.PORT) || 3000;
app.listen(PORT, () => console.log(`Running on port ${PORT}`));
```

This line already works correctly in both places: locally it falls back to `3000`, on Railway it uses whatever port the platform actually assigns.

## `.gitignore`, confirmed before pushing

```
node_modules
dist
.env
```

`dist` does not need to be committed, since the build step regenerates it on the platform during deployment. `node_modules` never gets committed, since `npm install` reinstalls dependencies fresh anywhere the code runs.

## Running migrations against production

Covered in depth in [Migrations](../5%20Postgres%20and%20Prisma/5%20Migrations.md) (Phase 2). Restated here because it matters directly for deployment:

```bash
npx prisma migrate deploy
```

⚠️ **Pitfall, worth repeating**: `migrate dev` is for local development, and can prompt or behave in ways not meant for a live database. `migrate deploy` is the correct command for production, it applies existing, already-committed migrations without generating new ones or asking questions.

## A production-ready `package.json` scripts section

```json
{
  "scripts": {
    "dev": "tsx watch src/index.ts",
    "build": "tsc",
    "start": "node dist/index.js",
    "postinstall": "prisma generate"
  }
}
```

`postinstall` runs automatically right after `npm install`, ensuring Prisma Client is regenerated on the deployment platform too, not just on your own machine. Without this, a fresh deployment's Prisma Client can be stale or missing entirely.

## A quick pre-deploy checklist

```
[ ] npm run build succeeds locally with no errors
[ ] node dist/index.js runs correctly (using a local .env for this test)
[ ] .env is in .gitignore, confirmed with: git status
[ ] All required env vars are documented (a .env.example file helps here)
[ ] package.json has build, start and postinstall scripts set correctly
```

## Key takeaways

- Production runs compiled JavaScript (`npm run build` then `npm start`), never `tsx`, which is a development-only convenience.
- Environment variables move from a local `.env` file to the hosting platform's dashboard, `.env` itself is never uploaded anywhere.
- `PORT` should be read from `process.env.PORT` with a local fallback, since hosting platforms often assign it dynamically.
- `prisma migrate deploy`, not `migrate dev`, is the correct command to run against a production database, and a `postinstall` script keeps Prisma Client correctly generated on the deployment platform.
