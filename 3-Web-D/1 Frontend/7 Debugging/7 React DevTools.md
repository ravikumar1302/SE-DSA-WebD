# React DevTools

The browser's own DevTools understand HTML, CSS and plain JavaScript, but a React app's real structure is components, props and state, not raw DOM nodes. React DevTools is a browser extension that adds two new panels, Components and Profiler, that understand React directly.

## Installing it

Search "React Developer Tools" in the Chrome or Firefox extension store, install it, then open any page running React (in development mode especially). Two new tabs, "⚛️ Components" and "⚛️ Profiler," appear in DevTools automatically.

## The Components tab

Shows the actual component tree, not the raw DOM, `<UserCard>`, `<Button>`, `<Modal>`, exactly as written in the code, nested the way they are actually composed.

```
App
 └─ Dashboard
     ├─ Sidebar
     └─ UserList
         ├─ UserCard (props: { id: 1, name: "Ravi" })
         ├─ UserCard (props: { id: 2, name: "Asha" })
         └─ UserCard (props: { id: 3, name: "Neel" })
```

Clicking any component shows its current props and state on the right, live. Editing a value there updates the component immediately, exactly like editing a CSS value in the Styles tab, letting you test "what if this prop were different" without changing code and reloading.

## "Why did this render"

A checkbox in the Profiler settings ("Record why each component rendered") shows, next to a highlighted render, the actual reason: a specific prop changed, state changed, the parent re-rendered, or a context value changed. This directly answers the "why is this component re-rendering" question that plain `console.log` struggles with, since a log shows that a render happened, not why.

## Highlighting updates

Another setting, "Highlight updates when components render," draws a brief colored border around any component the instant it re-renders. Watching this while interacting with the page makes over-rendering visually obvious: if typing one character into a search box lights up the entire page in colored borders, that is a strong, immediate signal that state lives too high up the tree, more on this pattern in the next file.

## The Profiler tab

Click record, interact with the app for a few seconds, stop recording. The Profiler shows a timeline of every render that happened, how long each took and which component triggered it. Bars are colored by render time, a quick way to spot the one component that is disproportionately slow among dozens that render fine.

📌 Reach for the Profiler specifically when something feels slow but you cannot tell which component is responsible. For "why did this one specific render happen," the simpler "why did this render" checkbox above is usually faster.

## Searching the component tree

For a large app, scrolling through nested components is slow. The search icon at the top of the Components tab filters the tree by component name, typing "UserCard" instantly narrows a deep tree down to only matching nodes and their ancestors.

## Key takeaways

- React DevTools adds a Components tab (the real component tree, live props and state) and a Profiler tab (render timing) on top of the browser's own tools.
- Editing props or state directly in the Components tab tests "what if" without changing code.
- "Highlight updates when components render" makes over-rendering visible at a glance, without any logging.
- The Profiler answers "which component is slow," the "why did this render" checkbox answers "why did this specific render happen."
