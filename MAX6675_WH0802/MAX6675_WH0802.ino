
#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3, 2);
#include "MAX6675/max6675.cpp"
const uint8_t     thermoDO  = 8;                                 // Определяем константу с указанием № вывода Arduino к которому подключён вывод DO  ( SO, MISO ) модуля на чипе MAX6675
const uint8_t     thermoCS  = 9;                                 // Определяем константу с указанием № вывода Arduino к которому подключён вывод CS  ( SS )       модуля на чипе MAX6675
const uint8_t     thermoCLK = 10;                                 // Определяем константу с указанием № вывода Arduino к которому подключён вывод CLK ( SCK )      модуля на чипе MAX6675
uint8_t           degree[8] = {140,146,146,140,128,128,128,128}; // Определяем массив хрянящий биты символа градуса
MAX6675           thermo(thermoCLK, thermoCS, thermoDO);         // Объявляем объект thermo для работы с функциями и методами библиотеки MAX6675, указывая выводы ( CLK , CS , DO )

void setup() {  //Инициализация серийного порта для вывода диагностических сообщений
  Serial.begin(115200);
  Serial.println("MAX6675_WH0802 init");
  //Инициализация экрана
  lcd.begin(8, 2);
 
}
 void loop() {
 //Serial.println(analogRead(0));
 lcd.setCursor(0,0);
 lcd.print("Температура"); 
  lcd.setCursor(0,1);
  lcd.print(thermo.readCelsius());
  Serial.println(thermo.readCelsius());
  lcd.print(" C       ");
  delay(1000);
}     
