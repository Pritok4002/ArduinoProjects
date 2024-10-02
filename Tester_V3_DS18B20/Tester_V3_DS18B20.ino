int Page = 5;
int Total_Page = 5;

#define RX_PIN 10                                          
#define TX_PIN 9                                         
#define BAUDRATE 9600       
#define DebugMode true


#include "LiquidCrystalRus-master/LiquidCrystalRus.h"
#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3, 2);

#include "GyverBME280/src/GyverBME280.h"   
#include "GyverBME280/src/GyverBME280.cpp"                  
GyverBME280 bme;  
#include "GyverNTC/src/GyverNTC.cpp"
//GyverNTC therm(6, 985, 3435);

#include "DS18B20_RT/src/DS18B20.h"
#include "DS18B20_RT/src/DS18B20.cpp"
#define ONE_WIRE_BUS              2

OneWire oneWire(ONE_WIRE_BUS);
DS18B20 DS18B20_Sensor(&oneWire);



#include "Wire.h"
#include "ACD10/ACD10.h"
#include "ACD10/ACD10.cpp"
ACD10 ACD10Sensor;

#include "MH-Z19/src/MHZ19.h"
#include "MH-Z19/src/MHZ19.cpp"
MHZ19 myMHZ19; 

#include <SoftwareSerial.h> 
SoftwareSerial mySerial(RX_PIN, TX_PIN);




bool Rightflag = false;
bool Leftflag = false;
void FastDisplay(String Text, float Value);
float ACD10_CO2 =0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUDRATE);
  mySerial.begin(BAUDRATE);                               // Uno example: Begin Stream with MHZ19 baudrate  
  myMHZ19.begin(mySerial);

  Wire.begin();
  ACD10Sensor.begin();
  bme.begin();
  lcd.begin(8, 2);

  DS18B20_Sensor.begin();  


  pinMode(12, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);

  
  
}

void loop() {
  bme.begin();
  float pressure = bme.readPressure(); 
  float Temperature = bme.readTemperature();

  ACD10Sensor.requestSensor();
  while (ACD10Sensor.requestReady() == false) delay(10);
  ACD10Sensor.readSensor();
  float ACD10_CO2 = ACD10Sensor.getCO2Concentration();
  

  uint32_t btnTimer = 0;
 
  


  ///////////////////////Button Scanner////////////////////////
  //////////////////////Right Button/////////////////////////
  bool RightButton = !digitalRead(12);
  if (RightButton && !Rightflag && millis() - btnTimer > 100) {  // обработчик нажатия
    Rightflag = true;
    btnTimer = millis();
    
    if(++Page >= Total_Page)Page =0;
    if(DebugMode)Serial.println(Page);
  }
  if (!RightButton && Rightflag && millis() - btnTimer > 100) {  // обработчик отпускания
    Rightflag = false;  
    btnTimer = millis();
    //Serial.println("release");
  }
  ////////////////////Left Button//////////////////////////
  bool LeftButton = !digitalRead(11);
  if (LeftButton && !Leftflag && millis() - btnTimer > 100) {  // обработчик нажатия
    Leftflag = true;
    btnTimer = millis();
    
    if(--Page < 0)Page =Total_Page-1;
    if(DebugMode)Serial.println(Page);
  }
  if (!LeftButton && Leftflag && millis() - btnTimer > 100) {  // обработчик отпускания
    Leftflag = false;  
     btnTimer = millis();
    //Serial.println("release");
  }
  ///////////////////////////End Button sCANNER//////////////////////////////
  ////////////////////////////////////////////////////////////////////////



      switch(Page)
      {
        case 0: 
          
           
          FastDisplay("BME ГПА   ",pressure/100.0f);
          Serial.println("BME ГПА ");
          break;
        case 1: 
          
          FastDisplay("BME C`    ",Temperature);
          Serial.println("BME C ");
          break;
        case 2: 
          

          FastDisplay("ACD ppm    ",ACD10_CO2);
          Serial.println(ACD10_CO2);
          break;
        case 3: 
          int MHZ19_Co2 = myMHZ19.getCO2();
          //FastDisplay("MH-Z16    ",MHZ19_Co2);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("MH-Z16    ");
          lcd.setCursor(0,1);
          lcd.print(MHZ19_Co2);
          Serial.println("MH-Z16 ");
          break;
        case 4: 
          DS18B20_Sensor.requestTemperatures();

          //  wait until sensor is ready
          while (!DS18B20_Sensor.isConversionComplete())
          {
            delay(1);
          }

          float DsTemp = DS18B20_Sensor.getTempC();
          FastDisplay("DS18B20    ",DsTemp);
          Serial.print("DS18B20 = ");
          Serial.println(DsTemp);
        break;
                    
        default: 
        break;
      }
    delay(10);


}

  void FastDisplay(String Text, float Value) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(Text);
    lcd.setCursor(0,1);
    lcd.print(Value);
    
  }
