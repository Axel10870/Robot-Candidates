#include "Aperturas.h"
//traductor de casillas relativas a absolutas, para ver si hay apertura en cada direccion
Aperturas::Aperturas()
    : sensorIzquierda(*(new UltraSonico(0, 0))),
      sensorDerecha(*(new UltraSonico(0, 0))),
      sensorFrente(*(new UltraSonico(0, 0))),
      aperturas{false, false, false, false},
      casillasVecinas() {
}

Aperturas::Aperturas(UltraSonico &sensorIzquierda, UltraSonico &sensorDerecha, UltraSonico &sensorFrente)
    : sensorIzquierda(sensorIzquierda),
      sensorDerecha(sensorDerecha),
      sensorFrente(sensorFrente),
      aperturas{false, false, false, false},
      casillasVecinas() {
}

void Aperturas::leerAperturas(int fila, int columna, int direccion) {
    //se asume que el robot esta en la casilla (fila, columna) y mirando hacia la direccion
    //direccion: 0=N, 1=E, 2=S, 3=O
    //se leen los sensores ultrasónicos para determinar si hay apertura en cada dirección
    //se actualiza el arreglo aperturas con true si hay apertura y false si no hay
    //pasa sensores para ver si hay pared o no
    casillasVecinas.detectarApertura(sensorIzquierda, sensorDerecha, sensorFrente);
    for (int i = 0; i < 4; i++) {
        int d = (i + direccion) % 4; //direccion absoluta a la que mira el robot
        if (direccion == i) {
            //leer sensor frente
            aperturas[d] = casillasVecinas.isAperturaFrente();
        } else if ((direccion + 1) % 4 == i) {
            //leer sensor derecha
            aperturas[d] = casillasVecinas.isAperturaDer();
        } else if ((direccion + 2) % 4 == i) {
            //sensor atras no hay asi que como viene de atras asumir que si puede ir
            aperturas[d] = true;
        } else if ((direccion + 3) % 4 == i) {
            //leer sensor izquierda
            aperturas[d] = casillasVecinas.isAperturaIzq();
        }
    }
}

bool Aperturas::getApertura(int direccion) const {
    if (direccion < 0 || direccion >= 4) {
        return false;
    }
    return aperturas[direccion];
}

void Aperturas::setApertura(int direccion, bool apertura) {
    if (direccion < 0 || direccion >= 4) {
        return;
    }
    aperturas[direccion] = apertura;
}

Aperturas& Aperturas::operator=(const Aperturas& other) {
    if (this != &other) {
        for (int i = 0; i < 4; ++i) {
            aperturas[i] = other.aperturas[i];
        }
        casillasVecinas = other.casillasVecinas;
    }
    return *this;
}