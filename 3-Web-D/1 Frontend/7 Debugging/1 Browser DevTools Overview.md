# Browser DevTools Overview

Every modern browser (Chrome, Firefox, Edge) ships a full set of developer tools for free, opened with `F12` or `Ctrl+Shift+I` (`Cmd+Option+I` on Mac). This file maps out the panels so later files can go deep on each one without re-explaining where to find it.

## The panel map

| Panel | What it shows | Use it for |
|---|---|---|
| Elements | The live DOM tree and computed CSS | Inspecting or editing HTML/CSS on the fly, file 7 |
| Console | Logs, errors, a live JavaScript prompt | Reading errors, running quick expressions, file 3 and 5 |
| Sources | Every loaded file, breakpoints, call stack | Stepping through code line by line, file 4 |
| Network | Every request the page made | Checking API calls, status codes, payloads, file 6 |
| Application | Storage: cookies, localStorage, sessionStorage, cache | Inspecting or clearing saved data |
| Performance | A recording of what the browser did over time | Finding slow renders or scripts, file 11 |
| Memory | Heap snapshots | Finding memory leaks, file 11 |

📌 Elements, Console, Sources and Network cover the vast majority of day-to-day debugging. The rest come up less often but matter when they do.

## Opening DevTools at the right spot

Right-click any element on the page and choose "Inspect" instead of opening DevTools generically and hunting for the element in a large tree. This jumps straight to the Elements panel with that exact node selected, which is faster for layout and styling bugs.

## The Console is more than an error log

The Console panel does three separate jobs, worth telling apart:

```
1. Shows errors and warnings the page threw on its own
2. Shows anything a running console.log(...) call printed
3. Is a live JavaScript prompt, type an expression, press enter, see the result
```

That third job is easy to miss as a beginner. You can type `document.querySelectorAll("button").length` directly into the Console right now and get a real answer, no code change needed. This turns "let me add a log and refresh" into "let me just ask the browser directly," often faster.

## Docking and workflow tips

- Docking DevTools to the side (rather than the bottom) leaves more vertical space to see a real page layout while debugging it.
- The device toolbar icon (a phone and tablet icon, top left of DevTools) simulates different screen sizes, useful for responsive layout bugs without needing a second device.
- DevTools settings (gear icon) let you preserve console log history across page reloads and enable dark mode, small things that add up over daily use.

## Firefox and Edge

Chrome DevTools are used as the reference here since they are the most common, but Firefox DevTools and Edge DevTools (Edge is Chromium-based, nearly identical to Chrome's) cover the same panels with the same core ideas. Everything in this folder transfers with only minor naming differences.

## Key takeaways

- DevTools panels map to specific jobs: Elements for the DOM/CSS, Console for logs and quick checks, Sources for stepping through code, Network for requests.
- Right-click an element and "Inspect" jumps straight to it, faster than searching a large tree.
- The Console is also a live JavaScript prompt, not just somewhere logs land.
- The core panels and ideas are the same across Chrome, Firefox and Edge.
