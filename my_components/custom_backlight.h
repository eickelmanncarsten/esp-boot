#pragma once
#include "esphome.h"

class CustomBacklightOutput : public esphome::output::BinaryOutput, public esphome::Component {
 private:
  esphome::Component *hub_{nullptr};

 public:
  void set_pin_hub(esphome::Component *hub) { this->hub_ = hub; }

  void setup() override {
    // Initialisierung falls nötig
  }

  void write_state(bool state) override {
    if (state) {
      ESP_LOGD("backlight", "Backlight wird eingeschaltet...");
    } else {
      ESP_LOGD("backlight", "Backlight wird ausgeschaltet...");
    }
  }
};
