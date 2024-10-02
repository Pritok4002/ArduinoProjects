// Sht20 вывод на дисплей V0.0.1

#include "Wire.h"
#include "QMC5883L/src/QMC5883LCompass.cpp"
QMC5883LCompass compass;

#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3,8);


void setup()
{
  Serial.begin(115200);
  Serial.println("BH1750_WH0802_V0.0.1");
  lcd.begin(8, 2);
  Wire.begin();
  compass.init();
  compass.setSmoothing(10,true);
  compass.setCalibrationOffsets(177.00, 270.00, 185.00);
  compass.setCalibrationScales(1.06, 0.96, 0.98);

}


void loop()
{
  compass.read();
  // Return Azimuth reading
  int azimuth = compass.getAzimuth();

  Serial.print(azimuth);
  lcd.setCursor(0, 0);    //Курсор на первой строке
  lcd.print("Азимут"); //ИНТЕРВАЛ
  lcd.setCursor(0, 1);    //Курсор на первой строке
  lcd.print(azimuth); //ИНТЕРВАЛ
  lcd.print("          ");
  delay(10);
}


//  -- END OF FILE --
