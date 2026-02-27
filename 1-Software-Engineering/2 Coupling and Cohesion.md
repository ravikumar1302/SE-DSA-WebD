# SDLC : Coupling vs Cohesion

## 1 Coupling vs Cohesion

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

## 2 Real example (SDLC + Coupling + Cohesion)

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
