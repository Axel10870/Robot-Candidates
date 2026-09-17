#include <Arduino.h>
#include "Wire.h"
#include "Adafruit_TCS34725.h"
#include "Ultrasonico.h"  
#include "MotorControl.h"

  //color Sensor set
  #define redpin 3
  #define greenpin 5
  #define bluepin 6
  #define commonAnode true
  byte gammatable[256];
  Adafruit_TCS34725 tcs= Adafruit_TCS34725(
    TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

  //pins se definen despues
  //Car iniciar 4 motores
MotorControl motorControl;

  //Sensor Ultrasonico, primerp pin es el trigger y el segundo es el echo
  UltraSonico sensorFrente(38, 39);//Frente
  UltraSonico sensorIzquierda(36, 37);//Izquierda
  UltraSonico sensorDerecha(40, 41);//Derecha

  //variables
  //int speed;
//int t;??? dos tiempos??
double distanceFrente;
double distanceIzquierda;
double distanceDerecha;
bool bloqueo = false;
int detector= 4; //IR sensor

void setup() {
  //Left Front Motor
  motorControl.begin();

  //primer pin es ENA, segundo es In1 y tercero es In2
  motorControl.motorFrontLeft(9, 22, 23); //Left Front Motor
  motorControl.motorFrontRight(10, 26, 27); //Right Front Motor
  motorControl.motorBackLeft(11, 30, 31); //Left Back Motor
  motorControl.motorBackRight(12, 34, 35); //Right Back Motor

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
}


void loop() {
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
  //*/
  analogWrite(redpin, gammatable[(int)red]);
  analogWrite(greenpin, gammatable[(int)green]);
  analogWrite(bluepin, gammatable[(int)blue]);
  


  if(distanceFrente<=5){ //Si hay 5 cm o menos
    bool bloqueo = true;
  }

  if(bloqueo == true){
    Serial.println("Obstaculo detectado");
    Parking();
    delay(1000);
    neutro();
  }
  else{
    Avanzar(100);
  }

  //Ultrasonic medir distancia
  distanceFrente = sensorFrente.getDistance();
  distanceIzquierda = sensorIzquierda.getDistance();  
  distanceDerecha = sensorDerecha.getDistance();

  if(distanceFrente<=5){ //Si hay 5 cm
    bool bloqueo = true;
  }
}
