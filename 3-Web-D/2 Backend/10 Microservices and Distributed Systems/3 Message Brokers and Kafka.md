# Message Brokers and Kafka

📌 Lighter reference notes, matching Phase 7's "know it exists" philosophy. [`03-architecture.md`](../0%20Concepts/03-architecture.md) covers message queues and brokers conceptually as the plumbing under event-driven architecture, this file focuses on Kafka specifically and how it differs from the queue you already know.

## You already know the basic idea

[Background Jobs and Queues](../9%20Advanced%20Topics/1%20Background%20Jobs%20and%20Queues.md) (Phase 6 notes) covered a queue (BullMQ, Redis-backed): your API adds a job, one worker picks it up and processes it. A message broker generalizes this same idea to many services, publishing and subscribing to events, not just one API handing work to one type of worker.

```
Simple queue (Phase 6):
API -----> queue -----> one worker type, processes jobs

Message broker (Kafka):
Service A -----> publishes an event ("submission accepted")
                        |
          ┌─────────────┼─────────────┐
          v              v              v
   Leaderboard      Email          Analytics
   service updates  service sends  service records
   the ranking       a notification the event
```

The key difference: one event can have **many** independent subscribers, each reacting to it in their own way, without the publisher knowing or caring who is listening.

## Why this matters specifically for microservices

Once a system is split into several services (previous file), they need to communicate. Direct network calls between them (service A calls service B's API directly) work, but tightly couple them, if service B is slow or down, service A's request hangs or fails too. A message broker decouples this: service A publishes an event and moves on immediately, whichever services care about that event process it independently, on their own time.

```
Direct call (tightly coupled):        Through a broker (decoupled):
A calls B's API directly               A publishes an event, done
A waits for B's response               B, C, D each independently
If B is down, A's request fails        consume the event whenever
                                        they are ready, A never waits
```

## What makes Kafka specifically different from a simple queue

| | Simple queue (BullMQ/Redis) | Kafka |
|---|---|---|
| Typical scale | One app, moderate throughput | Very high throughput, many services, many events per second |
| Message history | Usually consumed once, then gone | Events are retained (a durable log), can be replayed or re-read |
| Number of independent consumers per message | Usually one worker type processes each job | Many different services can independently subscribe to the same event stream |
| Setup complexity | Low, a Redis instance is enough | Meaningfully higher, its own cluster, its own operational concerns |
| Right scale for | A single app's background work (AlgoRift's code execution, Phase 6) | Coordinating many services at real scale |

📌 The trap named directly in the roadmap: adding a message broker for a problem a simple queue already solves. AlgoRift's actual async need (running submitted code without blocking a request) is exactly a simple-queue problem, Kafka would be meaningfully more infrastructure than the problem calls for.

## The core Kafka vocabulary, for recognition

```
Topic     - a named stream of events, e.g. "submission-events"
Producer  - a service that publishes events onto a topic
Consumer  - a service that reads events from a topic
Broker    - the Kafka server(s) that store and route events between producers and consumers
```

```ts
// producer, conceptual shape
await kafkaProducer.send({
  topic: "submission-events",
  messages: [{ value: JSON.stringify({ submissionId: 42, status: "accepted" }) }],
});

// consumer, conceptual shape, in a different service entirely
kafkaConsumer.on("submission-events", (event) => {
  updateLeaderboardCache(event.userId); // reacts independently, on its own schedule
});
```

## When this would actually become relevant to AlgoRift

Only if AlgoRift genuinely split into several independent services (previous file) that each needed to react to the same events (a submission being accepted mattering to a leaderboard service, a notifications service and an analytics service, all separately) at a scale where a simple Redis-backed queue's throughput and lack of message replay became a real, felt limitation. Nothing on your actual roadmap reaches that point.

## Key takeaways

- A message broker lets one event have many independent subscribers, decoupling services from needing to call each other directly and wait on the response.
- Kafka specifically adds durable, replayable event history and very high throughput, real capability, at real added operational cost, over a simple queue.
- The queue you already know (BullMQ/Redis, Phase 6) is the correct scale of tool for AlgoRift's actual async need, running submitted code without blocking a request.
- This becomes relevant only in a genuinely multi-service system reacting to shared events at real scale, worth recognizing the shape without treating it as a missing piece of AlgoRift today.
