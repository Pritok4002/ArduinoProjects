#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(7, 6, 5, 4, 3, 2);

int32_t value;
byte buff[5];
int32_t offset;
int FirstRead = 10;
void setup() {
  Serial.begin(489600);
  lcd.begin(8, 2);
  lcd.setCursor(0, 0);
  lcd.print("0.00");
  lcd.setCursor(0, 1);
  lcd.print("Грамм");
}

void loop() {
  if (Serial.available() >= 5) {
    Serial.readBytes(buff, 5);
    if (buff[4] == 0x53) {
      value = ( static_cast<unsigned long>(0x00) << 24
                | static_cast<unsigned long>(buff[1]) << 16
                | static_cast<unsigned long>(buff[2]) << 8
                | static_cast<unsigned long>(buff[3]) );
    }
    else if (buff[3] == 0x53){
      value = ( static_cast<unsigned long>(0x00) << 24
                | static_cast<unsigned long>(buff[0]) << 16
                | static_cast<unsigned long>(buff[1]) << 8
                | static_cast<unsigned long>(buff[2]) );
    }

    if (FirstRead > 0) {
      offset = value;
      FirstRead--;
    }
  }
  int32_t test = value - offset;
  if (FirstRead <= 0) {
    lcd.setCursor(0, 0);
    lcd.print((value-offset)* -0.000395939, 2);//
    //lcd.print(value, HEX); // lcd.print(buff[1],HEX); lcd.print(buff[2],HEX); lcd.print(buff[3],HEX); lcd.print(buff[4],HEX);
    lcd.print("         ");
    lcd.setCursor(0, 1);
    lcd.print("Грамм");
  }
}
