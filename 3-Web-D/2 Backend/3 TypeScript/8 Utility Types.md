# Utility Types

TypeScript ships a set of built-in generic types that transform an existing type into a new one. They save you from writing near-duplicate interfaces by hand. All of them are used constantly in real backend code, especially around database models and request/response shapes.

## Starting type used in examples

```ts
interface User {
  id: number;
  name: string;
  email: string;
  password: string;
}
```

## `Partial<T>`

Makes every property optional.

```ts
type UpdateUserInput = Partial<User>;

const update: UpdateUserInput = { name: "New Name" }; // valid, other fields omitted
```

📌 Common use: an update/PATCH endpoint, where the caller may send only the fields they want to change.

## `Required<T>`

Opposite of `Partial`, makes every property required, even ones that were originally optional.

```ts
interface Draft {
  title?: string;
  body?: string;
}

type PublishedPost = Required<Draft>;
// both title and body are now required
```

## `Readonly<T>`

Makes every property readonly, cannot be reassigned after creation.

```ts
const user: Readonly<User> = {
  id: 1,
  name: "Ravi",
  email: "ravi@example.com",
  password: "hashed",
};

user.name = "New Name"; // error, readonly
```

## `Pick<T, Keys>`

Builds a new type using only the listed properties.

```ts
type UserPreview = Pick<User, "id" | "name">;

const preview: UserPreview = { id: 1, name: "Ravi" };
// email and password are not part of this type
```

📌 Common use: a public-facing version of a model that hides sensitive fields by only picking the safe ones.

## `Omit<T, Keys>`

Opposite of `Pick`, builds a new type excluding the listed properties.

```ts
type PublicUser = Omit<User, "password">;

const publicUser: PublicUser = {
  id: 1,
  name: "Ravi",
  email: "ravi@example.com",
};
// password is not allowed here
```

`Omit` is the one you will use most often in a real backend. Never send a `password` field back in an API response, `Omit<User, "password">` enforces that at the type level, so it becomes a compile error if you accidentally include it.

## `Pick` vs `Omit`

| | `Pick<T, Keys>` | `Omit<T, Keys>` |
|---|---|---|
| Keeps | Only the listed keys | Everything except the listed keys |
| Best for | A small subset (2 to 3 fields) | A large type minus a few sensitive/internal fields |

## `Record<Keys, ValueType>`

Builds an object type where every key is of type `Keys` and every value is of type `ValueType`.

```ts
type RoleLabels = Record<"admin" | "editor" | "viewer", string>;

const labels: RoleLabels = {
  admin: "Administrator",
  editor: "Editor",
  viewer: "Viewer",
};
```

📌 Common use: lookup tables, caching by id, grouping data by a category.

```ts
type SubmissionsByStatus = Record<"pending" | "accepted" | "rejected", Submission[]>;
```

## `Exclude<T, U>` and `Extract<T, U>`

Work on union types, not object shapes.

```ts
type Status = "pending" | "active" | "closed" | "archived";

type OpenStatus = Exclude<Status, "closed" | "archived">;
// "pending" | "active"

type ClosedStatus = Extract<Status, "closed" | "archived">;
// "closed" | "archived"
```

`Exclude` removes members from a union, `Extract` keeps only the matching members.

## Combining utility types

They stack together naturally.

```ts
type UpdateUserInput = Partial<Omit<User, "id" | "password">>;
// every field optional, except id and password are not allowed at all
```

This single line describes "an object where the caller may update name and/or email, but never the id or password", exactly the kind of type you write for a `PATCH /users/:id` request body in Phase 4 of the roadmap.

## Summary table

| Utility type | What it does | Typical backend use |
|---|---|---|
| `Partial<T>` | All fields optional | Update/PATCH request bodies |
| `Required<T>` | All fields required | Enforcing a "fully filled in" version of a draft type |
| `Readonly<T>` | All fields read-only | Config objects, values that must not mutate |
| `Pick<T, K>` | Keep only listed fields | Small preview/summary objects |
| `Omit<T, K>` | Remove listed fields | Hiding sensitive fields like passwords from responses |
| `Record<K, V>` | Build a lookup object type | Grouping data by category, caching by key |
| `Exclude<T, U>` | Remove members from a union | Narrowing down a status/category union |
| `Extract<T, U>` | Keep only matching union members | Filtering a union down to related values |

## Key takeaways

- Utility types build new types from existing ones, avoiding duplicate interface definitions.
- `Omit<T, "password">` is the standard way to model a safe, public version of a user model.
- `Partial` fits PATCH endpoints, `Pick`/`Omit` fit response shaping, `Record` fits lookup tables.
- These combine with each other, so you rarely need to write a request/response type completely from scratch.
