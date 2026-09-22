#include "movements.h"
//clase para controlar los 4 motores, y sus movimientos en conjunto, se le pasan los pines de control y el pin de velocidad
Movements::Movements()
    :   frontLeft(0, 0, 0),
        frontRight(0, 0, 0),
        backLeft(0, 0, 0),
        backRight(0, 0, 0) { 
            }

    void Movements::begin() {
        frontLeft.begin();
        frontRight.begin();
        backLeft.begin();
        backRight.begin();
    }

    void Movements::motorFrontLeft(int ENA_PIN, int In1_PIN, int In2_PIN) {
        frontLeft = Motor(ENA_PIN, In1_PIN, In2_PIN);
    }

    void Movements::motorFrontRight(int ENA_PIN, int In1_PIN, int In2_PIN) {
        frontRight = Motor(ENA_PIN, In1_PIN, In2_PIN);
    }

    void Movements::motorBackLeft(int ENA_PIN, int In1_PIN, int In2_PIN) {
        backLeft = Motor(ENA_PIN, In1_PIN, In2_PIN);
    }

    void Movements::motorBackRight(int ENA_PIN, int In1_PIN, int In2_PIN) {
        backRight = Motor(ENA_PIN, In1_PIN, In2_PIN);
    }
    void Movements::avanzar(int speed) {
        frontLeft.avanzar(speed);
        frontRight.avanzar(speed);
        backLeft.avanzar(speed);
        backRight.avanzar(speed);
    }

    void Movements::retroceder(int speed) {
        frontLeft.retroceder(speed);
        frontRight.retroceder(speed);
        backLeft.retroceder(speed);
        backRight.retroceder(speed);
    }
    void Movements::derecha(int speed) {
        frontLeft.avanzar(speed);
        frontRight.retroceder(speed);
        backLeft.avanzar(speed);
        backRight.retroceder(speed);
    }
    void Movements::izquierda(int speed) {
        frontLeft.retroceder(speed);
        frontRight.avanzar(speed);
        backLeft.retroceder(speed);
        backRight.avanzar(speed);
    }
    void Movements::neutro() {
        frontLeft.parar();
        frontRight.parar();
        backLeft.parar();
        backRight.parar();
    }
    void Movements::freno() {
        frontLeft.frenar();
        frontRight.frenar();
        backLeft.frenar();
        backRight.frenar();
    }
