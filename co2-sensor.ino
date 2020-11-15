#include "parameters.h"
#include "display.h"
#include "co2.h"
#include "thermometer.h"
#include "network.h"

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("eCO2 sensor");
  setupScreen();
  setupCo2();
  setupThermometer();
}

uint16_t serialIdx = 1; // set to one to avoid sending first imprecise reading

void loop() {
  float temperature = getTemperature();
  float humidity = getHumidity();
  unsigned int co2 = getCo2(temperature, humidity);
  displayData(temperature, humidity, co2);
  if (serialIdx++ % 6 == 0) {
    Serial.printf("Update: temp: %.1f c - humitidy: %.0f - co2: %i\n", temperature, humidity, co2);
    #ifdef WIFI_SSID
    if (connectToWifi(WIFI_SSID, WIFI_PASSWORD)) {
       sendMetrics(temperature, humidity, co2);
    }
    #endif
  }
  delay(10 * 1000);
}
