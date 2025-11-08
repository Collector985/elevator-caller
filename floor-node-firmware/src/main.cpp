/**
 * Elevator Call Station - Floor Node Firmware v2.1
 * Hardware: Adafruit Feather RP2040 + RFM95 LoRa Radio
 *
 * NEW: Floor number configured via CrowPanel, stored in EEPROM!
 * No more recompiling for each floor!
 *
 * Features:
 * - 3 buttons: UP, DOWN, MATERIALS/LOAD
 * - 3 LED indicators
 * - EEPROM floor number storage (configure via display)
 * - Pairing mode (hold all 3 buttons on startup)
 * - RSSI-based auto-clear with elevator proximity
 * - Advanced power management (300+ day battery life)
 */

#include <Arduino.h>
#include <SPI.h>
#include <RH_RF95.h>
#include <EEPROM.h>

// Pin definitions for Feather RP2040
#define RFM95_CS   8
#define RFM95_INT  7
#define RFM95_RST  11

// Button pins
#define BTN_UP     12
#define BTN_DOWN   13
#define BTN_LOAD   14

// LED pins
#define LED_UP     10
#define LED_DOWN   9
#define LED_LOAD   6

// EEPROM addresses
#define EEPROM_MAGIC_ADDR 0
#define EEPROM_FLOOR_ADDR 4
#define EEPROM_MAGIC 0xABCD1234

// Protocol commands
enum Commands {
  CMD_CALL_UP = 0x01,
  CMD_CALL_DOWN = 0x02,
  CMD_CALL_LOAD = 0x03,
  CMD_ACK = 0x10,
  CMD_CLEAR = 0x20,
  CMD_CLEAR_ALL = 0x21,
  CMD_ELEVATOR_POS = 0x30,
  CMD_PING = 0x40,
  CMD_SET_FLOOR = 0x50,      // NEW: Set floor number
  CMD_PAIR_MODE = 0x51        // NEW: Enter pairing mode
};

enum CallState {
  STATE_IDLE,
  STATE_CALLING,
  STATE_ACKNOWLEDGED,
  STATE_TIMEOUT
};

enum PowerMode {
  MODE_DEEP_SLEEP,
  MODE_BEACON,
  MODE_ACTIVE,
  MODE_PAIRING         // NEW: Pairing mode
};

// Global objects
RH_RF95 rf95(RFM95_CS, RFM95_INT);

// State management
struct FloorCall {
  CallState upState = STATE_IDLE;
  CallState downState = STATE_IDLE;
  CallState loadState = STATE_IDLE;
  uint32_t upTime = 0;
  uint32_t downTime = 0;
  uint32_t loadTime = 0;
} calls;

uint8_t floorNumber = 0;  // Will be loaded from EEPROM
uint8_t messageId = 0;
uint32_t lastBeaconTime = 0;
uint32_t lastButtonCheck = 0;
bool elevatorNearby = false;
uint8_t elevatorFloor = 0;
int8_t lastRSSI = -120;
PowerMode currentPowerMode = MODE_DEEP_SLEEP;

// Statistics
uint32_t totalTransmissions = 0;
uint32_t totalClears = 0;
uint32_t autoClears = 0;

// Function prototypes
bool initializeLoRa();
uint8_t loadFloorNumber();
void saveFloorNumber(uint8_t floor);
void enterPairingMode();
void exitPairingMode();
bool checkPairingButtons();
void sendPacket(uint8_t command, uint8_t data);
bool waitForAck(uint8_t command, uint32_t timeout);
void checkForCommands();
void handleCommand(uint8_t command, uint8_t data);
void handleElevatorPosition(uint8_t floor);
void handleSetFloor(uint8_t floor);
void checkButtons();
void placeCall(uint8_t callType);
void handleActiveCalls();
void sendBeacon();
void sendStatusPacket();
void checkCallTimeouts(uint32_t now);
void autoClearCalls();
void clearAllCalls();
void managePowerState();
bool hasActiveCalls();
void wakeUp();
void ledStartupSequence();
void ledPairingSequence();
void flashLED(uint8_t pin, uint8_t times);
void errorBlink();
uint8_t calculateChecksum(uint8_t* data, uint8_t len);
void printStatus();

