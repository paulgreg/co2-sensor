#define CO2_THRESHOLD 1000

#include "display.h"
#include "co2.h"
#include "thermometer.h"

void setup() {
  Serial.begin(115200);
  setupScreen();
  setupCo2();
  setupThermometer();
}

int i = 0;

void loop() {
  float temperature = getTemperature();
  float humidity = getHumidity();
  int co2 = getCo2();
  if (i++ % 100 == 0) Serial.printf("Update: temp: %2.2f c - humitidy: %3f - co2: %4i\n", temperature, humidity, co2);
  displayData(temperature, humidity, co2);
  delay(100);
}
