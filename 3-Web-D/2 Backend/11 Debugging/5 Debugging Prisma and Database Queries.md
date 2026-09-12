# Debugging Prisma and Database Queries

A wrong or slow database query often looks, from the outside, exactly like a wrong or slow API response. This file is about seeing what Prisma is actually doing underneath the abstraction.

## Turning on Prisma's query log

```ts
const prisma = new PrismaClient({
  log: ["query", "info", "warn", "error"],
});
```

With this enabled, every actual SQL query Prisma runs prints to the terminal, alongside how long it took.

```
prisma:query SELECT "id", "title", "difficulty" FROM "Problem" WHERE "id" = $1 LIMIT $2
prisma:query Params: [12, 1]
```

📌 This is the single fastest way to answer "what is Prisma actually sending to the database," instead of guessing based on the JavaScript call that produced it. Turn it on for local debugging, and off (or set to only `error`) in production, the volume is too high to leave on permanently.

## Confirming the N+1 problem directly

The N+1 pattern (covered conceptually in [`05-databases-and-storage.md`](../0%20Concepts/05-databases-and-storage.md) and practically in [Relations in Prisma](../5%20Postgres%20and%20Prisma/3%20Relations%20in%20Prisma.md)) is easy to suspect but satisfying to actually confirm. With query logging on, a list endpoint fetching relations in a loop shows as many separate `SELECT` queries in the terminal, one per item, instead of one query with a `JOIN`.

```
Without eager loading (N+1), fetching 20 problems' tags:
SELECT ... FROM "Problem" LIMIT 20      <- 1 query
SELECT ... FROM "Tag" WHERE "problemId" = 1   <- then 20 more, one per problem
SELECT ... FROM "Tag" WHERE "problemId" = 2
... (18 more)

With include, one query does the join:
SELECT ... FROM "Problem" LEFT JOIN "Tag" ON ... LIMIT 20   <- 1 query total
```

Counting the actual query lines in the log, rather than reasoning about the code abstractly, removes any doubt about whether this specific endpoint has the problem.

## Prisma Studio, a visual look at the data

```bash
npx prisma studio
```

Opens a browser-based table editor for the actual database, every table, every row, editable directly. Useful for a very specific class of bug: "is the data actually what I think it is," checking whether a row exists, whether a foreign key is set correctly, or whether a migration actually applied the change you expected, without writing a throwaway script or query just to look.

## `EXPLAIN ANALYZE`, reading why a query is slow

For a query that is correct but slow, Postgres can show its actual execution plan.

```sql
EXPLAIN ANALYZE
SELECT * FROM "Submission" WHERE "userId" = 5 ORDER BY "createdAt" DESC;
```

```
Seq Scan on "Submission"  (cost=0.00..1834.00 rows=50000 width=64) (actual time=0.02..12.4 rows=200 loops=1)
  Filter: ("userId" = 5)
```

`Seq Scan` (sequential scan) means Postgres read every row in the table to find matches, exactly what an index avoids. Seeing `Seq Scan` on a large table where you expected an index to be used is the direct evidence behind the advice in [Indexes and Query Performance](../5%20Postgres%20and%20Prisma/6%20Indexes%20and%20Query%20Performance.md), rather than assuming an index helped without checking.

## Reproducing a Prisma error outside the app

For a confusing Prisma error, copying the exact generated SQL (from the query log above) and running it directly in `psql` or Prisma Studio's SQL runner isolates whether the problem is in the query itself or in how the application code is calling Prisma, the same minimal-reproduction idea applied to a database query specifically.

## Common Prisma-specific gotchas to check first

| Symptom | Check |
|---|---|
| A field is missing from a result | Was `include` or `select` used, relations do not load automatically |
| TypeScript says a field does not exist, but it is in the schema | Prisma Client not regenerated, `npx prisma generate` |
| `update`/`delete` throws instead of returning null | Expected behavior for those methods on no match, check existence first |
| Data looks stale after a change | Confirm the migration actually ran against this database, `npx prisma migrate status` |

## Key takeaways

- Prisma's query log shows the real SQL being sent, the fastest way to confirm what is actually happening under the ORM.
- Counting queries in the log directly confirms (or rules out) an N+1 problem, rather than reasoning about it abstractly.
- Prisma Studio is for looking at real data directly, `EXPLAIN ANALYZE` is for understanding why a specific query is slow.
- A confusing Prisma error is often easier to debug by running the actual generated SQL directly against the database first.
