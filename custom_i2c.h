#include "esphome.h"
#include <Wire.h>

class CustomI2CInit : public Component {
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
    delay(100);

    // 2. Den echten I2C-Bus mit der Arduino Wire-Bibliothek initialisieren
    // Das umgeht den blockierenden ESP-IDF-Treiber vollständig!
    Wire.begin(6, 7, 100000); 
    
    // 3. Den PCA9554 (0x20) direkt ansprechen und das Backlight einschalten
    Wire.beginTransmission(0x20);
    byte error = Wire.endTransmission();
    
    if (error == 0) {
      ESP_LOGI("custom_i2c", "Erfolg! PCA9554 an 0x20 reagiert auf Arduino Wire!");
      
      // Pin 0 (Backlight) als Ausgang definieren
      Wire.beginTransmission(0x20);
      Wire.write(0x03); // Konfigurationsregister
      Wire.write(0xFE); // Pin 0 = Output, Rest = Input
      Wire.endTransmission();

      // Pin 0 auf HIGH setzen (Backlight einschalten)
      Wire.beginTransmission(0x20);
      Wire.write(0x01); // Ausgangsregister
      Wire.write(0x01); // Pin 0 auf HIGH
      Wire.endTransmission();
      ESP_LOGI("custom_i2c", "Backlight-Befehl erfolgreich gesendet!");
    } else {
      ESP_LOGE("custom_i2c", "PCA9554 hat nicht geantwortet. Fehlercode: %d", error);
    }
  }
};
