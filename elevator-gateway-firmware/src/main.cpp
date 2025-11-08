/**
 * Elevator Gateway System
 * Hardware: LILYGO T-ETH Elite + SX1302 Gateway Shield + CrowPanel 7" Display
 *
 * Features:
 * - SX1302 8-channel simultaneous LoRa reception
 * - RSSI-based proximity auto-clear
 * - I2C communication to CrowPanel display
 * - Ethernet connectivity + web interface
 * - 40-floor support
 */

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Ethernet.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <RadioLib.h>
#include <queue>

// ============= PIN DEFINITIONS =============
// SX1302 pins
#define SX1302_NSS 5
#define SX1302_RESET 14
#define SX1302_BUSY 13
#define SX1302_DIO1 12

// I2C pins for CrowPanel
#define I2C_SDA 21
#define I2C_SCL 22

// ============= PROTOCOL =============
enum Commands {
  CMD_CALL_UP = 0x01,
  CMD_CALL_DOWN = 0x02,
  CMD_CALL_LOAD = 0x03,
  CMD_ACK = 0x10,
  CMD_CLEAR = 0x20,
  CMD_CLEAR_ALL = 0x21,
  CMD_ELEVATOR_POS = 0x30,
  CMD_PING = 0x40
};

enum CallDirection {
  DIR_NONE = 0,
  DIR_UP = 1,
  DIR_DOWN = 2,
  DIR_LOAD = 3
};

// ============= DATA STRUCTURES =============
struct FloorCall {
  bool upActive = false;
  bool downActive = false;
  bool loadActive = false;
  uint32_t upTime = 0;
  uint32_t downTime = 0;
  uint32_t loadTime = 0;
  int8_t lastRSSI = -120;
  uint32_t lastHeard = 0;
  bool acknowledged = false;
};

struct LoRaPacket {
  uint8_t floor;
  uint8_t command;
  uint8_t data;
  uint8_t messageId;
  int8_t rssi;
  float snr;
  uint8_t sf;
  uint32_t frequency;
  uint32_t timestamp;
};

struct DisplayPacket {
  uint8_t floor;
  uint8_t status;  // Bit field: UP|DOWN|LOAD|ACK
  int8_t rssi;
};

// ============= GLOBALS =============
SX1302 gateway = new Module(SX1302_NSS, SX1302_DIO1, SX1302_RESET, SX1302_BUSY);
FloorCall floorCalls[TOTAL_FLOORS + 1];  // Index 0 unused, 1-40 for floors
std::queue<LoRaPacket> packetQueue;
std::queue<DisplayPacket> displayQueue;

uint8_t currentFloor = 20;  // Elevator's current position
uint8_t targetFloor = 20;
bool isMoving = false;
uint32_t lastBroadcast = 0;
uint32_t lastDisplayUpdate = 0;

// RSSI-based proximity tracking
int8_t floorRSSI[TOTAL_FLOORS + 1];
bool floorProximity[TOTAL_FLOORS + 1];
uint32_t proximityClearTime[TOTAL_FLOORS + 1];

// Statistics
uint32_t totalPacketsReceived = 0;
uint32_t totalCallsReceived = 0;
uint32_t totalCallsCleared = 0;
uint32_t autoClearedCount = 0;

// Ethernet & Web Server
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 1, 100);
WebServer webServer(80);

// Function prototypes
bool initializeSX1302();
void handleLoRaReception();
void processPacketQueue();
void handleCallRequest(uint8_t floor, uint8_t direction, uint8_t messageId, int8_t rssi);
void handlePing(uint8_t floor, uint8_t status, int8_t rssi);
void sendAcknowledgment(uint8_t floor, uint8_t command, uint8_t messageId);
void sendClearCommand(uint8_t floor, uint8_t callType);
void checkProximityAndAutoClear();
void autoClearFloor(uint8_t floor);
void manualClearFloor(uint8_t floor, uint8_t callType);
void broadcastElevatorPosition();
void simulateElevatorMovement();
bool hasCallsAbove(uint8_t floor);
bool hasCallsBelow(uint8_t floor);
void handleDisplayRequest();
void handleDisplayCommand(int numBytes);
void queueDisplayUpdate(uint8_t floor);
void updateDisplayData();
void initializeEthernet();
void setupWebServer();
void handleWebRoot();
void handleWebStatus();
void handleWebFloors();
void handleWebClear();
void handleWebStats();
void initializeFloorData();
uint8_t calculateChecksum(uint8_t* data, uint8_t len);
void logPacket(LoRaPacket &pkt);

