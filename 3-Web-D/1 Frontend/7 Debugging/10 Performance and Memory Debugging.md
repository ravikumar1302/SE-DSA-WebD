# Performance and Memory Debugging

"The page feels slow" is not specific enough to fix. The Performance and Memory panels turn a vague feeling into an actual measurement, showing where the time or memory really goes.

## Recording a Performance profile

Open the Performance panel, click record, interact with the page the way a user experiencing the slowness would, stop recording. The result is a timeline with several rows stacked vertically.

```
Main thread activity  ─────────────────────────────────────►
Frames                [ ][ ][ ][ gap = dropped frame ][ ]
Scripting              ███ long task blocking the thread
Rendering                  ██
Painting                     █
```

A long, unbroken block in the "Scripting" row means JavaScript is blocking the main thread for that whole stretch, nothing else (rendering, responding to clicks) can happen until it finishes. Clicking that block shows the exact function responsible, often the fastest way to find "which function is actually slow" without guessing.

## Dropped frames and jank

Smooth animation needs a new frame roughly every 16ms (60 frames per second). A gap in the "Frames" row means a frame was dropped, usually because a long script blocked the main thread right when a frame was due. This is the technical explanation behind what feels like "jank," a stutter during scrolling or an animation.

## The Performance tab versus the React Profiler

| | Performance tab (browser) | React Profiler (React DevTools) |
|---|---|---|
| Shows | Everything the browser did: scripting, layout, painting, network | Only React component renders |
| Best for | "Is the page itself slow, at the browser level" | "Which component's render is slow" |
| Granularity | The whole page | Component by component |

Use the Performance tab first for a general "something feels slow," then the React Profiler (file 7) specifically once the cause is confirmed to be React re-rendering rather than, say, a large image decode or a layout thrashing loop.

## Memory leaks

A memory leak means memory usage keeps climbing and never comes back down, even after the thing that used it should be gone, for example navigating away from a page whose event listener was never removed.

```js
useEffect(() => {
  window.addEventListener("resize", handleResize);
  // missing: return () => window.removeEventListener("resize", handleResize);
}, []);
```

Without the cleanup function, every time this component mounts, a new listener is added and never removed, even after the component unmounts. Ten mounts and unmounts leave ten stacked listeners, all still running, all holding onto memory the component should have released.

## Taking a heap snapshot

The Memory panel's "Heap snapshot" option captures every object currently in memory at that moment. Taking one snapshot, performing an action that should release memory (closing a modal, navigating away), then taking a second snapshot and comparing the two, shows exactly what grew and did not shrink back, often pointing straight at the leaking reference.

📌 Reach for a heap snapshot specifically when memory usage (visible in the Task Manager, `Shift+Esc` in Chrome, or the Memory panel itself) keeps climbing across normal use and never drops, not for a one-off slow render, that is a Performance panel or React Profiler job instead.

## Lighthouse, a quick health check

The Lighthouse tab runs an automated audit and scores Performance, Accessibility, Best Practices and SEO, with specific, actionable suggestions attached to each low score (an oversized image, a render-blocking script, missing alt text). It will not pinpoint a specific bug the way the Performance panel does, but it is a fast first pass to catch obvious, common problems before digging deeper manually.

## Key takeaways

- The Performance panel shows exactly which function blocked the main thread, turning "it feels slow" into a specific answer.
- Dropped frames in the timeline are the technical cause of visible jank during scrolling or animation.
- A missing cleanup function in `useEffect` (an event listener never removed) is one of the most common sources of a memory leak in React apps.
- Lighthouse is a fast first-pass health check, the Performance panel and heap snapshots are for digging into a specific, already-suspected problem.
