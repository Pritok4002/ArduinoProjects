#define DUST_SENSOR_PIN_PM10  2  //Must be the pins that
#define DUST_SENSOR_PIN_PM25  3  //support interrupts


#define INTERVAL_COUNTDOWN 1000
#define INTERVAL_READ 30000

#include "KarserDSM501/KarserDSM501.cpp"
void pm10_handleInterrupt();
void pm25_handleInterrupt();

KarserDSM501 pm10(DUST_SENSOR_PIN_PM10, pm10_handleInterrupt);
KarserDSM501 pm25(DUST_SENSOR_PIN_PM25, pm25_handleInterrupt);

void pm10_handleInterrupt() { pm10.handleInterrupt(); }
void pm25_handleInterrupt() { pm25.handleInterrupt(); }
unsigned long timer = 0;

#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 9, 8);
void setup() {  //Инициализация серийного порта для вывода диагностических сообщений
  Serial.begin(115200);
  Serial.println("MQ4_WH0802 init");
  //Инициализация экрана
  lcd.begin(8, 2);
  lcd.setCursor(0,0);
 lcd.print("0.00"); 

 lcd.setCursor(0,1);
 lcd.print("0.00"); 
 
 
}
 void loop() {
 //Serial.println(analogRead(0));
  
  if (!pm10.isReady() && (millis() >= timer + INTERVAL_COUNTDOWN)) {
    Serial.println("DSM501 warm up: " + String(pm10.getReadyCountdown()));
    timer += INTERVAL_COUNTDOWN;
  } else if (millis() >= timer + INTERVAL_READ) {
    timer += INTERVAL_READ;
  lcd.setCursor(0,0);
  lcd.print(String(pm10.readPM()));
  lcd.print("        ");

  lcd.setCursor(0,1);
  lcd.print(String(pm25.readPM()));
  lcd.print("        ");
    //Serial.println("pm10: "+String(pm10.readPM()));    
  }
}     
