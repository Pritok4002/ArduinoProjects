// Sht20 вывод на дисплей V0.0.1

#include "DHT/DHT.cpp"
#define DHTPIN 10     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3,8);


void setup()
{
  Serial.begin(115200);
  Serial.println("DHT_WH0802_V0.0.1");
  lcd.begin(8, 2);
  dht.begin();

}


void loop()
{
   float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
 
  
  lcd.setCursor(0, 0);    //Курсор на первой строке
  lcd.print(t); //ИНТЕРВАЛ
  lcd.print("температура");
  lcd.setCursor(0, 1);    //Курсор на первой строке
  lcd.print(h); //ИНТЕРВАЛ
lcd.print("влажность");
   delay(2000);
}


//  -- END OF FILE --
