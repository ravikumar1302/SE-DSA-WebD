# Neon and Prisma Setup

## What Neon is

Neon is a serverless PostgreSQL host. "Serverless" here means you do not manage a server yourself, you get a working Postgres database instantly, and it scales down automatically when idle, useful for a free-tier personal project like AlgoRift.

```
Your Express app  ────network────>  Neon (runs Postgres for you)
```

Neon is a hosting choice, not a different kind of database. Everything you learn about PostgreSQL applies exactly the same whether it runs on Neon, a local install or any other host.

## Creating a Neon project

1. Sign up at Neon and create a new project.
2. Neon gives you a **connection string**, a single URL containing everything needed to connect: host, port, database name, username and password.

```
postgresql://username:password@host.neon.tech/dbname?sslmode=require
```

⚠️ **Pitfall**: this string contains your database password in plain text. Never commit it to git, it goes in `.env`, covered in [Env Vars and Config](../4%20Express%20Fundamentals/5%20Env%20Vars%20and%20Config.md).

```
# .env
DATABASE_URL="postgresql://username:password@host.neon.tech/dbname?sslmode=require"
```

## What Prisma is

Prisma is an ORM (Object-Relational Mapper), covered conceptually in [`05-databases-and-storage.md`](../0%20Concepts/05-databases-and-storage.md). In practice, it is three things working together:

| Part | What it does |
|---|---|
| `schema.prisma` | A file where you describe your tables and their relationships, in a simple, readable syntax |
| Prisma Migrate | Turns your schema into actual SQL commands that create/alter tables in the real database |
| Prisma Client | A fully typed JavaScript/TypeScript library, generated from your schema, used to query the database in your code |

```
schema.prisma  ──(migrate)──>  Real Postgres tables
schema.prisma  ──(generate)──> Prisma Client (typed query functions in your code)
```

## Installing Prisma

```bash
npm install -D prisma
npm install @prisma/client
```

`prisma` (the CLI, a dev dependency) is used while developing, for migrations and schema changes. `@prisma/client` (a regular dependency) is the library your running app actually imports to query the database.

## Initializing Prisma

```bash
npx prisma init
```

This creates:

```
prisma/
└── schema.prisma
.env              (adds a DATABASE_URL placeholder if not already present)
```

## The `schema.prisma` file

```prisma
generator client {
  provider = "prisma-client-js"
}

datasource db {
  provider = "postgresql"
  url      = env("DATABASE_URL")
}

model Problem {
  id          Int      @id @default(autoincrement())
  title       String
  description String
  difficulty  String
  createdAt   DateTime @default(now())
}
```

| Part | Meaning |
|---|---|
| `generator client` | Tells Prisma to generate the TypeScript client library |
| `datasource db` | Which database, and where its connection string comes from (`.env`, via `DATABASE_URL`) |
| `model Problem` | Defines a table named `Problem` |
| `@id` | Marks `id` as the primary key |
| `@default(autoincrement())` | Postgres generates the next number automatically |
| `@default(now())` | Fills in the current timestamp automatically when a row is created |

## Prisma field types

| Prisma type | Maps to (roughly) | TypeScript type generated |
|---|---|---|
| `String` | `text`/`varchar` | `string` |
| `Int` | `integer` | `number` |
| `Boolean` | `boolean` | `boolean` |
| `DateTime` | `timestamp` | `Date` |
| `Float` | `double precision` | `number` |

## Running your first migration

```bash
npx prisma migrate dev --name init
```

This does three things: creates the actual `Problem` table in your Neon database, saves a record of this change as a migration file (in `prisma/migrations/`) and regenerates Prisma Client to match the new schema.

```
prisma/
├── schema.prisma
└── migrations/
    └── 20240101000000_init/
        └── migration.sql
```

📌 Each migration file is real SQL, generated automatically. You rarely need to write it by hand, but it is readable, and it is the actual history of how your schema evolved.

## Using Prisma Client in code

```ts
import { PrismaClient } from "@prisma/client";

export const prisma = new PrismaClient();
```

📌 **Rule of thumb**: create exactly one `PrismaClient` instance and reuse it everywhere (usually exported from a single file, like `src/lib/prisma.ts`). Creating a new one per request opens far more database connections than needed.

```ts
async function getAllProblems() {
  const problems = await prisma.problem.findMany();
  return problems;
}
```

`prisma.problem` here is fully typed, generated directly from your `schema.prisma` model named `Problem`. Your editor will autocomplete every field correctly, and a typo in a field name is a compile error, not a runtime surprise.

## Exploring your data visually

```bash
npx prisma studio
```

Opens a browser-based table editor for your database, useful for checking that data actually looks the way you expect, without writing SQL by hand.

## Key takeaways

- Neon hosts Postgres for you, `DATABASE_URL` in `.env` is how your app connects to it.
- `schema.prisma` describes your tables, `prisma migrate dev` applies that schema to the real database and generates a typed client.
- One shared `PrismaClient` instance is the standard pattern, not one per request.
- `npx prisma studio` gives you a visual way to inspect your data during development.
