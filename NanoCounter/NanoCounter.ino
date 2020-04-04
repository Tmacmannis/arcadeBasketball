#include <HCSR04.h>
#include <Wire.h>

UltraSonicDistanceSensor distanceSensor(12, 13);  // Initialize sensor that uses digital pins 13 and 12.

bool shotMade = false;
int count;

void setup () {
    Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
    Wire.begin(8);                // join i2c bus with address #8
    Wire.onRequest(requestEvent); // register event
}

void loop () {
    double distance = distanceSensor.measureDistanceCm();
    //delay(40);
    //Serial.println(distance);
    if (distance < 5){
      count++;
      shotMade = true;
      delay(150);
      //Serial.println(count);
      Serial.write("T");
    }
    else{
      delay(40); 
    }
}

void requestEvent() {
  if (shotMade){
    Wire.write("T");
    shotMade = false;
  } else{
    Wire.write("F");
  }
}
