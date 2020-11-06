#define CO2_THRESHOLD 410

#include "display.h"
#include "thermometer.h"

void setup() {
  Serial.begin(115200);
  setupScreen();
  setupThermometer();
}

void loop() {
  float temperature = getTemperature();
  float humidity = getHumidity();
  int co2 = 400;
  Serial.printf("Update: temp: %2.2f c - humitidy: %3f - co2: %4i\n", temperature, humidity, co2);
  displayData(temperature, humidity, co2);
  delay(100);
}
