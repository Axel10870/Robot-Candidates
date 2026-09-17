#ifndef ULTRASONICO_H
#define ULTRASONICO_H
#include <Arduino.h>

class UltraSonico {
public:
    UltraSonico(int triggerPin, int echoPin);
    void begin();
    long getDistance();// en cm

private:
    int triggerPin;
    int echoPin;
};

#endif // ULTRASONICO_H