# Relations in Prisma

This file covers how the one-to-many and many-to-many relationships from [Relational Modeling Basics](0%20Relational%20Modeling%20Basics.md) are actually written in `schema.prisma`, and how to query across them.

## One-to-many: Problem and Submission

```prisma
model Problem {
  id          Int          @id @default(autoincrement())
  title       String
  submissions Submission[]  // "a Problem has many Submissions"
}

model Submission {
  id        Int      @id @default(autoincrement())
  code      String
  status    String
  problemId Int                                  // the foreign key column
  problem   Problem  @relation(fields: [problemId], references: [id])  // the relation itself
}
```

| Line | Meaning |
|---|---|
| `submissions Submission[]` in `Problem` | Not a real column, a convenience field, "give me all related submissions" |
| `problemId Int` in `Submission` | The actual foreign key column, stored in the database |
| `problem Problem @relation(...)` | Tells Prisma how `problemId` connects back to `Problem.id` |

```
Problem                    Submission
┌────┐                     ┌────┬───────────┐
│ id │◄────────────────────│ id │ problemId │
└────┘                     └────┴───────────┘
        one problem, many submissions pointing back to it
```

## Creating a submission tied to a problem

```ts
const submission = await prisma.submission.create({
  data: {
    code: "print('hi')",
    status: "pending",
    problemId: 5,   // links this submission to problem 5
  },
});
```

## Fetching a problem with its submissions: `include`

By default, Prisma does not fetch related data, only the requested table's own columns. Use `include` to pull in related rows in the same query.

```ts
const problem = await prisma.problem.findUnique({
  where: { id: 1 },
  include: { submissions: true },
});

// problem.submissions is now Submission[], attached directly
```

Without `include`, `problem.submissions` would not exist on the returned object at all.

⚠️ **Pitfall**: fetching a list of problems, then separately querying submissions for each one in a loop, is the N+1 query problem described in [`05-databases-and-storage.md`](../0%20Concepts/05-databases-and-storage.md). `include` fetches everything needed in far fewer queries, always prefer it over manual loops.

```ts
// wrong: N+1 queries (one for problems, then one more per problem)
const problems = await prisma.problem.findMany();
for (const problem of problems) {
  const submissions = await prisma.submission.findMany({ where: { problemId: problem.id } });
}

// right: one query, submissions included directly
const problems = await prisma.problem.findMany({
  include: { submissions: true },
});
```

## Many-to-many: Problem and Tag

Many-to-many needs an explicit join table, `ProblemTag`, as covered in the modeling basics file.

```prisma
model Problem {
  id   Int          @id @default(autoincrement())
  title String
  tags ProblemTag[]
}

model Tag {
  id       Int          @id @default(autoincrement())
  name     String       @unique
  problems ProblemTag[]
}

model ProblemTag {
  problemId Int
  tagId     Int
  problem   Problem @relation(fields: [problemId], references: [id])
  tag       Tag     @relation(fields: [tagId], references: [id])

  @@id([problemId, tagId])   // composite primary key, one pairing appears only once
}
```

`@@id([problemId, tagId])` makes the combination of both columns the primary key, so the same problem-tag pairing cannot be inserted twice.

### Prisma's implicit many-to-many (a shortcut)

For simple cases where the join table carries no extra data of its own, Prisma can manage the join table for you automatically, without writing a `ProblemTag` model at all.

```prisma
model Problem {
  id   Int   @id @default(autoincrement())
  title String
  tags Tag[]
}

model Tag {
  id       Int       @id @default(autoincrement())
  name     String    @unique
  problems Problem[]
}
```

Prisma creates and manages a hidden join table behind the scenes.

| | Explicit join table (`ProblemTag` model) | Implicit join table (Prisma-managed) |
|---|---|---|
| Extra columns on the pairing (e.g. `addedAt`) | Yes, add them to the model | No, only the two foreign keys exist |
| You query the join table directly | Yes, if needed | No, it is hidden from you |
| Setup complexity | More code, more control | Less code, less flexibility |

📌 **Rule of thumb**: start with the implicit shortcut unless you specifically need extra data on the pairing itself (for example, tracking who added a tag and when). AlgoRift's `ProblemTag` needs no extra fields, so the implicit version works fine.

## Connecting many-to-many data

```ts
const problem = await prisma.problem.create({
  data: {
    title: "Two Sum",
    tags: {
      connect: [{ id: 1 }, { id: 2 }],  // link to existing tags by id
    },
  },
});
```

```ts
const problem = await prisma.problem.create({
  data: {
    title: "Two Sum",
    tags: {
      create: [{ name: "Array" }, { name: "Hash Map" }], // create new tags on the fly
    },
  },
});
```

`connect` links to tags that already exist. `create` (nested inside another `create`) makes new related rows in the same call. Mixing both is also valid when some tags already exist and others do not.

## Fetching a problem with both relations at once

```ts
const problem = await prisma.problem.findUnique({
  where: { id: 1 },
  include: {
    submissions: true,
    tags: { include: { tag: true } },  // include the actual Tag data, not just the join rows
  },
});
```

With the explicit `ProblemTag` join table, `problem.tags` is an array of `ProblemTag` rows, each needing its own nested `include: { tag: true }` to reach the actual tag name. With the implicit shortcut, `problem.tags` gives you the `Tag[]` directly, one less nesting level.

## Key takeaways

- One-to-many: the "many" side stores a foreign key column, the "one" side gets a convenience array field through `@relation`.
- Many-to-many always needs a join table, either written explicitly (when the pairing needs extra data) or handled implicitly by Prisma (when it does not).
- `include` fetches related data in the same query, always prefer it over fetching relations in a manual loop.
- `connect` links to existing related rows, `create` makes new ones, both work inside a single `create` or `update` call.
