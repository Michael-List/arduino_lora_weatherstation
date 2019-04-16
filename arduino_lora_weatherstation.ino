#include <SPI.h> // For lora
#include <LoRa.h> // For lora
#include "seeed_bme680.h" // Humidity, temperature and pressure sensor

#define IIC_ADDR uint8_t(0x76) // Address of BME680 sensor
Seeed_BME680 bme680(IIC_ADDR); // IIC PROTOCOL

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
  LoRa.endPacket();

  delay(5000);
}
