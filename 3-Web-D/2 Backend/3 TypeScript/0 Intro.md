# TypeScript - Introduction

## What is TypeScript

TypeScript is JavaScript with types added on top. It is not a new language that replaces JavaScript. Every valid JavaScript file is also valid TypeScript. TypeScript just lets you describe the *shape* of your data (what type a variable, function parameter or return value should be) and checks that shape before your code runs.

Browsers and Node.js cannot run TypeScript directly. TypeScript code is **compiled (transpiled)** into plain JavaScript first, then that JavaScript runs normally.

```
Your .ts file  --->  TypeScript Compiler (tsc)  --->  plain .js file  --->  runs in Node/browser
```

## Why it exists

JavaScript is dynamically typed. A variable can hold a string, then later hold a number, and JavaScript will not stop you.

```js
let user = "Ravi";
user = 42;        // JavaScript allows this silently
```

This flexibility causes real bugs in larger codebases:

- You call a function with the wrong argument type and only find out at runtime, maybe in production.
- You rename a property in one file and forget to update it in ten other files.
- Your editor cannot reliably autocomplete because it does not know what shape an object has.

TypeScript catches these problems **while you write code**, not after you run it.

```ts
let user: string = "Ravi";
user = 42;   // Error caught immediately: Type 'number' is not assignable to type 'string'
```

## How it fits into a backend project

In the roadmap, Phase 0 sets up a Node project with TypeScript from day one. The compiler checks your code as you write it (through your editor) and again when you build for production. During development you will use a tool called `tsx` to run `.ts` files directly without a separate compile step, so the workflow feels the same as writing plain JavaScript.

## JavaScript vs TypeScript

| | JavaScript | TypeScript |
|---|---|---|
| Type checking | None (dynamic, checked at runtime) | Static (checked before running) |
| Runs directly in Node/browser | Yes | No, must be compiled to JS first |
| Catches typos in property names | No | Yes, usually |
| Autocomplete quality in editors | Limited | Strong, because types describe the shape |
| Learning curve | Lower | Slightly higher, worth it for real projects |
| File extension | `.js` | `.ts` (`.tsx` for React/JSX files) |

## Should you use it for everything

Not always. A 20 line script does not need TypeScript. But any backend API that will grow, that other people (or future you) will maintain and that handles real data, benefits a lot from it. This is why the roadmap locks it in from Phase 0.

## Key takeaways

- TypeScript adds types to JavaScript and compiles down to plain JavaScript.
- It catches type mistakes at write time instead of at runtime.
- Your React experience already primed you for this, since React with TypeScript works the same way.
- Next file: project setup, `tsconfig.json` and running TypeScript with `tsx`.
