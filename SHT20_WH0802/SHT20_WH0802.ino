// Sht20 вывод на дисплей V0.0.1

#include "Wire.h"
#include "SHT2x/SHT2x.cpp"
SHT2x sht;

#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3,2);



void setup()
{
  Serial.begin(115200);
  Serial.println("SHT20_WH0802_V0.0.1");
  lcd.begin(8, 2);
  Wire.begin();
  sht.begin();
}


void loop()
{
  sht.read();
  Serial.print(sht.getTemperature(), 1);
  Serial.print("\t");
  Serial.println(sht.getHumidity(), 1);
  lcd.setCursor(0, 0);    //Курсор на первой строке
  lcd.print(String(sht.getTemperature())+"Температура"); //ИНТЕРВАЛ
  lcd.setCursor(0, 1);    //Курсор на первой строке
  lcd.print(String(sht.getHumidity())+"Влажность"); //ИНТЕРВАЛ

  delay(100);
}


//  -- END OF FILE --
