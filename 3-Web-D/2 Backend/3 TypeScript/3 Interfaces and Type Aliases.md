# Interfaces and Type Aliases

Both `interface` and `type` let you give a name to a shape, so you do not have to repeat that shape everywhere.

## Interface

```ts
interface User {
  id: number;
  name: string;
  email: string;
}

const user: User = {
  id: 1,
  name: "Ravi",
  email: "ravi@example.com",
};
```

## Type alias

```ts
type User = {
  id: number;
  name: string;
  email: string;
};
```

For plain object shapes like this, `interface` and `type` behave almost identically. The differences show up in less common cases.

## Key differences

| Feature | `interface` | `type` |
|---|---|---|
| Object shapes | Yes | Yes |
| Extending / combining | `extends` keyword | `&` (intersection) |
| Union types (`A \| B`) | No | Yes |
| Primitives, tuples, function types | No | Yes |
| Declaration merging (same name adds fields) | Yes | No, causes an error |
| Typical use | Describing objects, especially ones that classes will implement | Everything else: unions, primitives, function signatures |

### Extending

```ts
interface Animal {
  name: string;
}

interface Dog extends Animal {
  breed: string;
}
```

```ts
type Animal = {
  name: string;
};

type Dog = Animal & {
  breed: string;
};
```

### Declaration merging (interface-only feature)

```ts
interface User {
  id: number;
}

interface User {
  name: string;
}

// User now has both id and name
const user: User = { id: 1, name: "Ravi" };
```

This is rare in your own code, but it is how libraries let you add properties to their existing types (for example, adding a custom field to Express's `Request` type).

### Things only `type` can do

```ts
type ID = string | number;              // union, interface cannot do this
type Point = [number, number];          // tuple
type Callback = (data: string) => void; // function type
```

## Optional properties

```ts
interface User {
  id: number;
  name: string;
  nickname?: string;   // optional, may be undefined
}

const user: User = { id: 1, name: "Ravi" }; // valid, nickname omitted
```

## Readonly properties

```ts
interface User {
  readonly id: number;
  name: string;
}

const user: User = { id: 1, name: "Ravi" };
user.id = 2;   // error, id is readonly
user.name = "Aman"; // fine
```

Useful for values that should never change after creation, like a database primary key.

## Index signatures

Used when you do not know the exact property names ahead of time, but you know the type of the values.

```ts
interface Scores {
  [studentName: string]: number;
}

const scores: Scores = {
  Ravi: 90,
  Aman: 85,
};
```

## Which one should you use

📌 **Rule of thumb**: use `interface` for object shapes, especially ones a class will implement. Use `type` for everything else (unions, function types, tuples or combining several things together). This matches common practice in real backend codebases, including your future Express + Prisma setup, where `interface` describes request bodies and Prisma-generated `type`s describe database models.

## Example: a backend request body

```ts
interface CreateProblemRequest {
  title: string;
  description: string;
  difficulty: "easy" | "medium" | "hard";
  tagIds: number[];
}

function createProblem(body: CreateProblemRequest) {
  // body.title, body.difficulty etc are all type-checked here
}
```

This is exactly the shape of typing you will do constantly once you reach Phase 1 (Express) and Phase 3 (validation with Zod) of the roadmap. Zod schemas can even generate a `type` like this automatically from the validation rules.

## Key takeaways

- `interface` and `type` both name a shape, mostly interchangeable for plain objects.
- `interface` supports extending and merging, `type` supports unions and more flexible combinations.
- Use `?` for optional properties, `readonly` for properties that should not change.
- Default to `interface` for object/request shapes, `type` for everything else.
