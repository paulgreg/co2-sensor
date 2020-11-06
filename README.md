# esp8266 CO2 sensor

That project goad is to mesure CO2 and so, tell user to open their window if too high. It’s a simple way to remind to recycle air in order to fight against COVID19. Inspiration is from [Eole project](http://lafabrique.centralesupelec.fr/projetco2/)

## Components

 * esp8266
 * I2C 128X64 OLED LCD screen
 * Humidity & temperature DHT11 sensor (needed as input to SGP30)
 * SGP30 Air Quality Sensor CO2 sensor

## Connections

### I2C screen

 * GND on GND
 * VCC on 3.3V
 * SCL on esp8266 D1
 * SDA on esp8266 D2

### SGP30 sensor

 * GND on GND
 * VCC on 3.3V
 * SCL on esp8266 D1
 * SDA on esp8266 D2

### DHT11 sensor

 * GND on GND
 * VCC on 3.3V
 * sensor to d5 / GPIO14

## Components references

  * [I2C OLED screen](https://randomnerdtutorials.com/esp8266-0-96-inch-oled-display-with-arduino-ide/)
  * [DHT11 sensor tryout](https://hackaday.io/project/175689/log/185783-humidity-temperature-module)
  * [Adafruit SGP30 sensor explanation](https://learn.adafruit.com/adafruit-sgp30-gas-tvoc-eco2-mox-sensor/arduino-code)
  * [esp8266 pinout reference](https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/)
