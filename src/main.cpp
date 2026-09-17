#include <Arduino.h>
#include "Wire.h"
#include "Adafruit_TCS34725.h"
#include "Ultrasonico.h"
//a
  //color Sensor set
  #define redpin 3
  #define greenpin 5
  #define bluepin 6
  #define commonAnode true
  byte gammatable[256];
  Adafruit_TCS34725 tcs= Adafruit_TCS34725(
    TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

  //pins se definen despues
  //Car
  ////Motor set 1
const int ENA_PIN=9; //PMW  // Power Left Front Motor
const int In1_PIN=22;
const int In2_PIN=23;
const int ENB_PIN=10; //PMW // Power Right Front Motor
const int In3_PIN=26;
const int In4_PIN=27;

  ////Motor set 2
const int ENC_PIN=11; //PMW // Power Left Back Motor
const int In5_PIN=30;
const int In6_PIN=31;
const int END_PIN=12; //PMW // Power Right Back Motor
const int In7_PIN=34;
const int In8_PIN=35;

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

void setup() {
  //Left Front Motor
  pinMode(ENA_PIN, OUTPUT);
  pinMode(In1_PIN, OUTPUT);
  pinMode(In2_PIN, OUTPUT);

  //Right Front Motor
  pinMode(ENB_PIN, OUTPUT);
  pinMode(In3_PIN, OUTPUT);
  pinMode(In4_PIN, OUTPUT);

  //Left Back Motor
  pinMode(ENC_PIN, OUTPUT);
  pinMode(In5_PIN, OUTPUT);
  pinMode(In6_PIN, OUTPUT);

  //Right Back Motor
  pinMode(END_PIN, OUTPUT);
  pinMode(In7_PIN, OUTPUT);
  pinMode(In8_PIN, OUTPUT);

  //empieza comunicacion serial
  Serial.begin(9600);

  //Ultrasonicos
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
  if(valueIR == HIGH){ //checa si hay obstaculo
    Serial.println("Detectado obstaculo");//cambiar a un boolean
  }
  
  //Colores
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

  //Ultrasonic
  distanceFrente = sensorFrente.getDistance();
  distanceIzquierda = sensorIzquierda.getDistance();  
  distanceDerecha = sensorDerecha.getDistance();

  if(distanceFrente<=5){ //Si hay 5 cm
    bool bloqueo = true;
  }

  Avanzar(100);
}


////FUNCIONES DE MOVIMIENTO
void Avanzar(int speed){
  //Velocidades
  analogWrite(ENA_PIN, speed);
  analogWrite(ENB_PIN, speed);
  analogWrite(ENC_PIN, speed);
  analogWrite(END_PIN, speed);
  //Direcciones
  digitalWrite(In1_PIN, 1);
  digitalWrite(In2_PIN, 0);
  digitalWrite(In3_PIN, 1);
  digitalWrite(In4_PIN, 0);
  digitalWrite(In5_PIN, 1);
  digitalWrite(In6_PIN, 0);
  digitalWrite(In7_PIN, 1);
  digitalWrite(In8_PIN, 0);
}
void Retroceder(int speed){
  //Velocidades
  analogWrite(ENA_PIN, speed);
  analogWrite(ENB_PIN, speed);
  analogWrite(ENC_PIN, speed);
  analogWrite(END_PIN, speed);
  //Direcciones
  digitalWrite(In1_PIN, 0);
  digitalWrite(In2_PIN, 1);
  digitalWrite(In3_PIN, 0);
  digitalWrite(In4_PIN, 1);
  digitalWrite(In5_PIN, 0);
  digitalWrite(In6_PIN, 1);
  digitalWrite(In7_PIN, 0);
  digitalWrite(In8_PIN, 1);
}
void Derecha(int speed){
  //Velocidades
  analogWrite(ENA_PIN, speed);
  analogWrite(ENB_PIN, speed);
  analogWrite(ENC_PIN, speed);
  analogWrite(END_PIN, speed);
  //Direcciones
  digitalWrite(In1_PIN, 1);
  digitalWrite(In2_PIN, 0);
  digitalWrite(In3_PIN, 0);
  digitalWrite(In4_PIN, 1);
  digitalWrite(In5_PIN, 1);
  digitalWrite(In6_PIN, 0);
  digitalWrite(In7_PIN, 0);
  digitalWrite(In8_PIN, 1);
}
void Izquierda(int speed){
  //Velocidades
  analogWrite(ENA_PIN, speed);
  analogWrite(ENB_PIN, speed);
  analogWrite(ENC_PIN, speed);
  analogWrite(END_PIN, speed);
  //Direcciones
  digitalWrite(In1_PIN, 0);
  digitalWrite(In2_PIN, 1);
  digitalWrite(In3_PIN, 1);
  digitalWrite(In4_PIN, 0);
  digitalWrite(In5_PIN, 0);
  digitalWrite(In6_PIN, 1);
  digitalWrite(In7_PIN, 1);
  digitalWrite(In8_PIN, 0);
}
void neutro(){
  analogWrite(ENA_PIN, 0);
  analogWrite(ENB_PIN, 0);
  analogWrite(ENC_PIN, 0);
  analogWrite(END_PIN, 0);
  //Direcciones
  digitalWrite(In1_PIN, 0);
  digitalWrite(In2_PIN, 0);
  digitalWrite(In3_PIN, 0);
  digitalWrite(In4_PIN, 0);
  digitalWrite(In5_PIN, 0);
  digitalWrite(In6_PIN, 0);
  digitalWrite(In7_PIN, 0);
  digitalWrite(In8_PIN, 0);
}
void Parking(){
  analogWrite(ENA_PIN, 100);
  analogWrite(ENB_PIN, 100);
  analogWrite(ENC_PIN, 100);
  analogWrite(END_PIN, 100);
  //Direcciones
  digitalWrite(In1_PIN, 1);
  digitalWrite(In2_PIN, 1);
  digitalWrite(In3_PIN, 1);
  digitalWrite(In4_PIN, 1);
  digitalWrite(In5_PIN, 1);
  digitalWrite(In6_PIN, 1);
  digitalWrite(In7_PIN, 1);
  digitalWrite(In8_PIN, 1);
}