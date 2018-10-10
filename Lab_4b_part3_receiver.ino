#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); //RX TX
String outString1 =""; //this stores incoming string from the master
String outString2 ="";
String outString3 ="";
boolean stringComplete1 = false; //to indicate when the string is completed
const int LED = 8;
int val = 0;
void setup() {
  BTSerial.begin(9600); //begin bluetooth communication
  Serial.begin(9600); //begin serial communication
  outString1.reserve(10); //reserve the length of string
  outString2.reserve(10);
  outString3.reserve(10);
  pinMode(LED, OUTPUT);
}

void loop() {
  if (BTSerial.available()) {
    char inChar1 = (char) BTSerial.read(); //reads single character at a time
    outString1 += inChar; //appends character to outString
    if (inChar1 == '\n') { //check for newline character to know if the string is 
      stringComplete1 = true;  //complete or not
      char inChar2 = (char) BTSerial.read();
      outString2 += inChar2;
      if (inChar2 == '\n') {
        stringComplete2 = true;
        inChar3 = (char) BTSerial.read();
        outString3 += inChar3;
        if(inChar3 == '\n'){
          stringComplete3 = true;
        }
      }
    }
  }
  if (stringComplete1 && stringComplete2 && stringComplete3) {
    val1 = outString1.toInt();
    val2 = outString2.toInt();
    val3 = outString3.toInt();
    if(val1 == 0 && val2 == 1 && val3 == 0){
      digitalWrite(LED, HIGH);
    }
    else{
      digitalWrite(LED, LOW);
    }
    // clear the string:
    outString1 = ""; //clear this string to store new characters
    outString2 = "";
    outString3 = "";
    stringComplete1 = false;
    stringComplete2 = false;
    stringComplete3 = false;
  }
}
