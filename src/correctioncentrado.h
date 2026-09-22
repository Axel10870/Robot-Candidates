#ifndef CORRECTIONCENTRADO_H
#define CORRECTIONCENTRADO_H
#include <movements.h>
#include <Arduino.h>
#include <Ultrasonico.h>
//clase para centrar el robot con 2 paredes a los lados y ver si hay una apertura/ruta
class CorrectionCentrado {
private:
    long referenciaIzq, referenciaDer;
    bool aperturaIzq, aperturaDer;
public:
    long distIzq, distDer;
    CorrectionCentrado();
    long getCorrection(Ultrasonico &sensorIzquierda, Ultrasonico &sensorDerecha);
    void detectarApertura();
    void centrar(Movements &movements, UltraSonico &sensorIzquierda, UltraSonico &sensorDerecha);
}
#endif // CORRECTIONCENTRADO_H