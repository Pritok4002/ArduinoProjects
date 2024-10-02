
#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3,2);


void setup()
{
  Serial.begin(115200);
  Serial.println("TreamaTemperatureAnalog_WH0802_V0.0.1");
  lcd.begin(8, 2);
}


void loop()
{
 
  int reading = analogRead(0);                        // Считываем напряжение датчика
  float voltage = reading * 5.0;                              // Преобразуем показания в напряжение( для 3.3v используйте значение 3.3 )
  voltage /= 1024.0;                                          
  float temperatureC = (voltage - 0.5) * 100 ;       
  Serial.println(analogRead(0));
  lcd.setCursor(0, 0);    //Курсор на первой строке
  lcd.print("температура"); //ИНТЕРВАЛ
  lcd.setCursor(0, 1);    //Курсор на первой строке
  lcd.print(temperatureC); //ИНТЕРВАЛ
  lcd.print("        ");

  delay(100);
}


//  -- END OF FILE --
