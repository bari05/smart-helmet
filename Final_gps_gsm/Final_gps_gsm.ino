/*
  ### Send SMS messages
  1. This example is used to test DFRobot_SIM808 GPS/GPRS/GSM Shield's send SMS func.
  2. Open the SIM808_SendSMS example or copy these code to your project
  3. Replace the phoneNumber：#define PHONE_NUMBER  "187******39"
  4. Download and dial the function switch to Arduino, and enjoy it

  create on 2016/09/23, version: 1.0
  by jason
*/
#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>
#include <String.h>

//Mobile phone number,need to change
#define PHONE_NUMBER "01756500104"
#define leftPin 5
#define frontPin 4
#define rightPin 3
#define stopPin 6


SoftwareSerial Blue(10,11); //rx, tx

//The content of messages sent

const byte emergencyPin = 2;
volatile byte state = LOW;

DFRobot_SIM808 sim808(&Serial);

void setup() {
  //mySerial.begin(9600);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(6,OUTPUT);
  
  Serial.begin(9600);
  Blue.begin(9600);

  //******** Initialize sim808 module *************
  while (!sim808.init()) {
    delay(1000);
    Serial.print("Sim808 init error\r\n");
  }
  //************* Turn on the GPS power************
  if ( sim808.attachGPS())
    Serial.println("Open the GPS power success");
  else
    Serial.println("Open the GPS power failure");
  //
  pinMode(emergencyPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(emergencyPin), emergencyPressed, HIGH);

  Serial.println("Setup Done");
  //******** define phone number and text **********

}

void loop() {
  if(digitalRead(leftPin)==HIGH){
    Blue.write('0');
    Serial.println("Left Button pressed");
  }
  if(digitalRead(frontPin)==HIGH){
    Blue.write('2');
    Serial.println("Front Button pressed");
  }
  if(digitalRead(rightPin)==HIGH){
    Blue.write('1');
    Serial.println("Right Button pressed");
  }
  if(digitalRead(stopPin)==HIGH){
    Blue.write('3');
    Serial.println("Stop Button pressed");
  }
  if (state == HIGH) {
    while (true) {
      //Serial.println("Inside Emergency Loop");
      if (sim808.getGPS()) {
        String url = "I am in danger! Here is my location. Help me! https://maps.google.com/?q=";
       
        url = url + sim808.GPSdata.lat + "," + sim808.GPSdata.lon;
        Serial.println(url);

        Serial.print("speed_kph :");
        Serial.println(sim808.GPSdata.speed_kph);
        Serial.print("heading :");
        Serial.println(sim808.GPSdata.heading);

        //************* Turn off the GPS power ************
        sim808.detachGPS();
        char urlToSend[url.length()];
        strcpy(urlToSend,url.c_str());
        //sim808.sendSMS(PHONE_NUMBER, urlToSend);
        Serial.println("Done"+url);
        state = LOW;
        break;
      }
    }

  }
}

void emergencyPressed() {
  state = HIGH;
  Serial.println("Imergency button Pressed");
}
