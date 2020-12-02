int moeda;

void setup() {
  pinMode(A0, INPUT);
  pinMode(53,OUTPUT);
  Serial.begin(9600);
  moeda = 0;
}

void loop() {
  //Serial.println(analogRead(A0));
  if(analogRead(A0) > 1010){
    digitalWrite(53,HIGH);
    moeda++;
    Serial.print("Tem ");
    Serial.print(moeda);
    Serial.println(" moedas.");
    delay(100);
    
  }else{
    digitalWrite(53,LOW);
  }
}
