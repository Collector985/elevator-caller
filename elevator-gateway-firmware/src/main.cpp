/**
 * Elevator Gateway System - T-ETH Elite + T-SX1302
 *
 * Hardware: LILYGO T-ETH Elite ESP32-S3 + T-SX1302 Gateway Shield
 *
 * Features:
 * - SX1302 8-channel LoRa reception
 * - I2C communication to CrowPanel display
 * - Ethernet web interface
 * - RSSI-based auto-clear
 */

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
// #include <Ethernet.h>  // TODO: Add W5500 Ethernet support
// #include <WebServer.h>
#include <ArduinoJson.h>
#include "utilities.h"
#include "loragw_reg.h"
#include "loragw_hal.h"
#include "loragw_spi.h"

// ============= DEFINITIONS =============
#define LGW_TOTALREGS                           1044
#define SX1302_REG_COMMON_CTRL0_CLK32_RIF_CTRL  1
#define LGW_REG_SUCCESS                         0
#define LGW_REG_ERROR                           -1

extern const struct lgw_reg_s loregs[LGW_TOTALREGS + 1];

// Protocol commands
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

// Floor state tracking
struct FloorCall {
  bool upActive = false;
  bool downActive = false;
  bool loadActive = false;
  uint32_t upTime = 0;
  uint32_t downTime = 0;
  uint32_t loadTime = 0;
  int8_t lastRSSI = -120;
  uint32_t lastHeard = 0;
};

struct DisplayPacket {
  uint8_t floor;
  uint8_t status;  // Bit0:UP Bit1:DOWN Bit2:LOAD Bit7:ELEV_POS
  int8_t rssi;
};

// ============= GLOBALS =============
FloorCall floorCalls[TOTAL_FLOORS + 1];  // Index 0 unused, 1-TOTAL_FLOORS
uint8_t currentElevatorFloor = 1;
uint32_t lastDisplayUpdate = 0;
uint32_t totalPacketsReceived = 0;

// Ethernet & Web Server (TODO: Enable when W5500 library is added)
// byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
// IPAddress ip(192, 168, 1, 100);
// WebServer webServer(80);

// ============= FUNCTION PROTOTYPES =============
bool initializeSX1302();
void handleSerialCommands();
void handleLoRaReception();
void processLoRaPacket(struct lgw_pkt_rx_s* pkt);
void sendAcknowledgment(uint8_t floor, uint8_t command, uint8_t messageId);
void checkProximityAndAutoClear();
void handleDisplayRequest();
void handleDisplayCommand(int numBytes);
// void setupWebServer();  // TODO: Enable W5500 support
// void handleWebRoot();
// void handleWebStatus();
void logMessage(const char* msg);

// ============= SETUP =============
void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("========================================"));
  Serial.println(F("Elevator Gateway System v2.0"));
  Serial.println(F("T-ETH Elite + T-SX1302"));
  Serial.println(F("========================================"));

  // Initialize LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Initialize I2C for display communication
  Wire.begin(I2C_SLAVE_ADDRESS, I2C_SDA_PIN, I2C_SCL_PIN);
  Wire.onRequest(handleDisplayRequest);
  Wire.onReceive(handleDisplayCommand);
  Serial.printf("I2C slave initialized at address 0x%02X\n", I2C_SLAVE_ADDRESS);

  // Initialize Ethernet (TODO: Enable W5500 support)
  // Serial.print(F("Initializing Ethernet..."));
  // Ethernet.init(ETH_CS_PIN);
  // Ethernet.begin(mac, ip);
  // delay(1000);
  // Serial.print(F(" IP: "));
  // Serial.println(Ethernet.localIP());

  // Initialize SX1302
  if (!initializeSX1302()) {
    Serial.println(F("SX1302 initialization FAILED!"));
    while (true) {
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      delay(500);
    }
  }

  // Setup web server (TODO: Enable W5500 support)
  // setupWebServer();

  Serial.println(F("Gateway Ready!"));
  Serial.printf("Total Floors: %d\n", TOTAL_FLOORS);
  Serial.printf("Auto-clear RSSI: %d dBm\n", AUTO_CLEAR_RSSI);
  Serial.println(F("\nType 'H' for serial commands help\n"));

  digitalWrite(LED_PIN, HIGH);
}

