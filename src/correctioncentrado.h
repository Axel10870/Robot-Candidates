#ifndef CORRECTIONCENTRADO_H
#define CORRECTIONCENTRADO_H
#include <movements.h>
#include <Arduino.h>
#include <Ultrasonico.h>
//clase para centrar el robot con 2 paredes a los lados y ver si hay una apertura/ruta
class CorrectionCentrado {
private:
    bool aperturaIzq, aperturaDer, aperturaFrente;
public:
    float distIzq, distDer, distFrente;
    CorrectionCentrado();
    float getCorrection(Ultrasonico &sensorIzquierda, Ultrasonico &sensorDerecha);
    void detectarApertura(Ultrasonico &sensorIzquierda, Ultrasonico &sensorDerecha, Ultrasonico &sensorFrente);
    void centrar(Movements &movements, Ultrasonico &sensorIzquierda, Ultrasonico &sensorDerecha);
    bool isAperturaIzq();
    bool isAperturaDer();
    bool isAperturaFrente();
};
#endif // CORRECTIONCENTRADO_H