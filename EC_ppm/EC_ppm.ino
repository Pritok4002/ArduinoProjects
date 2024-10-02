/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground through 220 ohm resistor

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogInOutSerial
*/
float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
    float voltage = 0;
    float ppm = 0;
// обычное среднее арифметическое для float
float midArifm() {
  float sum = 0;                      // локальная переменная sum
  for (int i = 0; i < 20; i++)  // согласно количеству усреднений
  {
    voltage = (float)(analogRead(0) * 1.1) / 1024;
    sum += voltage;
    delay(100);
  }
  return (sum / 20);
}


// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9;  // Analog output pin that the LED is attached to

int sensorValue = 0;  // value read from the pot
int outputValue = 0;  // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  analogReference(INTERNAL);
}

void loop() {
  // read the analog in value:
  ppm = mapf(midArifm(),0.8,0.9,1400,3500);
  Serial.print((float)(analogRead(0) * (float)1.1) / (float)1024);
  Serial.print("    ");
  Serial.println(ppm);

//3500 = 0.98
//1400 = 0.77
  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
}
