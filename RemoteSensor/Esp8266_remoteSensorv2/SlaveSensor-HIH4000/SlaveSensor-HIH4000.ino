double mapf(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
#include <SoftwareSerial.h>

#define MYPORT_TX 0
#define MYPORT_RX 4

EspSoftwareSerial::UART myPort;
uint8_t mac[] = {0x11, 0x11, 0x11, 0x11, 0x11, 0x11};


#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

int SensorValue;
unsigned long lastTime = 0;
unsigned long timerDelay = 10;

bool ReadMac=true;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Статус отправки пакета: ");
  if (sendStatus == 0) {
    Serial.println("Успешно");
  } else {
    Serial.println("Ошибка");
  }
}
void setup() {
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
        Serial.print(mac[0],HEX);
      Serial.print(mac[1],HEX);
      Serial.print(mac[2],HEX);
      Serial.print(mac[3],HEX);
      Serial.print(mac[4],HEX);
      Serial.println(mac[5],HEX);
}
void loop() {
  if ((millis() - lastTime) > timerDelay) {
    SensorValue = analogRead(0)*1.18;
    SensorValue = mapf(SensorValue,256,1000,948,3798);
    SensorValue = min(max(SensorValue,0),4095);
    Serial.print(SensorValue);
    
    esp_now_send(mac, (uint8_t *)&SensorValue, sizeof(SensorValue));
    lastTime = millis();
  }
  if(myPort.available())
     if (myPort.readBytes((byte*)&mac, sizeof(mac))) {
      Serial.print(mac[0],HEX);
      Serial.print(mac[1],HEX);
      Serial.print(mac[2],HEX);
      Serial.print(mac[3],HEX);
      Serial.print(mac[4],HEX);
      Serial.println(mac[5],HEX);
      EEPROM.put(0, mac);
      EEPROM.commit();
      }
}
