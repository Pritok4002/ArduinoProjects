#include <SoftwareSerial.h>

const int arduino_rx = 4;
const int arduino_tx = 5;
SoftwareSerial mySerial (arduino_rx, arduino_tx);

const int led_Pin = 13;

void setup()  {
  pinMode( arduino_rx,INPUT); pinMode( arduino_tx,OUTPUT);
  pinMode( led_Pin,OUTPUT);
  Serial.begin(9600); 
  mySerial.begin(9600);
}

void loop() {    
  if (mySerial.available()) {
    char c = mySerial.read(); 

if (c == '1'){ digitalWrite(led_Pin, HIGH);}
if (c == '0'){ digitalWrite(led_Pin, LOW);}
  }
}