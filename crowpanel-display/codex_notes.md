# Codex Notes

## Current Display State
- Panel orientation set to portrait (480×800) with full 24‑bit RGB output.
- Boot sequence runs a LovyanGFX full‑screen sanity pattern for 60s (gradient, color bars, anti‑aliased text via sprite fonts) before launching the LVGL UI.
- Runtime UI still uses LVGL for layout/touch; floor grid is LVGL labels plus indicator bars. Visual quality won’t match SquareLine-generated layouts yet.

## Outstanding Work
- To match SquareLine samples, we need the SquareLine project export (`ui.c/ui.h`) or detailed mockups. Without that, the LVGL UI is hand-built and minimal.
- Touch driver still TODO; LVGL calls exist but there’s no actual touch input hookup.
- Perf/memory overlay currently uses LVGL defaults; consider custom Lovyan sprite overlay for smoother fonts + real CPU/RAM telemetry.

## How to Iterate
1. Provide SquareLine assets if you want identical layouts. I’ll integrate them into the LVGL build.
2. If you prefer a custom Lovyan UI (no LVGL), let me know so I can refactor the render loop to pure sprite-based drawing.
3. Use `pio run -t upload` to flash; `python -m serial.tools.miniterm /dev/ttyUSB0 115200` for logs (PlatformIO monitor fails on this shell).

– Codex
