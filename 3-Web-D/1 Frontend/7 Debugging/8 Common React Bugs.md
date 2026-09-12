# Common React Bugs

A handful of bugs come up over and over in React code, often confusing beginners because the code "looks correct." This file names each one, shows what it looks like broken, and how to spot it with the tools from the earlier files.

## Stale closures

A function created inside a component "closes over" the values that existed at the time it was created. If that value later changes but the function was not recreated, it keeps using the old one.

```jsx
function Counter() {
  const [count, setCount] = useState(0);

  useEffect(() => {
    const interval = setInterval(() => {
      console.log(count); // always logs 0, forever
      setCount(count + 1); // always sets to 1, forever
    }, 1000);
    return () => clearInterval(interval);
  }, []); // empty array, this effect runs once, closing over count = 0 permanently

  return <p>{count}</p>;
}
```

The effect ran once, when `count` was `0`, and the interval callback keeps that `0` forever, since the effect never re-runs to create a new closure with a fresh `count`. Fix: use the updater function form, `setCount(c => c + 1)`, which does not depend on the closed-over value at all, or add `count` to the dependency array so the effect re-creates the interval with a fresh value each time.

🔗 See [React Hooks - useEffect](../5%20React%20JS/4%20React%20Hooks%20-%20useEffect.md) for how the dependency array controls when an effect re-runs.

## Infinite re-render loops

```jsx
function UserList() {
  const [users, setUsers] = useState([]);
  setUsers(users); // called directly during render, not inside an effect or handler
  return <ul>{users.map(u => <li key={u.id}>{u.name}</li>)}</ul>;
}
```

Calling a state setter directly in the render body (not inside `useEffect`, an event handler, or a condition that stops it) triggers a re-render, which calls the setter again, forever. The browser tab usually freezes or the console fills with "Maximum update depth exceeded."

```
Render runs -> calls setState -> triggers a new render -> calls setState -> ...
```

Fix: only call setters inside effects (with a correct dependency array so they do not run every render), event handlers, or guarded by a real condition.

## Missing or wrong `key` props

```jsx
{items.map((item, index) => (
  <ItemRow key={index} item={item} /> // index as key, fragile
))}
```

Using the array index as a `key` works until the list reorders, items get inserted, or items get removed from the middle. React uses `key` to match old elements to new ones between renders, an index-based key can mismatch an item with the wrong row's leftover internal state (a text input keeping the wrong item's typed value is a classic symptom). Fix: use a real, stable identifier from the data, `item.id`, not the array position.

## State not updating "immediately"

```jsx
function handleClick() {
  setCount(count + 1);
  console.log(count); // still logs the OLD value, not the new one
}
```

State updates are not synchronous, calling a setter schedules a re-render, it does not mutate the variable in place right there. The component re-renders with the new value on the next render, `count` inside this same function call is still the old one. This is expected behavior, not a bug, but it surprises beginners reading straight through the code top to bottom.

## Effect running twice in development

In React 18's Strict Mode (development only), effects intentionally run twice on mount, to help surface bugs like the stale closure and cleanup issues above. This does not happen in production, seeing an effect fire twice in development while debugging is expected, not a real bug on its own, unless the effect also misbehaves in production.

## Where to look, quick reference

| Symptom | Likely bug | Fix direction |
|---|---|---|
| A value inside a callback never updates | Stale closure | Updater function form, or fix the dependency array |
| Page freezes, "Maximum update depth exceeded" | State set directly during render | Move the setter into an effect, handler, or guard it |
| Wrong row's input keeps old text after reordering | Index used as `key` | Use a stable id from the data |
| A variable seems "one step behind" right after setting it | State updates are async, not immediate | Read the new value in the next render or a `useEffect`, not the same line |
| An effect fires twice, only in development | React 18 Strict Mode, intentional | Not a real bug unless it also breaks in production |

## Key takeaways

- Stale closures happen when a function keeps an old value from when it was created, the updater function form of a state setter avoids depending on it at all.
- Calling a setter directly during render (not in an effect or handler) causes an infinite loop.
- `key` should be a stable id from the data, not the array index, especially for lists that reorder or change.
- State setters schedule a re-render, they do not update the variable synchronously in the same line.
