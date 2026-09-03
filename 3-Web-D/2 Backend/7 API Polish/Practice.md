# Practice: API Polish

Short phase, short list. These are about consistency across everything already built, not new features.

---

### 1. Audit what you currently return

List every endpoint and the exact shape it returns today.

**Done when**: you can point at two routes whose shapes disagree, without opening the code again.

---

### 2. Apply one success envelope everywhere

Wrap every successful response in the same outer shape.

**Hint**: a small `sendSuccess(res, data, status)` helper keeps it honest.

**Done when**: no controller builds the envelope by hand, and every route goes through the helper.

---

### 3. Apply one error envelope everywhere

Make the central error handler emit the matching failure shape.

**Done when**: a 404, a 400 validation failure and an unexpected 500 all come back in the same structure.

---

### 4. Type the envelope

Define `ApiResponse<T>` and use it for at least one endpoint end to end.

**Done when**: checking `success` narrows the type correctly on the consuming side.

---

### 5. Validate query parameters

Use Zod with coercion for `page`, `limit`, `sort` and a filter, with defaults and a maximum limit.

**Done when**: `?page=abc` is rejected cleanly, and `?limit=99999` is silently capped rather than obeyed.

---

### 6. Restrict sortable fields

Make `sort` an explicit allowlist rather than any string.

**Done when**: `?sort=password` is rejected before it ever reaches the database query.

---

### 7. Return pagination metadata

Add total count and total pages alongside the items.

**Hint**: `Promise.all` for the rows and the count, so they run together.

**Done when**: a frontend could render page numbers using only the response, with no extra request.

---

### 8. Build the leaderboard the wrong way first

Fetch every accepted submission and rank users in JavaScript. Note how many rows crossed the network.

**Done when**: it works, and you can describe exactly why it will not survive growth.

---

### 9. Then build it correctly

Rewrite it with `groupBy`, ordering by the count, paginated.

**Done when**: ranking happens entirely in the database, and the response includes the rank number.

---

### 10. Verify the whole surface

Walk every endpoint with curl and confirm shape, status code and pagination behavior.

**Done when**: nothing surprises you, which is the actual point of this phase.

---

## Stretch

Write the response shapes as a short document a frontend developer could build against without reading your source. If that document is hard to write, the API is not consistent yet.
