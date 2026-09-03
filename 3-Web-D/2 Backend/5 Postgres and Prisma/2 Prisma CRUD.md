# Prisma CRUD

All examples assume this model and a shared `prisma` client:

```prisma
model Problem {
  id          Int      @id @default(autoincrement())
  title       String
  difficulty  String
  createdAt   DateTime @default(now())
}
```

```ts
import { prisma } from "../lib/prisma";
```

## Create

```ts
const problem = await prisma.problem.create({
  data: {
    title: "Two Sum",
    difficulty: "easy",
  },
});
```

`create` returns the full created row, including the auto-generated `id` and `createdAt`, since the database fills those in.

## Read: `findMany`

```ts
const problems = await prisma.problem.findMany();
```

Returns every row as an array. Almost every query starts here, then adds options.

```ts
const easyProblems = await prisma.problem.findMany({
  where: { difficulty: "easy" },
});
```

## Read: `findUnique`

Finds exactly one row by a unique field (usually the primary key).

```ts
const problem = await prisma.problem.findUnique({
  where: { id: 1 },
});
// problem is Problem | null
```

Returns `null` if nothing matches, never throws. Always check for `null` before using the result.

```ts
const problem = await prisma.problem.findUnique({ where: { id } });
if (!problem) {
  throw new NotFoundError(`Problem ${id} not found`);
}
```

## Read: `findFirst`

Like `findMany`, but returns only the first matching row, or `null`. Useful when a `where` clause is not guaranteed unique, but you only want one result.

```ts
const problem = await prisma.problem.findFirst({
  where: { title: "Two Sum" },
});
```

## `findUnique` vs `findFirst`

| | `findUnique` | `findFirst` |
|---|---|---|
| Requires a unique field | Yes (id, or any field marked `@unique`) | No, any condition works |
| Performance | Faster, database can use a direct lookup | Slower, scans until it finds a match |
| Use when | Looking up by id or another unique field | Filtering by a non-unique field, first match is fine |

## Update

```ts
const updated = await prisma.problem.update({
  where: { id: 1 },
  data: { difficulty: "medium" },
});
```

`update` throws an error if no row matches the `where` clause, unlike `findUnique`, which returns `null`. Always confirm the row exists first, or catch the error.

```ts
try {
  const updated = await prisma.problem.update({
    where: { id },
    data: req.body,
  });
  res.status(200).json(updated);
} catch (err) {
  throw new NotFoundError(`Problem ${id} not found`);
}
```

## Delete

```ts
await prisma.problem.delete({
  where: { id: 1 },
});
```

Same rule applies: throws if the row does not exist. Same try/catch pattern as `update`.

## Comparing to the Phase 1 in-memory service

The service layer's public shape barely changes, only the internals swap from array operations to Prisma calls. This is exactly why the routes/controllers/services split from Phase 1 pays off now.

```ts
// Phase 1: in-memory array
export const problemService = {
  getAll(): Problem[] {
    return problems;
  },
  // ...
};

// Phase 2: real database, same shape, now async
export const problemService = {
  async getAll(): Promise<Problem[]> {
    return prisma.problem.findMany();
  },
  // ...
};
```

⚠️ **Pitfall**: every Prisma call returns a `Promise`. Forgetting `await` means you get a `Promise` object instead of the actual data, and `res.json()` will send back something like `{}` instead of your real result. Controllers calling these service functions must also be updated to `await` them.

## The full rewritten service

```ts
import { prisma } from "../lib/prisma";

export const problemService = {
  async getAll() {
    return prisma.problem.findMany();
  },

  async getById(id: number) {
    return prisma.problem.findUnique({ where: { id } });
  },

  async create(data: { title: string; difficulty: string }) {
    return prisma.problem.create({ data });
  },

  async update(id: number, data: Partial<{ title: string; difficulty: string }>) {
    return prisma.problem.update({ where: { id }, data });
  },

  async delete(id: number) {
    return prisma.problem.delete({ where: { id } });
  },
};
```

## Summary table

| Operation | Method | Returns on no match | Throws on no match |
|---|---|---|---|
| Create | `create` | N/A | N/A |
| Read many | `findMany` | Empty array `[]` | No |
| Read one (by unique field) | `findUnique` | `null` | No |
| Read one (any condition) | `findFirst` | `null` | No |
| Update | `update` | N/A | Yes |
| Delete | `delete` | N/A | Yes |

## Key takeaways

- `create`, `findMany`, `findUnique`, `update` and `delete` cover the same five operations the Phase 1 in-memory service already had, just backed by a real database now.
- `findUnique`/`findFirst` return `null` on no match, `update`/`delete` throw instead, handle each correctly.
- Every Prisma call is async, `await` it, and mark the surrounding function `async` too.
- The routes/controllers layers barely change, only the service internals do, proving the layered structure from Phase 1 was worth building.
