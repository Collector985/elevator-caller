/**
 * I2C Pin Scanner for GT911 Touch Controller
 * Tests multiple GPIO pin combinations to find the correct I2C pins
 */

#include <Arduino.h>
#include <Wire.h>

// Common ESP32-S3 GPIO pins that could be used for I2C
const uint8_t test_pins[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42
};

const int num_pins = sizeof(test_pins) / sizeof(test_pins[0]);

void scanI2COnPins(uint8_t sda, uint8_t scl) {
    TwoWire testBus = TwoWire(0);

    // Try to initialize the I2C bus
    if (!testBus.begin(sda, scl, 400000)) {
        return;  // Failed to initialize
    }

    delay(10);

    // Scan for devices on this pin combination
    for (uint8_t addr = 0x01; addr < 0x7F; addr++) {
        testBus.beginTransmission(addr);
        uint8_t error = testBus.endTransmission();

        if (error == 0) {
            Serial.printf(">>> FOUND! GPIO %d (SDA) / GPIO %d (SCL) -> Device at 0x%02X",
                         sda, scl, addr);

            if (addr == 0x14 || addr == 0x5D) {
                Serial.print(" *** GT911 TOUCH CONTROLLER ***");
            } else if (addr == 0x18) {
                Serial.print(" (TCA9534)");
            } else if (addr == 0x30) {
                Serial.print(" (Backlight)");
            }
            Serial.println();
        }
    }

    testBus.end();
    delay(10);
}

void setup() {
    Serial.begin(115200);
    delay(2000);

    Serial.println("\n\n");
    Serial.println("=======================================================");
    Serial.println("      I2C PIN SCANNER FOR GT911 TOUCH CONTROLLER");
    Serial.println("=======================================================");
    Serial.println("Scanning all possible GPIO pin combinations...");
    Serial.println("This will take a few minutes...");
    Serial.println("=======================================================\n");

    int combinationsTested = 0;
    int devicesFound = 0;

    // Test all combinations of SDA/SCL pins
    for (int i = 0; i < num_pins; i++) {
        for (int j = 0; j < num_pins; j++) {
            if (i == j) continue;  // Skip same pin

            uint8_t sda = test_pins[i];
            uint8_t scl = test_pins[j];

            combinationsTested++;

            // Print progress every 50 combinations
            if (combinationsTested % 50 == 0) {
                Serial.printf("Progress: Tested %d combinations...\n", combinationsTested);
            }

            scanI2COnPins(sda, scl);
        }
    }

    Serial.println("\n=======================================================");
    Serial.printf("Scan complete! Tested %d pin combinations.\n", combinationsTested);
    Serial.println("=======================================================");
    Serial.println("\nLook for lines with '*** GT911 TOUCH CONTROLLER ***'");
    Serial.println("Those are the correct pins to use!\n");
}

void loop() {
    // Nothing to do
    delay(1000);
}
