# 07 - Security

The moment your backend is on the internet, it's under attack - automated bots probe every public server constantly. Security isn't a feature you add at the end; it's a mindset you build in from the start. This chapter covers the essential defensive concepts every backend engineer must own.

💡 **The core mindset - never trust the client.** Anything from outside your server (request bodies, headers, query params, uploaded files, even data from other services) is *potentially hostile* until validated. Every input is guilty until proven innocent. Most vulnerabilities trace back to trusting input that shouldn't have been trusted.

---

## Part A - Authentication vs Authorization (the foundation)

These two get confused constantly. Keep them straight:

- **Authentication (AuthN)** - *Who are you?* Verifying identity (login).
- **Authorization (AuthZ)** - *What are you allowed to do?* Checking permissions.

💡 You authenticate **once** (prove identity), then authorize **every action** (can *this* user do *this* thing?). An admin and a regular user may both be authenticated; authorization is what stops the regular user from deleting others' data.

⚠️ **Pitfall - broken access control:** authenticating users but forgetting to authorize actions. Classic bug: `GET /orders/456` returns the order *without* checking it belongs to the logged-in user - so anyone can read anyone's orders by changing the number (an "IDOR" - Insecure Direct Object Reference). **Always check ownership/permission on every protected resource.**

---

## Part B - Handling passwords & credentials

### Never store passwords in plaintext. Ever.
If your DB leaks (they do leak), plaintext passwords hand attackers every account - and users reuse passwords across sites.

### Hash, don't encrypt
- **Encryption** is reversible (you can decrypt with a key). Wrong for passwords.
- **Hashing** is one-way - you can't get the password back from the hash. On login, you hash the attempt and compare hashes.
- Use a **slow, salted** password hash designed for this: **bcrypt, argon2, scrypt**. Their slowness is *intentional* - it makes brute-forcing expensive.

### Salting
A **salt** is random data added to each password before hashing, so identical passwords produce different hashes. 💡 Defeats "rainbow tables" (precomputed hash lookups) and hides the fact that two users share a password. Good hash functions (bcrypt/argon2) handle salting for you.

📌 **Rule:** never hand-roll password hashing with plain SHA-256/MD5 - those are fast (bad for passwords) and unsalted. Use bcrypt/argon2 via a trusted library.

---

## Part C - Sessions, Tokens and OAuth

How do you stay logged in across requests (HTTP is stateless)?

### Session-based auth (stateful)
Server creates a **session**, stores it (in memory/Redis/DB) and gives the client a **session ID** in a cookie. Each request sends the cookie; the server looks up the session.
- ✅ Easy to revoke (delete the session), server controls everything
- ❌ Server must store session state - a scaling consideration (needs shared session store when horizontal - file 04)

