#include "FastLED.h"
#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

// How many leds in your strip?
#define NUM_LEDS 51

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 18
#define CLOCK_PIN 15
#define RECV_PIN 2

// Define the array of leds
CRGB leds[NUM_LEDS];
CRGB CurrentColor;

IRrecv irrecv(RECV_PIN);
decode_results results;

int mode = 0;
int prevmode = 0;

unsigned long previousMillis = 0; 
unsigned long interval = 1000; 

void setup() { 
    irrecv.enableIRIn(); // Start the receiver
      
    // Uncomment/edit one of the following lines for your leds arrangement.
    FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RBG>(leds, NUM_LEDS);
}

int checkIR(){
  int result = -1;

  if (irrecv.decode(&results)) {
      
      switch (results.value){
        case 16738455 : result = 0; break;
        case 16724175 : result = 1; break;
        case 16718055 : result = 2; break;
        case 16743045 : result = 3; break;
        case 16716015 : result = 4; break;
        case 16726215 : result = 5; break;
        case 16734885 : result = 6; break;
        case 16728765 : result = 7; break;
        case 16730805 : result = 8; break;
        case 16732845 : result = 9; break;
        case 16750695 : result = 10; break; //100+
        case 16756815 : result = 11; break; //200+
        case 16769055 : result = 12; break; //vol-
        case 16754775 : result = 13; break; //vol+
        case 16748655 : result = 14; break; //EQ
        case 16720605 : result = 15; break; //prev
        case 16712445 : result = 16; break; //next
        case 16761405 : result = 17; break; //playpause
        case 16753245 : result = 18; break; //ch- 
        case 16736925 : result = 19; break; //ch
        case 16769565 : result = 20; break; //ch+
        default : result = -1; break;
      }
      
      irrecv.resume(); // Receive the next value
  }
  
  return result;
}

void modeCycleRandomColors(){
  interval = 1000;
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    randomSeed(analogRead(0));
    int rnd = random(1,9);
  
    switch (rnd){
      case 1 : CurrentColor = CRGB::Crimson; break;
      case 2 : CurrentColor = CRGB::Yellow; break;
      case 3 : CurrentColor = CRGB::Red; break;
      case 4 : CurrentColor = CRGB::DarkOrange; break;
      case 5 : CurrentColor = CRGB::BlueViolet; break;
      case 6 : CurrentColor = CRGB::Blue; break;
      case 7 : CurrentColor = CRGB::Silver; break; 
      case 8 : CurrentColor = CRGB::Orange; break;
      case 9 : CurrentColor = CRGB::Green; break;
    }
  
    ShowColorOnAll(CurrentColor,0);

    previousMillis = currentMillis;
  }
}

void ShowColorOnAll(CRGB color,int delayvalue){
  for (int i=0; i < NUM_LEDS; i++){
    leds[i] = color;
  }

  FastLED.show();
  delay(delayvalue);
}

void loop() { 
  int newmode = checkIR();

  if (newmode>=0){
    mode=newmode;
    
    previousMillis = 0;
    
    switch (mode){
      case 0 : modeCycleRandomColors(); break;
      case 1 : ShowColorOnAll(CRGB::Red,0); break;
      case 2 : ShowColorOnAll(CRGB::Blue,0); break;
      case 3 : ShowColorOnAll(CRGB::Green,0); break;
      case 4 : ShowColorOnAll(CRGB::Violet,0); break;
      case 5 : ShowColorOnAll(CRGB::Yellow,0); break;
      case 6 : ShowColorOnAll(CRGB::Brown,0); break;
      case 7 : ShowColorOnAll(CRGB::Pink,0); break;
      case 8 : ShowColorOnAll(CRGB::Crimson,0); break;
      case 9 : ShowColorOnAll(CRGB::Orange,0); break;
      default : ShowColorOnAll(CRGB::Black,0); break;
    }
    prevmode = mode;  
  }

  if (mode==prevmode)
  {
    switch (mode){
      case 0 : modeCycleRandomColors(); break;
      //case 1 : ShowColorOnAll(CRGB::Red,0); break;    //  keine Änderungen benötigt
      //case 2 : ShowColorOnAll(CRGB::Blue,0); break;   //  keine Änderungen benötigt
      //case 3 : ShowColorOnAll(CRGB::Green,0); break;  //  keine Änderungen benötigt
      //default : ShowColorOnAll(CRGB::Black,0); break;   //  keine Änderungen benötigt
    } 
  }
  prevmode = mode;
}
