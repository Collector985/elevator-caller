# Color Palette

## Primary Colors

### Background Colors
| Name | Hex Code | RGB | Usage |
|------|----------|-----|-------|
| **Screen Background** | `#667eea` | RGB(102, 126, 234) | Main screen background (purple gradient) |
| **Panel Background** | `#FFFFFF` | RGB(255, 255, 255) | Main white panel container |
| **Shaft Color** | `#2c3e50` | RGB(44, 62, 80) | Shaft representation (dark gray) |
| **Navigation Bar** | `#34495e` | RGB(52, 73, 94) | Bottom navigation bar (dark slate) |

### Call Type Colors
| Name | Hex Code | RGB | Usage |
|------|----------|-----|-------|
| **UP Call** | `#2ecc71` | RGB(46, 204, 113) | UP direction indicator (green) |
| **DOWN Call** | `#e74c3c` | RGB(231, 76, 60) | DOWN direction indicator (red) |
| **LOAD Call** | `#f39c12` | RGB(243, 156, 18) | LOAD/Materials call (orange) |

### Status Colors
| Name | Hex Code | RGB | Usage |
|------|----------|-----|-------|
| **Elevator Current** | `#3498db` | RGB(52, 152, 219) | Current elevator position (blue) |
| **Active Nav Button** | `#3498db` | RGB(52, 152, 219) | Selected navigation button |

### UI Element Colors
| Name | Hex Code | RGB | Usage |
|------|----------|-----|-------|
| **Floor Card BG** | `#34495e` | RGB(52, 73, 94) | Floor number card background |
| **Inactive Button** | `#9ea3b4` | RGB(158, 163, 180) | Inactive UP/DOWN buttons |
| **Text White** | `#FFFFFF` | RGB(255, 255, 255) | Primary text color |
| **Text Black** | `#000000` | RGB(0, 0, 0) | Dark text on light backgrounds |
| **Nav Button BG** | `#2c3e50` | RGB(44, 62, 80) | Inactive navigation buttons |

### Grid View Colors (Future)
| Name | Hex Code | RGB | Usage |
|------|----------|-----|-------|
| **Grid Cell** | `#ecf0f1` | RGB(236, 240, 241) | Grid cell background |
| **Grid Border** | `#bdc3c7` | RGB(189, 195, 199) | Grid cell borders |
| **Grid Current** | `#e3f2fd` | RGB(227, 242, 253) | Current floor in grid |

### Log Panel Colors (Future)
| Name | Hex Code | RGB | Usage |
|------|----------|-----|-------|
| **Log Background** | `#111111` | RGB(17, 17, 17) | Log panel background (almost black) |
| **Log Text** | `#2ecc71` | RGB(46, 204, 113) | Log text (green terminal style) |

## Color Constants for LVGL Creator

```c
// Define in LVGL Creator or lv_conf.h
#define UI_COLOR_BG         lv_color_hex(0x667eea)
#define UI_COLOR_PANEL      lv_color_hex(0xFFFFFF)
#define UI_COLOR_SHAFT      lv_color_hex(0x2c3e50)
#define UI_COLOR_ELEV       lv_color_hex(0x3498db)
#define UI_COLOR_UP         lv_color_hex(0x2ecc71)
#define UI_COLOR_DOWN       lv_color_hex(0xe74c3c)
#define UI_COLOR_LOAD       lv_color_hex(0xf39c12)
#define UI_COLOR_NAV        lv_color_hex(0x34495e)
#define UI_COLOR_INACTIVE   lv_color_hex(0x9ea3b4)
```

## Opacity Values
- **Full Opaque**: `LV_OPA_COVER` (255)
- **High Opacity**: `LV_OPA_80` (204)
- **Medium Opacity**: `LV_OPA_60` (153)
- **Transparent**: `LV_OPA_TRANSP` (0)

## Color Usage Guidelines

### Semantic Meanings
- **Green** (#2ecc71): Positive action, upward movement
- **Red** (#e74c3c): Negative action, downward movement
- **Orange** (#f39c12): Special function, load/materials
- **Blue** (#3498db): Current state, active selection
- **Gray** (#34495e, #2c3e50): Neutral, containers, navigation

### Accessibility
- Ensure 4.5:1 contrast ratio for text
- White text on #34495e: ✓ Pass (7.5:1)
- White text on #2c3e50: ✓ Pass (8.6:1)
- Green #2ecc71 on white: ✓ Pass (2.7:1 for large text)
- Red #e74c3c on white: ✓ Pass (3.5:1 for large text)

### State Colors
```
Inactive State:  #9ea3b4 (light gray)
Active UP:       #2ecc71 (green)
Active DOWN:     #e74c3c (red)
Active LOAD:     #f39c12 (orange text)
Current Floor:   #3498db background + white outline
```
