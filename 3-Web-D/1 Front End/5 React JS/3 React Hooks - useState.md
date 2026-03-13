# React Hooks – Overview

- _Hooks_ were introduced in _React 16.8_ to let functional components use state and lifecycle features without classes
- It does not work inside classes
- Hooks are backward-compatible, which means it does not contain any breaking changes

They enable:

- State in functional components
- Logic reuse via custom hooks
- Cleaner composition over inheritance
- Removal of `this` and class boilerplate

## When to use Hooks

1. If you write a function component and then you want to add some state to it,previously you do this by converting it to a class
2. But, now you can do it by using a Hook inside the existing function component

## Rules of Hooks

1. Call Hooks only at the top level (no loops/conditions/ nested functions)
2. Call Hooks only inside/from React function components or custom Hooks
3. Maintain the same call order on every render
4. All the hooks in react start with keyword `use` like useState, useContext, useEffect

React maps Hook calls by execution order internally

## Hooks State

- Hook state is the new way of declaring a state in React app
- Hook uses useState() functional component for setting and retrieving state

## `useState` Hook

`useState` adds local state to functional components

- A state of a component is a variable that holds some information that may change over the lifetime of the component
- Whenever the value of the state changes, the component re-renders itself with updated values
- OR It is the most important and often used hook. The purpose of this hook is to handle reactive data, any data that changes in the application is called state, when any of the data changes, React re-renders the UI

### Syntax

```
const [state, setState] = useState(initialValue);
```

- `state` → current state value
- `setState` → it is a function to update state/ count value
- `initialValue` → starting value (used only on first render)

---

## Example

```
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

```
setCount((prev) => prev + 1);
```

Use when new state depends on previous state

---

### 2. State Replacement (Not Merge)

Unlike class `setState`, `useState` replaces values:

```
setUser((prev) => ({ ...prev, name: "John" }));
```

You must merge manually for objects

---

### 3. Multiple State Variables

```
const [name, setName] = useState("");
const [age, setAge] = useState(0);
```

Encourages separation and predictable updates

---

### 4. Lazy Initialization

```
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
