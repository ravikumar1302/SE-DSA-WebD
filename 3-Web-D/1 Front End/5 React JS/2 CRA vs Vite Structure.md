## CRA (create-react-app) vs VITE

### Why use Vite instead of CRA?

1. Faster & Modern – Instant dev server start using native ES modules
2. CRA is deprecated by the React team
3. Better performance – Faster reloads and builds, even in large projects
4. Smaller production bundles (uses modern tooling like Rollup)
5. Lightweight & flexible – Easier to configure; not overly opinionated

### Folder Structure Differences

| Area             | CRA                        | Vite                  |
| ---------------- | -------------------------- | --------------------- |
| Entry JS file    | `src/index.js`             | `src/main.jsx`        |
| Main component   | `src/App.js`               | `src/App.jsx`         |
| HTML file        | `public/index.html`        | `index.html` (root)   |
| Global CSS       | `src/index.css`            | `src/index.css`       |
| Component CSS    | `src/App.css`              | `src/App.css`         |
| Environment file | `.env` (uses `REACT_APP_`) | `.env` (uses `VITE_`) |

---

# Quick Summary

| File        | Purpose                                                       | Analogy with house 🏠                 |
| ----------- | ------------------------------------------------------------- | ------------------------------------- |
| `main.jsx`  | Starts the React app & renders `<App />`                      | Main electric switch (turns house on) |
| `App.jsx`   | Main UI component (app layout)                                | The house structure                   |
| `index.css` | Global styles for the entire app - (Global CSS, for main.jsx) | Paint/design for the whole house      |
| `App.css`   | Styles specific to `App.jsx`                                  | Design for the main hall              |

In larger projects:

- Each component can have its own CSS file (e.g., Navbar.jsx, Navbar.css)

---

## Why are there **2 JSX files**?

In Vite (and CRA), you usually see: main.jsx, App.jsx

| `main.jsx` → Entry File                         | `App.jsx` → Main Component                                                   |
| ----------------------------------------------- | ---------------------------------------------------------------------------- |
| This is the **starting point** of your app      | This is your main UI component                                               |
| It connects React to the HTML file              | You write your website layout here                                           |
| It renders `<App />` into the `div#root`        | Later, you can create more components like: Navbar.jsx, Footer.jsx, Home.jsx |
| **Think of it as:** “Start the React app here.” | **Think of it as:** “This is my main webpage layout”                         |

---

## Why are there **2 CSS files**?

You usually see: index.css, App.css

| `index.css` → Global CSS                                                                | `App.css` → Component CSS                      |
| --------------------------------------------------------------------------------------- | ---------------------------------------------- |
| This applies styles to **entire application**                                           | This is mainly for styling `App.jsx` component |
| **Example:**                                                                            | **Example:**                                   |
| `body { margin: 0; font-family: Arial; }`                                               | `.container { text-align: center; }`           |
| **Used for:**<br> Body styles, Reset styles, Default fonts, Global background color etc | Used for layout & styling specific to App      |
| 👉 Affects everything                                                                   | 👉 Specific to App component (App.jsx)         |
