#include <Wire.h>
#include "Adafruit_SGP30.h"

// https://learn.adafruit.com/adafruit-sgp30-gas-tvoc-eco2-mox-sensor/arduino-code
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
  
  // Calibration baselines
  uint16_t baselineeCO2 = readValue(0);
  uint16_t baselineeTVOC = readValue(1);
  Serial.print("< Restauring baselines values: eCO2: 0x"); Serial.print(baselineeCO2, HEX);
  Serial.print(" & TVOC: 0x"); Serial.println(baselineeTVOC, HEX);
  sgp.setIAQBaseline(baselineeCO2, baselineeTVOC); 
}


/* return absolute humidity [mg/m^3] with approximation formula
* @param temperature [°C]
* @param humidity [%RH]
*/
uint32_t getAbsoluteHumidity(float temperature, float humidity) {
    // approximation formula from Sensirion SGP30 Driver Integration chapter 3.15
    const float absoluteHumidity = 216.7f * ((humidity / 100.0f) * 6.112f * exp((17.62f * temperature) / (243.12f + temperature)) / (273.15f + temperature)); // [g/m^3]
    const uint32_t absoluteHumidityScaled = static_cast<uint32_t>(1000.0f * absoluteHumidity); // [mg/m^3]
    return absoluteHumidityScaled;
}

uint16_t co2idx = 1;

int getCo2(float temperature, float humidity) {
  sgp.setHumidity(getAbsoluteHumidity(temperature, humidity));
  
  if (!sgp.IAQmeasure()) {
    Serial.println("Measurement failed");
    return 0;
  }

  if (co2idx++ % 3600 == 0) {
    uint16_t baselineeCO2, baselineeTVOC;
    if (!sgp.getIAQBaseline(&baselineeCO2, &baselineeTVOC)) {
      Serial.println("Failed to get baseline readings");
    } else {
      Serial.print("> Saving baselines values: eCO2: 0x"); Serial.print(baselineeCO2, HEX);
      Serial.print(" & TVOC: 0x"); Serial.println(baselineeTVOC, HEX);
      writeValue(0, baselineeCO2);
      writeValue(1, baselineeTVOC);
    }
  }
  
  return sgp.eCO2;
}
