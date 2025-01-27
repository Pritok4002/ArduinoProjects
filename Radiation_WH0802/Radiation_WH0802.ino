#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3, 2);

void setup() {
  Serial.begin(115200);
  Serial.println("Radiation_WH0802_V0.0.1");
  lcd.begin(8, 2);
}
bool flag = false;
uint8_t counter = 0;
unsigned long timerOffset = 0;
uint8_t resultArr[10];
uint8_t resultArrPtr = 0;
uint16_t Mid = 0;
uint8_t MidCounter = 0;
void loop() {
  // читаем инвертированное значение для удобства
  bool btnState = digitalRead(12);
  if (btnState && !flag) {  // обработчик нажатия
    flag = true;
    counter++;
    Serial.println(counter);
    lcd.setCursor(0, 0);    //Курсор на первой строке
    lcd.print(counter); //ИНТЕРВАЛ
    lcd.print(" мкР/ч        "); //ИНТЕРВАЛ
  }
  if (!btnState && flag) {  // обработчик отпускания
    flag = false;
    //Serial.println("release");
  }
  if (millis() > timerOffset + 36000)
  {
    timerOffset = millis();

    Serial.println();
    Serial.println(counter);
    lcd.setCursor(0, 1);
    lcd.print(counter); //ИНТЕРВАЛ
    lcd.print("         "); //ИНТЕРВА
    counter = 0;
    /*resultArr[resultArrPtr++] = counter;
      if (resultArrPtr >= 10)
      resultArrPtr = 0;
      counter = 0;

      for (int i = 0; i < 10; i++)
      {
      Mid += resultArr[i];
      Serial.print(resultArr[i]);
      Serial.print("\t");
      if (resultArr[i] > 0)
        {

        MidCounter++;
        }

      }
      Serial.println();
      Serial.println(Mid);
      Serial.println(MidCounter);
      lcd.setCursor(0, 1);
      lcd.print((float)Mid/MidCounter,1); //ИНТЕРВАЛ
      lcd.print("         "); //ИНТЕРВА
      MidCounter = 0;
      Mid =0;
    */

  }
}
