#include "LiquidCrystalRus/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3, 8);
#include <GyverPower.h>
#define SensorPin 10 // нога мк на герконы
#define ButtonPin 2 // нога мк на кнопку
#define LcdPower 12
#define HoldPower 5000
#define wooble 100 // Защита от дребезга в мс


void isr() {}



long StartTime = 0; // время начала отсчета
long StopTime = 0; // конец отсчета

bool flag = false;
uint32_t SensorTimer = 0;
bool flagbutton = false;
uint32_t btnTimer = 0;
uint32_t btnTimerPower = 0;

bool SecondClick = false;
bool RunTimer = false;
int state = 0;
bool powerv = false;




void PowerDownF(){
  lcd.noDisplay();
  powerv = false;
  RunTimer = false;
  delay(50);
  digitalWrite(3, 0);
  digitalWrite(4, 0);
  digitalWrite(5, 0);
  digitalWrite(6, 0);
  digitalWrite(7, 0);
  digitalWrite(8, 0);
  digitalWrite(12, 0);

  Serial.println("go sleep");
  
  
  delay(300);
  attachInterrupt(0, isr, FALLING);
  power.sleep(SLEEP_FOREVER);
  
}
void PowerOnF(){
  detachInterrupt(0);

}






void setup() {
  // put your setup code here, to SecondClick once:
  pinMode(SensorPin, INPUT_PULLUP);
  pinMode(ButtonPin, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(12, OUTPUT);

  delay(50);
  lcd.begin(8, 2);
  lcd.setCursor(0, 0);
  lcd.noDisplay();
  Serial.begin(115200);
  Serial.println("Stopwatch init OK");
  PowerDownF();
  power.setSleepMode(POWERDOWN_SLEEP);
  //Инициализация экрана

}















void loop() {
  // put your main code here, to SecondClick repeatedly:
   bool SensorState = !digitalRead(SensorPin);
   bool btnState = !digitalRead(ButtonPin);


  //оБРАБОТКА ДАТЧИКА///////////
  if (SensorState && !flag && millis() - SensorTimer > wooble && powerv) {


    flag = true;
    SensorTimer = millis();
    if(state == 0){
      lcd.setCursor(0, 1);
      lcd.print("                  ");
      StartTime = millis();
      RunTimer =true;
      state++;
    }
    else if(state==1)
    {
      RunTimer =false;
      state++;
    }
    Serial.println("Sensor");
  }
  if (!SensorState && flag && millis() - SensorTimer > wooble) {
    flag = false;
    SensorTimer = millis();
    //Serial.println("release");
  }
  ///////////////////////



  //ОБРАБОТКА КНОПКИ///////////
  // HOLD/////////////*
  
  if(btnState && millis() - btnTimerPower > HoldPower && !powerv)
{
  flagbutton = true;
  btnTimerPower = millis();
  PowerOnF();
  StartTime=millis();
  StopTime=millis();
  digitalWrite(12, 1);
  delay(50);
  lcd.begin(8, 2);
  lcd.display();
  lcd.setCursor(0, 0);
  powerv = true;


}
else if(btnState && millis() - btnTimerPower > HoldPower && powerv)
{
  btnTimerPower = millis();
  PowerDownF();
  
  powerv = false;
  
}



// click//////////
if(!btnState)btnTimerPower = millis();

  if (btnState && !flagbutton && millis() - btnTimer > wooble && powerv) {
    flagbutton = true;
    btnTimer = millis();
    if(state == 0){
      lcd.setCursor(0, 1);
      lcd.print("                  ");
      StartTime = millis();
      RunTimer =true;
      state++;
    }
    else if(state==1)
    {
      RunTimer =false;
      state++;
    }
    else if(state==2)
    {
      lcd.setCursor(0, 1);
      lcd.print("                  ");
      StartTime = StopTime;
      state = 0;
    }
    Serial.println("press");
  }
  if (!btnState && flagbutton && millis() - btnTimer > wooble) {
    flagbutton = false;
    btnTimer = millis();
    btnTimerPower = millis();
    //Serial.println("release");
  }
  ///////////////////////

  if (RunTimer && powerv)StopTime = millis();
  float time = (StopTime-StartTime)/(1000.000);
  if (time >= 999.999) {
  RunTimer = false;
  state = 2;
  }
  if (powerv) {
    lcd.setCursor(0, 1);
    lcd.print(fmin(time, 999.999),3);
    Serial.println(StopTime-StartTime);
  }
  ///int powerdown
  //if(!powerv && millis() - btnTimerPower > HoldPower)
  {

  }

 // Serial.println(time,3);  
}
