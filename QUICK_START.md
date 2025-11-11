# 🚀 Quick Start Guide - Elevator LoRa System

## Hardware You Have

✅ **Adafruit Feather RP2040** (floor nodes) - Raspberry Pi RP2040 chip
✅ **LILYGO T-ETH Elite + T-SX1302 Gateway** (central receiver) - ESP32-S3, NOT Raspberry Pi!
✅ **CrowPanel 7" Display** (operator interface) - ESP32-S3
✅ **LILYGO T-Beam** (optional testing simulator) - ESP32-S3

### ⚠️ Platform Clarification

**Only the floor nodes use Raspberry Pi silicon (RP2040)**. The gateway, display, and T-Beam all use ESP32-S3!

## Configuration - P3, P2, P1, Ground, Floors 1-25 (29 Total)

Your system supports:
- **P3** = Parking Level 3 (Floor ID: 253)
- **P2** = Parking Level 2 (Floor ID: 254)
- **P1** = Parking Level 1 (Floor ID: 255)
- **G** = Ground Floor (Floor ID: 1)
- **1-25** = Floors 1-25 (Floor IDs: 2-26)

## Step-by-Step Setup

### 1. Upload Firmware (One Time Per Device)

**⚠️ CRITICAL**: Connect only ONE device at a time to avoid uploading wrong firmware!

```bash
# Gateway - Upload to T-ETH Elite (connect gateway first)
cd elevator-gateway-firmware
pio run --target upload --upload-port /dev/ttyACM0
# Disconnect gateway before next step!

# Display - Upload to CrowPanel (connect display)
cd ../crowpanel-display
pio run --target upload --upload-port /dev/ttyACM0
# Disconnect display before next step!

# Floor nodes - Upload to ALL Feather RP2040 boards (connect one at a time)
cd ../floor-node-firmware
pio run -e adafruit_feather_rp2040 --target upload --upload-port /dev/ttyACM0
# Repeat for each floor node

# T-Beam Simulator (optional, for testing without floor nodes)
cd floor-node-firmware
pio run -e tbeam-supreme-simulator --target upload --upload-port /dev/ttyACM0
```

### Common Upload Mistakes

**If T-Beam shows "SX1302 initialization FAILED!":**
- You uploaded gateway firmware to the T-Beam (wrong!)
- Re-upload with: `pio run -e tbeam-supreme-simulator --target upload`

**If T-ETH Elite shows "SX1262 initialization failed":**
- You uploaded T-Beam simulator firmware to the gateway (wrong!)
- Re-upload from `elevator-gateway-firmware/` directory

###2. Configure Floor Nodes (Easy Method - No Recompiling!)

For each floor node:

**Step 1:** Hold all 3 buttons (UP + DOWN + LOAD) while powering on
- All 3 LEDs will flash together = PAIRING MODE

**Step 2:** Go to CrowPanel display
- Touch the "CONFIG" button (top right)
- Touch the floor you want to assign (e.g., "P3", "G", "15")
- The display will show "Waiting for node..."

**Step 3:** The floor node LEDs will flash rapidly, then solid
- Floor assigned! The node will remember this forever (stored in EEPROM)
- Repeat for all 29 floor nodes

### 3. Floor Label Mapping

When configuring on CrowPanel, you'll see:

```
Display Shows    Internal ID    Physical Location
─────────────────────────────────────────────────
P3               253            Parking Level 3
P2               254            Parking Level 2
P1               255            Parking Level 1
G                1              Ground Floor
1                2              First Floor
2                3              Second Floor
...              ...            ...
25               26             25th Floor
```

## How Pairing Works

1. **Power on floor node while holding all 3 buttons** → Enters pairing mode
2. Floor node broadcasts "I need a floor number!" every second
3. **Touch floor on CrowPanel** → Sends floor assignment via LoRa
4. Floor node receives assignment, saves to EEPROM, exits pairing mode
5. Done! That node is now permanently assigned to that floor

## Normal Operation

After configuration:

