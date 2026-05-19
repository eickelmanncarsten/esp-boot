#pragma once

#include "esphome/core/component.h"
#include "esphome/components/output/binary_output.h"
#include "esphome/components/pca9554/pca9554.h"

namespace esphome {
namespace custom_backlight {

class CustomBacklightOutput : public output::BinaryOutput, public Component {
 public:
  void set_pin_hub(pca9554::PCA9554Component *hub) { this->hub_ = hub; }

  void setup() override {
    this->write_state(true);
  }

  void write_state(bool state) override {
    if (this->hub_ != nullptr) {
        // Nutzt die korrekte, offizielle Methode der ESPHome PCA9554-Komponente
        this->hub_->digital_write(5, state); 
    }
  }

 protected:
  pca9554::PCA9554Component *hub_{nullptr};
};

}  // namespace custom_backlight
}  // namespace esphome
