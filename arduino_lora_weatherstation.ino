#include <SPI.h> // For lora
#include <LoRa.h> // For lora
#include "seeed_bme680.h" // Humidity, temperature and pressure sensor
#include <Wire.h> // For sunlight sensor
#include "SI114X.h" // For sunlight sensor

#define IIC_ADDR uint8_t(0x76) // Address of BME680 sensor
Seeed_BME680 bme680(IIC_ADDR); // IIC PROTOCOL
SI114X SI1145 = SI114X(); // Sunlight sensor
static int frequency = 868300000; // For the frequency you are allowed to use in your country look at: https://www.thethingsnetwork.org/docs/lorawan/frequency-plans.html

// Sensor data
float temperature;
float pressure;
float humidity;
float visibleLight;
float irLight;
float uvLight;

// Other vars
static int SENDXTIMES = 3;
static int SLEEPTIME = 900000; // Sleeptime in ms
static bool SLEEPMODEON = false; // Turn "sleepmode" on which is just a delay
static int POWEROFFPIN = 0; // Adafruit TPL5110 mode pin
static char STATIONID[] = "01";
String loraData;

void setup() {
  digitalWrite(POWEROFFPIN, LOW);
  
// For debugging
//  Serial.begin(9600);
//  while (!Serial);

  LoRa.setTxPower(17);
  LoRa.setSpreadingFactor(8);
  LoRa.setCodingRate4(5);
  LoRa.enableCrc();

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

  // Build lora data package
  loraData = STATIONID;
  loraData += ";";
  loraData += temperature;
  loraData += ";";
  loraData += pressure;
  loraData += ";";
  loraData += humidity;
  loraData += ";";
  loraData += visibleLight;
  loraData += ";";
  loraData += irLight;
  loraData += ";";
  loraData += uvLight;
  loraData += ";;";

  // send packet x times
  for (int c = 0; c < SENDXTIMES; c++) {
    LoRa.beginPacket();
    LoRa.print(loraData);
    LoRa.endPacket();

    delay(200);
  }

  if (SLEEPMODEON) {
    delay(SLEEPTIME);
  }
  else {
    digitalWrite(POWEROFFPIN, HIGH);
  }
}
