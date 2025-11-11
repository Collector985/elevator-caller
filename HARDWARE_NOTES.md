# Hardware Notes

## Important Platform Clarifications

### ⚠️ Common Confusion - ESP32 vs Raspberry Pi

This project uses **three different microcontroller platforms**:

1. **T-ETH Elite Gateway** - Uses **ESP32-S3** (Espressif, NOT Raspberry Pi)
2. **Floor Nodes** - Uses **RP2040** (Raspberry Pi silicon, on Adafruit Feather boards)
3. **T-Beam Simulator** - Uses **ESP32-S3** (Espressif, NOT Raspberry Pi)
4. **CrowPanel Display** - Uses **ESP32-S3** (Espressif, NOT Raspberry Pi)

**Key Point**: Only the floor nodes use Raspberry Pi silicon (RP2040 chip). Everything else is ESP32-S3!

### Upload Port Issues

When you see `UnknownPlatform: Unknown development platform 'https://github.com/maxgerhardt/platform-raspberrypi.git'`:
- This means you're in the `floor-node-firmware` directory
- PlatformIO reads `platformio.ini` even for commands like `pio device monitor`
- **Solution**: Change to a different directory or use `screen /dev/ttyACM0 115200`

### Device Identification

| Device | Chip | Platform | Upload Port | Firmware Location |
|--------|------|----------|-------------|-------------------|
| **T-ETH Elite Gateway** | ESP32-S3 | `espressif32` | `/dev/ttyACM0` | `elevator-gateway-firmware/` |
| **CrowPanel Display** | ESP32-S3 | `espressif32` | `/dev/ttyACM0` | `crowpanel-display/` |
| **T-Beam** | ESP32-S3 | `espressif32` | `/dev/ttyACM0` | `floor-node-firmware/` (simulator env) |
| **Adafruit Feather RP2040** | RP2040 | `raspberrypi` | `/dev/ttyACM0` | `floor-node-firmware/` (main env) |

**All use the same USB port (`/dev/ttyACM0`) - only one can be connected at a time!**

---

## T-ETH Elite + T-SX1302 Gateway Configuration

### Overview
The gateway uses the LILYGO T-ETH Elite ESP32-S3 board with the T-SX1302 LoRa Gateway Shield for 8-channel simultaneous LoRa packet reception.

**Platform**: `espressif32` (ESP32-S3, NOT Raspberry Pi!)

### Hardware Stack
```
┌─────────────────────────────────┐
│   T-SX1302 LoRa Gateway Shield  │  ← 8-channel concentrator
│   - SX1302 baseband processor   │
│   - SX1250 radio frontends (×2) │
│   - GPS module                  │
└────────────┬────────────────────┘
             │ SPI Bus
┌────────────▼────────────────────┐
│   T-ETH Elite ESP32-S3          │  ← Main controller
│   - ESP32-S3 (240MHz, dual-core)│
│   - 8MB Flash / 8MB PSRAM       │
│   - W5500 Ethernet              │
│   - I2C for display             │
└─────────────────────────────────┘
```

### Pin Assignments (T-ETH Elite)

#### SX1302 LoRa Gateway Interface
- **SPI Bus** (shared with SD card)
  - MISO: GPIO 9
  - MOSI: GPIO 11
  - SCLK: GPIO 10
  - CS: GPIO 40 (dedicated to SX1302)
- **Control Pins**
  - RESET: GPIO 46
  - IRQ/DIO: GPIO 8
  - BUSY: GPIO 16

#### W5500 Ethernet Interface
- **SPI Bus** (separate from LoRa)
  - MISO: GPIO 47
  - MOSI: GPIO 21
  - SCLK: GPIO 48
  - CS: GPIO 45
- **Control Pins**
  - INT: GPIO 14
  - RST: GPIO -1 (not used)

#### I2C Interface (CrowPanel Display)
- **I2C Bus**
  - SDA: GPIO 17
  - SCL: GPIO 18
  - Slave Address: 0x08

#### GPS Module (on T-SX1302 shield)
- RX: GPIO 39
- TX: GPIO 42

#### Status LED
- LED: GPIO 38

### Build Configuration

#### PlatformIO Settings
```ini
[env:lilygo-t-eth-elite]
platform = espressif32
board = esp32-s3-devkitc-1
framework = arduino

build_flags =
    -D ARDUINO_USB_CDC_ON_BOOT=1
    -D TOTAL_FLOORS=40
    -D GATEWAY_FREQUENCY=915.0
    -D I2C_SLAVE_ADDRESS=0x08
    -D AUTO_CLEAR_RSSI=-60
    -D PROXIMITY_RSSI=-75
    -D CORE_DEBUG_LEVEL=4

lib_deps =
    bblanchon/ArduinoJson@^6.21.3
    Wire
    SPI
    Ethernet
```

### SX1302 HAL Integration

