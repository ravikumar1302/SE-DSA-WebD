# Next.js Specific Debugging

Next.js adds server rendering, file-based routing and a server/client component split on top of React. Each of these introduces its own class of bug that plain React debugging does not prepare you for.

## Hydration errors

Next.js renders a page's HTML on the server first, sends it to the browser, then React "hydrates" it, attaching event handlers and taking over the already-rendered HTML. A hydration error means the HTML React expected to see (based on what it would render right now) did not match what the server actually sent.

```
Server renders:  <p>Logged in as Guest</p>
Browser renders: <p>Logged in as Ravi</p>   (localStorage read after hydration)
                 ^ mismatch, React throws a hydration error
```

Common causes:

- Reading `localStorage`, `window` or anything browser-only during the initial render, the server has none of these, so it renders something different than the browser would.
- Using `Date.now()`, `Math.random()` or any value that differs between server and client render.
- Browser extensions injecting attributes into the HTML before React hydrates (this one is not your code's fault, and Next.js usually warns about it separately).

📌 Fix direction: anything that depends on the browser (`localStorage`, `window`, current time) belongs inside a `useEffect`, which only runs after hydration, on the client, never during the initial server render.

## Server components versus client components

App Router components are server components by default, they run only on the server, never ship their JavaScript to the browser, and cannot use hooks, browser APIs or event handlers. Adding `"use client"` at the top of a file opts it into being a client component instead.

| | Server component (default) | Client component (`"use client"`) |
|---|---|---|
| Runs | Only on the server | On the server once, then again in the browser |
| Can use hooks (`useState`, `useEffect`) | No | Yes |
| Can use browser APIs, event handlers | No | Yes |
| Ships JavaScript to the browser | No | Yes |
| Good for | Static content, data fetching, layout | Interactivity, anything with state |

A common error, `You're importing a component that needs useState. It only works in a Client Component`, means exactly this: a hook was used in a file without `"use client"` at the top. Fix: add the directive, or move the interactive piece into its own small client component and keep the rest server-rendered.

🔗 Background on this split in general terms lives in [`03-architecture.md`](../../2%20Backend/0%20Concepts/03-architecture.md), the serverless section covers where Next.js route handlers fit.

## Debugging server-rendered errors

An error thrown during server rendering shows up in the terminal running `next dev`, not always in the browser console, since that code never ran in the browser at all. When a page fails to render and the browser shows a generic error screen, check the terminal first, the real stack trace is usually sitting there.

## The `next.config.js` and environment variable gotcha

Only environment variables prefixed with `NEXT_PUBLIC_` are available in client components, since anything without that prefix is deliberately kept server-only, to avoid leaking secrets into browser-shipped code.

```
DATABASE_URL=...              -> server only, undefined if read in a client component
NEXT_PUBLIC_API_URL=...       -> available in both server and client components
```

⚠️ **Pitfall**: reading a non-prefixed variable inside a client component silently returns `undefined`, no error, no warning, just a value quietly missing. If a client-side fetch is calling `undefined/api/...`, this is the first thing to check.

## Fast Refresh not updating

Next.js's Fast Refresh (hot reloading) can occasionally get into a broken state, showing stale content or not reflecting a saved change. Before assuming a real bug, a full page reload (not just Fast Refresh) rules out a stuck dev-server state, this is a common false alarm that wastes time debugging code that was already correct.

## Key takeaways

- A hydration error means the server-rendered HTML and the first client render disagreed, usually caused by browser-only values (`localStorage`, `window`, current time) read outside a `useEffect`.
- Hooks, browser APIs and event handlers need `"use client"`, server components cannot use them at all.
- A server-rendering error appears in the terminal running `next dev`, not necessarily the browser console.
- Only `NEXT_PUBLIC_` prefixed environment variables reach client components, others return `undefined` silently.