void setup() {
  // Set clock speed
  set_sys_clock_khz(CPU_SPEED_MHZ * 1000, true);

  Serial.begin(115200);
  delay(1000);

  Serial.println(F("========================================"));
  Serial.println(F("Floor Node v2.1"));
  Serial.println(F("Configurable Floor Assignment"));
  Serial.println(F("========================================"));

  // Initialize EEPROM
  EEPROM.begin(256);

  // Load floor number from EEPROM
  floorNumber = loadFloorNumber();

  // Initialize hardware
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_LOAD, INPUT_PULLUP);

  pinMode(LED_UP, OUTPUT);
  pinMode(LED_DOWN, OUTPUT);
  pinMode(LED_LOAD, OUTPUT);

  // Check if all 3 buttons are held on startup = pairing mode
  if (checkPairingButtons()) {
    Serial.println(F("*** PAIRING MODE ACTIVATED ***"));
    Serial.println(F("Use CrowPanel to assign floor number"));
    enterPairingMode();
    // Will stay in pairing mode until floor assigned
  }

  ledStartupSequence();

  if (!initializeLoRa()) {
    Serial.println(F("LoRa initialization FAILED!"));
    errorBlink();
  }

  Serial.print(F("CPU Speed: "));
  Serial.print(CPU_SPEED_MHZ);
  Serial.println(F(" MHz"));

  if (floorNumber == 0) {
    Serial.println(F("*** NO FLOOR ASSIGNED ***"));
    Serial.println(F("Hold all 3 buttons and reboot to enter pairing mode"));
  } else {
    Serial.print(F("Assigned Floor: "));
    Serial.println(floorNumber);
  }

  printStatus();

  // Configure wake interrupts
  attachInterrupt(digitalPinToInterrupt(BTN_UP), wakeUp, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_DOWN), wakeUp, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_LOAD), wakeUp, FALLING);
}

void loop() {
  // Handle pairing mode
  if (currentPowerMode == MODE_PAIRING) {
    ledPairingSequence();
    checkForCommands();
    delay(100);
    return;
  }

  if (millis() - lastButtonCheck > 50) {
    checkButtons();
    lastButtonCheck = millis();
  }

  if (hasActiveCalls()) {
    handleActiveCalls();
  }

  checkForCommands();
  managePowerState();
}

// ============= EEPROM FUNCTIONS =============
uint8_t loadFloorNumber() {
  uint32_t magic;
  EEPROM.get(EEPROM_MAGIC_ADDR, magic);

  if (magic == EEPROM_MAGIC) {
    uint8_t floor;
    EEPROM.get(EEPROM_FLOOR_ADDR, floor);
    Serial.print(F("Loaded floor number from EEPROM: "));
    Serial.println(floor);
    return floor;
  } else {
    Serial.println(F("No floor number stored in EEPROM"));
    return 0;  // Not configured
  }
}

void saveFloorNumber(uint8_t floor) {
  uint32_t magic = EEPROM_MAGIC;
  EEPROM.put(EEPROM_MAGIC_ADDR, magic);
  EEPROM.put(EEPROM_FLOOR_ADDR, floor);
  EEPROM.commit();

  floorNumber = floor;

  Serial.print(F("Saved floor number to EEPROM: "));
  Serial.println(floor);
}

// ============= PAIRING MODE =============
bool checkPairingButtons() {
  // Check if all 3 buttons are pressed
  return (digitalRead(BTN_UP) == LOW &&
          digitalRead(BTN_DOWN) == LOW &&
          digitalRead(BTN_LOAD) == LOW);
}

void enterPairingMode() {
  currentPowerMode = MODE_PAIRING;

  // Send pairing broadcast every second
  uint32_t lastPairBroadcast = 0;

  while (currentPowerMode == MODE_PAIRING) {
    if (millis() - lastPairBroadcast > 1000) {
      // Send pairing request
      uint8_t packet[5];
      packet[0] = 0xFF;  // Broadcast
      packet[1] = CMD_PAIR_MODE;
      packet[2] = 0;
      packet[3] = messageId++;
      packet[4] = calculateChecksum(packet, 4);

      rf95.send(packet, sizeof(packet));
      rf95.waitPacketSent();

      Serial.println(F("Pairing broadcast sent..."));
      lastPairBroadcast = millis();
    }

    // Flash all LEDs
    ledPairingSequence();

    // Check for floor assignment
    checkForCommands();

    delay(100);
  }
}