// ============= MAIN LOOP =============
void loop() {
  // Handle serial commands for testing
  handleSerialCommands();

  // Handle LoRa packet reception
  handleLoRaReception();

  // Check for proximity-based auto-clear (every 100ms)
  static uint32_t lastProximityCheck = 0;
  if (millis() - lastProximityCheck > 100) {
    checkProximityAndAutoClear();
    lastProximityCheck = millis();
  }

  // Handle web server requests (TODO: Enable W5500 support)
  // webServer.handleClient();

  // Blink LED to show we're alive
  static uint32_t lastBlink = 0;
  if (millis() - lastBlink > 1000) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    lastBlink = millis();
  }

  delay(5);  // Small delay to prevent watchdog issues
}

void handleSerialCommands() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd.startsWith("U")) {
      // Simulate UP call: U5 = Floor 5 UP
      int floor = cmd.substring(1).toInt();
      if (floor >= 1 && floor <= TOTAL_FLOORS) {
        floorCalls[floor].upActive = true;
        Serial.printf("Simulated: Floor %d UP\n", floor);
      }
    } else if (cmd.startsWith("D")) {
      // Simulate DOWN call: D5 = Floor 5 DOWN
      int floor = cmd.substring(1).toInt();
      if (floor >= 1 && floor <= TOTAL_FLOORS) {
        floorCalls[floor].downActive = true;
        Serial.printf("Simulated: Floor %d DOWN\n", floor);
      }
    } else if (cmd.startsWith("L")) {
      // Simulate LOAD call: L5 = Floor 5 LOAD
      int floor = cmd.substring(1).toInt();
      if (floor >= 1 && floor <= TOTAL_FLOORS) {
        floorCalls[floor].loadActive = true;
        Serial.printf("Simulated: Floor %d LOAD\n", floor);
      }
    } else if (cmd.startsWith("C")) {
      // Clear floor: C5 = Clear Floor 5
      int floor = cmd.substring(1).toInt();
      if (floor >= 1 && floor <= TOTAL_FLOORS) {
        floorCalls[floor].upActive = false;
        floorCalls[floor].downActive = false;
        floorCalls[floor].loadActive = false;
        Serial.printf("Cleared: Floor %d\n", floor);
      }
    } else if (cmd == "S") {
      // Show status
      Serial.println("\n=== Gateway Status ===");
      Serial.printf("Total packets: %u\n", totalPacketsReceived);
      Serial.printf("Elevator floor: %u\n", currentElevatorFloor);
      Serial.println("\nActive calls:");
      for (uint8_t i = 1; i <= TOTAL_FLOORS; i++) {
        if (floorCalls[i].upActive || floorCalls[i].downActive || floorCalls[i].loadActive) {
          Serial.printf("  Floor %u: ", i);
          if (floorCalls[i].upActive) Serial.print("UP ");
          if (floorCalls[i].downActive) Serial.print("DOWN ");
          if (floorCalls[i].loadActive) Serial.print("LOAD ");
          Serial.printf("(RSSI: %d dBm)\n", floorCalls[i].lastRSSI);
        }
      }
    } else if (cmd == "H") {
      // Help
      Serial.println("\n=== Serial Commands ===");
      Serial.println("U<floor> - Simulate UP call (e.g., U5)");
      Serial.println("D<floor> - Simulate DOWN call (e.g., D10)");
      Serial.println("L<floor> - Simulate LOAD call (e.g., L15)");
      Serial.println("C<floor> - Clear floor (e.g., C5)");
      Serial.println("S - Show status");
      Serial.println("H - Show this help");
    }
  }
}

// ============= SX1302 FUNCTIONS =============
bool initializeSX1302() {
  Serial.print(F("Initializing SX1302..."));

  // Connect to SX1302
  if (lgw_connect("") != LGW_REG_SUCCESS) {
    Serial.println(F(" FAILED to connect!"));
    return false;
  }

  Serial.println(F(" Connected!"));

  // Test register access
  Serial.print(F("Testing SX1302 registers..."));
  int32_t val;
  int x = lgw_reg_r(0, &val);
  if (x != LGW_REG_SUCCESS) {
    Serial.println(F(" FAILED!"));
    return false;
  }
  Serial.println(F(" OK!"));

  // Start the concentrator
  Serial.print(F("Starting SX1302..."));
  if (lgw_start() != LGW_HAL_SUCCESS) {
    Serial.println(F(" FAILED!"));
    return false;
  }
  Serial.println(F(" Started!"));

  return true;
}

void handleLoRaReception() {
  const uint8_t MAX_PACKETS = 8;
  struct lgw_pkt_rx_s rxpkt[MAX_PACKETS];

  int nb_pkt = lgw_receive(MAX_PACKETS, rxpkt);

  if (nb_pkt > 0) {
    for (int i = 0; i < nb_pkt; i++) {
      // Process each received packet
      if (rxpkt[i].status == STAT_CRC_OK && rxpkt[i].size >= 4) {
        processLoRaPacket(&rxpkt[i]);
        totalPacketsReceived++;
      }
    }
  }
}

