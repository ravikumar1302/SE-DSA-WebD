# SDLC, Coupling and Cohesion

## 1. Principles of Software Engineering

| Principle                     | Full Form                                                                                            | Clear Explanation                                                                                  |
| ----------------------------- | ---------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------- |
| **SOLID**                     | Single Responsibility, Open/Closed, Liskov Substitution, Interface Segregation, Dependency Inversion | A set of 5 rules that help write clean, flexible code where changes don’t break existing features. |
| **Single Responsibility (S)** | —                                                                                                    | One class or module should do only one job.                                                        |
| **Open/Closed (O)**           | —                                                                                                    | Code should allow new features without changing existing code.                                     |
| **Liskov Substitution (L)**   | —                                                                                                    | A child class should work wherever its parent class is expected.                                   |
| **Interface Segregation (I)** | —                                                                                                    | Don’t force a class to implement methods it doesn’t need.                                          |
| **Dependency Inversion (D)**  | —                                                                                                    | High-level code should depend on abstractions, not concrete implementations.                       |
| **GRASP**                     | General Responsibility Assignment Software Patterns                                                  | Principles that guide how to assign responsibilities to classes and objects.                       |
| **GRASP (Core idea)**         | —                                                                                                    | Give responsibilities to the class best suited to handle them.                                     |
| **DRY**                       | Don’t Repeat Yourself                                                                                | Avoid duplicating logic; put it in one place and reuse it.                                         |
| **KISS**                      | Keep It Simple, Stupid                                                                               | Prefer simple solutions over complex ones for better readability and maintenance.                  |

## 2. SDLC :

- SDLC (Software Development Life Cycle) is a thinking framework to build, run, and evolve software safely and predictably.
- SDLC exists to reduce risk, not to add process
- It answers:
    - What should we build?
    - How do we build it?
    - How do we verify it?
    - How do we release it?
    - How do we maintain it when things break?

- SDLC exists (core reasons) because of below reasons :

1. To reduce business risk, Without SDLC:
    - Features break production
    - Deadlines slip
    - Cost explodes
    - Engineers burn out
    - SDLC adds controlled checkpoints.

2. To manage complexity : Software grows fast, SDLC prevents:
    - Random coding
    - Tight coupling
    - Fragile systems

3. To enable collaboration : SDLC defines:
    - Who does what
    - When decisions are made
    - How work is reviewed
    - Without SDLC → chaos in multi-engineer teams.

4. To create predictability : Management doesn’t need perfection, They need:
    - Rough timelines
    - Confidence
    - Fewer surprises
    - SDLC gives visibility into progress.

## 3 Different SDLC Models :

a) **Waterfall — Rare, but still alive**

- When it actually exists : Government, Defense, Banking core systems and their upgrades, Medical software
- Why it exists in above cases :
    - Core banking system upgrade
    - Fixed scope
    - Regulatory approval required
    - Heavy documentation
    - Long testing cycles

- Why startups avoid it
    - Requirements change
    - Feedback comes too late
    - High failure cost

b) **Agile (Scrum / Kanban) — Default in most teams**

- What it really means in practice
- Work is broken into small, shippable chunks
- Requirements evolve
- Feedback comes from production usage, not documents

- Real example
    - Startup building a SaaS dashboard
    - Sprint 1: basic auth + user list
    - Sprint 2: filters + pagination
    - Sprint 3: performance fixes from real users
    - Requirements change every sprint → Agile survives, Waterfall dies.

- Why industry uses it
    - Business changes fast
    - Stakeholders don’t know exact requirements upfront
    - Shipping early gives real feedback
    - Downsides (important)
    - Can become chaotic if no tech discipline
    - Juniors may feel lost without clear specs

- Downsides (important)
    - Can become chaotic if no tech discipline
    - Juniors may feel lost without clear specs

👉 Most startups = Agile + shortcuts

c) **Iterative / Incremental — How mature teams think**

- This is Agile’s engineering backbone.
- Core idea
    - Build core first
    - Add features in layers
    - Refactor continuously
        - Refactoring in software engineering is restructuring existing code to improve its internal design, readability and maintainability without changing its external behavior or functionality, making it cleaner, simpler, and easier to extend
- Real example : Payment system
    - Iteration 1: card payment (happy path)
    - Iteration 2: retries, logging
    - Iteration 3: refunds, edge cases
    - Iteration 4: monitoring, alerts
    - System evolves safely.

- Why it’s used
    - Reduces risk
    - Allows learning from production
    - Supports refactoring

d) **DevOps / CI-CD Driven Model — Modern reality**

- This is not a “model” in textbooks, but this runs production today.
- What defines it
    - Code → PR → Tests → Deploy automatically
    - Releases are small and frequent
    - Engineers own production

