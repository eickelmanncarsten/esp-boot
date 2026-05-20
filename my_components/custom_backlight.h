#pragma once
#include "esphome.h"

class CustomBacklightOutput {
 private:
  esphome::Component *hub_{nullptr};

 public:
  void set_pin_hub(esphome::Component *hub) { this->hub_ = hub; }

  void set_state(bool state) {
    if (state) {
      ESP_LOGD("backlight", "Backlight wird eingeschaltet...");
      // Hier läuft dein originaler Code zum Einschalten über den Expander
    } else {
      ESP_LOGD("backlight", "Backlight wird ausgeschaltet...");
      // Hier läuft dein originaler Code zum Ausschalten über den Expander
    }
  }
};

// Wir erstellen direkt eine globale Instanz, die wir im YAML ansprechen können
extern CustomBacklightOutput my_bl;
CustomBacklightOutput my_bl;
