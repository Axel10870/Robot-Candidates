#include "backTracking.h"
BackTracking::BackTracking(UltraSonico &sensorIzquierda, UltraSonico &sensorDerecha, UltraSonico &sensorFrente)
    : aperturas(sensorIzquierda, sensorDerecha, sensorFrente) {
    memset(visited, false, sizeof(visited));
}
void BackTracking::solver(int fila, int columna,int direccion) {
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
    visited[nuevaFila][nuevaColumna] = true;
    aperturas.leerAperturas(fila, columna, direccion);
    vecinos[fila][columna] = aperturas; // te dice sus vecinos y si se puede ir o no
    //intenta ir a cada casilla vecina, en orden de preferencia, recto, derecha, izquierda, volver
    for (int i = 0; i < 4; i++) {
        //dentro del mapa
        if (nuevaFila >= 0 && nuevaFila < TAM && nuevaColumna >= 0 && nuevaColumna < TAM && !visited[nuevaFila][nuevaColumna]) {
            dfs(nuevaFila, nuevaColumna, direccion);
        }
    }
}