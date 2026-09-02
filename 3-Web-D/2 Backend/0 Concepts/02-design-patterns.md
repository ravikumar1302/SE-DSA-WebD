# 02 - Design Patterns

A **design pattern** is a named, reusable solution to a problem that shows up again and again. Patterns aren't code you copy - they're *templates* for how to structure code. Their real value is **shared vocabulary**: saying "use a Repository here" instantly communicates a whole design to another engineer.

💡 **Why they matter:** smart people already solved the common structural problems. Patterns save you from reinventing (often badly) and give teams a common language. But - patterns are tools, not goals. Forcing a pattern where it isn't needed is over-engineering (violates KISS/YAGNI from file 01).

The classic patterns come in three families: **Creational** (how objects are made), **Structural** (how objects are composed), **Behavioral** (how objects interact). Then there are **backend/architecture patterns** you'll use constantly. We'll cover the ones that actually earn their keep in backend work.

---

## Creational patterns - *how things get made*

### Singleton
Ensures a class has **exactly one instance**, shared everywhere.
- **Use:** a single DB connection pool, a config object, a logger.
- ⚠️ **Pitfall:** singletons are secretly global state - they make testing hard and hide dependencies. Use sparingly; often dependency injection is cleaner.

### Factory
A function/class whose job is to **create objects**, hiding the messy construction logic from the caller.
- **Use:** `createPaymentProcessor(type)` returns the right processor (Stripe, PayPal…) without the caller knowing how each is built.
- 💡 **Why:** centralizes creation logic (DRY) and lets you add new types without changing callers (Open/Closed).

### Builder
Constructs a complex object **step by step**, instead of a constructor with 12 arguments.
- **Use:** building a complicated query or a configured HTTP request piece by piece.
- 💡 Improves readability and avoids "which of these 12 args was which?"

---

## Structural patterns - *how things compose*

### Adapter
Wraps an incompatible interface so it fits what your code expects - a "translator."
- **Use:** you switch SMS providers; write an adapter so the new provider matches your existing `SmsSender` interface. The rest of your app doesn't change.
- 💡 This is Dependency Inversion in action - depend on your interface, adapt the outside world to it.

### Facade
A single simplified interface in front of a complicated subsystem.
- **Use:** an `OrderService.placeOrder()` that internally coordinates inventory, payment, shipping and email - callers see one clean method.
- 💡 Reduces coupling: callers depend on the simple facade, not the tangle behind it.

### Proxy
A stand-in that controls access to another object (for caching, lazy-loading, access control, logging).
- **Use:** a caching proxy that returns stored results before hitting the real (expensive) service.

### Decorator
Wraps an object to add behavior **without changing it**.
- **Use:** wrapping a request handler to add logging, then auth, then rate-limiting - each a layer. (This is the conceptual root of **middleware**, below.)

---

## Behavioral patterns - *how things interact*

### Strategy
Define a family of interchangeable algorithms and pick one at runtime.
- **Use:** different pricing strategies, sorting strategies or auth strategies selected by config/context.
- 💡 The clean alternative to a sprawling `if/else` or `switch` - add a new strategy without editing existing ones (Open/Closed again).

### Observer (Pub/Sub)
Objects (subscribers) register interest in an event; when it happens, they're all notified.
- **Use:** "when a user signs up" → send welcome email + create profile + log analytics, each an independent subscriber. The signup code doesn't know or care who's listening.
- 💡 Powerful for **decoupling** - the publisher and subscribers don't depend on each other. This is the seed of **event-driven architecture** (file 03).

### Command
Wrap a request/action as an object, so it can be queued, logged or undone.
- **Use:** job queues (each job is a command), undo systems.

### Iterator, State, Template Method, Chain of Responsibility
Worth knowing by name; you'll meet them, but they're lower-priority for backend beginners. **Chain of Responsibility** deserves a mention - a request passes along a chain of handlers until one handles it - because it's *exactly* how middleware pipelines work.

---

## The backend patterns you'll actually live in

These aren't from the classic "Gang of Four" book but are the daily bread of backend engineering.

