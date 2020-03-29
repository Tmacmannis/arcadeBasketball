//We always have to include the library
#include "LedControl.h"
#include <EEPROM.h>
#include <Wire.h>

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
 
LedControl lc=LedControl(12,11,10,1);
boolean on = false;
volatile int score = 0;

int currentGameScore = 0;
int highScore = 0;
int currentGameTime = 15;
long previousGameTime = 0;
long previousScoreTime = 0;
unsigned long delaytime=1000;
unsigned long scoreCheckDelay =10;
boolean gameLive = false;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  lc.shutdown(0,false);
  lc.setScanLimit(0,5);
  lc.setIntensity(0,15);
  lc.clearDisplay(0);

  delay(100);
  highScore = EEPROM.read(0);
  Serial.println(highScore);
  
  //set digits at start
  printMaxScore(highScore);
  printScore(0);
  printTime(currentGameTime);

  delay(1000);
  //*******************
}

void loop() { 

  checkGameTime();
  checkForScore();
  checkGameState();
//  delay(10);
    
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
    currentGameTime = 15;
    currentGameScore = 0;
    printMaxScore(highScore);
    printScore(0);
    printTime(currentGameTime);
  }
}

void checkForScore(){
//  if (Serial.available() > 0) {
//    Serial.read();
//    currentGameScore = currentGameScore + 2;
//    printScore(currentGameScore);
//  }
  //Serial.println("test");
  unsigned long currentMillis = millis();
  if (currentMillis - previousScoreTime >= scoreCheckDelay){
    Serial.println("test");
    previousScoreTime = currentMillis;
    Wire.requestFrom(8, 1);    // request 6 bytes from slave device #8
    while (Wire.available()) { // slave may send less than requested
      char c = Wire.read(); // receive a byte as character
      Serial.print(c);
      if (c == 'T'){
        currentGameScore = currentGameScore + 2;
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
      EEPROM.write(0, highScore);
    }
  }
}
