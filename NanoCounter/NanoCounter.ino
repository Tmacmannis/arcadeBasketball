#include <HCSR04.h>
#include <Wire.h>

#define SENSORPIN 12

// UltraSonicDistanceSensor distanceSensor(12, 13);  // Initialize sensor that uses digital pins 13 and 12.

bool shotMade = false;
int count;

int buttonState = 0;         // current state of the button
int lastButtonState = 0; 

unsigned long previousMillis = 0;

unsigned long buttonPressStart = 0;
unsigned long buttonPressEnd = 0;

int sensorState = 0, lastState=0;

void setup () {
    Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
    Wire.begin(8);                // join i2c bus with address #8
    Wire.onRequest(requestEvent); // register event

    pinMode(SENSORPIN, INPUT_PULLUP);
    
}

void loop () {
//    double distance = distanceSensor.measureDistanceCm();
    //delay(40);
    //Serial.println(distance);
//    if (distance < 5){
//      count++;
//      shotMade = true;
//      delay(150);
//      //Serial.println(count);
//      Serial.write("T");
//    }
//    else{
//      delay(40); 
//    }

//    if(digitalRead(5) == LOW){
//      count++;
//      shotMade = true;
//      Serial.write("T");
//    }

//     buttonState = digitalRead(12);
// //    Serial.println(buttonState);

//   // compare the buttonState to its previous state
//   if (buttonState != lastButtonState) {
//     // if the state has changed, increment the counter
//     if (buttonState == HIGH) {
//       // if the current state is HIGH then the button went from off to on:
//       //Serial.println("off");
//       buttonPressEnd = millis();
//       //Serial.print("time button pressed: ");
//       Serial.println(buttonPressEnd - buttonPressStart);
//     } else {
// //      Serial.write("T");
//       unsigned long currentMillis = millis();
//       //Serial.print("since last shot made: ");
//       //Serial.println(currentMillis - previousMillis);
//       buttonPressStart = millis();
//       if (currentMillis - previousMillis > 90) {
//         count++;
//         shotMade = true;
//         Serial.write("T");
//         //Serial.println("score!");
//       } else {
//         Serial.println("****************shot not counted!**************");
//       }
//       previousMillis = currentMillis;
      
// //      delay(100);
      
//     }
//     // Delay a little bit to avoid bouncing
//     delay(10);
//   }
//   // save the current state as the last state, for next time through the loop
//   lastButtonState = buttonState;


  sensorState = digitalRead(SENSORPIN);
 
  // check if the sensor beam is broken
  // if it is, the sensorState is LOW:
  if (sensorState == LOW) {     
    // turn LED on:
    //digitalWrite(LEDPIN, HIGH);  
  } 
  else {
    // turn LED off:
    //digitalWrite(LEDPIN, LOW); 
  }
  
  if (sensorState && !lastState) {
    Serial.println("Unbroken");
  } 
  if (!sensorState && lastState) {
    Serial.println("Broken");
    Serial.write("T");
  }
  lastState = sensorState;



}

void requestEvent() {
  if (shotMade){
    Wire.write("T");
    shotMade = false;
  } else{
    Wire.write("F");
  }
}
