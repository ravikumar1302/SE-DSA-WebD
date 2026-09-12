# Breakpoints and the Sources Panel

A `console.log` tells you a value at one moment, then the code keeps running. A breakpoint pauses the entire page exactly at that line, letting you inspect every variable in scope, step forward one line at a time and watch how values change. It is the single most powerful debugging tool in the browser, and the least used by beginners.

## Setting a line breakpoint

1. Open the Sources panel.
2. Find the file (or search it with `Ctrl+P`).
3. Click the line number where you want execution to pause.
4. Trigger that code (click a button, submit a form, whatever runs it).

The page freezes at that exact line. Every variable currently in scope is visible in the "Scope" panel on the right, no need to log them one by one.

```
Without a breakpoint:
code runs start to finish -> you only see whatever you logged, after the fact

With a breakpoint:
code runs -> pauses exactly here -> inspect everything, live, then step forward
```

## Stepping through code

Once paused, four buttons control movement:

| Button | Shortcut | Does |
|---|---|---|
| Resume | `F8` | Continue running until the next breakpoint |
| Step over | `F10` | Run the current line, do not enter function calls it makes |
| Step into | `F11` | Enter the function being called on this line |
| Step out | `Shift+F11` | Finish the current function, return to whoever called it |

📌 **Rule of thumb**: step over by default, step into only when the function you are stepping over is the one you actually suspect is wrong. Stepping into every function call quickly gets you lost deep in library code you do not need to see.

## Conditional breakpoints

Right-click a line number and choose "Add conditional breakpoint." The page only pauses when the condition is true.

```js
// pauses only when this specific item is being processed, not all 500 others
item.id === 42
```

Extremely useful in a loop where only one specific iteration is the problem. Without a condition, you would hit the same breakpoint hundreds of times before reaching the one you care about.

## Watch expressions

The Watch panel (next to Scope) lets you type an expression once, and it re-evaluates automatically every time you pause, even if that expression is not a variable currently visible on screen, for example `user.profile.settings.theme`.

## DOM breakpoints, pausing on a DOM change

In the Elements panel, right-click any element and choose "Break on" -> subtree modifications, attribute modifications or node removal. Execution pauses the instant JavaScript changes that element, useful when something on the page changes and you cannot find which code did it.

## XHR/fetch breakpoints

In the Sources panel's left sidebar, there is an "XHR/Fetch Breakpoints" section. Add a URL fragment (or leave it blank to catch all requests), and execution pauses right before that network request fires, showing exactly what triggered it in the call stack.

## The debugger statement

Instead of clicking a line number, you can pause from inside the code itself.

```js
function calculateTotal(items) {
  debugger; // execution pauses here whenever this line runs, if DevTools is open
  return items.reduce((sum, item) => sum + item.price, 0);
}
```

Handy for a breakpoint you want to travel with the code temporarily, remove it before committing, the same as a stray `console.log`.

## Key takeaways

- A breakpoint pauses the page at an exact line, letting you inspect every variable live, more powerful than any number of logs.
- Step over by default, step into only the specific function you suspect is wrong.
- Conditional breakpoints skip straight to the one iteration or case that actually matters.
- DOM and XHR/fetch breakpoints pause on an event rather than a line, useful when you know what happened but not which code caused it.
