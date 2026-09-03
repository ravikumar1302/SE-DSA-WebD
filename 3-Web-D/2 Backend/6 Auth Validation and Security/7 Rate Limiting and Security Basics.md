# Rate Limiting and Security Basics

A round-up of the practical, "starter threat list" items from Phase 3 of the roadmap. [`07-security.md`](../0%20Concepts/07-security.md) covers the full OWASP Top 10 in depth, this file focuses on what to actually implement right now.

## Rate limiting

Without a limit, nothing stops one client from sending thousands of requests per second, whether from a bug, a bot or a deliberate attack (most commonly, repeatedly guessing passwords on a login route).

```bash
npm install express-rate-limit
```

```ts
import rateLimit from "express-rate-limit";

const authLimiter = rateLimit({
  windowMs: 15 * 60 * 1000, // 15 minutes
  max: 10,                   // 10 requests per window, per IP
  message: { error: "Too many attempts, please try again later" },
});

app.use("/auth", authLimiter);
```

This limits every route under `/auth` (login, register) to 10 requests per 15 minutes per IP address. A legitimate user rarely hits this, a script trying to brute-force passwords hits it almost immediately.

📌 **Rule of thumb**: apply stricter limits to auth routes (login, register, password reset) than to general read routes, they are the routes most valuable to an attacker attempting to guess credentials.

```
Without rate limiting:
attacker tries 100,000 password guesses per minute against /auth/login

With rate limiting (10 per 15 min):
attacker gets 10 attempts, then blocked, brute-forcing becomes impractical
```

## SQL injection, and why Prisma mostly handles it

SQL injection happens when untrusted input is inserted directly into a SQL query string, letting an attacker change the query's actual meaning.

```ts
// vulnerable, hand-written SQL string concatenation
const query = `SELECT * FROM users WHERE email = '${email}'`;
// if email = "' OR '1'='1", the query becomes:
// SELECT * FROM users WHERE email = '' OR '1'='1'   <- matches every row
```

Prisma's normal query methods (`findMany`, `where`, and so on) parameterize values automatically, values are sent separately from the query structure, never concatenated into it. This is covered in more depth in [Raw SQL Escape Hatch](../5%20Postgres%20and%20Prisma/7%20Raw%20SQL%20Escape%20Hatch.md) (Phase 2 notes), the risk reappears specifically with `$queryRawUnsafe`, avoided by default.

```ts
// safe, Prisma parameterizes this automatically
await prisma.user.findUnique({ where: { email } });
```

## XSS awareness, briefly

Cross-site scripting means an attacker gets malicious JavaScript to run inside another user's browser, usually by getting unescaped user input rendered as HTML.

```
Attacker submits a comment: <script>stealCookies()</script>
If rendered as raw HTML by the frontend, this script actually runs
in every other visitor's browser who views that comment
```

This is primarily a frontend rendering concern (React escapes content by default, which already protects you in most cases), but the backend has a role too: never trust that data you return is automatically safe just because it came from your own database, it was still originally supplied by a user at some point.

📌 For AlgoRift specifically, submitted code is stored and displayed, exactly the kind of user-generated content that needs careful rendering on the frontend side, never executed or rendered as raw HTML.

## Secrets hygiene, a recap

Already covered in [Env Vars and Config](../4%20Express%20Fundamentals/5%20Env%20Vars%20and%20Config.md) (Phase 1 notes), worth restating as part of the Phase 3 security pass:

| Rule | Why |
|---|---|
| Never commit `.env` | Secrets in git history are permanent, even after deletion |
| Never log secrets (passwords, tokens, `JWT_SECRET`) | Logs are stored, backed up and often viewed by more people than the database |
| Use different secrets for dev and production | A leaked dev secret should never compromise production |
| Rotate secrets that may have leaked | A committed-then-removed secret should be treated as compromised, generate a new one |

## Putting it together: securing the auth routes

```ts
import { Router } from "express";
import rateLimit from "express-rate-limit";

const authLimiter = rateLimit({ windowMs: 15 * 60 * 1000, max: 10 });

const router = Router();

router.post("/register", authLimiter, validateBody(RegisterSchema), authController.register);
router.post("/login", authLimiter, validateBody(LoginSchema), authController.login);

export default router;
```

One route now has: rate limiting (against brute force), schema validation (against malformed/malicious input), and, inside the controller, password hashing plus safe, Prisma-parameterized database queries. Each concern from this Phase 3 folder stacks together into one properly defended route.

## A quick threat checklist for a route like this

| Threat | Defense already in place | From file |
|---|---|---|
| Brute-force login attempts | Rate limiting | This file |
| Malformed/malicious request bodies | Zod validation | [Validation with Zod](0%20Validation%20with%20Zod.md) |
| Leaked passwords from a data breach | bcrypt hashing | [Password Hashing](1%20Password%20Hashing.md) |
| Forged/tampered tokens | JWT signature verification | [JWT in Practice](3%20JWT%20in%20Practice.md) |
| Acting as another user | Auth middleware + ownership checks | [Auth Middleware](4%20Auth%20Middleware%20and%20Route%20Protection.md) and [Ownership](5%20Ownership%20and%20Authorization%20Checks.md) |
| Cross-origin abuse from arbitrary websites | Explicit CORS origin list | [CORS](6%20CORS.md) |
| SQL injection | Prisma's parameterized queries | Phase 2, [Raw SQL Escape Hatch](../5%20Postgres%20and%20Prisma/7%20Raw%20SQL%20Escape%20Hatch.md) |

## Key takeaways

- Rate limiting, applied especially to auth routes, makes brute-force credential guessing impractical rather than merely inconvenient.
- Prisma's normal query methods protect against SQL injection automatically, the risk only reappears if you reach for `$queryRawUnsafe`.
- XSS is mostly a frontend rendering concern, but backend-stored, user-supplied content (like submitted code) should never be assumed safe to render as raw HTML.
- A genuinely secure route stacks several small defenses together (rate limit, validation, hashing, auth, ownership, CORS), no single one covers everything alone.
