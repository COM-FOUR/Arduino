#include "FastLED.h"
#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

// How many leds in your strip?
#define NUM_LEDS 50

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 18
#define CLOCK_PIN 15
#define RECV_PIN 11

// Define the array of leds
CRGB leds[NUM_LEDS];
CRGB CurrentColor;

IRrecv irrecv(RECV_PIN);
decode_results results;

int mode = 1;

void setup() { 
    irrecv.enableIRIn(); // Start the receiver
      
    // Uncomment/edit one of the following lines for your leds arrangement.
    FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RBG>(leds, NUM_LEDS);
}

void loop() { 
  int newmode = checkIR();

  if (newmode>0){
    mode=newmode;
    //initLEDs(mode);
  }

  switch (mode){
    case 1 : modeCycleRandomColors(); break;
  }
}

int checkIR(){
  int result = 0;

  if (irrecv.decode(&results)) {
      
      switch (results.value){
        case 1 : result = 1; break;
        case 2 : result = 2; break;
        case 3 : result = 3; break;
      }
      
      irrecv.resume(); // Receive the next value
  }
  
  return result;
}

void modeCycleRandomColors(){
  randomSeed(analogRead(0));
  int rnd = random(1,9);
  
  switch (rnd){
    case 1 :
    case 2 :
    case 3 : CurrentColor = CRGB::Red ;break;
    case 4 :
    case 5 : 
    case 6 : CurrentColor = CRGB::Blue ;break;
    case 7 :
    case 8 :
    case 9 : CurrentColor = CRGB::Green ;break;
  }
  
  ShowColorOnAll(CurrentColor,1000);
  //ShowColorOnAll(CRGB::Black,0);
}

void ShowColorOnAll(CRGB color,int delayvalue){
  for (int i=0; i < NUM_LEDS; i++){
    leds[i] = color;
  }

  FastLED.show();
  delay(delayvalue);
}
//void initLEDs(int mode){
//  for (int i=0; i < NUM_LEDS; i++){
//    leds[i] = color;
//  }
//}
