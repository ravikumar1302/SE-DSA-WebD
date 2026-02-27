## Basics of React JS

1. Extension : .jsx

    - .js → Standard Js files
    - .jsx → JavaScript XML : Js files that contain JSX syntax (React’s HTML-like syntax). While JSX can live in .js files too, some teams prefer .jsx to make it clear
    - .ts → TypeScript files (if your React project uses TypeScript)
    - .tsx → TypeScript files with JSX inside

2. So, if you’re writing React components in plain JavaScript, you can use either:

    - Component.js
    - Component.jsx

3. If using TypeScript with React:

    - Component.ts (no JSX inside)
    - Component.tsx (with JSX inside)

4. JSX : JavaScript XML. It is JS Syntex Extension

---

### Need of React

1. Whenever a webpage is loaded, Browser creates a tree like structure of HTML, called as DOM (Document object model)
2. With growing size of code, it becomes difficult to manage DOM
3. So, with React, webpage is defined using different re-usable components. And react handles the process of creating and updating DOM elements. E.g.
    1. When any dynamic value/state is updated, reach updates the same in Light weight Virtual DOM and checks the same with Actual DOM.
    2. If change is found, then only the actual (Browser) DOM is updated
4. React Projects Use A Build Process

    - Raw, unprocessed React code won't execute in the browser, as JSX is not a default JavaScript feature
    - In addition, the code would not be optimized for production (e.g., not minified)
    - React projects require a build process that transforms your code; create-react-app, vite etc. give you such a build process (no custom setup or tweaking needed)

5. Main use of React JS is to develop UI that improves the speed of apps. It uses virtual DOM that improves performance of app.
    - The JS virtual DOM is faster than regular DOM

---

1. React JS is all abbout components, which are reusable. Each component has it's own logic and control
2.
