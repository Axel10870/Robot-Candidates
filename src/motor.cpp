#include "motor.h"
//clase para controlar un motor, se le pasan los pines de control y el pin de velocidad
Motor::Motor(int ENA_PIN, int In1_PIN, int In2_PIN) {
    this->ENA_PIN = ENA_PIN;
    this->In1_PIN = In1_PIN;
    this->In2_PIN = In2_PIN;
}

void Motor::begin() {
    pinMode(ENA_PIN, OUTPUT);
    pinMode(In1_PIN, OUTPUT);
    pinMode(In2_PIN, OUTPUT);
}

void Motor::avanzar(int speed) {
    analogWrite(ENA_PIN, speed);
    digitalWrite(In1_PIN, HIGH);
    digitalWrite(In2_PIN, LOW);
}

void Motor::retroceder(int speed) {
    analogWrite(ENA_PIN, speed);
    digitalWrite(In1_PIN, LOW);
    digitalWrite(In2_PIN, HIGH);
}

void Motor::parar() {
    digitalWrite(In1_PIN, LOW);
    digitalWrite(In2_PIN, LOW);
}
void Motor::frenar() {
    digitalWrite(In1_PIN, HIGH);
    digitalWrite(In2_PIN, HIGH);
}