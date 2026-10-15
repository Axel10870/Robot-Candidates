#include <Arduino.h>
#include "Wire.h"
#include "Adafruit_TCS34725.h"
#include "Ultrasonico.h"  
#include "movements.h"

  //color Sensor set
  #define redpin 3
  #define greenpin 5
  #define bluepin 6
  #define commonAnode true
  byte gammatable[256];
 //// Adafruit_TCS34725 tcs= Adafruit_TCS34725(
  ////  TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

  //pins se definen despues
  //Car iniciar 4 motores, pines puestos en 0, se cambia en setup()
Movements movements;

  //Sensor Ultrasonico, primer pin es el trigger y el segundo es el echo
  UltraSonico sensorFrente(25, 24);//Frente
  UltraSonico sensorIzquierda(27, 26);//Izquierda
  UltraSonico sensorDerecha(23, 22);//Derecha

  //variables
//int t;??? dos tiempos??
double distanceFrente;
double distanceIzquierda;
double distanceDerecha;
int detector= 4; //IR sensor
bool PelotaenPosesion = false;
int STAGE = 0; ///////////////////////////////Etapa del circuito////////////////////////////
bool Union = false; ///////UNION DE ETAPAS////////


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
  //Motores poner los pines de cada motor
  //primer pin es EN, segundo es In1 y tercero es In2
  movements.motorFrontLeft(28, 31, 30); //Left Front Motor
  movements.motorFrontRight(11, 35, 33); //Right Front Motor
  movements.motorBackLeft(8, 9, 29); //Left Back Motor
  movements.motorBackRight(10, 34, 32); //Right Back Motor

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

  //color
  //// if(tcs.begin()){ //checar si se conecto correctamente
  //// }else{
  ////   Serial.println(
  ////     "No TCS34725 found ... check your conections");
  ////     while(1);
  //// }
  pinMode(redpin, OUTPUT);//declarar los pines como output
  pinMode(bluepin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  for(int i=0; i<256; i++){ //ajustar intensidad LED's para ver lso cambios de brillo mejor (ni idea como funciona pero meh)
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x*=255;
    if(commonAnode){
      gammatable[i]= 255 - x;
    } else{
      gammatable[i] = x;
    }
  }
  movements.avanzar(100); // Avanza al inicio para no confundirse 
  delay(1000);
}


