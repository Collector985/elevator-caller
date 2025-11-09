# LVGL Elevator Display - Project Specification

## Overview
This document specifies the complete LVGL design for the CrowPanel 7" elevator display interface.

## Hardware Specifications
- **Display**: CrowPanel 7" Advance (Elecrow)
- **Resolution**: 800×480 pixels (landscape orientation)
- **Touch**: Capacitive touch (GT911)
- **MCU**: ESP32-S3 with PSRAM
- **Interface**: I2C communication with gateway

## Software Stack
- **LVGL Version**: 8.3.0
- **Color Depth**: RGB565 (16-bit)
- **Framework**: Arduino
- **Graphics Driver**: LovyanGFX

## Display Configuration
```c
Screen Width:    480px (after rotation)
Screen Height:   800px (after rotation)
Rotation:        1 (landscape)
Touch Swap XY:   true
Touch Invert Y:  true
DPI:             130
Refresh Rate:    30ms
```

## Memory Settings
```c
LVGL Memory:     128KB
Draw Buffer:     480 × 10 pixels
Color Format:    RGB565 with byte swap
Antialiasing:    Enabled
Shadow Cache:    Disabled (0)
```

## System Features
- **Total Floors**: 37 (configurable via TOTAL_FLOORS)
  - Standard floors: 1-34
  - Parking floors: P1, P2, P3
- **Call Types**: UP, DOWN, LOAD (per floor)
- **Navigation**: 3-screen system (SHAFT, GRID, CONTROL)
- **Current Implementation**: SHAFT view only

## Key Capabilities
1. Real-time call status display (UP/DOWN/LOAD)
2. Current elevator floor highlighting
3. Touch-based call clearing
4. RSSI signal strength display
5. I2C communication with gateway
6. Serial command interface

## Performance Requirements
- Touch response: <50ms
- Display update: 30ms refresh
- I2C polling: 200ms interval
- Smooth animations for state changes

## Design Philosophy
- Industrial, professional appearance
- High contrast for construction site visibility
- Simple, intuitive touch interface
- Minimal color palette for clarity
- Large touch targets (28×28px minimum)
