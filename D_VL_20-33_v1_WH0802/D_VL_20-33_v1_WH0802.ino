double mapf(double x, double in_min, double in_max, double out_min, double out_max)
{

    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3, 2);
void setup() {  //Инициализация серийного порта для вывода диагностических сообщений
  Serial.begin(115200);
  Serial.println("D_VL_20-33_v1_WH0802 init");
  //Инициализация экрана
  lcd.begin(8, 2);
 
}
 void loop() {
 Serial.println(analogRead(0));
 lcd.setCursor(0,0);
 lcd.print("humind"); 
  lcd.setCursor(0,1);
  float voltage = ((float)analogRead(0)*5)/1024;
  lcd.print(min(max(mapf(voltage,0.75,2.4,10,90)+5,0),100));
  lcd.print(" %       ");
}     
