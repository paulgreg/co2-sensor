# esp8266 CO2 sensor

That project goad is to mesure CO2 and so, tell user to open their window if too high. It’s a simple way to remind to recycle air in order to fight against COVID19. Inspiration is from [Eole project](lafabrique.centralesupelec.fr/projetco2/)

## Components
 
 * esp8266
 * I2C 128X64 OLED LCD screen
 * Digital Thermometer Dallas TO-92 DS18B20
 * SGP30 Air Quality Sensor CO2 sensor


## Connections

### I2C screen

 * GND on GND
 * VCC on 3.3V
 * SCL on esp8266 D1
 * SDA on esp8266 D2

### Dallas TO-92 DS18B20

 * GND on GND
 * VCC on 5V
 * DQ to esp8266 D5 but a 4.7K resistor is necessary between +5V and Data wire as [explained here](https://projetsdiy.fr/mesure-temperature-dallas-ds18b20-code-arduino-compatible-esp8266-esp32-domoticz-http/)


## Components references

  * [I2C OLED screen](https://randomnerdtutorials.com/esp8266-0-96-inch-oled-display-with-arduino-ide/)
  * [Mesure de température DS18B20](https://projetsdiy.fr/mesure-temperature-dallas-ds18b20-code-arduino-compatible-esp8266-esp32-domoticz-http/)
  * [esp8266 pinout reference](https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/)
