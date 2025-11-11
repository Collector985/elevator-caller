/**
 * T-Beam Supreme Floor Call Simulator
 *
 * Simulates random floor calling with UP, DOWN, and LOAD (materials) calls
 * Sends LoRa packets to T-ETH Elite gateway for testing display integration
 *
 * Hardware: T-Beam Supreme (ESP32-S3 + SX1262)
 */

#include <Arduino.h>
#include <RadioLib.h>

// T-Beam Supreme Pin Definitions
// Note: These may vary depending on your exact T-Beam Supreme version
// Standard T-Beam v1.2+ pins:
#define LORA_MISO_PIN   19
#define LORA_MOSI_PIN   27
#define LORA_SCLK_PIN   5
#define LORA_CS_PIN     18
#define LORA_RST_PIN    23
#define LORA_DIO1_PIN   33
#define LORA_BUSY_PIN   32

// LED pin
#define LED_PIN         4

// Protocol commands (matching gateway)
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

// LoRa radio instance (SX1262)
SX1262 radio = new Module(LORA_CS_PIN, LORA_DIO1_PIN, LORA_RST_PIN, LORA_BUSY_PIN);

// State variables
uint8_t messageId = 0;
uint32_t lastCallTime = 0;
uint32_t nextCallInterval = 0;
uint32_t totalCalls = 0;
uint32_t upCalls = 0;
uint32_t downCalls = 0;
uint32_t loadCalls = 0;

// Function prototypes
bool initializeLoRa();
void sendRandomCall();
void sendPacket(uint8_t floor, uint8_t command, uint8_t data);
uint8_t calculateChecksum(uint8_t* data, uint8_t len);
void ledFlash(uint8_t times);
void printStats();

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println(F("========================================"));
  Serial.println(F("T-Beam Supreme Floor Call Simulator"));
  Serial.println(F("Random UP/DOWN/LOAD Testing"));
  Serial.println(F("========================================"));

  // Initialize LED
  pinMode(LED_PIN, OUTPUT);
  ledFlash(3);

  // Initialize LoRa
  if (!initializeLoRa()) {
    Serial.println(F("LoRa initialization FAILED!"));
    while (true) {
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      delay(200);
    }
  }

  Serial.println(F("\n*** Simulator Started ***"));
  Serial.print(F("Frequency: "));
  Serial.print(LORA_FREQUENCY);
  Serial.println(F(" MHz"));
  Serial.print(F("Spreading Factor: "));
  Serial.println(SPREADING_FACTOR);
  Serial.print(F("TX Power: "));
  Serial.print(TX_POWER);
  Serial.println(F(" dBm"));
  Serial.print(F("Total Floors: "));
  Serial.println(TOTAL_FLOORS);
  Serial.print(F("Call Interval: "));
  Serial.print(MIN_CALL_INTERVAL / 1000);
  Serial.print(F("-"));
  Serial.print(MAX_CALL_INTERVAL / 1000);
  Serial.println(F(" seconds\n"));

  // Set first random interval
  randomSeed(esp_random());
  nextCallInterval = random(MIN_CALL_INTERVAL, MAX_CALL_INTERVAL);
}

void loop() {
  uint32_t now = millis();

  // Send random call at random intervals
  if (now - lastCallTime >= nextCallInterval) {
    sendRandomCall();
    lastCallTime = now;
    nextCallInterval = random(MIN_CALL_INTERVAL, MAX_CALL_INTERVAL);
  }

  // Check for incoming ACKs (optional)
  if (radio.available()) {
    uint8_t buf[255];
    int state = radio.readData(buf, sizeof(buf));

    if (state == RADIOLIB_ERR_NONE) {
      int16_t rssi = radio.getRSSI();
      Serial.print(F("RX: Cmd=0x"));
      Serial.print(buf[1], HEX);
      Serial.print(F(" RSSI="));
      Serial.print(rssi);
      Serial.println(F(" dBm"));

      if (buf[1] == CMD_ACK) {
        Serial.println(F("  -> ACK received!"));
        ledFlash(1);
      }
    }
  }

  delay(100);
}

