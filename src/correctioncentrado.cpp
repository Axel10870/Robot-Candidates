#include "correctioncentrado.h"
CorrectionCentrado::CorrectionCentrado() {
    aperturaIzq = false;
    aperturaDer = false;
    aperturaFrente = false;
    distIzq = 0;
    distDer = 0;
    distFrente = 0;
}
float CorrectionCentrado::getCorrection(UltraSonico &sensorIzquierda, UltraSonico &sensorDerecha) {
    distIzq = sensorIzquierda.getDistance();
    distDer = sensorDerecha.getDistance();
    //en caso de que tengan pared y su deferencia sea mayor a 1 cm, se devuelve la diferencia para corregir el movimiento
    if (distIzq < 8.0 && distDer < 8.0 && (distIzq-distDer > 1.0||distDer-distIzq > 1.0)) {
        return distIzq - distDer;
    }
    return 0;
}
void CorrectionCentrado::centrar(Movements &movements, UltraSonico &sensorIzquierda, UltraSonico &sensorDerecha) {
    //sumar/restar correccion a velocidad para centrarse, multiplicado por 5 para que sea mas notorio el cambio de velocidad
    float correction = getCorrection(sensorIzquierda, sensorDerecha);
        movements.avanzarIzquierda(100+5*correction);
        movements.avanzarDerecha(100-5*correction); 
}
void CorrectionCentrado::detectarApertura(UltraSonico &sensorIzquierda, UltraSonico &sensorDerecha, UltraSonico &sensorFrente) {
    //detectar si hay apertura a los lados o al frente, para tomar decisiones de movimiento
    distIzq = sensorIzquierda.getDistance();
    distDer = sensorDerecha.getDistance();
    distFrente = sensorFrente.getDistance();
    aperturaIzq = distIzq >= 12.0? true : false;
    aperturaDer = distDer >= 12.0? true : false;
    aperturaFrente = distFrente >= 20.0? true : false;
}
//te dice cuando hay una ruta/nodo abierto por explorar usado por backtracking
bool CorrectionCentrado::isAperturaIzq() {
    return aperturaIzq;
}
bool CorrectionCentrado::isAperturaDer() {
    return aperturaDer;
}
bool CorrectionCentrado::isAperturaFrente() {
    return aperturaFrente;
}