// ============= SETUP =============
void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("========================================"));
  Serial.println(F("Elevator Gateway System v2.0"));
  Serial.println(F("T-ETH Elite + SX1302 + CrowPanel"));
  Serial.println(F("========================================"));

  // Initialize I2C for display communication
  Wire.begin(I2C_SLAVE_ADDRESS, I2C_SDA, I2C_SCL);
  Wire.onRequest(handleDisplayRequest);
  Wire.onReceive(handleDisplayCommand);

  // Initialize Ethernet
  initializeEthernet();

  // Initialize SX1302 Gateway
  if (!initializeSX1302()) {
    Serial.println(F("SX1302 initialization FAILED!"));
    while (true) { delay(1000); }
  }

  // Initialize data structures
  initializeFloorData();

  // Setup web server endpoints
  setupWebServer();

  Serial.println(F("Gateway Ready!"));
  Serial.print(F("IP Address: "));
  Serial.println(Ethernet.localIP());
  Serial.print(F("Total Floors: "));
  Serial.println(TOTAL_FLOORS);
}

// ============= MAIN LOOP =============
void loop() {
  // Check for LoRa packets
  handleLoRaReception();

  // Process packet queue
  processPacketQueue();

  // Broadcast elevator position
  if (millis() - lastBroadcast > ELEVATOR_BROADCAST_INTERVAL) {
    broadcastElevatorPosition();
    lastBroadcast = millis();
  }

  // Check proximity and auto-clear
  checkProximityAndAutoClear();

  // Handle web server
  webServer.handleClient();

  // Update display via I2C
  updateDisplayData();

  // Simulate elevator movement (for testing)
  simulateElevatorMovement();
}

// ============= SX1302 FUNCTIONS =============
bool initializeSX1302() {
  Serial.print(F("Initializing SX1302..."));

  int state = gateway.begin(
    GATEWAY_FREQUENCY,
    125.0,  // Bandwidth in kHz
    7,      // Spreading factor (will listen to SF7-SF12)
    5,      // Coding rate
    0x12,   // Sync word
    10,     // Output power in dBm
    8,      // Preamble length
    0       // TCXO voltage
  );

  if (state != RADIOLIB_ERR_NONE) {
    Serial.print(F("Failed, code "));
    Serial.println(state);
    return false;
  }

  // Configure for 8-channel reception
  gateway.setFrequencyDeviation(25.0);

  // Set up for continuous reception
  gateway.startReceive();

  Serial.println(F("Success!"));
  return true;
}

void handleLoRaReception() {
  if (gateway.available()) {
    uint8_t data[255];
    int packetSize = gateway.getPacketLength();

    if (packetSize > 0 && packetSize < 255) {
      int state = gateway.readData(data, packetSize);

      if (state == RADIOLIB_ERR_NONE) {
        LoRaPacket pkt;
        pkt.floor = data[0];
        pkt.command = data[1];
        pkt.data = data[2];
        pkt.messageId = data[3];
        pkt.rssi = gateway.getRSSI();
        pkt.snr = gateway.getSNR();
        pkt.sf = gateway.getSpreadingFactor();
        pkt.frequency = gateway.getFrequency();
        pkt.timestamp = millis();

        packetQueue.push(pkt);
        totalPacketsReceived++;
        logPacket(pkt);
      }
    }

    gateway.startReceive();
  }
}

