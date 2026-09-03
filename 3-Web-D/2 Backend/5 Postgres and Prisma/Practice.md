# Practice: Postgres and Prisma

These convert the in-memory API from the previous phase into a real database-backed one.

---

### 1. Model one table, migrate it

Create a Neon project, connect it, model `Problem` in `schema.prisma` and run the first migration.

**Done when**: the table exists, visible in `npx prisma studio`, and a migration folder was created in your repo.

---

### 2. Swap the array for the database

Rewrite the `problems` service to use Prisma, leaving routes and controllers unchanged.

**Hint**: every method becomes `async`, and every caller needs `await`.

**Done when**: data survives a server restart, and the routes file was not touched at all.

---

### 3. Handle "not found" correctly for each method

`findUnique` returns null on no match, `update` and `delete` throw.

**Done when**: requesting, updating and deleting a nonexistent id all return 404, not 500.

---

### 4. Add a one-to-many relation

Add `Submission`, related to `Problem`, and migrate.

**Done when**: creating a submission for a nonexistent problem is rejected by the database, not just by your code.

---

### 5. Add a many-to-many relation

Add `Tag`, related to `Problem` both ways.

**Hint**: try the implicit version first, and be able to say what an explicit join table would give you instead.

**Done when**: one problem can carry several tags, and one tag applies to several problems.

---

### 6. Fetch related data in one query

Return a problem together with its tags and its five most recent submissions.

**Done when**: it is a single query with `include`, not a loop that queries per row.

---

### 7. Create the N+1 problem, then fix it

Deliberately fetch all problems, then loop and query submissions for each. Count the queries. Then rewrite it with `include`.

**Done when**: you can state the query count before and after, and explain why the difference grows with the row count.

---

### 8. Filter, sort and paginate

Add `?difficulty=`, `?sort=`, `?page=` and `?limit=` to the problems list.

**Done when**: `limit` is capped at a maximum, and all of it happens in the query, not in JavaScript afterward.

---

### 9. Justify one index

Add an index to a column you actually filter or sort by, and write one sentence in the schema comment explaining why that column and not another.

**Done when**: you can also name a column you deliberately did not index, and why.

---

### 10. Write one migration that changes an existing table

Add a field to a table that already has rows, and migrate it.

**Done when**: existing rows survive, and you understand what happened to them for the new column.

---

## Stretch

Write the same "problems with tag names" query twice, once with Prisma's query API and once with `$queryRaw`. Compare readability and typing, then decide which you would keep and why.
