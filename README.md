# 🏗️ Elevator LoRa Call Station System

A professional-grade elevator call station system using LoRa wireless communication for construction sites and buildings under renovation. Designed for Section 5 elevators in towers under construction.

## 🎯 System Overview

This system replaces traditional wired elevator call stations with wireless LoRa-based nodes, providing:
- **40-floor support** with room for expansion
- **Three call types per floor**: UP, DOWN, and MATERIALS/LOAD
- **RSSI-based proximity auto-clearing** - calls clear automatically when elevator arrives
- **300+ day battery life** on floor nodes
- **Real-time operator display** showing all active calls
- **Web interface** for remote monitoring

## 📐 System Architecture

```
┌─────────────────┐
│   Floor Node    │  (30-40 units, one per floor)
│ Feather RP2040  │
│   + RFM95 LoRa  │
│   + 3 Buttons   │
│   + 3 LEDs      │
│   + Battery     │
└────────┬────────┘
         │  LoRa 915 MHz
         │
         ▼
┌────────────────────────────────┐
│    Central Gateway Station     │
│  ┌──────────────────────────┐ │
│  │  T-ETH Elite + SX1302    │ │ ← 8-channel LoRa Gateway
│  │  (receives all floors)   │ │
│  └──────────┬───────────────┘ │
│             │ I2C              │
│  ┌──────────▼───────────────┐ │
│  │  CrowPanel 7" Display    │ │ ← Operator Interface
│  │  (800x480 touchscreen)   │ │
│  └──────────────────────────┘ │
│             │ Ethernet         │
│  ┌──────────▼───────────────┐ │
│  │  Web Interface           │ │ ← Remote Monitoring
│  │  (192.168.1.100)         │ │
│  └──────────────────────────┘ │
└────────────────────────────────┘
```

## 🛠️ Hardware Requirements

### ⚠️ Platform Clarification

This project uses **three different microcontroller platforms**:

| Device | Chip | Platform | Purpose |
|--------|------|----------|---------|
| **Floor Nodes** | RP2040 | Raspberry Pi | Battery-powered call buttons |
| **Gateway** | ESP32-S3 | Espressif | Central LoRa receiver |
| **Display** | ESP32-S3 | Espressif | Operator interface |
| **T-Beam (optional)** | ESP32-S3 | Espressif | Testing simulator |

**Important**: Only the floor nodes use Raspberry Pi silicon (RP2040). The gateway and display use ESP32-S3!

### Floor Node (×30-40, one per floor)
- **Adafruit Feather RP2040** - Main controller (Raspberry Pi RP2040 chip)
- **RFM95 LoRa Radio Module** (915 MHz for US, 868 MHz for EU)
- **3× R16-503AD Illuminated Push Buttons** (UP, DOWN, LOAD)
- **2× ER34615 3.6V Batteries** (7000mAh total capacity)
- **Enclosure** (weatherproof for construction sites)

### Central Gateway Station (×1)
- **LILYGO T-ETH Elite ESP32-S3** - Main gateway controller (ESP32-S3, NOT Raspberry Pi!)
- **T-SX1302 LoRa Gateway Shield** - 8-channel simultaneous reception
- **CrowPanel 7" Advance Display** (800×480 touchscreen, ESP32-S3)
- **5V 3A Power Supply** - Powers gateway + display
- **Ethernet Cable** - For network connectivity (optional, not yet implemented)
- **Antenna** - Magnetic mount on elevator car roof
- **Coax Cable** - Connects gateway to car-mounted antenna

### Testing Equipment (Optional)
- **LILYGO T-Beam** - ESP32-S3 with SX1262 LoRa for simulating floor nodes

## 📦 Project Structure

```
elevator-caller/
├── floor-node-firmware/       # PlatformIO project for floor nodes
│   ├── platformio.ini          # Build configuration
│   └── src/
│       └── main.cpp            # Floor node firmware
│
├── elevator-gateway-firmware/  # PlatformIO project for gateway
│   ├── platformio.ini          # Build configuration
│   └── src/
│       └── main.cpp            # Gateway firmware
│
├── crowpanel-display/          # PlatformIO project for display
│   ├── platformio.ini          # Build configuration
│   └── src/
│       └── main.cpp            # Display interface
│
├── tools/
│   └── config-generator.html   # Configuration tool
│
├── elevator_simulator.html     # Web-based system simulator
│
├── old elevator chat           # Previous design discussions
│
└── README.md                   # This file
```

