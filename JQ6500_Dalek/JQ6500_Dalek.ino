#include <JQ6500_Serial.h>

JQ6500_Serial mp3(8,9);

int bluePin=16;
int bluePin2=14;
int whitePin=10;
int buttonPin1=4;
int buttonPin2=5;
int buttonPin3=6;
int buttonPin4=7;

bool pulseActive;
unsigned int numFiles; // Total number of files on media (autodetected in setup())

void setup() {
  
  mp3.begin(9600);
  mp3.reset();
  mp3.setVolume(25);
  mp3.setLoopMode(MP3_LOOP_NONE);
  mp3.setEqualizer(MP3_EQ_ROCK);
  numFiles = mp3.countFiles(MP3_SRC_BUILTIN);
  
  pinMode(bluePin,OUTPUT);
  digitalWrite(bluePin,HIGH);
  pinMode(bluePin2,OUTPUT);
  digitalWrite(bluePin2,HIGH);
  
  pinMode(whitePin,OUTPUT);

  pinMode(buttonPin1,INPUT);
  pinMode(buttonPin2,INPUT);
  pinMode(buttonPin3,INPUT);
  pinMode(buttonPin4,INPUT);

  digitalWrite(buttonPin1,HIGH);
  digitalWrite(buttonPin2,HIGH);
  digitalWrite(buttonPin3,HIGH);
  digitalWrite(buttonPin4,HIGH);
}

void loop() {
  switch (checkButtonPressed()){
    case 1 : playSpecificSound(1); break;
    case 2 : playSpecificSound(2); break;
    case 3 : playSpecificSound(3); break;
    case 4 : playRandomSound(); break;
  }

  if(mp3.getStatus() == MP3_STATUS_PLAYING){
    if (!pulseActive)
      doLEDPulse();
  } else {
    analogWrite(whitePin,0);
  }
}

void doLEDPulse(){
  pulseActive=true;
  float in, out;
  
  for (in = 0; in < 6.283; in = in + 0.05)
  {
    out = sin(in) * 127.5 + 127.5;
    analogWrite(whitePin,out);
  }
  pulseActive=false;
}

int checkButtonPressed(){
  int result = 0;

  for (int i=1; i <= 4; i++){
    switch(i){
      case 1 : if (checkButtonPressed2(buttonPin1)) result = i; break;
      case 2 : if (checkButtonPressed2(buttonPin2)) result = i; break;
      case 3 : if (checkButtonPressed2(buttonPin3)) result = i; break;
      case 4 : if (checkButtonPressed2(buttonPin4)) result = i; break;
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

void playSpecificSound(unsigned int indexNo)
{
  if(mp3.getStatus() == MP3_STATUS_PLAYING)
    mp3.pause();

  doLEDPulse();
  mp3.playFileByIndexNumber(indexNo);
  
}

void playRandomSound()
{
  if(mp3.getStatus() == MP3_STATUS_PLAYING)
    mp3.pause();
  
  unsigned int pick;
  do
  { 
    pick = random(1,numFiles+1);
  } while(pick == mp3.currentFileIndexNumber(MP3_SRC_BUILTIN));

  doLEDPulse();
  mp3.playFileByIndexNumber(pick);
  
}
