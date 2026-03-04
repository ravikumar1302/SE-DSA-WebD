## React Hooks – Overview

_Hooks_ were introduced in _React 16.8_ to let functional components use state and lifecycle features without classes

They enable:

- State in functional components
- Logic reuse via custom hooks
- Cleaner composition over inheritance
- Removal of `this` and class boilerplate

---

## Rules of Hooks

1. Call Hooks only at the top level (no loops/conditions)
2. Call Hooks only inside React function components or custom Hooks
3. Maintain the same call order on every render

React maps Hook calls by execution order internally

---

# `useState` Hook

`useState` adds local state to functional components.

### Syntax

```javascript
const [state, setState] = useState(initialValue);
```

- `state` → current state value
- `setState` → function to update state
- `initialValue` → starting value (used only on first render)

---

## Example

```javascript
import React, { useState } from "react";

function Counter() {
    const [count, setCount] = useState(0);

    return (
        <>
            <p>{count}</p>
            <button onClick={() => setCount((prev) => prev + 1)}>Increment</button>
        </>
    );
}
```

---

## How It Works (Developer View)

- React stores state per component instance
- Each render re-executes the function
- Calling `setState` schedules a re-render
- Updates are batched
- DOM updates only if virtual DOM changes

---

## Important Behaviors

### 1. Functional Updates (Avoid stale closures)

```javascript
setCount((prev) => prev + 1);
```

Use when new state depends on previous state

---

### 2. State Replacement (Not Merge)

Unlike class `setState`, `useState` replaces values:

```javascript
setUser((prev) => ({ ...prev, name: "John" }));
```

You must merge manually for objects

---

### 3. Multiple State Variables

```javascript
const [name, setName] = useState("");
const [age, setAge] = useState(0);
```

Encourages separation and predictable updates

---

### 4. Lazy Initialization

```javascript
const [state] = useState(() => expensiveComputation());
```

Function runs only on first render

---

## When to Use `useState`

Use for:

- UI state (forms, toggles, counters)
- Component-local logic

Avoid for:

- Complex transitions → use `useReducer`
- Shared/global state → context or state libraries

---

<br>

**Mental model:**
`useState` is a persistent state cell tied to component execution order. React preserves it across renders; your function just re-runs
