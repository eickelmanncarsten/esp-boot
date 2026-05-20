#pragma once
#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "driver/i2c_master.h" // Nativer ESP-IDF I2C-Treiber

namespace esphome {

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
    delay(150); 

    ESP_LOGD("custom_i2c", "Initialisiere nativen ESP-IDF I2C-Master auf Port 1...");

    // 2. Bus-Konfiguration für Port 1 erstellen
    i2c_master_bus_config_t bus_config = {};
    bus_config.i2c_port = I2C_NUM_1; // Explizit Port 1 nutzen!
    bus_config.sda_io_num = GPIO_NUM_6;
    bus_config.scl_io_num = GPIO_NUM_7;
    bus_config.clk_source = I2C_CLK_SRC_DEFAULT;
    bus_config.glitch_ignore_cnt = 7;
    bus_config.flags.enable_internal_pullup = true;

    i2c_master_bus_handle_t bus_handle;
    esp_err_t err = i2c_new_master_bus(&bus_config, &bus_handle);

    if (err != ESP_OK) {
      ESP_LOGE("custom_i2c", "Native Bus-Initialisierung fehlgeschlagen! Fehler: %s", esp_err_to_name(err));
      return;
    }

    // 3. Device-Konfiguration für den PCA9554 (0x20) hinzufügen
    i2c_device_config_t dev_config = {};
    dev_config.dev_addr_length = I2C_ADDR_BIT_LEN_7;
    dev_config.device_address = 0x20;
    dev_config.scl_speed_hz = 100000;

    i2c_master_dev_handle_t dev_handle;
    err = i2c_master_bus_add_device(bus_handle, &dev_config, &dev_handle);

    if (err == ESP_OK) {
      ESP_LOGI("custom_i2c", "+++ ERFOLG: PCA9554 (0x20) an nativen Port 1 gebunden! +++");

      // 4. Register beschreiben (Pin 0 als Output konfigurieren)
      // Register 0x03 (Configuration), Wert 0xFE (Pin 0 = Output, Rest = Input)
      uint8_t config_data[2] = {0x03, 0xFE};
      err = i2c_master_transmit(dev_handle, config_data, 2, 1000);
      if (err != ESP_OK) {
        ESP_LOGE("custom_i2c", "Fehler beim Schreiben des Konfigurationsregisters: %s", esp_err_to_name(err));
      }

      // 5. Pin 0 auf HIGH setzen (Backlight einschalten)
      // Register 0x01 (Output Port), Wert 0x01 (Pin 0 = HIGH)
      uint8_t write_data[2] = {0x01, 0x01};
      err = i2c_master_transmit(dev_handle, write_data, 2, 1000);
      
      if (err == ESP_OK) {
        ESP_LOGI("custom_i2c", "Backlight-Befehl erfolgreich nativ abgesetzt!");
      } else {
        ESP_LOGE("custom_i2c", "Fehler beim Senden des Backlight-Signals: %s", esp_err_to_name(err));
      }

    } else {
      ESP_LOGE("custom_i2c", "Konnte Device nicht an den Bus binden. Fehler: %s", esp_err_to_name(err));
    }
  }
};

}  // namespace esphome
