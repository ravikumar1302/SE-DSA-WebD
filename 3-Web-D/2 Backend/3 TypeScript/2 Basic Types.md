# Basic Types

## Primitive types

```ts
let name: string = "Ravi";
let age: number = 25;
let isActive: boolean = true;
let nothing: null = null;
let notSet: undefined = undefined;
```

TypeScript's `number` type covers integers and decimals both, there is no separate `int` or `float` like in Java or C++.

## Type inference

You do not have to write the type every time. TypeScript can often figure it out from the assigned value.

```ts
let name = "Ravi";     // inferred as string
let age = 25;          // inferred as number
```

**Rule of thumb**: let TypeScript infer types for simple local variables. Write explicit types for function parameters, return values and anywhere the type is not obvious from context.

## Arrays

```ts
let ids: number[] = [1, 2, 3];
let names: string[] = ["Ravi", "Aman"];

// alternate syntax, same meaning
let scores: Array<number> = [10, 20, 30];
```

## Tuples

A tuple is a fixed-length array where each position has a specific, known type.

```ts
let user: [string, number] = ["Ravi", 25];
// user[0] is always string, user[1] is always number
```

Plain arrays do not enforce position or length. Tuples do. Useful for things like `[status, data]` pairs or coordinate pairs `[x, y]`.

## Object types

```ts
let user: { name: string; age: number } = {
  name: "Ravi",
  age: 25,
};
```

Writing the object shape inline like this works, but gets repetitive. The next file covers `interface` and `type`, which name a shape so you can reuse it.

## Enums

An enum is a set of named constant values.

```ts
enum Status {
  Pending,
  Active,
  Closed,
}

let current: Status = Status.Active;
```

By default, enum values are numbers (`Pending = 0`, `Active = 1`, `Closed = 2`). You can also use strings, which are safer to log and debug:

```ts
enum Status {
  Pending = "PENDING",
  Active = "ACTIVE",
  Closed = "CLOSED",
}
```

📌 In backend work, string enums are common for things like order status, user roles, submission status (matches the `status` field in the AlgoRift `Submission` model from the roadmap).

## `any`, `unknown`, `never`, `void`

| Type | Meaning | When to use |
|---|---|---|
| `any` | Turns off type checking for that value completely | Avoid. It defeats the point of TypeScript. Only as a last resort. |
| `unknown` | Value could be anything, but you must check its type before using it | Safer alternative to `any`, use for values from outside your code (API responses, user input) |
| `never` | A value that can never happen, function never returns normally | Rare, used for functions that always throw or loop forever |
| `void` | Function returns nothing useful | Common for functions that only perform a side effect, like logging |

```ts
function logMessage(message: string): void {
  console.log(message);
  // no return statement needed
}

function crash(): never {
  throw new Error("something went wrong");
}
```

### Why `unknown` is better than `any`

```ts
function handleInput(data: any) {
  data.toUpperCase();   // no error here, even though data might be a number, crashes at runtime
}

function handleInput(data: unknown) {
  data.toUpperCase();   // TypeScript error: 'data' is of type 'unknown'
  if (typeof data === "string") {
    data.toUpperCase(); // fine now, TypeScript knows it is a string here
  }
}
```

`unknown` forces you to check the type before using it. This is exactly the kind of check you want when data comes from a request body, since you cannot trust it blindly (see the "validation as boundary" idea in [`07-security.md`](../0%20Concepts/07-security.md)).

## Union types

A value can be one of several types.

```ts
let id: string | number;
id = "abc123";  // valid
id = 42;        // also valid
id = true;      // error
```

Common in backend code for things like a status code that could be a specific set of numbers, or a result that is either data or an error.

```ts
type ApiResult = { success: true; data: string } | { success: false; error: string };
```

## Intersection types

Combines multiple types into one, must satisfy all of them.

```ts
type WithId = { id: number };
type WithName = { name: string };

type Entity = WithId & WithName;
// Entity must have both id and name
```

## Literal types

A type that is one exact value, not just "a string" but this exact string.

```ts
let direction: "up" | "down" | "left" | "right";
direction = "up";     // valid
direction = "sideways"; // error
```

This is how you get an enum-like restriction without a full `enum`. Useful for things like HTTP methods:

```ts
type HttpMethod = "GET" | "POST" | "PUT" | "PATCH" | "DELETE";
```

## Type narrowing

TypeScript can narrow a broader type down to a more specific one based on runtime checks.

```ts
function printLength(value: string | number) {
  if (typeof value === "string") {
    console.log(value.length);  // TypeScript knows value is string here
  } else {
    console.log(value.toFixed(2)); // TypeScript knows value is number here
  }
}
```

This is the main technique used with `unknown` and union types. Common narrowing checks:

| Check | Used for |
|---|---|
| `typeof value === "string"` | Primitives (string, number, boolean) |
| `Array.isArray(value)` | Arrays |
| `value instanceof SomeClass` | Class instances |
| `"key" in value` | Checking a property exists on an object |

## Key takeaways

- Let TypeScript infer simple variable types, be explicit for function signatures.
- Prefer `unknown` over `any` for untrusted data, then narrow it before use.
- Union types and literal types model "one of these specific options" cleanly, common for status fields and HTTP methods.
- Type narrowing lets you safely work with values after checking what they actually are.