### MVC (Model-View-Controller) and its API cousin
Separates concerns into:
- **Model** - data + business rules
- **View** - presentation (in APIs, this is often just JSON serialization)
- **Controller** - receives requests, coordinates, responds

💡 In pure-backend APIs you'll often see **Controller → Service → Repository** layering instead (see below), which is MVC's spirit adapted for APIs. It's Separation of Concerns made concrete.

### Repository pattern
An abstraction over data access. Your business logic asks a `UserRepository` for users and never touches SQL/ORM directly.

⚖️ **Why bother?**

| Without Repository | With Repository |
|---|---|
| Business logic littered with DB queries | Business logic is pure, DB details hidden |
| Hard to test (need a real DB) | Easy to test (swap in a fake repository) |
| Switching DB = rewrite everywhere | Switching DB = rewrite one repository |

📌 This is Dependency Inversion + Single Responsibility in practice. One of the highest-value patterns for backend.

### Service layer
Where **business logic** lives, between controllers (HTTP concerns) and repositories (data concerns). "Transfer money" - validate, check balance, debit, credit, log - belongs in a service, not smeared across a controller.

💡 Keeps controllers thin (just translate HTTP ↔ calls) and repositories dumb (just data). Each layer has one job.

### Dependency Injection (DI)
Instead of a module *creating* its own dependencies, they're **passed in** from outside.

```
// Tightly coupled - creates its own dependency:
class UserService { db = new PostgresDB() }   // stuck with Postgres, untestable

// Injected - receives its dependency:
class UserService { constructor(repo) { this.repo = repo } }  // swap/fake freely
```

💡 **Why it's everywhere:** DI makes code testable (inject a fake), flexible (inject a different implementation) and honest (dependencies are visible in the constructor, not hidden inside). It's the practical payoff of the Dependency Inversion Principle.

### Middleware pattern
A pipeline of functions each request passes through in order - logging → parsing → auth → rate-limiting → your handler. Each layer can act, then pass control on (or stop the chain).

💡 It's **Decorator + Chain of Responsibility** applied to request handling. It keeps cross-cutting concerns (auth, logging) out of your business logic and in reusable, composable layers. You'll use this constantly (Express and Next.js middleware).

### DTO (Data Transfer Object)
A plain object shaped specifically for moving data across a boundary (e.g., what your API returns), separate from your internal DB models.

💡 **Why:** you don't want to leak internal DB fields (like `passwordHash`) to API responses. DTOs let the outside shape differ from the inside shape - decoupling your API contract from your storage.

---

## Anti-patterns - patterns of *failure* to recognize

Knowing what *not* to do is as valuable as knowing what to do:

- **God Object / God Class** - one class that does everything and knows everything. The opposite of Single Responsibility.
- **Spaghetti code** - no clear structure, control flow tangled, everything coupled.
- **Big Ball of Mud** - a whole system with no discernible architecture.
- **Golden Hammer** - "I know pattern X, so everything is a nail." Forcing a familiar tool onto every problem.
- **Premature optimization** - complicating code for performance you haven't proven you need. (Measure first - file 04.)
- **Magic numbers/strings** - unexplained literals (`if status == 3`) instead of named constants (`if status == ORDER_SHIPPED`).

---

## How to actually use patterns (the mature take)

📌 **Don't** scan your problem for "which pattern fits." **Do** write the simplest thing that works, and when it gets painful in a *specific* way, reach for the pattern that relieves *that* pain. Patterns are answers to problems you actually have - not a checklist to pre-apply.

⚠️ **The beginner trap:** learning patterns and then over-applying them, wrapping simple code in factories and strategies it never needed. That's just complexity with fancy names. KISS and YAGNI win most arguments.

---

## Key takeaways

- Patterns = named, reusable structural solutions + a **shared vocabulary**.
- Backend life is mostly: **Controller → Service → Repository**, wired with **Dependency Injection**, decorated with **Middleware**, decoupled with **Observer/events** and **DTOs**.
- Every pattern traces back to file 01: reduce coupling, raise cohesion, depend on abstractions.
- Recognize **anti-patterns**; apply patterns only when a real pain calls for them.

➡️ Next: [`03-architecture.md`](03-architecture.md) - zooming out from code structure to *whole-system* shape.
