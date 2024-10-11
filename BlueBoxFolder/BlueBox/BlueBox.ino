String Morze = ".--. .-. .. - --- -.-";
const long interval1 = 10;

int Page = 0;
int Total_Page = 4;
#define PageButtonPin 12 // к какому пину подключено кнопка смены
#define PowerButtonPin 11 // к какому пину подключено кнопка смены

#define ThermPin 6 // к какому пину подключено термосопротивление
#define ECPin2k 0 // к какому пину подключен щуп электропроводности
#define ECPin20k 1 // к какому пину подключен щуп электропроводности
#define PHPin 2 // к какому пину подключен щуп PH
#define ThermResistor 985 // Сопротивление резистора на делителе к термистору  
#define ThermB 3435 // коэффициент температурной чувствительности B
//B = (ln(R1) – ln(R2)) / (1 / T1 - 1 / T2),
//где R1 и R2 - значения сопротивлений при температурах соответственно T1 и T2, выраженных в Кельвинах.

//////////Значения для Калибровки EC метра //////////////////
int Raw1EC = 260;     // показания с Монитора порта первой жидкости
int Target1EC = 1640; // значения с эталона первой жидкости
int Raw2EC = 727;     //показания с Монитора порта второй жидкост
int Target2EC = 7000; //значения с эталона второй жидкости
//256 -1640  !!  727 - 7000
///////// Значения для Калибровки PH метра////////////////
int Raw1PH = 221;     // показания с Монитора порта первой жидкости
int Target1PH = 0;    // значения с эталона первой жидкости
int Raw2PH = 678;     // показания с Монитора порта второй жидкости
int Target2PH = 10;   // значения с эталона второй жидкости
// 220.5 - 0 !! 687.5 - 10



#define DebugMode true

#include "Mapf/src/Mapf.h"
#include "Mapf/src/Mapf.cpp"

#include "GyverNTC/src/GyverNTC.h"
#include "GyverNTC/src/GyverNTC.cpp"
GyverNTC therm(ThermPin, ThermResistor, ThermB);



#include "LiquidCrystalRus-master/LiquidCrystalRus.h"
#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3, 2);


bool PageButtonFlag = false;
bool PageButton2Flag = false;
bool Power = true;
void setup() {
  // put your setup code here, to run once:
    pinMode(LED_BUILTIN, OUTPUT);
  for(int i = 0; i < Morze.length(); i++)
  {
    if (Morze[i]=='.') {
      digitalWrite(LED_BUILTIN, 1);
      delay(interval1);
      digitalWrite(LED_BUILTIN, 0);
    }
    else if (Morze[i]=='-'){
      digitalWrite(LED_BUILTIN, 1);
      delay(interval1*3);
      digitalWrite(LED_BUILTIN, 0);
    }
    delay(interval1);
  }
  Serial.begin(9600);
  Serial.println("BlueBox V0.3 init");
  lcd.begin(8, 2);

  pinMode(12, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  //Serial.println("    Меню");
  //Serial.println("1 - Калибровка EC метра");
  //Serial.println("2 - Калибровка PH метра");
}

void loop() {


  uint32_t btnTimer = 0;
  bool SwitchButton = !digitalRead(PageButtonPin);
  if (SwitchButton && !PageButtonFlag && millis() - btnTimer > 100) {  // обработчик нажатия
    PageButtonFlag = true;
    btnTimer = millis();
    
    if(++Page >= Total_Page)Page =0;

  }
    if (!SwitchButton && PageButtonFlag && millis() - btnTimer > 100) {  // обработчик отпускания
    PageButtonFlag = false;  
    btnTimer = millis();
  }

  uint32_t btn2Timer = 0;
  
  bool SwitchButton2 = !digitalRead(PowerButtonPin);
  if (SwitchButton2 && !PageButton2Flag && millis() - btn2Timer > 100) {  // обработчик нажатия
    PageButton2Flag = true;
    btn2Timer = millis();
    Serial.println("Power Button click");
    Power = !Power;
    if (Power) {
    lcd.display();
    Serial.print("lcd.display :"+ Power);
    Serial.println(Power);
    }
    else {
    lcd.noDisplay();
    Serial.print("lcd.nodisplay :"+ Power);
    Serial.println(Power);
    }
  }
    if (!SwitchButton2 && PageButton2Flag && millis() - btn2Timer > 100) {  // обработчик отпускания
    PageButton2Flag = false;  
    btn2Timer = millis();
    Serial.println("Power Button Up");
  }


  if (Page == 0) {
    lcd.setCursor(0,0);
        lcd.print("EEC 2К      ");
        int AR2k = analogRead(ECPin2k);
        double EEC2K = mapf(AR2k,87,516,213,1505);
        double constEEC2K = constrain(EEC2K, 0, 2000);
        lcd.setCursor(0,1);
        lcd.print((String)constEEC2K+"           ");

        Serial.print("sensor2k = ");
        Serial.print(AR2k);
        Serial.print("\t Value = ");
        Serial.println(constEEC2K);
  }
  else if (Page == 1) {
        lcd.setCursor(0,0);
        lcd.print("EEC 20К           ");
        int AR20k = analogRead(ECPin20k);
        double EEC20K = mapf(AR20k,280,490,8380,15140);
        double constEEC20K = constrain(EEC20K, 0, 20000);
        lcd.setCursor(0,1);
        lcd.print((String)constEEC20K+"           ");


        Serial.print("sensor20k = ");
        Serial.print(AR20k);
        Serial.print("\t Value = ");
        Serial.println(constEEC20K);
  }
  else if (Page == 2) {
    int PH = analogRead(PHPin);
    float PHMap = mapf(PH, Raw1PH, Raw2PH, Target1PH, Target2PH); // 220.5 - 0 !! 687.5 - 10
    float PHConst = constrain(PHMap,0,14);
    
        lcd.setCursor(0,0);
        lcd.print("PH                 ");
        lcd.setCursor(0,1);
        lcd.print((String)PHConst+"           ");

        Serial.print("sensorPH = ");
        Serial.print(PH);
        Serial.print("\t Value = ");
        Serial.println(PHConst);

  }
  else if (Page == 3) {
    float Thermistor = therm.getTempAverage();
    lcd.setCursor(0,0);
    lcd.print("Температ                ");
        lcd.setCursor(0,1);
        lcd.print((String)Thermistor+"           ");

        //Serial.print("sensortherm = ");
        //Serial.print(Thermistor);
        //Serial.print("\t Value = ");
        //Serial.println(Thermistor);
  }
  delay(200);
}
/* 
PH 5v - 5v! GND - GND ! S - A1

EC 5v - 5v! GND - GND ! S - A0

Термистор GND A6

Резистор A6 5V

Кнопка смена D12 GND
*/