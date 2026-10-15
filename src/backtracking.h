#ifndef BACKTRACKING_H
#define BACKTRACKING_H
#include <Arduino.h>
#include "Aperturas.h"
#include "Movements.h"

// Your header file content here
class BackTracking {
public:
    BackTracking(UltraSonico &sensorIzquierda, UltraSonico &sensorDerecha, UltraSonico &sensorFrente, Movements &robot);
    void solver(int fila, int columna,int direccion);
    static constexpr int TAM = 40;
    bool visited[TAM][TAM];
    bool deadEnd[TAM][TAM];
    Aperturas vecinos[TAM][TAM];
    Aperturas aperturas;
private:
    void dfs(int fila, int columna, int direccion);
    //para marcar movimiento a cada direccion, N=0, E=1, S=2, O=3
    const int direccionFila[4] = {-1, 0, 1, 0};
    const int direccionColumna[4] = {0, 1, 0, -1};
    // prefrencia de movimiento, 0=recto, 1=derecha, 3=izquierda
    // y factor de correccion en caso de ver a otro lado, +1 giro derecha, +3 giro izquierda
    const int direccionMovimiento[3]= {0,1,3};
    
    
};
#endif // BACKTRACKING_H