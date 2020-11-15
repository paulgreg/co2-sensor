#include <Wire.h>
#include "Adafruit_SGP30.h"
#include <EEPROM.h>

Adafruit_SGP30 sgp; // https://learn.adafruit.com/adafruit-sgp30-gas-tvoc-eco2-mox-sensor/arduino-code
 
struct BASELINES {
  uint16_t co2;
  uint16_t tvoc;
};

BASELINES baselines;

void setupCo2() {
  if (!sgp.begin()){
    Serial.println("Sensor not found !");
    delay(1000);
    while (1);
  }
  Serial.print("Found SGP30 serial #");
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);

  // Calibration baselines
  EEPROM.begin(sizeof(baselines));
  EEPROM.get(0, baselines);
  Serial.print("< Restauring baselines values: eCO2: 0x"); Serial.print(baselines.co2, HEX);
  Serial.print(" & TVOC: 0x"); Serial.println(baselines.tvoc, HEX);
  sgp.setIAQBaseline(baselines.co2, baselines.tvoc); 
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
  if (co2idx++ % 360 == 0) {
    if (!sgp.getIAQBaseline(&baselines.co2, &baselines.tvoc)) {
      Serial.println("Failed to get baseline readings");
    } else {
      Serial.print("> Saving baselines values: eCO2: 0x"); Serial.print(baselines.co2, HEX);
      Serial.print(" & TVOC: 0x"); Serial.println(baselines.tvoc, HEX);
      EEPROM.put(0, baselines);
      EEPROM.commit();
    }
  }
  
  return sgp.eCO2;
}
