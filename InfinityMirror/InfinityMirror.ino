#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 50

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 18
#define CLOCK_PIN 15

// Define the array of leds
CRGB leds[NUM_LEDS];
CRGB CurrentColor;

int buttonPin1 = 9;
int buttonPin2 = 8;
int buttonPin3 = 7;
int buttonPin4 = 6;
int buttonPin5 = 5;

int mode = 1;

void setup() { 
    // Uncomment/edit one of the following lines for your leds arrangement.
    FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RBG>(leds, NUM_LEDS);

  pinMode(buttonPin1,INPUT);
  pinMode(buttonPin2,INPUT);
  pinMode(buttonPin3,INPUT);
  pinMode(buttonPin4,INPUT);
  pinMode(buttonPin5,INPUT);
  
  digitalWrite(buttonPin1,HIGH);
  digitalWrite(buttonPin2,HIGH);
  digitalWrite(buttonPin3,HIGH);
  digitalWrite(buttonPin4,HIGH);
  digitalWrite(buttonPin5,HIGH);
}

void loop() { 
  int newmode = checkButtonPressed();

  if (newmode>0){
    mode=newmode;
    //initLEDs(mode);
  }

  switch (mode){
    case 1 : modeCycleRandomColors(); break;
  }
}

int checkButtonPressed(){
  int result = 0;

  for (int i=1; i <= 5; i++){
    switch(i){
      case 1 : if (checkButtonPressed2(buttonPin1)) result = i; break;
      case 2 : if (checkButtonPressed2(buttonPin2)) result = i; break;
      case 3 : if (checkButtonPressed2(buttonPin3)) result = i; break;
      case 4 : if (checkButtonPressed2(buttonPin4)) result = i; break;
      case 5 : if (checkButtonPressed2(buttonPin5)) result = i; break;
    }
  } 
  
  return result;
}
bool checkButtonPressed2(int pin){
  int result = false;

  if (digitalRead(pin)==LOW){
    result = true;
    digitalWrite(pin,HIGH);
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
