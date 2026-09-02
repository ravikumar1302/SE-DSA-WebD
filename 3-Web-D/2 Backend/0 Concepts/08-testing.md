# 08 - Testing

Testing is how you gain the **confidence to change code without fear**. Every backend of consequence has automated tests; without them, every change is a gamble and every deploy is stressful. Tests are not bureaucracy - they're the safety net that lets you move fast *without* breaking things.

💡 **Why it matters:** manually re-checking your whole app after every change is impossible past a certain size. Automated tests re-check it in seconds, every time. They catch regressions (things that used to work and quietly broke), document how code is *supposed* to behave and make refactoring safe. The confidence tests give you is the whole point.

---

## The Testing Pyramid - the mental model

A guide to *how many* of each kind of test to write. Shape: wide at the bottom, narrow at the top.

```
          ▲   /\
   fewer  |  /E2E\        ← few: slow, expensive, brittle, high-level
          | /------\
          |/ Integr.\     ← some: components working together
   more   /----------\
          / Unit tests \  ← many: fast, cheap, focused, low-level
          --------------
```

💡 **The logic:** unit tests are fast and cheap, so write *lots*. E2E tests are slow and fragile, so write *few* - just the critical paths. Integration sits in between. An inverted pyramid (mostly slow E2E tests) is a common, painful anti-pattern: slow suites, flaky failures, hard debugging.

---

## The levels of testing

### 1. Unit tests - *does one small piece work in isolation?*
Test a single function/module **in isolation** from its dependencies (DB, network, other modules).
- **Scope:** one function/class - e.g., "does `calculateDiscount(price, coupon)` return the right number?"
- **Speed:** milliseconds. Run thousands in seconds.
- **Isolation:** dependencies are replaced with **test doubles** (mocks/stubs - below), so you're testing *only* this unit's logic.
- 💡 Pinpoints bugs precisely - when one fails, you know exactly where. This is where testable design pays off: code with injected dependencies (file 02) is easy to unit test.

### 2. Integration tests - *do pieces work together?*
Test that multiple components **cooperate** correctly - e.g., your service layer talking to a *real* database, or your API route hitting the actual data layer.
- **Scope:** several units combined; often includes real infrastructure (a test DB).
- **Speed:** slower (real I/O).
- 💡 Catches bugs that unit tests can't: wrong SQL, mis-wired dependencies, serialization mismatches. The seams *between* components are where lots of real bugs live.

### 3. System testing - *does the whole app behave?*
Test the **complete, integrated system** as a whole against its requirements, in an environment close to production. Broader than integration - it exercises the assembled application end-to-end at the system level (functionality, sometimes performance/security too).

### 4. End-to-End (E2E) tests - *does the full user journey work?*
Simulate a **real user flow** through the entire stack: e.g., "register → log in → create an order → see it in the list," driving the actual API (and often a real frontend).
- **Scope:** the whole system, top to bottom.
- **Speed:** slowest, most brittle (many moving parts).
- 💡 Highest confidence that the real thing works - but expensive to write and maintain, so reserve for **critical paths** (signup, checkout, payment).

⚖️ **The four levels at a glance:**

| Level | Tests | Speed | Isolation | How many |
|---|---|---|---|---|
| **Unit** | One function/module | Fastest | Fully isolated (mocks) | Many |
| **Integration** | Components together | Medium | Real dependencies | Some |
| **System** | Whole app vs requirements | Slow | Full system | Fewer |
| **E2E** | Full user journeys | Slowest | Everything real | Fewest |

### Other kinds worth naming
- **Regression testing** - re-running tests to confirm new changes didn't break old behavior (your whole suite serves this).
- **Smoke testing** - a quick "is it even alive?" check after deploy (does the app start, do key endpoints respond).
- **Acceptance testing** - does it meet the business/user requirements (often written with/for stakeholders).
- **Performance/load testing** - behavior under load (file 04).
- **Security testing** - probing for vulnerabilities (penetration testing).

---

## Test doubles: Mocks, Stubs, Fakes, Spies

To test a unit in isolation, you replace its real dependencies with stand-ins ("test doubles"):

- **Stub** - returns canned answers ("when asked for user 1, return this fixed object"). Controls *inputs* to your code.
- **Mock** - a stub that also *verifies interactions* ("assert `sendEmail` was called once with these args"). Checks *behavior*.
- **Fake** - a working but simplified implementation (an in-memory DB instead of the real one).
- **Spy** - wraps a real object to record how it was called, without replacing it.

