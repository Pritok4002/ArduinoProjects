#include <TimerOne.h> // подключаем библиотеку TimerOne для задействования функций Таймера1 

int val = 0;                                 // переменная для хранения оцифрованного значения сигнала  

// функция sendData вызывается каждый раз, когда срабатывает прерывание Таймера1 (проходит заданное число микросекунд)
void sendData() {
  Serial.write("A0");                       // записываем в Serial-порт имя поля в программе для визуализации, куда надо выводить сигнал
                                            // всего в этой программе 4 поля, которые имеют имена A0, A1, A2, A3 (сверху вниз, по порядку их 
                                            // расположения в окне программы)
  val = analogRead(A0);                     // записываем в переменную val оцифрованное значение сигнала с ножки А0 на Arduino.
                                            // val может принимать значение в диапазоне от 0 до 1023, см. http://arduino.ru/Reference/AnalogRead 
  Serial.write(map(val, 0, 1023, 0, 255));  // записываем в Serial-порт значение val, предварительно отнормированное на диапазон значений от 0 до 255,
                                            // см. описание команды map:  http://arduino.ru/Reference/Map 
     
  //ВОТ ЭТОТ КОД Я ДОБАВИЛ ДЛЯ ОСТАЛЬНЫХ 3 КАНАЛОВ
  Serial.write("A1");                       //ОТПРАВЛЯЕМ В ПОРТ ЗАГАЛОВОК С ИМЕНЕМ КАНАЛА, С КОТОРОГО БУДУТ ДАННЫЕ
  val = analogRead(A1);                     //ЧИТАЕМ ДАННЫЕ С ПОРТА
  Serial.write(map(val, 0, 1023, 0, 255));  //ОТПРАВЛЯЕМ ОТФОРМАТИРОВАННЫЕ ДАННЫЕ В ПОРТ

  Serial.write("A2");                       //ЭТИ ПОВТОРЫ СДЕЛАНЫ ПО АНАЛОГИИ С ПРЕДЫДУЩИМИ
  val = analogRead(A2);
  Serial.write(map(val, 0, 1023, 0, 255));

  Serial.write("A3");
  val = analogRead(A3);
  Serial.write(map(val, 0, 1023, 0, 255));
  //ДОБАВЛЕННЫЙ КОД ЗАКОНЧЕН
  
}

// функция setup вызывается однократно при запуске Arduino
void setup() {
  //analogReference(EXTERNAL);
  Serial.begin(115200);                    // инициализируем Serial-порт на скорости 115200 Кбит/c. 
                                           // такую же скорость надо установить в программе для визуализации
  Timer1.initialize(3000);                 // инициализируем Таймер1, аргументом указываем интервал срабатывания - 3000 микросекунд 
                                           // (1 000 000 микросекунд = 1 сек)
  Timer1.attachInterrupt(sendData);        // как только проходит 3000 микросекунд - наступает прерывание (вызывается функция sendData)
}

void loop(){
// а в бесконечном цикле мы ничего не делаем. Таймер1 сам будет вызывать функцию sendData через каждые 3000 микросекунд
  }
