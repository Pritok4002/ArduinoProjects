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

uint16_t SensorsValueArr[4] = {0, 0, 0, 0};

void OnDataRecv(uint8_t *mac, uint8_t *data, uint8_t len) {
  //memcpy(&receivedData, data, sizeof(receivedData));
  memcpy(&SensorsValueArr, data, sizeof(SensorsValueArr));
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
int16_t sensor1 = 0;
int16_t sensor2 = 0;
int16_t sensor3 = 0;
int16_t sensor4 = 0;
void loop() {
  if ((millis() - lastTime) > timerDelay) {
    lastTime = millis();
  sensor1 = SensorsValueArr[0];
  sensor2 = SensorsValueArr[1];
  sensor3 = SensorsValueArr[2];
  sensor4 = SensorsValueArr[3];
  
  byte sensor1_first = sensor1 & 0b0000000001111111;
  byte sensor1_second = sensor1>>7;
  sensor1_second = sensor1_second & 0b00011111;
  sensor1_second = sensor1_second | 0b10000000;
  Serial.write(sensor1_first);
  Serial.write(sensor1_second);


  byte sensor2_first = sensor2 & 0b0000000001111111;
  byte sensor2_second = sensor2>>7;
  sensor2_second = sensor2_second & 0b00011111;
  sensor2_second = sensor2_second | 0b10100000;
  Serial.write(sensor2_first);
  Serial.write(sensor2_second);


  byte sensor3_first = sensor3 & 0b0000000001111111;
  byte sensor3_second = sensor3>>7;
  sensor3_second = sensor3_second & 0b00011111;
  sensor3_second = sensor3_second | 0b11000000;
  Serial.write(sensor3_first);
  Serial.write(sensor3_second);

  
  byte sensor4_first = sensor4 & 0b0000000001111111;
  byte sensor4_second = sensor4>>7;
  sensor4_second = sensor4_second & 0b00011111;
  sensor4_second = sensor4_second | 0b11100000;
  Serial.write(sensor4_first);
  Serial.write(sensor4_second);
  }
}
