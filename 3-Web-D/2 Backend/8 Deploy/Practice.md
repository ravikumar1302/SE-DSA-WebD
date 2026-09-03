# Practice: Deploy

Fewer exercises, more checklist, because this phase is mostly about doing it once carefully rather than repeatedly.

---

### 1. Prove the production path locally

Run `npm run build`, then run the compiled output directly with Node.

**Done when**: `node dist/index.js` starts the server correctly, with no TypeScript involved at runtime.

---

### 2. Audit what would ship

Run `git status`, and check what is tracked.

**Done when**: `.env`, `node_modules` and `dist` are all ignored, confirmed rather than assumed.

---

### 3. Document required variables

Create a `.env.example` with every variable name and a placeholder value.

**Done when**: someone cloning the repo knows exactly what to set, without reading the source.

---

### 4. Deploy the smallest thing first

Deploy while the app only has `/health`, before anything complicated is involved.

**Done when**: the live URL returns JSON, and the deploy pipeline is proven before real routes are added.

---

### 5. Break it on purpose

Remove one required environment variable in the platform dashboard and redeploy.

**Done when**: the logs show a clear startup failure naming the missing variable, and you fix it from the logs alone.

---

### 6. Migrate production

Run `prisma migrate deploy` against the production database.

**Done when**: the production schema matches your local one, and you can explain why `migrate dev` would have been the wrong command.

---

### 7. Read production logs deliberately

Trigger a real error on the deployed app, then find it in the logs.

**Done when**: you can locate a specific request's failure without local debugging tools.

---

### 8. Connect a real frontend

Point a small Next.js page at the deployed API and fetch real data.

**Done when**: data renders in the browser, from the live API, not from localhost.

---

### 9. Hit the CORS wall

Before adding the deployed frontend origin to the allowlist, load the page and read the browser console.

**Done when**: you recognize the CORS error on sight, and know why curl never showed it.

---

### 10. Full loop, live

Register, log in and perform one authenticated action, entirely against production.

**Done when**: it works end to end in a browser, on the real URL, with no local server running anywhere.

---

## Stretch

Deploy a second, throwaway copy of the app and point it at a separate database. Having a staging environment you can break freely changes how confidently you deploy the real one.
