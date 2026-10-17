#include <Arduino.h>
#include "Wire.h"
#include "Ultrasonico.h"  
#include "movements.h"
#include "Servo.h"
#include <SPI.h>

  //color Sensor set
  #define redpin 5
  #define greenpin 3
  #define bluepin 6
  #define commonAnode true
  #define S0 36     // Pin S0 para escala de frecuencia
  #define S1 37     // Pin S1 para escala de frecuencia
  #define S2 39     // Pin S2 para selección de filtro de color (Rojo/Azul)
  #define S3 38     // Pin S3 para selección de filtro de color (Verde/Sin filtro)
  #define sensorOut 40 // Pin OUT del sensor (debe soportar interrupciones o lectura de pulsos)

// Variables para almacenar las frecuencias leídas de cada color
int frecuenciaRojo = 0;
int frecuenciaVerde = 0;
int frecuenciaAzul = 0;

  //pins se definen despues
  //Car iniciar 4 motores, pines puestos en 0, se cambia en setup()
Movements movements;

  //Sensor Ultrasonico, primer pin es el trigger y el segundo es el echo
  UltraSonico sensorFrente(25, 24);//Frente
  UltraSonico sensorIzquierda(23, 22);//Izquierda
  UltraSonico sensorDerecha(27, 26);//Derecha

  //variables
//int t;??? dos tiempos??
double distanceFrente;
double distanceIzquierda;
double distanceDerecha;
int detector= 49; //IR sensor
bool PelotaenPosesion = false;
int STAGE = 1; ///////////////////////////////Etapa del circuito////////////////////////////
bool Union = false; ///////UNION DE ETAPAS////////
Servo garra;



//STAGE 1
bool bloqueofrontal = false;
bool bloqueolateralizq = false;
bool bloqueolateralder = false;

//STAGE 2
bool valueIR = LOW;
String Rosa; //Dirección
bool bloqueoIR;
bool Procesosalida = false; //Para que no se quede en un loop infinito de buscar la salida

//STAGE 3
String Color; //Color detectado
int direccion = 0; //Dirección del color detectado
String Lectura;
int Traduccion_lectura; //Traducción de la lectura del color a un número para comparar con la dirección

void setup() {

  garra.attach(12); // Asignar el pin de la garra


  //Motores poner los pines de cada motor
  //primer pin es EN, segundo es In1 y tercero es In2
  movements.motorBackLeft(9, 29, 31);
  movements.motorFrontLeft(8, 28, 30);
  movements.motorBackRight(10, 32, 34);
  movements.motorFrontRight(11, 33, 35);

//Especificar que son cada pin de todos los motores (Output, etc)
  movements.begin();

  //empieza comunicacion serial
  Serial.begin(9600);

  //Ultrasonicos modo de pines
  sensorFrente.begin();
  sensorIzquierda.begin();
  sensorDerecha.begin();

   //infrarrojo (IR)
  pinMode(detector, INPUT);

  // --- Setup TCS3200 ---
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Configurar escala de frecuencia al 20% (Ideal para microcontroladores)
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.println("Iniciando robot...");
  delay(5000); // Esperar un segundo para estabilizar el sensor

  movements.avanzar(200); // Avanza al inicio para no confundirse 
  delay(5500);
}


