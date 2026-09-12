# Debugging, Backend Edition

The general debugging process from [the frontend debugging notes](../../1%20Frontend/7%20Debugging/0%20Intro.md), reproduce, isolate, hypothesize, verify, applies here exactly the same way. This file is about what changes when the code runs on a server instead of in a browser.

## What actually changes

```
Frontend debugging                    Backend debugging
-----------------------------         -----------------------------
Visual feedback: the page             No visual feedback: a request
looks wrong, click around             either succeeds, fails or
to explore                            hangs, nothing to look at
DevTools attached to the page         A terminal, logs or an
automatically                         attached debugger you set up
The user is the browser tab           The "user" can be your own
in front of you                       frontend, curl, Postman or a
                                       real client you cannot see
```

The biggest shift for someone coming from frontend debugging: there is no page to stare at. A backend bug shows up as a wrong response, a slow response, a crash or nothing at all, silence, and the only way to see what happened is by reading logs, attaching a debugger or making requests deliberately to observe behavior.

## The four-step loop, applied to a backend bug

1. **Reproduce**: find the exact request (method, URL, body, headers) that triggers the bug, ideally as a `curl` command or a saved request, so it can be fired the same way every time.
2. **Isolate**: is it the route, the middleware, the service logic or the database call. Comment out or bypass pieces the same way frontend debugging comments out components.
3. **Hypothesize**: a specific guess, "the token is expired," not "auth is broken."
4. **Verify**: a breakpoint, a log, or a smaller test request that confirms or rejects the guess.

## Where the tools differ

| Frontend tool | Backend equivalent |
|---|---|
| Browser DevTools breakpoints | Node's own debugger, file 1 |
| The Network tab | `curl`/Postman plus server-side request logging, file 3 and 5 |
| React DevTools | No direct equivalent, service-layer logic is plain functions, testable directly |
| Console in the browser | The terminal running your server, plus a real logger, file 4 |
| A hydration warning in the console | A stack trace in the terminal running the process |

## Where this folder is going

The files ahead cover Node's own debugger and breakpoints, reading Express requests and middleware order, async stack traces, structured logging, Prisma-specific query debugging, auth and JWT debugging, debugging once deployed with no attached debugger, and basic performance debugging. For symptom-by-symptom lookup ("this exact error, what do I do"), the [Troubleshooting Index](../Troubleshooting%20Index.md) is the faster reference, this folder is for building the underlying skill, not for looking up one specific fix.

## Key takeaways

- The same four-step loop applies, reproduce, isolate, hypothesize, verify, the tools available at each step are what differ.
- Without a visible page, logs and a real debugger attached to the Node process replace the browser's DevTools.
- A reliably repeatable request (a saved `curl` command or Postman request) is the backend equivalent of "reproduce the bug."