The gateway uses Semtech's native SX1302 HAL (Hardware Abstraction Layer) instead of RadioLib for optimal performance:

#### Key Components
1. **loragw_hal.h** - High-level concentrator API
2. **loragw_reg.h** - Register access functions
3. **loragw_spi.h** - SPI communication layer

#### Implementation Status
- ✅ SPI communication layer implemented
- ✅ Register access working
- ✅ Packet reception (lgw_receive)
- ✅ Packet transmission (lgw_send)
- ✅ Multi-channel configuration
- ⚠️ GPS time sync (TODO)
- ⚠️ Spectral scan (TODO)

### Communication Interfaces

#### LoRa Reception (SX1302)
- **8 simultaneous channels** at SF7-SF12
- **Frequency**: 915.0 MHz (US) / 868.0 MHz (EU)
- **Bandwidth**: 125 kHz
- **Coding Rate**: 4/5
- **Power**: +14 dBm TX

#### I2C to Display (Slave Mode)
The gateway acts as an I2C slave device to the CrowPanel display:
- **Protocol**: Request/Response
- **Data Structure**: Floor status packets (3 bytes)
- **Update Rate**: On-demand (display polls)

#### Ethernet Interface (TODO)
W5500 Ethernet is currently disabled pending library integration:
```cpp
// TODO: Add W5500 Ethernet support
// #include <Ethernet.h>
// #include <WebServer.h>
```

### Current Build Status

#### Gateway Firmware
✅ **Compiles successfully**
- RAM Usage: 6.1% (20,048 bytes)
- Flash Usage: 9.7% (304,201 bytes)

#### Known Issues
1. W5500 Ethernet library not yet integrated
2. GPS module not yet utilized
3. Web server endpoints commented out

### Antenna Configuration

#### Recommended Setup
```
Gateway Box (Control Room)
    │
    │ Coax Cable (50Ω, low loss)
    │
    ▼
┌───────────────────┐
│  Magnetic Mount   │  ← On elevator car roof
│  Antenna          │
│  (915/868 MHz)    │
└───────────────────┘
```

#### Why Elevator Car Mounting Works
- RF signals leak through shaft gaps:
  - Guide rails: 2-5 cm gaps
  - Door frames: 1-2 cm gaps
  - Cable/conduit openings: 10+ cm
- Direct line-of-sight to floor nodes when car passes
- Strong RSSI (>-60 dBm) enables proximity detection

### Upload Procedure

```bash
cd elevator-gateway-firmware
pio run --target upload --upload-port /dev/ttyACM0
```

#### Serial Monitor
```bash
pio device monitor --port /dev/ttyACM0 --baud 115200
```

#### Expected Boot Output
```
========================================
Elevator Gateway System v2.0
T-ETH Elite + T-SX1302
========================================
I2C slave initialized at address 0x08
Initializing SX1302... Connected!
Testing SX1302 registers... OK!
Starting SX1302... Started!
Gateway Ready!
Total Floors: 40
Auto-clear RSSI: -60 dBm
```

### Serial Commands (Testing)

The gateway supports serial commands for testing without floor nodes:

| Command | Description | Example |
|---------|-------------|---------|
| `U<floor>` | Simulate UP call | `U5` (Floor 5 UP) |
| `D<floor>` | Simulate DOWN call | `D10` (Floor 10 DOWN) |
| `L<floor>` | Simulate LOAD call | `L15` (Floor 15 LOAD) |
| `C<floor>` | Clear floor | `C5` (Clear Floor 5) |
| `S` | Show status | Displays all active calls |
| `H` | Help | Show command list |

### Power Requirements

- **Input**: 5V DC, 3A minimum
- **Typical Draw**: ~500-800 mA
- **Peak Draw**: 1.5A (during LoRa TX)
- **Ethernet**: Adds ~100 mA when active

### Next Steps / TODO

- [ ] Integrate W5500 Ethernet library
- [ ] Enable web server endpoints
- [ ] Add GPS time synchronization
- [ ] Implement firmware OTA updates
- [ ] Add system health monitoring
- [ ] Create web dashboard for monitoring

---

## T-Beam (Simulator Configuration)

### ⚠️ IMPORTANT: Don't Mix Up Devices!

The T-Beam looks similar to the T-ETH Elite, but they are **different devices**:

| Feature | T-Beam | T-ETH Elite |
|---------|--------|-------------|
| **Purpose** | Floor call simulator | Gateway controller |
| **Chip** | ESP32-S3 | ESP32-S3 |
| **LoRa** | SX1262 (single channel) | SX1302 (8-channel gateway) |
| **Ethernet** | ❌ No | ✅ W5500 |
| **Display Port** | ❌ No I2C slave | ✅ I2C slave mode |
| **Firmware** | `floor-node-firmware/` | `elevator-gateway-firmware/` |

### Common Mistake (What Just Happened!)

