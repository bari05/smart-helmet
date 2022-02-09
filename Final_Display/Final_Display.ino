// Including the required Arduino libraries
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Uncomment according to your hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// Defining size, and output pins
#define MAX_DEVICES 4
#define CS_PIN 10

// Create a new instance of the MD_Parola class with hardware SPI connection
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

int state=2;
void setup() {


  Serial.begin(9600);
  
  myDisplay.begin();

  // Set the intensity (brightness) of the display (0-15)
  myDisplay.setIntensity(1);

  // Clear the display
  myDisplay.displayClear();

  myDisplay.displayScroll("^ ^ ^ ^ ^", PA_CENTER, PA_SCROLL_UP, 70);
}

void loop() {
  //Serial.println("Not available");
  if (myDisplay.displayAnimate()) {
    myDisplay.displayReset();
  }
 if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    state = Serial.read(); // Reads the data from the serial port
  //Serial.println(state);
    if(state=='2'){
      myDisplay.displayClear();
      myDisplay.displayScroll("^ ^ ^ ^ ^", PA_CENTER, PA_SCROLL_UP, 75);
    }
    if(state=='3'){
      myDisplay.displayClear();
      myDisplay.displayText("STOP", PA_CENTER, 75, 100, PA_NO_EFFECT, PA_NO_EFFECT);
    }
    if(state=='0'){
      myDisplay.displayClear();
      myDisplay.displayScroll("< < < < < < < < < < < < < < < < < < < <", PA_CENTER, PA_SCROLL_LEFT, 75);
    }
    if(state=='1'){
      myDisplay.displayClear();
      myDisplay.displayScroll("> > > > > > > > > > > > > > > > > > > >", PA_CENTER, PA_SCROLL_RIGHT, 75);
    }
    Serial.println(state);
 }
}
