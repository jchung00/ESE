#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); //RX TX
String outString =""; //this stores incoming string from the master
boolean stringComplete = false; //to indicate when the string is completed
const int LED = 8;
int val = 0;

void setup() {
  BTSerial.begin(9600); //begin bluetooth communication
  Serial.begin(9600); //begin serial communication
  outString.reserve(10); //reserve the length of string
  pinMode(LED, OUTPUT);
}

void loop() {
  if (BTSerial.available()) {
    char inChar = (char) BTSerial.read(); //reads single character at a time
    outString += inChar; //appends character to outString
    if (inChar == '\n') { //check for newline character to know if the string is 
      stringComplete = true;  //complete or not
    }
  }
  if (stringComplete) {
    Serial.println(outString);
    val = outString.toInt();
    if(val == 1){
      Serial.println("case 1");
      digitalWrite(LED, HIGH);
    }
    else{
      Serial.println("case 2");
      digitalWrite(LED, LOW);
    }
    outString = ""; //clear this string to store new characters
    stringComplete = false;
  }
}
