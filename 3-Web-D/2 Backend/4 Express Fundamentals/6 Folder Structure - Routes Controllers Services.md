# Folder Structure: Routes, Controllers, Services

## Why not just put everything in one file

Early Express tutorials often put every route directly in `index.ts`.

```ts
app.get("/problems", (req, res) => {
  // fetch logic, filtering logic, response formatting, all mixed together
});

app.post("/problems", (req, res) => {
  // validation, saving, response, all mixed together
});
```

This works for a handful of routes. It breaks down fast once a project grows: files get huge, logic is duplicated across handlers and testing anything requires spinning up the whole Express app. This is exactly the coupling and cohesion problem covered in [`01-foundations.md`](../0%20Concepts/01-foundations.md), one file doing too many unrelated jobs.

## The three-layer split

```
Request
   |
   v
┌─────────────┐
│   Routes    │   URL + method  -->  which controller function handles it
└─────────────┘
   |
   v
┌─────────────┐
│ Controllers │   reads req, calls the right service, shapes the response
└─────────────┘
   |
   v
┌─────────────┐
│  Services   │   the actual business logic, talks to the database
└─────────────┘
```

| Layer | Job | Should know about |
|---|---|---|
| Routes | Map a URL + method to a controller function | Express only |
| Controllers | Read `req`, call the service, send `res` | `req`/`res`, not business logic details |
| Services | Actual logic: validation rules, calculations, database queries | Nothing about HTTP, `req` or `res` at all |

📌 **Rule of thumb**: if a service function needed `req` or `res` to work, that is a sign logic leaked into the wrong layer. Services should be callable and testable with plain function arguments, no Express involved.

## Folder layout

```
src/
├── routes/
│   └── problems.routes.ts
├── controllers/
│   └── problems.controller.ts
├── services/
│   └── problems.service.ts
└── index.ts
```

## Example: `problems.service.ts`

The service holds the actual logic and data access. For Phase 1, "data access" just means an in-memory array, it becomes real database queries once Prisma is introduced in Phase 2.

```ts
interface Problem {
  id: number;
  title: string;
  difficulty: "easy" | "medium" | "hard";
}

let problems: Problem[] = [];
let nextId = 1;

export const problemService = {
  getAll(): Problem[] {
    return problems;
  },

  getById(id: number): Problem | undefined {
    return problems.find((p) => p.id === id);
  },

  create(data: Omit<Problem, "id">): Problem {
    const problem: Problem = { id: nextId++, ...data };
    problems.push(problem);
    return problem;
  },

  update(id: number, data: Partial<Omit<Problem, "id">>): Problem | undefined {
    const problem = this.getById(id);
    if (!problem) return undefined;
    Object.assign(problem, data);
    return problem;
  },

  delete(id: number): boolean {
    const index = problems.findIndex((p) => p.id === id);
    if (index === -1) return false;
    problems.splice(index, 1);
    return true;
  },
};
```

Notice this file never imports Express, never sees `req` or `res`. It could be tested directly, or reused in a completely different context (a CLI tool, a background job), without any changes.

## Example: `problems.controller.ts`

The controller is the translator between HTTP and the service. It stays thin on purpose.

```ts
import { Request, Response } from "express";
import { problemService } from "../services/problems.service";

export const problemsController = {
  getAll(req: Request, res: Response) {
    const problems = problemService.getAll();
    res.status(200).json(problems);
  },

  getById(req: Request, res: Response) {
    const id = Number(req.params.id);
    const problem = problemService.getById(id);
    if (!problem) {
      res.status(404).json({ error: "Problem not found" });
      return;
    }
    res.status(200).json(problem);
  },

  create(req: Request, res: Response) {
    const problem = problemService.create(req.body);
    res.status(201).json(problem);
  },

  update(req: Request, res: Response) {
    const id = Number(req.params.id);
    const problem = problemService.update(id, req.body);
    if (!problem) {
      res.status(404).json({ error: "Problem not found" });
      return;
    }
    res.status(200).json(problem);
  },

  delete(req: Request, res: Response) {
    const id = Number(req.params.id);
    const deleted = problemService.delete(id);
    if (!deleted) {
      res.status(404).json({ error: "Problem not found" });
      return;
    }
    res.status(204).send();
  },
};
```

⚠️ **Pitfall**: a "fat controller" happens when business logic (filtering, calculations, validation rules) creeps into the controller instead of staying in the service. A good test: could you swap Express for a different framework by only rewriting the controllers and routes? If yes, the split is clean.

## Example: `problems.routes.ts`

```ts
import { Router } from "express";
import { problemsController } from "../controllers/problems.controller";

const router = Router();

router.get("/", problemsController.getAll);
router.get("/:id", problemsController.getById);
router.post("/", problemsController.create);
router.put("/:id", problemsController.update);
router.delete("/:id", problemsController.delete);

export default router;
```

`express.Router()` creates a mini, self-contained router that can be mounted onto the main app. It groups related routes together instead of registering every route directly on `app`.

## Mounting the router in `index.ts`

```ts
import express from "express";
import problemsRouter from "./routes/problems.routes";

const app = express();
app.use(express.json());

app.use("/problems", problemsRouter);

app.listen(3000);
```

`app.use("/problems", problemsRouter)` prefixes every route inside `problemsRouter` with `/problems`. So `router.get("/:id", ...)` actually becomes `GET /problems/:id` from the outside.

## Key takeaways

- Routes map URLs to controllers, controllers translate between HTTP and services, services hold the real logic. Each layer only knows about the one below it.
- Services should never import Express or reference `req`/`res`, this keeps them testable and reusable.
- `express.Router()` groups related routes into their own file, mounted onto the main app with a path prefix.
- This same structure carries forward unchanged into Phase 2, only the inside of the service functions changes, from array operations to Prisma queries.
