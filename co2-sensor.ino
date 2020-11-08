// reset should be only set the first time and revert then
#define RESET_EEPROM false

#define CO2_THRESHOLD 1000

#include "eeprom.h"
#include "display.h"
#include "co2.h"
#include "thermometer.h"

void setup() {
  Serial.begin(115200);
  delay(500);
  setupEEPROM(RESET_EEPROM);
  setupScreen();
  setupCo2();
  setupThermometer();
}

uint16_t serialIdx = 0;

void loop() {
  float temperature = getTemperature();
  float humidity = getHumidity();
  unsigned int co2 = getCo2(temperature, humidity);
  if (serialIdx++ % 60 == 0) Serial.printf("Update: temp: %2.2f c - humitidy: %3f - co2: %4i\n", temperature, humidity, co2);
  displayData(temperature, humidity, co2);
  delay(1000);
}
