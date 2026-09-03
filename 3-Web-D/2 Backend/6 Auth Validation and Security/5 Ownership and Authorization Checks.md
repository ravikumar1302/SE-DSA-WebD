# Ownership and Authorization Checks

`requireAuth` (previous file) answers "who is this?". It does not answer "is this specific action allowed for this specific user?", that is authorization, and it needs its own check, separate from authentication.

## The scenario

```
User #42 is logged in (requireAuth confirms this)
User #42 tries to DELETE submission #7

Is submission #7 actually owned by user #42?
   yes -> allow, 204
   no  -> 403 Forbidden, this is not their data
```

A valid, working token proves identity. It says nothing about whether this particular user is allowed to touch this particular resource.

## Tying data to its owner

The `Submission` model needs a `userId` foreign key, so ownership can actually be checked.

```prisma
model Submission {
  id        Int      @id @default(autoincrement())
  code      String
  status    String
  userId    Int
  problemId Int

  user      User     @relation(fields: [userId], references: [id])
  problem   Problem  @relation(fields: [problemId], references: [id])
}
```

When a submission is created, it is stamped with the authenticated user's id, taken from `req.userId`, never from the request body (a client could put any `userId` they want in the body, only the verified token is trustworthy).

```ts
async create(req: Request, res: Response) {
  const userId = req.userId!;
  const submission = await submissionService.create(userId, req.body);
  res.status(201).json(submission);
}
```

```ts
async create(userId: number, data: { problemId: number; code: string }) {
  return prisma.submission.create({
    data: { ...data, userId, status: "pending" },
  });
}
```

## Checking ownership before a destructive action

```ts
async function deleteSubmission(userId: number, submissionId: number) {
  const submission = await prisma.submission.findUnique({ where: { id: submissionId } });

  if (!submission) {
    throw new NotFoundError("Submission not found");
  }

  if (submission.userId !== userId) {
    throw new ForbiddenError("You do not own this submission");
  }

  return prisma.submission.delete({ where: { id: submissionId } });
}
```

```ts
class ForbiddenError extends AppError {
  constructor(message = "Forbidden") {
    super(403, message);
  }
}
```

## The correct order of checks

```
1. Does the resource exist at all?          -> if not, 404
2. Does the current user own/control it?    -> if not, 403
3. Perform the action
```

⚠️ **Pitfall**: checking ownership before checking existence can leak information. If a `404` and a `403` are distinguishable, an attacker can probe ids to learn which ones exist versus which ones exist but belong to someone else. Some systems deliberately return `404` for both cases to avoid leaking existence, a judgment call depending on how sensitive the resource is. For AlgoRift's submissions, returning the correct, distinct code (`404` then `403`) is a reasonable default, matching the roadmap's own checklist.

## Ownership as its own reusable middleware (optional pattern)

For routes where the resource id is in the URL, ownership checking can be pulled out into middleware too, keeping controllers focused purely on the action itself.

```ts
function requireSubmissionOwnership() {
  return async (req: Request, res: Response, next: NextFunction) => {
    const submissionId = Number(req.params.id);
    const submission = await prisma.submission.findUnique({ where: { id: submissionId } });

    if (!submission) {
      next(new NotFoundError("Submission not found"));
      return;
    }
    if (submission.userId !== req.userId) {
      next(new ForbiddenError("You do not own this submission"));
      return;
    }

    next();
  };
}
```

```ts
router.delete("/:id", requireAuth, requireSubmissionOwnership(), submissionsController.delete);
```

The controller's `delete` method can now assume ownership has already been verified, it only needs to perform the deletion.

## AuthN vs AuthZ, one more time, in code

| Step | Middleware | Answers |
|---|---|---|
| 1 | `requireAuth` | "Is there a valid, logged-in user at all?" (401 if not) |
| 2 | `requireSubmissionOwnership` | "Does that user own this specific resource?" (403 if not) |

These stack, in order, in the same middleware pipeline covered in Phase 1.

```
request
   |
requireAuth ---------> 401 if not logged in
   |
requireSubmissionOwnership ---------> 403 if not the owner
   |
controller handler
```

## Beyond simple ownership: roles

Ownership ("is this yours") is one form of authorization. A second common form is role-based: "is this user an admin". AlgoRift's roadmap does not require this in Phase 3, but the shape is worth knowing.

```ts
function requireRole(role: string) {
  return (req: Request, res: Response, next: NextFunction) => {
    if (req.userRole !== role) {
      next(new ForbiddenError(`Requires ${role} role`));
      return;
    }
    next();
  };
}

router.delete("/problems/:id", requireAuth, requireRole("admin"), problemsController.delete);
```

Same shape as ownership checking, a different condition being checked.

## Key takeaways

- Authentication (`requireAuth`) proves identity. Authorization (ownership/role checks) proves permission for a specific action, they are separate checks, both needed.
- Always take the acting user's id from the verified token (`req.userId`), never from the request body, the body is client-controlled and cannot be trusted for identity.
- Check existence first (404), then ownership (403), a request for a resource that does not exist should never leak whether it belongs to someone else.
- Ownership and role checks can be pulled into their own reusable middleware, keeping controllers focused only on the actual action.
