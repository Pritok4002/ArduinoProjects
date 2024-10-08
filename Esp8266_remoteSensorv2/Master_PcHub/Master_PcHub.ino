#include <SoftwareSerial.h>

#define MYPORT_TX 4
#define MYPORT_RX 0

EspSoftwareSerial::UART myPort;

#include <ESP8266WiFi.h>
#include <espnow.h>
uint8_t mac[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint16_t receivedData = 2048;  //данные полученные с датчика

unsigned long lastTime = 0;
unsigned long timerDelay = 1; // Интервал между отправками данных

void OnDataRecv(uint8_t *mac, uint8_t *data, uint8_t len) {
  memcpy(&receivedData, data, sizeof(receivedData));
}
void setup() {
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
  //Serial.print(mac[0],HEX);
  //Serial.print(mac[1],HEX);
  //Serial.print(mac[2],HEX);
  //Serial.print(mac[3],HEX);
  //Serial.print(mac[4],HEX);
  //Serial.println(mac[5],HEX);
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
myPort.write((byte *)&mac,sizeof(mac));

}
void loop() {
  if ((millis() - lastTime) > timerDelay) {
    lastTime = millis();
    uint16_t sensor1 = receivedData;
  
    byte sensor1_first = sensor1 & 0b0000000001111111;
    byte sensor1_second = sensor1>>7;
    sensor1_second = sensor1_second & 0b00011111;
    sensor1_second = sensor1_second | 0b10000000;
    Serial.write(sensor1_first);
    Serial.write(sensor1_second);
  }
  
}
