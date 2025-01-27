#include <SoftwareSerial.h>
#define MYPORT_TX 4
#define MYPORT_RX 0
EspSoftwareSerial::UART myPort;
#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
LiquidCrystalRus lcd(2, 5, 13, 12, 14, 16);

double mapf(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


#include <ESP8266WiFi.h>
#include <espnow.h>
uint8_t mac[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

float Packet[3] = {0.0, 0.0, 0.0};


volatile unsigned long lastRecv = 0;
void OnDataRecv(uint8_t *mac, uint8_t *data, uint8_t len) {
  memcpy(&Packet, data, sizeof(Packet));
  lastRecv = millis();
}
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Статус отправки пакета: ");
  if (sendStatus == 0) {
    Serial.println("Успешно");
  } else {
    Serial.println("Ошибка");
  }
}



void setup() {
  lcd.begin(8, 2);
  Serial.begin(489600);
  //Serial.begin(115200);
  myPort.begin(38400, SWSERIAL_8N1, MYPORT_RX, MYPORT_TX, false);
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
  if (esp_now_init() != 0) {
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_recv_cb(OnDataRecv);
  myPort.write((byte *)&mac, sizeof(mac)); 
}

void loop() {
  /*lcd.setCursor(0, 0);
  lcd.print("qwer1234");
  //lcd.print(Packet[0],1);lcd.print(" C     ");
  lcd.setCursor(0, 1);
  //lcd.print(Packet[0],1);
  //lcd.print(" %     ");
  lcd.print("йцук1234");
  */
    if (millis() > lastRecv + 2000)
    {
    lcd.setCursor(0, 0);
    lcd.print("sensor    ");
    lcd.setCursor(0, 1);
    lcd.print("off-line    ");
    }
    else
    {
    lcd.setCursor(0, 0);
    lcd.print(Packet[0],1);lcd.print(" C     ");
    lcd.setCursor(0, 1);
    lcd.print(Packet[1],1);
    lcd.print(" %     ");
    }
}
