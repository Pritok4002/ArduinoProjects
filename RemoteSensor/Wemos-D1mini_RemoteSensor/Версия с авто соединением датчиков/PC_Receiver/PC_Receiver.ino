#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(2, 5, 13, 12, 14, 16);

double mapf(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


#include <ESP8266WiFi.h>
#include <espnow.h>
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t mac[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint16_t receivedData = 0;  //данные полученные с датчика

unsigned long lastTime = 0;
unsigned long timerDelay = 1; // Интервал между отправками данных
unsigned long lastTime2 = 0;
unsigned long timerDelay2 = 300; // Интервал между отправками данных
unsigned long midSensor1 = 0;

uint16_t SensorsValueArr[4] = {0, 0, 0, 0};
#define buffSize 10
uint16_t Sensor1Buff[buffSize];
uint8_t buffPointer = 0;

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  /*Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0) {
    Serial.println("Delivery success");
  }
  else {
    Serial.println("Delivery fail");
  }*/
}
volatile unsigned long lastRecv = 0;
void OnDataRecv(uint8_t *mac, uint8_t *data, uint8_t len) {
  memcpy(&SensorsValueArr, data, sizeof(SensorsValueArr));
  lastRecv = millis();
}



void setup() {
  lcd.begin(8, 2);
  Serial.begin(489600);
  //Serial.begin(115200);


  
  String kek = WiFi.macAddress();
  int index = 0;
  int start = 0;
  while (index < 6) {
    int end = kek.indexOf(':', start);
    if (end == -1) {
      end = kek.length();
    }
    // Извлекаем подстроку и конвертируем в целое число
    String byteString = kek.substring(start, end);
    mac[index] = (int8_t) strtol(byteString.c_str(), NULL, 16);
    // Обновляем индексы
    start = end + 1;
    index++;
  }

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  if (esp_now_init() != 0) {
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
}
int16_t sensor1 = 0;
int16_t sensor2 = 0;
int16_t sensor3 = 0;
int16_t sensor4 = 0;


String IamLost = "SensorWhereAreYou";
void loop() {
  //SensorsValueArr[0] = 1000;
  if ((millis() - lastTime) > timerDelay) {
    lastTime = millis();

    if (millis() > lastRecv + 2000)
    {
      sensor1 = 0;
      sensor2 = 0;
      sensor3 = 0;
      sensor4 = 0;
      lcd.setCursor(0, 0);
      lcd.print("Датчик    ");
      lcd.setCursor(0, 1);
      lcd.print("выключен    ");
      esp_now_send(broadcastAddress, (uint8_t *) &message, sizeof(message));
    }
    else
    {
      
      sensor1 = SensorsValueArr[0];
      sensor2 = SensorsValueArr[1];
      sensor3 = SensorsValueArr[2];
      sensor4 = SensorsValueArr[3];
      Sensor1Buff[buffPointer++] = sensor1;
      if (buffPointer >= buffSize)buffPointer = 0;
      if ((millis() - lastTime2) > timerDelay2) {
        midSensor1 = 0;
        for (int i = 0; i < buffSize; i++)
        {
          midSensor1 += Sensor1Buff[i];
        }
        midSensor1 = midSensor1 / buffSize;
        lastTime2 = millis();
        lcd.setCursor(0, 0);
        lcd.print(mapf(midSensor1, 1000, 2500, 13.4, 72.5), 1);
        lcd.print(" %     ");
        lcd.setCursor(0, 1);
        lcd.print("        ");
      }

    }


    byte sensor1_first = sensor1 & 0b0000000001111111;
    byte sensor1_second = sensor1 >> 7;
    sensor1_second = sensor1_second & 0b00011111;
    sensor1_second = sensor1_second | 0b10000000;
    Serial.write(sensor1_first);
    Serial.write(sensor1_second);


    byte sensor2_first = sensor2 & 0b0000000001111111;
    byte sensor2_second = sensor2 >> 7;
    sensor2_second = sensor2_second & 0b00011111;
    sensor2_second = sensor2_second | 0b10100000;
    Serial.write(sensor2_first);
    Serial.write(sensor2_second);


    byte sensor3_first = sensor3 & 0b0000000001111111;
    byte sensor3_second = sensor3 >> 7;
    sensor3_second = sensor3_second & 0b00011111;
    sensor3_second = sensor3_second | 0b11000000;
    Serial.write(sensor3_first);
    Serial.write(sensor3_second);


    byte sensor4_first = sensor4 & 0b0000000001111111;
    byte sensor4_second = sensor4 >> 7;
    sensor4_second = sensor4_second & 0b00011111;
    sensor4_second = sensor4_second | 0b11100000;
    Serial.write(sensor4_first);
    Serial.write(sensor4_second);
  }
}
