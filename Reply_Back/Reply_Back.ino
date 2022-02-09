
#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>
#include <String.h>

#define MESSAGE_LENGTH 160
#define messageToSend "Here is my location: https://maps.google.com/?q=23.57,90.22"

char message[MESSAGE_LENGTH];
int messageIndex = 0;
char phone[16];
char datetime[24];

DFRobot_SIM808 sim808(&Serial);

void setup() {
  Serial.begin(9600);

  //******** Initialize sim808 module *************
  while(!sim808.init()) {
      Serial.print("Sim808 init error\r\n");
      delay(1000);
  }
  delay(3000);  
}

void loop() {
  //*********** Detecting unread SMS ************************
   messageIndex = sim808.isSMSunread();
   if (messageIndex > 0) { 
      sim808.readSMS(messageIndex, message, MESSAGE_LENGTH, phone, datetime);
      sim808.deleteSMS(messageIndex);
      Serial.println(message);
      if (strstr (message,"location") != NULL){
        Serial.println("keyword matched");
        delay(3000);
        sim808.sendSMS(phone,messageToSend);
        delay(3000);
        Serial.println("location Sent");
      }
   }
}
