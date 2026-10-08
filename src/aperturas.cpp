#include "Aperturas.h"
//traductor de casillas relativas a absolutas, para ver si hay apertura en cada direccion
Aperturas::Aperturas() {
    for (int i = 0; i < 4; i++) {
        aperturas[i] = false;
    }
    casillasVecinas = CorrectionCentrado();
    
}
void Aperturas::leerAperturas(int fila, int columna, int direccion, UltraSonico &sensorIzquierda, UltraSonico &sensorDerecha, UltraSonico &sensorFrente) {
    //se asume que el robot esta en la casilla (fila, columna) y mirando hacia la direccion
    //direccion: 0=N, 1=E, 2=S, 3=O
    //se leen los sensores ultrasónicos para determinar si hay apertura en cada dirección
    //se actualiza el arreglo aperturas con true si hay apertura y false si no hay
    //pasa sensores para ver si hay pared o no
    casillasVecinas.detectarApertura(sensorIzquierda, sensorDerecha, sensorFrente);
    for (int i = 0; i < 4; i++) {
        int d= (i+direccion) % 4; //direccion absoluta a la que mira el robot
        if(direccion==i){
            //leer sensor frente
            aperturas[d] = casillasVecinas.isAperturaFrente();
        }
        else if((direccion+1)%4==i){
            //leer sensor derecha
            aperturas[d] = casillasVecinas.isAperturaDer();
        }
        else if((direccion+2)%4==i){
            //sensor atras no hay asi que como viene de atras asumir que si puede ir
            aperturas[d] = true;
        }
        else if((direccion+3)%4==i){
            //leer sensor izquierda
            aperturas[d] = casillasVecinas.isAperturaIzq();
        }
    }
}