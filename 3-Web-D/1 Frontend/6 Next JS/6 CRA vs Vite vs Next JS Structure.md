# CRA vs Vite vs Next.js

## Why use **Next.js** instead of CRA / Vite?

### CRA

1. Older setup
2. Slow builds
3. Deprecated by React team

### Vite

1. Fast dev server
2. Best for SPA apps
3. You manually add routing, SEO, backend

### Next.js

1. Full React framework
2. Built-in routing
3. SSR + SEO support
4. Backend APIs included
5. Production-ready by default

👉 **Vite = React App**

👉 **Next.js = React Framework**

---

# Folder Structure Differences

| Area          | CRA                 | Vite           | Next.js (App Router) |
| ------------- | ------------------- | -------------- | -------------------- |
| Entry file    | `src/index.js`      | `src/main.jsx` | ❌ Not needed        |
| Main UI       | `App.js`            | `App.jsx`      | `app/page.jsx`       |
| Global layout | App.js              | App.jsx        | `app/layout.jsx`     |
| HTML file     | `public/index.html` | `index.html`   | ❌ Auto handled      |
| Routing       | Manual              | Manual         | File-based           |
| Global CSS    | `index.css`         | `index.css`    | `globals.css`        |
| Component CSS | `App.css`           | `App.css`      | `*.module.css`       |
| Env vars      | `REACT_APP_`        | `VITE_`        | `NEXT_PUBLIC_`       |

---

# Quick Summary

| File                | Purpose          | House Analogy 🏠  |
| ------------------- | ---------------- | ----------------- |
| `main.jsx` (Vite)   | Starts React app | Main switch       |
| `App.jsx` (Vite)    | Main layout      | House structure   |
| `layout.jsx` (Next) | Global layout    | Entire house      |
| `page.jsx` (Next)   | Page UI          | Individual room   |
| `globals.css`       | Global styles    | Whole house paint |
| `*.module.css`      | Component styles | Room design       |

---

# Where did things go in Next.js?

❌ `main.jsx` → Next.js starts React automatically

❌ `App.jsx`

Split into:

- `layout.jsx` → global layout
- `page.jsx` → page content

❌ `index.html` → Handled internally by Next.js

### CSS Changes

| Vite        | Next.js           |
| ----------- | ----------------- |
| `index.css` | `globals.css`     |
| `App.css`   | `Home.module.css` |

👉 Next.js uses **CSS Modules** by default

---

# Routing Difference

`Vite / CRA` → Install router manually

`Next.js` → Folder = Route

```
app/
 ├─ page.jsx      → /
 └─ about/page.jsx → /about
```

### One-Line Shift

👉 **Vite:** You configure React

👉 **Next.js:** Structure already exists — just add pages
