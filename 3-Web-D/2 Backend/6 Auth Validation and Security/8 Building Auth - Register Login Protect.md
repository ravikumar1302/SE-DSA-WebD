# Building Auth: Register, Login, Protect

This file walks through Phase 3's full deliverable end to end, combining every file in this folder into a working, secure auth system for AlgoRift.

## The `User` model

```prisma
model User {
  id        Int          @id @default(autoincrement())
  email     String       @unique
  password  String       // stores the bcrypt hash, never plaintext
  createdAt DateTime     @default(now())
  submissions Submission[]
}

model Submission {
  id        Int      @id @default(autoincrement())
  code      String
  status    String
  createdAt DateTime @default(now())

  userId    Int
  user      User     @relation(fields: [userId], references: [id])

  problemId Int
  problem   Problem  @relation(fields: [problemId], references: [id])
}
```

```bash
npx prisma migrate dev --name add_user_and_submission_owner
```

## Zod schemas

```ts
// src/schemas/auth.schemas.ts
import { z } from "zod";

export const RegisterSchema = z.object({
  email: z.string().email(),
  password: z.string().min(8),
});

export const LoginSchema = z.object({
  email: z.string().email(),
  password: z.string().min(1),
});
```

## The auth service

```ts
// src/services/auth.service.ts
import bcrypt from "bcrypt";
import jwt from "jsonwebtoken";
import { prisma } from "../lib/prisma";
import { AppError } from "../errors/app-error";

const SALT_ROUNDS = 10;

export const authService = {
  async register(email: string, password: string) {
    const existing = await prisma.user.findUnique({ where: { email } });
    if (existing) throw new AppError(400, "Email already registered");

    const hashedPassword = await bcrypt.hash(password, SALT_ROUNDS);
    const user = await prisma.user.create({
      data: { email, password: hashedPassword },
    });

    return { id: user.id, email: user.email };
  },

  async login(email: string, password: string) {
    const user = await prisma.user.findUnique({ where: { email } });
    if (!user) throw new AppError(401, "Invalid credentials");

    const isValid = await bcrypt.compare(password, user.password);
    if (!isValid) throw new AppError(401, "Invalid credentials");

    const token = jwt.sign({ userId: user.id }, process.env.JWT_SECRET!, { expiresIn: "7d" });
    return { token, user: { id: user.id, email: user.email } };
  },
};
```

## The auth controller and routes

```ts
// src/controllers/auth.controller.ts
export const authController = {
  async register(req: Request, res: Response) {
    const user = await authService.register(req.body.email, req.body.password);
    res.status(201).json(user);
  },

  async login(req: Request, res: Response) {
    const result = await authService.login(req.body.email, req.body.password);
    res.status(200).json(result);
  },
};
```

```ts
// src/routes/auth.routes.ts
import { Router } from "express";
import rateLimit from "express-rate-limit";
import { authController } from "../controllers/auth.controller";
import { validateBody } from "../middleware/validate-body";
import { RegisterSchema, LoginSchema } from "../schemas/auth.schemas";
import { asyncHandler } from "../middleware/async-handler";

const authLimiter = rateLimit({ windowMs: 15 * 60 * 1000, max: 10 });
const router = Router();

router.post("/register", authLimiter, validateBody(RegisterSchema), asyncHandler(authController.register));
router.post("/login", authLimiter, validateBody(LoginSchema), asyncHandler(authController.login));

export default router;
```

## The auth middleware and typing

```ts
// src/middleware/require-auth.ts
export function requireAuth(req: Request, res: Response, next: NextFunction) {
  const header = req.headers.authorization;
  if (!header?.startsWith("Bearer ")) {
    res.status(401).json({ error: "Missing or invalid authorization header" });
    return;
  }

  try {
    const payload = jwt.verify(header.slice(7), process.env.JWT_SECRET!) as { userId: number };
    req.userId = payload.userId;
    next();
  } catch {
    res.status(401).json({ error: "Invalid or expired token" });
  }
}
```

```ts
// src/types/express.d.ts
declare global {
  namespace Express {
    interface Request {
      userId?: number;
    }
  }
}
export {};
```

## Protecting submission creation, and enforcing ownership

```ts
// src/services/submission.service.ts
export const submissionService = {
  async create(userId: number, data: { problemId: number; code: string }) {
    return prisma.submission.create({
      data: { ...data, userId, status: "pending" },
    });
  },

  async delete(userId: number, submissionId: number) {
    const submission = await prisma.submission.findUnique({ where: { id: submissionId } });
    if (!submission) throw new NotFoundError("Submission not found");
    if (submission.userId !== userId) throw new ForbiddenError("You do not own this submission");

    return prisma.submission.delete({ where: { id: submissionId } });
  },
};
```

```ts
// src/routes/submission.routes.ts
const router = Router();
router.use(requireAuth); // every route below requires a valid token

router.post("/", asyncHandler(submissionsController.create));
router.delete("/:id", asyncHandler(submissionsController.delete));

export default router;
```

## CORS, wired in `index.ts`

```ts
import cors from "cors";

const allowedOrigins = ["http://localhost:3001"]; // your Next.js frontend, in dev

app.use(cors({
  origin: (origin, callback) => {
    if (!origin || allowedOrigins.includes(origin)) callback(null, true);
    else callback(new Error("Not allowed by CORS"));
  },
  credentials: true,
}));
```

## Testing the full flow

```bash
# register
curl -X POST http://localhost:3000/auth/register \
  -H "Content-Type: application/json" \
  -d '{"email":"ravi@example.com","password":"hunter2222"}'

# login, capture the token
curl -X POST http://localhost:3000/auth/login \
  -H "Content-Type: application/json" \
  -d '{"email":"ravi@example.com","password":"hunter2222"}'
# response: { "token": "eyJhbGci...", "user": { "id": 1, "email": "..." } }

# create a submission with the token
curl -X POST http://localhost:3000/submissions \
  -H "Authorization: Bearer eyJhbGci..." \
  -H "Content-Type: application/json" \
  -d '{"problemId": 1, "code": "print(1)"}'

# without a token -> 401
curl -X POST http://localhost:3000/submissions -d '{}'

# deleting someone else's submission -> 403
curl -X DELETE http://localhost:3000/submissions/99 \
  -H "Authorization: Bearer <a different user's token>"
```

## Done when

A user can register, log in, get a token, create submissions tied to their account and is blocked (403) from touching others' data. Protected routes reject missing or invalid tokens (401), matching Phase 3 of the roadmap exactly.

## Key takeaways

- This file is the full stack of every earlier file here: Zod validation, bcrypt hashing, JWT issuing and verifying, auth middleware, ownership checks, CORS and rate limiting, working together on real routes.
- The identity used for every write (`userId`) always comes from the verified token, never from the request body, this is the core rule that makes ownership checks trustworthy.
- Consistent status codes (401 for "not logged in", 403 for "logged in but not allowed", 404 for "does not exist") make the whole API predictable and debuggable from the client side.
