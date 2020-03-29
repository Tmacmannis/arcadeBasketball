#include <HCSR04.h>

UltraSonicDistanceSensor distanceSensor(12, 13);  // Initialize sensor that uses digital pins 13 and 12.

int count;

void setup () {
    Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
}

void loop () {
    // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
    double distance = distanceSensor.measureDistanceCm();
    //delay(40);
    //Serial.println(distance);
    if (distance < 5){
      count++;
      delay(150);
      Serial.println(count);
    }
    else{
      delay(40); 
    }
}
