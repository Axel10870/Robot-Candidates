#ifndef APERTURAS_H
#define APERTURAS_H
#include <Arduino.h>
#include "Ultrasonico.h"
#include "correctioncentrado.h"

class Aperturas {
public:
    Aperturas();
    Aperturas(UltraSonico &sensorIzquierda, UltraSonico &sensorDerecha, UltraSonico &sensorFrente);
    void leerAperturas(int direccion);
    bool getApertura(int direccion) const;
    void setApertura(int direccion, bool apertura);
    //bool puedeIr(int fila, int columna);
    Aperturas& operator=(const Aperturas& other);
    UltraSonico &sensorIzquierda;
    UltraSonico &sensorDerecha;
    UltraSonico &sensorFrente;
private:
    uint8_t aperturas; // N, E, S, O
    CorrectionCentrado casillasVecinas;
};

#endif // APERTURAS_H