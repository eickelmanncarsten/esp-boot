#pragma once
#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace custom_touch {

class CustomTouch : public Component, public i2c::I2CDevice {
 public:
  void setup() override {
    // Der I2C-Bus ist bereits frei, wir senden nur ein kurzes Hallo an den Chip
    ESP_LOGD("custom_touch", "Initialisiere FocalTech Touchscreen auf Adresse 0x%02X...", this->address_);
  }
  void loop() override {
    // Hier fügen wir später die Touch-Koordinaten ein, sobald das Display leuchtet
  }
};

}  // namespace custom_touch
}  // namespace esphome
