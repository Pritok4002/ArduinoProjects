double mapf(double x, double in_min, double in_max, double out_min, double out_max)
{

    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#include "GyverBME280/src/GyverBME280.cpp"                   // Подключение библиотеки
GyverBME280 bme;                              // Создание обьекта bme


#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3, 2);
void setup() {  //Инициализация серийного порта для вывода диагностических сообщений
  Serial.begin(115200);
  Serial.println("MultiSensor2_WH0802 init");
  for(int i =0;i<6;i++)
  {
    pinMode(i+8,INPUT_PULLUP);  
  }
  pinMode(13,INPUT_PULLUP);
  
  //Инициализация экрана
  lcd.begin(8, 2);
  bme.begin();

      
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
    case 1: // давление
    lcd.setCursor(0,0);
    lcd.print("Датчик ");
    lcd.print(PageNumber);
    lcd.setCursor(0,1);
    voltage = ((float)analogRead(0)*5)/1024;
    result = mapf(voltage,3,1,235,85);
    lcd.print(result,1);
    lcd.print(" кПа       ");
      break;
    case 2:// жидкость и газ температура
        lcd.setCursor(0,0);
    lcd.print("Датчик ");
    lcd.print(PageNumber);
    lcd.setCursor(0,1);
    voltage = ((float)analogRead(1)*5)/1024;
    result = mapf(voltage,3,1,99.6,26.4);
    lcd.print(result,1);
    lcd.print(" C       ");
    break;
    case 3://атмосферное давление
        lcd.setCursor(0,0);
    lcd.print("Датчик ");
    lcd.print("гПа");
    lcd.setCursor(0,1);
    lcd.print(bme.readPressure()/100.0f);
    lcd.print("        ");
    break;
    case 4: //влажность 
        lcd.setCursor(0,0);
    lcd.print("Датчик ");
    lcd.print(PageNumber);
    lcd.setCursor(0,1);
    voltage = ((float)analogRead(2)*5)/1024;
    result = mapf(voltage,1,2,22.5,71);
    lcd.print(result,1);
    lcd.print(" %       ");
    break;
    case 5: //температура окружающей среды
        lcd.setCursor(0,0);
    lcd.print("Датчик ");
    lcd.print(PageNumber);
    lcd.setCursor(0,1);
    voltage = ((float)analogRead(3)*5)/1024;
    result = mapf(voltage,3,1,99.6,26.4);
    lcd.print(result,1);
    lcd.print("        ");
      break;
    case 6://магнитое поле
        lcd.setCursor(0,0);
    lcd.print("Датчик ");
    lcd.print(PageNumber);
    lcd.setCursor(0,1);
    voltage = ((float)analogRead(6)*5)/1024;
    result = mapf(voltage,3,1,90,-35);
    lcd.print(result,1);
    lcd.print(" мТл        ");
      break;

  }
  
 
}     
