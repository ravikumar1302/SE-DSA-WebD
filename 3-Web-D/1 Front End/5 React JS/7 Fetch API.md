# Fetch API – Overview

- In **React**, the **Fetch API** is used to **retrieve or send data to a server** inside components
- It is commonly used with the `useEffect` Hook to perform **side effects** like API calls
- Works seamlessly with functional components

## What It Enables

- Fetch data when a component loads
- Send user input to backend APIs
- Update UI dynamically based on server data

## When to Use Fetch in React

1. When you need to load data from an API on component mount
2. When submitting forms or sending data
3. When syncing UI with backend data

## Basic Pattern in React

- Use `useEffect` → to run API call
- Use `useState` → to store data

## Example (GET Request)

```
import React, { useEffect, useState } from "react";

function Users() {
    const [users, setUsers] = useState([]);

    useEffect(() => {
        fetch("https://api.example.com/users")
            .then((res) => res.json())
            .then((data) => setUsers(data))
            .catch((err) => console.error(err));
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

## Using Async/Await in React

```
import React, { useEffect, useState } from "react";

function Users() {
    const [users, setUsers] = useState([]);

    useEffect(() => {
        async function fetchData() {
            try {
                const res = await fetch("https://api.example.com/users");
                const data = await res.json();
                setUsers(data);
            } catch (err) {
                console.error(err);
            }
        }

        fetchData();
    }, []);

    return <div>{users.length} users</div>;
}
```

## Important Behaviors

### 1. Runs Inside `useEffect`

- Prevents repeated API calls on every render
- `[]` dependency → runs only once (on mount)

### 2. State Triggers Re-render

- `setUsers(data)` updates state
- Component re-renders with new data

### 3. Loading & Error State (Best Practice)

```javascript
const [loading, setLoading] = useState(true);
const [error, setError] = useState(null);
```

### 4. Cleanup (Avoid Memory Leaks)

```
const controller = new AbortController();

fetch(url, { signal: controller.signal });

return () => controller.abort();
```

## When to Use Fetch

Use for:

- Data fetching in components
- Simple API calls
- Small to medium apps

## When NOT to Use Fetch Alone

Avoid when:

- Complex caching needed → use libraries like React Query
- Many API calls → use abstraction layer (services)

## Mental Model

Fetch in React =
**“Run side effect → get data → store in state → UI updates automatically”**
