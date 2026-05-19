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
    this->write_state(true); // Schaltet das Backlight initial ein
  }

  void write_state(bool state) override {
    // KORREKTUR: pin_write statt digital_write
    if (this->hub_ != nullptr) {
        this->hub_->pin_write(5, state); 
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
    // JETZT EXAKT: digital_write ist die richtige Methode für den PCA9554
    if (this->hub_ != nullptr) {
        this->hub_->digital_write(5, state); 
    }
  }

 protected:
  pca9554::PCA9554Component *hub_{nullptr};
};

}  // namespace custom_backlight
}  // namespace esphome
    }
  }

 protected:
  pca9554::PCA9554Component *hub_{nullptr};
};

}  // namespace custom_backlight
}  // namespace esphome
