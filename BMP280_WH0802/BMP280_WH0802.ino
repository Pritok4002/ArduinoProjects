#include "GyverBME280/src/GyverBME280.cpp"                // Подключение библиотеки
GyverBME280 bme;                              // Создание обьекта bme

#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3,2);


void setup()
{
  Serial.begin(115200);
  Serial.println("BMP280_WH0802_V0.0.1");
  lcd.begin(8, 2);
  Wire.begin(); //Join I2C bus
  bme.begin();                                // Если доп. настройки не нужны  - инициализируем датчик

}


void loop()
{
  uint32_t pressure = bme.readPressure();
  float temperature = bme.readTemperature();
  float humi = bme.readHumidity();

  Serial.print("Temperature: ");
  Serial.print(bme.readTemperature());        // Выводим темперутуру в [*C]
  Serial.println(" *C");

  Serial.print("Humidity: ");
  Serial.print(bme.readHumidity());           // Выводим влажность в [%]
  Serial.println(" %");

 // int pressure = bme.readPressure();        // Читаем давление в [Па]
  Serial.print("Pressure: ");
  
  lcd.setCursor(0, 0);    //Курсор на первой строке
  lcd.print(pressure); //ИНТЕРВАЛ
  lcd.print("давление");
  lcd.setCursor(0, 1);    //Курсор на первой строке
  lcd.print(temperature); //ИНТЕРВАЛ
  lcd.print("температура");

  delay(100);
}


//  -- END OF FILE --