💡 **Why:** you don't want your unit test for "order total logic" to actually charge a credit card or need a live database. Doubles let you test *your* logic deterministically, fast, without side effects. ⚠️ **Pitfall:** over-mocking - mock so much that you're testing your mocks, not real behavior. Mock external/slow things (network, DB, time); prefer real objects for your own simple code.

---

## Anatomy of a good test: Arrange-Act-Assert

Structure each test in three clear steps:
1. **Arrange** - set up inputs, data and doubles
2. **Act** - call the thing under test
3. **Assert** - check the result is what you expect

```
// Arrange
const cart = new Cart([{ price: 100 }, { price: 50 }]);
// Act
const total = cart.getTotal();
// Assert
expect(total).toBe(150);
```

**Qualities of good tests (FIRST):**
- **F**ast - so you actually run them often
- **I**solated - don't depend on each other or on order
- **R**epeatable - same result every run (no reliance on time, randomness, network)
- **S**elf-validating - clearly pass/fail, no manual interpretation
- **T**imely - written close to the code they test

⚠️ **Test behavior, not implementation.** Assert *what* the code does (its outputs/effects), not *how* it does it internally. Tests coupled to internals break every time you refactor - defeating the purpose.

---

## TDD - Test-Driven Development

A discipline where you write the **test first**, watch it fail, then write just enough code to pass, then refactor. The **Red → Green → Refactor** loop:
1. **Red** - write a failing test for the behavior you want
2. **Green** - write the minimal code to make it pass
3. **Refactor** - clean up, tests still green

💡 **Why people swear by it:** it forces you to define "done" before coding, produces naturally testable designs and guarantees test coverage. Not everyone does strict TDD, but the habit of *thinking about tests as you write* is universally valuable. You don't have to be dogmatic - even writing tests right *after* the code beats not writing them.

---

## Code coverage - useful metric, dangerous target

**Coverage** = the % of your code executed by tests. Helpful for spotting *untested* areas.

⚠️ **But it measures quantity, not quality.** 100% coverage with weak assertions proves nothing - you *ran* the code without checking it's *correct*. And chasing 100% wastes effort on trivial code. 📌 Treat coverage as a *smell detector* (very low coverage = worry) not a goal. Aim to test what *matters* - core logic, edge cases, error paths - not to hit a number.

---

## What to actually test (practical priorities)

You can't test everything; prioritize:
1. **Core business logic** - the rules that make your app *your app*. Highest value.
2. **Edge cases** - empty inputs, zero, negatives, huge values, boundaries.
3. **Error paths** - what happens when things fail (bad input, DB down)? Often under-tested.
4. **Bug fixes** - when you fix a bug, write a test that would've caught it, so it never returns.
5. **Critical user journeys** - a few E2E tests on signup/checkout/payment.

📌 Don't bother unit-testing trivial getters or framework code. Test *your* decisions and *your* risks.

---

## Testing tools (concept, not stack-specific)

Every ecosystem has:
- **Test runner + assertion framework** - runs tests, provides `expect`/`assert` (Jest, Vitest, Mocha in JS; pytest in Python; JUnit in Java; Go's built-in testing).
- **Mocking library** - creates test doubles (often built into the runner).
- **API/HTTP testing** - hit your endpoints in tests (Supertest for Node; requests/httpx for Python; Postman/Newman for external).
- **E2E frameworks** - drive full flows (Playwright, Cypress for web).
- **Coverage tools** - report coverage (built into most runners).

---

## Where testing meets CI/CD

The payoff compounds when tests run **automatically on every change** in your pipeline (file 09): push code → tests run → merge blocked if they fail. This is how teams keep a shared codebase healthy - broken code never reaches main. Tests you never run rot; tests that run automatically protect you continuously.

---

## Key takeaways

- Tests buy **confidence to change code fearlessly** - that's the whole point.
- Follow the **pyramid**: many fast **unit** tests, some **integration**, few **E2E** (critical paths only).
- Know the levels: **unit** (isolated) → **integration** (together) → **system** (whole app) → **E2E** (user journeys).
- Use **test doubles** to isolate units, but don't over-mock. Structure tests **Arrange-Act-Assert**; keep them **FIRST**.
- **Test behavior, not implementation.** Treat **coverage** as a hint, not a goal.
- Prioritize **core logic, edge cases, error paths and past bugs.**
- Run tests **automatically in CI** so they actually protect you.

➡️ Next: [`09-cicd-devops.md`](09-cicd-devops.md) - automating the path from commit to production.
