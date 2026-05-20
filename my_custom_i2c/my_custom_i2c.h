#pragma once
#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include <Wire.h>

namespace esphome {

// Wir erstellen eine dedizierte Instanz für den zweiten Hardware-I2C-Port (1)
TwoWire MyWire(1);

class MyCustomI2CComponent : public Component {
 public:
  void setup() override {
    ESP_LOGD("custom_i2c", "Starte manuellen Hardware-Reset der Peripherie...");
    
    // 1. Reset-Pins hart ansteuern, um alle ICs aufzuwecken
    pinMode(5, OUTPUT);
    digitalWrite(5, LOW);
    pinMode(40, OUTPUT);
    digitalWrite(40, LOW);
    delay(50);
    digitalWrite(5, HIGH);
    digitalWrite(40, HIGH);
    delay(150); // Dem Bus etwas mehr Zeit geben, sich elektrisch einzupendeln

    ESP_LOGD("custom_i2c", "Initialisiere Arduino Wire auf Hardware-Port 1...");
    // 2. Den echten I2C-Bus (Pins 6 & 7) auf dem freien Port 1 starten
    MyWire.begin(6, 7, 100000); 
    
    // 3. Den PCA9554 (0x20) direkt ansprechen und das Backlight einschalten
    MyWire.beginTransmission(0x20);
    byte error = MyWire.endTransmission();
    
    if (error == 0) {
      ESP_LOGI("custom_i2c", "+++ ERFOLG! PCA9554 an 0x20 reagiert auf Port 1 +++");
      
      // Pin 0 (Backlight) als Ausgang definieren
      MyWire.beginTransmission(0x20);
      MyWire.write(0x03); // Konfigurationsregister
      MyWire.write(0xFE); // Pin 0 = Output, Rest = Input
      MyWire.endTransmission();

      // Pin 0 auf HIGH setzen (Backlight einschalten)
      MyWire.beginTransmission(0x20);
      MyWire.write(0x01); // Ausgangsregister
      MyWire.write(0x01); // Pin 0 auf HIGH
      MyWire.endTransmission();
      ESP_LOGI("custom_i2c", "Backlight-Befehl wurde erfolgreich abgesetzt!");
    } else {
      ESP_LOGE("custom_i2c", "PCA9554 hat auf Port 1 nicht geantwortet. Fehlercode: %d", error);
    }
  }
};

}  // namespace esphome
