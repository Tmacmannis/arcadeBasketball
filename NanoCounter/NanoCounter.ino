#include <HCSR04.h>
#include <Wire.h>

UltraSonicDistanceSensor distanceSensor(12, 13);  // Initialize sensor that uses digital pins 13 and 12.

bool shotMade = false;
int count;

int buttonState = 0;         // current state of the button
int lastButtonState = 0; 

void setup () {
    Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
    Wire.begin(8);                // join i2c bus with address #8
    Wire.onRequest(requestEvent); // register event

    pinMode(12, INPUT_PULLUP);
    
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

    buttonState = digitalRead(12);
//    Serial.println(buttonState);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      Serial.println("off");
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("shot made");
      count++;
      shotMade = true;
      Serial.write("T");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;
}

void requestEvent() {
  if (shotMade){
    Wire.write("T");
    shotMade = false;
  } else{
    Wire.write("F");
  }
}