void processPacketQueue() {
  while (!packetQueue.empty()) {
    LoRaPacket pkt = packetQueue.front();
    packetQueue.pop();

    // Validate floor number
    if (pkt.floor < 1 || pkt.floor > TOTAL_FLOORS) {
      continue;
    }

    // Update RSSI tracking
    floorRSSI[pkt.floor] = pkt.rssi;
    floorCalls[pkt.floor].lastRSSI = pkt.rssi;
    floorCalls[pkt.floor].lastHeard = millis();

    // Process command
    switch (pkt.command) {
      case CMD_CALL_UP:
        handleCallRequest(pkt.floor, DIR_UP, pkt.messageId, pkt.rssi);
        break;

      case CMD_CALL_DOWN:
        handleCallRequest(pkt.floor, DIR_DOWN, pkt.messageId, pkt.rssi);
        break;

      case CMD_CALL_LOAD:
        handleCallRequest(pkt.floor, DIR_LOAD, pkt.messageId, pkt.rssi);
        break;

      case CMD_PING:
        handlePing(pkt.floor, pkt.data, pkt.rssi);
        break;

      default:
        break;
    }
  }
}

void handleCallRequest(uint8_t floor, uint8_t direction, uint8_t messageId, int8_t rssi) {
  Serial.print(F("Call from floor "));
  Serial.print(floor);
  Serial.print(F(" Dir: "));
  Serial.print(direction);
  Serial.print(F(" RSSI: "));
  Serial.println(rssi);

  totalCallsReceived++;

  // Update floor call status
  switch (direction) {
    case DIR_UP:
      if (!floorCalls[floor].upActive) {
        floorCalls[floor].upActive = true;
        floorCalls[floor].upTime = millis();
      }
      break;

    case DIR_DOWN:
      if (!floorCalls[floor].downActive) {
        floorCalls[floor].downActive = true;
        floorCalls[floor].downTime = millis();
      }
      break;

    case DIR_LOAD:
      if (!floorCalls[floor].loadActive) {
        floorCalls[floor].loadActive = true;
        floorCalls[floor].loadTime = millis();
      }
      break;
  }

  // Send acknowledgment
  sendAcknowledgment(floor, direction, messageId);

  // Update display
  queueDisplayUpdate(floor);
}

void handlePing(uint8_t floor, uint8_t status, int8_t rssi) {
  // Ping contains status bits for active calls
  if (status & 0x01) floorCalls[floor].upActive = true;
  if (status & 0x02) floorCalls[floor].downActive = true;
  if (status & 0x04) floorCalls[floor].loadActive = true;

  // Check for proximity-based auto-clear
  if (rssi > AUTO_CLEAR_RSSI && abs(currentFloor - floor) <= 1) {
    autoClearFloor(floor);
  }
}

void sendAcknowledgment(uint8_t floor, uint8_t command, uint8_t messageId) {
  uint8_t packet[5];
  packet[0] = floor;
  packet[1] = CMD_ACK;
  packet[2] = command;
  packet[3] = messageId;
  packet[4] = calculateChecksum(packet, 4);

  gateway.transmit(packet, sizeof(packet));

  Serial.print(F("ACK sent to floor "));
  Serial.println(floor);
}

void sendClearCommand(uint8_t floor, uint8_t callType) {
  uint8_t packet[4];
  packet[0] = floor;
  packet[1] = CMD_CLEAR;
  packet[2] = callType;
  packet[3] = calculateChecksum(packet, 3);

  gateway.transmit(packet, sizeof(packet));

  Serial.print(F("Clear sent to floor "));
  Serial.print(floor);
  Serial.print(F(" Type: "));
  Serial.println(callType);
}

