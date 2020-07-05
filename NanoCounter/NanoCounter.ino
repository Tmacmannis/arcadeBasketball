#define SENSORPIN 12

int sensorState = 0, lastState=0;

void setup () {
    Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
    pinMode(SENSORPIN, INPUT_PULLUP);
}

void loop () {

  sensorState = digitalRead(SENSORPIN);
  
  if (sensorState && !lastState) {
    Serial.println("Unbroken");
  } 
  if (!sensorState && lastState) {
    Serial.println("Broken");
    Serial.write("T");
  }
  lastState = sensorState;

}