void processLoRaPacket(struct lgw_pkt_rx_s* pkt) {
  // Extract packet data
  uint8_t floor = pkt->payload[0];
  uint8_t command = pkt->payload[1];
  uint8_t data = pkt->payload[2];
  uint8_t messageId = pkt->payload[3];
  int8_t rssi = (int8_t)pkt->rssis;  // Signal RSSI

  // Validate floor number
  if (floor < 1 || floor > TOTAL_FLOORS) {
    Serial.printf("Invalid floor: %u\n", floor);
    return;
  }

  // Update RSSI tracking
  floorCalls[floor].lastRSSI = rssi;
  floorCalls[floor].lastHeard = millis();

  // Process command
  switch (command) {
    case CMD_CALL_UP:
      floorCalls[floor].upActive = true;
      floorCalls[floor].upTime = millis();
      Serial.printf("Floor %u: UP call (RSSI: %d dBm)\n", floor, rssi);
      sendAcknowledgment(floor, CMD_ACK, messageId);
      break;

    case CMD_CALL_DOWN:
      floorCalls[floor].downActive = true;
      floorCalls[floor].downTime = millis();
      Serial.printf("Floor %u: DOWN call (RSSI: %d dBm)\n", floor, rssi);
      sendAcknowledgment(floor, CMD_ACK, messageId);
      break;

    case CMD_CALL_LOAD:
      floorCalls[floor].loadActive = true;
      floorCalls[floor].loadTime = millis();
      Serial.printf("Floor %u: LOAD call (RSSI: %d dBm)\n", floor, rssi);
      sendAcknowledgment(floor, CMD_ACK, messageId);
      break;

    case CMD_PING:
      // Heartbeat from floor node
      Serial.printf("Floor %u: PING (RSSI: %d dBm)\n", floor, rssi);
      break;

    default:
      Serial.printf("Floor %u: Unknown command 0x%02X\n", floor, command);
      break;
  }
}

void sendAcknowledgment(uint8_t floor, uint8_t command, uint8_t messageId) {
  struct lgw_pkt_tx_s txpkt;
  memset(&txpkt, 0, sizeof(txpkt));

  // Configure TX packet
  txpkt.freq_hz = GATEWAY_FREQUENCY * 1000000;  // Convert MHz to Hz
  txpkt.tx_mode = IMMEDIATE;
  txpkt.rf_chain = 0;
  txpkt.rf_power = 14;  // 14 dBm
  txpkt.modulation = MOD_LORA;
  txpkt.bandwidth = BW_125KHZ;
  txpkt.datarate = DR_LORA_SF7;
  txpkt.coderate = CR_LORA_4_5;
  txpkt.invert_pol = true;
  txpkt.preamble = 8;
  txpkt.no_crc = false;
  txpkt.no_header = false;

  // Build packet payload
  txpkt.payload[0] = floor;
  txpkt.payload[1] = command;
  txpkt.payload[2] = 0;
  txpkt.payload[3] = messageId;
  txpkt.size = 4;

  // Send packet
  int ret = lgw_send(&txpkt);
  if (ret == LGW_HAL_SUCCESS) {
    Serial.printf("ACK sent to floor %u\n", floor);
  } else {
    Serial.printf("ACK send failed: %d\n", ret);
  }
}

void checkProximityAndAutoClear() {
  // Check each floor for proximity-based auto-clear
  for (uint8_t floor = 1; floor <= TOTAL_FLOORS; floor++) {
    if (floorCalls[floor].upActive || floorCalls[floor].downActive || floorCalls[floor].loadActive) {
      // Check if RSSI indicates elevator is at this floor
      if (floorCalls[floor].lastRSSI > AUTO_CLEAR_RSSI) {
        // Strong signal = elevator is nearby, auto-clear
        if (floorCalls[floor].upActive) {
          floorCalls[floor].upActive = false;
          Serial.printf("Auto-cleared Floor %u UP (RSSI: %d dBm)\n", floor, floorCalls[floor].lastRSSI);
        }
        if (floorCalls[floor].downActive) {
          floorCalls[floor].downActive = false;
          Serial.printf("Auto-cleared Floor %u DOWN (RSSI: %d dBm)\n", floor, floorCalls[floor].lastRSSI);
        }
        if (floorCalls[floor].loadActive) {
          floorCalls[floor].loadActive = false;
          Serial.printf("Auto-cleared Floor %u LOAD (RSSI: %d dBm)\n", floor, floorCalls[floor].lastRSSI);
        }
      }
    }
  }
}

