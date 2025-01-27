double mapf(double x, double in_min, double in_max, double out_min, double out_max)
{

    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3, 2);
void setup() {
Serial.begin(115200);
lcd.begin(8, 2);
analogReference(EXTERNAL);
}
float adc0;
float result;
// the loop function runs over and over again forever
void loop() {
    lcd.setCursor(0,0);
    lcd.print(mapf(analogRead(1),515,60,23.5,100),1);
    lcd.print(" C       ");  
    lcd.setCursor(0,1);
    adc0 = analogRead(0);
    result = mapf(adc0,100,900,193.29,20.01);
    lcd.print(result,1);
    lcd.print(" кПа       ");
    Serial.println(result);
    delay(200);
}
