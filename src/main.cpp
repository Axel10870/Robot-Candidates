#include <Arduino.h>
  #include "Wire.h"
  #include "Adafruit_TCS34725.h"

  #define redpin 3
  #define greenpin 5
  #define bluepin 6
  #define communAnote true

  byte gammatable[256];
  
  Adafruit_TCS34725 tcs= Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50mMS, TCS34725_GAIN_4X);
  //pins se definen despues
  //Driver
  const int ENA_PIN=9; //in a PMW pin
	const int In1_PIN=10;
	const int In2_PIN=11;
	const int ENB_PIN=12; //in a PMW pin
	const int In3_PIN=13;
	const int In4_PIN=14;
  //Sensor Ultrasonico
  const int Trigger=2;
  const int Echo=3;
void setup() {
  // put your setup code here, to run once:
  //Left Motor
  pinMode(ENA_PIN, OUTPUT);
  pinMode(In1_PIN, OUTPUT);
  pinMode(In2_PIN, OUTPUT);
  //right Motor
  pinMode(ENB_PIN, OUTPUT);
  pinMode(In3_PIN, OUTPUT);
  pinMode(In4_PIN, OUTPUT);
  //Ultrasonico
  Serial.begin(9600);
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);
  digitalWrite(Trigger, LOW);
  double t=0;
  double d=0;
}

void loop() {
  // put your main code here, to run repeatedly:
  //sonic
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);
  t= pulseIn(Echo, HIGH);
  d= t/59;
  //motor moves
  if(infront){
    Motor.front('L',200);
    Motor.front('R',200);
  }else if(turn_left){
    Motor.back('L',100);
    Motor.front('R',100);
  }else if(turn_right){
    Motor.front('L',100);
    Motor.back('R',100);
  }else if(back){
    Motor.back('L',200);
    Motor.back('R',200);
  }else{
    Motor.stop('L');
    Motor.stop('R');
  }

}
struct Motor{
  //the motor goes to the front(normal)
  void front(char side,int speed){
    digitalWrite(side==L?In1_PIN:In3_PIN, HIGH);
    digitalWrite(side==L?In2_PIN:In4_PIN, LOW);
    //velocidad(0-254)
    analogWrite(side==L?ENA_PIN:ENB_PIN, speed);
  }
  //no movement
  void stop(char side){
    digitalWrite(side==L?In1_PIN:In3_PIN, LOW);
    digitalWrite(side==L?In2_PIN:In4_PIN, LOW);
  }
  //the motor goes backwards
  void back(char side, int speed){
    digitalWrite(side==L?In1_PIN:In3_PIN, LOW);
    digitalWrite(side==L?In2_PIN:In4_PIN, HIGH);
    //velocidad(0-254)x2
    analogWrite(side==L?ENA_PIN:ENB_PIN, speed);
  }
}