- Real example : Feature flag rollout
    - Code merged to main
    - Deployed but hidden
    - Enabled for 5% users
    - Monitor errors
    - Roll out to 100%

- Why industry moved here
    - Faster releases
    - Lower blast radius
    - Easy rollback

e) **Spiral — Used in high-risk systems**

- Core idea
    - Build → analyze risk → refine → repeat
    - Heavy emphasis on risk mitigation

- Real example
    - Autonomous vehicle software
    - Simulate environment
    - Identify failure modes
    - Improve control logic
    - Repeat

- Why it’s rare
    - Expensive
    - Slow
    - Needs strong engineering maturity

f) **Prototype / MVP-Driven — Startup special**

- What really happens
    - Build fast prototype
    - Validate idea
    - Either kill or rebuild properly

- Real example : Internal admin tool
    - Hardcoded values
    - Minimal validation
    - Used by 3 people
    - Later rewritten cleanly

g) Other models : RAD, V-Model, Big Bang etc

- Are models like RAD (Rapid Application Development), V-Model, Big Bang, etc. needed?
- Academically: yes
- Professionally (first 2–3 months): mostly no
- Conceptually: understand why they existed, not how to follow them
- These models solved specific historical problems. Modern teams absorbed their ideas, not the models themselves.
- | Model     | What to learn              |
  | --------- | -------------------------- |
  | RAD       | Speed + feedback matters   |
  | V-Model   | Testing must map to intent |
  | Prototype | Validate before scaling    |
  | Big Bang  | What **not** to do         |

## 4 Coupling vs Cohesion

- Big picture :
    - Coupling → how much modules depend on each other
    - Cohesion → how focused a module is on one responsibility

- Goal : Low coupling + High cohesion

- This directly affects: Bug risk, Ease of change, Code review quality
- **Cohesion** (inside a module) : Cohesion measures whether a piece of code does ONE clear job.
    - High cohesion:
        - Code has a single purpose
        - Easy to name
        - Easy to test
    - Low cohesion:
        - Mixed responsibilities
        - “God” functions/classes
        - Hard to reason about

```
Example: Low Cohesion (bad)
class UserService {
    void createUser(User u) { ... }
    void sendEmail(User u) { ... }
    void generatePdfReport() { ... }
    void backupDatabase() { ... }
}

Problems:
   a) Multiple unrelated responsibilities
   b) Changes break unrelated behavior
   c) Impossible to test cleanly

Example: High Cohesion (good)
class UserService {
    void createUser(User u) { ... }
}
class EmailService {
    void sendUserWelcomeEmail(User u) { ... }
}
class ReportService {
    void generateUserReport() { ... }
}

Each class has one reason to change.
```

- **Coupling** (between modules) : Coupling measures how tightly one module depends on another’s details.
    - High coupling:
        - Change in one place breaks many places
        - Hard to refactor
        - Hard to test in isolation
    - Low coupling:
        - Modules talk via contracts
        - Changes are localized

```
Example: High Coupling (bad)
class OrderService {
    void placeOrder() {
        Database db = new Database();
        db.connect("localhost", "root", "password");
        db.execute("INSERT INTO orders...");
    }
}

Problems:
   a) Tied to DB implementation
   b) Hard to test
   c) Any DB change breaks this class


Example: Low Coupling (good)
class OrderService {
    private OrderRepository repo;

    OrderService(OrderRepository repo) {
        this.repo = repo;
    }

    void placeOrder(Order o) {
        repo.save(o);
    }
}

interface OrderRepository {
    void save(Order o);
}

OrderService doesn’t care how data is stored.
```

## Real example (SDLC + Coupling + Cohesion)

- Scenario : E-commerce: “Place Order” feature

- SDLC (how work flows)
    - Requirement :
        - User places order → payment → confirmation
        - (Edge cases: payment fail, stock issue)
    - Design (lightweight)
        - Decide responsibilities before coding.
    - Develop → Test → Deploy → Monitor
        - Small changes, safe release.
    - SDLC = thinking before, during, and after code

- Architecture (simple & realistic)
  Controller -> OrderService -> Payment, Inventory, Email

- Cohesion (inside components)
    - OrderService → order flow only
    - PaymentService → payment logic only
    - InventoryService → stock only
    - Each unit has one job.
    - One class = one responsibility = high cohesion

- Coupling (between components)
    - Good
        - OrderService calls services/interfaces
        - Doesn’t know DB, gateways, SMTP details

    - Bad
        - OrderService directly talks to DB, payment SDK, email
        - Low coupling = easy change, safe refactor

- Because of:
    - High cohesion → logic is in right place
    - Low coupling → change is local
    - No rewrite needed.

## One-line memory hook (important)

    - SDLC = when to think
    - Cohesion = where logic lives
    - Coupling = how safely it changes
