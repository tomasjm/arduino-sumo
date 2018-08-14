/*
  Programa de control de motores
  KIT AUTO: N°09
  Version IDE: Arduino 1.6.11
  Autor: Tomas Jimenez
  Fecha: 07/08/2018
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
byte PIN_SL = A0;

//// Pines de sensor ultrasonico

byte pinEcho = 12;
byte pinTrigger = 13;

// VALORES
//// Valor seguidor de linea
int VALOR_SL;
bool SUPERFICIE_NEGRA;
bool PRENDIDO;


unsigned long ircode;
//// Valores sensor ultrasonico
unsigned int val_tiempo, val_distancia;

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
  // Pines sensor ultrasonico
  pinMode(pinEcho, INPUT);
  pinMode(pinTrigger, OUTPUT);

  //Inicializar receptor de infrarrojo
  ir.begin();

  //Inicializar monitor serial
  Serial.begin(9600);
  Serial.println("monitor inicializado");
}

void loop()
{
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
  while (PRENDIDO)
  {
    Serial.println();
    Serial.println("Auto prendido");
    //REALIZA MIENTRAS ESTÁ PRENDIDO
    //COMPROBAR SI LA SUPERFICIE ES NEGRA O BLANCA
    //SUPERFICIE_NEGRA = TRUE :: FALSE
    Superficie();
    if (SUPERFICIE_NEGRA)
    {
      Retroceder(500, 255);
      Derecha(750, 200);
      Avanzar(250, 200);
    }
    else
    {
      // Se calculará la distancia en centrimetos
      CalcDistancia();
      if (val_distancia < 30)
      {
        Avanzar(0, 200);
      } else {
        Avanzar(0, 200);
      }
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
  while (ir.available())
  {
    // Si es que llega una señal infrarroja, guardará su valor en la variable "ircode"
    ircode = ir.read();
    Serial.println(ircode, HEX);
  }
  if (ircode == 0x6F905583)
  {
    digitalWrite(PIN_LED, HIGH);
    Serial.print("Auto encendido, LED ON");
    Serial.print(" || ");
    PRENDIDO = true;
  }
  else if (ircode == 0x77885583)
  {
    digitalWrite(PIN_LED, LOW);
    Serial.println("Auto apagado, LED OFF");
    PRENDIDO = false;
    Parar(0);
  }
}
//FUNCION COMPROBAR SUPERFICIA
void Superficie()
{
  // RANGOS
  // BLANCO 640 - 1017 NEGRO. 828 PROMEDIO
  VALOR_SL = analogRead(PIN_SL);
  if (VALOR_SL > 785)
  {
    SUPERFICIE_NEGRA = true;
  }
  else if (VALOR_SL < 785)
  {
    SUPERFICIE_NEGRA = false;
  }
  Serial.print("VALOR DE SUPERFICIE: ");
  Serial.print(VALOR_SL);
  Serial.print(" || ");
  Serial.print("SUPERFICIE NEGRA: ");
  Serial.print(SUPERFICIE_NEGRA);
  Serial.print(" || ");
}
// Funcion para calcular distancia de objetos
void CalcDistancia()
{
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(5);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);

  val_tiempo = pulseIn(pinEcho, HIGH);

  val_distancia = val_tiempo / 58;
  Serial.print("Detectado obstaculo a: ");
  Serial.print(val_distancia);
  Serial.print(" centimetros");
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
