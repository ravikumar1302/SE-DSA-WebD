# Password Hashing

## Never store passwords in plaintext

If a database is ever leaked or breached, plaintext passwords hand an attacker every user's real password directly, and since many people reuse passwords across sites, the damage spreads far beyond just your app.

```
users table (WRONG, never do this)
┌────┬───────────────────┬────────────┐
│ id │ email             │ password   │
├────┼───────────────────┼────────────┤
│ 1  │ ravi@example.com  │ hunter22   │  <- readable by anyone with DB access
└────┴───────────────────┴────────────┘
```

## Hashing, not encrypting

Encryption is reversible, if you have the key, you can turn ciphertext back into the original value. Hashing is one-way, there is no key that turns a hash back into the original password.

```
Encryption:  password  --(key)-->  ciphertext  --(same key)-->  password   (reversible)
Hashing:     password  --(hash function)-->  hash               (not reversible)
```

You never need to "read back" a user's password, you only ever need to check whether a given attempt matches. Hashing is the correct tool for exactly this reason.

## How login actually works with hashing

```
Registration:
  user submits password "hunter22"
  server computes hash("hunter22") = "a3f5...c92"
  server stores "a3f5...c92" in the database, never the real password

Login:
  user submits password "hunter22" again
  server computes hash("hunter22") = "a3f5...c92"
  server compares this new hash to the stored one
  match -> login succeeds
```

The server never stores, and never needs, the real password after the moment it is hashed.

## Salting

Hashing the same password always produces the same hash. This is a problem: if two users happen to pick the same password, their stored hashes would be identical, and an attacker with a precomputed table of common password hashes (a "rainbow table") could look up matches instantly.

A **salt** is random data added to the password before hashing, unique per user, so identical passwords produce completely different stored hashes.

```
User A: hash("hunter22" + saltA) = "x9f2...a1"
User B: hash("hunter22" + saltB) = "k4m8...q7"
```

Modern hashing libraries (bcrypt, argon2) generate and store the salt automatically as part of the resulting hash string, you do not manage salts by hand.

## Hashing with bcrypt

```bash
npm install bcrypt
npm install -D @types/bcrypt
```

```ts
import bcrypt from "bcrypt";

const SALT_ROUNDS = 10;

async function hashPassword(plainPassword: string): Promise<string> {
  return bcrypt.hash(plainPassword, SALT_ROUNDS);
}

async function verifyPassword(plainPassword: string, hash: string): Promise<boolean> {
  return bcrypt.compare(plainPassword, hash);
}
```

`SALT_ROUNDS` controls how computationally expensive the hash is to compute. Higher is slower but more resistant to brute-force attempts. `10` is a reasonable, common default.

```ts
const hashed = await hashPassword("hunter22");
// "$2b$10$N9qo8uLOickgx2ZMRZoMy..."  (the salt is embedded inside this string)

const isValid = await verifyPassword("hunter22", hashed);
// true

const isValid2 = await verifyPassword("wrongpassword", hashed);
// false
```

`bcrypt.compare` internally re-derives the salt from the stored hash, hashes the attempted password with that same salt and compares the results, you never do this comparison manually.

## Using it in registration

```ts
async function register(email: string, plainPassword: string) {
  const existing = await prisma.user.findUnique({ where: { email } });
  if (existing) {
    throw new AppError(400, "Email already registered");
  }

  const passwordHash = await hashPassword(plainPassword);

  return prisma.user.create({
    data: { email, password: passwordHash },
  });
}
```

⚠️ **Pitfall**: never log the plain password, anywhere, even temporarily during debugging. Logs are often stored, backed up and viewed by more people than the database itself.

## bcrypt vs argon2

| | bcrypt | argon2 |
|---|---|---|
| Age | Older, extremely well established | Newer, won a password-hashing competition in 2015 |
| Resistance to specialized hardware attacks (GPU cracking) | Good | Better, designed specifically against this |
| Ecosystem/library maturity in Node | Very mature, widely used | Mature, growing adoption |
| Roadmap's recommendation | Either is fine to learn the concept with, bcrypt has more tutorials/examples | A reasonable upgrade later, once the concept is solid |

📌 The specific library matters far less than the underlying idea: never store plaintext, always hash with a salted, purpose-built algorithm, never a generic hash like plain SHA-256 (too fast, making brute-force attempts cheap).

## Why not a plain hash function like SHA-256

```ts
import crypto from "crypto";
const hash = crypto.createHash("sha256").update(password).digest("hex"); // WRONG for passwords
```

SHA-256 is designed to be fast, useful for checking file integrity, wrong property for passwords. A fast hash lets an attacker with a leaked database try billions of guesses per second. bcrypt and argon2 are deliberately slow, by design, making large-scale guessing impractical.

## Key takeaways

- Never store plaintext passwords, hash them, hashing is one-way, unlike encryption.
- A salt (unique random data per password) prevents identical passwords from producing identical stored hashes, bcrypt/argon2 handle this automatically.
- `bcrypt.hash` on registration, `bcrypt.compare` on login, never manually compare a plain password against a stored hash yourself.
- Never use a fast general-purpose hash (like plain SHA-256) for passwords, purpose-built slow algorithms (bcrypt, argon2) are what make brute-force attacks impractical.