If you upload **gateway firmware** to the T-Beam, you'll see:
```
Elevator Gateway System v2.0
T-ETH Elite + T-SX1302
========================================
I2C slave initialized at address 0x08
Initializing SX1302... FAILED to connect!
SX1302 initialization FAILED!
```

**This is WRONG!** The T-Beam doesn't have an SX1302, so of course it fails.

### Correct Upload Procedure for T-Beam

**Always use the simulator environment:**

```bash
# Make sure you're in the correct directory
cd floor-node-firmware

# Use the tbeam-supreme-simulator environment
pio run -e tbeam-supreme-simulator --target upload --upload-port /dev/ttyACM0
```

**NEVER use:**
```bash
cd elevator-gateway-firmware  # ❌ WRONG for T-Beam!
pio run --target upload        # This uploads gateway firmware
```

### Configuration

```ini
[env:tbeam-supreme-simulator]
platform = espressif32            # ESP32-S3 platform
board = esp32-s3-devkitc-1
framework = arduino

build_flags =
    -D ARDUINO_USB_CDC_ON_BOOT=1
    -D LORA_FREQUENCY=915.0       # Must match gateway
    -D SPREADING_FACTOR=9
    -D TX_POWER=20
    -D TOTAL_FLOORS=40
    -D MIN_CALL_INTERVAL=5000     # 5 seconds minimum
    -D MAX_CALL_INTERVAL=20000    # 20 seconds maximum
    -D SIMULATOR_MODE=1

lib_deps =
    jgromes/RadioLib@^6.4.0       # RadioLib for SX1262
    bblanchon/ArduinoJson@^6.21.3
```

### T-Beam Pin Definitions

The simulator code uses these pins (standard T-Beam v1.2+):

```cpp
// SX1262 LoRa Radio
#define LORA_MISO_PIN   19
#define LORA_MOSI_PIN   27
#define LORA_SCLK_PIN   5
#define LORA_CS_PIN     18
#define LORA_RST_PIN    23
#define LORA_DIO1_PIN   33
#define LORA_BUSY_PIN   32

// Status LED
#define LED_PIN         4
```

**Note**: Pin definitions may vary for different T-Beam versions (v1.0, v1.1, v1.2, Supreme). Check your board's pinout!

### Expected Serial Output

After successful upload and reset:

```
========================================
T-Beam Supreme Floor Call Simulator
Random UP/DOWN/LOAD Testing
========================================
Initializing SX1262... success!
LoRa configured successfully

*** Simulator Started ***
Frequency: 915.0 MHz
Spreading Factor: 9
TX Power: 20 dBm
Total Floors: 40
Call Interval: 5-20 seconds

Sending: Floor 15 - UP
  -> Packet sent successfully
Sending: Floor 23 - DOWN
  -> Packet sent successfully
Sending: Floor 8 - LOAD
  -> Packet sent successfully

========== STATISTICS ==========
Total Calls: 10
  UP:   4 (40%)
  DOWN: 4 (40%)
  LOAD: 2 (20%)
================================
```

### What it Does

The T-Beam simulator generates random floor call requests to test the gateway:
- **Simulates multiple floor nodes** (randomly picks floors 1-40)
- **Random call types**: 40% UP, 40% DOWN, 20% LOAD
- **Random intervals**: 5-20 seconds between calls
- **Uses RadioLib**: For SX1262 single-channel LoRa
- **Listens for ACKs**: Shows when gateway acknowledges packets

### Testing with Gateway

1. **Connect T-ETH Elite gateway** with SX1302 shield
2. **Upload gateway firmware** to T-ETH Elite
3. **Connect CrowPanel display** via I2C
4. **Disconnect T-ETH Elite**
5. **Connect T-Beam** and upload simulator firmware
6. **Reconnect T-ETH Elite** (now both are powered)
7. **Watch the display** - random floor calls should appear!

### Troubleshooting T-Beam

**LoRa initialization fails:**
- Check pin definitions match your T-Beam version
- Verify antenna is connected (never TX without antenna!)
- Try a different board variant in `platformio.ini`

**No packets received by gateway:**
- Verify frequency matches (915 MHz vs 868 MHz)
- Check spreading factor matches (SF9)
- Ensure sync word matches (0x12 is standard)
- Move devices closer together

**Serial monitor won't open from floor-node-firmware directory:**
```bash
# Use screen instead (works from any directory)
screen /dev/ttyACM0 115200

# Or change to a different firmware directory first
cd ../elevator-gateway-firmware
pio device monitor --port /dev/ttyACM0 --baud 115200
```

### Monitoring T-Beam Serial Output

```bash
# Option 1: screen (simplest)
screen /dev/ttyACM0 115200
# Exit: Ctrl+A, then K, then Y

# Option 2: From a different project directory
cd ../elevator-gateway-firmware
pio device monitor --port /dev/ttyACM0 --baud 115200

# Option 3: Direct cat (for quick checks)
cat /dev/ttyACM0
```

---

*Last Updated: 2025-11-09*
