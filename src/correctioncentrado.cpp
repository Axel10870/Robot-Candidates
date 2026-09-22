#include "correctioncentrado.h"
CorrectionCentrado::CorrectionCentrado() {
    referenciaIzq = 0;
    referenciaDer = 0;
    aperturaIzq = false;
    aperturaDer = false;
    distIzq = 0;
    distDer = 0;
}
/*long CorrectionCentrado::getCorrection(Ultrasonico &sensorIzquierda, Ultrasonico &sensorDerecha) {
    distIzq = sensorIzquierda.getDistance();
    distDer = sensorDerecha.getDistance();
    if (distIzq < 8.0 && distDer < 8.0) {
        return distIzq - referenciaIzq;

    }
    return 0;
}*/