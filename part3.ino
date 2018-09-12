const static int LED = 10;
const static int btn1 = 5;
const static int btn2 = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(btn1) && digitalRead(btn2)){
    digitalWrite(LED, HIGH);
  }
  else{
    digitalWrite(LED, LOW);
  }
}
