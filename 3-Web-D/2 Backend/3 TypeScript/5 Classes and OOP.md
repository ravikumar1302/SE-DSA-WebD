# Classes and OOP

TypeScript classes work like JavaScript classes, with types added to properties, parameters and return values. If you already know OOP from your DSA work in C++/Java, this will feel familiar, the keywords are the same.

## Basic class

```ts
class User {
  id: number;
  name: string;

  constructor(id: number, name: string) {
    this.id = id;
    this.name = name;
  }

  greet(): string {
    return `Hello, ${this.name}`;
  }
}

const user = new User(1, "Ravi");
```

## Access modifiers

| Modifier | Accessible from | Typical use |
|---|---|---|
| `public` (default) | Anywhere | Normal properties and methods |
| `private` | Only inside the class itself | Internal details, hides implementation |
| `protected` | Inside the class and its subclasses | Shared internal state for a family of classes |
| `readonly` | Anywhere for reading, nowhere for writing after construction | Values that must not change, like an id |

```ts
class BankAccount {
  private balance: number;
  readonly accountId: string;

  constructor(accountId: string, startingBalance: number) {
    this.accountId = accountId;
    this.balance = startingBalance;
  }

  deposit(amount: number): void {
    this.balance += amount;
  }

  getBalance(): number {
    return this.balance;
  }
}

const account = new BankAccount("acc-1", 1000);
account.balance;       // error, balance is private
account.getBalance();  // fine, 1000
account.accountId = "acc-2"; // error, readonly
```

`private` is a TypeScript-only, compile-time check. It stops mistakes in your code, but it is not a real runtime security boundary, since it disappears once compiled to plain JavaScript. JavaScript's own `#privateField` syntax does enforce it at runtime, if you ever need that.

## Constructor shorthand

Writing `this.x = x` for every property gets repetitive. TypeScript lets you declare and assign in one place, directly in the constructor parameters.

```ts
class User {
  constructor(
    public id: number,
    public name: string,
    private password: string
  ) {}
}
```

This is identical to writing out the full properties and `this.x = x` assignments manually. It is a common shorthand you will see in real backend code, including many Express + Prisma project examples.

## Implementing an interface

A class can promise to match a given shape using `implements`.

```ts
interface Repository {
  findById(id: number): object | null;
  save(data: object): void;
}

class UserRepository implements Repository {
  findById(id: number) {
    // look up user
    return null;
  }

  save(data: object) {
    // save user
  }
}
```

If `UserRepository` is missing a method that `Repository` requires, or has the wrong type for it, TypeScript reports an error. This is the type-level backbone of the Repository pattern described in [`02-design-patterns.md`](../0%20Concepts/02-design-patterns.md), it guarantees every repository implementation exposes the same methods.

## Abstract classes

An abstract class cannot be instantiated directly, it exists only to be extended. It can define some shared logic and force subclasses to implement the rest.

```ts
abstract class Shape {
  abstract area(): number;  // subclasses must implement this

  describe(): string {
    return `This shape has an area of ${this.area()}`;
  }
}

class Circle extends Shape {
  constructor(private radius: number) {
    super();
  }

  area(): number {
    return Math.PI * this.radius ** 2;
  }
}

const shape = new Shape();     // error, cannot instantiate abstract class
const circle = new Circle(5);
circle.describe();             // "This shape has an area of 78.5..."
```

## Interface vs abstract class

| | Interface | Abstract class |
|---|---|---|
| Can contain implemented methods | No, only signatures | Yes |
| Can hold state (properties with values) | No | Yes |
| A class can use more than one | Yes (`implements A, B`) | No, only one (`extends`) |
| Runtime existence | None, erased when compiled | Yes, exists as a real class |

📌 Use an interface when you only need to describe a shape. Use an abstract class when you need to share actual code between related classes.

## How much OOP does backend work actually need

Not a huge amount, day to day. Node/Express backend code leans more on plain functions and objects (functional style) for request handling, and reserves classes mainly for things like:

- Services and repositories, where `implements` guarantees a consistent shape (see [`02-design-patterns.md`](../0%20Concepts/02-design-patterns.md), Repository pattern and Dependency Injection).
- Custom error classes (`class ValidationError extends Error {}`), covered when you reach error handling in Phase 1.

## Key takeaways

- Access modifiers (`public`, `private`, `protected`, `readonly`) control what outside code can touch, checked at compile time only.
- Constructor shorthand (`constructor(public x: number)`) saves repetitive assignment code.
- `implements` makes a class match an interface's shape, this backs the Repository and Service patterns you will build in Phase 2 and 3.
- Abstract classes share real code across subclasses, interfaces only share shape.
