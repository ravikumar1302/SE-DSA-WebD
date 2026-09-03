# Building the Problems CRUD API

This file walks through Phase 1's actual deliverable end to end: a full, in-memory CRUD API for `problems`, matching the checklist in the roadmap. It pulls together everything from the earlier files in this folder into one working app.

## Goal

```
POST   /problems       -> create        -> 201
GET    /problems       -> list          -> 200
GET    /problems/:id   -> one, or 404
PUT    /problems/:id   -> update, or 404
DELETE /problems/:id   -> 204, or 404
```

## Final folder structure for this phase

```
src/
├── routes/
│   └── problems.routes.ts
├── controllers/
│   └── problems.controller.ts
├── services/
│   └── problems.service.ts
├── middleware/
│   ├── logger.ts
│   └── error-handler.ts
├── errors/
│   └── app-error.ts
└── index.ts
```

## `src/errors/app-error.ts`

```ts
export class AppError extends Error {
  constructor(public statusCode: number, message: string) {
    super(message);
  }
}

export class NotFoundError extends AppError {
  constructor(message = "Resource not found") {
    super(404, message);
  }
}
```

## `src/services/problems.service.ts`

```ts
export interface Problem {
  id: number;
  title: string;
  description: string;
  difficulty: "easy" | "medium" | "hard";
  createdAt: string;
}

type CreateProblemInput = Omit<Problem, "id" | "createdAt">;
type UpdateProblemInput = Partial<CreateProblemInput>;

let problems: Problem[] = [];
let nextId = 1;

export const problemService = {
  getAll(): Problem[] {
    return problems;
  },

  getById(id: number): Problem | undefined {
    return problems.find((p) => p.id === id);
  },

  create(data: CreateProblemInput): Problem {
    const problem: Problem = {
      id: nextId++,
      createdAt: new Date().toISOString(),
      ...data,
    };
    problems.push(problem);
    return problem;
  },

  update(id: number, data: UpdateProblemInput): Problem | undefined {
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

## `src/controllers/problems.controller.ts`

```ts
import { Request, Response } from "express";
import { problemService } from "../services/problems.service";
import { NotFoundError } from "../errors/app-error";

export const problemsController = {
  getAll(req: Request, res: Response) {
    res.status(200).json(problemService.getAll());
  },

  getById(req: Request, res: Response) {
    const id = Number(req.params.id);
    const problem = problemService.getById(id);
    if (!problem) throw new NotFoundError(`Problem ${id} not found`);
    res.status(200).json(problem);
  },

  create(req: Request, res: Response) {
    const problem = problemService.create(req.body);
    res.status(201).json(problem);
  },

  update(req: Request, res: Response) {
    const id = Number(req.params.id);
    const problem = problemService.update(id, req.body);
    if (!problem) throw new NotFoundError(`Problem ${id} not found`);
    res.status(200).json(problem);
  },

  delete(req: Request, res: Response) {
    const id = Number(req.params.id);
    const deleted = problemService.delete(id);
    if (!deleted) throw new NotFoundError(`Problem ${id} not found`);
    res.status(204).send();
  },
};
```

Notice controllers now `throw` instead of manually writing `res.status(404).json(...)` everywhere. The central error handler (next file section) turns thrown `AppError`s into the correct response automatically.

## `src/routes/problems.routes.ts`

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

## `src/middleware/logger.ts`

```ts
import { Request, Response, NextFunction } from "express";

export function logger(req: Request, res: Response, next: NextFunction) {
  console.log(`${req.method} ${req.url}`);
  next();
}
```

## `src/middleware/error-handler.ts`

```ts
import { Request, Response, NextFunction } from "express";
import { AppError } from "../errors/app-error";

export function errorHandler(err: Error, req: Request, res: Response, next: NextFunction) {
  if (err instanceof AppError) {
    res.status(err.statusCode).json({ error: err.message });
    return;
  }
  console.error(err);
  res.status(500).json({ error: "Internal server error" });
}
```

⚠️ Since controller functions here are synchronous (no `await`), a plain `throw` reaches Express's default error handling correctly without needing the `asyncHandler` wrapper from the earlier file. Once services start making real, awaited database calls in Phase 2, wrap async controller functions as covered there.

## `src/index.ts`, wiring it all together

```ts
import "dotenv/config";
import express from "express";
import problemsRouter from "./routes/problems.routes";
import { logger } from "./middleware/logger";
import { errorHandler } from "./middleware/error-handler";

const app = express();

app.use(express.json());
app.use(logger);

app.get("/health", (req, res) => {
  res.status(200).json({ status: "ok" });
});

app.use("/problems", problemsRouter);

app.use(errorHandler); // always last

const PORT = Number(process.env.PORT) || 3000;
app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
```

## Testing it manually

Using `curl`, or any REST client (Postman, Thunder Client):

```bash
# create
curl -X POST http://localhost:3000/problems \
  -H "Content-Type: application/json" \
  -d '{"title":"Two Sum","description":"...","difficulty":"easy"}'

# list
curl http://localhost:3000/problems

# get one
curl http://localhost:3000/problems/1

# update
curl -X PUT http://localhost:3000/problems/1 \
  -H "Content-Type: application/json" \
  -d '{"difficulty":"medium"}'

# delete
curl -X DELETE http://localhost:3000/problems/1

# not found case
curl http://localhost:3000/problems/999
```

| Request | Expected status |
|---|---|
| `POST /problems` with valid body | `201` |
| `GET /problems` | `200` |
| `GET /problems/1` (exists) | `200` |
| `GET /problems/999` (missing) | `404` |
| `PUT /problems/1` (exists) | `200` |
| `PUT /problems/999` (missing) | `404` |
| `DELETE /problems/1` (exists) | `204`, empty body |
| `DELETE /problems/999` (missing) | `404` |

## Done when

All five routes behave correctly, the code is split across `routes/`, `controllers/`, `services/`, `errors/` and `middleware/`, and every response uses the right status code, matching Phase 1 of the roadmap exactly. Data resets every time the server restarts, since it lives only in memory, that limitation is what Phase 2 (Postgres + Prisma) replaces next.

## Key takeaways

- This file is where every earlier concept in this folder (HTTP methods and status codes, middleware, centralized error handling, env vars, layered folder structure) combines into one real, working API.
- Throwing custom errors from controllers, caught once by a central handler, keeps every route handler short and consistent.
- The in-memory array is deliberately temporary. Its only job is to prove the request/response and layering pattern works, before adding the complexity of a real database.
