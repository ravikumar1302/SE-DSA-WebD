# Generics

## The problem generics solve

Say you want a function that wraps a value in an array, for any type of value.

```ts
function wrapInArray(value: number): number[] {
  return [value];
}
```

This only works for numbers. Writing a separate version for every type (`wrapInArrayString`, `wrapInArrayBoolean`, ...) does not scale. Using `any` throws away all type safety.

```ts
function wrapInArray(value: any): any[] {
  return [value];
}

wrapInArray("hello")[0].toFixed(2); // no error at compile time, crashes at runtime
```

Generics solve this: write the function once, and let the caller decide the type each time it is used, while TypeScript still checks everything correctly.

| | `any` | `unknown` | `<T>` (generic) |
|---|---|---|---|
| Type checking | None, disabled entirely | Must be narrowed before use | Full, tied to the actual type used |
| The caller's type is preserved | No, becomes `any` everywhere | No, becomes `unknown` | Yes, `T` is exactly what was passed in |
| Safe to use directly | No, defeats TypeScript | No, forces a check first | Yes |
| Right use case | Rare, avoid where possible | Genuinely unknown data (e.g. `catch` blocks) | A function or type that should work the same way across many types |

## Generic functions

```ts
function wrapInArray<T>(value: T): T[] {
  return [value];
}

const numbers = wrapInArray(5);        // T is inferred as number, result: number[]
const words = wrapInArray("hello");    // T is inferred as string, result: string[]

words[0].toFixed(2);  // error, string has no toFixed method
```

`T` is a placeholder for "whatever type is passed in". You could name it anything, `T` is just the common convention (short for "Type"). TypeScript infers `T` automatically from the argument, you rarely need to specify it manually.

```ts
const result = wrapInArray<string>("hello"); // explicit, usually unnecessary
```

## Generic interfaces and types

```ts
interface ApiResponse<T> {
  success: boolean;
  data: T;
}

const userResponse: ApiResponse<User> = {
  success: true,
  data: { id: 1, name: "Ravi", email: "ravi@example.com" },
};

const problemsResponse: ApiResponse<Problem[]> = {
  success: true,
  data: [{ id: 1, title: "Two Sum" }],
};
```

Same `ApiResponse` shape reused for any kind of data, exactly matching the "consistent response envelope" idea from Phase 4 of the roadmap and [`06-apis.md`](../0%20Concepts/06-apis.md).

## Generic constraints

Sometimes you want to accept "any type, but it must have at least this property". The `extends` keyword adds that constraint.

```ts
interface HasId {
  id: number;
}

function findById<T extends HasId>(items: T[], id: number): T | undefined {
  return items.find((item) => item.id === id);
}
```

Without the constraint, TypeScript would not know that `item.id` exists, since `T` could be anything. `extends HasId` says "T can be any type, as long as it has an `id: number` property".

## A backend example: generic Repository

This is the generic pattern behind the Repository pattern from [`02-design-patterns.md`](../0%20Concepts/02-design-patterns.md).

```ts
interface Repository<T> {
  findById(id: number): T | null;
  findAll(): T[];
  save(item: T): T;
}

class ProblemRepository implements Repository<Problem> {
  findById(id: number): Problem | null {
    // real implementation would query the database
    return null;
  }

  findAll(): Problem[] {
    return [];
  }

  save(item: Problem): Problem {
    return item;
  }
}
```

`Repository<T>` defines the shape once. Every specific repository (`ProblemRepository`, `SubmissionRepository`, `TagRepository`) reuses the same contract, just with a different `T`. Prisma, which you will use from Phase 2 onward, generates types like this for you automatically.

## Multiple type parameters

Generics are not limited to one placeholder.

```ts
function pair<A, B>(first: A, second: B): [A, B] {
  return [first, second];
}

const result = pair("Ravi", 25); // [string, number]
```

## Default generic types

```ts
interface ApiResponse<T = unknown> {
  success: boolean;
  data: T;
}

const response: ApiResponse = { success: true, data: "anything" }; // T defaults to unknown
```

## Key takeaways

- Generics let you write one function or type that works correctly across many concrete types, without giving up type checking.
- `T` is inferred automatically from usage in most cases, you rarely write `<T>` explicitly when calling.
- `extends` adds a constraint, "this type must have at least these properties".
- Prisma's generated types and Express's `Request<Params, ResBody, ReqBody>` type both lean heavily on generics, understanding this file makes those far less mysterious later.
