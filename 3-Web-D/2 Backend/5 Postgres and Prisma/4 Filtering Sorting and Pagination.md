# Filtering, Sorting and Pagination

Real APIs rarely return every row in a table. `GET /problems` on a table with 50,000 rows needs filtering, sorting and pagination, otherwise every request pulls the entire table over the network.

## `where`: filtering

```ts
const easyProblems = await prisma.problem.findMany({
  where: { difficulty: "easy" },
});
```

### Common filter operators

```ts
await prisma.problem.findMany({
  where: {
    difficulty: "easy",
    title: { contains: "sum" },       // partial text match
    createdAt: { gte: someDate },     // greater than or equal
  },
});
```

| Operator | Meaning | Example |
|---|---|---|
| `equals` (default, can be omitted) | Exact match | `{ difficulty: "easy" }` |
| `not` | Not equal | `{ difficulty: { not: "hard" } }` |
| `in` | Matches any value in a list | `{ difficulty: { in: ["easy", "medium"] } }` |
| `contains` | Text contains a substring | `{ title: { contains: "sum" } }` |
| `gt`, `gte`, `lt`, `lte` | Greater/less than (numbers, dates) | `{ createdAt: { gte: someDate } }` |

### Combining conditions

```ts
// AND (default when listing multiple fields)
await prisma.problem.findMany({
  where: { difficulty: "easy", title: { contains: "sum" } },
});

// OR (explicit)
await prisma.problem.findMany({
  where: {
    OR: [{ difficulty: "easy" }, { difficulty: "medium" }],
  },
});
```

## `orderBy`: sorting

```ts
await prisma.problem.findMany({
  orderBy: { createdAt: "desc" },  // newest first
});
```

```ts
await prisma.problem.findMany({
  orderBy: [{ difficulty: "asc" }, { createdAt: "desc" }],  // sort by difficulty, then newest within each
});
```

## Pagination: `skip` and `take`

```ts
const page = 2;
const limit = 10;

const problems = await prisma.problem.findMany({
  skip: (page - 1) * limit,  // how many rows to skip
  take: limit,                // how many rows to return
});
```

```
page 1: skip 0,  take 10   -> rows 1-10
page 2: skip 10, take 10   -> rows 11-20
page 3: skip 20, take 10   -> rows 21-30
```

⚠️ **Pitfall**: an endpoint without a `take` limit will happily return every row in the table on a single request. Always cap `limit`, and set a sensible maximum even if the client requests more.

```ts
const limit = Math.min(Number(req.query.limit) || 10, 100); // never more than 100
```

## Returning total count for pagination info

The client usually needs to know the total number of matching rows too, to render page numbers or a "showing X of Y" message.

```ts
const [problems, total] = await Promise.all([
  prisma.problem.findMany({ where, skip, take }),
  prisma.problem.count({ where }),
]);

res.json({
  data: problems,
  pagination: { page, limit, total, totalPages: Math.ceil(total / limit) },
});
```

Running both queries with `Promise.all` fetches them in parallel instead of one after another, faster than doing them sequentially.

## A full controller example

```ts
export const problemsController = {
  async getAll(req: Request, res: Response) {
    const page = Number(req.query.page) || 1;
    const limit = Math.min(Number(req.query.limit) || 10, 100);
    const difficulty = req.query.difficulty as string | undefined;

    const where = difficulty ? { difficulty } : {};

    const [problems, total] = await Promise.all([
      prisma.problem.findMany({
        where,
        orderBy: { createdAt: "desc" },
        skip: (page - 1) * limit,
        take: limit,
      }),
      prisma.problem.count({ where }),
    ]);

    res.status(200).json({
      data: problems,
      pagination: { page, limit, total, totalPages: Math.ceil(total / limit) },
    });
  },
};
```

```
GET /problems?difficulty=easy&page=2&limit=10
```

This single query handles filtering (`difficulty`), sorting (newest first) and pagination (`page`/`limit`) together, all pushed down into the database rather than done in JavaScript after fetching everything.

## Offset pagination vs cursor pagination

`skip`/`take` (also called offset pagination) is simple and covers most needs, including AlgoRift's. It has one weakness worth knowing about.

| | Offset pagination (`skip`/`take`) | Cursor pagination |
|---|---|---|
| How it works | "Skip N rows, then take the next batch" | "Give me rows after this specific row's id" |
| Simplicity | Simple, easy to reason about | More setup, needs a stable sort field |
| Weakness | If rows are added/removed while paging, results can shift or repeat | Stable even while data changes |
| Performance on huge tables | Gets slower for very high page numbers | Stays fast regardless of page depth |

📌 Offset pagination is the right default for a project like AlgoRift. Cursor pagination matters at a much larger scale (think infinite-scroll feeds with millions of rows), file it under "know it exists" for now.

## Key takeaways

- `where` filters, `orderBy` sorts, `skip`/`take` paginate, all three combine in one query and run inside the database, not in your application code.
- Always cap `limit` to a sane maximum, never trust the client to ask for a reasonable page size.
- Use `Promise.all` to fetch data and a total count together, needed to build proper pagination metadata for the client.
- Offset pagination is the correct default choice for this project, cursor pagination is a "know it exists" concept for much larger scale.
