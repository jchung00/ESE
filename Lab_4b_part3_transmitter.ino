#include <SoftwareSerial.h>
SoftwareSerial  BTSerial(2, 3); //RX TX
const int b1 = 11;
const int b2 = 12;
const int b3 = 13;

void setup() {
  BTSerial.begin(9600); 
  Serial.begin(9600);
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
}

void loop() {
  int b1Val = digitalRead(b1);
  int b2Val = digitalRead(b2);
  int b3Val = digitalRead(b3);
  Serial.println("b1: " + b1Val);
  Serial.println("b2: " + b2Val);
  Serial.println("b3: " + b3Val);
  if(b1Val == 1 && b2Val == 0 && b3Val == 1){
    BTSerial.println("1");
  }
  else{
    BTSerial.println("0");
  }
  delay(500);
}
