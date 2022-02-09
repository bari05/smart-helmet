
#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>
#include <String.h>

#define PHONE_NUMBER "01756500104"
#define leftPin 5
#define frontPin 4
#define rightPin 3
#define stopPin 6
#define emergencyPin 2

SoftwareSerial Blue(10, 11); //rx, tx

DFRobot_SIM808 sim808(&Serial);
String url = "I am in danger! HELP ME !!! Here is my location: https://maps.google.com/?q=";
String replySMS = "Here is my location: https://maps.google.com/?q=";
char urlToSend[200];

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  Serial.begin(9600);
  Blue.begin(9600);

  //******** Initialize sim808 module *************
  while (!sim808.init()) {
    delay(1000);
    Serial.print("Sim808 init error\r\n");
  }
  //************* Turn on the GPS power************
  if ( sim808.attachGPS())
    Serial.println("Starting GPS");
  else
    Serial.println("Open the GPS power failure");


  while (true) {
    if (sim808.getGPS()) {
      url = url + sim808.GPSdata.lat + "," + sim808.GPSdata.lon;
      replySMS = replySMS + sim808.GPSdata.lat + "," + sim808.GPSdata.lon;
      sim808.detachGPS();
      strcpy(urlToSend, url.c_str());
      //sim808.sendSMS(PHONE_NUMBER, urlToSend);
      break;
    }
  }
  Serial.println("Open the GPS power successfull");
}

void loop() {

  if (digitalRead(leftPin) == HIGH) {
    Blue.write('0');
    // Serial.println("Left Button pressed");
  }
  if (digitalRead(frontPin) == HIGH) {
    Blue.write('2');
    //Serial.println("Front Button pressed");
  }
  if (digitalRead(rightPin) == HIGH) {
    Blue.write('1');
    //  Serial.println("Right Button pressed");
  }
  if (digitalRead(stopPin) == HIGH) {
    Blue.write('3');
    // Serial.println("Stop Button pressed");
  }
  if (digitalRead(emergencyPin) == HIGH) {
    Serial.println("Emergency Button pressed");
    delay(2000);
    sim808.sendSMS(PHONE_NUMBER, urlToSend);
    delay(2000);
    Serial.println("Message Sent.");
  }
}
