# GraphQL

📌 Lighter reference notes, matching Phase 7's "know it exists" philosophy. [`06-apis.md`](../0%20Concepts/06-apis.md) covers this alongside REST and gRPC conceptually, this file compares it directly against the REST API you actually built.

## The problem GraphQL addresses

A REST API (everything you built in Phases 1 to 4) exposes fixed endpoints, each returning a fixed shape of data.

```
GET /problems/5
{ "id": 5, "title": "Two Sum", "description": "...", "difficulty": "easy", "createdAt": "..." }
```

If a client only needs the `title`, it still receives every field, over-fetching. If a client needs a problem plus its tags plus its submissions, that might take three separate requests to three different REST endpoints, under-fetching in a single call.

GraphQL solves both: one endpoint, and the client specifies exactly which fields it wants, in one request, however nested.

```
POST /graphql
{
  problem(id: 5) {
    title
    tags { name }
    submissions(status: "accepted") { id, createdAt }
  }
}
```

The response contains exactly `title`, the tag names and matching submissions, nothing more, in one round trip.

## Comparing your actual `GET /problems/:id` route to GraphQL

```
REST (what you built):
GET /problems/5              -> the problem, no tags or submissions
GET /problems/5?include=tags  -> a custom query param, if you built one
GET /problems/5/submissions   -> a separate request entirely

GraphQL (the same data, one request):
query {
  problem(id: 5) {
    title
    tags { name }
    submissions { id, status }
  }
}
```

## REST vs GraphQL, compared

| | REST | GraphQL |
|---|---|---|
| Endpoints | Many, one per resource/action | One, `/graphql` |
| Over-fetching / under-fetching | A real, common problem | Solved, client asks for exactly what it needs |
| HTTP caching (browsers, CDNs cache by URL) | Works naturally, URLs are meaningful | Harder, every request goes to the same URL |
| Learning curve | Lower, matches plain HTTP directly | Higher, its own query language and type system |
| Tooling maturity for this stack (Express + Prisma) | Extremely mature, huge ecosystem | Good, but real added setup (a schema, resolvers) |
| Status code usage | Meaningful (200/404/etc, from your HTTP notes) | Usually always `200`, errors live inside the response body instead |

⚠️ The trap named directly in the roadmap: treating GraphQL as strictly better than REST. It solves over/under-fetching genuinely well, at the cost of HTTP caching, simpler tooling and the meaningful status codes you already built real habits around in Phase 1.

## What a minimal GraphQL setup looks like (for recognition)

```ts
import { ApolloServer } from "@apollo/server";

const typeDefs = `
  type Problem {
    id: ID!
    title: String!
    tags: [Tag!]!
  }
  type Tag { id: ID!, name: String! }
  type Query {
    problem(id: ID!): Problem
  }
`;

const resolvers = {
  Query: {
    problem: (_parent: unknown, args: { id: string }) => {
      return prisma.problem.findUnique({ where: { id: Number(args.id) }, include: { tags: true } });
    },
  },
};
```

A **resolver** is the GraphQL equivalent of a controller, a function that fetches the actual data for one field, called only when a client's query actually asks for that field. Notice `prisma.problem.findUnique` here, exactly the same Prisma call from Phase 2, GraphQL sits on top of the same data layer, it changes the API's outer shape, not your database logic underneath.

## When it would genuinely fit AlgoRift

A frontend making many separate requests to assemble one screen (a problem page needing the problem, its tags and recent submissions together) is the natural trigger. The roadmap's own REST-first choice already avoids this specific pain by designing `include`-based responses (Phase 2) and a consistent envelope (Phase 4) deliberately, exactly the kind of "solve it with REST first" approach that makes GraphQL usually unnecessary at this scale.

## Key takeaways

- GraphQL trades many fixed REST endpoints for one flexible endpoint, letting the client ask for exactly the fields and nested relations it needs in a single request.
- It is a genuine tradeoff, not a strict upgrade, HTTP caching and meaningful status codes (both real strengths of REST) become harder to use naturally with GraphQL.
- A resolver plays the same role as a REST controller, calling the same underlying database logic (Prisma, in AlgoRift's case), GraphQL changes the API's outer shape, not your data layer.
- REST, designed thoughtfully (relations via `include`, a consistent envelope), already avoids most of the over/under-fetching pain GraphQL exists to solve.
