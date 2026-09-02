# 01 - Software Engineering Foundations

These are the bedrock ideas. Every design pattern, architecture and best practice later is just an *application* of what's here. Learn these deeply and the rest becomes obvious instead of memorized.

---

## 1. What "software engineering" even means

Writing code that *works* is programming. Writing code that **keeps working as it grows and changes, across a team, over years** is engineering. The difference is entirely about managing **complexity** and **change**.

💡 **Why it matters:** Code is read far more often than it's written, and changed far more often than it's created from scratch. Almost every "best practice" exists to make future change cheaper and safer. If a rule doesn't reduce the cost of change or the risk of bugs, question it.

---

## 2. The SDLC (Software Development Life Cycle)

The stages software moves through, regardless of methodology:

1. **Requirements** - what are we building and why
2. **Design** - how will it be structured (architecture, data model, APIs)
3. **Implementation** - writing the code
4. **Testing** - verifying it does what it should
5. **Deployment** - getting it to users
6. **Maintenance** - fixing, improving, evolving (the longest phase by far)

⚖️ **Two ways to move through these:**

| | **Waterfall** | **Agile** |
|---|---|---|
| Flow | Each stage fully done before the next | Small iterations, cycle repeatedly |
| Change | Expensive, resisted | Expected, embraced |
| Feedback | Late (at the end) | Early and continuous |
| Best for | Fixed, well-understood requirements | Evolving products (most software today) |

📌 **Rule of thumb:** Modern backend work is almost always iterative. Build a thin slice end-to-end, ship it, learn, repeat - don't design the whole system perfectly upfront.

---

## 3. Modularity - the master concept

**Modularity** = breaking a system into smaller, self-contained pieces (modules) that each do one job and connect through clear interfaces.

Think of a module like a function or a file or a service: a box with a well-defined "what it does" (the interface) and a hidden "how it does it" (the implementation).

💡 **Why it matters:** A 10,000-line file is impossible to reason about - changing one thing risks breaking twenty others. Ten 1,000-line modules with clear boundaries mean you only need to understand *one* at a time. Modularity is how humans fit big systems into small heads.

Modularity gives you:
- **Isolation** - a bug lives in one module, not everywhere
- **Reusability** - a well-bounded module can be used elsewhere
- **Parallel work** - different people work on different modules
- **Testability** - you can test a module in isolation
- **Replaceability** - swap a module's insides without touching the rest

Everything else in this file (coupling, cohesion, abstraction, SOLID) is really about *doing modularity well*.

---

## 4. Coupling and Cohesion - the two dials

These are the two most important words for judging structure. Get these and you can evaluate almost any design.

### Coupling - how much modules depend on each other
- **Tight (high) coupling** = modules know a lot about each other's internals. Change one → must change others. Bad.
- **Loose (low) coupling** = modules interact only through clean interfaces, knowing as little as possible. Change one's insides → others don't care. Good.

### Cohesion - how focused a single module is
- **Low cohesion** = a module does many unrelated things (a "utils" dumping ground). Bad.
- **High cohesion** = everything in the module relates to one clear responsibility. Good.

📌 **The golden goal:** **Low coupling, high cohesion.** Modules that are focused internally and independent externally. Repeat this phrase until it's reflex - it's the single best lens for judging code structure.

⚠️ **Pitfall:** A giant `helpers.js` / `utils.py` file is the classic low-cohesion trap. It grows into an unrelated junk drawer that everything depends on (high coupling too). Group by *responsibility*, not by "miscellaneous."

---

## 5. Abstraction and Encapsulation

**Abstraction** = exposing *what* something does while hiding *how*. A `sendEmail(to, body)` function is an abstraction - callers don't know or care whether it uses SMTP, an API or carrier pigeon.

**Encapsulation** = bundling data with the code that operates on it, and hiding the internal state behind a controlled interface. Outsiders can't reach in and corrupt internals.

💡 **Why it matters:** Abstraction lets you *change the how without breaking the callers*. If every part of your app called the email API directly, switching providers means editing a hundred places. Behind one abstraction, it's one edit. This is the entire reason we build "layers" and "services."

⚠️ **Pitfall - leaky abstraction:** an abstraction that forces you to understand its internals anyway. E.g. a "simple" cache that silently returns stale data - you can't use it correctly without knowing how it works inside. Good abstractions let you ignore the internals safely.

---

## 6. The core principles (DRY, KISS, YAGNI, SoC)

