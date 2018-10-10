#include <SoftwareSerial.h>
SoftwareSerial  BTSerial(2, 3); //TX RX
const int button = 12;
int val;

void setup() {
  BTSerial.begin(9600); 
  Serial.begin(9600);
  pinMode(button, INPUT);
}

void loop() {
  val = digitalRead(button);
  Serial.println(val);
  if(val == HIGH) {
    BTSerial.print("H");
    Serial.println("H");
  }
  else if(val == LOW) {
    BTSerial.print("L");
    Serial.println("L");
  }
  delay(100);
}
