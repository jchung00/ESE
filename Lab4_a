/* Finish the following code to set an RGB LED to ‘RED’ color when the distance (in cm) is in the range [0,6) and to ‘GREEN’ when the distance ranges between [6, 20). Print the distance on the serial monitor in 500ms intervals. Also print ‘Out of Range’ when the distance calculated doesn’t fall within either of the specified ranges.

Take a picture of your circuit after you have completed it to submit with the postlab!

Connect channel 2 of the oscilloscope to the ‘Trig’ pin, PIN 13, and channel 1 to ‘Echo’, PIN 12. Observe how the pulse width of the ‘Echo’ changes with distance as demonstrated in Fig 4 & Fig 5.*/

#define trigPin 13
#define echoPin 12
#define redPin 5
#define greenPin 6
void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}
void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // start trig at 0
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); //The rising edge of trig pulse
  delayMicroseconds(10); // decides duration of trig pulse
  digitalWrite(trigPin, LOW); //falling edge of the trig pulse
  // NOTE: echo pin reads HIGH till it receives the reflected signal
  duration = pulseIn(echoPin, HIGH);  // Reading the duration for which echoPin was HIGH gives        //you the time the sensor receives a reflected signal at the echo pin
  distance = (duration / 2) / 29.1;   //Calculate the distance of the reflecting surface in cm
  Serial.println(distance);
  if(distance >= 0 && distance < 6){
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
  }
  else if(distance >= 6 && distance < 20){
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
  }
  else{
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    Serial.println("Distance out of range");
  }
  delay(500);
 //TODO
}
