#include <Arduino.h>
#include "Adafruit_TCS34725.h"
#include "motor.h"
#include "movements.h"
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
  Serial.begin(9600);

  // Sensor de color
  /*
  if (tcs.begin()) {
    Serial.println("TCS34725 OK");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  // Ajuste de intensidad LED RGB
  for (int i = 0; i < 256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;

    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;
    }
  }

  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
*/
  // Motores del robot
  robot.motorBackLeft(9, 29, 31);
  robot.motorFrontLeft(8, 28, 30);
  robot.motorBackRight(10, 32, 34);
  robot.motorFrontRight(11, 33, 35);
  /*
  robot.motorFrontLeft(11, 32, 34);
  robot.motorFrontRight(8, 30, 28);
  robot.motorBackLeft(10, 33, 35);
  robot.motorBackRight(9, 29, 31);
*/
  robot.begin();

  // Sensores de distancia
  sensorFrente.begin();
  sensorIzquierda.begin();
  sensorDerecha.begin();
}

void loop() {
  // -------------------- PRUEBA: MOTORES --------------------
  if (pruebaMotores) {
    Serial.println("PRUEBA MOTORES");
    delay(2000);
    robot.derecha(100);
    delay(2500);
    robot.neutro();
    /*
    robot.avanzar(180);
    delay(3000);
    robot.neutro();
    delay(3000);
    robot.derecha(180);
    delay(3000);
    robot.neutro();
    delay(3000);
    robot.izquierda(180);
    delay(3000);
    robot.neutro();
    delay(3000);
    robot.retroceder(180);
    delay(3000);
    robot.neutro();
    delay(3000);
    */
  }

  // -------------------- PRUEBA: ULTRASONICOS --------------------
  else if (pruebaUltrasonico) {
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

  // -------------------- PRUEBA: COLOR --------------------
  /*
  else if (pruebaColor) {
    float red, green, blue;
    tcs.getRGB(&red, &green, &blue);
    tcs.setInterrupt(true);

    Serial.print("R:");
    Serial.print(int(red));
    Serial.print(" G:");
    Serial.print(int(green));
    Serial.print(" B:");
    Serial.println(int(blue));

    analogWrite(redpin, gammatable[(int)red]);
    analogWrite(greenpin, gammatable[(int)green]);
    analogWrite(bluepin, gammatable[(int)blue]);

    delay(200);
  }*/

  // -------------------- PRUEBA CONJUNTA --------------------
  else {
    /*
    float red, green, blue;
    tcs.getRGB(&red, &green, &blue);
    tcs.setInterrupt(true);

  Serial.print("R:");
  Serial.print(int(red));
  Serial.print(" G:");
  Serial.print(int(green));
  Serial.print(" B:");
  Serial.print(int(blue));
  Serial.print("  |  ");
*/
  distanceFrente = sensorFrente.getDistance();
  distanceIzquierda = sensorIzquierda.getDistance();
  distanceDerecha = sensorDerecha.getDistance();

  Serial.print("F:");
  Serial.print(distanceFrente);
  Serial.print("cm  I:");
  Serial.print(distanceIzquierda);
  Serial.print("cm  D:");
  Serial.print(distanceDerecha);
  Serial.println("cm");

  if (distanceFrente < 22.0f && distanceDerecha > 12.0f) {
    robot.derecha(180);
    delay(350);
  }
  else if (distanceFrente < 22.0f && distanceIzquierda > 12.0f) {
    robot.izquierda(180);
    delay(350);
  }
  else if (distanceFrente < 22.0f && distanceIzquierda < 12.0f && distanceDerecha < 12.0f) {
    robot.retroceder(170);
    delay(700);
    robot.neutro();
    delay(250);
    robot.derecha(180);
    delay(600);
  }
  else {
    robot.avanzar(150);
  }
/*
  analogWrite(redpin, gammatable[(int)red]);
  analogWrite(greenpin, gammatable[(int)green]);
  analogWrite(bluepin, gammatable[(int)blue]);
*/
  delay(100);
}
}