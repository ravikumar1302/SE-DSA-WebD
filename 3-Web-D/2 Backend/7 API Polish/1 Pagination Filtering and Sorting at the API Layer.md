# Pagination, Filtering and Sorting at the API Layer

[Filtering Sorting and Pagination](../5%20Postgres%20and%20Prisma/4%20Filtering%20Sorting%20and%20Pagination.md) in the Phase 2 folder covered how Prisma's `where`, `orderBy`, `skip` and `take` work. This file covers the layer above that: designing the actual API contract (query params in, response shape out) so every list endpoint behaves the same way.

## Designing the query parameters

```
GET /problems?difficulty=easy&sort=createdAt&order=desc&page=2&limit=10
```

| Param | Purpose | Maps to |
|---|---|---|
| `difficulty` | Filter | `where: { difficulty }` |
| `sort` | Which field to sort by | `orderBy: { [sort]: order }` |
| `order` | Direction | `"asc"` or `"desc"` |
| `page` | Which page | used to compute `skip` |
| `limit` | Page size | `take` |

## Parsing and validating query params with Zod

Query params arrive as strings (or `undefined`), covered in [Where Data Lives in a Request](../4%20Express%20Fundamentals/2%20Where%20Data%20Lives%20in%20a%20Request.md). Zod can validate and convert them in one step, the same tool already used for request bodies in Phase 3.

```ts
import { z } from "zod";

const ListProblemsQuerySchema = z.object({
  difficulty: z.enum(["easy", "medium", "hard"]).optional(),
  sort: z.enum(["createdAt", "title"]).default("createdAt"),
  order: z.enum(["asc", "desc"]).default("desc"),
  page: z.coerce.number().int().min(1).default(1),
  limit: z.coerce.number().int().min(1).max(100).default(10),
});
```

`z.coerce.number()` converts a string query param (`"2"`) into an actual number before validating it, exactly the manual `Number(req.query.page) || 1` pattern from earlier phases, now handled declaratively, with proper bounds enforced (`.min(1).max(100)`) in the same place.

## Using it in the controller

```ts
export const problemsController = {
  async getAll(req: Request, res: Response) {
    const query = ListProblemsQuerySchema.parse(req.query);

    const where = query.difficulty ? { difficulty: query.difficulty } : {};

    const [problems, total] = await Promise.all([
      prisma.problem.findMany({
        where,
        orderBy: { [query.sort]: query.order },
        skip: (query.page - 1) * query.limit,
        take: query.limit,
      }),
      prisma.problem.count({ where }),
    ]);

    sendSuccess(res, {
      items: problems,
      pagination: {
        page: query.page,
        limit: query.limit,
        total,
        totalPages: Math.ceil(total / query.limit),
      },
    });
  },
};
```

## The consistent list response shape

Every paginated endpoint returns the same nested shape, matching the envelope pattern from the previous file.

```json
{
  "success": true,
  "data": {
    "items": [ { "id": 1, "title": "Two Sum" }, { "id": 2, "title": "..." } ],
    "pagination": {
      "page": 2,
      "limit": 10,
      "total": 47,
      "totalPages": 5
    }
  }
}
```

A frontend built against this shape can build one generic pagination component and reuse it for `problems`, `submissions` and any other list endpoint you add later, since they all share the exact same `{ items, pagination }` structure.

## A reusable generic type for this

```ts
interface PaginatedResult<T> {
  items: T[];
  pagination: {
    page: number;
    limit: number;
    total: number;
    totalPages: number;
  };
}

type ProblemsResponse = ApiResponse<PaginatedResult<Problem>>;
```

Same generics pattern as `ApiResponse<T>`, one shape, reused for every list endpoint regardless of what it lists.

## A shared pagination helper (avoids repeating the same math everywhere)

```ts
export function buildPaginationMeta(page: number, limit: number, total: number) {
  return { page, limit, total, totalPages: Math.ceil(total / limit) };
}
```

```ts
sendSuccess(res, {
  items: problems,
  pagination: buildPaginationMeta(query.page, query.limit, total),
});
```

## Validating the query schema itself, not just parsing it silently

⚠️ **Pitfall**: if `sort` allows any arbitrary string instead of a fixed `z.enum([...])`, a client could pass `sort=password` for a model that happens to have such a field, and get results ordered by it, an unintended way to probe field existence or leak minor information. Always restrict `sort` to an explicit allowlist of real, safe-to-sort-by fields, never pass the raw query value straight into Prisma's `orderBy`.

## Key takeaways

- Query params for filtering, sorting and pagination should be validated with the same tool (Zod) used for request bodies, `z.coerce` handles the string-to-number conversion cleanly.
- Every list endpoint should return the same `{ items, pagination }` shape, letting the frontend build one reusable pagination component for the whole API.
- Always restrict sortable fields to an explicit allowlist (`z.enum([...])`), never pass a raw query string directly into `orderBy`.
- This file is the API-facing contract, the underlying Prisma mechanics (`where`, `orderBy`, `skip`, `take`) were already covered in Phase 2.
