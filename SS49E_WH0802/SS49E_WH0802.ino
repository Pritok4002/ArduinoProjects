
 // GND -- [ R2 ] -- A0 -- [ R1 ] -- VIN
#define VREF 4.9    // точное напряжение на пине 5V (в данном случае зависит от стабилизатора на плате Arduino)
#define DIV_R1 30000  // точное значение 30 кОм резистора
#define DIV_R2 7501   // точное значение 7.5 кОм резистора

#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3,2);

double mapf(double x, double in_min, double in_max, double out_min, double out_max)
{

    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void setup()
{
  Serial.begin(115200);
  Serial.println("SS49E_WH0802_V0.0.1");
  lcd.begin(8, 2);
}

float output;
void loop()
{
  
  float sensor = analogRead(7);
  if(sensor<509)
  {
    output = mapf(sensor,0,503,-100,0);
  }
  else if(sensor>511)
  {
    output = mapf(sensor,506,1000,0,100);
  }
  else
    output = 0;
  
  
  Serial.println(analogRead(7));
  //Serial.println(analogRead(6));
  //Serial.println(analogRead(5));
  //Serial.println("----------------------");
  lcd.setCursor(0, 0);    //Курсор на первой строке
  lcd.print("Сила магнита"); //ИНТЕРВАЛ
  lcd.setCursor(0, 1);    //Курсор на первой строке
  lcd.print(output); //ИНТЕРВАЛ
  lcd.print("        ");

  delay(100);
}


//  -- END OF FILE --