### Token-based auth (stateless) - JWT
Server issues a signed **JWT (JSON Web Token)** on login. The client sends it (usually in an `Authorization: Bearer <token>` header) with each request. The server **verifies the signature** - no lookup needed.
- A JWT has three parts: **header.payload.signature**. The signature proves it wasn't tampered with.
- ✅ Stateless - any server can verify without shared storage; great for horizontal scaling and APIs
- ❌ **Hard to revoke** before expiry (it's valid until it expires) - mitigate with short lifetimes + refresh tokens
- ⚠️ **The payload is signed, not encrypted** - anyone can read it (base64). Never put secrets in a JWT.

⚖️ **Sessions vs JWT:**

| | Sessions | JWT |
|---|---|---|
| State | Server stores it | Stateless |
| Revocation | Easy | Hard (until expiry) |
| Scaling | Needs shared store | Scales freely |
| Best for | Traditional web apps | APIs, SPAs, mobile, microservices |

📌 Neither is universally "better" - pick per use case. Common pattern: short-lived JWT **access token** + longer-lived **refresh token** (which can be revoked).

### OAuth 2.0 & "Log in with Google"
**OAuth 2.0** is a framework for **delegated authorization** - letting an app access resources on your behalf *without* your password. It's what powers "Sign in with Google/GitHub." 💡 You never give the third-party app your Google password; Google issues it a scoped token. (**OpenID Connect** is a thin identity layer on top of OAuth for authentication specifically.)

---

## Part D - The OWASP Top 10 (the canonical threat list)

**OWASP** is a nonprofit that publishes the most critical web security risks. Every backend dev should know these categories. The greatest hits:

### 1. Injection (SQL injection, etc.)
Attacker sneaks malicious code into an input that gets executed. Classic: an input like `'; DROP TABLE users;--` concatenated into a SQL string.
- **Defense:** **parameterized queries / prepared statements** (never build queries by string-concatenating user input). ORMs and query builders do this for you - a big reason to use them. Validate/escape all input.

### 2. Broken Authentication
Weak login, guessable sessions, no brute-force protection, tokens that never expire.
- **Defense:** strong hashing, rate-limit logins, secure session/token handling, MFA where possible.

### 3. Sensitive Data Exposure
Leaking data by not encrypting it in transit or at rest, or returning too much in API responses.
- **Defense:** **HTTPS/TLS everywhere** (encrypt in transit), encrypt sensitive data at rest, never return fields like password hashes (use DTOs - file 02).

### 4. Broken Access Control
The IDOR/authorization gaps from Part A. Consistently the *most common* real-world vulnerability.
- **Defense:** check permissions on every protected action; deny by default.

### 5. Security Misconfiguration
Default passwords, verbose error messages leaking internals, debug mode in production, unnecessary open ports, permissive CORS.
- **Defense:** harden defaults, hide internal errors from users, least-privilege everything.

### 6. Cross-Site Scripting (XSS)
Attacker injects malicious JavaScript that runs in *other users'* browsers (e.g., a comment containing a `<script>`).
- **Defense:** escape/sanitize output, set a Content Security Policy. (More a frontend concern, but the backend must sanitize stored input.)

### 7. Cross-Site Request Forgery (CSRF)
Tricks a logged-in user's browser into making an unwanted request using their cookies.
- **Defense:** CSRF tokens, `SameSite` cookies. (Mostly affects cookie-based auth.)

### 8. Using Components with Known Vulnerabilities
Your dependencies have bugs. An outdated library with a known exploit is an open door.
- **Defense:** keep dependencies updated, scan them (`npm audit`, Dependabot, Snyk).

### 9. Insufficient Logging & Monitoring
If you can't see attacks, you can't respond. Breaches go undetected for months.
- **Defense:** log security events, monitor, alert on anomalies (file 09).

### 10. Server-Side Request Forgery (SSRF)
Tricking your server into making requests to internal systems it shouldn't.
- **Defense:** validate/allowlist URLs your server fetches.

---

## Part E - Encryption: in transit and at rest

- **In transit** - data moving over the network. Protect with **TLS/HTTPS** (the "S" in HTTPS). Non-negotiable; use it for *everything*, even internal traffic where feasible. TLS certificates are free (Let's Encrypt) and usually auto-managed by your host.
- **At rest** - data stored on disk (DB, backups, files). Encrypt sensitive data so a stolen disk/backup is useless. Most managed databases and object stores offer encryption-at-rest by default.

**Symmetric vs asymmetric (the basics):**
- **Symmetric** - one shared key encrypts and decrypts (fast; used for bulk data).
- **Asymmetric** - a public/private key pair (public encrypts, only private decrypts; used for key exchange and signatures). TLS uses asymmetric to safely establish a symmetric session key.

**Hashing vs encryption vs encoding - don't confuse them:**
| | Purpose | Reversible? |
|---|---|---|
| **Encoding** (base64) | Format/transport data | Yes (no security!) |
| **Encryption** | Confidentiality | Yes, with key |
| **Hashing** | Integrity / password storage | No (one-way) |

⚠️ Base64 is **not** security - it's just encoding. Anyone can decode it.

---

## Part F - Secrets management

Your app needs secrets: DB passwords, API keys, JWT signing keys.

- **Never hardcode secrets** in source code, and **never commit them** to git (bots scan public repos for leaked keys within *seconds*).
- Use **environment variables** (`.env` locally, kept out of git via `.gitignore`; real secrets set in your host's dashboard).
- For teams/production, use a **secrets manager** - AWS Secrets Manager, HashiCorp Vault, Doppler - which stores, rotates and audits access to secrets.

⚠️ **Pitfall:** committing a `.env` with real keys "just this once." Assume any secret pushed to git is compromised forever - rotate it immediately.

---

## Part G - Defensive habits that prevent whole classes of bugs

- **Input validation** - validate everything at the boundary (type, length, format, range). Reject bad input early. (Zod/Pydantic.)
- **Least privilege** - every user, service, DB account and token gets the *minimum* access it needs. A compromised low-privilege account does limited damage.
- **Rate limiting** - cap request rates to blunt brute-force and abuse (file 06).
- **Fail securely** - on error, deny access; don't "fail open." And don't leak stack traces/internal details in error responses.
- **Defense in depth** - layer defenses; don't rely on a single control. If one fails, others still protect you.
- **Keep dependencies patched** - automate updates and vulnerability scanning.
- **HTTPS everywhere** - always.
- **Principle of secure defaults** - the safe option should be the default; make people opt *into* risk, not out of it.

---

## Key takeaways

- **Never trust input.** Validate everything at the boundary.
- **AuthN (who) ≠ AuthZ (what).** Check permissions on *every* protected action - broken access control is the #1 real-world bug.
- **Hash passwords** with bcrypt/argon2 (salted, slow) - never plaintext, never plain SHA/MD5.
- Know **sessions vs JWT** tradeoffs and **OAuth** for delegated login.
- Internalize the **OWASP Top 10**, especially injection, broken access control and misconfiguration.
- **Encrypt in transit (TLS) and at rest**; know hashing ≠ encryption ≠ encoding.
- **Never commit secrets**; use env vars / secret managers.
- Practice **least privilege, defense in depth, secure defaults.**

---

## Where this shows up in the build

| Idea here | Where it becomes real |
|---|---|
| Authentication versus authorization | [AuthN vs AuthZ and Session vs Token Auth](../6%20Auth%20Validation%20and%20Security/2%20AuthN%20vs%20AuthZ%20and%20Session%20vs%20Token%20Auth.md) |
| Hashing and salting passwords | [Password Hashing](../6%20Auth%20Validation%20and%20Security/1%20Password%20Hashing.md) |
| Tokens, signed but not encrypted | [JWT in Practice](../6%20Auth%20Validation%20and%20Security/3%20JWT%20in%20Practice.md) |
| Broken access control | [Ownership and Authorization Checks](../6%20Auth%20Validation%20and%20Security/5%20Ownership%20and%20Authorization%20Checks.md) |
| Injection, and how an ORM prevents it | [Raw SQL Escape Hatch](../5%20Postgres%20and%20Prisma/7%20Raw%20SQL%20Escape%20Hatch.md) |
| Secrets management | [Env Vars and Config](../4%20Express%20Fundamentals/5%20Env%20Vars%20and%20Config.md) |
| Encryption in transit | [HTTP vs HTTPS](../4%20Express%20Fundamentals/9%20HTTP%20vs%20HTTPS.md) |
| Cross-origin rules | [CORS](../6%20Auth%20Validation%20and%20Security/6%20CORS.md) |

➡️ Next: [`08-testing.md`](08-testing.md) - proving your code (and your security) actually works.
