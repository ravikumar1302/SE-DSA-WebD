# Node.js Debugging Tools

Node has its own real debugger, not a substitute for `console.log`, a full breakpoint-based debugger, the same kind of tool the browser gives you for frontend code, just reached differently.

## The `debugger` statement, same idea as the frontend

```js
app.post("/problems", (req, res) => {
  debugger; // execution pauses here, if the process was started with --inspect
  const problem = problemService.create(req.body);
  res.status(201).json(problem);
});
```

On its own this does nothing, Node needs to be told to actually listen for it.

## Starting Node with the inspector

```bash
node --inspect index.js
```

This starts the server as normal, but also opens a debugging port. Open `chrome://inspect` in Chrome, and the running Node process appears under "Remote Target," clicking "inspect" opens a DevTools window, the exact same Sources panel used for frontend debugging, attached to your server code instead of a web page.

```bash
node --inspect-brk index.js
```

`--inspect-brk` pauses immediately on the very first line, useful when you need to set breakpoints before any code (including startup code) runs, rather than racing to open DevTools before the server finishes starting.

With `tsx` or `ts-node` (a TypeScript project, as covered in the TypeScript notes), the same flag works: `node --inspect -r tsx/cjs index.ts`, or check the tool's own docs for the exact inspector flag, since flags shift between versions.

## The VS Code debugger, the easier daily path

VS Code has a built-in debugger that does not need the `--inspect` flag or Chrome at all. A minimal `.vscode/launch.json`:

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "type": "node",
      "request": "launch",
      "name": "Debug Server",
      "runtimeExecutable": "npx",
      "runtimeArgs": ["tsx", "index.ts"],
      "console": "integratedTerminal"
    }
  ]
}
```

Set breakpoints by clicking the line-number gutter directly in the editor, press F5 to launch, the server starts under the debugger automatically. This is usually faster day to day than the Chrome route, since there is no separate window to manage, breakpoints live right in the file you are already editing.

## Stepping through backend code

The controls are identical to the frontend Sources panel: step over, step into, step out, resume, watch expressions, the call stack. The one backend-specific habit worth building: step over `await` calls into library code (Prisma, Express internals) by default, step into them only when you specifically suspect the library call itself, not your own code around it, is where the bug lives.

## Conditional breakpoints for one specific request

The same conditional-breakpoint idea from frontend debugging applies directly, useful when a route handles many requests and only one particular one misbehaves.

```
req.body.email === "broken@example.com"
```

Right-click the line (VS Code) or the line number (Chrome DevTools attached to Node) to add this condition, execution only pauses for the matching request, not every single one hitting that route.

## `console.log` still has its place

A breakpoint pauses the whole process, every other request waiting on that server also stalls until you resume. For a value that needs watching across many requests over time, without freezing the server for real traffic, a well-placed log (or the structured logging covered in file 4) is often the better tool. Breakpoints and logs solve different shapes of problem, the same distinction covered on the frontend side.

## Key takeaways

- `node --inspect` opens a real debugging port, Chrome DevTools can attach to a running Node process the same way it attaches to a web page.
- The VS Code debugger skips the separate Chrome window entirely, breakpoints live directly in the editor, usually the faster daily choice.
- A breakpoint pauses the entire server process, including unrelated requests, worth remembering before setting one on a live shared server.
- Step over library calls by default, step into them only when specifically suspected.
