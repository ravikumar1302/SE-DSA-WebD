# Basics of Next.js

1. **File Extensions**
    - `.js` → Standard JavaScript files
    - `.jsx` → JavaScript with JSX syntax
    - `.ts` → TypeScript files
    - `.tsx` → TypeScript with JSX syntax

2. **Next.js Pages**
    - Any `.js` or `.tsx` file inside the `pages` directory automatically becomes a route
        - Example:

            ```
            pages/index.js → accessible at /
            pages/about.js → accessible at /about
            ```

    - In Next.js 13+ with **App Router**, use the `app` directory:

        ```
        app/page.js → accessible at /
        app/about/page.js → accessible at /about
        ```

3. **JSX in Next.js**
    - Same as React: allows HTML-like syntax inside JS
    - Can include components, logic, loops, and conditional rendering

---

## Need of Next.js

1. React alone is **Client-side Rendering (CSR)** – the browser renders content after JS loads
   Next.js adds:
    - **Server-side Rendering (SSR)** → HTML generated on the server per request
    - **Static Site Generation (SSG)** → HTML pre-built at build time
    - **Incremental Static Regeneration (ISR)** → Static pages can update after deployment

2. Improves **SEO** and **performance** because search engines can see rendered HTML
3. Built-in routing based on filesystem (`pages` or `app`) – no manual `react-router` setup
4. Built-in optimizations:
    - Image optimization (`next/image`)
    - Automatic code splitting
    - API routes (`pages/api` or `app/api`)

---

## Component in Next.js

- Next.js is still **React-based**, so same rules apply:
    - Components return JSX
    - Use **PascalCase** for component names (`MyButton`, `UserProfile` )

- Components can live anywhere (`components/` folder is standard)

**Example:**

```
components/MyButton.jsx

export default function MyButton({ text, onClick }) {
  return <button onClick={onClick}>{text}</button>;
}
```

---

## Routing in Next.js

1. **Pages-based Routing (File System Routing)**
    - Each file in `pages/` (or `app/` in Next 13+) is a route
    - Nested folders → nested routes
    - Dynamic routes: `[id].js` or `[slug].js`

        ```
        pages/user/[id].js → /user/1, /user/2
        ```

2. **Linking Between Pages**
    - Use `next/link` for client-side navigation

    ```
    import Link from 'next/link';
    <Link href="/about">Go to About</Link>
    ```

3. use client

- Next.js App Router components are Server Components by default
- So, use `"use client";` in top of code where the page is expected to be client component

---

## Data Fetching in Next.js

Next.js provides multiple ways to fetch data:

| Method               | Description                            | Example                  |
| -------------------- | -------------------------------------- | ------------------------ |
| `getStaticProps`     | Fetch data at **build time** (SSG)     | For static pages         |
| `getServerSideProps` | Fetch data **per request** (SSR)       | For dynamic data         |
| `getStaticPaths`     | Define paths for **dynamic SSG pages** | With `[id].js` pages     |
| Client-side fetch    | Like React (`useEffect` + `fetch`)     | For interactive features |

**Example: Static Generation**

```js
export async function getStaticProps() {
    const res = await fetch("https://api.example.com/data");
    const data = await res.json();

    return {
        props: { data },
    };
}

export default function Page({ data }) {
    return <div>{data.title}</div>;
}
```

---

## API Routes in Next.js

- Next.js allows creating backend endpoints inside the app:

    ```
    pages/api/hello.js
    ```

- Example:

```js
export default function handler(req, res) {
    res.status(200).json({ message: "Hello from API" });
}
```

- Can be called from the frontend:

```js
fetch("/api/hello")
    .then((res) => res.json())
    .then((data) => console.log(data));
```

---

## Shared Data / State Management

- Next.js supports all React state methods:
    - `useState`, `useReducer`, `useContext`, Redux, etc.

- **Shared service pattern** works the same as React example you gave
- For server-side shared data, you can use **Server Components** in Next 13+

**Example Service**

```js
// dataService.js
class DataService {
    constructor() {
        this.data = {};
    }

    setData(data) {
        this.data = data;
    }

    getData() {
        return this.data;
    }
}

export default new DataService();
```

---

## Summary

| Feature       | React            | Next.js                                       |
| ------------- | ---------------- | --------------------------------------------- |
| Rendering     | Client-side      | SSR, SSG, ISR, CSR                            |
| Routing       | react-router     | File-based routing                            |
| SEO           | Limited          | Excellent (pre-rendered HTML)                 |
| Data Fetching | useEffect/fetch  | `getStaticProps`, `getServerSideProps`        |
| API           | External backend | Built-in API routes                           |
| Optimization  | Manual           | Built-in (code splitting, image, fonts, etc.) |
