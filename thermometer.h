#include <OneWire.h>
#include <DallasTemperature.h>
// A 4.7K resistor is necessary between +5V and Data wire  
#define PIN_ONEWIRE D5

OneWire oneWire(PIN_ONEWIRE); 
#define TEMPERATURE_PRECISION 10

DallasTemperature sensors(&oneWire);
// That address is what is printed on serial port when starting the project by the OneWireScanner function
DeviceAddress thermometer = { 0x28,  0xBD,  0xEA,  0x16,  0xA8,  0x1,  0x3C,  0xF };

float getTemperature(String label, DeviceAddress deviceAddress){
  sensors.requestTemperatures();
  return sensors.getTempC(deviceAddress);
}

void OneWireScanner(){
  byte i, type_s, data[12], addr[8];

  Serial.println("Scanning devices");
  
  if (!oneWire.search(addr)) {
    Serial.println("No more addresses.");
    Serial.println();
    oneWire.reset_search();
    return;
  }
  
  Serial.print("ROM = ");
  for( i = 0; i < 8; i++) {
    Serial.write(' ');
    Serial.print("0x");
    Serial.print(addr[i], HEX);
    if ( i != 7 ) {
      Serial.print(", ");
    }
  }
  
  if (OneWire::crc8(addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return;
  }
  Serial.println();
  // the first ROM byte indicates which chip
  switch (addr[0]) {
    case 0x10:
      Serial.println("  Chip = DS18S20");  // or old DS1820
      type_s = 1;
      break;
    case 0x28:
      Serial.println("  Chip = DS18B20");
      type_s = 0;
      break;
    case 0x22:
      Serial.println("  Chip = DS1822");
      type_s = 0;
      break;
    default:
      Serial.println("Device is not a DS18x20 family device.");
      return;
  } 
}

void setupThermometer() {
  OneWireScanner();
  
  sensors.begin();

  Serial.print("Locating devices...");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");

  // report parasite power requirements
  Serial.print("Parasite power is: "); 
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");

  // check and report if sensors are conneted 
  if (!sensors.getAddress(thermometer, 0)) Serial.println("Unable to find address for Device 0"); 

  // set the resolution to 9 bit per device
  sensors.setResolution(thermometer, TEMPERATURE_PRECISION);

  // Check that ensor is correctly configured
  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(thermometer), DEC); 
  Serial.println(); 
}
