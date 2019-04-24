#include <SPI.h> // For lora
#include <LoRa.h> // For lora
#include "seeed_bme680.h" // Humidity, temperature and pressure sensor
#include <Wire.h> // For sunlight sensor
#include "SI114X.h" // For sunlight sensor

#define IIC_ADDR uint8_t(0x76) // Address of BME680 sensor
Seeed_BME680 bme680(IIC_ADDR); // IIC PROTOCOL
SI114X SI1145 = SI114X(); // Sunlight sensor
static int sensorPin = A0; // Moisture sensor
static int frequency = 868300000; // For the frequency you are allowed to use in your country look at: https://www.thethingsnetwork.org/docs/lorawan/frequency-plans.html

// Sensor data
float temperature;
float pressure;
float humidity;
float visibleLight;
float irLight;
float uvLight;
int moisture;

// Other vars
static int SENDXTIMES = 3;
static int SLEEPTIME = 5000; // Sleeptime in ms
static char STATIONID[] = "01";

void setup() {
// For debugging
//  Serial.begin(9600);
//  while (!Serial);

  while (!LoRa.begin(frequency)) {
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
  // Collect sensor data
  if (bme680.read_sensor_data()) {
//  Failed to perform reading
    return;
  }

  temperature = bme680.sensor_result_value.temperature; // In C
  pressure = bme680.sensor_result_value.pressure / 100; // In hpa
  humidity = bme680.sensor_result_value.humidity; // In %
  visibleLight = SI1145.ReadVisible(); // Visible light in lm (lumen)
  irLight = SI1145.ReadIR(); // Infrared light in lm
  uvLight = (float)SI1145.ReadUV() / 100; // Ultraviolet light in lm
  moisture = analogRead(sensorPin); // Analog moisture sensor. Values between 0 - 1023

  // send packet x times
  for (int c = 0; c < SENDXTIMES; c++) {
    LoRa.beginPacket();
    LoRa.print(STATIONID);
    LoRa.print(";");
    LoRa.print(temperature);
    LoRa.print(";");
    LoRa.print(pressure);
    LoRa.print(";");
    LoRa.print(humidity);
    LoRa.print(";");
    LoRa.print(visibleLight);
    LoRa.print(";");
    LoRa.print(irLight);
    LoRa.print(";");
    LoRa.print(uvLight);
    LoRa.print(";");
    LoRa.print(moisture);
    LoRa.print(";");
    LoRa.endPacket();

    delay(200);
  }

  delay(SLEEPTIME);
}
