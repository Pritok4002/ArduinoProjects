

#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3,2);


void setup()
{
  Serial.begin(115200);
  Serial.println("UV_WH0802_V0.0.1");
  lcd.begin(8, 2);
}


void loop()
{       
  Serial.println(analogRead(0));
  lcd.setCursor(0, 0);    //Курсор на первой строке
  lcd.print("УФ"); //ИНТЕРВАЛ
  lcd.setCursor(0, 1);    //Курсор на первой строке
  lcd.print(analogRead(0)/(float)1000,3); //ИНТЕРВАЛ
  lcd.print("        ");

  delay(100);
}


//  -- END OF FILE --
