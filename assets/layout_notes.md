# Elevator Caller Layout Notes (480×800 portrait)

## Screen Regions
1. **Header (0–120 px)**
   - Gradient background pulled from palette (`#667eea` → `#764ba2`).
   - Title text (“Elevator Calls”) centered; use LVGL XML `<label>` with `align="top_mid"`.
   - Subtext row for legend (UP/LOAD/DOWN) using icon sprites or inline colored bars.

2. **Floor Grid (120–720 px)**
   - 40 rows at ~14 px height + 4 px spacing fits 600 px vertical span.
   - Each row: `F##` label + three 80×8 bars (UP green, LOAD amber, DOWN red).
   - Elevator car indicator: highlight current floor row with accent color `#1E88E5`.
   - Optional RSSI mini-bars next to each floor (reuse `.rssi-wave` idea from simulator).

3. **Footer (720–800 px)**
   - Status text (connection state, last packet, RSSI) left-aligned.
   - Two buttons (e.g., “Silence”, “Clear All”) using palette `#ecf0f1` background / `#3498db` border.

## Widget Mapping for LVGL XML
- Use `<obj>` with `flex_flow="column"` for the floor list container; wrap rows inside.
- Each row can be `<obj class="floor-row">` with `layout="flex" align="left"`.
- Bars can be `<obj>` with custom style (width/height) or `<bar>` widget for animated fill.

## Interaction
- Tap floor row → send clear command (`LV_EVENT_CLICKED`).
- Long press (optional) to bring up detail popup; map to `<event long_press>`. 

## Fonts
- Titles: `lv_font_montserrat_28`.
- Rows: `lv_font_montserrat_16` for clarity on 7" panel.
- Status: `lv_font_montserrat_18`.

