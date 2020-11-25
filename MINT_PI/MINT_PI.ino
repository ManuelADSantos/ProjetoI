//Biblioteca dos servos
#include <Servo.h>

//Pinos utilizados pelos infravermelhos (contagem das moedas)
#define iv010 A0
#define iv020 A1
#define iv100 A2
#define iv050 A3
#define iv200 A4

////Pinos utilizados pelos servos (devolução de moedas)
//#define servo010 12
//#define servo020 11
//#define servo100 10
//#define servo050 9
//#define servo200 8
//
////Criação de objetos do tipo servo e variáveis de posição dos servos
//Servo S010;
//Servo S020;
//Servo S050;
//Servo S100;
//Servo S200;
//int pos010, pos020, pos050, pos100, pos200;

//Variáveis utilizadas na contagem de moedas
float contagem = 0;
float um = 0;
float dois = 0;
float cinq = 0;
float vinte = 0;
float dez = 0;


//====== SETUP =============================================================
void setup()
{
  Serial.begin(9600);

  //Setup dos infravermelhos
  pinMode(iv010, INPUT);
  pinMode(iv020, INPUT);
  pinMode(iv100, INPUT);
  pinMode(iv050, INPUT);
  pinMode(iv200, INPUT);

  //Setup dos servos
//  S010.attach(servo010);
//  S010.write(0);
//  S020.attach(servo020);
//  S020.write(0);
//  S050.attach(servo050);
//  S050.write(0);
//  S100.attach(servo100);
//  S100.write(0);
//  S200.attach(servo200);
//  S200.write(0);
//  
}

//====== LOOP =============================================================
void loop() {

  //====== CONTAGEM DE MOEDAS ======================
  //Sensor dos 0.10€ ativado (passou moeda)
  if (analogRead(iv010) >= 1010) {
    dez += 0.10;
    delay(100);
  }
  //Sensor dos 0.20€ ativado (passou moeda)
  if (analogRead(iv020) >= 1010) {
    vinte += 0.20;
    delay(100);
  }
  //Sensor dos 0.50€ ativado (passou moeda)
  if (analogRead(iv050) >= 1010) {
    cinq += 0.50;
    delay(100);
  }
  //Sensor dos 1.00€ ativado (passou moeda)
  if (analogRead(iv100) >= 1010) {
    um += 1.00;
    delay(100);
  }
  //Sensor dos 2.00€ ativado (passou moeda)
  if (analogRead(iv200) >= 1010) {
    dois += 2.00;
    delay(100);
  }

  //====== DEVOLUÇÃO DE MOEDAS ======================
  //Servo dos 0.10€ ativado (dar moeda)
//  if (analogRead(iv010) < 100) {
//    dez += 0.10;
//  }
//  //Servo dos 0.20€ ativado (dar moeda)
//  if (analogRead(iv020) < 100) {
//    vinte += 0.20;
//  }
//  //Servo dos 0.50€ ativado (dar moeda)
//  if (analogRead(iv050) < 100) {
//    cinq += 0.50;
//  }
//  //Servo dos 1.00€ ativado (dar moeda)
//  if (analogRead(iv100) < 100) {
//    um += 1.00;
//  }
//  //Servo dos 2.00€ ativado (dar moeda)
//  if (analogRead(iv200) < 100) {
//    dois += 2.00;
//  }
  

  //====== MOSTRAR RESULTADOS ======================
  //Atualizar total
  contagem = um + dois + cinq + vinte + dez;

  //Mostrar total atual
  Serial.print("Montante acumulado: ");
  Serial.print(contagem);
  Serial.println(" €");
}
