#include "HX711/HX711.h"        
#include "HX711/HX711.cpp"                                     // подключаем библиотеку для работы с тензодатчиком

                                     // Указываем номер вывода, к которому подключен вывод SCK датчика

 
HX711 scale;                                                  // создаём объект scale

float calibration_factor = 127.31;                            // вводим калибровочный коэффициент
float units;                                                  // задаём переменную для измерений в граммах
float ounces;                                                 // задаём переменную для измерений в унциях

void setup() {
  Serial.begin(9600);                                         // инициируем работу последовательного порта на скорости 9600 бод
  scale.begin(6, 7);                                       // инициируем работу с датчиком
  scale.set_scale();                                          // выполняем измерение значения без калибровочного коэффициента
  scale.tare();                                               // сбрасываем значения веса на датчике в 0
  scale.set_scale(calibration_factor);                        // устанавливаем калибровочный коэффициент
}

void loop() {
                         

    //Serial.print("Reading: "); 
  units  =scale.get_units(10);                              
  ounces = units * 0.035274;                                  // переводим вес из унций в граммы
  Serial.println(ounces);                                       // выводим в монитор последовательного порта вес в граммах
  ///Serial.println(" grams"); 


}