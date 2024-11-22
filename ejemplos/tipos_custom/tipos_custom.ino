#include "string.h"

typedef struct {
    char nombre[15];
    uint8_t edad;
} persona;

void setup() {
    Serial.begin(115200);

    /* 
    Ejemplo usando instancias individuales
     - not what we need pero sirve para entender
    */

    persona persona1;
    persona persona2;

    strcpy((char*)&persona1.nombre,"Rigoberto");
    persona1.edad = 53;
    strcpy((char*)&persona2.nombre,"Eustaquio");
    persona2.edad = 55;

    Serial.print("nombre de persona1: ");
    Serial.println(persona1.nombre);
    Serial.print("edad de persona1: ");
    Serial.println(persona1.edad);

    Serial.print("nombre de persona2: ");
    Serial.println(persona2.nombre);
    Serial.print("edad de persona2: ");
    Serial.println(persona2.edad);


    Serial.println("--- ejemplos de lista abajo ---");
    /*
    Ejemplo usando una lista de "persona"
     - acá voy a reemplazar el uso de instancias por el nombre de la lista y el indice
    */

    persona personas[10];

    strcpy((char*)&(personas[0].nombre),"Florentino");
    strcpy((char*)&(personas[1].nombre),"Hermenegildo");
    strcpy((char*)&(personas[2].nombre),"Ceferino");
    strcpy((char*)&(personas[3].nombre),"Crisóstomo");
    strcpy((char*)&(personas[4].nombre),"Gumersindo");
    strcpy((char*)&(personas[5].nombre),"Melquíades");
    strcpy((char*)&(personas[6].nombre),"Procopio");
    //faltan crear 3... quedaba muy largo

    personas[0].edad = 7;
    personas[1].edad = 33;
    personas[2].edad = 90;
    personas[3].edad = 107;
    personas[4].edad = 63;
    personas[5].edad = 42;
    personas[6].edad = 25;
    //acá también debería agregar los 3 que faltan

    //ahora, para ver la información de cada uno puedo usar un for :D
    for(int num_pers = 0; num_pers < 7; num_pers++) {
        Serial.print("persona numero: ");
        Serial.println(num_pers);
        Serial.print("nombre: ");
        Serial.println(personas[num_pers].nombre);
        Serial.print("edad: ");
        Serial.println(personas[num_pers].edad);
    }

}

void loop() {

}