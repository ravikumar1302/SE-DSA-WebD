# Raw SQL Escape Hatch

## Why this exists

Prisma's query methods (`findMany`, `where`, `include`, and so on) cover the large majority of real backend needs. Occasionally a query is complex enough (heavy aggregation, database-specific features, a query that is measurably faster written by hand) that Prisma's normal API cannot express it cleanly. For these rare cases, Prisma provides a way to run real SQL directly.

📌 This is genuinely an escape hatch, not a default tool. Reach for it only when the normal Prisma API cannot do what you need, not as a habit.

## `$queryRaw`

```ts
const problems = await prisma.$queryRaw`
  SELECT * FROM "Problem" WHERE difficulty = ${difficulty}
`;
```

This uses a tagged template literal. Values inside `${}` are automatically parameterized (sent separately from the SQL text), not pasted directly into the query string.

⚠️ **Why this matters, security**: pasting user input directly into a SQL string is how SQL injection attacks happen, covered in [`07-security.md`](../0%20Concepts/07-security.md). `$queryRaw` with tagged template syntax protects you automatically, the same way Prisma's normal query methods do.

```ts
// SAFE: value is parameterized automatically
const problems = await prisma.$queryRaw`SELECT * FROM "Problem" WHERE difficulty = ${difficulty}`;

// DANGEROUS: never build SQL by concatenating strings, even with Prisma available
const problems = await prisma.$queryRawUnsafe(`SELECT * FROM "Problem" WHERE difficulty = '${difficulty}'`);
```

`$queryRawUnsafe` exists for cases where the query structure itself (not just a value) needs to be dynamic, and it does not protect you automatically, you become responsible for safety yourself. Avoid it unless you specifically understand why you need it.

## `$executeRaw`

Same idea, used for queries that change data (`INSERT`, `UPDATE`, `DELETE`) rather than read it.

```ts
await prisma.$executeRaw`UPDATE "Problem" SET difficulty = 'hard' WHERE id = ${id}`;
```

## `$queryRaw` vs normal Prisma queries

| | Normal Prisma methods | `$queryRaw` |
|---|---|---|
| Type safety | Full, matches your schema automatically | Manual, you type the result yourself |
| SQL injection protection | Automatic | Automatic, only with tagged template syntax |
| Readability | High, reads like your schema | Lower, requires knowing SQL |
| When to use | Almost always | Only when normal methods genuinely cannot express the query |

## Typing a raw query result

Prisma cannot know the shape of a raw query's result automatically, so you provide it.

```ts
interface LeaderboardRow {
  userId: number;
  username: string;
  submissionCount: number;
}

const leaderboard = await prisma.$queryRaw<LeaderboardRow[]>`
  SELECT u.id AS "userId", u.username, COUNT(s.id) AS "submissionCount"
  FROM "User" u
  JOIN "Submission" s ON s."userId" = u.id
  WHERE s.status = 'accepted'
  GROUP BY u.id, u.username
  ORDER BY "submissionCount" DESC
  LIMIT 10
`;
```

This is close to a real scenario from Phase 4 of the roadmap, the leaderboard. Aggregating counts per user, grouping and ranking is exactly the kind of query that can outgrow Prisma's built-in query builder as it gets more specific, though Prisma's own aggregation methods (`groupBy`, `count`, `_count`) should still be your first attempt before reaching for raw SQL.

## Prisma's own aggregation methods, worth trying first

```ts
const counts = await prisma.submission.groupBy({
  by: ["userId"],
  where: { status: "accepted" },
  _count: { id: true },
  orderBy: { _count: { id: "desc" } },
  take: 10,
});
```

`groupBy` handles a large share of aggregation needs (grouping, counting, ordering by a count) without dropping to raw SQL at all, fully typed, no manual result interface needed.

📌 **Rule of thumb**: try `groupBy`/`count`/`aggregate` first. Reach for `$queryRaw` only if the query is still not expressible cleanly that way.

## Key takeaways

- `$queryRaw` and `$executeRaw` let you run real SQL when Prisma's normal query API cannot express what you need.
- Tagged template syntax (backticks with `${}`) parameterizes values automatically, protecting against SQL injection, `$queryRawUnsafe` does not, avoid it.
- Raw query results are not automatically typed, provide the expected shape yourself.
- Prisma's own aggregation methods (`groupBy`, `count`, `aggregate`) solve most "I need raw SQL" situations without actually needing raw SQL, try them first.
