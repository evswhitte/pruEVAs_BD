#include <I2C_eeprom.h>
#include "Wire.h"

// This down there se copia como está
I2C_eeprom ee(0x50, I2C_DEVICESIZE_24LC256);

struct
{
  float temperature;
  float humidity;
  float pressure;
} measurement;

void setup() {
  Serial.begin(115200); // Inicializacion puerto serie :D
  Wire.begin();         // Inicializacion i2c 
  ee.begin();           // Inicialización del "manejador" de la memoria

  ee.setBlock(0, 0, sizeof(measurement)); // Limpia un bloque de memoria de tamaño (measuremenet) [bytes], 
  ee.readBlock(0, (uint8_t *) &measurement, sizeof(measurement)); // Escribo la información EEPROM -> RAM

  Serial.println("Información después de limpiar la memoria EEPROM: ");
  Serial.print("temp:\t");
  Serial.println(measurement.temperature);
  Serial.print("hum:\t");
  Serial.println(measurement.humidity);
  Serial.print("pres:\t");
  Serial.println(measurement.pressure);

  measurement.temperature = 22.5;
  measurement.humidity    = 53.1;
  measurement.pressure    = 1000.9;

  ee.writeBlock(0, (uint8_t *) &measurement, sizeof(measurement)); // Escribo la información RAM -> EEPROM
  ee.readBlock(0, (uint8_t *) &measurement, sizeof(measurement)); // Escribo la información EEPROM -> RAM

  Serial.println("Información después de escribir la memoria EEPROM: ");
  Serial.print("temp:\t");
  Serial.println(measurement.temperature);
  Serial.print("hum:\t");
  Serial.println(measurement.humidity);
  Serial.print("pres:\t");
  Serial.println(measurement.pressure);
}

void loop() {
  // put your main code here, to run repeatedly:

}
