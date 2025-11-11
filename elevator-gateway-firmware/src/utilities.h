#pragma once

// T-ETH-Elite ESP32-S3 Pin Definitions
#define LILYGO_T_ETH_ELITE_ESP32S3

// Ethernet pins (W5500)
#define ETH_MISO_PIN                     47
#define ETH_MOSI_PIN                     21
#define ETH_SCLK_PIN                     48
#define ETH_CS_PIN                       45
#define ETH_INT_PIN                      14
#define ETH_RST_PIN                      -1
#define ETH_ADDR                         1

// SPI pins (shared by LoRa/SD)
#define SPI_MISO_PIN                     9
#define SPI_MOSI_PIN                     11
#define SPI_SCLK_PIN                     10

// SD Card pins
#define SD_MISO_PIN                      SPI_MISO_PIN
#define SD_MOSI_PIN                      SPI_MOSI_PIN
#define SD_SCLK_PIN                      SPI_SCLK_PIN
#define SD_CS_PIN                        12

// I2C pins (for CrowPanel display)
#define I2C_SDA_PIN                      17
#define I2C_SCL_PIN                      18

// SX1302 LoRa Gateway pins
#define RADIO_MISO_PIN                   SPI_MISO_PIN
#define RADIO_MOSI_PIN                   SPI_MOSI_PIN
#define RADIO_SCLK_PIN                   SPI_SCLK_PIN
#define RADIO_CS_PIN                     40
#define RADIO_RST_PIN                    46
#define RADIO_IRQ_PIN                    8
#define RADIO_BUSY_PIN                   16

// GPS pins (on SX1302 shield)
#define GPS_RX_PIN                       39
#define GPS_TX_PIN                       42

// LED
#define LED_PIN                          38
