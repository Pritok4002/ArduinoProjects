#define PIRSensor1 8
#include "MLX90614/Adafruit_MLX90614.cpp"
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
  
#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3, 2);
void setup() {  //Инициализация серийного порта для вывода диагностических сообщений
  Serial.begin(115200);
  Serial.println("MLX90614_WH0802 init");
  //Инициализация экрана
  lcd.begin(8, 2);
   if (!mlx.begin()) {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
    while (1);
  };

}
 void loop() {
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  //Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF());
  //Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");

  Serial.println();
  
 
 lcd.setCursor(0,0);
 lcd.print(mlx.readAmbientTempC()); lcd.print(" С             "); 
  
  lcd.setCursor(0,1);
  lcd.print(mlx.readObjectTempC()); lcd.print(" С        ");
  //lcd.print("        ");
  
 }     
