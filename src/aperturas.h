#ifndef APERTURAS_H
#define APERTURAS_H
#include <Arduino.h>
#include "Ultrasonico.h"
#include "correctioncentrado.h"

class Aperturas {
public:
    Aperturas(UltraSonico &sensorIzquierda, UltraSonico &sensorDerecha, UltraSonico &sensorFrente);
    void leerAperturas(int fila, int columna, int direccion);
    bool puedeIr(int fila, int columna);
private:
    bool aperturas[4]; // N, E, S, O
    CorrectionCentrado casillasVecinas;
};

#endif // APERTURAS_H