# Documentation Update Summary

**Date**: 2025-11-09

## What Was Updated

All documentation has been updated to clarify the hardware platforms and prevent confusion between different devices.

### Files Updated

1. ✅ **HARDWARE_NOTES.md** - New comprehensive hardware reference
2. ✅ **README.md** - Main project documentation
3. ✅ **QUICK_START.md** - Quick start guide

## Key Clarifications Made

### Platform Confusion (ESP32 vs Raspberry Pi)

**The Problem**: Confusion about which devices use which chips.

**The Clarification**:
- **Floor Nodes**: RP2040 (Raspberry Pi chip on Adafruit Feather boards)
- **Gateway (T-ETH Elite)**: ESP32-S3 (Espressif, NOT Raspberry Pi!)
- **Display (CrowPanel)**: ESP32-S3 (Espressif, NOT Raspberry Pi!)
- **T-Beam Simulator**: ESP32-S3 (Espressif, NOT Raspberry Pi!)

**Only the floor nodes use Raspberry Pi silicon!**

### Device Identification Issues

Added clear identification table in all docs:

| Device | Chip | Platform | Upload Port | Firmware Location |
|--------|------|----------|-------------|-------------------|
| **T-ETH Elite Gateway** | ESP32-S3 | `espressif32` | `/dev/ttyACM0` | `elevator-gateway-firmware/` |
| **CrowPanel Display** | ESP32-S3 | `espressif32` | `/dev/ttyACM0` | `crowpanel-display/` |
| **T-Beam** | ESP32-S3 | `espressif32` | `/dev/ttyACM0` | `floor-node-firmware/` (simulator env) |
| **Adafruit Feather RP2040** | RP2040 | `raspberrypi` | `/dev/ttyACM0` | `floor-node-firmware/` (main env) |

### Common Mistakes Documented

#### Wrong Firmware Upload

**Symptom**: T-Beam shows "SX1302 initialization FAILED!"
**Cause**: Gateway firmware was uploaded to T-Beam
**Fix**: Re-upload with `pio run -e tbeam-supreme-simulator --target upload`

**Symptom**: T-ETH Elite shows "SX1262 initialization failed"
**Cause**: T-Beam firmware was uploaded to gateway
**Fix**: Re-upload from `elevator-gateway-firmware/` directory

#### Serial Monitor Issues

**Symptom**: `UnknownPlatform: Unknown development platform 'raspberrypi.git'`
**Cause**: Running `pio device monitor` from `floor-node-firmware` directory
**Fix**: Use `screen /dev/ttyACM0 115200` or change to different directory

## New Sections Added

### HARDWARE_NOTES.md

- ✅ Platform clarification section at the top
- ✅ Upload port issues explanation
- ✅ Device identification table
- ✅ Expanded T-Beam section with:
  - Pin definitions
  - Expected serial output
  - Troubleshooting guide
  - Testing procedures
  - Serial monitoring options

### README.md

- ✅ Platform clarification in hardware section
- ✅ T-Beam listed as optional testing equipment
- ✅ Updated upload procedures with environment flags
- ✅ Device identification table in troubleshooting
- ✅ Added T-Beam troubleshooting tips

### QUICK_START.md

- ✅ Platform clarification at the top
- ✅ Critical warning about connecting one device at a time
- ✅ Upload procedures with explicit environment flags
- ✅ Common upload mistakes section
- ✅ Serial monitor troubleshooting
- ✅ Device identification table
- ✅ T-Beam simulator troubleshooting

## Upload Procedures Now Clearly Documented

### Gateway (T-ETH Elite + T-SX1302)
```bash
cd elevator-gateway-firmware
pio run --target upload --upload-port /dev/ttyACM0
```

### Display (CrowPanel)
```bash
cd crowpanel-display
pio run --target upload --upload-port /dev/ttyACM0
```

### Floor Nodes (Feather RP2040)
```bash
cd floor-node-firmware
pio run -e adafruit_feather_rp2040 --target upload --upload-port /dev/ttyACM0
```

### T-Beam Simulator
```bash
cd floor-node-firmware
pio run -e tbeam-supreme-simulator --target upload --upload-port /dev/ttyACM0
```

## Serial Monitor Options Documented

### Option 1: screen (Recommended)
```bash
screen /dev/ttyACM0 115200
# Exit: Ctrl+A, then K, then Y
```

### Option 2: Change directory first
```bash
cd ../elevator-gateway-firmware
pio device monitor --port /dev/ttyACM0 --baud 115200
```

### Option 3: Direct read
```bash
cat /dev/ttyACM0
```

## Incident Documentation

### What Happened
1. User had T-Beam connected
2. We accidentally uploaded gateway firmware (from `elevator-gateway-firmware/`)
3. T-Beam booted and showed "SX1302 initialization FAILED!"
4. This caused confusion about which device was connected
5. We correctly re-uploaded T-Beam simulator firmware
6. User tried to use `pio device monitor` from `floor-node-firmware` directory
7. Got "UnknownPlatform" error because that directory uses RP2040 platform

### Lessons Learned
1. **Always specify which device is connected** before uploading
2. **All ESP32-S3 devices** (Gateway, Display, T-Beam) look similar in serial output
3. **Only the firmware they're running** differentiates them
4. **PlatformIO reads platformio.ini** even for monitor commands
5. **screen is more reliable** than `pio device monitor` when switching between platforms

### Prevention
All documentation now includes:
- ⚠️ Warning to connect only one device at a time
- Clear device identification tables
- Explicit environment flags in all upload commands
- Troubleshooting section for wrong firmware uploads
- Serial monitor alternatives that work from any directory

## Files for Reference

- **HARDWARE_NOTES.md** - Detailed hardware reference (440 lines)
- **README.md** - Main project documentation (444 lines)
- **QUICK_START.md** - Quick start guide (207 lines)
- **DOCUMENTATION_UPDATE_SUMMARY.md** - This file

## Next Steps for Users

1. Read HARDWARE_NOTES.md for detailed hardware information
2. Use README.md for overall system understanding
3. Use QUICK_START.md for step-by-step setup
4. Always check device before uploading firmware
5. Use `screen /dev/ttyACM0 115200` for serial monitoring when in doubt

---

*Documentation updated by Claude Code on 2025-11-09*
*All confusion resolved and preventive measures documented*
