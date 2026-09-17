#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H
#include "motor.h"
#include <Arduino.h>
class MotorControl {
public:
    MotorControl();
    void begin();
    void motorFrontLeft(int ENA_PIN, int In1_PIN, int In2_PIN);
    void motorFrontRight(int ENA_PIN, int In1_PIN, int In2_PIN);
    void motorBackLeft(int ENA_PIN, int In1_PIN, int In2_PIN);
    void motorBackRight(int ENA_PIN, int In1_PIN, int In2_PIN);
    void Avanzar(int speed);
    void Retroceder(int speed);
    void Derecha(int speed);
    void Izquierda(int speed);
    void neutro();

private:
    Motor frontLeft;
    Motor frontRight;
    Motor backLeft;
    Motor backRight;
};
#endif // MOTORCONTROL_H
