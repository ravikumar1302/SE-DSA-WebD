# JWT in Practice

## What is actually inside a JWT

A JWT (JSON Web Token) is a string made of three parts, separated by dots, each base64-encoded.

```
eyJhbGciOiJIUzI1NiJ9.eyJ1c2VySWQiOjQyfQ.4f3d9a...

  header       .        payload         .    signature
```

| Part | Contains | Example (decoded) |
|---|---|---|
| Header | Which algorithm was used | `{ "alg": "HS256" }` |
| Payload | The actual data (claims) | `{ "userId": 42, "exp": 1735689600 }` |
| Signature | Proof the token was not tampered with | A cryptographic signature over header + payload |

⚠️ **Critical**: the payload is only base64-encoded, not encrypted. Anyone can decode and read it (try pasting a JWT into jwt.io). **Never put secrets (passwords, credit card numbers) inside a JWT's payload.** The signature proves the token has not been altered, it does not hide what is inside.

## How the signature works

```
signature = sign(header + "." + payload, JWT_SECRET)
```

The server holds a secret key. When creating a token, it signs the header and payload with this secret. When verifying a token, it recomputes the signature using the same secret and checks it matches.

```
Client sends a tampered token (changed userId from 42 to 1)
      |
      v
Server recomputes the signature for the tampered payload
      |
      v
Recomputed signature does NOT match the token's original signature
      |
      v
Server rejects the token: invalid signature
```

Without knowing `JWT_SECRET`, nobody can produce a valid signature for a modified payload, this is what makes JWT trustworthy despite being readable.

## Installing and setting up

```bash
npm install jsonwebtoken
npm install -D @types/jsonwebtoken
```

```
# .env
JWT_SECRET=a-long-random-string-never-commit-this
```

⚠️ `JWT_SECRET` is exactly the kind of value covered in [Env Vars and Config](../4%20Express%20Fundamentals/5%20Env%20Vars%20and%20Config.md), never hardcoded, never committed, always read from `process.env`.

## Issuing a token, on login

```ts
import jwt from "jsonwebtoken";

function generateToken(userId: number): string {
  return jwt.sign(
    { userId },              // payload
    process.env.JWT_SECRET!,
    { expiresIn: "7d" }      // expiry
  );
}
```

```ts
async function login(email: string, plainPassword: string) {
  const user = await prisma.user.findUnique({ where: { email } });
  if (!user) throw new AppError(401, "Invalid credentials");

  const isValid = await verifyPassword(plainPassword, user.password);
  if (!isValid) throw new AppError(401, "Invalid credentials");

  const token = generateToken(user.id);
  return { token, user: { id: user.id, email: user.email } };
}
```

⚠️ **Pitfall**: returning the same error message ("Invalid credentials") whether the email does not exist or the password is wrong, is deliberate. Returning "email not found" vs "wrong password" separately tells an attacker which emails are registered in your system, a small but real information leak.

## Expiry

```ts
{ expiresIn: "7d" }   // 7 days
{ expiresIn: "1h" }   // 1 hour
{ expiresIn: "15m" }  // 15 minutes
```

`jsonwebtoken` automatically adds an `exp` claim to the payload based on this. A verified token past its expiry is rejected automatically.

📌 Shorter expiry is safer (a stolen token is useful for less time), but forces more frequent logins. A common real-world pattern (refresh tokens, covered later, "know it exists" for now) balances both, short-lived access tokens plus a longer-lived refresh mechanism.

## Verifying a token

```ts
function verifyToken(token: string): { userId: number } {
  return jwt.verify(token, process.env.JWT_SECRET!) as { userId: number };
}
```

`jwt.verify` throws if the signature is invalid or the token has expired.

```ts
try {
  const payload = verifyToken(token);
  // payload.userId is now trustworthy
} catch (err) {
  // invalid or expired token
}
```

## Where the client sends the token

The common convention is an `Authorization` header, using the `Bearer` scheme.

```
Authorization: Bearer eyJhbGciOiJIUzI1NiJ9.eyJ1c2VySWQiOjQyfQ.4f3d9a...
```

```ts
function getTokenFromHeader(req: Request): string | null {
  const header = req.headers.authorization; // "Bearer <token>"
  if (!header?.startsWith("Bearer ")) return null;
  return header.slice(7); // everything after "Bearer "
}
```

## A minimal login route, end to end

```ts
app.post("/auth/login", validateBody(LoginSchema), async (req, res) => {
  const { email, password } = req.body;
  const { token, user } = await authService.login(email, password);
  res.status(200).json({ token, user });
});
```

The next file covers the middleware that reads and verifies this token on protected routes.

## JWT vs session, at the code level

| | Session | JWT |
|---|---|---|
| What the server checks per request | Looks up a session ID in storage | Verifies a signature mathematically, no lookup |
| What the client stores | A session ID (usually a cookie, automatic) | The full token (usually sent manually in a header) |
| Immediate logout/revoke | Delete the session record | Not naturally possible, token remains valid until it expires |

## Key takeaways

- A JWT has three parts: header, payload and signature. The payload is readable by anyone, never put secrets inside it.
- The signature, made with a server-only secret, proves the token has not been tampered with, it does not hide the payload's contents.
- `jwt.sign` issues a token with an expiry, `jwt.verify` checks the signature and expiry, throwing if either fails.
- Tokens are conventionally sent as `Authorization: Bearer <token>`, read and verified by middleware on every protected route.
