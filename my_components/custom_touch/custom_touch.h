#pragma once
#include "esphome.h"

// Der Namespace muss mit der __init__.py übereinstimmen
namespace custom_touch {

class CustomTouch : public esphome::Component, public esphome::i2c::I2CDevice {
 public:
  void setup() override {
    ESP_LOGD("custom_touch", "Initialisiere FocalTech Touchscreen auf Adresse 0x%02X...", this->address_);
  }
  void loop() override {}
};

}  // namespace custom_touch
