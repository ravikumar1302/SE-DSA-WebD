# CSS and Layout Debugging

Layout bugs are different from logic bugs, there is no error message, just something visually in the wrong place. DevTools has purpose-built tools for this that beat guessing values and refreshing repeatedly.

## The box model inspector

Selecting any element in the Elements panel shows a small diagram at the bottom (or in the Computed tab): nested boxes for content, padding, border and margin, each labelled with its actual pixel value.

```
┌───────────────────────────── margin ──────────────────────────────┐
│  ┌───────────────────────── border ──────────────────────────┐    │
│  │  ┌─────────────────────  padding  ──────────────────────┐ │    │
│  │  │                                                       │ │    │
│  │  │                     content                           │ │    │
│  │  │                                                       │ │    │
│  │  └───────────────────────────────────────────────────────┘ │    │
│  └───────────────────────────────────────────────────────────┘    │
└──────────────────────────────────────────────────────────────────┘
```

This answers "why is there a gap here" or "why is this wider than I set it" faster than reading the stylesheet, since it shows the real computed numbers, after every rule (including inherited and browser-default ones) has already been applied.

## Computed styles, seeing what actually won

CSS rules can conflict, several selectors can target the same element, and only one value wins for each property. The "Computed" tab lists the final value the browser actually used for every property, and clicking one expands to show every rule that tried to set it, with the winning one highlighted.

📌 This is the fastest way to answer "why isn't my CSS applying," a rule further down the cascade, a more specific selector, or `!important` somewhere is usually the answer, and the Computed tab shows exactly which one won without needing to trace the cascade by hand.

## Editing styles live

The Styles tab (next to Elements) lets you edit any CSS property directly and see the page update instantly, no save or refresh needed. This is the fastest way to test a fix: try a value, see if it looks right, adjust, repeat. Once satisfied, copy the change back into the actual source file, DevTools edits do not persist after a reload.

## Toggling element states

A `:hover`, `:focus` or `:active` style is hard to inspect normally, moving the mouse to trigger `:hover` also moves it away from DevTools. The Styles panel has a ":hov" button (or right-click -> "Force state") that locks an element into that state so its styles can be inspected and edited normally.

## The flex and grid overlays

Any element with `display: flex` or `display: grid` shows a small badge next to it in the Elements panel. Clicking the badge draws a visual overlay directly on the page: for flex, arrows showing the main and cross axis, for grid, numbered grid lines and cell boundaries.

```
Without the overlay: guessing which axis "justify-content" affects
With the overlay: an arrow drawn on the real page showing the axis directly
```

This turns flex and grid debugging from "adjust a value, refresh, squint" into "look at the arrow, it is immediately obvious which direction is which."

## Common layout bugs and where to look

| Symptom | Likely cause | Where to check |
|---|---|---|
| Unexpected gap around an element | Margin collapsing, or default browser margin on that element | Box model diagram |
| Element wider or taller than expected | `box-sizing` default (`content-box`) adding padding/border on top of the set width | Computed tab, check `box-sizing` |
| A style not applying at all | A more specific selector, later rule, or `!important` elsewhere winning | Computed tab, expand the property |
| Flex items not aligning as expected | Wrong axis assumed, `justify-content` and `align-items` control different axes | Flex overlay |
| An element overlapping others unexpectedly | `position: absolute`/`fixed` removed it from normal flow | Box model, check `position` and `z-index` |

## Key takeaways

- The box model inspector shows real computed pixel values for content, padding, border and margin, faster than reading the stylesheet.
- The Computed tab shows exactly which CSS rule won when several conflict, answering "why isn't my style applying."
- Force-state toggles let you inspect `:hover`/`:focus` styles without the mouse fighting DevTools.
- The flex and grid overlays draw the actual axes and grid lines on the page, removing the guesswork.
