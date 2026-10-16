#include "Aperturas.h"
//traductor de casillas relativas a absolutas, para ver si hay apertura en cada direccion
Aperturas::Aperturas()
    : sensorIzquierda(*(new UltraSonico(0, 0))),
      sensorDerecha(*(new UltraSonico(0, 0))),
      sensorFrente(*(new UltraSonico(0, 0))),
      aperturas{0},
      casillasVecinas() {
}

Aperturas::Aperturas(UltraSonico &sensorIzquierda, UltraSonico &sensorDerecha, UltraSonico &sensorFrente)
    : sensorIzquierda(sensorIzquierda),
      sensorDerecha(sensorDerecha),
      sensorFrente(sensorFrente),
      aperturas{0},
      casillasVecinas() {
}

void Aperturas::leerAperturas(int direccion) {
    //mirando havia direccion: 0=N, 1=E, 2=S, 3=O
    //se leen los sensores ultrasónicos para determinar si hay apertura en cada dirección
    //se actualiza el arreglo aperturas con true si hay apertura y false si no hay
    //pasa sensores para ver si hay pared o no
    casillasVecinas.detectarApertura(sensorIzquierda, sensorDerecha, sensorFrente);
    for (int relativa = 0; relativa < 4; relativa++) {
        int d = (relativa + direccion) % 4; //direccion absoluta a la que mira el robot
        bool abierta;

        switch (relativa) {
            case 0: abierta = casillasVecinas.isAperturaFrente(); break;
            case 1: abierta = casillasVecinas.isAperturaDer();    break;
            case 2: abierta = true;                               break;
            default: abierta = casillasVecinas.isAperturaIzq();   break;
        }
        setApertura(d, abierta);//actualiza la apertura en direccion absoluta
    }
}

bool Aperturas::getApertura(int direccion) const {
    return (aperturas & (1U << direccion)) != 0;
}

void Aperturas::setApertura(int direccion, bool apertura) {
    if (apertura) {
        aperturas |= (1U << direccion);  // activa ese bit
    } else {
        aperturas &= ~(1U << direccion); // desactiva ese bit
    }
}

Aperturas& Aperturas::operator=(const Aperturas& other) {
    if (this != &other) {
        aperturas = other.aperturas;
    }
    return *this;
}