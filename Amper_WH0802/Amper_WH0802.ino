


#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3,8);


void setup()
{
  analogReference(INTERNAL);
  Serial.begin(115200);
  Serial.println("5Ampere_WH0802_V0.0.1");
  lcd.begin(8, 2);
}


void loop()
{
  float current = (1.1 / (float)analogRead(6)) * 0.185;
   
  Serial.println(current);
  lcd.setCursor(0, 0);    //Курсор на первой строке
  lcd.print("Ток 5А"); //ИНТЕРВАЛ
  lcd.setCursor(0, 1);    //Курсор на первой строке
  lcd.print(current); //ИНТЕРВАЛ
  lcd.print("        ");

  delay(100);
}


//  -- END OF FILE --
