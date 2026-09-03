# Indexes and Query Performance

## Why queries slow down

Without help, a database checks a query's condition against every single row in a table, one by one, to find matches. This is called a full table scan.

```
WHERE email = 'ravi@example.com'

Table with 10 rows:    checking 10 rows, instant
Table with 10 million rows:    checking 10 million rows, slow
```

At small scale this is invisible. As a table grows, queries that filter, sort or join on a column without help get proportionally slower, this is exactly the kind of bottleneck [`04-scalability.md`](../0%20Concepts/04-scalability.md) describes as "usually the real bottleneck".

## What an index does

An index is a separate, sorted data structure the database keeps alongside the table, built on one or more columns. It lets the database jump almost directly to matching rows instead of scanning everything.

```
Without an index:                  With an index on "email":
scan every row one by one    ┌─────────────────────────┐
                              │ sorted lookup structure │
row 1: no match               │ (like a book's index)   │
row 2: no match               └─────────────────────────┘
row 3: match! (found late)          finds the match almost
...                                  instantly, regardless
row 10,000,000: done                of table size
```

A rough real-world comparison: finding a name in an unsorted list of a million names means checking them one by one. Finding it in a sorted phone book with an index means jumping almost straight to it. Same idea here.

## Adding an index in Prisma

```prisma
model Submission {
  id        Int      @id @default(autoincrement())
  status    String
  userId    Int
  problemId Int

  @@index([userId])       // speeds up queries filtering by userId
  @@index([problemId])    // speeds up queries filtering by problemId
}
```

`@@index([field])` tells Prisma (and the migration it generates) to create a database index on that column.

## The primary key is already indexed

You never need to manually index a column marked `@id`, Postgres creates an index for the primary key automatically. The same applies to any field marked `@unique`.

```prisma
model User {
  id    Int    @id @default(autoincrement())  // already indexed, automatic
  email String @unique                         // already indexed, automatic
}
```

## Which columns actually need an index

📌 **Rule of thumb**: index the columns you **filter, join or sort by**, not every column.

```ts
// this query filters by problemId -> problemId should be indexed
await prisma.submission.findMany({ where: { problemId: 5 } });

// this query filters by userId AND sorts by createdAt
// -> a composite index on [userId, createdAt] helps most here
await prisma.submission.findMany({
  where: { userId: 2 },
  orderBy: { createdAt: "desc" },
});
```

```prisma
model Submission {
  // ...
  @@index([userId, createdAt])
}
```

## The tradeoff: indexes are not free

⚠️ **The tradeoff**: indexes speed up reads, but slow down writes, since every `insert`/`update` must also update every index on that table, and each index uses extra storage.

| | No index | With index |
|---|---|---|
| Read speed (filtering by that column) | Slow on large tables | Fast, even on large tables |
| Write speed (insert/update) | Faster, nothing extra to update | Slightly slower, index must update too |
| Storage used | None extra | Extra space for the index structure |

This is why "index every column, just in case" is the wrong instinct. A table that is written to constantly but rarely filtered by a given column gains nothing from indexing it, and pays a real cost.

## A practical checklist for AlgoRift

| Column | Index it? | Why |
|---|---|---|
| `Problem.id`, `Tag.id`, `Submission.id` | Automatic | Primary keys are always indexed |
| `User.email` | Yes (`@unique`) | Looked up on every login, uniqueness needs an index anyway |
| `Submission.userId` | Yes | Every "my submissions" query filters by this |
| `Submission.problemId` | Yes | Every "submissions for this problem" query filters by this |
| `Problem.description` (long text) | No | Never filtered or sorted by directly |

## Seeing it happen

You do not need to memorize database internals to use this correctly day to day. The practical workflow: build the feature first, then if a specific query feels slow as the data grows, check whether it filters or sorts by a column that has no index, and add one, exactly matching the "measure first, then optimize the proven bottleneck" rule from [`04-scalability.md`](../0%20Concepts/04-scalability.md).

## Key takeaways

- An index lets the database find matching rows quickly instead of scanning the whole table, the tradeoff being slightly slower writes and extra storage.
- Primary keys and `@unique` fields are indexed automatically, no manual index needed.
- Add `@@index([field])` on columns you actually filter, join or sort by, not every column.
- Do not pre-optimize by indexing everything, add indexes when a real, measured slow query points to a specific column.
