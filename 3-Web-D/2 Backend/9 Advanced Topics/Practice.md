# Practice: Advanced Topics

Unlike the earlier phases, do **not** work through these in order. Each one is meant to be done at the moment its problem actually appears in the project. Doing them early is exactly the trap this phase warns about.

---

### 1. Cache something expensive

**Trigger**: the leaderboard query feels slow, or you notice it recomputing constantly.

Cache the result in Redis with a short expiry, serving from cache when present.

**Done when**: repeated requests hit the database once per expiry window, not once per request.

---

### 2. Invalidate a cache deliberately

**Trigger**: cached data feels stale in a way users would notice.

Clear the cached key when the underlying data changes.

**Done when**: an accepted submission is reflected immediately, not after the expiry.

---

### 3. Move slow work off the request

**Trigger**: a request takes seconds because it is doing real work inline.

Queue the job, respond immediately with a pending status, update it when the worker finishes.

**Done when**: the endpoint responds in milliseconds, and status changes later without any request being held open.

---

### 4. Handle a failed job

**Trigger**: a queued job throws.

Decide what happens: retry, mark failed, alert.

**Done when**: a failing job cannot silently disappear, and its state is visible in the database.

---

### 5. Accept a file upload

**Trigger**: a feature genuinely needs an image or attachment.

Upload to object storage, store only the URL in Postgres.

**Done when**: the database holds a link, never file bytes, and the file is retrievable from its URL.

---

### 6. Replace polling with a push

**Trigger**: the frontend is polling an endpoint on a timer.

Open a WebSocket connection and push the update when it happens.

**Done when**: the client updates within a moment of the change, with no repeated requests in the network tab.

---

### 7. Write your first unit test

**Trigger**: the app is stable and you are afraid to refactor something.

Test one service function with no database and no Express.

**Done when**: it runs in milliseconds, and fails correctly when you deliberately break the function.

---

### 8. Write your first integration test

**Trigger**: a bug appeared that a unit test could not have caught.

Test one route end to end against a separate test database.

**Done when**: it exercises the real route, real service and real database, without touching your development data.

---

### 9. Test a past bug

**Trigger**: you just fixed something.

Write the test that would have caught it.

**Done when**: reverting the fix makes the test fail.

---

### 10. Containerize the app

**Trigger**: you need reproducible environments, or a platform that expects a container.

Write a `Dockerfile`, build it, run it locally.

**Done when**: the container runs the app correctly with environment variables passed in, no local Node setup required.

---

## Stretch

For each item above that you have not done, write one sentence describing the symptom that would make you reach for it. If you cannot describe the symptom, you are not ready for that tool yet, which is the correct answer.
