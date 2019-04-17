# Arduino weatherstation with lora data transmission

# Used sensors
* [Groove temperature, humidity, pressure and gas sensor (BME680) from Seeedstudio](http://wiki.seeedstudio.com/Grove-Temperature_Humidity_Pressure_Gas_Sensor_BME680/)
* [Groove sunlight sensor (SI1145) from Seeedstudio](http://wiki.seeedstudio.com/Grove-Sunlight_Sensor/)
* [Groove analog Moisture sensor from Seeedstudio](http://wiki.seeedstudio.com/Grove-Moisture_Sensor/)

# Used libraries
* https://github.com/Seeed-Studio/Seeed_BME680
* https://github.com/SeeedDocument/Grove-Sunlight_Sensor/

# Send data format
Example: 01;21.16;954.98;46.88;260;256;0.00;7;  
The ; is a divider between the different values.  
The values are in this order:
* Station number
* Temperature in celsius
* Pressure in hectopascal
* Humidity in %
* Visible light in lumen
* Infrared light in lumen
* Ultraviolet light in lumen
* Analog moisture sensor