void loop() {
//                       ULTRASÓNICOS | DETECCIÓN DE OBSTÁCULOS (PAREDES)
  if(STAGE == 0){ ///PRUEBAS
    distanceFrente = sensorFrente.getDistance();
    distanceIzquierda = sensorIzquierda.getDistance();
    distanceDerecha = sensorDerecha.getDistance();

    Serial.println("Distancia frontal: " ); Serial.println(distanceFrente); Serial.println("cm | ");
    Serial.println("Distancia derecha: " ); Serial.println(distanceFrente); Serial.println("cm | ");
    Serial.println("Distancia izquierda: " ); Serial.println(distanceFrente); Serial.println("cm | ");

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
      movements.avanzar(25);
      delay(500);
      Serial.println("Salida encontrada! :D");
      movements.freno();
      delay(200);
      movements.neutro();
      movements.izquierda(100);
      delay(500);
      movements.freno();
      movements.avanzar(50);
      delay(500);
      movements.neutro();
      STAGE = 2; //Cambio de etapa
      Union = true; 
    }

    else if(bloqueolateralder == false && bloqueofrontal == false && PelotaenPosesion == false){
      movements.avanzar(25);
      delay(250);
      Serial.println("Camino derecho detectado. Posible pelota!");
      movements.freno();
      delay(200);
      movements.neutro();
      movements.derecha(100);
      delay(500);
      movements.freno();
      delay(200);
      movements.neutro();
      movements.avanzar(50);
      delay(500);
      movements.neutro();
    }

    else if(bloqueofrontal == true && bloqueolateralizq == true && bloqueolateralder == true && PelotaenPosesion == false){
      Serial.println("Pelota encontrada!");
      movements.avanzar(50);
      delay(500);
      movements.neutro();
      //GARRA ON                                             <<<<=========
      PelotaenPosesion = true;
      movements.retroceder(50);
      delay(1000);
      movements.neutro();
      movements.derecha(50);
      delay(500);
      movements.neutro();
    }

    if(bloqueofrontal == true){
      Serial.println("Obstaculo físico detectado");
      movements.freno();
      delay(200);
      movements.neutro();
      movements.derecha(75);
      delay(500);
      movements.avanzar(100);
      delay(200);
      movements.neutro();
    }
    else{
      movements.avanzar(100);
    }
  }


  if (STAGE == 2 && Union == true){ //           CAMBIO ETAPA 1-2 Circuito B
    movements.avanzar(50);
    delay(200);
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
      movements.izquierda(30);
      delay(1000);
      movements.neutro();           /// QUEDAR VOLTEANDO AL ESTE
      Rosa = "Este";
      
    }
    else if(Rosa == "Este" && bloqueofrontal == true){         //DAR LA VUELTA PARA DEVOLVERSE
      movements.izquierda(30);
      delay(2000);
      movements.neutro();
      Rosa = "Oeste";
      delay(200);
    }
    else if(Rosa == "Este" && bloqueofrontal == false && Procesosalida == false){
      movements.izquierda(30);
      delay(1200);
      movements.neutro();
      Rosa = "Norte";
      delay(200);
    }
    else if(Rosa == "Oeste" && bloqueofrontal == true){             //VOLTEAR AL FRENTE PARA CONTINUAR
      movements.derecha(30);
      delay(1000);
      movements.neutro();
      Rosa = "Norte";
      delay(200);
    }
    else if(Rosa == "Norte" && bloqueoIR == true && Procesosalida == false){           // DETECTAR BARRERA IR Y SEGUIR BUSCANDO
      movements.freno();
      delay(200);
      movements.retroceder(50);
      delay(500);
      movements.neutro();
      movements.derecha(100);
      delay(500);
      movements.neutro();
      Rosa = "Este";
      movements.avanzar(50);
      delay(500);//                                 <<<==== 16 CENTIMETROS
      movements.neutro();
    }
    else if(Procesosalida == true && Rosa == "Este" && bloqueolateralizq == false){
      delay(200);
      movements.izquierda(50);
      delay(500);
      movements.neutro();
      Rosa = "Norte";
      Serial.println("Salida encontrada! :D");
      movements.avanzar(50);
      delay(500);
      movements.neutro();
      STAGE = 3; //Cambio de etapa
      Union = true;
    }
    else if(Rosa == "Norte" && bloqueoIR == false && bloqueofrontal == false){ // Avanzar normal
      movements.avanzar(50);
    }
    
  }
  


  if(STAGE == 3 && Union == true){ //           CAMBIO ETAPA 2-3 Circuito B
    movements.avanzar(50);
    delay(200);
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
    float red, green, blue;
    //// tcs.getRGB(&red, &green, &blue);
    //// tcs.setInterrupt(false);

    //// Serial.print("R:\t"); Serial.print(int(red));
    //// Serial.print("\tG:\t"); Serial.print(int(green));
    //// Serial.print("\tB:\t"); Serial.print(int(blue));
    Serial.print("\n");
    //*/
    analogWrite(redpin, gammatable[(int)constrain(red, 0, 255)]);
    analogWrite(greenpin, gammatable[(int)constrain(green, 0, 255)]);
    analogWrite(bluepin, gammatable[(int)constrain(blue, 0, 255)]);


    // Calculo de porcentaje de cada color
    float sumaTotal = red + green + blue + 1.0;
    float rNorm = (red / sumaTotal) * 100.0;
    float gNorm = (green / sumaTotal) * 100.0;
    float bNorm = (blue / sumaTotal) * 100.0;

    //Corroborar colores (supervisión)
    Serial.print("R_norm: "); Serial.print(rNorm);
    Serial.print(" | G_norm: "); Serial.print(gNorm);
    Serial.print(" | B_norm: "); Serial.println(bNorm);

    //Interpretación de colores según porcentaje de cada color
    if (rNorm > 45.0 && gNorm > 30.0 && bNorm < 25.0) {
      Color = "Naranja";     // Predomina Rojo y Verde moderado
    } 
    else if (gNorm > 35.0 && bNorm > 30.0 && rNorm < 30.0) {
      Color = "Celeste";     // Predomina Verde y Azul alto
    } 
    else if (rNorm > 40.0 && bNorm > 30.0 && gNorm < 25.0) {
      Color = "Rosa";        // Predomina Rojo y Azul con poco verde
    } 
    else if (rNorm > 35.0 && gNorm > 35.0 && bNorm < 20.0) {
      Color = "Amarrillo";   // Rojo y Verde altos (mezcla para amarillo)
    }

    ////// DELIMITAR RANGOS DE COLORES PARA DETECTAR CUAL ES EL COLOR CORRECTO Y LA ACCIÓN POR HACER


    //Action detection
    if(Color == "Naranja"){
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

    // Actions
    if(Traduccion_lectura < direccion){
      movements.izquierda(100);
      delay(500);
      movements.neutro();
      direccion--;
    }
    else if(Traduccion_lectura > direccion){
      movements.derecha(100);
      delay(500);
      movements.neutro();
      direccion++;
    }
    else if(Traduccion_lectura == direccion){
      movements.avanzar(100);
      delay(500);//                                <<<==== Ajustar a una casilla
      movements.neutro();
    }

  }

}
