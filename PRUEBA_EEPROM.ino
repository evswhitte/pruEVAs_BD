#include <I2C_eeprom.h>
#include "Wire.h"

// This down there se copia como está
I2C_eeprom ee(0x50, I2C_DEVICESIZE_24LC256);

typedef struct {
  char nombreComida[14];
  uint8_t cantidad;
} datoComida;

/*
struct
{
  float temperature;
  float humidity;
  float pressure;
} measurement;
*/

void setup() {
  Serial.begin(115200);  // Inicializacion puerto serie :D
  Wire.begin();          // Inicializacion i2c
  ee.begin();            // Inicialización del "manejador" de la memoria

  ee.setBlock(0, 0, sizeof(datoComida));                        // Limpia un bloque de memoria de tamaño (measuremenet) [bytes],
  ee.readBlock(0, (uint8_t *)&datoComida, sizeof(datoComida));  // Escribo la información EEPROM -> RAM

  Serial.println("Información después de limpiar la memoria EEPROM: ");
  Serial.print("nom:\t");
  Serial.println(datoComida.nombreComida);
  Serial.print("cant:\t");
  Serial.println(datoComida.cantidad);

  datoComida.nombreComida = "manzana verde";
  datoComida.cantidad = 5;

  ee.writeBlock(0, (uint8_t *)&datoComida, sizeof(datoComida));  // Escribo la información RAM -> EEPROM
  ee.readBlock(0, (uint8_t *)&datoComida, sizeof(datoComida));   // Leo la información EEPROM -> RAM

  Serial.println("Información después de escribir la memoria EEPROM: ");
  Serial.print("nom:\t");
  Serial.println(datoComida.nombreComida);
  Serial.print("cant:\t");
  Serial.println(datoComida.cantidad);
}

void loop() {
  // put your main code here, to run repeatedly:
}