#include <Arduino.h>
#include "Wire.h"
#include "Adafruit_TCS34725.h"
#include "Ultrasonico.h"  
#include "movements.h"
#include "motor.h"
#include "ultrasonico.h"
#include "correctioncentrado.h"
#include "backtracking.h"
#include "sensorColor.h"

// -------------------- Color sensor --------------------
sensorColor color(36, 37, 39, 38, 40);

// -------------------- Robot --------------------
Movements robot;
UltraSonico sensorFrente(25, 24);   // Trigger, Echo - Frente
UltraSonico sensorIzquierda(23, 22); // Trigger, Echo - Izquierda
UltraSonico sensorDerecha(27, 26);  // Trigger, Echo - Derecha

float distanceFrente;
float distanceIzquierda;
float distanceDerecha;

//IR
const int detector=47;
CorrectionCentrado correction;
// Cambiar booleans para porbar cosas
bool pruebaMotores = false;
bool pruebaUltrasonico = false;
bool pruebaColor = true;
bool pruebaConjunta = false;

BackTracking laberintoSolver(sensorIzquierda, sensorDerecha, sensorFrente, robot);
void setup() {
  //IR
  pinMode(detector, INPUT);
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

  laberintoSolver.solver(5, 1, 0); //comienza a resolver el laberinto desde la casilla (5,0) mirando hacia el norte (direccion 0)
  robot.retroceder(100);
  delay(2000);
  robot.neutro();
  delay(3000);

  
  if(pruebaMotores) {
    Serial.println("PRUEBA MOTORES");
    correction.centrarYAvanzarCasilla(robot, sensorIzquierda, sensorDerecha, sensorFrente);
    delay(10000);
    robot.neutro();
    delay(3000);
    /*
    robot.derecha(100);
    delay(6700);
    robot.neutro();
    delay(3000);
  Serial.println("PRUEBA MOTORES");
  correction.centrarYAvanzarCasilla(robot, sensorIzquierda, sensorDerecha, sensorFrente);
  delay(10000);
  robot.neutro();
  delay(3000);
  robot.derecha(100);
  delay(6700);
  robot.neutro();
  delay(3000);
    */
  }/*
   if(pruebaColor){
   
  Serial.print("Red PW = ");
	Serial.print(redPW);
	Serial.print(" - Green PW = ");
	Serial.print(greenPW);
	Serial.print(" - Blue PW = ");
	Serial.println(bluePW);
  analogWrite(redPin, redPW);
  analogWrite(greenPin, greenPW);
  analogWrite(bluePin, bluePW);
   }
   */
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

    delay(300);
    /*
    if (distanceFrente < 22.0f && distanceDerecha > 12.0f) {
    robot.derecha(100);
    delay(3350);
  }
  else if (distanceFrente < 22.0f && distanceIzquierda > 12.0f) {
    robot.izquierda(100);
    delay(3350);
  }
  else if (distanceFrente < 22.0f && distanceIzquierda < 12.0f && distanceDerecha < 12.0f) {
    robot.derecha(100);
    delay(6700);
    robot.neutro();
    delay(250);
  }
  
    robot.avanzar(100);
    delay(3000);
  */
  delay(100);
  }
  
  //Infrarrojo
  int valueIR = 0;
  valueIR = digitalRead(detector);
  if(valueIR == HIGH){ //checa si hay obstaaculo
    Serial.println("Detectado obstaculo");//cambiar a un boolean
  
  }
}
