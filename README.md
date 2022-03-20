# Arduino weather station with lora data transmission

# Used sensors/modules
* [Groove temperature, humidity, pressure and gas sensor (BME680) from Seeedstudio](http://wiki.seeedstudio.com/Grove-Temperature_Humidity_Pressure_Gas_Sensor_BME680/)
* [Groove sunlight sensor (SI1145) from Seeedstudio](http://wiki.seeedstudio.com/Grove-Sunlight_Sensor/)
* [Adafruit TPL5110 power timer](https://learn.adafruit.com/adafruit-tpl5110-power-timer-breakout/usage)

# Used libraries
* https://github.com/Seeed-Studio/Seeed_BME680
* https://github.com/SeeedDocument/Grove-Sunlight_Sensor/
* https://github.com/sandeepmistry/arduino-LoRa
  * NOTE: Requires firmware v1.1.6 or later on the on-board Murata module. Please use the MKRWANFWUpdate_standalone example from latest MKRWAN library release to update the firmware.
* https://github.com/arduino/ArduinoCore-samd (version 1.6.21)

# Lora information (Arduino)
* Lora TX power is set to 20
* LoRa SF (spreading factor) is set to 8
* LoRa bandwith is set to 125E3 Hz
* LoRa coding rate is set to 4/5
* Lora preamble length ist set to 8
* Lora sync word ist set to 0x34
* Frequency is set to 868300000 -> 868.3 MHz

# Lora information (Arduino)
Gateway is a Dragino OLG02 Outdoor Dual Channels LoRa IoT Gateway (https://www.dragino.com/products/lora-lorawan-gateway/item/136-olg02.html)

# Send data format
Example: <4567>01;21.16;954.98;46.88;260;256;0.00;;  
The ; is a divider between the different values.  
The values are in this order:
* Station number
* Temperature in celsius
* Pressure in hectopascal
* Humidity in %
* Visible light in lumen
* Infrared light in lumen
* Ultraviolet light in lumen