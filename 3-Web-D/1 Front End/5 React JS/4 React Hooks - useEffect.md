## `useEffect` Hook

`useEffect` lets functional components **perform side effects after rendering**

A **side effect** is any operation that interacts with something **outside the React component**, such as:

- API requests
- DOM manipulation
- Timers
- Event listeners
- Subscriptions
- Logging

React runs effects **after the component renders and the DOM updates**

---

## Syntax

```
useEffect(() => {
    // side effect logic

    return () => {
        // cleanup (optional)
    };
}, [dependencies]);
```

### Parameters

- **effect function** → code that runs after render
- **cleanup function** → runs before the effect re-runs or when component unmounts
- **dependency array** → controls when the effect runs

---

# Basic Example

```
import React, { useState, useEffect } from "react";

function Counter() {
    const [count, setCount] = useState(0);

    useEffect(() => {
        console.log("Component rendered or count changed");
    }, [count]);

    return (
        <>
            <p>{count}</p>
            <button onClick={() => setCount(count + 1)}>Increment</button>
        </>
    );
}
```

---

# How It Works (Developer View)

- Effects run **after React commits changes to the DOM**
- Each render gets its **own effect instance**
- Before running a new effect, React **cleans up the previous one**
- Effects are **scheduled asynchronously**
- Dependencies determine **when the effect re-runs**

Lifecycle mapping (rough idea):

```
Mount → useEffect runs
Update → cleanup old effect → run new effect
Unmount → cleanup runs
```

---

# Dependency Array Behavior

### 1. Run On Every Render

```
useEffect(() => {
    console.log("Runs on every render");
});
```

No dependency array → runs after **every render**

---

### 2. Run Only Once (On Mount)

```
useEffect(() => {
    console.log("Runs only once");
}, []);
```

Empty dependency array → runs **only on first render**

Equivalent to:

```
componentDidMount
```

---

### 3. Run When Specific Value Changes

```
useEffect(() => {
    console.log("Runs when count changes");
}, [count]);
```

Effect runs when **any dependency changes**

---

# Cleanup Function

Cleanup prevents **memory leaks** and unwanted subscriptions

```
useEffect(() => {
    const timer = setInterval(() => {
        console.log("Tick");
    }, 1000);

    return () => {
        clearInterval(timer);
    };
}, []);
```

Cleanup runs:

1. Before the effect re-runs
2. When component **unmounts**

---

# Example: API Fetch

```
import { useEffect, useState } from "react";

function Users() {
    const [users, setUsers] = useState([]);

    useEffect(() => {
        fetch("https://api.example.com/users")
            .then((res) => res.json())
            .then((data) => setUsers(data));
    }, []);

    return (
        <ul>
            {users.map((user) => (
                <li key={user.id}>{user.name}</li>
            ))}
        </ul>
    );
}
```

---

# Example: Event Listener

```
useEffect(() => {
    function handleResize() {
        console.log(window.innerWidth);
    }

    window.addEventListener("resize", handleResize);

    return () => {
        window.removeEventListener("resize", handleResize);
    };
}, []);
```

---

# Important Behaviors

## 1. Effects Run After Render

Rendering is **pure**. Effects run **after rendering completes**

```
Render → Commit DOM → Run useEffect
```

---

## 2. Closures in Effects

Effects capture values from the render they belong to

```
useEffect(() => {
    console.log(count);
}, []);
```

This will always log **initial count**, not updates

Fix by adding dependency:

```
useEffect(() => {
    console.log(count);
}, [count]);
```

---

## 3. Dependency Rules

React expects **all external values used inside the effect** to appear in dependencies

Bad:

```
useEffect(() => {
    console.log(count);
}, []);
```

Correct:

```
useEffect(() => {
    console.log(count);
}, [count]);
```

---

## 4. Effects Should Not Be Conditional

Bad:

```
if (count > 5) {
    useEffect(() => {
        console.log("bad pattern");
    });
}
```

Correct:

```
useEffect(() => {
    if (count > 5) {
        console.log("valid pattern");
    }
}, [count]);
```

Hooks must run in **consistent order**

---

# Common Patterns

### 1. Fetch Data

```
useEffect → API call
```

---

### 2. Setup Subscriptions

```
useEffect → subscribe
cleanup → unsubscribe
```

---

### 3. Timers / Intervals

```
useEffect → setInterval
cleanup → clearInterval
```

---

### 4. DOM Interactions

```
useEffect → focus element
useEffect → manipulate scroll
```

---

# When to Use `useEffect`

Use for:

- Data fetching
- Subscriptions
- Timers
- DOM APIs
- Logging / analytics

Avoid for:

- Pure calculations
- Derived state

Example of bad usage:

```
useEffect(() => {
    setFullName(firstName + lastName);
}, [firstName, lastName]);
```

Better:

```
const fullName = firstName + lastName;
```

---

# Mental Model

Think of `useEffect` as:

**"Synchronizing the component with the outside world"**

```
Render UI
↓
React commits DOM
↓
useEffect runs side effects
```

Components **describes UI**, and `useEffect` **connects it to external systems**
