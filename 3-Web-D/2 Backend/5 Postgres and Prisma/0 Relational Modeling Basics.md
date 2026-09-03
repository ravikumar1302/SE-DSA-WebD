# Relational Modeling Basics

Phase 1 stored `problems` in a plain array. That data disappears every time the server restarts, and nothing stops duplicate or inconsistent entries. Phase 2 replaces the array with a real relational database: PostgreSQL. Before writing any Prisma code, it helps to understand how relational data is actually structured. [`05-databases-and-storage.md`](../0%20Concepts/05-databases-and-storage.md) covers the theory (SQL vs NoSQL, ACID, CAP), this file focuses on the practical modeling you will do for AlgoRift.

## Tables, rows and columns

A relational database stores data in tables, each shaped like a spreadsheet.

```
Problem table
┌────┬────────────┬────────────┐
│ id │ title      │ difficulty │
├────┼────────────┼────────────┤
│ 1  │ Two Sum    │ easy       │
│ 2  │ Add Digits │ easy       │
└────┴────────────┴────────────┘
```

Each row is one record. Each column has a fixed type (`id` is always a number, `title` is always text).

## Primary keys

A primary key uniquely identifies one row in a table. No two rows can share the same primary key value.

```
id (primary key) | title
1                 | Two Sum
2                 | Add Digits
```

In almost every table you build, `id` is the primary key, usually an auto-incrementing number.

## Foreign keys

A foreign key is a column in one table that points to the primary key of another table. This is how tables connect to each other.

```
Submission table
┌────┬──────────┬───────────┐
│ id │ status   │ problemId │  <- foreign key, points to Problem.id
├────┼──────────┼───────────┤
│ 1  │ accepted │ 1         │
│ 2  │ failed   │ 1         │
│ 3  │ accepted │ 2         │
└────┴──────────┴───────────┘
```

`problemId` in the `Submission` table matches an `id` in the `Problem` table. This is how the database knows "submission 1 belongs to problem 1", without repeating the whole problem's data inside every submission row.

## The three relationship types

### One-to-one

Each row in table A matches exactly one row in table B, and vice versa. Less common in everyday apps.

```
User ──── one ──── Profile
(one user has exactly one profile, one profile belongs to exactly one user)
```

### One-to-many

One row in table A can relate to many rows in table B, but each row in table B relates back to only one row in table A.

```
Problem (1) ──────< Submission (many)
"one problem has many submissions, each submission belongs to one problem"
```

This is the most common relationship in real apps. In AlgoRift: one `Problem` has many `Submission`s, one `User` has many `Submission`s.

### Many-to-many

Rows in table A can relate to many rows in table B, and rows in table B can relate to many rows in table A.

```
Problem (many) ──────< >────── Tag (many)
"one problem can have many tags, one tag can apply to many problems"
```

Relational databases cannot represent many-to-many directly with a single foreign key, since a foreign key can only point to one row. It needs a third table in between, called a **join table**.

```
Problem table          ProblemTag table (join table)         Tag table
┌────┬─────────┐        ┌───────────┬────────┐                ┌────┬───────┐
│ id │ title   │        │ problemId │ tagId  │                │ id │ name  │
├────┼─────────┤        ├───────────┼────────┤                ├────┼───────┤
│ 1  │ Two Sum │        │ 1         │ 1      │                │ 1  │ Array │
│ 2  │ ...     │        │ 1         │ 2      │                │ 2  │ Hash  │
└────┴─────────┘        │ 2         │ 1      │                └────┴───────┘
                         └───────────┴────────┘
```

Problem 1 has tags 1 and 2. Tag 1 applies to problems 1 and 2. Each row in `ProblemTag` is just a pairing, with its own foreign keys pointing to both sides.

## AlgoRift's data model, in plain terms

| Table | Relationship |
|---|---|
| `User` → `Submission` | one-to-many, one user has many submissions |
| `Problem` → `Submission` | one-to-many, one problem has many submissions |
| `Problem` ↔ `Tag` | many-to-many, through a `ProblemTag` join table |

```
User ──1:many──> Submission <──many:1── Problem ──many:many──> Tag
```

This is exactly the shape described in the "Data model to build" section of the roadmap's Phase 2. The next files in this folder cover how to describe this shape to Prisma, and how Prisma turns it into real database tables.

## Why relational, not NoSQL, for this project

The roadmap's default advice (also in [`05-databases-and-storage.md`](../0%20Concepts/05-databases-and-storage.md)) is to start with PostgreSQL unless there is a specific reason not to. AlgoRift's data is naturally relational: problems have many tags, tags apply to many problems, submissions clearly belong to one problem and one user. Modeling this in a document database (like MongoDB) would mean either duplicating data across documents or manually managing references yourself, work a relational database already does correctly out of the box.

## Key takeaways

- A primary key uniquely identifies a row. A foreign key in one table points to the primary key of another, this is how tables connect.
- One-to-many is the most common relationship: one parent row, many child rows, each child pointing back to one parent.
- Many-to-many needs a join table in between, since a single foreign key can only point to one row.
- AlgoRift needs one-to-many (`Problem`/`User` → `Submission`) and many-to-many (`Problem` ↔ `Tag`), covering both patterns you will meet in almost every real backend project.
