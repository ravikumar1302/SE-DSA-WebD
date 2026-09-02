# 05 - Databases & Storage

Data is the heart of most backends. This chapter covers how databases are categorized, the guarantees they make, how to make them fast and correct, the role of ORMs and the different kinds of *cloud storage* (which beginners often conflate with databases).

---

## Part A - The big split: SQL vs NoSQL

### SQL (Relational) databases
Data lives in **tables** (rows and columns) with a fixed **schema**. Tables relate via keys. You query with **SQL**. Examples: **PostgreSQL, MySQL**, SQL Server, SQLite, Oracle.

- ✅ **Structure & integrity** - schema enforces valid data; relationships are first-class
- ✅ **Powerful queries** - JOINs, aggregations, ad-hoc questions
- ✅ **ACID transactions** - strong correctness guarantees (below)
- ✅ **Mature, battle-tested, universal**
- ❌ Rigid schema (changes need migrations)
- ❌ Horizontal scaling of writes is harder (traditionally)

### NoSQL databases
An umbrella for non-relational stores, usually **flexible schema** and built for **horizontal scale**. Four main types:

| Type | Shape | Examples | Good for |
|---|---|---|---|
| **Document** | JSON-like documents | MongoDB, CouchDB | Flexible/nested data, rapid iteration |
| **Key-Value** | Simple key → value | Redis, DynamoDB | Caching, sessions, ultra-fast lookups |
| **Column-family** | Rows with dynamic columns | Cassandra, HBase | Massive write-heavy, time-series |
| **Graph** | Nodes + edges | Neo4j | Relationships-first (social, recommendations) |

- ✅ **Flexible schema** - store varied/evolving shapes without migrations
- ✅ **Horizontal scaling** - many were built to shard from day one
- ✅ **Fast for simple access patterns** at huge scale
- ❌ **Weaker guarantees** (often eventual consistency)
- ❌ **Limited/awkward JOINs** - you often duplicate data (denormalize) instead
- ❌ Easy to model badly if your access patterns change

⚖️ **SQL vs NoSQL - how to choose:**

| Question | Lean SQL | Lean NoSQL |
|---|---|---|
| Is the data highly relational? | Yes | No |
| Do you need complex queries/JOINs? | Yes | No |
| Do you need strong consistency (money!)? | Yes | Tolerable to relax |
| Is the schema unknown/rapidly changing? | No | Yes |
| Do you need extreme horizontal write scale? | Harder | Built for it |

📌 **Default advice:** **start with a relational DB (PostgreSQL).** It's flexible enough for the vast majority of apps, enforces correctness while you're still learning your domain and Postgres even handles JSON well when you need flexibility. Reach for NoSQL for a *specific* reason (caching → Redis, huge flexible documents → Mongo, graph problems → Neo4j), not as a default.

⚠️ **Pitfall:** choosing NoSQL because it sounds modern/"scales," then desperately missing JOINs and transactions. Most apps aren't at the scale where NoSQL's tradeoffs pay off.

---

## Part B - ACID, BASE, and the CAP theorem

### ACID - the guarantees of (most) relational transactions
A **transaction** is a group of operations that must succeed or fail *together*.
- **A**tomicity - all steps happen, or none do (no half-finished transfers)
- **C**onsistency - the DB moves from one valid state to another (rules/constraints hold)
- **I**solation - concurrent transactions don't corrupt each other
- **D**urability - once committed, it survives crashes

💡 **Why it matters:** imagine a bank transfer - debit one account, credit another. Without atomicity, a crash mid-way could debit without crediting. ACID makes "money can't vanish" a *guarantee*, not a hope. This is why financial/critical data → relational.

### BASE - the NoSQL philosophy (the tradeoff)
- **B**asically **A**vailable - the system stays responsive
- **S**oft state - data may be in flux
- **E**ventual consistency - replicas converge to the same value *eventually*, not instantly

