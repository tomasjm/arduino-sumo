# Arduino-sumo

Proyecto de Arduino-sumo para la universidad.

Componentes utilizados:

- Arduino UNO
- 4 Servomotores
- Puente H
- Seguidor de linea
- Receptor infrarrojo
- Sensor ultrasonico
- Leds
- Conexión a baterias

Cuenta con las siguientes funciones:

- Detección de salida de plataforma (Detecta superficie negra)
- Detección de obstaculos o vehiculos para ir a chocar
- Automatización de acciones para evitar la salida de la rampa
- Estructurado en funciones/componentes para facilidad de uso.

## Comenzando

Estas instrucciones te guiarán para poder utilizar el código con éxito.

### Pre-requisitos

Necesitarás tener conocimiento básico de electrónica, C++ y arduino, como lo son los conocimientos de los sensores, motores y sus conexiones.

### Configuración de proyecto

El código está debidamente comentado, en caso de que no lo entiendan, seguir esto.

```
#include <NECIRrcv.h>
#define IRPIN 11

NECIRrcv ir(IRPIN);
```

Este fragmento importa la libreria que se utilizará para captar los mensajes infrarrojos de un control remoto.

Ahora, los pines

```
byte ENA = 5;
byte ENB = 6;

byte IN1 = 7;
byte IN2 = 8;
byte IN3 = 9;
byte IN4 = 10;

byte PIN_SL = A2;
```

ENA y ENB corresponden a los pines de potencia del puente H.

INX corresponden a los pines que controlan el giro de las ruedas.

PIN_SL corresponde al pin del seguidor de linea.

## Testear el código

Una vez configurado correctamente los pines y haber realizado las conexiones, podrás subir el código a la placa.
Tu auto sumo deberá avanzar, detectar superficies negras, girar y volver a avanzar, sin traspasar aquella superficie.

## Modificando el código

### Variables a destacar

Hay 3 variables globales:

- Valor del seguidor de linea
- Booleano de SUPERFICIE_NEGRA
- Booleano de PRENDIDO

Cada uno representa lo que su nombre indica.

### Setup()

Es requisito previo entender que se hizo en el setup.

### Loop()

Al final del código están todas las funciones que hacen funcionar el programa. El loop se intentará dejar lo más limpio posible.

```
void loop()
{
  unsigned long ircode;

  while (ir.available())
  {
    ircode = ir.read();
    Serial.println(ircode, HEX);
  }
  ComprobarEstado();
  while (PRENDIDO = true)
  {
    Superficie();
    if (SUPERFICIE_NEGRA)
    {
      Derecha(1000, 255);
      Avanzar(0, 255);
    }
    else
    {
      Avanzar(0, 255);
    }
    ComprobarEstado();
  }
}
```

Ahora mismo, el loop asigna la variable ircode, y mientras el receptor infrarrojo esté activo, asignara el valor recibido a la variable ircode.
Se llamará luego a la función ComprobarEstado(), la cual lee el código de Ircode recibido desde el control remoto para determinar si se prende o no el auto.
Si es que la variable PRENDIDO = true, se ejecutará el while que funcionará mientras el auto esté prendido.
Llamará a la función Superficie() que comprueba mediante los valores recibidos del seguidor de linea si es que la superficie es negra o blanca.
Si SUPERFICIE_NEGRA = true, girará y luego avanzará.
A continuación se explicarán las funciones.

### Funciones generales

Tenemos las siguientes funciones:

#### Avanzar()

```
Give an example
```

## Creado con

- [Arduino](https://www.arduino.cc/) - Microcontrolador electronico

## Authors

- **Tomás Jiménez** - [tomasjm](https://github.com/tomasjm)

## Licencia

Proyecto de codigo abierto, uso libre