## 🚀 Quick Start

### 1. Clone Repository

```bash
git clone https://github.com/Collector985/elevator-caller.git
cd elevator-caller
```

### 2. Install PlatformIO

```bash
# Install PlatformIO Core
pip install platformio

# Or use VS Code extension
# Search for "PlatformIO IDE" in VS Code extensions
```

### 3. Configure Your System

Open `tools/config-generator.html` in a web browser and enter your parameters:
- Number of floors
- LoRa frequency (915 MHz US, 868 MHz EU)
- Power settings
- Network configuration

The tool will generate custom `platformio.ini` configurations.

### 4. Build and Upload

**⚠️ Important**: Only connect ONE device at a time to avoid uploading to the wrong board!

#### Gateway (T-ETH Elite + T-SX1302)

```bash
cd elevator-gateway-firmware
pio run --target upload --upload-port /dev/ttyACM0
```

Disconnect the gateway before connecting the next device.

#### Display (CrowPanel)

```bash
cd crowpanel-display
pio run --target upload --upload-port /dev/ttyACM0
```

#### Floor Nodes (Adafruit Feather RP2040)

For each floor node, update `FLOOR_NUMBER` in `platformio.ini`:

```bash
cd floor-node-firmware

# Edit platformio.ini and set:
# -D FLOOR_NUMBER=15  (change for each floor!)

pio run -e adafruit_feather_rp2040 --target upload --upload-port /dev/ttyACM0
```

Repeat for all 30-40 floor nodes, changing the floor number each time.

#### T-Beam Simulator (Optional Testing)

If you have a LILYGO T-Beam for testing:

```bash
cd floor-node-firmware
pio run -e tbeam-supreme-simulator --target upload --upload-port /dev/ttyACM0
```

This simulates random floor calls for testing the gateway and display.

### 5. Test the System

1. Open the web simulator (`elevator_simulator.html`) to understand the system
2. Power on the gateway and verify the display shows the floor grid
3. Power on floor nodes one at a time
4. Press a button on a floor node - LED should light and call should appear on display
5. When elevator reaches that floor, call should auto-clear

## 🔧 Configuration

### Floor Node Settings (`floor-node-firmware/platformio.ini`)

```ini
build_flags =
    -D FLOOR_NUMBER=15              ; Change for each floor!
    -D CPU_SPEED_MHZ=48             ; Lower = better battery life
    -D LORA_FREQUENCY=915.0         ; 915 MHz (US) or 868 MHz (EU)
    -D SPREADING_FACTOR=9           ; 7-12, higher = longer range
    -D TX_POWER=20                  ; 2-20 dBm
    -D BEACON_INTERVAL_MS=2000      ; Heartbeat when call active
    -D PROXIMITY_THRESHOLD_FLOORS=3 ; Stay awake when elevator nearby
```

### Gateway Settings (`elevator-gateway-firmware/platformio.ini`)

```ini
build_flags =
    -D TOTAL_FLOORS=40              ; System capacity
    -D GATEWAY_FREQUENCY=915.0      ; Must match floor nodes
    -D I2C_SLAVE_ADDRESS=0x08       ; For display communication
    -D AUTO_CLEAR_RSSI=-60          ; dBm threshold for auto-clear
    -D ELEVATOR_BROADCAST_INTERVAL=1000  ; Position updates (ms)
```

## 📡 Communication Protocol

### Packet Structure

```c
struct LoRaPacket {
    uint8_t floor;        // Floor number (1-40)
    uint8_t command;      // Command type
    uint8_t data;         // Additional data
    uint8_t messageId;    // Incrementing ID
    uint8_t checksum;     // XOR checksum
};
```

### Commands

| Command | Value | Description |
|---------|-------|-------------|
| `CMD_CALL_UP` | 0x01 | Call elevator going UP |
| `CMD_CALL_DOWN` | 0x02 | Call elevator going DOWN |
| `CMD_CALL_LOAD` | 0x03 | Call for MATERIALS/LOAD |
| `CMD_ACK` | 0x10 | Acknowledgment from gateway |
| `CMD_CLEAR` | 0x20 | Clear specific call |
| `CMD_CLEAR_ALL` | 0x21 | Clear all calls for floor |
| `CMD_ELEVATOR_POS` | 0x30 | Elevator position broadcast |
| `CMD_PING` | 0x40 | Status heartbeat |

### Communication Flow