💡 Many distributed NoSQL systems relax strict consistency to gain availability and scale. That's fine for a like-count; not fine for a bank balance.

### CAP Theorem
In a distributed system, when a **network partition** (P - nodes can't talk) happens, you can guarantee only **one** of:
- **C**onsistency - every read gets the latest write (or an error)
- **A**vailability - every request gets *a* response (maybe stale)

You can't have both *during a partition*. So distributed databases are effectively **CP** (prefer correctness, may reject requests) or **AP** (prefer uptime, may serve stale data).

💡 **Why it matters:** it forces an honest choice. A payment system picks **CP** (better to fail than be wrong). A social feed picks **AP** (better to show a slightly stale feed than an error). Understanding CAP explains *why* distributed databases behave the way they do.

---

## Part C - Making databases correct and fast

### Schema & data modeling
Design your tables/relationships to reflect the real domain. Relationships:
- **One-to-one** (a user ↔ one profile)
- **One-to-many** (a user → many orders)
- **Many-to-many** (students ↔ courses, via a join table)

### Normalization vs Denormalization
- **Normalization** - organize data to eliminate redundancy; each fact stored *once*. Prevents update anomalies (change an address in one place, not fifty). Standard for relational.
- **Denormalization** - deliberately duplicate data to avoid expensive JOINs and speed up reads. A performance tradeoff.

📌 **Normalize by default; denormalize deliberately** when a proven read-performance need justifies the duplication. Don't pre-denormalize.

### Indexes - the #1 performance tool
An **index** is a separate data structure (usually a B-tree) that lets the DB *find* rows fast instead of scanning the whole table - like a book's index vs reading every page.

💡 **Why:** a query filtering `WHERE email = ?` on a million-row table scans all million without an index; with one, it jumps straight there. Most "the database is slow" issues are missing indexes on filtered/joined/sorted columns.

⚠️ **The tradeoff:** indexes speed up *reads* but slow down *writes* (every insert/update must also update the index) and use storage. So index the columns you **filter, join or sort by** - not every column.

### Transactions in practice
Wrap multi-step operations that must be all-or-nothing in a transaction. (Transfer money, place an order that decrements stock + creates a record + charges a card.) If any step fails, the whole thing rolls back.

### N+1 query problem (a classic beginner trap)
You fetch a list of 100 users (1 query), then loop and fetch each user's posts (100 more queries) = 101 queries. Fix by fetching related data in one query (a JOIN, or your ORM's "eager loading"/`include`). ⚠️ Watch for this - it's the most common ORM performance bug.

---

## Part D - ORMs (Object-Relational Mappers)

An **ORM** lets you work with the database using your programming language's objects/methods instead of writing raw SQL. `user.save()` instead of `INSERT INTO users...`. Examples: Prisma, TypeORM, Sequelize (Node); SQLAlchemy, Django ORM (Python); Hibernate (Java).

⚖️ **ORM vs Query Builder vs Raw SQL:**

| Approach | What it is | Pros | Cons |
|---|---|---|---|
| **Raw SQL** | You write SQL strings | Full power & control, transparent | Verbose, manual mapping, injection risk if careless |
| **Query Builder** | Programmatic SQL (e.g. Knex) | Composable, safer, still SQL-ish | Less abstraction than ORM |
| **ORM** | Objects ↔ tables | Fast to write, type-safe, handles mapping/migrations, less boilerplate | Hides SQL (can generate slow queries), learning curve, "leaky" for complex needs |

**ORM benefits:**
- ✅ Productivity - less boilerplate, no manual row→object mapping
- ✅ Safety - parameterizes queries (mitigates SQL injection)
- ✅ Type safety (esp. Prisma with TS) - DB shape checked at compile time
- ✅ Migrations - versioned schema changes
- ✅ Portability - (somewhat) DB-agnostic

**ORM downsides:**
- ❌ Can generate inefficient queries (the N+1 trap, over-fetching)
- ❌ Hides what's really happening - you must still understand SQL underneath
- ❌ Complex/analytical queries are often clearer in raw SQL

