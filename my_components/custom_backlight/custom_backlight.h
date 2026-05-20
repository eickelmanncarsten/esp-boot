#pragma once
#include "esphome.h"
#include "esphome/core/component.h"
#include "esphome/components/output/binary_output.h"

namespace custom_backlight {

class CustomBacklightOutput : public esphome::output::BinaryOutput, public esphome::Component {
 private:
  esphome::Component *hub_{nullptr};

 public:
  void set_pin_hub(esphome::Component *hub) { this->hub_ = hub; }

  void setup() override {
    // Hier kommt deine originale Initialisierung hin
  }

  void write_state(bool state) override {
    if (state) {
      ESP_LOGD("backlight", "Backlight wird eingeschaltet...");
    } else {
      ESP_LOGD("backlight", "Backlight wird ausgeschaltet...");
    }
  }
};

}  // namespace custom_backlight
