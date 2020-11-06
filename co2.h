#include <Wire.h>
#include "Adafruit_SGP30.h"

Adafruit_SGP30 sgp;

void setupCo2() {
  if (!sgp.begin()){
    Serial.println("Sensor not found :(");
    while (1);
  }
  Serial.print("Found SGP30 serial #");
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);
}

int co2 = 0;

int getCo2() {
  if (!sgp.IAQmeasure()) {
    Serial.println("Measurement failed");
    return co2;
  }
  return sgp.eCO2;
}
