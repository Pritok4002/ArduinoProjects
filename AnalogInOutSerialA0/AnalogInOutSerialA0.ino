

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A2;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;  // value read from the pot
float outputValue = 0;  // value output to the PWM (analog out)
int sensorValue2 = 0;  // value read from the pot
float outputValue2 = 0;  // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:


  // print the results to the Serial Monitor:
  Serial.print("A0 = ");
  Serial.println(1);
  //Serial.print(',');
 // Serial.print("\t A2 = ");
 // Serial.println(outputValue2);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(100);
}
