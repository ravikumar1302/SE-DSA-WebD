# Debugging Mindset

The general mindset, binary search debugging, minimal reproduction, rubber duck explaining, knowing when to step away, is covered in full in [the frontend debugging mindset notes](../../1%20Frontend/7%20Debugging/11%20Debugging%20Mindset%20and%20Strategies.md), and applies to backend code exactly as written there. This file is short on purpose, just the backend-specific version of each idea.

## Binary search, applied to a backend bug

`git bisect` works identically here, checking out an older commit and re-running the same request against it narrows down exactly which change introduced a regression, often faster than reading a diff and guessing.

For narrowing down where inside one request a bug lives, the same halving idea from the frontend notes applies to the layers themselves.

```
Bug is somewhere in this request
      |
      v
Does the route/controller layer even get called correctly? -> log and check
      |
      v
Does the service layer return the right thing, tested directly, no HTTP involved?
      |
      v
Does the database query, run directly in Prisma Studio or psql, return the right thing?
```

Testing the service layer directly (a plain function call, no Express involved) is only possible because of the routes/controllers/services split from the Express Fundamentals notes, another place where that earlier architectural choice pays off.

## Minimal reproduction, a backend version

A minimal reproduction for a backend bug is often a single `curl` command, or a tiny standalone script calling the suspect service function directly, stripped of the full request/response cycle, auth and unrelated middleware.

```bash
curl -X POST http://localhost:3000/problems \
  -H "Content-Type: application/json" \
  -d '{"title": "Two Sum", "difficulty": "easy"}'
```

A saved, minimal `curl` command that reliably reproduces the bug is worth more than a long description of "sometimes when I use the app," the same principle as the frontend notes, applied to a request instead of a UI interaction.

## Rubber duck, applied to a data flow

Explaining a request out loud, step by step, request arrives, middleware runs in this order, controller calls this service, service calls Prisma, Prisma sends this query, database returns this, surfaces the same kind of missed assumption the frontend version does, usually at the exact step where the explanation gets vague or hand-wavy.

## Key takeaways

- The mindset itself does not change between frontend and backend, only what gets bisected, reproduced or explained does.
- The routes/controllers/services split makes layer-by-layer isolation possible, testing the service directly without any HTTP involved at all.
- A saved, minimal `curl` command is the backend equivalent of a minimal frontend reproduction, small, exact and repeatable.
