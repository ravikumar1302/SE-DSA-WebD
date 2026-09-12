# Debugging Auth and Middleware Chains

Auth bugs are especially confusing because they often produce the same generic symptom, a 401 or 403, no matter what the actual underlying cause is. This file narrows down which of several possible causes is the real one.

## Step 1: is a token actually being sent

Before anything else, confirm the request is even carrying a token.

```ts
app.use((req, res, next) => {
  console.log("auth header:", req.headers.authorization);
  next();
});
```

If this logs `undefined`, the problem is entirely on the client, the frontend never attached the header, this rules out the entire backend auth flow as a cause and saves time debugging the wrong half of the system.

## Step 2: decode the token to see what is actually inside it

A JWT is not encrypted, only signed, its payload can be read by anyone, including you while debugging, without needing the secret.

```ts
import jwt from "jsonwebtoken";

const decoded = jwt.decode(token); // does NOT verify the signature, just reads the payload
console.log(decoded);
```

```
{ userId: 5, iat: 1704000000, exp: 1704003600 }
```

This confirms whether the token actually contains the `userId` your middleware expects, and whether `exp` (the expiry timestamp) has already passed. Pasting a token into [jwt.io](https://jwt.io) does the same thing visually, useful when debugging without wanting to write a throwaway script.

📌 **Important distinction**: `jwt.decode` reads the payload without checking the signature, `jwt.verify` checks the signature and throws if it does not match. Use `decode` purely to inspect contents while debugging, the real auth middleware must always use `verify`, decoding alone proves nothing about whether the token is genuine.

## Step 3: confirm the secret matches

A token signed with one `JWT_SECRET` fails `jwt.verify` against a different secret, even if the token itself is otherwise perfectly valid and unexpired. This commonly happens after a deploy if the environment variable was not set identically in the new environment, or was rotated without reissuing tokens. Logging (never the secret itself, only whether it is present) which environment is running helps rule this in or out.

```ts
console.log("JWT_SECRET is set:", Boolean(process.env.JWT_SECRET));
```

## Step 4: confirm middleware order

Covered generally in the previous file on Express debugging, worth restating specifically for auth: `requireAuth` must be registered before any route it should protect, and any route-specific middleware chain (`app.get("/admin", requireAuth, requireAdminRole, handler)`) runs strictly left to right. A `403` where a `401` was expected (or the reverse) often means two auth-related middleware functions are in the wrong order relative to each other.

```
requireAuth checks: is there a valid token at all           -> 401 if not
requireAdminRole checks: does this valid user have admin role -> 403 if not

If requireAdminRole runs BEFORE requireAuth, it reads req.userId
before requireAuth ever set it, likely undefined, likely wrong result
```

## Step 5: check what the middleware actually attached to `req`

TypeScript's declaration merging (covered in the Express Fundamentals notes) makes `req.userId` type-check, it does not guarantee the middleware actually ran and set it correctly on this specific request. Logging directly inside the protected route handler confirms.

```ts
app.get("/profile", requireAuth, (req, res) => {
  console.log("req.userId:", req.userId); // is it actually set, and to the right value
  // ...
});
```

## A quick diagnostic table

| Symptom | Check first |
|---|---|
| Every request gets 401, even with a token | Is the header actually reaching the server, step 1 |
| Token looks fine when decoded, still fails | Secret mismatch between signing and verifying, step 3 |
| 401 immediately after a token was issued | Check `exp` in the decoded payload, might already be expired |
| A route is reachable without auth at all | Middleware order, `requireAuth` registered after the route |
| `req.userId` is `undefined` inside the handler | The auth middleware for this exact route never ran, or ran but did not set it |

## Key takeaways

- Confirm a token is actually being sent before suspecting anything about how it is processed.
- `jwt.decode` reads a token's payload without checking its signature, useful purely for inspecting contents while debugging, never a substitute for `verify` in real auth logic.
- A secret mismatch between where a token was signed and where it is verified produces the same generic failure as an invalid token, worth checking explicitly.
- Middleware order bugs produce auth symptoms that look like logic bugs, always confirm registration order before assuming the logic itself is wrong.
