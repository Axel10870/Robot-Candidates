#ifndef APERTURAS_H
#define APERTURAS_H
#include <Arduino.h>
#include "Ultrasonico.h"
#include "correctioncentrado.h"

class Aperturas {
public:
    Aperturas();
    Aperturas(UltraSonico &sensorIzquierda, UltraSonico &sensorDerecha, UltraSonico &sensorFrente);
    void leerAperturas(int fila, int columna, int direccion);
    bool puedeIr(int fila, int columna);
    Aperturas& operator=(const Aperturas& other);
    UltraSonico &sensorIzquierda;
    UltraSonico &sensorDerecha;
    UltraSonico &sensorFrente;
private:
    bool aperturas[4]; // N, E, S, O
    CorrectionCentrado casillasVecinas;
    Movements &robot;
};

#endif // APERTURAS_H