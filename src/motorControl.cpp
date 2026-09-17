#include "MotorControl.h"

MotorControl::MotorControl()
    : frontLeft(0, 0, 0),
      frontRight(0, 0, 0),
      backLeft(0, 0, 0),
      backRight(0, 0, 0) {}

void MotorControl::begin() {
    frontLeft.begin();
    frontRight.begin();
    backLeft.begin();
    backRight.begin();
}

void MotorControl::motorFrontLeft(int ENA_PIN, int In1_PIN, int In2_PIN) {
    frontLeft = Motor(ENA_PIN, In1_PIN, In2_PIN);
}

void MotorControl::motorFrontRight(int ENA_PIN, int In1_PIN, int In2_PIN) {
    frontRight = Motor(ENA_PIN, In1_PIN, In2_PIN);
}

void MotorControl::motorBackLeft(int ENA_PIN, int In1_PIN, int In2_PIN) {
    backLeft = Motor(ENA_PIN, In1_PIN, In2_PIN);
}

void MotorControl::motorBackRight(int ENA_PIN, int In1_PIN, int In2_PIN) {
    backRight = Motor(ENA_PIN, In1_PIN, In2_PIN);
}
void MotorControl::Avanzar(int speed) {
    frontLeft.avanzar(speed);
    frontRight.avanzar(speed);
    backLeft.avanzar(speed);
    backRight.avanzar(speed);
}

void MotorControl::Retroceder(int speed) {
    frontLeft.retroceder(speed);
    frontRight.retroceder(speed);
    backLeft.retroceder(speed);
    backRight.retroceder(speed);
}
void MotorControl::Derecha(int speed) {
    frontLeft.avanzar(speed);
    frontRight.retroceder(speed);
    backLeft.avanzar(speed);
    backRight.retroceder(speed);
}
void MotorControl::Izquierda(int speed) {
    frontLeft.retroceder(speed);
    frontRight.avanzar(speed);
    backLeft.retroceder(speed);
    backRight.avanzar(speed);
}
