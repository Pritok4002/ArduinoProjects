int Page = 0;
int Total_Page = 3;
#define PageButtonPin 12 // к какому пину подключено кнопка смены
#define PowerButtonPin 11 // к какому пину подключено кнопка смены

#define ThermPin 6 // к какому пину подключено термосопротивление
#define ECPin2k 0 // к какому пину подключен щуп электропроводности
#define ECPin20k 1 // к какому пину подключен щуп электропроводности
#define PHPin 2 // к какому пину подключен щуп PH

#define DebugMode true

double mapf(double x, double in_min, double in_max, double out_min, double out_max)
{

    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
//LiquidCrystalRus lcd(7, 6, 5, 4, 3, 2);
#include "Adafruit_LiquidCrystal.h"
Adafruit_LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

bool PageButtonFlag = false;

void setup() {
  //analogReference(EXTERNAL);
  //analogReadResolution(12);

  Serial.begin(115200);
  Serial.println("BlueBoxLGT8F328 V1 init");
  Serial.println(VCAL3);
  lcd.begin(8, 2);

  pinMode(12, INPUT_PULLUP);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  
}

void loop() {
  int ADC_EC20k = analogRead(ECPin20k);
  int ADC_EC2k = analogRead(ECPin2k);
  int ADC_Ph = analogRead(PHPin);



  //Смена страниц
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
//////////////////////////////////
///////////////////////////////////

  
  if (Page == 0) { //страница которая будет отображать электропроводность
    lcd.setCursor(0,0);        
        if(ADC_EC20k>404)
        {
          lcd.setCursor(0,0);
          lcd.print("EEC20k        ");
          lcd.setCursor(0,1);
          float EC20k_Converted = mapf(ADC_EC20k,124,2482,650,13200);
          lcd.print((int)min(EC20k_Converted,200000));
          lcd.print("      ");
        }
        else
        {
          lcd.setCursor(0,0);
          lcd.print("EEC2k         ");
          lcd.setCursor(0,1);
          
          float EC2k_Converted = mapf(ADC_EC2k,124,2482,65.0,1320.0);
          lcd.print(max(0,EC2k_Converted),3);
          lcd.print("      ");
        }
        
        Serial.print("sensor20k = ");
        Serial.println(ADC_EC20k);
        
        Serial.print("sensor2k = ");
        Serial.println(ADC_EC2k);
        //Serial.print("\t Value = ");
        //Serial.println(EC2k_Converted);
  }
  else if (Page == 1) { //Страница PH
        lcd.setCursor(0,0);
        lcd.print("Ph           ");
        float Ph_Converted = mapf(ADC_Ph,621,2482,12.43,5.45);
        lcd.setCursor(0,1);
        lcd.print(max(0,Ph_Converted),3);
        lcd.print("       ");

        Serial.print("sensorPh = ");
        Serial.print(ADC_Ph);
        Serial.print("\t Value = ");
        Serial.println(Ph_Converted);
  }
  else if (Page == 2) {// страница температура
    
        lcd.setCursor(0,0);
        lcd.print("temperature                 ");
        lcd.setCursor(0,1);

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
