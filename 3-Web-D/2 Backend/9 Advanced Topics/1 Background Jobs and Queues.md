# Background Jobs and Queues

📌 Lighter reference notes, matching Phase 6's "add only when needed" philosophy.

## The problem

Some work is too slow to do inside a normal request/response cycle. If `POST /submissions` had to actually run the submitted code, wait for it to finish and only then respond, a slow or stuck submission would leave the client hanging, and tie up your server the whole time.

```
Without a queue:
POST /submissions -> [runs code, takes 8 seconds] -> response
                       client waits the whole 8 seconds, blocking the request

With a queue:
POST /submissions -> [add job to queue] -> response immediately ("pending")
                       a separate worker picks up the job later, runs it, updates status
```

## The pattern

```
Your API                Queue (Redis-backed, often via BullMQ)          Worker process
   |                            |                                            |
   |--- add job "run submission 42" -->                                     |
   |<-- responds "pending" immediately --                                    |
                                 |                                            |
                                 |----- worker picks up the job ------------>|
                                                                              | runs the code
                                                                              | updates Submission.status
```

Your API and the worker can even be separate running processes (or separate parts of Phase 5's deployment), the queue is what connects them without either needing to know about the other directly.

| | Handling it inline (in the request) | Handling it via a queue |
|---|---|---|
| Response time | As slow as the work itself | Immediate, "pending" |
| A slow or stuck task | Blocks the request, the client waits | Never blocks the request, runs separately |
| Retrying on failure | Manual, awkward mid-request | The queue can retry the job on its own |
| Best for | Fast, reliable work (milliseconds) | Slow or unreliable work (seconds or more) |
| Added complexity | None | A worker process, a queue connection |

## When to reach for this

- Running submitted code (AlgoRift's actual use case, exactly the kind of slow, potentially unreliable work that should never block a request).
- Sending emails.
- Generating reports, image processing, any task measured in seconds rather than milliseconds.

📌 If a task reliably finishes in under roughly 100ms, a queue is unneeded complexity. Reach for one specifically when a task is slow, unreliable or both.

## A minimal shape with BullMQ

```bash
npm install bullmq
```

```ts
import { Queue, Worker } from "bullmq";

const submissionQueue = new Queue("submissions", { connection: { url: process.env.REDIS_URL } });

// adding a job, from your API route
async function queueSubmission(submissionId: number) {
  await submissionQueue.add("run", { submissionId });
}
```

```ts
// a separate worker process, run independently of your API
new Worker("submissions", async (job) => {
  const { submissionId } = job.data;
  const result = await runCode(submissionId); // the actual slow work
  await prisma.submission.update({
    where: { id: submissionId },
    data: { status: result.passed ? "accepted" : "failed" },
  });
}, { connection: { url: process.env.REDIS_URL } });
```

The API route becomes fast and simple, it just queues the job and responds immediately.

```ts
async function create(req: Request, res: Response) {
  const submission = await submissionService.create(req.userId!, req.body); // status: "pending"
  await queueSubmission(submission.id);
  sendSuccess(res, submission, 201);
}
```

## Client polling or checking status later

Since the response no longer includes the final result, the client checks back.

```
GET /submissions/42
{ "success": true, "data": { "id": 42, "status": "pending" } }
... (later)
GET /submissions/42
{ "success": true, "data": { "id": 42, "status": "accepted" } }
```

This is also exactly the situation [WebSockets and Realtime](3%20WebSockets%20and%20Realtime.md) (next file) can improve on, pushing the status update to the client instead of the client repeatedly asking.

## Key takeaways

- Queues decouple "accept the request fast" from "do the slow work eventually," a worker process handles jobs independently of the API responding to users.
- Use one for genuinely slow or unreliable work (running code, sending emails), not for anything that already finishes quickly.
- The API's job becomes "queue it and respond immediately," the actual result becomes available later, checked by polling or, more smoothly, pushed via WebSockets.
