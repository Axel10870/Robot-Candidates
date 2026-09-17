#include "Ultrasonico.h"
// Constructor, define los pines de trigger y echo
 UltraSonico :: UltraSonico(int triggerPin, int echoPin) {
    this->triggerPin = triggerPin;
    this->echoPin = echoPin;
 } 
 // Inicializa los pines del sensor ultrasónico, ponerlo en el setup() del main.cpp
 void UltraSonico :: begin() {
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    digitalWrite(triggerPin, LOW);
 }
// Obtiene la distancia medida por el sensor ultrasónico en centímetros, en loop()
 long UltraSonico :: getDistance() {
    double t=0;
    double distance=0;
    digitalWrite(triggerPin, HIGH);
    delay(10);
    digitalWrite(triggerPin, LOW);
    t= pulseIn(echoPin, HIGH);
    distance = t / 58.0; // Convert to centimeters
    return distance;
 }

