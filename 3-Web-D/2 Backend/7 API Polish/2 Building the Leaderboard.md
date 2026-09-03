# Building the Leaderboard

`GET /leaderboard` is Phase 4's centerpiece deliverable: ranking users by their accepted submissions, computed inside the database rather than in application code.

## Why aggregation belongs in the database

A tempting first approach: fetch every submission, then count and rank them in JavaScript.

```ts
// WRONG approach, do not do this
const submissions = await prisma.submission.findMany({ where: { status: "accepted" } });
const counts: Record<number, number> = {};
for (const s of submissions) {
  counts[s.userId] = (counts[s.userId] || 0) + 1;
}
// then sort counts manually...
```

⚠️ **Pitfall**: this pulls every accepted submission across every user, over the network, into your application, just to count them. On a small dataset it works, at real scale it is slow and wastes memory, it is exactly the mistake named directly in the roadmap: "doing aggregation in JS after fetching everything, push it into the DB query." Databases are built to do counting and grouping efficiently, at the data itself, without shipping every row elsewhere first.

## Prisma's `groupBy`, the right tool

```ts
const rankings = await prisma.submission.groupBy({
  by: ["userId"],
  where: { status: "accepted" },
  _count: { id: true },
  orderBy: { _count: { id: "desc" } },
});
```

| Part | Meaning |
|---|---|
| `by: ["userId"]` | Group rows together by this field |
| `where: { status: "accepted" }` | Only count accepted submissions |
| `_count: { id: true }` | For each group, count how many rows it has |
| `orderBy: { _count: { id: "desc" } }` | Sort groups by that count, highest first |

`rankings` comes back as an array like:

```ts
[
  { userId: 3, _count: { id: 42 } },
  { userId: 1, _count: { id: 30 } },
  { userId: 7, _count: { id: 18 } },
]
```

## Joining in user details

`groupBy` only returns the grouped field and the aggregate, not the full `User` row. A second, small query fetches the display data for just the users on the leaderboard.

```ts
async function getLeaderboard(limit: number, page: number) {
  const rankings = await prisma.submission.groupBy({
    by: ["userId"],
    where: { status: "accepted" },
    _count: { id: true },
    orderBy: { _count: { id: "desc" } },
    skip: (page - 1) * limit,
    take: limit,
  });

  const userIds = rankings.map((r) => r.userId);
  const users = await prisma.user.findMany({
    where: { id: { in: userIds } },
    select: { id: true, email: true },
  });

  const userMap = new Map(users.map((u) => [u.id, u]));

  return rankings.map((r, index) => ({
    rank: (page - 1) * limit + index + 1,
    userId: r.userId,
    email: userMap.get(r.userId)?.email,
    acceptedCount: r._count.id,
  }));
}
```

`select: { id: true, email: true }` fetches only the fields actually needed, not the user's password hash or every other column, an easy, deliberate habit worth keeping any time you fetch a `User`.

## Pagination on `groupBy`

`skip`/`take` work directly on `groupBy` results the same way they work on `findMany`, covered in the Phase 2 pagination file, no new concept needed here, just applied to grouped, aggregated rows instead of plain ones.

## The controller

```ts
export const leaderboardController = {
  async get(req: Request, res: Response) {
    const query = LeaderboardQuerySchema.parse(req.query); // page, limit, validated with Zod
    const leaderboard = await getLeaderboard(query.limit, query.page);
    sendSuccess(res, { items: leaderboard });
  },
};
```

## The response shape

```json
{
  "success": true,
  "data": {
    "items": [
      { "rank": 1, "userId": 3, "email": "ravi@example.com", "acceptedCount": 42 },
      { "rank": 2, "userId": 1, "email": "aman@example.com", "acceptedCount": 30 }
    ]
  }
}
```

## Why this query is a natural caching candidate later

Computing a leaderboard across every user's submissions gets more expensive as the table grows, and the ranking rarely needs to be accurate to the exact second. This is exactly the scenario [`04-scalability.md`](../0%20Concepts/04-scalability.md) describes for caching: "read-often, change-rarely" data, expensive to compute, cheap to serve from a cache. Phase 6 of the roadmap names the leaderboard directly as "the perfect first excuse" to add Redis caching, this file's query is the one you would cache at that point, no rewrite of the underlying logic needed later, just a cache layer added in front of it.

## Key takeaways

- Aggregation (counting, grouping, ranking) belongs in the database query, never done by fetching everything and computing in JavaScript afterward.
- `groupBy` with `_count` and `orderBy` on the count produces a ranked leaderboard directly, `skip`/`take` paginate it exactly like any other query.
- A second, targeted query (`select`ing only needed fields) joins in display data for the grouped ids, keeping both queries cheap.
- This exact query is the natural candidate for Redis caching once you reach Phase 6, the roadmap calls this out by name.
