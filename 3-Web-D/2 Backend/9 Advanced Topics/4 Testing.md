# Testing

📌 Lighter reference notes here specifically because [`08-testing.md`](../0%20Concepts/08-testing.md) already covers the theory (the testing pyramid, unit vs integration vs e2e, TDD, mocking) in real depth. This file is the practical version, applied directly to the Express + Prisma stack you actually built.

## The testing pyramid, quick recap

```
        /\
       /e2e\        few, slow, test the whole real system
      /------\
     /integr. \     some, test pieces working together (e.g. a route + real DB)
    /----------\
   /   unit      \  many, fast, test one function in isolation
  /----------------\
```

| | Unit | Integration | E2E |
|---|---|---|---|
| Tests | One function, in isolation | Several pieces together (route + real DB) | The whole real system, as a user would use it |
| Speed | Fast (milliseconds) | Slower (a real database call) | Slowest |
| Count in a healthy suite | Many | Some | Few |
| Needs a database or server | No | Yes, a test database | Yes, the full running app |
| Catches | Broken logic in one function | Pieces not wiring together correctly | Real user-facing breakage across the whole flow |

## Why the service layer split (Phase 1) pays off here

Services (`problemService`, `authService`, and so on) never import Express, never touch `req`/`res`. That was the whole point of the layering built back in [Folder Structure: Routes, Controllers, Services](../4%20Express%20Fundamentals/6%20Folder%20Structure%20-%20Routes%20Controllers%20Services.md), it means service functions are plain, callable functions, trivially testable without spinning up an HTTP server at all.

```ts
// this needs nothing Express-related to test
describe("problemService.create", () => {
  it("creates a problem with the given data", async () => {
    const problem = await problemService.create({ title: "Two Sum", difficulty: "easy" });
    expect(problem.title).toBe("Two Sum");
  });
});
```

## Setting up a testing tool

```bash
npm install -D vitest
```

Vitest is a common modern choice for a TypeScript project, fast, and its API closely matches Jest, so almost any Jest example you find online transfers directly.

```json
{ "scripts": { "test": "vitest" } }
```

## Unit test example: pure logic, no database

```ts
function calculateRank(acceptedCount: number, allCounts: number[]): number {
  return allCounts.filter((c) => c > acceptedCount).length + 1;
}

describe("calculateRank", () => {
  it("returns 1 for the highest count", () => {
    expect(calculateRank(50, [50, 30, 10])).toBe(1);
  });

  it("returns correct rank for a middle value", () => {
    expect(calculateRank(30, [50, 30, 10])).toBe(2);
  });
});
```

Fast, no setup, no database, exactly the "many, fast, isolated" layer of the pyramid.

## Integration test example: a real database, a test route

```ts
describe("POST /problems", () => {
  it("creates a problem and returns 201", async () => {
    const res = await request(app)
      .post("/problems")
      .send({ title: "Two Sum", description: "...", difficulty: "easy" });

    expect(res.status).toBe(201);
    expect(res.body.data.title).toBe("Two Sum");
  });
});
```

`supertest` (paired with your test runner) sends real HTTP requests to your Express app in memory, without needing an actual running server or port. This tests the routes/controllers/services layers together, closer to how a real client experiences the API.

⚠️ **Pitfall**: running integration tests against your real production or development database is risky, tests should use a separate test database (a second Neon branch works well here), so running the test suite never touches real data.

## Mocking, briefly

[`08-testing.md`](../0%20Concepts/08-testing.md) covers this conceptually. In this stack, mocking most often means replacing Prisma calls with fake, controlled responses, so a unit test does not need a real database at all.

```ts
vi.mock("../lib/prisma", () => ({
  prisma: { problem: { findUnique: vi.fn().mockResolvedValue({ id: 1, title: "Two Sum" }) } },
}));
```

## What to actually test first, on a project this size

📌 Matching [`08-testing.md`](../0%20Concepts/08-testing.md)'s own practical priorities: core logic (rank calculation, ownership checks), edge cases (an empty leaderboard, a missing problem) and anything that has broken once before. Do not aim for 100% coverage on a learning project, aim for confidence on the parts most likely to silently break.

## Key takeaways

- The routes/controllers/services split from Phase 1 is what makes services trivially unit-testable, no Express or database required for pure logic.
- Integration tests (via `supertest`) exercise a real route through your actual Express app, against a separate test database, never your real one.
- Mocking Prisma calls lets you unit test logic without a real database at all, reserved for cases where a real query would be slow or unnecessary for what you are actually testing.
- Bolt testing on once the app is stable (the roadmap's own framing), prioritize core logic and past bugs over chasing full coverage.
