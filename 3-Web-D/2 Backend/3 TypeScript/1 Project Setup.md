# Project Setup

## Step 1: Initialize the project

```bash
npm init -y
```

This creates a `package.json` file. It tracks your project's dependencies and scripts.

## Step 2: Install TypeScript and dev tools

```bash
npm install -D typescript tsx @types/node
```

| Package | What it does |
|---|---|
| `typescript` | The TypeScript compiler (`tsc`). Type-checks your code and can convert `.ts` to `.js`. |
| `tsx` | Runs `.ts` files directly, without a separate build step. Used only in development. |
| `@types/node` | Type definitions for Node's built-in modules (`fs`, `http`, `path`, etc). Node itself is written in JS, so these types are added separately. |

These go in `devDependencies` (the `-D` flag) because they are only needed while developing, not when your compiled app runs in production.

## Step 3: Create `tsconfig.json`

```bash
npx tsc --init
```

This generates a config file that controls how TypeScript checks and compiles your code. A minimal, sensible backend config:

```json
{
  "compilerOptions": {
    "target": "ES2022",
    "module": "NodeNext",
    "moduleResolution": "NodeNext",
    "outDir": "dist",
    "rootDir": "src",
    "strict": true,
    "esModuleInterop": true,
    "skipLibCheck": true,
    "forceConsistentCasingInFileNames": true
  },
  "include": ["src/**/*"]
}
```

### Important options explained

| Option | Meaning | Why it matters |
|---|---|---|
| `target` | Which JS version to compile down to | `ES2022` works on modern Node versions |
| `module` / `moduleResolution` | How imports/exports are resolved | `NodeNext` matches how Node actually loads modules |
| `outDir` | Where compiled `.js` files go | Keeps compiled output separate from source |
| `rootDir` | Where your source `.ts` files live | Usually `src` |
| `strict` | Turns on all strict type checking rules | See below, always keep this `true` |
| `esModuleInterop` | Allows `import x from "y"` style imports to work smoothly | Avoids import syntax headaches |
| `skipLibCheck` | Skips type checking inside `node_modules` | Speeds up compilation, library types are not your concern |

### Why `strict: true` matters

`strict` bundles several checks together, the most important being:

- `strictNullChecks`: `null` and `undefined` are not silently allowed everywhere. You must handle them on purpose.
- `noImplicitAny`: every variable must have a known type, either written or inferred. No silent fallback to `any` (which turns off type checking for that value).

```ts
// with strict: false, this compiles with no warning
function greet(name) {
  return "Hello " + name;
}

// with strict: true, TypeScript forces you to be explicit
function greet(name: string) {
  return "Hello " + name;
}
```

Skipping `strict` at the start feels easier, but it defeats the purpose of using TypeScript at all. Loose TypeScript teaches bad habits that are hard to unlearn later.

## Step 4: Folder structure

```
project/
├── src/
│   └── index.ts
├── dist/          (generated, compiled JS goes here, do not edit by hand)
├── tsconfig.json
├── package.json
└── .env
```

## Step 5: Scripts in `package.json`

```json
{
  "scripts": {
    "dev": "tsx watch src/index.ts",
    "build": "tsc",
    "start": "node dist/index.js"
  }
}
```

| Script | When to use it |
|---|---|
| `npm run dev` | Local development. `tsx watch` re-runs your app on every save, no manual compile step. |
| `npm run build` | Before deploying. Compiles all `.ts` files in `src/` to `.js` files in `dist/`. |
| `npm start` | Running the compiled app in production. Runs plain Node on plain JS, fast and simple. |

**Rule of thumb**: use `tsx` only in development. In production, always compile first (`build`) then run the compiled JavaScript (`start`). Running `tsx` in production works, but it recompiles on every start and adds unnecessary overhead.

## Step 6: Prove it works

`src/index.ts`:

```ts
import http from "http";

const server = http.createServer((req, res) => {
  if (req.url === "/health") {
    res.writeHead(200, { "Content-Type": "application/json" });
    res.end(JSON.stringify({ status: "ok" }));
    return;
  }
  res.writeHead(404);
  res.end();
});

server.listen(3000, () => {
  console.log("Server running on http://localhost:3000");
});
```

Run it:

```bash
npm run dev
```

Visit `http://localhost:3000/health` in a browser. You should see `{"status":"ok"}`.

This uses Node's raw `http` module on purpose, no Express yet. Seeing the raw request/response cycle once makes it obvious later what Express is actually doing for you underneath.

## Key takeaways

- `tsconfig.json` controls how TypeScript checks your code. Always start with `strict: true`.
- `tsx` is for development speed, compiled JS through `tsc` is for production.
- A `src` → `dist` split keeps source and compiled output cleanly separated.