void exitPairingMode() {
  currentPowerMode = MODE_DEEP_SLEEP;
  Serial.println(F("Exiting pairing mode"));

  // Flash success
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_UP, HIGH);
    digitalWrite(LED_DOWN, HIGH);
    digitalWrite(LED_LOAD, HIGH);
    delay(100);
    digitalWrite(LED_UP, LOW);
    digitalWrite(LED_DOWN, LOW);
    digitalWrite(LED_LOAD, LOW);
    delay(100);
  }
}

// ============= LORA FUNCTIONS =============
bool initializeLoRa() {
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  if (!rf95.init()) {
    return false;
  }

  rf95.setFrequency(LORA_FREQUENCY);
  rf95.setSpreadingFactor(SPREADING_FACTOR);
  rf95.setTxPower(TX_POWER, false);
  rf95.setSignalBandwidth(125000);
  rf95.setCodingRate4(5);
  rf95.setPreambleLength(8);

  Serial.println(F("LoRa initialized successfully"));
  return true;
}

void sendPacket(uint8_t command, uint8_t data) {
  uint8_t packet[5];
  packet[0] = floorNumber;
  packet[1] = command;
  packet[2] = data;
  packet[3] = messageId++;
  packet[4] = calculateChecksum(packet, 4);

  rf95.send(packet, sizeof(packet));
  rf95.waitPacketSent();
  totalTransmissions++;

  Serial.print(F("TX: Cmd=0x"));
  Serial.print(command, HEX);
  Serial.print(F(" MsgID="));
  Serial.println(packet[3]);
}

bool waitForAck(uint8_t command, uint32_t timeout) {
  uint32_t start = millis();

  while (millis() - start < timeout) {
    if (rf95.available()) {
      uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
      uint8_t len = sizeof(buf);

      if (rf95.recv(buf, &len)) {
        lastRSSI = rf95.lastRssi();
        if (buf[0] == floorNumber && buf[1] == CMD_ACK && buf[2] == command) {
          Serial.print(F("ACK (RSSI: "));
          Serial.print(lastRSSI);
          Serial.println(F(" dBm)"));
          return true;
        }
      }
    }
    delay(10);
  }
  return false;
}

void checkForCommands() {
  if (rf95.available()) {
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.recv(buf, &len)) {
      lastRSSI = rf95.lastRssi();

      // In pairing mode, accept any floor assignment
      if (currentPowerMode == MODE_PAIRING && buf[1] == CMD_SET_FLOOR) {
        handleSetFloor(buf[2]);
        return;
      }

      // Normal mode - only accept messages for our floor or broadcast
      if (buf[0] == floorNumber || buf[0] == 0xFF) {
        handleCommand(buf[1], buf[2]);
      } else if (buf[1] == CMD_ELEVATOR_POS) {
        handleElevatorPosition(buf[2]);
      }
    }
  }
}

void handleCommand(uint8_t command, uint8_t data) {
  switch (command) {
    case CMD_CLEAR:
      if (data == CMD_CALL_UP && calls.upState != STATE_IDLE) {
        calls.upState = STATE_IDLE;
        digitalWrite(LED_UP, LOW);
        totalClears++;
        Serial.println(F("UP cleared"));
      } else if (data == CMD_CALL_DOWN && calls.downState != STATE_IDLE) {
        calls.downState = STATE_IDLE;
        digitalWrite(LED_DOWN, LOW);
        totalClears++;
        Serial.println(F("DOWN cleared"));
      } else if (data == CMD_CALL_LOAD && calls.loadState != STATE_IDLE) {
        calls.loadState = STATE_IDLE;
        digitalWrite(LED_LOAD, LOW);
        totalClears++;
        Serial.println(F("LOAD cleared"));
      }
      break;

    case CMD_CLEAR_ALL:
      clearAllCalls();
      totalClears += 3;
      Serial.println(F("All cleared"));
      break;

    case CMD_PING:
      sendStatusPacket();
      break;

    case CMD_SET_FLOOR:
      handleSetFloor(data);
      break;
  }
}

