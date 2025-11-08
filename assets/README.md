# Elevator Caller Asset Pack

This folder captures reusable assets inspired by `elevator_simulator.html` for the 480×800 portrait CrowPanel display.

## Palette
See `palette.json` for the primary brand colors:
- Gradient blues (`#667eea → #764ba2`) for headers and elevator car.
- Functional colors for UP/DOWN/LOAD calls (green/red/amber).
- Neutral greys for backgrounds and text.

## Icons (`assets/icons/`)
SVGs sized for LVGL image widgets:
- `up.svg` – rounded square with green arrow.
- `down.svg` – red arrow icon.
- `load.svg` – amber cargo crate.
- `elevator_car.svg` – 60×30 gradient car used in shaft view or legend.

## Layout Notes
`layout_notes.md` outlines how to map the simulator’s building/controls into a 480×800 LVGL screen using XML (header, floor list, footer).

Use these files when authoring LVGL XML (see https://docs.lvgl.io/master/details/xml/index.html) so the embedded UI matches the simulator styling without needing SquareLine.
