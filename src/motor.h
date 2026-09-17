#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>
Class Motor{
    public:
    Motor(int ENA_PIN, int In1_PIN, int In2_PIN);
    void begin();
    void avanzar(int speed);
    void retroceder(int speed);
    void parar();

    private:
    int ENA_PIN;
    int In1_PIN;
    int In2_PIN;
};

#endif // MOTOR_H