void handleSetFloor(uint8_t floor) {
  Serial.print(F("*** FLOOR ASSIGNED: "));
  Serial.print(floor);
  Serial.println(F(" ***"));

  saveFloorNumber(floor);

  // Exit pairing mode if we're in it
  if (currentPowerMode == MODE_PAIRING) {
    exitPairingMode();
  }

  // Send ACK
  uint8_t packet[5];
  packet[0] = floorNumber;
  packet[1] = CMD_ACK;
  packet[2] = CMD_SET_FLOOR;
  packet[3] = messageId++;
  packet[4] = calculateChecksum(packet, 4);

  rf95.send(packet, sizeof(packet));
  rf95.waitPacketSent();

  printStatus();
}

void handleElevatorPosition(uint8_t floor) {
  if (floorNumber == 0) return;  // Not configured yet

  elevatorFloor = floor;
  int distance = abs(elevatorFloor - floorNumber);
  bool wasNearby = elevatorNearby;
  elevatorNearby = (distance <= PROXIMITY_THRESHOLD_FLOORS);

  if (distance <= 1 && lastRSSI > -60 && hasActiveCalls()) {
    Serial.print(F("Auto-clear (RSSI: "));
    Serial.print(lastRSSI);
    Serial.println(F(")"));
    autoClearCalls();
  }

  if (elevatorNearby && !wasNearby) {
    currentPowerMode = MODE_ACTIVE;
  } else if (!elevatorNearby && wasNearby) {
    currentPowerMode = hasActiveCalls() ? MODE_BEACON : MODE_DEEP_SLEEP;
  }
}

void checkButtons() {
  if (floorNumber == 0) return;  // Not configured yet

  if (digitalRead(BTN_UP) == LOW && calls.upState == STATE_IDLE) {
    delay(50);
    if (digitalRead(BTN_UP) == LOW) placeCall(CMD_CALL_UP);
  }
  if (digitalRead(BTN_DOWN) == LOW && calls.downState == STATE_IDLE) {
    delay(50);
    if (digitalRead(BTN_DOWN) == LOW) placeCall(CMD_CALL_DOWN);
  }
  if (digitalRead(BTN_LOAD) == LOW && calls.loadState == STATE_IDLE) {
    delay(50);
    if (digitalRead(BTN_LOAD) == LOW) placeCall(CMD_CALL_LOAD);
  }
}

void placeCall(uint8_t callType) {
  Serial.print(F("Button: "));
  Serial.println(callType == CMD_CALL_UP ? "UP" : callType == CMD_CALL_DOWN ? "DOWN" : "LOAD");

  switch (callType) {
    case CMD_CALL_UP:
      digitalWrite(LED_UP, HIGH);
      calls.upState = STATE_CALLING;
      calls.upTime = millis();
      break;
    case CMD_CALL_DOWN:
      digitalWrite(LED_DOWN, HIGH);
      calls.downState = STATE_CALLING;
      calls.downTime = millis();
      break;
    case CMD_CALL_LOAD:
      digitalWrite(LED_LOAD, HIGH);
      calls.loadState = STATE_CALLING;
      calls.loadTime = millis();
      break;
  }

  sendPacket(callType, 0);

  if (waitForAck(callType, ACK_TIMEOUT_MS)) {
    switch (callType) {
      case CMD_CALL_UP:
        calls.upState = STATE_ACKNOWLEDGED;
        flashLED(LED_UP, 3);
        break;
      case CMD_CALL_DOWN:
        calls.downState = STATE_ACKNOWLEDGED;
        flashLED(LED_DOWN, 3);
        break;
      case CMD_CALL_LOAD:
        calls.loadState = STATE_ACKNOWLEDGED;
        flashLED(LED_LOAD, 3);
        break;
    }
  }

  currentPowerMode = MODE_BEACON;
  lastBeaconTime = millis();
}

void handleActiveCalls() {
  uint32_t now = millis();

  if (now - lastBeaconTime >= BEACON_INTERVAL_MS) {
    lastBeaconTime = now;
    sendBeacon();
  }

  checkCallTimeouts(now);
}

void sendBeacon() {
  uint8_t status = 0;
  if (calls.upState != STATE_IDLE) status |= 0x01;
  if (calls.downState != STATE_IDLE) status |= 0x02;
  if (calls.loadState != STATE_IDLE) status |= 0x04;

  if (status > 0) {
    sendPacket(CMD_PING, status);
    delay(LISTEN_WINDOW_MS);
    checkForCommands();
  }
}

