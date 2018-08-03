/*
  Programa de control de motores
  KIT AUTO: N°09
  Version IDE: Arduino 1.6.11
  Autor: Tomas Jimenez
  Fecha: 24/07/2018
*/

#include <NECIRrcv.h>
#define IRPIN 11

NECIRrcv ir(IRPIN);

byte PIN_LED = 3;

// Configuracion de pines de motores
//// Pines velocidad
byte ENA = 5;
byte ENB = 6;
//// Pines control de giro
byte IN1 = 7;
byte IN2 = 8;
byte IN3 = 9;
byte IN4 = 10;

//// Pin seguidor de linea
byte PIN_SL = A2;

// VALORES
//// Valor seguidor de linea
int VALOR_SL;
bool SUPERFICIE_NEGRA;
bool PRENDIDO;

void setup()
{
  // Pines de velocidad
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  // Pines control de giro
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  // Pin de led
  pinMode(PIN_LED, OUTPUT);

  //Inicializar receptor de infrarrojo
  ir.begin();

  //Inicializar monitor serial
  Serial.begin(9600);
  Serial.println("monitor inicializado");
}

void loop()
{
  unsigned long ircode;

  // Comprueba la señal infrarrojo
  while (ir.available())
  {
    // Si es que llega una señal infrarroja, guardará su valor en la variable "ircode"
    ircode = ir.read();
    Serial.println(ircode, HEX);
  }
  // FUNCION COMPROBAR ESTADO, DEVUELVE PRENDIDO O APAGADO, SI ESTÁ PRENDIDO ENTONCES:: PRENDIDO = true
  ComprobarEstado();
  // ENTRA AL WHILE SOLO SI ES QUE PRENDIDO = TRUE
  while (PRENDIDO = true)
  {
    //REALIZA MIENTRAS ESTÁ PRENDIDO
    //COMPROBAR SI LA SUPERFICIE ES NEGRA O BLANCA
    //SUPERFICIE_NEGRA = TRUE :: FALSE
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
    /*SI COMPROBAR ESTADO DEVUELVE FALSE, ESTE SALDRÁ DEL WHILE*/
    ComprobarEstado();
  } // FIN DEL WHILE
}
// FIN DEL LOOP

/*-------------- FUNCIONES --------*/

//FUNCION PARA COMPROBAR SI ESTÁ PRENDIDO O APAGADO
// DEVUELVE TRUE O FALSE
void ComprobarEstado()
{
  if (ircode == 0x6F905583)
  {
    digitalWrite(PIN_LED, HIGH);
    Serial.println("led on");
    PRENDIDO = true;
  }
  else if (ircode == 0x77885583)
  {
    digitalWrite(PIN_LED, LOW);
    Serial.println("led off");
    PRENDIDO = false;
    Parar();
  }
}
//FUNCION COMPROBAR SUPERFICIA
void Superficie()
{
  // RANGOS
  // BLANCO 640 - 1017 NEGRO. 828 PROMEDIO
  VALOR_SL = analogRead(PIN_SL);
  if (VALOR_SL > 828)
  {
    SUPERFICIE_NEGRA = true;
  }
  else if (VALOR_SL < 828)
  {
    SUPERFICIE_NEGRA = false;
  }
  Serial.println(VALOR_SL);
  Serial.print("SUPERFICIA NEGRA ");
  Serial.println(SUPERFICIE_NEGRA);
}
//FUNCIONES DE ACCION DE MOTORES
//TIEMPO EN MILESIMAS DEL DELAY, Y VELOCIDAD CON RANGOS DE 0-255, USAR 185-255 PARA MINIMIZAR ERRORES DE ENERGIA
void Avanzar(int tiempo, int velocidad)
{
  // CASOS
  // 6 señales
  //// 2 velocidad
  analogWrite(ENA, velocidad); //0 - 255
  analogWrite(ENB, velocidad);
  //// 4 giro
  //// Motor derecho
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  //// Motor izquierdo
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(tiempo);
}
void Parar(int tiempo)
{
  // CASOS
  // 6 señales
  //// 2 velocidad
  analogWrite(ENA, 0); //0 - 255
  analogWrite(ENB, 0);
  //// 4 giro
  //// Motor derecho
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  //// Motor izquierdo
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(tiempo);
}
void Retroceder(int tiempo, int velocidad)
{
  // CASOS
  // 6 señales
  //// 2 velocidad
  analogWrite(ENA, velocidad); //0 - 255
  analogWrite(ENB, velocidad);
  //// 4 giro
  //// Motor derecho
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //// Motor izquierdo
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(tiempo);
}
void Derecha(int tiempo, int velocidad)
{
  // CASOS
  // 6 señales
  //// 2 velocidad
  analogWrite(ENA, velocidad); //0 - 255
  analogWrite(ENB, velocidad);
  //// 4 giro
  //// Motor derecho
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //// Motor izquierdo
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(tiempo);
}
void Izquierda(int tiempo, int velocidad)
{
  // CASOS
  // 6 señales
  //// 2 velocidad
  analogWrite(ENA, velocidad); //0 - 255
  analogWrite(ENB, velocidad);
  //// 4 giro
  //// Motor derecho
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  //// Motor izquierdo
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(tiempo);
}
