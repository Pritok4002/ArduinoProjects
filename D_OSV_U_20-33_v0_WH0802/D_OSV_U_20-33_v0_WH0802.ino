double mapf(double x, double in_min, double in_max, double out_min, double out_max)
{

    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3, 2);
void setup() {  //Инициализация серийного порта для вывода диагностических сообщений
  //analogReference(EXTERNAL);
  Serial.begin(115200);
  Serial.println("D_OSV_U_20-33_v0_WH0802 init");
  //Инициализация экрана
  lcd.begin(8, 2);
 
}
 void loop() {
 Serial.println(analogRead(0));
 Serial.println(analogRead(1));
 Serial.println(analogRead(2));
 Serial.println("----------------------");  
  float voltage0 = ((float)analogRead(0)*5)/1024;
  float voltage1 = ((float)analogRead(1)*5)/1024;
  float voltage2 = ((float)analogRead(2)*5)/1024;

  lcd.setCursor(0,0);
  lcd.print(min(max(mapf(voltage0,0.2,3.02,10,150),0),165));
  lcd.print("           ");
  lcd.setCursor(0,1);
  lcd.print((int)min(max(mapf(voltage1,0.5,3.02,1000,6000),0),6600));
  lcd.print(" ");
  lcd.print((int)min(max(mapf(voltage2,0.5,3.02,100,600),0),660));
  lcd.print("      ");
}     
