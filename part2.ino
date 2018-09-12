const static int LED = 12;
const static int LED2 = 10;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED2, LOW);
  delay(250);                       // wait for a second
  digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(LED2, HIGH);
  delay(250);                       // wait for a second
}
