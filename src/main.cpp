#include <Arduino.h>
#include "Wire.h"
#include "Adafruit_TCS34725.h"
#include "Ultrasonico.h"  
#include "movements.h"

  //color Sensor set
  #define redpin 3
  #define greenpin 5
  #define bluepin 6
  #define commonAnode true
  byte gammatable[256];
  Adafruit_TCS34725 tcs= Adafruit_TCS34725(
    TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

  //pins se definen despues
  //Car iniciar 4 motores, pines puestos en 0, se cambia en setup()
Movements movements;

  //Sensor Ultrasonico, primer pin es el trigger y el segundo es el echo
  UltraSonico sensorFrente(38, 39);//Frente
  UltraSonico sensorIzquierda(36, 37);//Izquierda
  UltraSonico sensorDerecha(40, 41);//Derecha

  //variables
  //int speed;
//int t;??? dos tiempos??
double distanceFrente;
double distanceIzquierda;
double distanceDerecha;
int detector= 4; //IR sensor
bool PelotaenPosesion = false;
bool bloqueofrontal = false;
bool bloqueolateralizq = false;
bool bloqueolateralder = false;
bool valueIR = LOW;

int STAGE = 1; //Etapa del circuito

void setup() {
  //Motores poner los pines de cada motor
  //primer pin es ENA, segundo es In1 y tercero es In2
  movements.motorFrontLeft(9, 22, 23); //Left Front Motor
  movements.motorFrontRight(10, 26, 27); //Right Front Motor
  movements.motorBackLeft(11, 30, 31); //Left Back Motor
  movements.motorBackRight(12, 34, 35); //Right Back Motor

//Especificar que son cada pin de todos los motores (Output, etc)
  movements.begin();

  //empieza comunicacion serial
  Serial.begin(9600);

  //Ultrasonicos modo de pines
  sensorFrente.begin();
  sensorIzquierda.begin();
  sensorDerecha.begin();

   //infrarrojo (IR)
  pinMode(detector, INPUT);

  //color
  if(tcs.begin()){ //checar si se conecto correctamente
  }else{
    Serial.println(
      "No TCS34725 found ... check your conections");
      while(1);
  }
  pinMode(redpin, OUTPUT);//declarar los pines como output
  pinMode(bluepin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  for(int i=0; i<256; i++){ //ajustar intensidad LED's para ver lso cambios de brillo mejor (ni idea como funciona pero meh)
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x*=255;
    if(commonAnode){
      gammatable[i]= 255 - x;
    } else{
      gammatable[i] = x;
    }
  }
  movements.avanzar(100); // Avanza al inicio para no confundirse 
  delay(1000);
}


void loop() {
//                       ULTRASÓNICOS | DETECCIÓN DE OBSTÁCULOS (PAREDES)
  if(STAGE == 1){ //           ETAPA 1 CIRCUITO B
    distanceFrente = sensorFrente.getDistance();
    distanceIzquierda = sensorIzquierda.getDistance();
    distanceDerecha = sensorDerecha.getDistance();


    if(distanceFrente<=5){ //Si hay 5 cm o menos
    bloqueofrontal = true;
    }
    if(distanceIzquierda<=5){ //Si hay 5 cm o menos
    bloqueolateralizq = true;
    }
    if(distanceDerecha<=5){ //Si hay 5 cm o menos
    bloqueolateralder = true;
    }

    if(bloqueofrontal == false && bloqueolateralizq == false && PelotaenPosesion == true){
      movements.avanzar(25);
      delay(500);
      Serial.println("Salida encontrada! :D");
      movements.freno();
      delay(200);
      movements.neutro();
      movements.izquierda(100);
      delay(500);
      movements.freno();
      movements.avanzar(50);
      delay(500);
      movements.neutro();
      STAGE = 2; //Cambio de etapa
    }

    if(bloqueolateralder == false && bloqueofrontal == false && PelotaenPosesion == false){
      movements.avanzar(25);
      delay(250);
      Serial.println("Camino derecho detectado. Posible pelota!");
      movements.freno();
      delay(200);
      movements.neutro();
      movements.derecha(100);
      delay(500);
      movements.freno();
      delay(200);
      movements.neutro();
      movements.avanzar(50);
      delay(500);
      movements.neutro();
    }

    if(bloqueofrontal == true && bloqueolateralizq == true && bloqueolateralder == true PelotaenPosesion == false){
      Serial.println("Pelota encontrada!");
      movements.avanzar(50);
      delay(500);
      movements.neutro();
      //GARRA ON                                             <<<<=========
      PelotaenPosesion = true;
      movements.retroceder(50);
      delay(1000);
      movements.neutro();
      movements.derecha(50);
      delay(500);
      movements.neutro();
    }

    if(bloqueofrontal == true){
      Serial.println("Obstaculo físico detectado");
      movements.freno();
      delay(200);
      movements.neutro();
      movements.derecha(75);
      delay(500);
      movements.avanzar(100);
      delay(200);
      movements.neutro();
    }
    else {
      movements.avanzar(100);
    }
  }
  else if(PelotaenPosesion){ //           ETAPA 2 CIRCUITO B
    movements.avanzar(100);
  }
  

  //Infrarrojo
  valueIR = digitalRead(detector);
  if(valueIR == HIGH){ //checa si hay obstaaculo
    Serial.println("Barrera infraroja detectada");//cambiar a un boolean
  }

  //////////////                                 COLORES
  float red, green, blue;
  tcs.getRGB(&red, &green, &blue);
  tcs.setInterrupt(true);
  ///* para checar que valores lee (quitar primeras 2  lineas para comentar todo)
  Serial.print("R:\t"); Serial.print(int(red));
  Serial.print("\tG:\t"); Serial.print(int(green));
  Serial.print("\tB:\t"); Serial.print(int(blue));
  Serial.print("\n");
  //*/
  analogWrite(redpin, gammatable[(int)red]);
  analogWrite(greenpin, gammatable[(int)green]);
  analogWrite(bluepin, gammatable[(int)blue]);
  


  

  //Ultrasonic medir distancia
  distanceFrente = sensorFrente.getDistance();
  distanceIzquierda = sensorIzquierda.getDistance();  
  distanceDerecha = sensorDerecha.getDistance();

}
