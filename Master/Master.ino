#include <SoftwareSerial.h>


const int button = 7;
int button_state = 0;

const int arduino_rx = 4;
const int arduino_tx = 5;
SoftwareSerial mySerial (arduino_rx, arduino_tx);

void setup()  {
  pinMode( arduino_rx,INPUT); pinMode( arduino_tx,OUTPUT);
  pinMode( button,INPUT_PULLUP);
  Serial.begin(9600);  
  mySerial.begin(9600);
}

void loop() {
  button_state = digitalRead(button);
  if (button_state == LOW){ mySerial.print("1"); }      
  if (button_state == HIGH){ mySerial.print("0"); }    
}