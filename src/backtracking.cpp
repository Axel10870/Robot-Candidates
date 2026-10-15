#include "backTracking.h"
BackTracking::BackTracking(UltraSonico &sensorIzquierda, UltraSonico &sensorDerecha, UltraSonico &sensorFrente, Movements &robot)
    : aperturas(sensorIzquierda, sensorDerecha, sensorFrente),
      theRobot(&robot) {
    memset(visited, false, sizeof(visited));
    memset(deadEnd, false, sizeof(deadEnd));
}
void BackTracking::solver(int fila, int columna,int direccion) {
    //poner bool si se comple la meta si si fin
    if(true){
        return;
    }
    else{
        dfs(fila, columna, direccion); // pasa casilla donde estaba y direccion a la que se movio
    }
}
void BackTracking::dfs(int fila, int columna, int direccion) {
    //traduce a su nueva posicion en la matriz
    int nuevaFila = fila + direccionFila[direccion];
    int nuevaColumna = columna + direccionColumna[direccion];
    if(!visited[nuevaFila][nuevaColumna]){ //en caso de no haber ido ahi nunca, lee sus aperturas y guarda en la matriz de vecinos
        aperturas.leerAperturas(fila, columna, direccion);
        vecinos[fila][columna] = aperturas; // te dice sus vecinos y si se puede ir o no
        visited[nuevaFila][nuevaColumna] = true;
    }
    if(deadEnd[fila][columna]){ //si de donde viene no tiene continuacion, lo elimina de la lista de vecinos
        vecinos[nuevaFila][nuevaColumna].setApertura((direccion + 2) % 4, false);//marca de donde viene como dead end/ no puede ir
    }
    //intenta ir a cada casilla vecina, en orden de preferencia, recto, derecha, izquierda, volver fuera del for para marcar que no hay nada de donde viene
    for (int i = 0; i < 3; i++) {
        //dentro del mapa
        if (nuevaFila >= 0 && nuevaFila < TAM && nuevaColumna >= 0 && nuevaColumna < TAM) {
            //si se puede ir a esa direccion
            if (vecinos[nuevaFila][nuevaColumna].getApertura((direccion + direccionMovimiento[i]) % 4)) {
                if(i==1){//si es derecha, gira a la derecha
                    theRobot->derecha(100);
                }else if(i==2){//si es izquierda, gira a la izquierda
                    theRobot->izquierda(100);
                }//despues de vueltas o si es enfrente, avanza a la casilla vecina que decidio ir
                theRobot->avanzar(100);
                 dfs(nuevaFila, nuevaColumna, ((direccion+direccionMovimiento[i]) % 4));
            }
            
        }
    }
    //en caso de que no haya salida hacia ninguna direccion que no sea volver, marca como dead end y vuelve a la casilla anterior
    deadEnd[nuevaFila][nuevaColumna] = true;
    if(!deadEnd[fila][columna]){//si de donde viene no es dead end entonces vuelve y marca que no puede ir a la casilla donde estaba
        vecinos[fila][columna].setApertura((direccion + 2) % 4, false);//marca de donde viene como dead end/ no puede ir
        theRobot->derecha(100); //gira a la derecha para volver a la casilla anterior
        theRobot->derecha(100); //gira a la derecha para volver a la casilla anterior
        theRobot->avanzar(100); //avanza a la casilla anterior
        dfs(nuevaFila, nuevaColumna, (direccion+2)%4); //vuelve a la casilla anterior
    }
}