```
Floor Node                Gateway                Display
    │                        │                      │
    │──CALL_UP──────────────>│                      │
    │<─────ACK───────────────│                      │
    │                        │─────Update──────────>│
    │                        │                      │
    │──PING (every 2s)──────>│ (while call active) │
    │                        │                      │
    │                        │──ELEVATOR_POS───────>│
    │<───ELEVATOR_POS────────│                      │
    │                        │                      │
    │                  (Elevator arrives)           │
    │<─────CLEAR─────────────│  (RSSI > -60 dBm)   │
    │                        │                      │
```

## 🔋 Power Management

### Floor Node Battery Life

Power modes:
- **DEEP_SLEEP**: No active calls - ~0.1 mA
- **BEACON**: Active call - ~0.95 mA average (wake every 2s)
- **ACTIVE**: Elevator nearby - ~12 mA (stay responsive)

**Expected battery life with 7000 mAh capacity:**
- Idle (no calls): **7+ years**
- Moderate use (10 calls/day): **307 days**
- Heavy use (50 calls/day): **180 days**

### Optimization Tips

1. **Lower CPU speed**: 48 MHz instead of 133 MHz saves 50% power
2. **Longer beacon interval**: 2-3 seconds is optimal
3. **Higher spreading factor**: SF9-10 for construction sites
4. **Quality batteries**: Use ER34615 lithium thionyl chloride

## 🌐 Web Interface

Access the gateway web interface at `http://192.168.1.100/` (or your configured IP).

### Endpoints

- `/` - Main status page with floor grid
- `/status` - JSON system statistics
- `/floors` - JSON list of active calls
- `/clear?floor=X&type=Y` - Manually clear a call
- `/stats` - System statistics

### Example API Usage

```bash
# Get system status
curl http://192.168.1.100/status

# Get active floors
curl http://192.168.1.100/floors

# Clear floor 15 UP call (type 1=UP, 2=DOWN, 3=LOAD)
curl "http://192.168.1.100/clear?floor=15&type=1"
```

## 📱 Display Interface

The CrowPanel 7" display shows:
- **8×5 grid** of 40 floors
- **Three indicators per floor**: UP (green), LOAD (yellow), DOWN (red)
- **Current elevator position**: Blue border highlight
- **RSSI signal strength**: Displayed per floor
- **Touch to clear**: Tap any floor to clear all its calls

## 🏗️ Installation Guide

### Floor Node Installation

1. **Power**: Install 2× ER34615 batteries in series (7.2V)
2. **Mounting**: Install weatherproof enclosure near elevator shaft
3. **Buttons**: Wire UP, DOWN, LOAD buttons
4. **LEDs**: Connect indicator LEDs
5. **Antenna**: Attach small whip antenna (915/868 MHz)
6. **Testing**: Power on, verify LED sequence
7. **Labeling**: Clearly label floor number on enclosure

### Gateway Installation

1. **Location**: Install in elevator control room or operator station
2. **Antenna Routing**: Run coax from gateway to elevator car roof
3. **Magnetic Mount**: Attach antenna to car roof (best signal)
4. **Display Connection**: Connect CrowPanel via I2C (4 wires)
5. **Power**: Connect 5V 3A power supply
6. **Network**: Connect Ethernet cable
7. **Testing**: Verify web interface accessible

### Antenna Placement

**Best location**: Magnetic mount on elevator car roof

Why it works:
- Signals "leak" around elevator car through gaps
- Guide rails: 2-5 cm gaps each side
- Door gaps: 1-2 cm
- Cable openings: 10+ cm
- Total RF penetration: Excellent in drywall shafts

Expected range: ±15 floors direct, all floors with good shaft propagation

## 🧪 Testing & Troubleshooting

### Testing Procedure

1. **Start with simulator**: Open `elevator_simulator.html` to understand system
2. **Gateway first**: Power on gateway, verify it initializes (serial output)
3. **Optional - T-Beam simulator**: Test with simulated floor calls
4. **One floor node**: Power on a single floor node
5. **Press button**: Should see LED light and call on display
6. **Check RSSI**: Should be -50 to -80 dBm for good signal
7. **Auto-clear test**: Simulate elevator arrival
8. **Add more nodes**: Power on additional floor nodes one by one

### Common Issues

**"UnknownPlatform: Unknown development platform 'raspberrypi.git'" error:**
- You're in the `floor-node-firmware` directory
- PlatformIO reads `platformio.ini` even for `pio device monitor`
- **Solution**: Change directory or use `screen /dev/ttyACM0 115200`

