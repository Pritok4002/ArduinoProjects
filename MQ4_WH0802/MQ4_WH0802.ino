
#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3, 2);
void setup() {  //Инициализация серийного порта для вывода диагностических сообщений
  Serial.begin(115200);
  Serial.println("MQ4_WH0802 init");
  //Инициализация экрана
  lcd.begin(8, 2);
 
}
 void loop() {
 Serial.println(analogRead(0));
 lcd.setCursor(0,0);
 lcd.print("Вольт"); 
  lcd.setCursor(0,1);
  lcd.print(((float)analogRead(0)*5)/1024);
  lcd.print("        ");
}     
