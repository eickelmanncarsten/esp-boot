#pragma once

#include "esphome/core/component.h"
#include "esphome/components/output/binary_output.h"
#include "esphome/components/pca9554/pca9554.h"

namespace esphome {
namespace custom_backlight {

class CustomBacklightOutput : public output::BinaryOutput, public Component {
 public:
  void setup() override {
    // Wartet, bis der I2C-Expander bereit ist, und schaltet das Backlight initial ein
    this->write_state(true);
  }

  void write_state(bool state) override {
    // Holt sich die Instanz des TCA9554-Hubs aus der laufenden Applikation
    // Pin 5 steuert laut Schaltplan die Hintergrundbeleuchtung
    if (pca9554::global_pca9554_channels[0] != nullptr) {
        pca9554::global_pca9554_channels[0]->digital_write(5, state);
    }
  }
};

}  // namespace custom_backlight
}  // namespace esphome