1. **Press UP/DOWN/LOAD button** on any floor → LED lights up
2. **Call appears on CrowPanel** → Operator sees it
3. **Elevator moves to floor** → Auto-clears when RSSI > -60 dBm
4. **Or touch floor on display** → Manually clear the call

## Configuration Settings

All config is in `platformio.ini` files - you can change:

### Floor Node (`floor-node-firmware/platformio.ini`)
```ini
-D CPU_SPEED_MHZ=48         # Lower = longer battery life
-D LORA_FREQUENCY=915.0     # 915 MHz (US) or 868 MHz (EU)
-D SPREADING_FACTOR=9       # 7-12, higher = longer range
-D BEACON_INTERVAL_MS=2000  # How often to send "I'm still waiting"
```

### Gateway (`elevator-gateway-firmware/platformio.ini`)
```ini
-D TOTAL_FLOORS=29          # P3, P2, P1, G, 1-25
-D AUTO_CLEAR_RSSI=-60      # Signal strength for auto-clear
-D GATEWAY_FREQUENCY=915.0  # Must match floor nodes
```

## Troubleshooting

### "UnknownPlatform" error when using pio device monitor
```
UnknownPlatform: Unknown development platform 'https://github.com/maxgerhardt/platform-raspberrypi.git'
```

**Cause**: You're in the `floor-node-firmware` directory, which uses the RP2040 platform.

**Solution**: Use one of these methods:
```bash
# Method 1: Use screen (works from any directory)
screen /dev/ttyACM0 115200
# Exit: Ctrl+A, then K, then Y

# Method 2: Change to a different project directory
cd ../elevator-gateway-firmware
pio device monitor --port /dev/ttyACM0 --baud 115200

# Method 3: Install the RP2040 platform (if you need it)
cd floor-node-firmware
pio platform install https://github.com/maxgerhardt/platform-raspberrypi.git
```

### Wrong firmware uploaded (device identification)

| What You See | Device Connected | Fix |
|--------------|------------------|-----|
| "SX1302 initialization FAILED!" | T-Beam | Re-upload from `floor-node-firmware/` with `-e tbeam-supreme-simulator` |
| "SX1262 initialization failed" | T-ETH Elite | Re-upload from `elevator-gateway-firmware/` |
| Device doesn't boot | Wrong firmware | Check serial output to identify device |

### Floor node won't enter pairing mode
- Hold all 3 buttons BEFORE powering on
- Keep holding for 2-3 seconds after power on
- LEDs should flash together if in pairing mode

### Can't assign floor on CrowPanel
- Make sure floor node is in pairing mode (LEDs flashing)
- Check LoRa frequency matches (915 MHz or 868 MHz)
- Try moving floor node closer to gateway

### Floor node forgets its floor number
- Check battery voltage (need 6V+ minimum)
- EEPROM should retain forever, but try reassigning
- If problem persists, check for EEPROM library issues

### Call doesn't auto-clear
- Check RSSI threshold (-60 dBm default)
- Verify elevator position broadcasts working
- Make sure floor node is receiving position updates
- Try moving antenna to elevator car roof

### T-Beam simulator not sending packets
- Check pin definitions in `simulator.cpp` match your T-Beam version
- Verify antenna is connected (never TX without antenna!)
- Use `screen /dev/ttyACM0 115200` to check serial output
- Ensure frequency matches gateway (915.0 MHz)

## Web Interface

Access at `http://192.168.1.100/` (or your configured IP)

**Endpoints:**
- `/` - Main status page
- `/status` - JSON system stats
- `/floors` - JSON active calls
- `/clear?floor=X&type=Y` - Clear call (type: 1=UP, 2=DOWN, 3=LOAD)

## Battery Life

With default settings (48 MHz CPU, 2 second beacons):
- **Idle** (no calls): 7+ years
- **Moderate use** (10 calls/day): 307 days
- **Heavy use** (50 calls/day): 180 days

## Need Help?

1. Check serial monitor output (115200 baud)
2. Floor nodes print their status on startup
3. Gateway shows all received packets
4. Use web simulator (`elevator_simulator.html`) to test concepts

---

**That's it!** Upload firmware once, then configure floor numbers via the CrowPanel. No recompiling needed! 🎉