**Wrong firmware uploaded to device:**
- T-Beam shows "SX1302 initialization FAILED!" = gateway firmware was uploaded (wrong!)
- T-ETH Elite shows "SX1262 initialization failed" = simulator firmware was uploaded (wrong!)
- **Solution**: See HARDWARE_NOTES.md for correct upload procedures

**Device identification confusion:**
| If you see... | Device is... | Correct firmware... |
|---------------|--------------|---------------------|
| SX1302 initialization | T-ETH Elite Gateway | `elevator-gateway-firmware/` |
| SX1262 initialization | T-Beam | `floor-node-firmware/` (simulator env) |
| LVGL initialization | CrowPanel Display | `crowpanel-display/` |
| RFM95 initialization | Feather RP2040 | `floor-node-firmware/` (main env) |

**Floor node won't connect:**
- Check batteries (need 6V+ minimum)
- Verify LoRa frequency matches gateway (915 MHz vs 868 MHz)
- Check antenna connection (never TX without antenna!)
- Move closer to gateway for testing

**No auto-clear:**
- Check RSSI threshold setting (-60 dBm default)
- Verify elevator position broadcasts working
- Ensure floor nodes receiving position updates

**Short battery life:**
- Check for continuous TX (LED always on)
- Verify sleep modes working
- Reduce CPU speed to 48 MHz
- Increase beacon interval

**Display not updating:**
- Check I2C connections (SDA, SCL, GND, 5V)
- Verify I2C address (0x08 default)
- Check gateway firmware serial output

**T-Beam simulator not working:**
- Check pin definitions match your T-Beam version
- Verify frequency matches gateway (915.0 MHz)
- Ensure antenna is connected
- Use `screen /dev/ttyACM0 115200` to monitor output

## 🔐 Safety & Regulations

⚠️ **Important Considerations:**

1. **NOT a safety system**: This is a convenience system only
2. **Backup required**: Keep traditional controls functional
3. **Testing**: Thoroughly test before relying on system
4. **Maintenance**: Check batteries monthly
5. **FCC/CE Compliance**: Verify LoRa frequency legal in your region
6. **Construction site**: Use weatherproof enclosures

## 📊 System Specifications

| Parameter | Value |
|-----------|-------|
| **Operating Frequency** | 915 MHz (US) / 868 MHz (EU) |
| **Max Floors** | 40 (expandable to 100+) |
| **Range** | ±15 floors direct, all floors via shaft propagation |
| **Battery Life** | 300+ days with moderate use |
| **Calls per Floor** | 3 (UP, DOWN, LOAD) |
| **Auto-Clear** | Yes, RSSI-based proximity detection |
| **Display** | 800×480 touchscreen |
| **Web Interface** | Ethernet + WiFi capable |
| **Channels** | 8 simultaneous (SX1302 gateway) |
| **Power** | Floor nodes: Battery, Gateway: 5V 3A |

## 🛠️ Advanced Configuration

### Custom Antenna Setup

For difficult installations:
```
Gateway in basement → Use repeater on mid-floor
Very tall building → Multiple gateways with load balancing
Metal shaft → External antenna routing
```

### RSSI Threshold Tuning

Adjust auto-clear sensitivity:
```c
// More aggressive (clear farther away)
#define AUTO_CLEAR_RSSI -75

// More conservative (only clear when very close)
#define AUTO_CLEAR_RSSI -55
```

### Network Configuration

Static IP setup in gateway code:
```cpp
IPAddress ip(192, 168, 1, 100);        // Gateway IP
IPAddress gateway(192, 168, 1, 1);     // Network gateway
IPAddress subnet(255, 255, 255, 0);    // Subnet mask
```

## 📝 License

This project is open source. See individual files for specific licenses.

## 🙏 Acknowledgments

- LoRa technology by Semtech
- RadioLib by jgromes
- PlatformIO build system
- LILYGO for T-ETH Elite hardware
- Adafruit for Feather RP2040

## 📞 Support

- **Issues**: Open a GitHub issue
- **Discussions**: Use GitHub Discussions
- **Documentation**: See `old elevator chat` for design rationale

## 🔄 Version History

- **v2.0** (Current): Complete PlatformIO-based system with RSSI auto-clear
- **v1.0**: Initial prototype

---

Built with ❤️ for construction site elevators worldwide 🏗️
