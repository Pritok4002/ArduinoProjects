#include "HX711/HX711.h"        
#include "HX711/HX711.cpp"    // подключаем библиотеку для работы с тензодатчиком
#include <EEPROM.h>

float GetCalibrationFactor(float weight_of_standard);
float GetWeight(float _calibration_factor);


HX711 scale;                // создаём объект scale для работы с тензодатчиком
const bool Debug = true;  //константа которая включает или отключает отладочные сообщения
const float conversion_rate    = 0.035274; //константа для конвертации значения в грамм

uint8_t DOUT_PIN = 6;       // указываем вывод DOUT, к которому подключен HX711
uint8_t SCK_PIN  = 7;       // указываем вывод SCK, к которому подключен HX711

float StandartWeight = 100;   //значение груза для калибровки
float calibration_factor;   // калибровочное значение для каждого тензодатчика свое значение



void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(12, INPUT_PULLUP);

  Serial.begin(115200);
  scale.begin(DOUT_PIN, SCK_PIN);
  scale.set_scale();                                                                     
  scale.tare();   

  EEPROM.get(20, calibration_factor);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(GetWeight(calibration_factor));

  if(!digitalRead(12))
  {
    calibration_factor =  GetCalibrationFactor(StandartWeight);
  }
}


float GetCalibrationFactor(float weight_of_standard )
{
  scale.set_scale();                                                                      // не калибруем полученные значения
  scale.tare();                                                                           // обнуляем вес на весах (тарируем)
  if(Debug)Serial.println("You have 10 seconds to set your known load");                  // выводим в монитор порта текст о том, что у вас есть 10 секунд для установки эталонного веса на весы
  digitalWrite(LED_BUILTIN, true);                                                        // включаем светодиод для обозначения того что происходит калибровка
  delay(10000);                                                                           // ждём 10 секунд
  if(Debug)Serial.print("calibration factor: ");                                          // выводим текст в монитор поседовательного порта
  float Cal_factor = scale.get_units(10) / (weight_of_standard / conversion_rate);        // получаем округленное значения по 10 считывания датчик и расчитываем фактор
  digitalWrite(LED_BUILTIN, false);
  if(Debug)Serial.println(Cal_factor);

  EEPROM.put(20, Cal_factor);                             // сохраняем в EEPROM значение калибровки
  return Cal_factor;
  
}

float GetWeight(float _calibration_factor)
{
  scale.set_scale(_calibration_factor);
  float units  = scale.get_units(10);                              
  double ounces = units * 0.035274;                                  // переводим вес из унций в граммы
  return ounces;                                   
}

