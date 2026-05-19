#pragma once

#include "esphome/core/component.h"
#include "esphome/components/output/binary_output.h"
#include "esphome/components/pca9554/pca9554.h"

namespace esphome {
namespace custom_backlight {

class CustomBacklightOutput : public output::BinaryOutput, public Component {
 public:
  // Wir übergeben dem Backlight die Instanz unseres Expanders
  void set_pin_hub(pca9554::PCA9554Component *hub) { this->hub_ = hub; }

  void setup() override {
    // Schaltet das Backlight beim Starten initial ein
    this->write_state(true);
  }

  void write_state(bool state) override {
    // Greift sauber über die offizielle ESPHome-Komponente auf Pin 5 zu
    if (this->hub_ != nullptr) {
        this->hub_->digital_write(5, state);
    }
  }

 protected:
  pca9554::PCA9554Component *hub_{nullptr};
};

}  // namespace custom_backlight
}  // namespace esphome
