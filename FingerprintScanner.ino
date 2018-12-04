#include "FPS_GT511C3.h"
#include "SoftwareSerial.h"

#include <SPI.h>
#include <WiFi101.h>
 
char ssid[] = "AirPennNet-Device"; //  your network SSID (name)
char pass[] = "penn1740wifi"; // your network password

int status = WL_IDLE_STATUS;

// Initialize the Wifi client library
WiFiClient client;

// ThingSpeak Settings
char server[] = "api.thingspeak.com";
String writeAPIKey = "1SWMTISZXF0A14E2";

unsigned long lastConnectionTime = 0; // track the last connection time
const unsigned long postingInterval = 40L * 1000L; // post data every 40 seconds

int tempval = 0;

// FPS (TX) is connected to pin 4 (Arduino's Software RX)
// FPS (RX) is connected through a converter to pin 5 (Arduino's Software TX)
FPS_GT511C3 fps(4, 5); // (Arduino SS_RX = pin 4, Arduino SS_TX = pin 5)

String s = "";
const int SWITCH = 8;
boolean isOn = true;

void setup()
{
  Serial.begin(9600); //set up Arduino's hardware serial UART
   while ( status != WL_CONNECTED) {
    Serial.println("Attempting to connect.");
    // Connect to WPA/WPA2 Wi-Fi network
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection
    delay(10000);
  }
  Serial.println("Wifi connected!");

  delay(100);
  //fps.UseSerialDebug = true;
  fps.Open();         //send serial command to initialize fps
  fps.SetLED(true);   //turn on LED so fps can see fingerprint
  pinMode(SWITCH, INPUT);
  Serial.println("System booting...");
}

void httpRequest(int id) {
  // read analog pin 5
  tempval = id;     // read the temperature sensor pin
  Serial.print(id);
  Serial.println(" will be marked as present");

  // create data string to send to ThingSpeak
  String data = String("field1=" + String(id, DEC)); 
  
  // close any connection before sending a new request
  client.stop();

  // POST data to ThingSpeak
  if (client.connect(server, 80)) {
    client.println("POST /update HTTP/1.1");
    client.println("Host: api.thingspeak.com");
    client.println("Connection: close");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("X-THINGSPEAKAPIKEY: "+writeAPIKey);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.print(data.length());
    client.print("\n\n");
    client.print(data);

    // note the last connection time
    lastConnectionTime = millis();
  }
}


void Enroll(String pennKey)
{
  int id = pennKey.toInt();
  // Enroll test
  fps.EnrollStart(id);

  // enroll
  Serial.print("Press finger to Enroll for: ");
  Serial.println(id);
  if(!fps.CheckEnrolled(id)){
    while(fps.IsPressFinger() == false) delay(100);
    bool bret = fps.CaptureFinger(true);
    int iret = 0;
    if (bret != false)
    {
      Serial.println("Remove finger");
      fps.Enroll1(); 
      while(fps.IsPressFinger() == true) delay(100);
      Serial.println("Press same finger again");
      while(fps.IsPressFinger() == false) delay(100);
      bret = fps.CaptureFinger(true);
      if (bret != false)
      {
        Serial.println("Remove finger");
        fps.Enroll2();
        while(fps.IsPressFinger() == true) delay(100);
        Serial.println("Press same finger yet again");
        while(fps.IsPressFinger() == false) delay(100);
        bret = fps.CaptureFinger(true);
        if (bret != false)
        {
          Serial.println("Remove finger");
          iret = fps.Enroll3();
          if (iret == 0)
          {
            Serial.println("Enrolling Successful");
          }
          else if(iret == 3){
            Serial.println("Fingerprint has already been registered under a different ID");
          }
          else
          {
            Serial.print("Enrolling Failed with error code:");
            Serial.println(iret);
          }
        }
        else Serial.println("Failed to capture third finger");
      }
      else Serial.println("Failed to capture second finger");
    }
    else Serial.println("Failed to capture first finger");
  }
  else{
    Serial.println("Penn ID has already been registered");
  }
}

void idFinger(){
  if (fps.IsPressFinger())
  {
    fps.CaptureFinger(false);
    int id = fps.Identify1_N();
    
       /*Note:  GT-521F52 can hold 3000 fingerprint templates
                GT-521F32 can hold 200 fingerprint templates
                 GT-511C3 can hold 200 fingerprint templates. 
                GT-511C1R can hold 20 fingerprint templates.
       Make sure to change the id depending on what
       model you are using */
    Serial.println("Read: ");
    Serial.println(id);
    if (id < 200) //<- change id value depending model you are using
    {//if the fingerprint matches, provide the matching template ID
      Serial.print("Verified ID:");
      Serial.println(id);
      httpRequest(id);
    }
    else
    {//if unable to recognize
      Serial.println("Finger not found");
    }
  }
  else
  {
    Serial.println("Please press finger");
  }
  delay(100);
}

void loop()
{
  if(isOn){
    fps.SetLED(true);
    Serial.println("Type Enroll or Attendance");
    String s = Serial.readString();
    if(s.equals("Enroll")){
      s = "";
      Serial.println("Enroll Mode: On");
      while(true){
        //isOn = digitalRead(SWITCH);
        Serial.println("Type in your Penn ID or type EXIT to exit Enroll Mode");
        delay(1000);
        String pennId = Serial.readString();
        Serial.print("Input: ");
        Serial.println(pennId);
        if(pennId.equals("EXIT")){
          break;
        }
        else if(!pennId.equals("")){
          Enroll(pennId);
          pennId = "";
        }
      }
    }
    else if(s.equals("Attendance")){
      s = "";
      Serial.println("Attendance Mode: On");
      while(true){
        //isOn = digitalRead(SWITCH);
        idFinger();
        delay(1000);
        Serial.println("Type EXIT to exit Attendance Mode");
        String command = Serial.readString();
        if(command.equals("EXIT")){
          break;
        }
      }
    }
    isOn = digitalRead(SWITCH);
  }
  else{
    Serial.println("Pausing...");
    fps.SetLED(false);
    isOn = digitalRead(SWITCH);
    delay(1000);
  }
}
