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
    if (distIzq < 8.0 && distDer < 8.0) {
        return distIzq - distDer;
    }else if(distIzq<4.0){
        return -(4-distIzq);
    } else if (distDer<4.0){
        return 4-distDer;
    }
    return 0;
}
void CorrectionCentrado::centrarYAvanzarCasilla(Movements &movements, UltraSonico &sensorIzquierda, UltraSonico &sensorDerecha, UltraSonico &sensorFrente) {
    //sumar/restar correccion a velocidad para centrarse, multiplicado por 5 para que sea mas notorio el cambio de velocidad
    float correction = getCorrection(sensorIzquierda, sensorDerecha);
    float distanceFrente = sensorFrente.getDistance();
    float n = 5.5;
    bool yaCambio = false;
    while((int)(distanceFrente)% 30 > n) {//si esta 5 cm de una casilla para, para hacer dfs a la siguiente(osea hasta moverse a otra casilla)
        movements.avanzarIzquierda((int)(125-10.0*correction));
        movements.avanzarDerecha((int)(125+10.0*correction)); 
        delay(50);
        correction = getCorrection(sensorIzquierda, sensorDerecha);
        distanceFrente = sensorFrente.getDistance();
        if(distanceFrente<=30 && !yaCambio){
            n-=1.5;
            yaCambio=true;
        }
    }
    movements.neutro();
}
void CorrectionCentrado::detectarApertura(UltraSonico &sensorIzquierda, UltraSonico &sensorDerecha, UltraSonico &sensorFrente) {
    //detectar si hay apertura a los lados o al frente, para tomar decisiones de movimiento
    distIzq = sensorIzquierda.getDistance();
    distDer = sensorDerecha.getDistance();
    distFrente = sensorFrente.getDistance();
    aperturaIzq = distIzq >= 15.0? true : false;
    aperturaDer = distDer >= 15.0? true : false;
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


