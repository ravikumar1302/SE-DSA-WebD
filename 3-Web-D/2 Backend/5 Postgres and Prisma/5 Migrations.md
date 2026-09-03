# Migrations

## What a migration is

A migration is a recorded, incremental change to your database schema. Every time you add a table, add a column or change a relationship, a new migration captures exactly what changed, as real SQL.

```
migration 1: create Problem table
migration 2: create Tag table
migration 3: create ProblemTag join table
migration 4: add "status" column to Submission
```

Applied in order, these migrations turn an empty database into one matching your current schema exactly. This history is also what lets a teammate, or a fresh production database, reach the exact same schema by simply running every migration in order.

## Why not just edit the schema by hand

Editing tables directly in a database GUI, or with ad-hoc SQL run once, feels faster in the moment. It breaks down for a real reason: there is no record of what changed, when or why. Another environment (your teammate's machine, production) has no way to catch up automatically, and you have no way to undo a bad change cleanly.

⚠️ **Pitfall**: editing the database by hand instead of through migrations means your `schema.prisma` file and your actual database can silently drift apart. Prisma Client, generated from the schema file, will then not match reality, and queries can fail in confusing ways.

## `prisma migrate dev`

Used only in development.

```bash
npx prisma migrate dev --name add_submission_status
```

This does four things, in order:

1. Compares your current `schema.prisma` against the last known migration state.
2. Generates a new SQL migration file describing the difference.
3. Applies that SQL to your (development) database.
4. Regenerates Prisma Client to match.

```
prisma/migrations/
├── 20240101000000_init/
│   └── migration.sql
├── 20240103000000_add_submission_status/
│   └── migration.sql
```

Each folder is one migration, named with a timestamp and the `--name` you gave it. Meaningful names (`add_submission_status`, not `update1`) make this history actually readable later.

## `prisma migrate deploy`

Used in production, and only in production.

```bash
npx prisma migrate deploy
```

Applies any migrations that exist but have not yet run against this database. It does **not** generate new migrations, compare against your schema file or ask any questions, it purely replays existing, already-committed migration files.

## `migrate dev` vs `migrate deploy`

| | `migrate dev` | `migrate deploy` |
|---|---|---|
| Creates new migration files | Yes | No |
| Where it runs | Local development database | Production (or staging) database |
| Interactive prompts | Yes, may ask about data loss | No, fully non-interactive |
| Safe to run repeatedly | Mostly, designed for iteration | Yes, applies only what has not run yet |

⚠️ **Pitfall from the roadmap**: running `migrate dev` against production is a real mistake beginners make. It can prompt for destructive changes or behave unpredictably outside a development context. Production always uses `migrate deploy`, this is exactly what Phase 5 of the roadmap's deploy checklist calls out.

## A typical migration workflow

```
1. Edit schema.prisma (add a field, a table, a relation)
        |
        v
2. npx prisma migrate dev --name <describe the change>
        |
        v
3. Prisma Client regenerates automatically, TypeScript now knows about the change
        |
        v
4. Commit both schema.prisma AND the new migration folder to git
        |
        v
5. On deploy: npx prisma migrate deploy applies it to production
```

Migration files must be committed to git. They are not build output, they are the actual history of your schema, and production needs them to know what to apply.

## Rolling back

Prisma does not have a single "undo last migration" command, since a migration can be genuinely destructive (e.g. it already dropped a column, the data is gone). The standard approach: write a new migration that reverses the change, keeping the history honest about everything that actually happened.

📌 This is the same idea as never rewriting git history on a shared branch, forward-only changes keep everyone's understanding of "what actually happened" consistent.

## `prisma generate` vs `prisma migrate`

| Command | What it touches | When it runs |
|---|---|---|
| `prisma generate` | Only regenerates Prisma Client's TypeScript types, does not touch the database | Automatically after `migrate dev`, or manually after pulling schema changes from git |
| `prisma migrate dev` | Changes the actual database AND regenerates the client | When you personally changed the schema |

⚠️ If you pull a teammate's schema change from git, your local Prisma Client is now out of date until you run `npx prisma generate` (or `npx prisma migrate dev`, which includes it). A common symptom: TypeScript errors about fields that "don't exist", even though they are clearly in `schema.prisma`.

## Key takeaways

- Migrations are the recorded, ordered history of every schema change, always commit the generated migration files to git.
- `migrate dev` is for local development, creates and applies new migrations. `migrate deploy` is for production, only applies what already exists.
- Never edit the database schema by hand, it breaks the link between `schema.prisma`, the migration history and the real database.
- After pulling schema changes made by someone else, run `prisma generate` (or `migrate dev`) to catch your local Prisma Client back up.
