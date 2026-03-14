# React Memo

**`React.memo`** is a performance optimization feature in **React** that **prevents a functional component from re-rendering if its props haven’t changed** or it is a higher-order component that memoizes functional components and skips re-rendering when props remain unchanged

In simple terms:
➡️ It **memorizes (caches) the last rendered result** of a component and **reuses it** when the same props are passed again

## 1. Basic Idea

Normally in React:

- When a **parent component re-renders**
- **all child components also re-render** — even if their props are the same

`React.memo` avoids this unnecessary re-render

## 2. Basic Syntax

```
import React from "react";

const MyComponent = ({ name }) => {
    console.log("Rendering MyComponent");
    return <h1>Hello {name}</h1>;
};

export default React.memo(MyComponent);
```

Now:

- If `name` **doesn't change**
- `MyComponent` **will not re-render**

## 3. Example Without React.memo

```
function Parent() {
    const [count, setCount] = React.useState(0);

    return (
        <>
            <button onClick={() => setCount(count + 1)}>Increment</button>
            <Child name="John" />
        </>
    );
}

function Child({ name }) {
    console.log("Child rendered");
    return <h1>{name}</h1>;
}
```

Every time `count` changes:

👉 `Child` re-renders even though `name` didn't change

## 4. Example With React.memo

```
const Child = React.memo(function Child({ name }) {
    console.log("Child rendered");
    return <h1>{name}</h1>;
});
```

Now:

- Parent re-renders ✅
- Child **does NOT re-render** if `name` is unchanged

## 5. Custom Comparison Function (Advanced)

You can control how props are compared.

```
const Child = React.memo(
    function Child({ user }) {
        return <h1>{user.name}</h1>;
    },
    (prevProps, nextProps) => {
        return prevProps.user.id === nextProps.user.id;
    },
);
```

If the function returns:

- `true` → skip re-render
- `false` → re-render

## 6. React.memo vs Other React Hooks

| Feature       | Purpose                          |
| ------------- | -------------------------------- |
| `React.memo`  | Prevents **component re-render** |
| `useMemo`     | Memoizes **computed values**     |
| `useCallback` | Memoizes **functions**           |

---

## 7. When to Use React.memo

Use it when:

- ✅ Component renders **often**
- ✅ Rendering is **expensive**
- ✅ Props **rarely change**

Avoid using it everywhere because it also has **comparison overhead**
