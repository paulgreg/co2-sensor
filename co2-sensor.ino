#define CO2_THRESHOLD 410

#include "display.h"
#include "thermometer.h"

void setup() {
  Serial.begin(115200);

  setupScreen();  
  setupThermometer();

  delay(500);
  display.clearDisplay();
}

bool fakeCO2Climb = true;
int fakeCO2 = 800;

void loop() {
  float temp = getTemperature("temp : ", thermometer);

  if (fakeCO2Climb) fakeCO2++;
  else fakeCO2--;

  if (fakeCO2 > 600) fakeCO2Climb = false;
  else if (fakeCO2 < 500) fakeCO2Climb = true;

  Serial.printf("Update: temp: %2.2f c - co2: %4i\n", temp, fakeCO2);
  
  displayData(temp, fakeCO2);
  delay(10);
}