### DRY - Don't Repeat Yourself
Every piece of knowledge should have **one** authoritative place. Copy-pasted logic means a bug fixed in one copy stays broken in the others.

⚠️ **But:** don't over-DRY. Two pieces of code that *look* similar today but represent *different concepts* will need to change independently - forcing them together creates worse coupling. **Duplication is cheaper than the wrong abstraction.**

### KISS - Keep It Simple, Stupid
The simplest solution that works is usually the best. Clever code is a liability - you (or someone) has to maintain it at 2 a.m. later.

### YAGNI - You Aren't Gonna Need It
Don't build for imagined future requirements. Build what's needed *now*. Most "we might need it later" features never arrive, and the speculative flexibility just adds complexity today.

💡 KISS + YAGNI together are the antidote to over-engineering - the most common failure of enthusiastic learners.

### Separation of Concerns (SoC)
Different *kinds* of work belong in different places: request handling ≠ business logic ≠ database access. Mixing them creates tangled, untestable code. (This directly produces the "layered architecture" you'll see in file 03.)

---

## 7. SOLID - five principles for maintainable code

Originally for object-oriented code, but the *ideas* apply everywhere in backend design. Don't memorize the acronym - understand each idea's purpose.

### S - Single Responsibility Principle
A module/class should have **one reason to change** - i.e., one job.
💡 If a class handles user data *and* sends emails *and* formats reports, three unrelated forces pull on it. Split them. (This is just "high cohesion" restated.)

### O - Open/Closed Principle
Code should be **open for extension, closed for modification** - add new behavior without editing existing, tested code.
💡 Example: instead of a giant `if paymentType == ...` that you edit for every new payment method, define a common interface and *add* a new implementation. Existing code stays untouched (and un-broken).

### L - Liskov Substitution Principle
A subtype should be usable **anywhere its parent type is expected**, without surprises.
💡 If `Penguin extends Bird` but `Bird.fly()` breaks for penguins, your hierarchy is lying. Subtypes must honor the parent's contract.

### I - Interface Segregation Principle
Don't force a module to depend on methods it doesn't use. Prefer several small, focused interfaces over one fat one.
💡 A `Printer` shouldn't have to implement `scan()` and `fax()` just because they're bundled in one big `Machine` interface.

### D - Dependency Inversion Principle
High-level code should depend on **abstractions**, not concrete details. Details depend on abstractions, not the reverse.
💡 Your business logic shouldn't import "PostgreSQL" directly - it should depend on a `UserRepository` interface. Then you can swap Postgres for anything, and *test* with a fake. This principle powers **Dependency Injection** (file 02) and clean architecture (file 03).

📌 **The through-line of all five:** isolate what changes, depend on stable abstractions, keep each piece focused. It's coupling/cohesion again, spelled out five ways.

---

## 8. Other foundational habits

- **Naming** - clear names are the cheapest documentation. `getUserById` beats `getData`. Spend real effort here.
- **Fail fast & loud** - validate early, throw clear errors, don't silently swallow failures. Hidden bugs are the expensive ones.
- **Single source of truth** - one authoritative place for each piece of data/config. Duplicated truth drifts out of sync.
- **Explicit over implicit** - code that hides what it's doing (magic) is hard to debug. Prefer obvious.
- **Composition over inheritance** - building behavior by combining small pieces is usually more flexible than deep class hierarchies (which get rigid fast).

---

## 9. Technical debt

**Technical debt** = the future cost of choosing a quick-but-messy solution now instead of a clean one. Like financial debt, it accrues "interest": messy code slows every future change.

💡 **Why it matters:** debt isn't always bad - taking some on to ship fast can be the right call. The danger is *unmanaged* debt that's never paid down until the codebase is unworkable. Name it, track it, pay it back deliberately.

⚠️ **Pitfall:** treating "make it perfect" as free. Gold-plating (endless polishing) is debt in the other direction - you pay in shipped-too-late.

---

## Key takeaways

- Engineering ≠ programming; it's about **managing change and complexity**.
- **Modularity** is the master skill; **low coupling + high cohesion** is how you measure it.
- **Abstraction** lets you change *how* without breaking *who uses it*.
- **DRY/KISS/YAGNI** fight over-engineering; **SOLID** spells out good modularity.
- Every later concept (patterns, architecture, scaling) is these ideas applied at bigger scales.

➡️ Next: [`02-design-patterns.md`](02-design-patterns.md) - named, reusable solutions built from exactly these principles.
