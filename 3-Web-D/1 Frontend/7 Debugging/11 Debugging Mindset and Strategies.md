# Debugging Mindset and Strategies

Tools find things fast once you already know roughly where to look. These strategies help decide where to look in the first place, especially for a bug with no obvious starting point.

## Binary search debugging

Covered briefly in file 0, worth a closer, practical look here. When a bug's location is completely unknown, cut the search space in half repeatedly rather than checking files one by one from the top.

```
The bug is somewhere in a 500-line function
      |
      v
Comment out (or add a return) at the halfway point
      |
      v
Bug still happens?  -> it's in the first half, repeat there
Bug gone?           -> it's in the second half, repeat there
```

The same idea applies across commits, not just lines of code. If a bug appeared sometime in the last twenty commits but you do not know which one, `git bisect` automates exactly this binary search, checking out a middle commit, asking "good or bad," and narrowing down to the exact commit that introduced it in `log2(20)`, about 5, steps instead of checking all 20 one by one.

## Minimal reproduction

Once a bug reproduces (file 0's step 1), the next useful move is often shrinking it, not immediately fixing it. Strip away everything not needed to still see the bug: unrelated components, unrelated state, unrelated styling. What remains is the minimal reproduction.

Why bother, instead of fixing it in the full messy context directly: a minimal reproduction removes every distraction, makes the actual cause far more visible, and if you ever need to ask someone else for help (a teammate, a forum, an AI assistant), a small reproducible example gets a useful answer far faster than "my whole app is broken" with a huge unrelated codebase attached.

## Rubber duck debugging

Explain the code line by line, out loud, to anything, a rubber duck, a pet, an empty chair, as if teaching it exactly what each line does and why. The value is not in the listener, it is in forcing yourself to state assumptions explicitly instead of skimming past them mentally. Very often the mismatch between "what I assumed this line does" and "what it actually does" surfaces the moment it is said out loud, before finishing the explanation.

## `debugger` versus a log, when to use which

| | A `console.log` | A `debugger` statement or breakpoint |
|---|---|---|
| Best for | Watching a value change across many calls or renders, over time | Inspecting the full state at one exact moment in detail |
| Speed to set up | Instant | Slightly more setup, but pauses everything |
| What you see | Only what you explicitly logged | Every variable in scope, live |

Neither replaces the other, a log is better for a pattern over time ("how does this value change across ten renders"), a breakpoint is better for depth at one moment ("what exactly is every variable here, right now").

## Reading the bug report critically

A bug report from someone else ("it's broken") is rarely the full story. Before touching code, get the exact reproduction steps first, question one and step one from file 0's loop, even if that means asking the reporter follow-up questions. Time spent confirming the actual repro steps upfront usually saves far more time than skipping straight to guessing.

## When you are genuinely stuck

- Step away for a few minutes, actual distance from the screen often surfaces the missed assumption that staring longer will not.
- Re-read the actual error message one more time, word by word, slowly. It is common to skim past the exact detail that would have solved it in seconds.
- Check whether the bug also happens on a known-good commit (an older, working version). If yes, it was never actually caused by the recent change you suspected.
- Search the exact error message. A specific, unusual error string is often already documented somewhere, a generic guess like "app not working" rarely is.

This mindset, more than any single tool, is what separates fast debugging from slow debugging. The tools in the earlier files make each step quicker, but the order (reproduce, isolate, hypothesize, verify) and the discipline of not skipping straight to a guess are what actually get you to the fix.