// ============= PROXIMITY & AUTO-CLEAR =============
void checkProximityAndAutoClear() {
  for (uint8_t floor = 1; floor <= TOTAL_FLOORS; floor++) {
    // Skip if no recent data
    if (millis() - floorCalls[floor].lastHeard > 10000) {
      continue;
    }

    int8_t rssi = floorCalls[floor].lastRSSI;

    // Check if elevator is at or very near this floor
    if (abs(currentFloor - floor) <= 1) {
      if (rssi > AUTO_CLEAR_RSSI) {
        // Very strong signal and we're at the floor
        if (!floorProximity[floor]) {
          // Just arrived at floor
          floorProximity[floor] = true;
          proximityClearTime[floor] = millis() + 2000;  // Wait 2 seconds
        } else if (millis() > proximityClearTime[floor]) {
          // Been at floor for 2+ seconds, auto-clear
          autoClearFloor(floor);
        }
      }
    } else {
      // Not near this floor anymore
      floorProximity[floor] = false;
    }
  }
}

void autoClearFloor(uint8_t floor) {
  bool clearedSomething = false;

  if (floorCalls[floor].upActive) {
    floorCalls[floor].upActive = false;
    sendClearCommand(floor, CMD_CALL_UP);
    clearedSomething = true;
    totalCallsCleared++;
  }

  if (floorCalls[floor].downActive) {
    floorCalls[floor].downActive = false;
    sendClearCommand(floor, CMD_CALL_DOWN);
    clearedSomething = true;
    totalCallsCleared++;
  }

  if (floorCalls[floor].loadActive) {
    floorCalls[floor].loadActive = false;
    sendClearCommand(floor, CMD_CALL_LOAD);
    clearedSomething = true;
    totalCallsCleared++;
  }

  if (clearedSomething) {
    autoClearedCount++;
    Serial.print(F("AUTO-CLEARED floor "));
    Serial.print(floor);
    Serial.print(F(" (RSSI: "));
    Serial.print(floorCalls[floor].lastRSSI);
    Serial.println(F(")"));

    queueDisplayUpdate(floor);
  }
}

void manualClearFloor(uint8_t floor, uint8_t callType) {
  switch (callType) {
    case DIR_UP:
      if (floorCalls[floor].upActive) {
        floorCalls[floor].upActive = false;
        sendClearCommand(floor, CMD_CALL_UP);
        totalCallsCleared++;
      }
      break;

    case DIR_DOWN:
      if (floorCalls[floor].downActive) {
        floorCalls[floor].downActive = false;
        sendClearCommand(floor, CMD_CALL_DOWN);
        totalCallsCleared++;
      }
      break;

    case DIR_LOAD:
      if (floorCalls[floor].loadActive) {
        floorCalls[floor].loadActive = false;
        sendClearCommand(floor, CMD_CALL_LOAD);
        totalCallsCleared++;
      }
      break;

    case 0xFF:  // Clear all
      if (floorCalls[floor].upActive) {
        floorCalls[floor].upActive = false;
        totalCallsCleared++;
      }
      if (floorCalls[floor].downActive) {
        floorCalls[floor].downActive = false;
        totalCallsCleared++;
      }
      if (floorCalls[floor].loadActive) {
        floorCalls[floor].loadActive = false;
        totalCallsCleared++;
      }
      sendClearCommand(floor, CMD_CLEAR_ALL);
      break;
  }

  queueDisplayUpdate(floor);
}

// ============= ELEVATOR POSITION =============
void broadcastElevatorPosition() {
  uint8_t packet[3];
  packet[0] = 0xFF;  // Broadcast address
  packet[1] = CMD_ELEVATOR_POS;
  packet[2] = currentFloor;

  gateway.transmit(packet, sizeof(packet));
}

void simulateElevatorMovement() {
  static uint32_t lastMove = 0;
  static bool goingUp = true;

  // Move every 3 seconds for simulation
  if (millis() - lastMove > 3000) {
    lastMove = millis();

    if (hasCallsAbove(currentFloor) && goingUp) {
      currentFloor++;
      if (currentFloor >= TOTAL_FLOORS) goingUp = false;
    } else if (hasCallsBelow(currentFloor) && !goingUp) {
      currentFloor--;
      if (currentFloor <= 1) goingUp = true;
    } else if (hasCallsAbove(currentFloor)) {
      goingUp = true;
      currentFloor++;
    } else if (hasCallsBelow(currentFloor)) {
      goingUp = false;
      currentFloor--;
    }

    Serial.print(F("Elevator at floor "));
    Serial.println(currentFloor);
  }
}

