// Example sketch for reading values from ADC and printing to //Serial Monitor 
int photopin = 0; // variable to store analog pin number
const static int LED = 12;
void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(photopin, INPUT);    // initialize photopin as
}
void loop() {
    int pinValue = analogRead(photopin); // read and store
  //value from ADC 
    Serial.print("Value= ");
    Serial.println(pinValue);
    if(pinValue > 650){
      //Serial.println("hello");
      digitalWrite(LED, HIGH);
    }
    else{
      digitalWrite(LED, LOW);
    }
    delay(500); // To make the values more readable when looping
}
