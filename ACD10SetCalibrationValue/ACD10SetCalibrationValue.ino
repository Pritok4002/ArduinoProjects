int Current_CO2_Level =2000;

#include "Wire.h"
#include "ACD10.h"


ACD10 mySensor;


void setup()
{
  Serial.begin(9600);

  Wire.begin();
  mySensor.begin();
  delay(10);
  mySensor.setCalibrationMode(0);
  delay(10);
  mySensor.setManualCalibration(Current_CO2_Level);
  delay(10);
  Serial.println(mySensor.readManualCalibration());

}


void loop()
{
  mySensor.requestSensor();
  while (mySensor.requestReady() == false) delay(10);
  mySensor.readSensor();
  Serial.print(mySensor.getCO2Concentration());
  Serial.println();

  delay(1000);
}


//  -- END OF FILE --
