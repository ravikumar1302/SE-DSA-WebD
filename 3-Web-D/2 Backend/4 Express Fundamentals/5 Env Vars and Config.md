# Environment Variables and Config

## The problem

Hardcoding values like ports, database URLs and secret keys directly into your code causes real issues:

```ts
const DATABASE_URL = "postgres://user:password123@localhost:5432/mydb"; // hardcoded, bad
app.listen(3000); // hardcoded port, bad
```

- The same code cannot run against different databases (local, staging, production) without editing the file each time.
- Secrets (passwords, API keys, JWT signing keys) end up committed to git, visible to anyone with repo access, forever, even if deleted later since git history keeps it.

## Environment variables

An environment variable is a value set outside your code, in the operating system or hosting platform, that your program reads at runtime.

```ts
console.log(process.env.PORT);        // reads the PORT variable, or undefined if not set
console.log(process.env.DATABASE_URL);
```

`process.env` is a Node global object holding every environment variable currently set for the running process.

## `.env` files and `dotenv`

Setting environment variables manually every time you run your app is inconvenient during development. The `dotenv` package reads a `.env` file and loads its contents into `process.env` automatically.

```bash
npm install dotenv
```

`.env` file:

```
PORT=3000
DATABASE_URL=postgres://user:password123@localhost:5432/mydb
JWT_SECRET=some-long-random-string
```

Loading it at the very top of your entry file:

```ts
import "dotenv/config";

const PORT = process.env.PORT || 3000;
```

## `.env` must never be committed

```
# .gitignore
.env
node_modules
dist
```

⚠️ **Pitfall**: committing `.env` to git puts every secret inside it into your repository's history permanently, including on any public GitHub repo. Bots actively scan public repositories for leaked keys within seconds of a push. Always add `.env` to `.gitignore` before the first commit, not after.

Instead, commit a `.env.example` file with the same variable names but placeholder values, so anyone cloning the project knows what to set up.

```
# .env.example
PORT=3000
DATABASE_URL=your-database-connection-string
JWT_SECRET=your-secret-here
```

## Typing environment variables

By default, `process.env.SOMETHING` is typed as `string | undefined`, since TypeScript cannot know at compile time whether a given variable will actually be set at runtime.

```ts
const PORT = process.env.PORT; // string | undefined
app.listen(PORT); // may error, depending on what app.listen expects
```

A common pattern: validate and convert at startup, once, so the rest of the app can trust the values.

```ts
const PORT = Number(process.env.PORT) || 3000;

const JWT_SECRET = process.env.JWT_SECRET;
if (!JWT_SECRET) {
  throw new Error("Missing required environment variable: JWT_SECRET");
}
// after this check, JWT_SECRET is narrowed to string, not string | undefined
```

📌 Failing fast at startup (throwing immediately if a required variable is missing) is much better than discovering it is missing halfway through handling a live request.

## Dev vs prod config

| | Development | Production |
|---|---|---|
| Where variables live | `.env` file, loaded by `dotenv` | Set directly in the hosting platform's dashboard (Railway, in the roadmap) |
| Committed to git | No, `.env` is gitignored | N/A, set outside the codebase entirely |
| Database | Often a local or free-tier dev database | The real production database (Neon, in the roadmap) |
| Secrets | Can be less sensitive placeholder values | Real secrets, rotated periodically |

This matches Phase 5 of the roadmap directly: locally you use a `.env` file, on Railway you set the same variable names in the platform's environment settings, and your code does not need to change at all between the two, since it only ever reads `process.env`.

## A small config module (optional, but a good habit)

Instead of reading `process.env` scattered across many files, centralize it in one place.

```ts
// src/config.ts
import "dotenv/config";

function requireEnv(name: string): string {
  const value = process.env[name];
  if (!value) {
    throw new Error(`Missing required environment variable: ${name}`);
  }
  return value;
}

export const config = {
  port: Number(process.env.PORT) || 3000,
  databaseUrl: requireEnv("DATABASE_URL"),
  jwtSecret: requireEnv("JWT_SECRET"),
};
```

```ts
import { config } from "./config";

app.listen(config.port);
```

Every required variable is validated once, at startup, in one file. Every other file imports `config` and gets fully typed, guaranteed-present values, instead of repeating `process.env.X` checks everywhere.

## Key takeaways

- Never hardcode ports, connection strings or secrets, read them from `process.env`.
- `.env` files plus `dotenv` make local development convenient, `.env` itself must always be gitignored.
- `process.env` values are `string | undefined` by default, validate required ones once at startup.
- The same code should work in development and production purely by changing where the environment variables come from, never by changing the code.
