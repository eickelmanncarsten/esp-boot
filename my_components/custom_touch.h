#pragma once
#include "esphome.h"

class CustomTouch : public esphome::Component, public esphome::i2c::I2CDevice {
 public:
  void setup() override {
    // Das '&' sorgt dafür, dass die Adresse des Busses übergeben wird
    this->set_i2c_bus(&id(bus_a));
    this->set_i2c_address(0x38);
    ESP_LOGD("custom_touch", "Initialisiere FocalTech Touchscreen auf Adresse 0x%02X...", this->address_);
  }
  void loop() override {}
};
