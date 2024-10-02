#define PIRSensor1 8
#define PIRSensor2 9
#define PIRSensor3 10
#define PIRSensor4 11
#define PIRSensor5 12
#define PIRSensor6 0
  
#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3, 2);
#include "GyverButton/src/GyverButton.cpp"

GButton PIR1(PIRSensor1);
GButton PIR2(PIRSensor2);
GButton PIR3(PIRSensor3);
GButton PIR4(PIRSensor4);
GButton PIR5(PIRSensor5);


uint8_t PIR1Count = 0;
uint8_t PIR2Count = 0;
uint8_t PIR3Count = 0;
uint8_t PIR4Count = 0;
uint8_t PIR5Count = 0;
uint8_t PIR6Count = 0;


void setup() {  //Инициализация серийного порта для вывода диагностических сообщений
  Serial.begin(115200);
  Serial.println("HCSR04_WH0802 init");
  //Инициализация экрана
  lcd.begin(8, 2);
  //PIR5.setTimeout(99999);  
}

 bool flag = false;
 bool btnState = false;
void loop() {
  PIR1.tick();
  PIR2.tick();
  PIR3.tick();
  PIR4.tick();
  PIR5.tick();
  
  lcd.setCursor(0,0);
  lcd.print(PIR1Count);
  lcd.setCursor(3,0);
  lcd.print(PIR2Count);
  lcd.setCursor(6,0);
  lcd.print(PIR3Count);
  
  lcd.setCursor(0,1);
  lcd.print(PIR4Count);
  lcd.setCursor(3,1);
  lcd.print(PIR5Count);
  lcd.setCursor(6,1);
  lcd.print(PIR6Count);
  

  
  if(PIR1.isRelease())
  {
    PIR1Count++;    
    Serial.println("PIR1click");
  }
  
  if(PIR2.isRelease())
  {
    PIR2Count++;    
    Serial.println("PIR2click");
  }
  
  if(PIR3.isRelease())
  {
    PIR3Count++;    
    Serial.println("PIR3click");
  }
  
  if(PIR4.isRelease())
  {
    Serial.println("PIR4click");
    PIR4Count++;    
  }
  
  if(PIR5.isRelease())
  {
    PIR5Count++; 
    Serial.println("PIR5click");   
  }



  //---------------analog
  int A0Read = analogRead(0);
  //Serial.println(A0Read);
  if(A0Read>100)
  { btnState = true;
  
  }
  else
  { btnState = false;}
  
  if (btnState && !flag) {  // обработчик нажатия
    flag = true;
    PIR6Count++;     
    Serial.println("press");
  }
  if (!btnState && flag) {  // обработчик отпускания
    flag = false;  
    //Serial.println("release");
  }

  
}     
