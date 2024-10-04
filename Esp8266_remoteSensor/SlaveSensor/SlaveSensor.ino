/*
   Сайт автора https://arduino-tex.ru/
   Проекты на Arduino https://portal-pk.ru/page-17/proekty-na-arduino.html
   Проекты на ESP https://arduino-tex.ru/menu/10/11/proekty-na-esp8266-esp32.html
   Страница урока https://arduino-tex.ru/news/173/vvedenie-v-esp-now-besprovodnaya-svyaz-na--esp8266.html
*/

#include <ESP8266WiFi.h>
#include <espnow.h>
// Замените на MAC-адрес получателя (получателя)
uint8_t receiverMacAddress[] = {0x40, 0x22, 0xD8, 0x94, 0xC6, 0xA9};
// Структура для передачи данных
uint16_t SensorValue;
unsigned long lastTime = 0;
unsigned long timerDelay = 100; // Интервал между отправками данных
// Callback-функция, которая вызывается после отправки данных
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
  // Инициализируем Wi-Fi как режим Station
  WiFi.mode(WIFI_STA);
  // Инициализируем ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Ошибка инициализации ESP-NOW");
    return;
  }
  // Устанавливаем роль отправителя
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  // Регистрируем callback-функцию OnDataSent для отслеживания статуса отправки
  esp_now_register_send_cb(OnDataSent);
  // Добавляем получателя (партнера) по указанному MAC-адресу
  esp_now_add_peer(receiverMacAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}
void loop() {
  if ((millis() - lastTime) > timerDelay) {
    // Заполняем структуру myData данными, которые хотим передат
    // Отправляем структуру myData по протоколу ESP-NOW на указанный MAC-адрес получателя
    SensorValue = analogRead(0);
    SensorValue = SensorValue*4;
    esp_now_send(receiverMacAddress, (uint8_t *)&SensorValue, sizeof(SensorValue));
    lastTime = millis();
  }
}
