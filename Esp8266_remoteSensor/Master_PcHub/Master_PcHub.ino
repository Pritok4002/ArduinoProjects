/*
   Сайт автора https://arduino-tex.ru/
   Проекты на Arduino https://portal-pk.ru/page-17/proekty-na-arduino.html
   Проекты на ESP https://arduino-tex.ru/menu/10/11/proekty-na-esp8266-esp32.html
   Страница урока https://arduino-tex.ru/news/173/vvedenie-v-esp-now-besprovodnaya-svyaz-na--esp8266.html
*/

#include <ESP8266WiFi.h>
#include <espnow.h>
// Структура для приема данных
uint16_t receivedData = 2048;

unsigned long lastTime = 0;
unsigned long timerDelay = 1; // Интервал между отправками данных
// Callback-функция, которая вызывается при приеме данных
void OnDataRecv(uint8_t *mac, uint8_t *data, uint8_t len) {
  memcpy(&receivedData, data, sizeof(receivedData));
  //Serial.print("Получены данные: ");
  //Serial.println(receivedData);
}
void setup() {
  Serial.begin(489600);
  //Serial1.begin
  // Инициализируем Wi-Fi как режим Station
  WiFi.mode(WIFI_STA);
  // Инициализируем ESP-NOW
  if (esp_now_init() != 0) {
    //Serial.println("Ошибка инициализации ESP-NOW");
    return;
  }
  // Устанавливаем роль получателя
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  // Регистрируем callback-функцию OnDataRecv для обработки принятых данных
  esp_now_register_recv_cb(OnDataRecv);
}
void loop() {
  if ((millis() - lastTime) > timerDelay) {

    lastTime = millis();
  
  
  // Ваш код основного цикла (если требуется)
  uint16_t sensor1 = receivedData;
  //uint16_t sensor1 = 512;
  
  byte sensor1_first = sensor1 & 0b0000000001111111;
  byte sensor1_second = sensor1>>7;
  sensor1_second = sensor1_second & 0b00011111;
  sensor1_second = sensor1_second | 0b10000000;
  Serial.write(sensor1_first);
  Serial.write(sensor1_second);
}
  }
