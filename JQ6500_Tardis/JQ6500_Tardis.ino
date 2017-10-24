#include <JQ6500_Serial.h>

JQ6500_Serial mp3(8,9);
int step;

int greenPin=5;
int redPin=6;
int bluePin=3;
int whitePin=10;

float in, out;
unsigned int rgbColour[3];
int i,decColour,incColour = 0;

const long cycleInterval = 20;
const long soundCheckInterval = 1000;
unsigned long prevCycleMillis,prevSoundCheckMillis = 0; 

void setup() {
  
  mp3.begin(9600);
  mp3.reset();
  mp3.setVolume(25);
  mp3.setLoopMode(MP3_LOOP_NONE);

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
  if (currentMillis - prevSoundCheckMillis >= soundCheckInterval) {
    checkSoundStatus();
    prevSoundCheckMillis = currentMillis;
  }  
  //CheckSound End
  
  //Pulse Start
  
  if (in>=6.283)
    in = 0;
      
  out = sin(in) * 127.5 + 127.5;
  analogWrite(whitePin,out);  
    
  in = in + 0.001;
  //Pulse End
}

void checkSoundStatus(){
  if(mp3.getStatus() != MP3_STATUS_PLAYING) {      
    if (step>=5)
      (step=0);     
      
    step++;
    mp3.playFileByIndexNumber(step);
  }
}

void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
