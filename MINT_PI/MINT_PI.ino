//Bibliotecas
#include <stdlib.h>
#include <Servo.h>

//Pinos utilizados pelos infravermelhos (moedas_contagem das moedas)
#define iv010 A0
#define iv020 A1
#define iv100 A2
#define iv050 A3
#define iv200 A4

//Pinos utilizados pelos servos (devolução de moedas)
#define servo010 12
#define servo020 11
#define servo100 10
#define servo050 9
#define servo200 8

//Criação de objetos do tipo servo e variáveis dos servos
Servo S010;
Servo S020;
Servo S050;
Servo S100;
Servo S200;
int servo_pos010, servo_pos020, servo_pos050, servo_pos100, servo_pos200;
bool moedas_saida;

//Variáveis utilizadas na moedas_contagem de moedas
float moedas_contagem = 0;
float moedas_100 = 0, moedas_200 = 0, moedas_050 = 0, moedas_020 = 0, moedas_010 = 0;
bool moedas_entrada = false;

//Protótipos de funções
void contar_moedas();
void dar_moedas();

//!!!!!!!! D&BUGS !!!!!!!!!!!!!!!!
String servo_sinal, demo_geral, demo_moedas;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//############## SETUP ############################################################
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
  S010.attach(servo010);
  S010.write(0);
  S020.attach(servo020);
  S020.write(0);
  S050.attach(servo050);
  S050.write(0);
  S100.attach(servo100);
  S100.write(0);
  S200.attach(servo200);
  S200.write(0);

}

//############## LOOP ###########################################################3
void loop() {

  Serial.println("MENU PRINCIPAL");
  //====== DEMO ===============================
  demo_geral = Serial.readString();
  if (demo_geral == "DEPOSITAR") {
    moedas_entrada = true;
  } else if (demo_geral == "LEVANTAR") {
    moedas_saida = true;
  }

  //====== RECEBER MOEDAS ======================
  if (moedas_entrada == true) {
    contar_moedas();
  }

  //====== DAR MOEDAS ==========================
  if (moedas_saida == true) {
    dar_moedas();
  }

}


//############## FUNÇÕES ###############################################################
//Função chamada para contar moedas depositadas
void contar_moedas() {
  Serial.println("A RECEBER DINHEIRO");
  while (moedas_entrada == true) {
    //====== RECEBER MOEDAS ======================
    //Sensor dos 0.10€ ativado (passou moeda)
    if (analogRead(iv010) >= 1010) {
      moedas_010 += 0.10;
      delay(100);
    }
    //Sensor dos 0.20€ ativado (passou moeda)
    if (analogRead(iv020) >= 1010) {
      moedas_020 += 0.20;
      delay(100);
    }
    //Sensor dos 0.50€ ativado (passou moeda)
    if (analogRead(iv050) >= 1010) {
      moedas_050 += 0.50;
      delay(100);
    }
    //Sensor dos 1.00€ ativado (passou moeda)
    if (analogRead(iv100) >= 1010) {
      moedas_100 += 1.00;
      delay(100);
    }
    //Sensor dos 2.00€ ativado (passou moeda)
    if (analogRead(iv200) >= 1010) {
      moedas_200 += 2.00;
      delay(100);
    }

    //====== MOSTRAR RESULTADOS ======================
    //Atualizar contagem
    moedas_contagem = moedas_100 + moedas_200 + moedas_050 + moedas_020 + moedas_010;

    //Mostrar total atual
    Serial.print("Montante acumulado: ");
    Serial.print(moedas_contagem);
    Serial.println(" €");

    if (Serial.available() > 0){
      demo_moedas = Serial.readString();
    }

    if (demo_moedas == "STOP_IN") {
      moedas_entrada = false;
    }
  }
  return;
}

//Função chamada para contar moedas levantadas
void dar_moedas() {
  Serial.println("A DAR DINHEIRO");

  Serial.println("\nSelecione dinheiro a dar:");
  Serial.println("1 -> 0.10€");
  Serial.println("2 -> 0.20€");
  Serial.println("3 -> 0.50€");
  Serial.println("4 -> 1.00€");
  Serial.println("5 -> 2.00€\n");

  while(moedas_saida){
    servo_sinal = Serial.readString();
    //====== DAR MOEDAS ======================
    //Servo dos 0.10€ ativado (dar moeda)
    if (servo_sinal == "1") {
      Serial.println("A dar moeda de 0.10€");
      S010.write(180);
      delay(500);
      S010.write(0);
      moedas_010 -= 0.10;
    }
    //Servo dos 0.20€ ativado (dar moeda)
    if (servo_sinal == "2") {
      Serial.println("A dar moeda de 0.20€");
      S020.write(180);
      delay(500);
      S020.write(0);
      moedas_020 -= 0.20;
    }
    //Servo dos 0.50€ ativado (dar moeda)
    if (servo_sinal == "3") {
      Serial.println("A dar moeda de 0.50€");
      S050.write(180);
      delay(500);
      S050.write(0);
      moedas_050 -= 0.50;
    }
    //Servo dos 1.00€ ativado (dar moeda)
    if (servo_sinal == "4") {
      Serial.println("A dar moeda de 1.00€");
      S100.write(180);
      delay(500);
      S100.write(0);
      moedas_100 -= 1.00;
    }
    //Servo dos 2.00€ ativado (dar moeda)
    if (servo_sinal == "5") {
      Serial.println("A dar moeda de 2.00€");
      S200.write(180);
      delay(500);
      S200.write(0);
      moedas_200 -= 2.00;
    }


    //====== MOSTRAR RESULTADOS ======================
    //Atualizar contagem
    moedas_contagem = moedas_100 + moedas_200 + moedas_050 + moedas_020 + moedas_010;

    //Mostrar total atual
    Serial.print("Montante acumulado: ");
    Serial.print(moedas_contagem);
    Serial.println(" €");

    if (servo_sinal == "STOP_OUT" || moedas_contagem == 0) {
      moedas_saida = false;
    }
  }
  return;
}
