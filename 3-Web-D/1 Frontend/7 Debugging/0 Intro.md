# Debugging, an Introduction

## Debugging is a skill, not luck

New developers often "debug" by changing random lines and refreshing the page, hoping something fixes itself. Sometimes it does, more often it wastes an hour and leaves the code messier than before. Debugging is a process with steps, the same way solving a maths problem has steps. Learn the process once, and it works on every bug, in every language, forever.

## The four-step loop

```
1. Reproduce   -> make the bug happen on demand, every time
2. Isolate     -> narrow down exactly where it happens
3. Hypothesize -> form one specific guess about the cause
4. Verify      -> test the guess, confirm or reject it, repeat
```

If a guess is wrong, that is not wasted effort, it removes one possibility and narrows the search. Guessing wildly without this loop tends to retest the same wrong ideas over and over.

### Step 1: Reproduce

A bug that happens "sometimes" cannot be fixed reliably. The first job is finding exact steps that trigger it every time.

- What page or component
- What action (click, type, refresh, navigate)
- What data or state was present
- Does it happen every time, or only sometimes

⚠️ **Pitfall**: fixing a bug based on a guess, without ever reproducing it, often "fixes" a symptom while the real cause stays. It looks solved until it reappears somewhere else.

### Step 2: Isolate

Once it reproduces, narrow down where. Comment out code, remove components, or use `git bisect` style thinking, cut the problem space in half repeatedly until the smallest possible piece still shows the bug.

```
Full app has the bug
      |
      v
Remove half the page, still there? -> keep narrowing this half
      |                                keep narrowing the other half
      v
Down to one component, one function, one line
```

This is the same binary search idea used in DSA, applied to a bug instead of a sorted array. Covered again in file 12.

### Step 3: Hypothesize

State a specific, testable guess: "the `count` variable is stale because the closure captured an old value", not a vague "something is wrong with state." A specific hypothesis tells you exactly what to check next.

### Step 4: Verify

Add a log, a breakpoint, or a small test that proves or disproves the hypothesis. If wrong, go back to step 3 with the new information. If right, the fix usually becomes obvious.

## Where this folder is going

The files ahead cover the tools for step 4 in detail: what the browser gives you (DevTools panels, breakpoints, the Network tab), what React and Next.js add on top, and general strategies for narrowing a bug down fast. Reading them will not remove the need for the four-step loop above, they make each step faster and more precise.

## Key takeaways

- Debugging is reproduce, isolate, hypothesize, verify, on a loop, not random guesses.
- A bug you cannot reproduce on demand cannot be fixed reliably.
- Isolating with a binary-search mindset turns "somewhere in this huge app" into "this one line" quickly.
- Every tool in the rest of this folder exists to make one of these four steps faster.
