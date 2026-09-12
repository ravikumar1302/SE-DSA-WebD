# Reading Errors and Stack Traces

A red error in the console can look intimidating, especially when it points at a minified file full of single-letter variable names. Most of that fear goes away once you know what each part of the message actually means.

## Anatomy of an error

```
TypeError: Cannot read properties of undefined (reading 'name')
    at UserCard (UserCard.jsx:12:23)
    at renderWithHooks (react-dom.development.js:16305:18)
    at mountIndeterminateComponent (react-dom.development.js:20074:13)
```

| Part | Meaning |
|---|---|
| `TypeError` | The error type, see the table below |
| `Cannot read properties of undefined (reading 'name')` | The actual message, here it means some value was `undefined` when `.name` was accessed on it |
| `at UserCard (UserCard.jsx:12:23)` | Your own code, the file, line and column where it happened |
| The lines below it | The call stack, everything that called everything else, in order, oldest at the bottom |

📌 **Read top to bottom, but look for your own file first.** The topmost line is where the error was thrown, but the most useful line is usually the first one that names one of your own files, everything below it is often library internals (React, a bundler) that you did not write and do not need to read closely.

## Common error types

| Error | Usually means |
|---|---|
| `TypeError` | Trying to use a value in a way its type does not support, calling something that is not a function, reading a property of `undefined`/`null` |
| `ReferenceError` | Using a variable that does not exist, or does not exist yet at that point |
| `SyntaxError` | The code itself is not valid JavaScript, a typo, a missing bracket |
| `RangeError` | A value is outside what is allowed, for example an array length set to a negative number |
| `NetworkError` / a failed `fetch` | A request could not complete, covered in file 6 |

## Source maps, why minified code becomes readable

Production JavaScript is minified: variable names shortened, whitespace removed, sometimes bundled into one giant file. Read directly, an error there is nearly useless.

```
Without a source map:
Error at bundle.min.js:1:48213     <- meaningless line number in a huge minified file

With a source map:
Error at UserCard.jsx:12:23        <- your actual original file and line
```

A source map is a separate file that maps positions in the minified code back to the original source. Most modern build tools (Vite, Next.js, Create React App) generate one automatically in development, and DevTools uses it automatically when present, this is why development errors already point at readable file names without any setup.

⚠️ **Pitfall**: production builds sometimes disable source maps (smaller output, and not exposing original source to anyone inspecting the deployed site). If you need to debug a production-only bug, check whether source maps are enabled for that build, or reproduce the same failure locally in development first.

## "Uncaught" versus a caught error

`Uncaught TypeError: ...` means nothing in the code caught this error with a `try/catch`, it propagated all the way up and stopped execution. An error caught deliberately (inside a `try/catch`, or a React error boundary) usually shows differently, often as a `console.error` you wrote yourself, or a fallback UI rendering instead of a red uncaught error. Seeing "Uncaught" is a strong signal that this specific spot has no error handling around it at all.

## Key takeaways

- Read the error message first, then look down the stack trace for the first line that names one of your own files, that is usually where the real problem is.
- `TypeError` almost always means a value was not what the code expected it to be, `undefined` or `null` where an object was assumed.
- Source maps are why development errors point at readable file names instead of minified gibberish, they can be missing in some production builds.
- "Uncaught" means no `try/catch` or error boundary handled it, the error had nowhere to go.
