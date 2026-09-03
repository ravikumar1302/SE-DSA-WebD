# Async Code

Backend code spends most of its time waiting: waiting for a database query, waiting for a network call, waiting for a file read. TypeScript typing for async code mostly means correctly typing `Promise` values.

## Promises, quick recap

A `Promise` represents a value that is not available yet, but will be at some point (resolved successfully) or will fail (rejected).

```
Promise<T>
   |
   ├── resolves ---> value of type T
   └── rejects  ---> an error
```

## Typing a Promise

```ts
function fetchUser(id: number): Promise<User> {
  return fetch(`/api/users/${id}`).then((res) => res.json());
}
```

`Promise<User>` means "this eventually resolves to a `User`, not a `User` right now". Calling `fetchUser(1)` does not give you a `User` directly, it gives you a `Promise` that will produce one later.

## `async`/`await`

`async` functions always return a `Promise`, even if you write a plain `return` inside them.

```ts
async function fetchUser(id: number): Promise<User> {
  const res = await fetch(`/api/users/${id}`);
  const data: User = await res.json();
  return data;
}
```

`await` pauses execution until the promise resolves, then gives you the resolved value directly (typed as `User` here, not `Promise<User>`). You do not need to write `Promise<User>` as the return type by hand, TypeScript infers it from the `return data` statement, but writing it explicitly documents the function's contract clearly for anyone reading it.

```ts
async function fetchUser(id: number) {
  const res = await fetch(`/api/users/${id}`);
  return res.json(); // inferred return type: Promise<any>, see note below
}
```

⚠️ **Pitfall**: `res.json()` returns `Promise<any>` by default, since `fetch` cannot know the shape of the response body ahead of time. Always tell TypeScript the expected shape yourself.

```ts
const data = (await res.json()) as User;
// or, cleaner: validate with a library like Zod (Phase 3 of the roadmap) instead of trusting the cast
```

## Error handling

```ts
async function fetchUser(id: number): Promise<User> {
  try {
    const res = await fetch(`/api/users/${id}`);
    if (!res.ok) {
      throw new Error(`Request failed with status ${res.status}`);
    }
    return (await res.json()) as User;
  } catch (error) {
    console.error("Failed to fetch user:", error);
    throw error;
  }
}
```

By default, `error` inside a `catch` block is typed `unknown`, not `any` (as of modern TypeScript with `strict` mode). This is deliberate, since a `throw` can technically throw anything, not just an `Error` object.

```ts
try {
  // ...
} catch (error) {
  console.log(error.message); // error, 'error' is of type 'unknown'

  if (error instanceof Error) {
    console.log(error.message); // fine, narrowed to Error
  }
}
```

## Async functions that don't return a value

```ts
async function saveLog(message: string): Promise<void> {
  await writeToFile(message);
}
```

`Promise<void>` means "this is async and eventually finishes, but produces no useful value". Common for functions whose only job is a side effect.

## Running multiple async operations

```ts
async function getDashboardData(userId: number) {
  const [user, submissions] = await Promise.all([
    fetchUser(userId),
    fetchSubmissions(userId),
  ]);
  return { user, submissions };
}
```

`Promise.all` runs both calls at the same time instead of one after another, and `TypeScript` correctly types the returned array as `[User, Submission[]]` based on what each promise resolves to.

| Approach | Behavior | When to use |
|---|---|---|
| `await` one after another | Runs sequentially, each waits for the previous | When one call depends on the result of another |
| `Promise.all([...])` | Runs all at once, waits for all to finish | When calls are independent of each other, faster overall |

## Typing Express route handlers (a preview)

You will meet this properly in Phase 1, but the shape is worth knowing now:

```ts
import { Request, Response } from "express";

async function getProblem(req: Request, res: Response): Promise<void> {
  const id = Number(req.params.id);
  const problem = await problemService.findById(id);
  res.json(problem);
}
```

Note the return type is `Promise<void>`, not `Promise<Problem>`. The function does not return the problem directly, it sends it through `res.json()` as a side effect. This distinction (returning a value vs sending a response) is a common early confusion when typing Express handlers.

## Key takeaways

- `Promise<T>` means "eventually resolves to a value of type T", not "is a T right now".
- `await` unwraps a promise to its resolved value, inside an `async` function only.
- `catch` blocks type their error as `unknown` under `strict` mode, narrow it with `instanceof Error` before using `.message`.
- `Promise.all` runs independent async calls in parallel, and TypeScript infers the correct tuple of result types.
