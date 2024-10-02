double mapf(double x, double in_min, double in_max, double out_min, double out_max)
{

    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#include "MLX90614/Adafruit_MLX90614.cpp"
Adafruit_MLX90614 mlx = Adafruit_MLX90614();


#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3, 2);
void setup() {  //Инициализация серийного порта для вывода диагностических сообщений
  Serial.begin(115200);
  Serial.println("MultiSensor_WH0802 init");
  for(int i =0;i<6;i++)
  {
    pinMode(i+8,INPUT_PULLUP);  
  }
  pinMode(13,INPUT_PULLUP);
  
  //Инициализация экрана
  lcd.begin(8, 2);

     if (!mlx.begin()) {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
    while (1);
  }; 
}
//const int[6] ButtonsRead;
const int SensorsPins[5] = {0,1,2,3,6};
int PageNumber = 0;
float voltage = 0;
float result = 0;
 void loop() {
  for(int i =6;i>0;i--)
  {
    if(!digitalRead(i+7))
    {
      PageNumber = i*!digitalRead(i+7);
    }
       Serial.print(digitalRead(i+7));
       
      
  }
  //Serial.println(digitalRead(13));
  Serial.println("------------------");
  switch(PageNumber)
  {
    case 0:
    lcd.setCursor(0,0);
    lcd.print("Мульти    ");
    lcd.setCursor(0,1);
    lcd.print("  Датчик");
      break;
    case 1: // Напряжение
    lcd.setCursor(0,0);
    lcd.print("Датчик ");
    lcd.print(PageNumber);
    lcd.setCursor(0,1);
    voltage = ((float)analogRead(0)*5)/1024;
    result = mapf(voltage,3.2,0.13,10,-10);
    lcd.print(result);
    lcd.print(" В       ");
      break;
    case 2:// Ток 2 ампера
        lcd.setCursor(0,0);
    lcd.print("Датчик ");
    lcd.print(PageNumber);
    lcd.setCursor(0,1);
    voltage = ((float)analogRead(1)*5)/1024;
    result = mapf(voltage,3,1,2.247,-1.1);
    lcd.print(result);
    lcd.print(" А       ");
    break;
    case 3://тмпература 
        lcd.setCursor(0,0);
    lcd.print("Датчик ");
    lcd.print(PageNumber);
    lcd.setCursor(0,1);
    lcd.print(mlx.readObjectTempC());
    lcd.print(" С       ");
    break;
    case 4: //освещенность 
        lcd.setCursor(0,0);
    lcd.print("Датчик ");
    lcd.print(PageNumber);
    lcd.setCursor(0,1);
    voltage = ((float)analogRead(2)*5)/1024;
    result = mapf(voltage,3,1,5416,1808);
    lcd.print((int)result);
    lcd.print(" лк       ");
    break;
    case 5: //Уровеь звука
        lcd.setCursor(0,0);
    lcd.print("Датчик ");
    lcd.print(PageNumber);
    lcd.setCursor(0,1);
    voltage = ((float)analogRead(3)*5)/1024;
    result = mapf(voltage,3,1,0.904,0.302);
    lcd.print(result);
    lcd.print("        ");
      break;
    case 6://ток 20мА
        lcd.setCursor(0,0);
    lcd.print("Датчик ");
    lcd.print(PageNumber);
    lcd.setCursor(0,1);
    voltage = ((float)analogRead(6)*5)/1024;
    result = mapf(voltage,3,1,17.72,-8.77);
    lcd.print(result);
    lcd.print(" мА        ");
      break;

  }
  
 
}     