bool initializeLoRa() {
  Serial.print(F("Initializing SX1262... "));

  // Initialize SX1262
  int state = radio.begin();

  if (state != RADIOLIB_ERR_NONE) {
    Serial.print(F("failed, code "));
    Serial.println(state);
    return false;
  }

  Serial.println(F("success!"));

  // Set LoRa parameters to match gateway
  radio.setFrequency(LORA_FREQUENCY);
  radio.setSpreadingFactor(SPREADING_FACTOR);
  radio.setOutputPower(TX_POWER);
  radio.setBandwidth(125.0);
  radio.setCodingRate(5);
  radio.setPreambleLength(8);
  radio.setSyncWord(0x12);  // Standard LoRa sync word

  Serial.println(F("LoRa configured successfully"));
  return true;
}

void sendRandomCall() {
  // Generate random floor (1 to TOTAL_FLOORS)
  uint8_t randomFloor = random(1, TOTAL_FLOORS + 1);

  // Generate random call type (UP, DOWN, or LOAD)
  // Weight: 40% UP, 40% DOWN, 20% LOAD
  uint8_t randomType = random(100);
  uint8_t command;
  const char* callTypeName;

  if (randomType < 40) {
    command = CMD_CALL_UP;
    callTypeName = "UP";
    upCalls++;
  } else if (randomType < 80) {
    command = CMD_CALL_DOWN;
    callTypeName = "DOWN";
    downCalls++;
  } else {
    command = CMD_CALL_LOAD;
    callTypeName = "LOAD";
    loadCalls++;
  }

  totalCalls++;

  // Send the packet
  Serial.print(F("Sending: Floor "));
  Serial.print(randomFloor);
  Serial.print(F(" - "));
  Serial.println(callTypeName);

  sendPacket(randomFloor, command, 0);

  // Flash LED
  digitalWrite(LED_PIN, HIGH);
  delay(50);
  digitalWrite(LED_PIN, LOW);

  // Print statistics every 10 calls
  if (totalCalls % 10 == 0) {
    printStats();
  }
}

void sendPacket(uint8_t floor, uint8_t command, uint8_t data) {
  uint8_t packet[5];
  packet[0] = floor;
  packet[1] = command;
  packet[2] = data;
  packet[3] = messageId++;
  packet[4] = calculateChecksum(packet, 4);

  int state = radio.transmit(packet, sizeof(packet));

  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("  -> Packet sent successfully"));
  } else {
    Serial.print(F("  -> TX failed, code "));
    Serial.println(state);
  }
}

uint8_t calculateChecksum(uint8_t* data, uint8_t len) {
  uint8_t sum = 0;
  for (uint8_t i = 0; i < len; i++) {
    sum ^= data[i];
  }
  return sum;
}

void ledFlash(uint8_t times) {
  for (uint8_t i = 0; i < times; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
}

void printStats() {
  Serial.println(F("\n========== STATISTICS =========="));
  Serial.print(F("Total Calls: "));
  Serial.println(totalCalls);
  Serial.print(F("  UP:   "));
  Serial.print(upCalls);
  Serial.print(F(" ("));
  Serial.print((upCalls * 100) / totalCalls);
  Serial.println(F("%)"));
  Serial.print(F("  DOWN: "));
  Serial.print(downCalls);
  Serial.print(F(" ("));
  Serial.print((downCalls * 100) / totalCalls);
  Serial.println(F("%)"));
  Serial.print(F("  LOAD: "));
  Serial.print(loadCalls);
  Serial.print(F(" ("));
  Serial.print((loadCalls * 100) / totalCalls);
  Serial.println(F("%)"));
  Serial.println(F("================================\n"));
}
