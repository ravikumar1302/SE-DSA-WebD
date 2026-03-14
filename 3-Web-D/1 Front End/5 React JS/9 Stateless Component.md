# Stateless Component

- A **Stateless Component** in React is a component that does not manage its own state
- It is a functional component that does not manage its own state and renders UI based only on the props it receives
- It simply receives data through props and renders UI based on those props
- Because it only focuses on displaying data, it is often called a Presentational Component

## 1. Basic Idea

A stateless component:

- ❌ Does **not use state**
- ✅ Receives **props**
- ✅ Returns **UI (JSX)**

It is basically a **pure function that returns UI**

## 2. Simple Example

```
function Greeting(props) {
    return <h1>Hello {props.name}</h1>;
}
```

Usage:

```
<Greeting name="John" />
```

Output:

```
Hello John
```

Here:

- Greeting does not manage any state
- It just displays data passed via props

## 3. Stateless Component Using Arrow Function

This is the **most common pattern**

```
const Greeting = ({ name }) => {
    return <h1>Hello {name}</h1>;
};
```

Even shorter:

```
const Greeting = ({ name }) => <h1>Hello {name}</h1>;
```

## 4. Stateless vs Stateful Component

| Feature    | Stateless Component | Stateful Component |
| ---------- | ------------------- | ------------------ |
| State      | ❌ No state         | ✅ Has state       |
| Purpose    | UI rendering        | Logic + UI         |
| Complexity | Simple              | More complex       |
| Example    | Display user info   | Manage form input  |

Example of **stateful component**:

```
function Counter() {
    const [count, setCount] = React.useState(0);

    return <button onClick={() => setCount(count + 1)}>{count}</button>;
}
```

## 5. Real-World Example

Stateless component:

```
const UserCard = ({ name, age }) => {
    return (
        <div>
            <h2>{name}</h2>
            <p>Age: {age}</p>
        </div>
    );
};
```

Parent component passes data:

```
<UserCard name="Alice" age={25} />
```

## 6. Advantages

- Simple and easy to understand
- Easier to test
- Reusable
- Faster rendering in many cases
- Good for UI-only components
