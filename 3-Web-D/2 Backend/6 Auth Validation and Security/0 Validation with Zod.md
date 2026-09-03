# Validation with Zod

## Why validation is not optional

TypeScript types disappear once your code compiles, they exist only to check your own code, not data arriving from outside it. A request body is just text sent by a client, TypeScript cannot verify it actually matches the shape you expect, only your own code deciding what to do with that data can.

```ts
interface CreateUserInput {
  email: string;
  password: string;
}

app.post("/register", (req: Request, res: Response) => {
  const body: CreateUserInput = req.body; // this is a lie, TypeScript trusts it blindly
  // if the client sent { email: 123, password: null }, this line does not catch it
});
```

⚠️ **Pitfall**: "the frontend already validates this" is not a reason to skip backend validation. Anyone can send a request directly with `curl`, Postman or a modified script, completely bypassing your frontend. The backend is the real boundary, it must never trust the client.

This is the "TypeScript types are compile-time only" mistake from the TypeScript notes, applied directly to real request data.

**The request flow with validation added:**

```
Request arrives
      |
      v
Does the body match the schema?
      |
   no  -----> respond 400, with a list of what was wrong, stop here
      |
   yes
      v
Route handler runs, using the validated, typed data
      |
      v
Response sent
```

Nothing after the schema check ever needs to guard against malformed input again, by the time a handler runs, the data is already known to be correct.

## What Zod is

Zod is a validation library. You describe the expected shape of data as a **schema**, Zod checks real data against it at runtime, and it can generate a matching TypeScript type automatically from that same schema. One definition, both runtime safety and compile-time types.

```bash
npm install zod
```

## A basic schema

```ts
import { z } from "zod";

const RegisterSchema = z.object({
  email: z.string().email(),
  password: z.string().min(8),
});
```

This describes: an object with an `email` field that must be a valid email string, and a `password` field that must be a string at least 8 characters long.

## Parsing data against a schema

```ts
const result = RegisterSchema.parse({ email: "ravi@example.com", password: "hunter22" });
// result is now typed AND validated
```

`parse` throws an error if the data does not match. `safeParse` does not throw, it returns an object describing success or failure instead, useful when you want to handle the failure yourself rather than relying on a thrown error.

```ts
const result = RegisterSchema.safeParse(req.body);

if (!result.success) {
  console.log(result.error.issues); // detailed list of what went wrong
} else {
  console.log(result.data); // the validated, typed data
}
```

## Deriving a TypeScript type from a schema

```ts
type RegisterInput = z.infer<typeof RegisterSchema>;
// equivalent to: { email: string; password: string }
```

This is the real benefit over writing a plain `interface`, the schema is the single source of truth, both the runtime check and the compile-time type come from the same definition, they cannot drift apart.

## Common Zod validators

| Validator | Checks | Example |
|---|---|---|
| `z.string()` | Value is a string | `z.string()` |
| `.email()` | Valid email format | `z.string().email()` |
| `.min(n)` / `.max(n)` | Minimum/maximum length (strings) or value (numbers) | `z.string().min(8)` |
| `z.number()` | Value is a number | `z.number().positive()` |
| `z.boolean()` | Value is a boolean | `z.boolean()` |
| `z.enum([...])` | Value is one of a fixed set | `z.enum(["easy", "medium", "hard"])` |
| `.optional()` | Field may be missing | `z.string().optional()` |
| `z.array(schema)` | Array where every item matches `schema` | `z.array(z.number())` |
| `.default(value)` | Fills in a value if the field is missing | `z.number().default(1)` |

## A real example: the AlgoRift `Problem` create schema

```ts
const CreateProblemSchema = z.object({
  title: z.string().min(1).max(200),
  description: z.string().min(1),
  difficulty: z.enum(["easy", "medium", "hard"]),
  tagIds: z.array(z.number()).optional(),
});

type CreateProblemInput = z.infer<typeof CreateProblemSchema>;
```

This single schema replaces the plain `interface CreateProblemInput` from earlier phases, and now actually enforces those rules at runtime too, not just at compile time in your editor.

## Using it in a route

```ts
app.post("/problems", (req: Request, res: Response) => {
  const result = CreateProblemSchema.safeParse(req.body);

  if (!result.success) {
    res.status(400).json({ error: "Invalid input", details: result.error.issues });
    return;
  }

  const problem = problemService.create(result.data); // result.data is fully typed and validated
  res.status(201).json(problem);
});
```

## Validation as its own middleware (cleaner, reused everywhere)

Repeating the same `safeParse` check in every route gets repetitive. A small generic middleware handles it once.

```ts
import { ZodSchema } from "zod";

function validateBody(schema: ZodSchema) {
  return (req: Request, res: Response, next: NextFunction) => {
    const result = schema.safeParse(req.body);
    if (!result.success) {
      res.status(400).json({ error: "Invalid input", details: result.error.issues });
      return;
    }
    req.body = result.data; // replace with the validated, typed version
    next();
  };
}
```

```ts
app.post("/problems", validateBody(CreateProblemSchema), (req, res) => {
  // req.body is guaranteed valid here, no need to check again
  const problem = problemService.create(req.body);
  res.status(201).json(problem);
});
```

This matches the generic `Repository<T>` pattern idea from the TypeScript notes, one reusable piece of middleware, parameterized by whichever schema a given route needs.

## Key takeaways

- TypeScript types check your own code, they cannot validate data coming from outside it, that needs a runtime check.
- Zod schemas validate real data at runtime and generate a matching TypeScript type from the same definition, avoiding drift between the two.
- `safeParse` is the right default in route handlers, it lets you return a clean `400` response instead of throwing.
- A generic `validateBody(schema)` middleware applies this pattern consistently across every route, instead of repeating the check by hand each time.