📌 **Mature stance:** use an ORM for the 90% of ordinary CRUD (it's faster and safer), but **learn SQL** so you understand what it generates and can drop to raw SQL for the hard 10%. Every good ORM has a raw-SQL escape hatch - use it without guilt. Don't let the ORM prevent you from understanding your own database.

---

## Part E - Cloud storage types (databases are NOT the only storage)

A frequent beginner confusion: "where do I put uploaded files/images?" **Not in your database.** Different data needs different storage. The main cloud storage categories:

### 1. Object storage
Stores files as **objects** (the file + metadata + a unique key) in a flat namespace ("buckets"). Accessed over HTTP.
- **Examples:** Amazon **S3**, Google Cloud Storage, Azure Blob Storage, Cloudflare R2.
- **Best for:** images, videos, PDFs, backups, static assets, user uploads - basically **any file (BLOB)**.
- ✅ Cheap, virtually infinite scale, durable, HTTP-accessible, integrates with CDNs.
- ❌ Not a filesystem (no in-place edits/appends - you replace whole objects), higher latency than block.
- 📌 **This is where uploaded files belong**, with the URL/key stored in your database.

### 2. Block storage
Raw storage volumes attached to a server, like a virtual hard drive. The OS formats it with a filesystem.
- **Examples:** Amazon EBS, Google Persistent Disk, Azure Disk.
- **Best for:** the disk your VM/database runs on - low-latency, high-performance, frequent read/write.
- ✅ Fast, supports in-place modification, acts like a real disk.
- ❌ Usually attaches to one machine at a time, more expensive, you manage it.

### 3. File storage
A shared filesystem (folders/files) accessible by **multiple** servers over the network (NFS/SMB).
- **Examples:** Amazon EFS, Azure Files.
- **Best for:** shared files across several machines, legacy apps expecting a filesystem.
- ✅ Familiar folder structure, shareable across servers.
- ❌ More expensive, can be a scaling/performance bottleneck.

⚖️ **Which storage when:**

| Need | Use |
|---|---|
| Structured, queryable, relational data | **Database (SQL/NoSQL)** |
| User uploads, images, videos, backups | **Object storage (S3-style)** |
| A disk for a server or database | **Block storage** |
| A filesystem shared by many servers | **File storage** |
| Fast ephemeral cache/session data | **In-memory store (Redis)** |

⚠️ **Pitfall:** storing large files as binary blobs *inside* your relational DB. It bloats the DB, slows backups and wastes expensive storage. Put files in object storage; store the *link* in the DB.

---

## Part F - Backups, replication, and safety

- **Backups** - regular copies to restore from disaster. Untested backups aren't backups - verify you can *restore*.
- **Point-in-time recovery** - restore to a specific moment (undo an accidental mass-delete).
- **Replication** - live copies for read-scaling and failover (file 04).
- **Migrations** - version-controlled, incremental schema changes so your DB structure evolves safely alongside code (never hand-edit production schema).

📌 The day you'll be *very* glad you set up backups is the day someone runs `DELETE` without a `WHERE`. Set them up before you need them.

---

## Key takeaways

- **SQL (Postgres) by default**; reach for a specific **NoSQL** for a specific reason.
- **ACID** = strong correctness (use for money/critical). **BASE/eventual consistency** = scale/availability tradeoff. **CAP** forces a C-or-A choice under partition.
- **Indexes** are your #1 speed tool (index what you filter/join/sort). Watch for **N+1** queries.
- Use an **ORM** for productivity/safety but **learn SQL underneath**; keep the raw-SQL escape hatch.
- **Files go in object storage (S3), not the database** - different storage types exist for different jobs.
- **Back up and migrate** deliberately; test restores.

➡️ Next: [`06-apis.md`](06-apis.md) - how the outside world talks to your backend.
