# Practice: Debugging

These are not code-writing exercises, they are scenarios. Each one describes a symptom, work out what you would check first and in what order, using the tools from this folder, then write down your reasoning before checking the hint.

---

### 1. A button click does nothing

Clicking a "Save" button on a page produces no visible change, no error in the console, no network request.

**Think through**: which panel would confirm whether the click handler even ran at all.

**Hint**: a `debugger` statement or breakpoint at the top of the handler, or `console.log` as a first quick check, answers "does this function run" before anything else matters.

---

### 2. A list shows stale data after an update

A todo list shows the old text for an item right after editing it, even though the network tab shows the update request succeeded with the new value.

**Think through**: is this a network problem or a React rendering problem, and how would you tell the difference.

**Hint**: check the Network tab response body first, confirm the new value is actually there. If it is, the bug is in how that response gets back into component state, not the request itself.

---

### 3. A component re-renders on every keystroke, even unrelated fields

Typing in a search box also re-renders a completely unrelated sidebar every single keystroke.

**Think through**: which React DevTools setting shows this happening visually, and what does it usually mean when the whole page lights up.

**Hint**: turn on "highlight updates when components render," then check where the search box's state actually lives, state that lives too high up the tree re-renders everything below it.

---

### 4. A fetch call returns 401 only in production, works locally

An API call works fine on `localhost`, returns 401 Unauthorized once deployed.

**Think through**: what differs between the two environments that could affect an auth header.

**Hint**: check the Network tab's request headers on the deployed site specifically, an environment variable holding the API URL or token might be missing or pointing at the wrong value in that environment.

---

### 5. A page briefly shows the wrong content, then flashes to the right content

A page shows "Guest" for a split second before switching to the logged-in user's name, and the console logs a hydration warning.

**Think through**: what does this describe, and where would you look first in a Next.js app.

**Hint**: this is the hydration mismatch pattern, check for a browser-only read (`localStorage`, `window`) happening outside a `useEffect`.

---

### 6. A layout looks correct in the Elements panel but wrong on screen

Inspecting an element shows the CSS you expect, but the element still renders at the wrong size on the page.

**Think through**: what tab shows the actual final, computed value after every conflicting rule has been resolved.

**Hint**: the Computed tab, expand the specific property in question and check which rule actually won.

---

### 7. The app gets slower the longer it stays open

A single-page app feels fine right after loading, noticeably sluggish after using it for ten minutes without a refresh.

**Think through**: what kind of bug causes something to degrade over time rather than being wrong from the start, and which panel would confirm it.

**Hint**: this is the shape of a memory leak, take two heap snapshots minutes apart during normal use and compare what grew.

---

### 8. Reproduce, then shrink

Pick any real bug you have hit before (or intentionally introduce one into a small test component). Write down the exact reproduction steps, then delete code from the reproduction until the bug just barely still happens.

**Think through**: how much of the original code turned out to be irrelevant to the actual bug.

**Hint**: this is the minimal reproduction exercise from file 11, applied for real once, it is a different skill than reading about it.
