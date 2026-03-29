# When NOT to use Next.js

## ❌ When Next.js is Overkill

### 1️⃣ Simple SPA / Internal Tools

- Dashboard, admin panels, prototypes
- SEO / SSR not needed
- Vite / CRA is enough → faster dev, smaller bundle

### 2️⃣ Pure Static Sites Without Dynamic Data

- Small personal landing page / brochure
- No API calls, no auth, no SEO concerns
- Next.js adds unnecessary complexity

### 3️⃣ Learning / Tiny Projects

- If your goal = learn React basics
- CRA / Vite simpler → less boilerplate

### 4️⃣ Non-React Frontend

- If project uses **Vue / Svelte / Angular** → Next.js irrelevant

### 5️⃣ Serverless / Backend Already Separate

- If backend is fully managed (Firebase functions / Supabase)
- Only frontend needed → CRA / Vite enough

### 6️⃣ Projects With Heavy Client-side Interactivity

- Games, rich animations, real-time dashboards
- SSR provides **no benefit**, may add complexity

---

## ⚡ TL;DR

- **Use Next.js** → SEO, SSR, SSG, API routes, production product
- **Don’t use Next.js** → simple SPA, prototypes, purely client-side apps
