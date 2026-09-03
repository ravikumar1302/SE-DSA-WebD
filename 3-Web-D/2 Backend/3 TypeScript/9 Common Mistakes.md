# Common Mistakes

A list of the mistakes beginners make most often with TypeScript, and why each one causes real problems later.

## 1. Reaching for `any` too quickly

```ts
function processData(data: any) {
  return data.value.toUpperCase();
}
```

This compiles fine, no matter what `data` actually is, and crashes at runtime the moment `data` does not have a `.value` property or `.value` is not a string. `any` silences TypeScript completely for that value, and it can silently spread: anything derived from an `any` value also becomes `any`.

**Fix**: use `unknown` and narrow it, or write out the real expected shape.

```ts
function processData(data: { value: string }) {
  return data.value.toUpperCase();
}
```

## 2. Turning off `strict` mode

```json
{ "compilerOptions": { "strict": false } }
```

This feels like it removes annoying errors, but those errors were catching real bugs. Without `strict`, `null` and `undefined` are allowed almost anywhere, and untyped parameters silently become `any`.

**Fix**: keep `strict: true` from the very first commit. It is much harder to turn on later, once a codebase has grown used to being loose.

## 3. Ignoring null and undefined

```ts
function getUserName(user: User | null) {
  return user.name; // error under strict mode: user might be null
}
```

**Fix**: check before using.

```ts
function getUserName(user: User | null) {
  if (!user) return "Unknown";
  return user.name;
}
```

## 4. Overusing type assertions (`as`)

```ts
const data = response as User; // "trust me, this is a User"
```

`as` tells TypeScript to stop checking and just believe you. If you are wrong, TypeScript will not catch it, and the mistake surfaces later as a runtime crash somewhere else, far from where the bad assertion was made.

**Fix**: only use `as` when you are certain and have no better option (some DOM APIs genuinely need it). For data coming from outside your code (API responses, database results, user input), validate it properly instead, using a library like Zod, covered in Phase 3 of the roadmap.

```ts
const data = UserSchema.parse(response); // validated, not just asserted
```

## 5. Not typing function return values on public/shared functions

```ts
function calculateTotal(items: Item[]) {
  // ... 40 lines later
  return items.length > 0 ? total : undefined;
}
```

If the return type is only inferred, a future edit that accidentally changes what gets returned will not be caught, since there is no explicit contract to check against.

**Fix**: write the return type explicitly for any function used across multiple files.

```ts
function calculateTotal(items: Item[]): number | undefined {
  // ...
}
```

## 6. Confusing `interface` and `type` overuse debates

Beginners sometimes spend real time deciding between `interface` and `type` for every single case. For plain object shapes, it rarely matters. Pick one convention (this repo's guide: `interface` for objects, `type` for unions/functions) and move on, consistency matters more than the specific choice here.

## 7. Not knowing the difference between compile-time and runtime types

```ts
interface User {
  id: number;
  name: string;
}

function processUser(user: User) {
  console.log(user);
}

const raw = JSON.parse('{"id": "not-a-number", "name": 123}');
processUser(raw); // no compile error, TypeScript trusts you here
```

TypeScript types disappear completely once compiled to JavaScript. They exist only to check your code while you write it, they do not exist at runtime and cannot validate data arriving from outside your program (an API request body, a database row, a `JSON.parse` result).

**Fix**: at every boundary where data enters your system from outside, validate it at runtime too. This is exactly why Phase 3 of the roadmap introduces Zod: it validates data at runtime and gives you a matching TypeScript type at the same time.

## 8. Fighting the compiler instead of fixing the real issue

When a type error seems confusing or wrong, the instinct is often to silence it (`as any`, `// @ts-ignore`) rather than understand it. Almost always, the error is pointing at a real gap in your code's logic, for example a case you forgot to handle, or a value that genuinely can be `null` and you had not accounted for it.

**Fix**: read the error message fully before working around it. TypeScript error messages usually name the exact mismatched types, which is often enough to spot the real bug.

## Summary table

| Mistake | Why it hurts | Fix |
|---|---|---|
| Overusing `any` | Silently disables type checking, bugs surface at runtime | Use `unknown` and narrow, or write the real shape |
| Disabling `strict` | Removes null/undefined and implicit-any protection | Keep `strict: true` from day one |
| Ignoring null checks | Crashes on `undefined`/`null` access | Check with `if` or optional chaining `?.` before use |
| Overusing `as` | Bypasses checking, no runtime guarantee | Validate untrusted data at runtime (Zod), reserve `as` for rare, certain cases |
| Skipping return types on shared functions | Silent breakage on future edits | Write explicit return types for anything used across files |
| Silencing errors instead of reading them | Hides real bugs instead of fixing them | Read the message, it usually names the actual problem |

## Key takeaways

- Most TypeScript mistakes come from working around the compiler instead of listening to it.
- Types are compile-time only, always validate data at runtime when it enters your system from outside.
- `unknown` plus narrowing beats `any` in almost every situation.
