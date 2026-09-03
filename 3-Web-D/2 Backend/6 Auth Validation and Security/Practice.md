# Practice: Auth, Validation and Security

This is the phase where mistakes are quiet rather than loud, so several of these are about spotting a flaw rather than adding a feature.

---

### 1. Validate one request body

Write a Zod schema for creating a problem, and reject invalid input with 400 plus useful details.

**Done when**: sending `{ "difficulty": "extreme" }` returns 400 naming the field, not a 500.

---

### 2. Make validation reusable

Turn that check into one `validateBody(schema)` middleware used by several routes.

**Done when**: adding validation to a new route is one line, and no controller calls `safeParse` itself.

---

### 3. Derive the type from the schema

Replace a hand-written request interface with `z.infer<typeof Schema>`.

**Done when**: changing the schema changes the type automatically, with nothing typed twice.

---

### 4. Hash a password properly

Add a `User` model, then register a user with a hashed password.

**Done when**: the stored value is a bcrypt hash, and the same password registered twice produces two different hashes.

---

### 5. Explain a design decision

Login returns "Invalid credentials" whether the email is unknown or the password is wrong.

**Done when**: you can explain in one sentence what an attacker learns if those two cases return different messages.

---

### 6. Issue and verify a token

Return a JWT on login, then verify it in middleware and attach the user id to the request.

**Hint**: `req.userId` needs declaration merging before TypeScript accepts it.

**Done when**: a missing token returns 401, a tampered token returns 401 and a valid one passes through.

---

### 7. Decode your own token

Paste a token you issued into a decoder, or decode it manually.

**Done when**: you can read the payload without the secret, and can say why that is expected rather than a bug.

---

### 8. Enforce ownership

Tie submissions to their creator, then block one user from deleting another user's submission.

**Done when**: the wrong user gets 403, a nonexistent id gets 404 and the checks happen in that order.

---

### 9. Find the flaw

```ts
async function createSubmission(req: Request, res: Response) {
  const submission = await prisma.submission.create({
    data: { code: req.body.code, userId: req.body.userId },
  });
  res.status(201).json(submission);
}
```

**Done when**: you can name the vulnerability, explain what an attacker would send and fix it in one line.

---

### 10. Lock down the edges

Add CORS with an explicit origin list and rate limiting on the auth routes.

**Done when**: a request from an unlisted origin is blocked in a browser, and repeated login attempts start returning 429.

---

## Stretch

Take any route you have written and list every way a hostile client could misuse it: missing fields, wrong types, oversized payloads, someone else's ids, repeated calls. Fix the ones that are real. This is threat modeling at the smallest useful scale.
