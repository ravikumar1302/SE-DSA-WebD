# Reading Stack Traces and Async Errors

Async code changes how errors travel. A synchronous error propagates up the call stack immediately, an async error can surface somewhere that looks unrelated to where it actually happened, or not surface at all if nothing is listening for it.

## A backend stack trace, read the same way as frontend

```
TypeError: Cannot read properties of null (reading 'email')
    at problemService.create (problemService.ts:14:23)
    at async ProblemController.create (problemController.ts:22:9)
    at async Layer.handle (express/lib/router/layer.js:95:5)
```

Same rule as the [frontend reading-errors file](../../1%20Frontend/7%20Debugging/4%20Reading%20Errors%20and%20Stack%20Traces.md): read top to bottom, the first line naming your own file is usually where the real problem is, everything below naming `express/lib/...` is library internals, rarely where the actual bug lives.

## The unhandled promise rejection

```ts
async function processSubmission(id: number) {
  const submission = await prisma.submission.findUnique({ where: { id } });
  return submission.result; // throws if submission is null, and nothing catches it
}

processSubmission(999); // called without await, without .catch
```

If a rejected promise has nothing waiting on it, Node prints an `UnhandledPromiseRejection` warning, and in modern Node versions can crash the process entirely. This is a distinct failure mode from a normal thrown error, the stack trace can be less precise, and the process can die well after the actual mistake, whenever this promise happens to settle.

```
Normal thrown error:
throw happens -> caught by try/catch, or crashes immediately, right here

Unhandled rejection:
promise rejects -> nothing was awaiting or .catch-ing it -> a warning fires
                    later, disconnected from where the mistake actually was
```

📌 **Rule of thumb**: every `async` function call should either be `await`-ed inside a `try/catch`, wrapped by something like `asyncHandler` (covered in [Centralized Error Handling](../4%20Express%20Fundamentals/4%20Centralized%20Error%20Handling.md)), or explicitly `.catch()`-ed. A bare unawaited async call with no error handling is where unhandled rejections come from.

## Where `try/catch` actually needs to sit

A `try/catch` only catches errors thrown inside its own block, including from an `await`ed call inside it, not errors from a callback registered elsewhere or a promise created but not awaited within it.

```ts
try {
  setTimeout(() => {
    throw new Error("this escapes the try block entirely");
  }, 100);
} catch (err) {
  // never runs, the throw happens later, outside this synchronous try block
}
```

The `try` block finished running (it just scheduled a timeout) before the thrown error even happens. This surprises developers coming from purely synchronous code, where a `try/catch` wrapping a function call also implicitly wraps everything that function does, synchronously.

## Async stack traces losing context

Older JavaScript engines used to produce a stack trace that stopped at the `await`, with no trace of what called the async function in the first place. Modern Node (and Chrome's V8 engine generally) preserves this with "async stack traces," shown as `at async functionName` lines, as in the example at the top of this file. If a stack trace looks unusually short or seems to be missing the caller, checking the Node version, and whether `--async-stack-traces` style behavior is enabled, is worth doing before assuming the code itself is the problem.

## A practical debugging habit for async code

Wrap a suspect async chain in explicit logs at each `await`, rather than one log at the end. This shows exactly which step in an async sequence actually failed or returned something unexpected, instead of guessing which of several awaited calls was the culprit.

```ts
async function createSubmission(userId: number, data: SubmissionInput) {
  console.log("step 1: validating");
  const validated = SubmissionSchema.parse(data);

  console.log("step 2: checking problem exists");
  const problem = await prisma.problem.findUnique({ where: { id: validated.problemId } });
  if (!problem) throw new Error("Problem not found");

  console.log("step 3: creating submission");
  return prisma.submission.create({ data: { ...validated, userId } });
}
```

The last log printed before a crash tells you exactly which step to focus on, without needing a debugger at all.

## Key takeaways

- Read a backend stack trace the same way as a frontend one, top to bottom, your own file first, library internals below rarely matter.
- An unhandled promise rejection is a distinct failure mode, an async call with no `await`, `.catch`, or wrapper, surfacing later and less precisely than a normal thrown error.
- A `try/catch` only catches what happens synchronously inside it, a callback scheduled inside (like `setTimeout`) escapes it entirely.
- Logging at each step of an async chain pinpoints exactly which awaited call failed, without needing a breakpoint.
