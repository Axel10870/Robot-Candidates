#include <Arduino.h>
#include "Wire.h"
  //#include "Adafruit_TCS34725.h"

  //#define redpin 3
  //#define greenpin 5
 // #define bluepin 6
#define communAnote true

byte gammatable[256];
  
  //Adafruit_TCS34725 tcs= Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50mMS, TCS34725_GAIN_4X);
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

  //Sensor Ultrasonico
const int Trigger=2;
const int Echo=3;

  //variables
  //int speed;
int t;
int distance;
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

  //Ultrasonico
  Serial.begin(9600);
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);
  digitalWrite(Trigger, LOW);
  double t=0;
  double d=0;
}

void loop() {
  //Ultrasonic
  digitalWrite(Trigger, HIGH);
  delay(10);
  digitalWrite(Trigger, LOW);
  t= pulseIn(Echo, HIGH);
  distance= t/58.2; //Distancia en cm

  if(distance=5){ //Si hay 5 cm
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