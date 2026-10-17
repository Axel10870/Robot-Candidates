#include "backTracking.h"
BackTracking::BackTracking(UltraSonico &sensorIzquierda, UltraSonico &sensorDerecha, UltraSonico &sensorFrente, Movements &robot)
    : aperturas(sensorIzquierda, sensorDerecha, sensorFrente),
      theRobot(&robot) {
    memset(visited, false, sizeof(visited));
    memset(deadEnd, false, sizeof(deadEnd));
    inicio=true;
}
void BackTracking::solver(int fila, int columna,int direccion) {
    //poner bool si se comple la meta si si fin
    if(false){
        return;
    }
    else{
        dfs(fila, columna, direccion); // pasa casilla donde estaba y direccion a la que se movio
    }
}
void BackTracking::dfs(int fila, int columna, int direccion) {
    if (fila < 0 || fila >= TAM || columna < 0 || columna >= TAM ||
        direccion < 0 || direccion >= 4) {
        return;
    }
    //traduce a su nueva posicion en la matriz
    int nuevaFila, nuevaColumna;
    if(!inicio){//si no es la primera casilla,  cambia posicion
        nuevaFila = fila + direccionFila[direccion];
        nuevaColumna = columna + direccionColumna[direccion];
    }else{ //si  es la primera casilla, no  cambia posicion
        nuevaFila = fila;
        nuevaColumna = columna;
    }
    if (nuevaFila < 0 || nuevaFila >= TAM || nuevaColumna < 0 || nuevaColumna >= TAM) {
        return;
    }
    delay(200);
    if(!visited[nuevaFila][nuevaColumna]){ //en caso de no haber ido ahi nunca, lee sus aperturas y guarda en la matriz de vecinos
        aperturas.leerAperturas(direccion);
        if(inicio){ //si es la primera casilla, marca que ya no es la primera
            aperturas.setApertura(2,false); //marca que no puede ir hacia atras porque es la primera
            inicio=false;
        }
        vecinos[nuevaFila][nuevaColumna] = 0;
        for (int i = 0; i < 4; ++i) {
            if (aperturas.getApertura(i)) {
                vecinos[nuevaFila][nuevaColumna] |= static_cast<uint8_t>(1U << i);
            }
        }
        visited[nuevaFila][nuevaColumna] = true;
    }
    if(deadEnd[fila][columna]){ //si de donde viene no tiene continuacion, lo elimina de la lista de vecinos
        vecinos[nuevaFila][nuevaColumna] &= static_cast<uint8_t>(~(1U << ((direccion + 2) % 4)));//marca de donde viene como dead end/ no puede ir
    }
    //intenta ir a cada casilla vecina, en orden de preferencia, recto, derecha, izquierda, volver fuera del for para marcar que no hay nada de donde viene
    for (int i = 0; i < 3; i++) {
        const int direccionDestino = (direccion + direccionMovimiento[i]) % 4;
        const int filaDestino = nuevaFila + direccionFila[direccionDestino];
        const int columnaDestino = nuevaColumna + direccionColumna[direccionDestino];
        const uint8_t mascara = static_cast<uint8_t>(1U << direccionDestino);

        if ((vecinos[nuevaFila][nuevaColumna] & mascara) == 0 ||
            filaDestino < 0 || filaDestino >= TAM ||
            columnaDestino < 0 || columnaDestino >= TAM ||
            visited[filaDestino][columnaDestino]) {
            continue;
        }

        if(i==1){//si es derecha, gira a la derecha
            theRobot->retroceder(100);
            delay(400);
            theRobot->derecha(100);
            delay(1900);
            theRobot->retroceder(100);
            delay(400);
            theRobot->derecha(100);
            delay(1900);
        }else if(i==2){//si es izquierda, gira a la izquierda
            theRobot->retroceder(100);
            delay(400);
            theRobot->izquierda(100);
            delay(1900);
            theRobot->retroceder(100);
            delay(400);
            theRobot->izquierda(100);
            delay(1900);
        }//despues de vueltas o si es enfrente, avanza a la casilla vecina que decidio ir
        theRobot->avanzar(150);
        delay(1500);
        centrarAvanzar.centrarYAvanzarCasilla(*theRobot, aperturas.sensorIzquierda, aperturas.sensorDerecha, aperturas.sensorFrente);
        dfs(nuevaFila, nuevaColumna, direccionDestino);
    }
    //en caso de que no haya salida hacia ninguna direccion que no sea volver, marca como dead end y vuelve a la casilla anterior
    deadEnd[nuevaFila][nuevaColumna] = true;
    if(!deadEnd[fila][columna]){//si de donde viene no es dead end entonces vuelve y marca que no puede ir a la casilla donde estaba
        vecinos[fila][columna] &= static_cast<uint8_t>(~(1U << ((direccion ) )));//marca de donde viene como dead end/ no puede ir
        theRobot->derecha(100); //gira 90 grados hacia la derecha
        delay(3350);
        theRobot->neutro();
        delay(250);
        theRobot->derecha(100); //completa el giro de 180 grados
        delay(1625);
         theRobot->avanzar(100);
        delay(250);
        theRobot->derecha(100); //completa el giro de 180 grados
        delay(1625);
        theRobot->avanzar(100);
        delay(250);
        theRobot->derecha(100);
        delay(1750);//para las paredes que pega
        theRobot->neutro();
        delay(250);
        theRobot->avanzar(150);
        delay(1500);
        centrarAvanzar.centrarYAvanzarCasilla(*theRobot, aperturas.sensorIzquierda, aperturas.sensorDerecha, aperturas.sensorFrente);
        dfs(nuevaFila, nuevaColumna, (direccion+2)%4); //vuelve a la casilla anterior
    }
}