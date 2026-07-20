# Context API – Overview

- The **Context API** is a feature in **React** that allows you to share data across components **without passing props manually at every level (prop drilling)**
- It works with functional components and integrates well with Hooks
- Introduced as a simpler alternative to state management libraries for certain use cases

## What It Enables

- Global/shared state (theme, auth, language, etc.)
- Avoids deeply nested prop passing
- Cleaner and more maintainable component trees

## When to Use Context

1. When multiple components need access to the same data
2. When props are being passed through many layers unnecessarily
3. For app-wide data like:
    - User authentication
    - Theme (dark/light mode)
    - Language settings

## Core Concepts

### 1. Create Context

```
const MyContext = React.createContext();
```

---

### 2. Provide Context

Wrap components with a **Provider** to supply data:

```
<MyContext.Provider value={data}>
    <Child />
</MyContext.Provider>
```

---

### 3. Consume Context

Access data using `useContext`:

```
const value = useContext(MyContext);
```

---

## Example

```
import React, { createContext, useContext } from "react";

const ThemeContext = createContext("light");

function App() {
    return (
        <ThemeContext.Provider value="dark">
            <Toolbar />
        </ThemeContext.Provider>
    );
}

function Toolbar() {
    return <Button />;
}

function Button() {
    const theme = useContext(ThemeContext);

    return <button>{theme}</button>;
}
```

## Important Notes

- Context avoids prop drilling but **does not replace state management entirely**
- Every time the context value changes, all consuming components re-render
- Best for **read-heavy, low-frequency updates**

## When NOT to Use Context

Avoid when:

- Data changes very frequently (performance issues)
- Only a few components need the data (props are simpler)
- Complex logic → consider `useReducer` or external libraries

## Mental Model

Context is like a **global data channel** for a component tree.
Instead of passing data step-by-step, components can directly “subscribe” to it.