// ============= I2C DISPLAY FUNCTIONS =============
void handleDisplayRequest() {
  // Find next floor with active calls to send to display
  static uint8_t lastFloorSent = 0;

  for (uint8_t i = 1; i <= TOTAL_FLOORS; i++) {
    uint8_t floor = (lastFloorSent + i) % (TOTAL_FLOORS + 1);
    if (floor == 0) floor = 1;

    if (floorCalls[floor].upActive || floorCalls[floor].downActive || floorCalls[floor].loadActive) {
      DisplayPacket pkt;
      pkt.floor = floor;
      pkt.status = 0;
      if (floorCalls[floor].upActive) pkt.status |= 0x01;
      if (floorCalls[floor].downActive) pkt.status |= 0x02;
      if (floorCalls[floor].loadActive) pkt.status |= 0x04;
      pkt.rssi = floorCalls[floor].lastRSSI;

      Wire.write((uint8_t*)&pkt, sizeof(DisplayPacket));
      lastFloorSent = floor;
      return;
    }
  }

  // If no active calls, send elevator position
  DisplayPacket pkt;
  pkt.floor = currentElevatorFloor;
  pkt.status = 0x80;  // Bit7 = elevator position
  pkt.rssi = 0;
  Wire.write((uint8_t*)&pkt, sizeof(DisplayPacket));
}

void handleDisplayCommand(int numBytes) {
  if (numBytes != 3) return;

  uint8_t floor = Wire.read();
  uint8_t command = Wire.read();
  uint8_t callType = Wire.read();

  if (floor < 1 || floor > TOTAL_FLOORS) return;

  // Handle clear command from display
  if (command == 0x20) {
    if (callType & 0x01) floorCalls[floor].upActive = false;
    if (callType & 0x02) floorCalls[floor].downActive = false;
    if (callType & 0x04) floorCalls[floor].loadActive = false;

    Serial.printf("Display cleared: Floor %u (mask 0x%02X)\n", floor, callType);
  }
}

// ============= WEB SERVER (TODO: Enable W5500 support) =============
/*
void setupWebServer() {
  webServer.on("/", handleWebRoot);
  webServer.on("/status", handleWebStatus);
  webServer.begin();
  Serial.println(F("Web server started"));
}

void handleWebRoot() {
  String html = "<!DOCTYPE html><html><head><title>Elevator Gateway</title></head><body>";
  html += "<h1>Elevator Gateway System</h1>";
  html += "<p>Total Packets: " + String(totalPacketsReceived) + "</p>";
  html += "<p>Elevator Floor: " + String(currentElevatorFloor) + "</p>";
  html += "<h2>Active Calls:</h2><ul>";

  for (uint8_t i = 1; i <= TOTAL_FLOORS; i++) {
    if (floorCalls[i].upActive || floorCalls[i].downActive || floorCalls[i].loadActive) {
      html += "<li>Floor " + String(i) + ": ";
      if (floorCalls[i].upActive) html += "UP ";
      if (floorCalls[i].downActive) html += "DOWN ";
      if (floorCalls[i].loadActive) html += "LOAD ";
      html += "(RSSI: " + String(floorCalls[i].lastRSSI) + " dBm)</li>";
    }
  }
  html += "</ul></body></html>";
  webServer.send(200, "text/html", html);
}

void handleWebStatus() {
  StaticJsonDocument<512> doc;
  doc["total_packets"] = totalPacketsReceived;
  doc["elevator_floor"] = currentElevatorFloor;
  doc["total_floors"] = TOTAL_FLOORS;

  JsonArray active_calls = doc.createNestedArray("active_calls");
  for (uint8_t i = 1; i <= TOTAL_FLOORS; i++) {
    if (floorCalls[i].upActive || floorCalls[i].downActive || floorCalls[i].loadActive) {
      JsonObject call = active_calls.createNestedObject();
      call["floor"] = i;
      call["up"] = floorCalls[i].upActive;
      call["down"] = floorCalls[i].downActive;
      call["load"] = floorCalls[i].loadActive;
      call["rssi"] = floorCalls[i].lastRSSI;
    }
  }

  String response;
  serializeJson(doc, response);
  webServer.send(200, "application/json", response);
}
*/

void logMessage(const char* msg) {
  Serial.println(msg);
}
