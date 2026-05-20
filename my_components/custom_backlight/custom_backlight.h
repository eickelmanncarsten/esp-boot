#pragma once
#include "esphome.h"

namespace custom_backlight {

class CustomBacklightOutput : public esphome::output::BinaryOutput, public esphome::Component {
 private:
  esphome::Component *hub_{nullptr};

 public:
  void set_pin_hub(esphome::Component *hub) { this->hub_ = hub; }

  void setup() override {
    // Hier kommt deine originale Initialisierung für den PCA9554-Pin des Backlights hin
    // Da wir den Hub als Pointer haben, kannst du ihn direkt ansprechen.
  }

  void write_state(bool state) override {
    // Hier wird das Backlight ein- oder ausgeschaltet
    if (state) {
      ESP_LOGD("backlight", "Backlight wird eingeschaltet...");
    } else {
      ESP_LOGD("backlight", "Backlight wird ausgeschaltet...");
    }
  }
};

}  // namespace custom_backlight
