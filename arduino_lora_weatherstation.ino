#include <SPI.h> // For lora
#include <LoRa.h> // For lora
#include "seeed_bme680.h" // Humidity, temperature and pressure sensor
#include <Wire.h> // For sunlight sensor
#include "SI114X.h" // For sunlight sensor

#define IIC_ADDR uint8_t(0x76) // Address of BME680 sensor
Seeed_BME680 bme680(IIC_ADDR); // IIC PROTOCOL
SI114X SI1145 = SI114X(); // Sunlight sensor
int sensorPin = A0; // Moisture sensor

void setup() {
// For debugging
//  Serial.begin(9600);
//  while (!Serial);

  while (!LoRa.begin(868300000)) {
//  If init failed, wait and try again
    delay(10000);
  }

  while (!bme680.init()) {
//  If init failed, wait and try again
    delay(10000);
  }

  while (!SI1145.Begin()) {
//  If init failed, wait and try again
    delay(10000);
  }
}

void loop() {
  if (bme680.read_sensor_data()) {
//  Failed to perform reading
    return;
  }

  // send packet
  LoRa.beginPacket();
  LoRa.print("01;");
  LoRa.print(bme680.sensor_result_value.temperature); // In C
  LoRa.print(";");
  LoRa.print(bme680.sensor_result_value.pressure / 100); // In hpa
  LoRa.print(";");
  LoRa.print(bme680.sensor_result_value.humidity); // In %
  LoRa.print(";");
  LoRa.print(SI1145.ReadVisible()); // Visible light in lm (lumen)
  LoRa.print(";");
  LoRa.print(SI1145.ReadIR()); // Infrared light in lm
  LoRa.print(";");
  LoRa.print((float)SI1145.ReadUV()/100); // Ultraviolet light in lm
  LoRa.print(";");
  LoRa.print(analogRead(sensorPin)); // Analog moisture sensor. Values between 0 - 1023
  LoRa.print(";");
  LoRa.endPacket();

  delay(5000);
}
