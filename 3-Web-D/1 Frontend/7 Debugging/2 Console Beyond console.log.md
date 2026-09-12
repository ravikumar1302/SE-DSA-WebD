# Console Beyond console.log

`console.log` works, but scattering it everywhere, then deleting every call once the bug is found, is slow and leaves the console cluttered while debugging. The Console object has several other methods, each suited to a specific kind of check.

## console.table, for arrays and objects

```js
const users = [
  { id: 1, name: "Ravi", role: "admin" },
  { id: 2, name: "Asha", role: "user" },
];

console.table(users);
```

Instead of a wall of nested `{ ... }` text, this prints an actual table, one row per item, one column per field. Reading the shape of an array of objects becomes instant instead of squinting at nested braces.

## console.group, for related logs

```js
console.group("Fetching user data");
console.log("Starting request");
console.log("Got response", response);
console.log("Parsed data", data);
console.groupEnd();
```

Wraps a set of related logs in a collapsible section in the console, instead of them scattering among unrelated logs from other parts of the app.

## console.trace, to answer "who called this"

```js
function updateCart() {
  console.trace("updateCart called from:");
}
```

Prints the full call stack, every function that led to this point, in order. Useful when a function runs and you genuinely do not know from where, a common situation in a large app with many event handlers.

## console.assert, to log only on failure

```js
console.assert(user.id !== undefined, "user.id is missing!", user);
```

Only prints if the first argument is falsy. This means a check can sit in the code permanently, silent when things are fine, loud the moment they are not, instead of a log that fires on every single call whether useful or not.

## console.count, to check how often something runs

```js
function handleClick() {
  console.count("handleClick calls");
}
```

Prints a running count each time it is hit. Directly useful for the "why is this rendering twenty times" class of bug, covered again in file 9.

## console.time, for quick timing

```js
console.time("fetchUsers");
await fetchUsers();
console.timeEnd("fetchUsers");
```

Prints how long the code between the two calls took, in milliseconds. A fast way to confirm "is this actually the slow part" before reaching for the full Performance panel (file 11).

## A quick reference

| Method | Answers |
|---|---|
| `console.table(arr)` | What does this array of objects actually look like |
| `console.group` / `groupEnd` | How do I keep related logs together |
| `console.trace()` | Who called this function |
| `console.assert(cond, msg)` | Log only when something is actually wrong |
| `console.count(label)` | How many times did this run |
| `console.time` / `timeEnd` | How long did this take |

⚠️ **Pitfall**: leaving `console.log` calls in committed code is a common code review complaint, they clutter the console for every future user and developer. Remove debug logs before committing, or use `console.assert` for checks meant to stay permanently.

## Key takeaways

- The Console object has purpose-built methods beyond `console.log`, each answering a specific question faster than a plain log would.
- `console.table` for arrays of objects, `console.trace` for "who called this," `console.count` for "how many times did this run."
- `console.assert` lets a check live in the code permanently without spamming the console when things are fine.
