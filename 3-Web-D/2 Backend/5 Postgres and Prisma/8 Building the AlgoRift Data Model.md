# Building the AlgoRift Data Model

This file walks through Phase 2's full deliverable: replacing the Phase 1 in-memory array with real Postgres tables for `Problem`, `Tag` and `Submission`, connected exactly as planned in [Relational Modeling Basics](0%20Relational%20Modeling%20Basics.md).

## The full `schema.prisma`

```prisma
generator client {
  provider = "prisma-client-js"
}

datasource db {
  provider = "postgresql"
  url      = env("DATABASE_URL")
}

model Problem {
  id          Int          @id @default(autoincrement())
  title       String
  description String
  difficulty  String
  createdAt   DateTime     @default(now())
  submissions Submission[]
  tags        Tag[]
}

model Tag {
  id       Int       @id @default(autoincrement())
  name     String    @unique
  problems Problem[]
}

model Submission {
  id        Int      @id @default(autoincrement())
  code      String
  status    String
  createdAt DateTime @default(now())

  problemId Int
  problem   Problem  @relation(fields: [problemId], references: [id])

  @@index([problemId])
}
```

This uses Prisma's implicit many-to-many for `Problem` ↔ `Tag` (no separate `ProblemTag` model needed, since the pairing carries no extra data), and an explicit foreign key for the one-to-many `Problem` → `Submission` relationship. Both patterns are covered in [Relations in Prisma](3%20Relations%20in%20Prisma.md).

## Applying it

```bash
npx prisma migrate dev --name init
```

This creates all three tables (plus Prisma's own hidden join table for the `Problem` ↔ `Tag` relation) in your Neon database in one step.

## Rewriting the service layer

The Phase 1 `problemService` (array-based) becomes this, following the same shape covered in [Prisma CRUD](2%20Prisma%20CRUD.md):

```ts
import { prisma } from "../lib/prisma";

interface CreateProblemInput {
  title: string;
  description: string;
  difficulty: string;
  tagIds?: number[];
}

export const problemService = {
  async getAll() {
    return prisma.problem.findMany({
      include: { tags: true },
      orderBy: { createdAt: "desc" },
    });
  },

  async getById(id: number) {
    return prisma.problem.findUnique({
      where: { id },
      include: { tags: true, submissions: true },
    });
  },

  async create(data: CreateProblemInput) {
    const { tagIds, ...rest } = data;
    return prisma.problem.create({
      data: {
        ...rest,
        tags: tagIds ? { connect: tagIds.map((id) => ({ id })) } : undefined,
      },
      include: { tags: true },
    });
  },

  async update(id: number, data: Partial<CreateProblemInput>) {
    const { tagIds, ...rest } = data;
    return prisma.problem.update({
      where: { id },
      data: {
        ...rest,
        tags: tagIds ? { set: tagIds.map((id) => ({ id })) } : undefined,
      },
      include: { tags: true },
    });
  },

  async delete(id: number) {
    return prisma.problem.delete({ where: { id } });
  },
};
```

Note `tags: { set: [...] }` in `update`, this replaces the entire set of connected tags with a new list, different from `connect`, which only adds to the existing set without removing anything.

| Operation | Effect on relations |
|---|---|
| `connect: [...]` | Adds these to the existing related rows |
| `set: [...]` | Replaces the entire related set with exactly these |
| `disconnect: [...]` | Removes these specific related rows, keeps the rest |

## The submission service

```ts
export const submissionService = {
  async create(problemId: number, data: { code: string }) {
    return prisma.submission.create({
      data: {
        code: data.code,
        status: "pending",
        problemId,
      },
    });
  },

  async getByProblem(problemId: number) {
    return prisma.submission.findMany({
      where: { problemId },
      orderBy: { createdAt: "desc" },
    });
  },
};
```

## Updating the controller for async

Every controller method calling these services needs `async`/`await` now, since Phase 1's synchronous array access has been replaced with real, awaited database calls.

```ts
export const problemsController = {
  async getAll(req: Request, res: Response) {
    const problems = await problemService.getAll();
    res.status(200).json(problems);
  },

  async getById(req: Request, res: Response) {
    const id = Number(req.params.id);
    const problem = await problemService.getById(id);
    if (!problem) throw new NotFoundError(`Problem ${id} not found`);
    res.status(200).json(problem);
  },

  // create, update, delete follow the same async pattern
};
```

⚠️ Since these controllers are now `async` and can `throw` from inside an awaited call, wrap them with the `asyncHandler` helper from [Centralized Error Handling](../4%20Express%20Fundamentals/4%20Centralized%20Error%20Handling.md) (in Express 4), so a thrown or rejected error actually reaches your error handler instead of hanging the request.

```ts
router.get("/:id", asyncHandler(problemsController.getById));
```

## Fetching a problem with everything, in one query

```ts
const problem = await prisma.problem.findUnique({
  where: { id: 1 },
  include: {
    tags: true,
    submissions: {
      orderBy: { createdAt: "desc" },
      take: 5,   // just the 5 most recent
    },
  },
});
```

One database round trip returns the problem, its tags and its 5 most recent submissions together, matching the roadmap's "fetch a problem with its tags and submissions" checklist item exactly.

## Verifying it visually

```bash
npx prisma studio
```

Create a problem, attach some tags, add a submission and confirm everything links up correctly in the table view before moving on.

## Done when

All `problems` CRUD persists to Neon, `tags` and `submissions` exist with correct relations and you can fetch a problem with its related data in one query, matching Phase 2 of the roadmap exactly.

## Key takeaways

- This file combines every earlier file in this folder: relational modeling, Neon/Prisma setup, CRUD, relations, filtering/pagination, migrations and indexing, into the actual working AlgoRift data layer.
- `include` fetches related data in one query, `connect`/`set`/`disconnect` control many-to-many relationships precisely.
- Moving from an in-memory array to Prisma changes almost nothing about the routes/controllers structure, only the service internals and the addition of `async`/`await`, proof the Phase 1 layering was worth the setup.
