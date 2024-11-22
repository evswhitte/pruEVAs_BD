# Memoria 💾

_esto habla específicamente del manejo de EEPROM, y en particular la EEPROM serie ```24LC256```_.

## Cuidado ⚠️

Las memorias EEPROM, por alguna cuestión electrónica que no viene al caso, tienen una cantidad de escrituras **limitada**. 😕

De aproximadamente *1.000.000* ciclos. 😎

Si dejamos una escritura corriendo en el void loop... un Arduino UNO puede ejecutar **16.000.000 instrucciones** en **1 segundo**!!! y un ESP32 **240.000.000**!!!! 😱😱😱

En ese caso, la memoria 🤯 **en poquitos segundos** (not quite literally, pero no se puede usar más).

Así que _cuidado_. Hay que asegurarse de que la memoria sólo se escriba cuando sea necesario, and we'll be fine.

## Ahora al código

First of all,

    #include <I2C_eeprom.h>

(tiene que estar instalado).

## pequeña pausa

Generalmente vamos a trasladar _piezas_ de información custom, más grandes que un dato de algún tipo estándar del lenguaje (int/char/etc). Un string cuenta como custom, un struct también. Para eso, nos vamos a manejar con _direcciones de memoria_ y _longitudes, en bytes_.

### Ctrl + C, Ctrl + V

* #### Dirección de memoria (aka puntero 🤙🏻)

      (byte *) &nombre_de_la_instancia_de_tipo_custom

* #### Longitud en bytes

      sizeof(nombre_de_la_instancia_de_tipo_custom)

    Esto **solo** funciona para datos de _longitud fija_!!! (ej: struct). Para strings, hay que usar strlen().

## AHORA SÍ, AL CÓDIGO...

### Inicialización

Esto va por fuera del ```void setup()```. No se pregunta, no se toca, _no nada_.

    I2C_eeprom ee(0x50, I2C_DEVICESIZE_24LC256);

Esto va en el ```void setup()```.

    Wire.begin();
    ee.begin();

### Acceso a memoria

* #### Borrado de un sector

      ee.setBlock(posicion, valor, cantidad_de_bytes);

    ```posicion```: número de byte de comienzo del sector.
    
    ```valor```: el valor que se va a copiar en cada byte.
    
    ```cantidad_de_bytes```: ...

* #### Escritura de un sector

      ee.writeBlock(posicion_de_eeprom, direccion_en_arduino, cantidad_de_bytes);
    
    ```posicion_de_eeprom```: importante - esto es un número (el número de byte en el que comenzar a escribir).

    ```direccion_en_arduino```: importante - esto **no** es un número. Es un _puntero_ (la tramoya que está más arriba. Just copy & paste).

    ```cantidad_de_bytes```: el amigo de antes.

* #### Lectura de un sector

      ee.readBlock(posicion_de_eeprom, direccion_en_arduino, cantidad_de_bytes);

    Los parámetros son los mismos que para ```writeBlock```.

    **Cuidado!** La ```direccion_en_arduino``` tiene que estar asociada a un dato _con el tamaño suficiente_ como para almacenar la cantidad de información que vamos a leer. Si no, empezamos a sobreescribir cosas que no deberíamos, y aparece el famoso _'se rompió todo'_ (formalmente 'memory leak').