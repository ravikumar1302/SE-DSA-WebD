# Where Data Lives in a Request

A single incoming request can carry data in four different places. Knowing which one to use, and where, is one of the most practical Express skills.

## The four locations

```
POST /problems/5/submissions?retry=true
Header: Authorization: Bearer abc123

Body:
{ "code": "print('hi')" }
```

| Location | In this example | Express access |
|---|---|---|
| Route params | `5` (the problem id) | `req.params.id` |
| Query params | `retry=true` | `req.query.retry` |
| Body | `{ "code": "print('hi')" }` | `req.body.code` |
| Headers | `Authorization: Bearer abc123` | `req.headers.authorization` |

## Route params

Part of the URL path itself, marked with `:` in the route definition. Used to identify **which specific resource** you mean.

```ts
app.get("/problems/:id", (req, res) => {
  const id = req.params.id;   // string, always a string, even if it looks like a number
  res.json({ id });
});
```

```
GET /problems/5   ->   req.params.id === "5"
```

⚠️ **Pitfall**: `req.params.id` is always a `string`, never a `number`, even for `/problems/5`. Convert it before using it as a number.

```ts
const id = Number(req.params.id);
if (Number.isNaN(id)) {
  res.status(400).json({ error: "Invalid id" });
  return;
}
```

Multiple params are allowed in one route:

```ts
app.get("/problems/:problemId/submissions/:submissionId", (req, res) => {
  const { problemId, submissionId } = req.params;
});
```

## Query params

The part of the URL after `?`, made of key-value pairs. Used for **optional** things: filtering, sorting, pagination, search terms.

```ts
app.get("/problems", (req, res) => {
  const difficulty = req.query.difficulty; // "easy" | undefined
  const page = req.query.page;             // string | undefined
});
```

```
GET /problems?difficulty=easy&page=2
req.query.difficulty === "easy"
req.query.page === "2"
```

Like params, query values are always strings (or `undefined` if not present). Convert types explicitly.

```ts
const page = Number(req.query.page) || 1;
const limit = Number(req.query.limit) || 10;
```

## Body

Data sent along with the request, used for `POST`, `PUT` and `PATCH`. This is the actual payload, the thing being created or updated.

```ts
app.post("/problems", (req, res) => {
  const { title, difficulty } = req.body;
});
```

Requires `app.use(express.json())` to be set up first (covered in the previous file), otherwise `req.body` is `undefined`.

## Headers

Metadata about the request itself, not the resource being requested. Common uses: authentication tokens, expected response format, custom client info.

```ts
app.get("/profile", (req, res) => {
  const token = req.headers.authorization; // "Bearer eyJhbGciOi..."
});
```

Header names are case-insensitive, Express automatically lowercases them, so always access them in lowercase: `req.headers.authorization`, not `req.headers.Authorization`.

## Choosing the right location

| Question | Answer | Location |
|---|---|---|
| Does this identify exactly one resource? | Yes | Route param |
| Is this optional, used to filter/sort/page a list? | Yes | Query param |
| Is this the actual data being created or changed? | Yes | Body |
| Is this about the request itself, not the resource? | Yes | Header |

### Example: designing a route

```
GET /problems/:id/submissions?status=accepted&page=2
```

- `:id` is a route param, since it identifies exactly one problem.
- `status` and `page` are query params, since they are optional filters on a list.

```
POST /problems/:id/submissions
Body: { "code": "...", "language": "python" }
```

- `:id` is still a route param.
- The submission content itself goes in the body, since it is the data being created, not an identifier or a filter.

## Summary table

| | Route params | Query params | Body | Headers |
|---|---|---|---|---|
| Used with | Any method | Mostly `GET` | `POST` / `PUT` / `PATCH` | Any method |
| Purpose | Identify a resource | Filter/sort/page | The actual payload | Metadata |
| Access in Express | `req.params` | `req.query` | `req.body` | `req.headers` |
| Type received | Always `string` | Always `string` or `undefined` | Whatever was parsed (usually an object) | Always `string` |

## Key takeaways

- Route params identify a specific resource, query params filter or shape a list, body carries the actual data, headers carry metadata.
- Params and query values always arrive as strings, convert them to numbers/booleans explicitly before using them.
- Choosing the wrong location for a piece of data (for example, putting a filter in the body of a `GET`) is a design mistake that makes an API awkward to use.
