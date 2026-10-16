#include <Arduino.h>
#include "Wire.h"
#include "Adafruit_TCS34725.h"
#include "Ultrasonico.h"  
#include "movements.h"
#include "motor.h"
#include "ultrasonico.h"

// -------------------- Color sensor --------------------
#define redpin 3
#define greenpin 5
#define bluepin 6
#define commonAnode true

byte gammatable[256];
Adafruit_TCS34725 tcs = Adafruit_TCS34725(
    TCS34725_INTEGRATIONTIME_50MS,
    TCS34725_GAIN_4X);

// -------------------- Robot --------------------
Movements robot;
UltraSonico sensorFrente(25, 24);   // Trigger, Echo - Frente
UltraSonico sensorIzquierda(23, 22); // Trigger, Echo - Izquierda
UltraSonico sensorDerecha(27, 26);  // Trigger, Echo - Derecha

float distanceFrente;
float distanceIzquierda;
float distanceDerecha;

// Cambiar booleans para porbar cosas
bool pruebaMotores = true;
bool pruebaUltrasonico = false;
bool pruebaColor = false;
bool pruebaConjunta = false;

void setup() {
  //Motores poner los pines de cada motor
  //primer pin es ENA, segundo es In1 y tercero es In2
  robot.motorBackLeft(9, 29, 31);
  robot.motorFrontLeft(8, 28, 30);
  robot.motorBackRight(10, 32, 34);
  robot.motorFrontRight(11, 33, 35);

//Especificar que son cada pin de todos los motores (Output, etc)
  robot.begin();

  //empieza comunicacion serial
  Serial.begin(9600);

  //Ultrasonicos modo de pines
  sensorFrente.begin();
  sensorIzquierda.begin();
  sensorDerecha.begin();
/*
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
    */
}


void loop() {
  Serial.println("PRUEBA MOTORES");
    robot.derecha(100);
    delay(3000);
    robot.neutro();
    delay(3000);
  if (pruebaUltrasonico) {
    distanceFrente = sensorFrente.getDistance();
    distanceIzquierda = sensorIzquierda.getDistance();
    distanceDerecha = sensorDerecha.getDistance();

    Serial.print("FR:");
    Serial.print(distanceFrente);
    Serial.print("cm  IZ:");
    Serial.print(distanceIzquierda);
    Serial.print("cm  DE:");
    Serial.print(distanceDerecha);
    Serial.println("cm");

    delay(500);
  }
  /*
  //Infrarrojo
  int valueIR = 0;
  valueIR = digitalRead(detector);
  if(valueIR == HIGH){ //checa si hay obstaaculo
    Serial.println("Detectado obstaculo");//cambiar a un boolean
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
  //
  analogWrite(redpin, gammatable[(int)red]);
  analogWrite(greenpin, gammatable[(int)green]);
  analogWrite(bluepin, gammatable[(int)blue]);
  

  if(distanceFrente<=5){ //Si hay 5 cm o menos
    bool bloqueo = true;
  }

  if(bloqueo == true){
    Serial.println("Obstaculo detectado");
    movements.freno();
    delay(1000);
    movements.neutro();
  }
  else{
    movements.avanzar(100);
  }

  //Ultrasonic medir distancia
  distanceFrente = sensorFrente.getDistance();
  distanceIzquierda = sensorIzquierda.getDistance();  
  distanceDerecha = sensorDerecha.getDistance();

  if(distanceFrente<=5){ //Si hay 5 cm
    bool bloqueo = true;
  }*/
}
