# Practice: TypeScript

Work through these in order. Each one is small on purpose, the goal is fluency with the syntax before Express arrives, not building anything real yet.

---

### 1. Set up a strict project from scratch

Create a fresh folder, initialize it, install TypeScript and `tsx`, and get a `.ts` file running with `strict: true`.

**Hint**: `npm init -y`, then the dev dependencies, then `npx tsc --init`.

**Done when**: saving the file auto-reloads and prints to the terminal, and `tsconfig.json` has `strict: true`.

---

### 2. Type an object shape two ways

Write the same `User` shape (id, email, optional nickname, readonly createdAt) once as an `interface` and once as a `type`.

**Hint**: `?` for optional, `readonly` for the field that must not change.

**Done when**: both compile, and reassigning `createdAt` produces an error in both.

---

### 3. Replace every `any` in this snippet

```ts
function getFirstItem(items: any): any {
  return items[0];
}

function formatUser(user: any) {
  return user.name.toUpperCase();
}
```

**Hint**: the first one wants a generic, the second wants a real shape.

**Done when**: calling `getFirstItem([1, 2, 3])` returns something typed `number`, and passing a user without a `name` is a compile error.

---

### 4. Narrow an unknown value

Write a function that takes `unknown` and returns its length if it is a string, its size if it is an array and `0` otherwise.

**Hint**: `typeof value === "string"` and `Array.isArray(value)`.

**Done when**: accessing `.length` before narrowing is an error, and after narrowing it is not.

---

### 5. Model a status field two ways

Represent submission status (pending, accepted, rejected) once as a string `enum` and once as a union of literal types.

**Done when**: assigning `"failed"` is rejected by both, and you can say in one sentence why you would pick one over the other.

---

### 6. Write a generic function with a constraint

Write `findById` that takes an array of anything having a numeric `id`, plus an id, and returns the match or `undefined`.

**Hint**: `<T extends { id: number }>`.

**Done when**: it works on an array of problems and an array of users without changes, and rejects an array of plain strings.

---

### 7. Build a response type with generics

Define `ApiResponse<T>` as either `{ success: true, data: T }` or `{ success: false, error: string }`.

**Done when**: after checking `if (response.success)`, TypeScript lets you access `.data` and blocks `.error`.

---

### 8. Type an async function correctly

Write a function that fetches a user by id and returns it, with an explicit return type. Then write one that only logs and returns nothing.

**Hint**: `Promise<User>` and `Promise<void>`.

**Done when**: forgetting `await` at the call site produces a visible type mismatch rather than silently passing.

---

### 9. Derive three types from one

Starting from a `User` interface (id, email, password, name), produce:

- a type safe to send in an API response, with no password
- a type for a PATCH body, where every field is optional and id cannot be changed
- a type with only id and name

**Hint**: `Omit`, `Partial` and `Pick`, which combine.

**Done when**: all three come from `User` alone, with no field names retyped by hand.

---

### 10. Handle an error correctly

Write a `try/catch` where the catch block logs `error.message` safely under strict mode.

**Done when**: it compiles without `as any`, and still handles a non-`Error` throw without crashing.

---

## Stretch

Take any file from a past frontend project, add types to one untyped function per file, and note which ones were harder than expected. The hard ones usually reveal a shape you never fully decided on.
