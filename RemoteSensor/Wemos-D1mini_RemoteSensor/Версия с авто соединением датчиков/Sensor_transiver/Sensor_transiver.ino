#include <SoftwareSerial.h>
#define MYPORT_TX 0
#define MYPORT_RX 4
EspSoftwareSerial::UART myPort;
#define S0 D7
#define S1 D6

#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t TargetMac[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

uint16_t SensorValue;
uint16_t SensorsValueArr[4] = {0, 0, 0, 0};

unsigned long lastTime = 0;
unsigned long timerDelay = 10;
struct GetMac
{
  uint8_t PacketID;
  uint8_t mac[6];
} GetMac;


void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Статус отправки пакета: ");
  if (sendStatus == 0) {
    Serial.println("Успешно");
  } else {
    Serial.println("Ошибка");
  }
}
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  Serial.print("Bytes received: ");
  Serial.println(*incomingData);
  Serial.println(*(incomingData+1));
  Serial.println(*(incomingData+2));
  Serial.println(*(incomingData+3));
  Serial.println(*(incomingData+4));
  memcpy(&GetMac, incomingData, sizeof(GetMac));
  
}



void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);


  Serial.begin(115200);
  myPort.begin(38400, SWSERIAL_8N1, MYPORT_RX, MYPORT_TX, false);
  if (!myPort) { // If the object did not initialize, then its configuration is invalid
    Serial.println("Invalid EspSoftwareSerial pin configuration, check config");
    while (1) { // Don't continue with invalid configuration
      delay (1000);
    }
  }
  EEPROM.begin(64);
  EEPROM.get(0, TargetMac);
  Serial.println(TargetMac[0]);
  Serial.println(TargetMac[1]);


  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  if (esp_now_init() != 0) {
    Serial.println("Ошибка инициализации ESP-NOW");
    return;
  }
  // Устанавливаем роль отправителя
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  // Регистрируем callback-функцию OnDataSent для отслеживания статуса отправки
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
  if (TargetMac[0] == 0x00 && TargetMac[1] == 0x00)
  {
    esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  }
  else
  {
    esp_now_add_peer(TargetMac, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  }
}
void loop() {
  /*
  if ((millis() - lastTime) > timerDelay) {
    //SensorValue = analogRead(0);
    //SensorValue = SensorValue * 4;
    digitalWrite(S0, LOW); digitalWrite(S1, LOW);
    SensorsValueArr[0] = analogRead(0) * 3.9 - 1;
    digitalWrite(S0, HIGH); digitalWrite(S1, LOW);
    SensorsValueArr[1] = analogRead(0) * 3.9 - 1;
    digitalWrite(S0, LOW); digitalWrite(S1, HIGH);
    SensorsValueArr[2] = analogRead(0) * 3.9 - 1;
    digitalWrite(S0, HIGH); digitalWrite(S1, HIGH);
    SensorsValueArr[3] = analogRead(0) * 3.9 - 1;

    Serial.print(SensorsValueArr[0]);
    Serial.print("!");
    Serial.print(SensorsValueArr[1]);
    Serial.print("!");
    Serial.print(SensorsValueArr[2]);
    esp_now_send(mac, (uint8_t *)&SensorsValueArr, sizeof(SensorsValueArr));
    lastTime = millis();

  }
  if (myPort.available()) {
    if (myPort.readBytes((byte*)&mac, sizeof(mac))) {
      Serial.print(mac[0], HEX);
      Serial.print(mac[1], HEX);
      Serial.print(mac[2], HEX);
      Serial.print(mac[3], HEX);
      Serial.print(mac[4], HEX);
      Serial.println(mac[5], HEX);
      EEPROM.put(0, mac);
      EEPROM.commit();
    }
  }
*/
}
