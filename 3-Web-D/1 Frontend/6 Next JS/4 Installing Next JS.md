# ✅ Next.js App Setup Choices (2026 Standard)

```
npx create-next-app@latest
```

### Recommended choices

| Setup Option             | Choice | Key Benefits                                            |
| ------------------------ | ------ | ------------------------------------------------------- |
| **TypeScript**           | ✅ YES | Better autocomplete • Fewer bugs • Industry standard    |
| **ESLint**               | ✅ YES | Auto error detection • Clean code • Team-ready          |
| **Tailwind CSS**         | ✅ YES | Fast UI building • Modern standard • Component-friendly |
| **`src/` Directory**     | ✅ YES | Cleaner structure • Scalable projects • Organized root  |
| **App Router**           | ✅ YES | Server Components • Better performance • Modern routing |
| **Import Alias (`@/*`)** | ❌ No  | Clean imports • No long paths • Easier refactoring      |
| **Turbopack**            | ✅ YES | Faster dev server • Instant refresh • Future default    |

#### Default import alias (@/\*) : ❌ No

Now use `import Button from "@/components/Button"` instead of `../../../components/Button`

- If you choose No : Would you like to customize the import alias? → No
    - Next.js automatically uses: `@/*`

---

<br><br>

# ✅ Next.js Post-Setup Checklist

```
Clean → Structure → Alias → Layout → Fonts → Env → Utils → Formatting
```

---

## 1️⃣ Remove Starter Demo Files

**Delete these**

```
app/page.module.css
public/vercel.svg
public/next.svg
```

**Replace website logo later**

```
app/favicon.ico
```

👉 Goal: start clean without demo clutter

---

## 2️⃣ Clean `app/page.tsx`

Replace default UI with minimal starter (below code), to prevent fighting with boiler template code later

```tsx
export default function Home() {
    return <main>Welcome</main>;
}
```

---

## 3️⃣ Create Project Folder Structure

Create inside `src/`:

```
components/   → reusable UI
lib/          → configs, db, helpers
hooks/        → custom hooks
utils/        → small utilities
services/     → API calls / actions
styles/       → global styles
types/        → TypeScript types
```

---

## 4️⃣ Setup Absolute Imports

Check `tsconfig.json`:

```json
{
    "compilerOptions": {
        "paths": {
            "@/*": ["./src/*"]
        }
    }
}
```

Now use `import Button from "@/components/Button"` instead of `../../../components/Button`

---

## 5️⃣ Configure Root Layout

Edit: `app/layout.tsx`

Basic structure:

```tsx
<html lang="en">
    <body>{children}</body>
</html>
```

Later this file holds:

- Providers
- Theme
- Metadata
- Fonts

👉 Think of it as **app shell**

---

## 6️⃣ Setup Fonts (Modern Way)

Use Next.js font optimization : `import { Inter } from "next/font/google";`

- automatic optimization
- no layout shift
- better performance

🚫 No one use CDN fonts anymore

---

## 7️⃣ Create Environment File

Create : `.env.local`

Add early placeholders :

```
DATABASE_URL=
NEXT_PUBLIC_APP_URL=http://localhost:3000
```

👉 Saves refactoring pain later

---

## 8️⃣ Add `cn()` Utility

Create: `src/utils/cn.ts`

```ts
import { clsx } from "clsx";
import { twMerge } from "tailwind-merge";

export function cn(...inputs: any[]) {
    return twMerge(clsx(inputs));
}
```

👉 Almost every Tailwind project uses this

---

## 9️⃣ Setup ESLint + Prettier

Install: `npm install -D prettier eslint-config-prettier`

Create `.prettierrc`

```json
{
    "semi": false,
    "singleQuote": true
}
```

👉 Prevent formatting conflicts later
