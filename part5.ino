//Analog read pins for accelerometer
const int xPin = 0;
const int yPin = 1;
const int zPin = 2;

//PWM pins for RGB LED
int redPin = 11;
int greenPin = 10;
int bluePin = 9;

//The minimum and maximum values that came from
//the accelerometer while standing still
//You very well may need to change these
int minVal[3] = {340, 340, 420};
int maxVal[3] = {400, 500, 600};


void setup(){
 Serial.begin(9600); 
 
 //Set the PWM pins connected to RGB LED as output
 pinMode(redPin, OUTPUT);
 pinMode(greenPin, OUTPUT);
 pinMode(bluePin, OUTPUT); 
}

void loop(){

 //read the analog values from the accelerometer
 int xRead = analogRead(xPin);
 int yRead = analogRead(yPin);
 int zRead = analogRead(zPin);

 //Output read values to Serial monitor
 Serial.print("x: ");
 Serial.print(xRead);
 Serial.print(" | y: ");
 Serial.print(yRead);
 Serial.print(" | z: ");
 Serial.println(zRead);

 //The analogWrite takes a range from 0-255
 //map function converts a given range
 int red = map(xRead, minVal[0], maxVal[0], 0, 255); 
 int green = map(yRead, minVal[1], maxVal[1], 0, 255);
 int blue = map(zRead, minVal[2], maxVal[2], 0, 255);
 
 setColor(red, green, blue);
 delay(100); //slow down the serial display to be able to read easier
}

void setColor(int red, int green, int blue)
{

 analogWrite(redPin, red);
 analogWrite(greenPin, green);
 analogWrite(bluePin, blue);  
}
