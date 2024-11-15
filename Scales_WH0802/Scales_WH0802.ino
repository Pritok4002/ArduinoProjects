#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3, 2);

#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {  //Инициализация серийного порта для вывода диагностических сообщений
  Serial.begin(489600);
  Serial.println("MQ4_WH0802 init");
  //Инициализация экрана
  lcd.begin(8, 2);
 mySerial.begin(4800);
}
int16_t scales;
 void loop() {
 //Serial.println(analogRead(0));
 
 lcd.setCursor(0,0);
 lcd.print(scales,BIN); 
  lcd.setCursor(0,1);
  lcd.print(scales<<8,BIN);
  lcd.print("        ");
  //delay(1000);
  if (Serial.available()) {
    mySerial.println(Serial.read(),BIN);
  }
}     
