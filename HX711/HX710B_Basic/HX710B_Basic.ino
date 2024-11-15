#include "HX710B.h"
#include "Mapf.h"

const int DOUT = 12;   //sensor data pin
const int SCLK  = 11;   //sensor clock pin

HX710B pressure_sensor; 

void setup() {
  Serial.begin(115200);
  pressure_sensor.begin(DOUT, SCLK);
}

void loop() {

  if (pressure_sensor.is_ready()) {
    Serial.print("АЦП: ");
    Serial.println(pressure_sensor.pascal());
    //Serial.print("ATM: ");
    //Serial.println(pressure_sensor.atm());
    //Serial.print("mmHg: ");
    //Serial.println(pressure_sensor.mmHg());
    //Serial.print("PSI: ");
    //Serial.println(pressure_sensor.psi());
  } else {
    Serial.println("Pressure sensor not found.");
  }

  delay(1000);
  
}
