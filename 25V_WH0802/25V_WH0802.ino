
 // GND -- [ R2 ] -- A0 -- [ R1 ] -- VIN
#define VREF 4.9    // точное напряжение на пине 5V (в данном случае зависит от стабилизатора на плате Arduino)
#define DIV_R1 30000  // точное значение 30 кОм резистора
#define DIV_R2 7501   // точное значение 7.5 кОм резистора

#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3,2);


void setup()
{
  Serial.begin(115200);
  Serial.println("25V_WH0802_V0.0.1_4.75");
  lcd.begin(8, 2);
}


void loop()
{
  //float voltage = (float)analogRead(0 ) * VREF * ((37500) / 7500) / 1024;
  int reading = analogRead(1);                        // Считываем напряжение датчика
  float voltage = reading * 5.0;                              // Преобразуем показания в напряжение( для 3.3v используйте значение 3.3 )
  voltage /= 1024.0;                                          
  float temperatureC = (voltage - 0.5) * 100 ;       
  Serial.println(analogRead(0));
  lcd.setCursor(0, 0);    //Курсор на первой строке
  lcd.print(temperatureC); //ИНТЕРВАЛ
  lcd.setCursor(0, 1);    //Курсор на первой строке
  lcd.print(analogRead(0)); //ИНТЕРВАЛ
  lcd.print("        ");

  delay(100);
}


//  -- END OF FILE --