bool hasCallsAbove(uint8_t floor) {
  for (uint8_t f = floor + 1; f <= TOTAL_FLOORS; f++) {
    if (floorCalls[f].upActive || floorCalls[f].downActive || floorCalls[f].loadActive) {
      return true;
    }
  }
  return false;
}

bool hasCallsBelow(uint8_t floor) {
  for (uint8_t f = 1; f < floor; f++) {
    if (floorCalls[f].upActive || floorCalls[f].downActive || floorCalls[f].loadActive) {
      return true;
    }
  }
  return false;
}

// ============= I2C DISPLAY COMMUNICATION =============
void handleDisplayRequest() {
  if (!displayQueue.empty()) {
    DisplayPacket pkt = displayQueue.front();
    displayQueue.pop();

    Wire.write((uint8_t*)&pkt, sizeof(DisplayPacket));
  } else {
    // Send current elevator position
    DisplayPacket pkt;
    pkt.floor = currentFloor;
    pkt.status = 0x80;  // Special flag for elevator position
    pkt.rssi = 0;

    Wire.write((uint8_t*)&pkt, sizeof(DisplayPacket));
  }
}

void handleDisplayCommand(int numBytes) {
  if (numBytes >= 3) {
    uint8_t floor = Wire.read();
    uint8_t command = Wire.read();
    uint8_t data = Wire.read();

    if (command == CMD_CLEAR) {
      manualClearFloor(floor, data);
    }
  }
}

void queueDisplayUpdate(uint8_t floor) {
  DisplayPacket pkt;
  pkt.floor = floor;
  pkt.status = 0;

  if (floorCalls[floor].upActive) pkt.status |= 0x01;
  if (floorCalls[floor].downActive) pkt.status |= 0x02;
  if (floorCalls[floor].loadActive) pkt.status |= 0x04;
  if (floorCalls[floor].acknowledged) pkt.status |= 0x08;

  pkt.rssi = floorCalls[floor].lastRSSI;

  displayQueue.push(pkt);
}

void updateDisplayData() {
  static uint32_t lastFullUpdate = 0;

  if (millis() - lastFullUpdate > 1000) {
    lastFullUpdate = millis();

    for (uint8_t floor = 1; floor <= TOTAL_FLOORS; floor++) {
      if (floorCalls[floor].upActive ||
          floorCalls[floor].downActive ||
          floorCalls[floor].loadActive) {
        queueDisplayUpdate(floor);
      }
    }
  }
}

// ============= WEB SERVER =============
void initializeEthernet() {
  Ethernet.begin(mac, ip);

  Serial.print(F("Ethernet IP: "));
  Serial.println(Ethernet.localIP());
}

void setupWebServer() {
  webServer.on("/", handleWebRoot);
  webServer.on("/status", handleWebStatus);
  webServer.on("/floors", handleWebFloors);
  webServer.on("/clear", handleWebClear);
  webServer.on("/stats", handleWebStats);

  webServer.begin();
}

void handleWebRoot() {
  String html = F("<!DOCTYPE html><html><head><title>Elevator Gateway</title>");
  html += F("<meta http-equiv='refresh' content='5'/>");
  html += F("<style>body{font-family:Arial;margin:20px;}");
  html += F(".floor{display:inline-block;width:60px;height:60px;margin:5px;");
  html += F("border:2px solid #ccc;text-align:center;line-height:60px;}");
  html += F(".active-up{background:#0f0;}.active-down{background:#f00;}");
  html += F(".active-load{background:#ff0;}.current{border-color:#00f;border-width:4px;}");
  html += F("</style></head><body>");
  html += F("<h1>Elevator Gateway Status</h1>");
  html += F("<p>Current Floor: <b>");
  html += currentFloor;
  html += F("</b></p>");
  html += F("<div id='floors'>");

  for (uint8_t f = TOTAL_FLOORS; f >= 1; f--) {
    html += F("<div class='floor ");
    if (f == currentFloor) html += F("current ");
    if (floorCalls[f].upActive) html += F("active-up ");
    if (floorCalls[f].downActive) html += F("active-down ");
    if (floorCalls[f].loadActive) html += F("active-load ");
    html += F("'>");
    html += f;
    html += F("</div>");
    if (f % 8 == 1) html += F("<br>");
  }

  html += F("</div></body></html>");

  webServer.send(200, "text/html", html);
}