void loop() {
//                       ULTRASÓNICOS | DETECCIÓN DE OBSTÁCULOS (PAREDES)
  if(STAGE == 0){ ///PRUEBAS
    distanceFrente = sensorFrente.getDistance();
    distanceIzquierda = sensorIzquierda.getDistance();
    distanceDerecha = sensorDerecha.getDistance();

    Serial.println("Distancia frontal: " ); Serial.println(distanceFrente); Serial.println("cm | ");
    Serial.println("Distancia derecha: " ); Serial.println(distanceDerecha); Serial.println("cm | ");
    Serial.println("Distancia izquierda: " ); Serial.println(distanceIzquierda); Serial.println("cm | ");

    delay(500);
  }
  if(STAGE == 1){ //           ETAPA 1 CIRCUITO B
    distanceFrente = sensorFrente.getDistance();
    distanceIzquierda = sensorIzquierda.getDistance();
    distanceDerecha = sensorDerecha.getDistance();


    if(distanceFrente<=5){ //Si hay 5 cm o menos
      bloqueofrontal = true;
    }
    else{
      bloqueofrontal = false;
    }
    if(distanceIzquierda<=5){ //Si hay 5 cm o menos
      bloqueolateralizq = true;
    }
    else{
      bloqueolateralizq = false;
    }
    if(distanceDerecha<=5){ //Si hay 5 cm o menos
      bloqueolateralder = true;
    }
    else{
      bloqueolateralder = false;
    }

    if(bloqueofrontal == false && bloqueolateralizq == false && PelotaenPosesion == true){
      movements.avanzar(120);
      delay(1300);
      Serial.println("Salida encontrada! :D");
      movements.freno();
      delay(200);
      movements.neutro();
      movements.izquierda(110);
      delay(3250);
      movements.freno();
      movements.avanzar(110);
      delay(4000);
      movements.neutro();
      STAGE = 2; //Cambio de etapa
      Union = true; 
    }

    else if(bloqueolateralder == false && bloqueofrontal == false && PelotaenPosesion == false){
      movements.avanzar(120);
      delay(800);
      Serial.println("Camino derecho detectado. Posible pelota!");
      movements.freno();
      delay(200);
      movements.neutro();
      movements.derecha(110);
      delay(3250);
      movements.freno();
      delay(200);
      movements.neutro();
      movements.avanzar(120);
      delay(3000);
      movements.neutro();
    }

    else if(distanceFrente<=30 && bloqueolateralizq == true && bloqueolateralder == true && PelotaenPosesion == false){
      Serial.println("Pelota encontrada!");
      movements.avanzar(120);
      delay(1300);
      movements.neutro();
      garra.write(110); // Cierra la garra para agarrar la pelota
      delay(500); // Espera un segundo para asegurar que la garra se cierre
      PelotaenPosesion = true;
      movements.retroceder(120);
      delay(500);
      movements.neutro();
      movements.derecha(110);
      delay(6500);
      movements.neutro();
    }

    else if(bloqueofrontal == true){
      Serial.println("Obstaculo físico detectado");
      movements.freno();
      delay(200);
      movements.retroceder(120);
      delay(300);
      movements.neutro();
      movements.derecha(110);
      delay(3250);
      movements.neutro();
    }
    else{
      movements.avanzar(120);
      delay(300);
    }
  }


  if (STAGE == 2 && Union == true){ //           CAMBIO ETAPA 1-2 Circuito B
    movements.avanzar(120);
    delay(2500);
    movements.neutro();
    Union = false;
    Rosa = "Norte";
  }


  else if(STAGE == 2 && Union == false){ //           ETAPA 2 CIRCUITO B
    
    ///////////SENSORES///////
    //Ultrasónico
    distanceFrente = sensorFrente.getDistance();
    if(distanceFrente<=5){ //Si hay 5 cm o menos
      bloqueofrontal = true;
    }
    else{
      bloqueofrontal = false;
    }
    distanceIzquierda = sensorIzquierda.getDistance();
    if(distanceIzquierda<=5){ //Si hay 5 cm o menos
      bloqueolateralizq = true;
    }
    else{
      bloqueolateralizq = false;
    }
    //Infrarrojo
    valueIR = digitalRead(detector);
    if(valueIR == HIGH){ //checa si hay obstaaculo
      Serial.println("Barrera infraroja detectada");//cambiar a un boolean
      bloqueoIR = true;
    }
    else {
      bloqueoIR = false;
    }


    //////////////////////MOVIMIENTO/////////////////////
    if(Rosa == "Norte" && bloqueofrontal == true && bloqueoIR == false){         //DAR LA VUELTA PARA DEVOLVERSE
      Serial.println("Momento de encontrar la puerta de salida!");
      Procesosalida = true;
      movements.izquierda(120);
      delay(3250);
      movements.neutro();           /// QUEDAR VOLTEANDO AL ESTE
      Rosa = "Este";
      
    }
    else if(Rosa == "Este" && bloqueofrontal == true){         //DAR LA VUELTA PARA DEVOLVERSE
      movements.izquierda(110);
      delay(3250);
      movements.neutro();
      Rosa = "Oeste";
      delay(200);
    }
    else if(Rosa == "Este" && bloqueofrontal == false && Procesosalida == false){
      movements.izquierda(110);
      delay(3250);
      movements.neutro();
      Rosa = "Norte";
      delay(200);
    }
    else if(Rosa == "Oeste" && bloqueofrontal == true){             //VOLTEAR AL FRENTE PARA CONTINUAR
      movements.derecha(110);
      delay(3250);
      movements.neutro();
      Rosa = "Norte";
      delay(200);
    }
    else if(Rosa == "Norte" && bloqueoIR == true && Procesosalida == false){           // DETECTAR BARRERA IR Y SEGUIR BUSCANDO
      movements.freno();
      delay(200);
      movements.retroceder(120);
      delay(1200);
      movements.neutro();
      movements.derecha(110);
      delay(3250);
      movements.neutro();
      Rosa = "Este";
      movements.avanzar(120);
      delay(3000);//                                 <<<==== 16 CENTIMETROS
      movements.neutro();
    }
    else if(Procesosalida == true && Rosa == "Este" && bloqueolateralizq == false){
      delay(200);
      movements.izquierda(110);
      delay(3250);
      movements.neutro();
      Rosa = "Norte";
      Serial.println("Salida encontrada! :D");
      movements.avanzar(120);
      delay(4000);
      movements.neutro();
      STAGE = 3; //Cambio de etapa
      Union = true;
    }
    else if(Rosa == "Norte" && bloqueoIR == false && bloqueofrontal == false){ // Avanzar normal
      movements.avanzar(120);
    }
    
  }
  


  if(STAGE == 3 && Union == true){ //           CAMBIO ETAPA 2-3 Circuito B
    movements.avanzar(120);
    delay(3000);
    movements.neutro();
    Union = false;
  }
  /////////////////////////////// FALTA DISTINGUIR Y ENCONTRAR SALIDA //////////////////////////////////

  if(STAGE == 3 && Union == false){ //           ETAPA 3 CIRCUITO B
    //////////////                       ORIENTACIÓN
    if(direccion == 0){
      Rosa = "Norte";
    }
    else if(direccion == 1){
      Rosa = "Este";
    }
    else if(direccion == 2){
      Rosa = "Sur";
    }
    else if(direccion == 3){
      Rosa = "Oeste";
    }
    else if(direccion == 4){
      direccion = 0;
    }

    //////////////                                 COLORES
    
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    frecuenciaRojo = pulseIn(sensorOut, LOW);

    // --- Leer Filtro VERDE ---
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    frecuenciaVerde = pulseIn(sensorOut, LOW);

    // --- Leer Filtro AZUL ---
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    frecuenciaAzul = pulseIn(sensorOut, LOW);

    // Nota con TCS3200: A MENOR frecuencia (tiempo de pulso más corto), MAYOR intensidad del color.
    // Para normalizar con el mismo principio, invertimos los valores o usamos proporciones inversas.
    // O mejor aún, convertimos los pulsos a valores directos de intensidad estimada:
    float rVal = 255.0 - constrain(frecuenciaRojo, 0, 255);
    float gVal = 255.0 - constrain(frecuenciaVerde, 0, 255);
    float bVal = 255.0 - constrain(frecuenciaAzul, 0, 255);

    // Depuración por serial
    Serial.print("R_freq: "); Serial.print(frecuenciaRojo);
    Serial.print("\tG_freq: "); Serial.print(frecuenciaVerde);
    Serial.print("\tB_freq: "); Serial.println(frecuenciaAzul);

    // 4. Clasificación por Rangos Normalizados
    if (25 > frecuenciaRojo && frecuenciaRojo > 15 && 55 > frecuenciaVerde && frecuenciaVerde > 40 && 
        60 > frecuenciaAzul && frecuenciaAzul > 40) {
      Color = "Naranja";     
    } 
    else if (65 > frecuenciaRojo && frecuenciaRojo > 50 && 35 > frecuenciaVerde && frecuenciaVerde > 25 && 
        25 > frecuenciaAzul && frecuenciaAzul > 15) {
      Color = "Celeste";     
    } 
    else if (20 > frecuenciaRojo && frecuenciaRojo > 5 && 70 > frecuenciaVerde && frecuenciaVerde > 20 && 
        30 > frecuenciaAzul && frecuenciaAzul > 15) {
      Color = "Rosa";        
    } 
    else if (20 > frecuenciaRojo && frecuenciaRojo > 10 && 25 > frecuenciaVerde && frecuenciaVerde > 10 && 
        35 > frecuenciaAzul && frecuenciaAzul > 20) {
      Color = "Amarrillo";   
    }
    else {
      Color = "Desconocido"; 
    }

    ////// DELIMITAR RANGOS DE COLORES PARA DETECTAR CUAL ES EL COLOR CORRECTO Y LA ACCIÓN POR HACER


    //Action detection
    if(Color == "Desconocido"){
      Lectura = "Valiendo Verga";
      Traduccion_lectura = 69;
    }
    else if(Color == "Naranja"){
      Lectura = "Norte";
      Traduccion_lectura = 0;
    }
    else if(Color == "Celeste"){
      Lectura = "Este";
      Traduccion_lectura = 1;
    }
    else if(Color == "Rosa"){
      Lectura = "Sur";
      Traduccion_lectura = 2;
    }
    else if(Color == "Amarrillo"){
      Lectura = "Oeste";
      Traduccion_lectura = 3;
    }

    Serial.println("Color detectado: " + Color);
    Serial.println("Dirección detectada: " + Lectura);

    // Actions
    
    if(Traduccion_lectura == 69){
      Serial.println("Repitiendo proceso");
      delay(2000);
    }
    else if(Traduccion_lectura < direccion){
      movements.izquierda(110);
      delay(3250);
      movements.neutro();
      direccion--;
    }
    else if(Traduccion_lectura > direccion){
      movements.derecha(110);
      delay(3250);
      movements.neutro();
      direccion++;
    }
    else if(Traduccion_lectura == direccion){
      movements.avanzar(120);
      delay(4000);//                                <<<==== Ajustar a una casilla
      movements.neutro();
    }

  }

}
