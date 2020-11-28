/*  S2 |  S3  | Photodiode Type
   LOW | LOW  | vermelho
   LOW | HIGH | azul
   HIGH| LOW  | clear
   HIGH| HIGH | verde
*/
 
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
#define R 9
#define G 10
#define B 11

//// Frequências lidas pelos fotodiodos
int frequencyR = 0, frequencyG = 0 , frequencyB=0, red, green, blue;

float total=0, cinco = 0, dez = 0, vinte = 0;

void setup() {
  
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  //Frequency-scaling a 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);

  //LED RGB para testes
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
}

void loop() {
  
  //----------------------------------------------- VERMELHO -------------------------------------------------------------------------
  
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Ler a frequência de saída - vermelho
  frequencyR = pulseIn(sensorOut, LOW);
  
  //analogWrite(LED_R,map(Red,42,366,255,0)); 366, 42, 0, 255
  
  
  red = map(frequencyR,366, 42, 0, 255);
  Serial.print("R= ");
  Serial.print(red);
  Serial.print("  ");
  delay(500);

  //----------------------------------------------------------VERDE------------------------------------------------------------------
  
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  //  Ler a frequência de saída - verde
  frequencyG = pulseIn(sensorOut, LOW);
  
  //analogWrite(LED_G,map(Green,62,359,0,255)); 359, 62, 0, 255
  
  green = map(frequencyG,359, 62, 0, 255 );  
  Serial.print("G= ");
  Serial.print(green);
  Serial.print("  ");
  delay(500);

  //------------------------------------------------------------AZUL---------------------------------------------------------------------
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // Ler a frequência de saída - azul
  frequencyB = pulseIn(sensorOut, LOW);
  
  // analogWrite(LED_B,map(Blue,101,244,0,255)); 244, 101, 0, 255
  blue = map(frequencyB,244, 101, 0, 255);
  
  Serial.print("B= ");
  Serial.print(blue);
  Serial.println("  ");
  delay(500);

  delay (2000);
  //--------------------------------------------------------------RGB e testes-----------------------------------------------------------

   //Verifica qual é a cor detetada

  if(red > green && red > blue){
      Serial.println(" - VERMELHO detetado!");
      digitalWrite(R, HIGH);
      digitalWrite(G, LOW);
      digitalWrite(B, LOW);
      cinco += 5.00;
      
  }
  if(green > red && green > blue){
    Serial.println(" - VERDE detetado!");
     digitalWrite(G,HIGH);
     digitalWrite(R, LOW);
     digitalWrite(B, LOW);
     dez += 10.00;
  }
  if(blue > red && blue > green){
    Serial.println(" - AZUL detetado!");
    digitalWrite(B, HIGH);
    digitalWrite(R, LOW);
    digitalWrite(G, LOW);
    vinte += 20.00;
    
  }

  /*digitalWrite(R, red);
  digitalWrite(G,green);
  digitalWrite(B, blue);*/

  total= cinco + dez + vinte;

  //Mostrar total atual
  Serial.print("Montante acumulado: ");
  Serial.print(total);
  Serial.println(" €");

}
