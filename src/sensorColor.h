#ifndef SENSORCOLOR_H
#define SENSORCOLOR_H
#include <Arduino.h>
class sensorColor{
public:
    sensorColor(int s0,int s1, int s2, int s3, int sensorout);
    void begin();
    int S0;
    int S1;
    int S2;
    int S3;
    int sensorOut;
    int redPW, redRGB;
    int greenPW, greenRGB;
    int bluePW, blueRGB;
    int redPin=5;
    int greenPin=6;
    int bluePin=3;
    String color;
    String setColor();
    void turnLed();

};
#endif