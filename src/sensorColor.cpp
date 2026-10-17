#include "sensorColor.h"

namespace {
const unsigned long PULSE_TIMEOUT_US = 25000UL;

int readPulseWidth(int filterS2, int filterS3, int sensorOut, int pinS2, int pinS3) {
    digitalWrite(pinS2, filterS2);
    digitalWrite(pinS3, filterS3);
    return static_cast<int>(pulseIn(sensorOut, LOW, PULSE_TIMEOUT_US));
}
}

sensorColor::sensorColor(int s0, int s1, int s2, int s3, int sensorout)
    : S0(s0),
      S1(s1),
      S2(s2),
      S3(s3),
      sensorOut(sensorout),
      redPW(0),
      redRGB(0),
      greenPW(0),
      greenRGB(0),
      bluePW(0),
      blueRGB(0),
      color("Sin lectura") {
}

void sensorColor::begin() {
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(sensorOut, INPUT);

    // TCS3200 output frequency scaling: 20%.
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);

    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

String sensorColor::setColor() {
    redPW = readPulseWidth(LOW, LOW, sensorOut, S2, S3);
    greenPW = readPulseWidth(HIGH, HIGH, sensorOut, S2, S3);
    bluePW = readPulseWidth(LOW, HIGH, sensorOut, S2, S3);

    if (redPW <= 0 || greenPW <= 0 || bluePW <= 0) {
        redRGB = 0;
        greenRGB = 0;
        blueRGB = 0;
        color = "Blanco";
        return color;
    }else if(redPW>33 && (greenPW>63 && greenPW<90)&&(bluePW>43&&bluePW<70)){
        redRGB =254;
        greenRGB=0;
        blueRGB=0;
        color="Red";
        return color;
    }


    return color;
}

void sensorColor::turnLed() {
    analogWrite(redPin, redRGB);
    analogWrite(greenPin, greenRGB);
    analogWrite(bluePin, blueRGB);
}