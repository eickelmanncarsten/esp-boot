#pragma once
#include "esphome.h"

namespace custom_touch {

class CustomTouch : public esphome::Component, public esphome::i2c::I2CDevice {
 public:
  void setup() override {
    // Hier holen wir uns den I2C-Bus über seine ID aus dem YAML ("bus_a")
    this->set_i2c_bus(id(bus_a));
    // Hier setzen wir die Adresse (0x38 = 56)
    this->set_i2c_address(0x38);
    
    ESP_LOGD("custom_touch", "Initialisiere FocalTech Touchscreen auf Adresse 0x%02X...", this->address_);
  }
  void loop() override {}
};

}  // namespace custom_touch
