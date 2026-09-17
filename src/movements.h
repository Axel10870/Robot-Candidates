#ifndef MOVEMENTS_H
#define MOVEMENTS_H
#include "motor.h"
#include <Arduino.h>
class Movements {
public:
    Movements();
    void begin();
    void motorFrontLeft(int ENA_PIN, int In1_PIN, int In2_PIN);
    void motorFrontRight(int ENA_PIN, int In1_PIN, int In2_PIN);
    void motorBackLeft(int ENA_PIN, int In1_PIN, int In2_PIN);
    void motorBackRight(int ENA_PIN, int In1_PIN, int In2_PIN);
    void avanzar(int speed);
    void retroceder(int speed);
    void derecha(int speed);
    void izquierda(int speed);
    void neutro();
    void freno();

private:
    Motor frontLeft;
    Motor frontRight;
    Motor backLeft;
    Motor backRight;
};
#endif // MOVEMENTS_H
