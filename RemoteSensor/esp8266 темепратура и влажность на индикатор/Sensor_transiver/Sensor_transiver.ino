#include <SoftwareSerial.h>
#define MYPORT_TX 0
#define MYPORT_RX 4
EspSoftwareSerial::UART myPort;

#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
uint8_t mac[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

float Packet[3] = {0.0, 0.0, 0.0};


#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 12     // Digital pin connected to the DHT sensor 
#define DHTTYPE    DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);

#include "OneWire/OneWire.cpp"
OneWire  ds(14);  // on pin 10 (a 4.7K resistor is necessary)



unsigned long lastTime = 0;
unsigned long timerDelay = 1000;

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
  dht.begin();

  EEPROM.begin(64);
  EEPROM.get(0, mac);
  Serial.println(mac[0], HEX);
  Serial.println(mac[1], HEX);
  Serial.println(mac[2], HEX);
  Serial.println(mac[3], HEX);
  Serial.println(mac[4], HEX);



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
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Packet[2] = event.temperature;
    Serial.print(Packet[2]);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Packet[1] = min(event.relative_humidity+5,100.0f);
    Serial.print(Packet[1]);
    Serial.println(F("%"));
  }


  byte i;
  byte present = 0;
  byte type_s;
  byte data[9];
  byte addr[8];
  float celsius;
  if ( !ds.search(addr)) {
    ds.reset_search();
    delay(250);
    return;
  }
  if (OneWire::crc8(addr, 7) != addr[7]) {
    return;
  }
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);
  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  present = ds.reset();
  ds.select(addr);
  ds.write(0xBE);
  for ( i = 0; i < 9; i++) {
    data[i] = ds.read();
  }
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
  }
  celsius = (float)raw / 16.0;
  Packet[0] = celsius;
  Serial.print("  Temperature = ");
  Serial.print(celsius);
  Serial.print(" Celsius, ");

  esp_now_send(mac, (uint8_t *)&Packet, sizeof(Packet));
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
