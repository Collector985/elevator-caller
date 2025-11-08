#pragma once

#define LGFX_USE_V1

#include <LovyanGFX.hpp>
#include <lgfx/v1/platforms/esp32s3/Panel_RGB.hpp>
#include <lgfx/v1/platforms/esp32s3/Bus_RGB.hpp>

class LGFX : public lgfx::LGFX_Device {
 public:
  LGFX() {
    auto bus_cfg = _bus_instance.config();
    bus_cfg.panel = &_panel_instance;

    bus_cfg.pin_d0 = GPIO_NUM_21;
    bus_cfg.pin_d1 = GPIO_NUM_47;
    bus_cfg.pin_d2 = GPIO_NUM_48;
    bus_cfg.pin_d3 = GPIO_NUM_45;
    bus_cfg.pin_d4 = GPIO_NUM_38;
    bus_cfg.pin_d5 = GPIO_NUM_9;
    bus_cfg.pin_d6 = GPIO_NUM_10;
    bus_cfg.pin_d7 = GPIO_NUM_11;
    bus_cfg.pin_d8 = GPIO_NUM_12;
    bus_cfg.pin_d9 = GPIO_NUM_13;
    bus_cfg.pin_d10 = GPIO_NUM_14;
    bus_cfg.pin_d11 = GPIO_NUM_7;
    bus_cfg.pin_d12 = GPIO_NUM_17;
    bus_cfg.pin_d13 = GPIO_NUM_18;
    bus_cfg.pin_d14 = GPIO_NUM_8;
    bus_cfg.pin_d15 = GPIO_NUM_46;

    bus_cfg.pin_henable = GPIO_NUM_42;
    bus_cfg.pin_vsync = GPIO_NUM_41;
    bus_cfg.pin_hsync = GPIO_NUM_40;
    bus_cfg.pin_pclk = GPIO_NUM_39;

    bus_cfg.freq_write = 16000000;
    bus_cfg.hsync_polarity = 0;
    bus_cfg.hsync_front_porch = 40;
    bus_cfg.hsync_pulse_width = 48;
    bus_cfg.hsync_back_porch = 40;

    bus_cfg.vsync_polarity = 0;
    bus_cfg.vsync_front_porch = 13;
    bus_cfg.vsync_pulse_width = 3;
    bus_cfg.vsync_back_porch = 32;

    bus_cfg.pclk_active_neg = 1;
    bus_cfg.de_idle_high = 0;
    bus_cfg.pclk_idle_high = 0;

    _bus_instance.config(bus_cfg);

    auto panel_cfg = _panel_instance.config();
    panel_cfg.memory_width = 800;
    panel_cfg.memory_height = 480;
    panel_cfg.panel_width = 800;
    panel_cfg.panel_height = 480;
    _panel_instance.config(panel_cfg);

    auto detail_cfg = _panel_instance.config_detail();
    detail_cfg.use_psram = 1;
    _panel_instance.config_detail(detail_cfg);

    _panel_instance.setBus(&_bus_instance);
    setPanel(&_panel_instance);
  }

 private:
  lgfx::Panel_RGB _panel_instance;
  lgfx::Bus_RGB _bus_instance;
};
