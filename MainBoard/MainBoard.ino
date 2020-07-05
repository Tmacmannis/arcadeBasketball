//We always have to include the library
#include "LedControl.h"
#include <EEPROM.h>
#include <Wire.h>
#include <Audio.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN

//*******************************
//Audio Setup
AudioPlaySdWav     playWav1;
AudioPlaySdWav     playWav2;
AudioPlaySdWav     playWav3;
AudioPlaySdWav     playWav4;
AudioMixer4        mix1;
AudioOutputI2S     headphones;
AudioOutputAnalog  dac;     // play to both I2S audio board and on-chip DAC

AudioConnection c1(playWav1, 0, mix1, 0);
AudioConnection c2(playWav2, 0, mix1, 1);
AudioConnection c3(playWav3, 0, mix1, 2);
AudioConnection c4(playWav4, 0, mix1, 3);
AudioConnection c5(mix1, 0, headphones, 0);
AudioConnection c6(mix1, 0, headphones, 1);
AudioConnection c10(mix1, 0, dac, 0);

AudioControlSGTL5000 audioShield;

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14
//*******************************
 
LedControl lc=LedControl(4,3,2,1);
boolean on = false;
volatile int score = 0;

int currentGameScore = 0;
int highScore = 0;
int currentGameTime = 30;
long previousGameTime = 0;
long previousScoreTime = 0;
unsigned long delaytime=1000;
unsigned long scoreCheckDelay =10;
boolean gameLive = false;

void setup() {
  
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(13, OUTPUT);
  lc.shutdown(0,false);
  lc.setScanLimit(0,5);
  lc.setIntensity(0,15);
  lc.clearDisplay(0);

  pinMode(5, INPUT_PULLUP);

  delay(100);
  highScore = EEPROM.read(0);
  Serial.println(highScore);
  
  //set digits at start
  printMaxScore(highScore);
  printScore(0);
  printTime(currentGameTime);

  //*******************************
  //Audio setup
  AudioMemory(10);
  audioShield.enable();
  audioShield.volume(1.0);
  
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  
  //*******************************

  delay(1000);
  //*******************
}

void loop() { 
	
  checkGameTime();
  checkForScore();
  checkGameState();
  checkResetScoreButton();
}



void checkGameTime(){
  unsigned long currentMillis = millis();
  if ((currentMillis - previousGameTime >= delaytime) && currentGameTime >= 0 && gameLive){
    previousGameTime = currentMillis;
    printTime(currentGameTime);
    currentGameTime--;
  }

  if (currentGameTime < 0){
    gameLive = false;
    currentGameTime = 30;
    //currentGameScore = 0;
    playWav2.play("BUZZER.WAV");
    printMaxScore(highScore);
    checkGameState();
    delay(5000);
    printScore(0);
    printTime(currentGameTime);
    serialFlush();
  }
}

void checkForScore(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousScoreTime >= scoreCheckDelay){
    previousScoreTime = currentMillis;

    if (Serial1.available() > 0) {
      char c = Serial1.read();
      Serial.println(c);
      if (c == 'T'){
      	if(currentGameTime < 10){
      		currentGameScore = currentGameScore + 3;
      	} else{
      		currentGameScore = currentGameScore + 2;
      	}
        
        playWav1.play("Swish.WAV");
        printScore(currentGameScore);
        if (!gameLive){
          gameLive = true;
        }
      }
    }
  }
}

void checkGameState(){
  if (!gameLive){
    if(currentGameScore > highScore){
      highScore = currentGameScore;
      printMaxScore(highScore);
      Serial.println("print high score");
      EEPROM.write(0, highScore);
    }
    currentGameScore = 0;
  }
}

void checkResetScoreButton(){
	if(digitalRead(5) == LOW){
		highScore = 0;
		EEPROM.write(0, 0);
		printMaxScore(0);
	}
}

void serialFlush(){
  while(Serial1.available() > 0) {
    char t = Serial1.read();
  }
}  