void handleWebStatus() {
  StaticJsonDocument<512> doc;

  doc["currentFloor"] = currentFloor;
  doc["totalPackets"] = totalPacketsReceived;
  doc["totalCalls"] = totalCallsReceived;
  doc["totalCleared"] = totalCallsCleared;
  doc["autoCleared"] = autoClearedCount;
  doc["uptime"] = millis() / 1000;

  String response;
  serializeJson(doc, response);

  webServer.send(200, "application/json", response);
}

void handleWebFloors() {
  StaticJsonDocument<2048> doc;
  JsonArray floors = doc.createNestedArray("floors");

  for (uint8_t f = 1; f <= TOTAL_FLOORS; f++) {
    if (floorCalls[f].upActive || floorCalls[f].downActive || floorCalls[f].loadActive) {
      JsonObject floor = floors.createNestedObject();
      floor["floor"] = f;
      floor["up"] = floorCalls[f].upActive;
      floor["down"] = floorCalls[f].downActive;
      floor["load"] = floorCalls[f].loadActive;
      floor["rssi"] = floorCalls[f].lastRSSI;
      floor["lastHeard"] = (millis() - floorCalls[f].lastHeard) / 1000;
    }
  }

  String response;
  serializeJson(doc, response);

  webServer.send(200, "application/json", response);
}

void handleWebClear() {
  if (webServer.hasArg("floor") && webServer.hasArg("type")) {
    uint8_t floor = webServer.arg("floor").toInt();
    uint8_t type = webServer.arg("type").toInt();

    if (floor >= 1 && floor <= TOTAL_FLOORS) {
      manualClearFloor(floor, type);
      webServer.send(200, "text/plain", "OK");
    } else {
      webServer.send(400, "text/plain", "Invalid floor");
    }
  } else {
    webServer.send(400, "text/plain", "Missing parameters");
  }
}

void handleWebStats() {
  String json = "{";
  json += "\"totalPackets\":" + String(totalPacketsReceived) + ",";
  json += "\"totalCalls\":" + String(totalCallsReceived) + ",";
  json += "\"totalCleared\":" + String(totalCallsCleared) + ",";
  json += "\"autoCleared\":" + String(autoClearedCount) + ",";
  json += "\"uptime\":" + String(millis() / 1000);
  json += "}";

  webServer.send(200, "application/json", json);
}

// ============= UTILITY FUNCTIONS =============
void initializeFloorData() {
  for (uint8_t f = 0; f <= TOTAL_FLOORS; f++) {
    floorCalls[f] = FloorCall();
    floorRSSI[f] = -120;
    floorProximity[f] = false;
    proximityClearTime[f] = 0;
  }
}

uint8_t calculateChecksum(uint8_t* data, uint8_t len) {
  uint8_t sum = 0;
  for (uint8_t i = 0; i < len; i++) {
    sum ^= data[i];
  }
  return sum;
}

void logPacket(LoRaPacket &pkt) {
  Serial.print(F("RX: Floor "));
  Serial.print(pkt.floor);
  Serial.print(F(" Cmd: 0x"));
  Serial.print(pkt.command, HEX);
  Serial.print(F(" RSSI: "));
  Serial.print(pkt.rssi);
  Serial.print(F(" SNR: "));
  Serial.print(pkt.snr);
  Serial.print(F(" SF: "));
  Serial.println(pkt.sf);
}
