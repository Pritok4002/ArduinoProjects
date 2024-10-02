// Sht20 вывод на дисплей V0.0.1

#include "Wire.h"
#include "BH1750/src/BH1750.cpp"
BH1750 lightMeter;

#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3,8);


void setup()
{
  Serial.begin(115200);
  Serial.println("BH1750_WH0802_V0.0.1");
  lcd.begin(8, 2);
  Wire.begin();
  lightMeter.begin();

}


void loop()
{
  float lux = lightMeter.readLightLevel();
  Serial.print(lux);
  lcd.setCursor(0, 0);    //Курсор на первой строке
  lcd.print("Освещение"); //ИНТЕРВАЛ
  lcd.setCursor(0, 1);    //Курсор на первой строке
  lcd.print(lux); //ИНТЕРВАЛ

  delay(100);
}


//  -- END OF FILE --
