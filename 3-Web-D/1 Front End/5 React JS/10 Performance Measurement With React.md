# Performance Measurement With React

#### Need of performance measurement

- When working on small projects, you shouldn’t run into any issues
- However, larger projects will typically have complex UI components, process more data & generally have more moving parts. All of these factors can impact the performance of your app

#### Three different approaches to measuring React performance:

1. Using the Chrome DevTools Performance tab
2. Using the React Developer Tools Chrome extension
3. Using React's Profiler API

## Using Chrome DevTools

- Chrome DevTools is a set of utilities shipped with Google Chrome to help developers debug issues with their websites at runtime
- DevTools gives us a visualization of the performance of your app
    - To see this, ensure that you are running React in development mode, open DevTools in your browser & then go to the “Performance” tab
- You can record the performance of your app from a point after the page has loaded or from the page load. There are two buttons in the top-left corner of the DevTools dialog
- Chrome DevTools Performance tab Timings section shows rendering times for individual React components
- Within the tab labeled “Call Tree” in the bottom pane, we can see the “Self Time” taken for each component’s render
    - "Self Time" is the cumulative amount of time spent rendering the component, excluding its children
    - The "Total Time" includes child rendering times

## Using React Developer Tools Chrome Extension

- It is a Chrome extension that lets you inspect the props & state of your components, as well as inspect their performance
- In React Developer Tools tab, there will be a tab called "Profiler". Click the record button to start recording performance data & after using your app, click the "Stop" button
- The Profiler will display a flame chart of the components in your app & how long they had taken to render, represented by the length of the bar
- A commit is when the determined changes to the DOM are applied by React
- React Developer Tools can also show what prop or state changes caused a re-render
    - First, enable the Record of why each component is rendered while profiling in the settings

## Using the "Profiler" React component

- The unstable_Profiler component is a relatively new addition to the library. Shipped in version 16.4, `<Profiler />` was built to help measure timing in components' lifecycle
- The Profiler component takes two props:
    - id: an identifier for what you're profiling
    - onRender: a callback that's called after a mount or update
