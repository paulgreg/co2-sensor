#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#include <OneWire.h>
#include <DallasTemperature.h>
// A 4.7K resistor is necessary between +5V and Data wire  
#define PIN_ONEWIRE D5
OneWire oneWire(PIN_ONEWIRE); 
#define TEMPERATURE_PRECISION 10

DallasTemperature sensors(&oneWire);
DeviceAddress thermometer = { 0x28,  0xBD,  0xEA,  0x16,  0xA8,  0x1,  0x3C,  0xF };

void setup() {
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  // Show initial display buffer contents on the screen the library initializes this with an Adafruit splash screen.
  display.display();
  delay(1000);
  display.clearDisplay();
  
  OneWireScanner();
  sensors.begin();

  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");

  // report parasite power requirements
  Serial.print("Parasite power is: "); 
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");

  // Vérifie sir les capteurs sont connectés | check and report if sensors are conneted 
  if (!sensors.getAddress(thermometer, 0)) Serial.println("Unable to find address for Device 0"); 

  // set the resolution to 9 bit per device
  sensors.setResolution(thermometer, TEMPERATURE_PRECISION);

  // On vérifie que le capteur st correctement configuré | Check that ensor is correctly configured
  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(thermometer), DEC); 
  Serial.println();
  
}

void loop() {
  sensors.requestTemperatures();
  float temp = getTemperature("temp : ", thermometer);
  displayData(temp);
  delay(1000);
}

float getTemperature(String label, DeviceAddress deviceAddress){
  return sensors.getTempC(deviceAddress);
}
  

void displayData(float temp) {

  char s[10];
  sprintf(s, "Temp:\n%2.2f C", temp);
  
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println(s);
  display.display();
  delay(2000);
}

void OneWireScanner(){
  byte i;
  byte type_s;
  byte data[12];
  byte addr[8];

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
