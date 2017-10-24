#include "BY8X01-16P.h"
#include "SoftwareSerial.h"
#define BY8X0116P_ENABLE_DEBUG_OUTPUT       1

const byte rxPin = 8;
const byte txPin = 9;
SoftwareSerial swSerial(rxPin, txPin);
BY8X0116P audioController(swSerial);




int step;

int greenPin=5;
int redPin=6;
int bluePin=3;
int whitePin=10;
int buttonPin=4;

float in, out;
unsigned int rgbColour[3];
int i,decColour,incColour = 0;
int numTracks;

const long cycleInterval = 20;
unsigned long prevCycleMillis,prevSoundCheckMillis = 0; 


void setup() {
  randomSeed(analogRead(0));
  
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin,HIGH);
  
  pinMode(rxPin, INPUT);          
  pinMode(txPin, OUTPUT);  
  
  swSerial.begin(9600);           // swSerial must be started first - only supported UART baud rate is 9600
  
  audioController.init(); 
  audioController.setEqualizerProfile(BY8X0116P_EqualizerProfile_Rock); 
  //audioController.setLoopPlaybackMode(BY8X0116P_LoopPlaybackMode_Random);
  audioController.setVolume(20);
  
  numTracks = 4;
  
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  pinMode(whitePin,OUTPUT);

  setColourRgb(0,0,0);
  
  rgbColour[0] = 255;
  rgbColour[1] = 0;
  rgbColour[2] = 0;

  while (true) {
    DoStuff();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //DoStuff();
}

void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void checkSoundStatus(){
  if (digitalRead(buttonPin) == LOW)
  {
    if (audioController.isPlaybackActive())
      audioController.stop(false);
    //audioController.play();
    int j = random(1, numTracks);
    audioController.playFileIndex(j);
    
    digitalWrite(buttonPin,HIGH);
    delay(100);
  }
}

void DoStuff(){
    unsigned long currentMillis = millis();
  
  //CycleRGB Start    
  if (currentMillis - prevCycleMillis >= cycleInterval) {
    if (i>=255) {
      i=0;
      decColour += 1;
    }
    
    if (i==0){
      if (decColour>2)
        decColour=0;

      if (decColour == 2) {
        incColour = 0;
      } else {
        incColour = decColour +1;
      }
    }

    rgbColour[decColour] -= 1;
    rgbColour[incColour] += 1;

    setColourRgb(rgbColour[0], rgbColour[1], rgbColour[2]);
    i += 1;
      
    prevCycleMillis = currentMillis;
  }  
  //CycleRGB End
  
  //CheckSound Start  
  checkSoundStatus();
  //CheckSound End
  
  //Pulse Start
  
  if (in>=6.283)
    in = 0;
      
  out = sin(in) * 127.5 + 127.5;
  analogWrite(whitePin,out);  
    
  in = in + 0.001;
  //Pulse End
}
