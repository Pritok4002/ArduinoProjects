#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3, 2);

#include "HX711/HX711.cpp"
HX711 scale;   
#define DT 10                                                                // указываем вывод DOUT, к которому подключен HX711
#define SCK 11 
float calibration_factor = 89.08945;    

float value;
long offset;
bool OnlineFlag = false;


void setup() {
  Serial.begin(489600);
  
  
  //scale.set_gain(3,true);
  //offset = scale.read_average(10);
  
  lcd.begin(8, 2);
  lcd.setCursor(0, 0);
  lcd.print("ждем");
  lcd.setCursor(0, 1);
  lcd.print("");
  scale.begin(DT, SCK);
  offset = scale.read_average(5); 
  offset = scale.read_average(20);
}

void loop() {
  if (Serial.available()) {
    OnlineFlag = true;
  }
  if(!OnlineFlag){
    value = (scale.read_average(1)-offset)*-0.00039594;
    lcd.setCursor(0, 0);
    if(value>=0)
    lcd.print(" ");
    
    lcd.print(value,2);//
    lcd.print("         ");
    lcd.setCursor(0, 1);
    lcd.print("Грамм");
  }
  else
  {
    pinMode(SCK,INPUT);
    lcd.setCursor(0, 0);
    lcd.print(":)");//
    lcd.print("         ");
    lcd.setCursor(0, 1);
    lcd.print("Радуга");
  }

    
}
