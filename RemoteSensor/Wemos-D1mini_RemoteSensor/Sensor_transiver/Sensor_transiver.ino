#include <SoftwareSerial.h>
#define MYPORT_TX 0
#define MYPORT_RX 4
EspSoftwareSerial::UART myPort;
#define S0 D7
#define S1 D6





#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
uint8_t mac[] = {0x11, 0x11, 0x11, 0x11, 0x11, 0x11};



uint16_t SensorValue;
uint16_t SensorsValueArr[4] = {0, 0, 0, 0};

unsigned long lastTime = 0;
unsigned long timerDelay = 10;



void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Статус отправки пакета: ");
  if (sendStatus == 0) {
    Serial.println("Успешно");
  } else {
    Serial.println("Ошибка");
  }
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
  EEPROM.get(0, mac);
  Serial.println(mac[0]);
  Serial.println(mac[1]);


  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) {
    Serial.println("Ошибка инициализации ESP-NOW");
    return;
  }
  // Устанавливаем роль отправителя
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  // Регистрируем callback-функцию OnDataSent для отслеживания статуса отправки
  esp_now_register_send_cb(OnDataSent);
  // Добавляем получателя (партнера) по указанному MAC-адресу
  esp_now_add_peer(mac, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}
void loop() {
  //


  if ((millis() - lastTime) > timerDelay) {
  //SensorValue = analogRead(0);
  //SensorValue = SensorValue * 4;
  digitalWrite(S0, LOW); digitalWrite(S1, LOW);
  SensorsValueArr[0] = analogRead(0) * 3.9-1;
  digitalWrite(S0, HIGH); digitalWrite(S1, LOW);
  SensorsValueArr[1] = analogRead(0) * 3.9-1;
  digitalWrite(S0, LOW); digitalWrite(S1, HIGH);
  SensorsValueArr[2] = analogRead(0) * 3.9-1;
  digitalWrite(S0, HIGH); digitalWrite(S1, HIGH);
  SensorsValueArr[3] = analogRead(0) * 3.9-1;

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

}
