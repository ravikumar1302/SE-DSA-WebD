# Functions

## Typing parameters and return values

```ts
function add(a: number, b: number): number {
  return a + b;
}
```

`a: number` and `b: number` type the parameters. `: number` after the parentheses types the return value. TypeScript can usually infer the return type on its own, but writing it explicitly is good practice for any function other people (or future you) will call, since it documents the contract clearly.

```ts
function add(a: number, b: number) {
  return a + b;   // return type inferred as number
}
```

## Optional parameters

```ts
function greet(name: string, title?: string) {
  return title ? `Hello ${title} ${name}` : `Hello ${name}`;
}

greet("Ravi");            // valid
greet("Ravi", "Mr.");     // valid
```

Optional parameters must come after required ones.

## Default parameters

```ts
function greet(name: string, title: string = "Mr.") {
  return `Hello ${title} ${name}`;
}
```

If `title` is not passed, it defaults to `"Mr."`. TypeScript infers the type of `title` as `string` from the default value automatically.

## Rest parameters

```ts
function sum(...numbers: number[]): number {
  return numbers.reduce((total, n) => total + n, 0);
}

sum(1, 2, 3, 4); // 10
```

## Function types

You can type a variable as "a function that takes these arguments and returns this type", useful for callbacks.

```ts
type MathOperation = (a: number, b: number) => number;

const multiply: MathOperation = (a, b) => a * b;
```

Note that inside the arrow function, `a` and `b` do not need their types repeated. TypeScript already knows their types from the `MathOperation` type.

### Callback example

```ts
function processNumbers(numbers: number[], callback: (n: number) => number): number[] {
  return numbers.map(callback);
}

processNumbers([1, 2, 3], (n) => n * 2); // [2, 4, 6]
```

## Void vs undefined return

```ts
function logAndReturn(): void {
  console.log("done");
  // no return, or "return;" with nothing after it
}
```

`void` means "the return value should be ignored, if any exists at all". It is the correct type for functions used purely for side effects (logging, sending a response, writing to a database).

## Function overloads

Sometimes a function behaves differently depending on the type of argument it receives. Overloads let you describe each valid combination.

```ts
function getUser(id: number): User;
function getUser(email: string): User;
function getUser(idOrEmail: number | string): User {
  if (typeof idOrEmail === "number") {
    // look up by id
  } else {
    // look up by email
  }
  return {} as User;
}
```

The first two lines are overload signatures, they tell TypeScript what valid calls look like. The third line is the actual implementation, which must handle every case the overloads promise. Overloads are not common in everyday backend code, but you will see them in library type definitions (like Express's own types).

## Arrow functions

Typing works the same way as regular functions.

```ts
const add = (a: number, b: number): number => a + b;
```

## Typing `this` is not usually your concern in backend code

`this` typing issues mostly come up with class methods and event handlers in the browser. In Express route handlers and service functions, you generally will not need to type `this` explicitly, since backend code tends to favor plain functions over relying on `this`.

## Key takeaways

- Type parameters explicitly, let TypeScript infer simple return types when the function body makes it obvious.
- Optional (`?`) and default parameters both handle "this argument might be missing", pick default when you have a sensible fallback value.
- Function types describe callbacks cleanly, common for `.map()`, `.filter()` and Express middleware signatures.
- `void` is the right return type for side-effect-only functions.
