  
#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
  
LiquidCrystalRus lcd(7, 6, 5, 4, 3, 2);

#include "NewPing/src/NewPing.cpp"

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 300 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {  //Инициализация серийного порта для вывода диагностических сообщений
  Serial.begin(115200);
  delay(100);
  Serial.println("HCSR04_WH0802 init");

  //Инициализация экрана
  lcd.begin(8, 2);
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Расстояние");
  lcd.setCursor(0,1);
  lcd.print(sonar.ping_cm());
  lcd.print(" см");
  delay(100);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  
}