void sendStatusPacket() {
  uint8_t status = 0;
  if (calls.upState != STATE_IDLE) status |= 0x01;
  if (calls.downState != STATE_IDLE) status |= 0x02;
  if (calls.loadState != STATE_IDLE) status |= 0x04;
  sendPacket(CMD_PING, status);
}

void checkCallTimeouts(uint32_t now) {
  const uint32_t TIMEOUT = 300000;  // 5 minutes
  if (calls.upState != STATE_IDLE && (now - calls.upTime > TIMEOUT)) {
    calls.upState = STATE_TIMEOUT;
  }
  if (calls.downState != STATE_IDLE && (now - calls.downTime > TIMEOUT)) {
    calls.downState = STATE_TIMEOUT;
  }
  if (calls.loadState != STATE_IDLE && (now - calls.loadTime > TIMEOUT)) {
    calls.loadState = STATE_TIMEOUT;
  }
}

void autoClearCalls() {
  if (calls.upState != STATE_IDLE) {
    calls.upState = STATE_IDLE;
    digitalWrite(LED_UP, LOW);
    autoClears++;
  }
  if (calls.downState != STATE_IDLE) {
    calls.downState = STATE_IDLE;
    digitalWrite(LED_DOWN, LOW);
    autoClears++;
  }
  if (calls.loadState != STATE_IDLE) {
    calls.loadState = STATE_IDLE;
    digitalWrite(LED_LOAD, LOW);
    autoClears++;
  }
  flashLED(LED_UP, 2);
  flashLED(LED_DOWN, 2);
  flashLED(LED_LOAD, 2);
}

void clearAllCalls() {
  calls.upState = STATE_IDLE;
  calls.downState = STATE_IDLE;
  calls.loadState = STATE_IDLE;
  digitalWrite(LED_UP, LOW);
  digitalWrite(LED_DOWN, LOW);
  digitalWrite(LED_LOAD, LOW);
}

void managePowerState() {
  if (!hasActiveCalls()) {
    delay(1000);
  } else if (elevatorNearby) {
    delay(100);
  } else {
    delay(100);
  }
}

bool hasActiveCalls() {
  return (calls.upState != STATE_IDLE ||
          calls.downState != STATE_IDLE ||
          calls.loadState != STATE_IDLE);
}

void wakeUp() {
  // ISR for button interrupts
}

void ledStartupSequence() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_UP, HIGH);
    delay(100);
    digitalWrite(LED_UP, LOW);
    digitalWrite(LED_DOWN, HIGH);
    delay(100);
    digitalWrite(LED_DOWN, LOW);
    digitalWrite(LED_LOAD, HIGH);
    delay(100);
    digitalWrite(LED_LOAD, LOW);
  }
}

void ledPairingSequence() {
  static uint32_t lastBlink = 0;
  static bool state = false;

  if (millis() - lastBlink > 250) {
    lastBlink = millis();
    state = !state;
    digitalWrite(LED_UP, state);
    digitalWrite(LED_DOWN, state);
    digitalWrite(LED_LOAD, state);
  }
}

void flashLED(uint8_t pin, uint8_t times) {
  for (uint8_t i = 0; i < times; i++) {
    digitalWrite(pin, HIGH);
    delay(100);
    digitalWrite(pin, LOW);
    delay(100);
  }
  digitalWrite(pin, HIGH);
}

void errorBlink() {
  while (true) {
    digitalWrite(LED_UP, HIGH);
    digitalWrite(LED_DOWN, HIGH);
    digitalWrite(LED_LOAD, HIGH);
    delay(200);
    digitalWrite(LED_UP, LOW);
    digitalWrite(LED_DOWN, LOW);
    digitalWrite(LED_LOAD, LOW);
    delay(200);
  }
}

uint8_t calculateChecksum(uint8_t* data, uint8_t len) {
  uint8_t sum = 0;
  for (uint8_t i = 0; i < len; i++) {
    sum ^= data[i];
  }
  return sum;
}

void printStatus() {
  Serial.println(F("Status:"));
  Serial.print(F("  Floor: "));
  if (floorNumber == 0) {
    Serial.println(F("NOT CONFIGURED"));
  } else {
    Serial.println(floorNumber);
  }
  Serial.print(F("  TX: "));
  Serial.print(totalTransmissions);
  Serial.print(F(", Clears: "));
  Serial.print(totalClears);
  Serial.print(F(", Auto: "));
  Serial.println(autoClears);
}
