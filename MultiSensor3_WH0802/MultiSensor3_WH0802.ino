double mapf(double x, double in_min, double in_max, double out_min, double out_max)
{

    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
const float AnalogRef = 3.3;
const int ADCMax = 1024;


#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3, 2);
void setup() {  //Инициализация серийного порта для вывода диагностических сообщений
  Serial.begin(115200);
  Serial.println("MultiSensor3_WH0802 init");
  for(int i =0;i<6;i++)
  {
    pinMode(i+8,INPUT_PULLUP);  
  }
  pinMode(13,INPUT_PULLUP);
  
  //Инициализация экрана
  lcd.begin(8, 2);
  analogReference(EXTERNAL);

      
}
//const int[6] ButtonsRead;
const int SensorsPins[5] = {0,1,2,3,6};
int PageNumber = 0;
float voltage = 0;
float result = 0;
 void loop() {
  for(int i =5;i>0;i--)
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
    case 1: // давление дифферинциальное
    lcd.setCursor(0,0);
    lcd.print("Датчик ");
    lcd.print(PageNumber);
    lcd.setCursor(0,1);
    voltage = ((float)analogRead(0)*AnalogRef)/ADCMax;
    result = mapf(voltage,3.175,1.78,0,100);
    lcd.print(result,2);
    lcd.print(" кПа       ");
      break;
    case 2:// Ускорение X
    lcd.setCursor(0,0);
    voltage = ((float)analogRead(1)*AnalogRef)/ADCMax;
    result = mapf(voltage,1.705,0.909,0.2,-100);
    lcd.print(result,1);
    lcd.print(" ");
    voltage = ((float)analogRead(2)*AnalogRef)/ADCMax;
    result = mapf(voltage,1.705,0.909,0.2,-100);
    lcd.print(result,1);
    lcd.print("     ");

    lcd.setCursor(0,1);
    voltage = ((float)analogRead(3)*AnalogRef)/ADCMax;
    result = mapf(voltage,1.705,0.909,0.2,-100);
    lcd.print(result,1);
    lcd.print(" м/с      ");
    break;
    case 3: //температура Жидкости
        lcd.setCursor(0,0);
    lcd.print("Датчик ");
    lcd.print(PageNumber);
    lcd.setCursor(0,1);
    voltage = ((float)analogRead(4)*AnalogRef)/ADCMax;
    result = mapf(voltage,3,1,99.6,26.4);
    lcd.print(result,1);
    lcd.print(" C       ");
      break;
  }
  
 
}     
