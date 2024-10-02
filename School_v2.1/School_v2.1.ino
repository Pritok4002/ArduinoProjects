  
  #include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
  
  LiquidCrystalRus lcd(7, 6, 5, 4, 3, 2);
  
const int btnModePin = 8;      //Конопка режим
const int btnStartPin = 9;     //Кнопка старт
const int sensorFstPin = 10;   //Первый датчик
const int sensorScndPin = 11;  //Второй датчик
int btnModeState = 0;
int btnStartState = 0;
int sensorFstState = 0;
int sensorScndState = 0;
int prevbtnModeState = 0;
int prevbtnStartState = 0;
int prevsensorFstState = 0;
int prevsensorScndState = 0;

int Mode = 1;         //Режим работы 1- главное меню, 2 - опыт
int MMPage = 1;       //Страница главного меню 1 или 2
int ExpNumb = -1;     //Какой опыт включен 1 - интервал, 2 - маятник
unsigned long StartTime = 0;   //Первое регистрируемое время
unsigned long EndTime = 0;     //Второе регистрируемое время
int FirstSensor = 0;  //Номер сработавшего первым датчика 1 или 2
unsigned long Interval = 0;   //Разница времени между первой сработкой датчика и текущим моментом/второй сработкой
bool AllreadyOnScreen = false;    //Эта страница уже выведена на экран
unsigned long ModeBtnPressed = 0;

void setup() {
  //Инициализация кнопок и датчиков
  pinMode(btnModePin,INPUT_PULLUP);
  pinMode(btnStartPin, INPUT_PULLUP);
  pinMode(sensorFstPin, INPUT_PULLUP);
  pinMode(sensorScndPin, INPUT_PULLUP);

  //Инициализация серийного порта для вывода диагностических сообщений
  Serial.begin(115200);
  delay(100);
  Serial.println("School_v2.1 init");

  //Инициализация экрана
  lcd.begin(8, 2);

  ModeBtnPressed = millis();
}

void loop() {
  //Serial.println("");
  //Проверка всех входящих пинов
  if (millis() - ModeBtnPressed > 400)    //Защищает от дребезга кнопки режима, после первого срабатывания на нажатие, перестает её слушать 0.4с
    btnModeState = !digitalRead(btnModePin);
  
  btnStartState = !digitalRead(btnStartPin);
  sensorFstState = digitalRead(sensorFstPin);
  sensorScndState = digitalRead(sensorScndPin);

  if (Mode == 1)    //Если мы в главном меню
  {    
    if (MMPage == 1)    //Если демонстрируется страница 1
    {
      if (!AllreadyOnScreen)
      {
        WriteOnScreen("Main", 1);   //Вывод на экран
        AllreadyOnScreen = true;
      } 
      
      if (btnModeState == HIGH && prevbtnModeState != btnModeState)   //Если нажата кнопка режим
      {
        MMPage = 2;   //Показать следующую страницу
        AllreadyOnScreen = false;
        ModeBtnPressed = millis();
      }
    }
    else    //Если демонстрируется страница 2
    {
      if (!AllreadyOnScreen)
      {
        WriteOnScreen("Main", 2);   //Вывод на экран
        AllreadyOnScreen = true;
      }      
      
      if (btnModeState == HIGH && prevbtnModeState != btnModeState)   //Если нажата кнопка режим
      {
        MMPage = 1;   //Показать следующую страницу
        AllreadyOnScreen = false;
        ModeBtnPressed = millis();
      }      
    }

    if (btnStartState == HIGH && prevbtnStartState != btnStartState)    //Если нажата кнопка старт
    {
      Mode = 2;   //Переключаем в режим опыта
      ExpNumb = MMPage;   //Номер опыта соответствует номеру страницы главного меню
      AllreadyOnScreen = false;
    }
  }
  else    //Если мы в режиме опыта
  {
    if (ExpNumb == 1)   //Если опыт 1
    {
      if (StartTime == 0)   //Проведение опыта еще не началось
      {
        if (!AllreadyOnScreen)
        {
          WriteOnScreen("Exp1", 0);   //Вывод на экран  
          AllreadyOnScreen = true;
        } 

        if (sensorFstState == LOW || sensorScndState == LOW)    //Если сработал один из сенсоров          
        {
          if (sensorFstState == LOW && sensorScndState == HIGH)   //Если сработал первый сенсор
          {
            FirstSensor = 1;    //Омечаем номер сенсора
            StartTime = millis();   //И ставим временную отметку начала опыта
          }
          if (sensorFstState == HIGH && sensorScndState == LOW)   //Если сработал второй сенсор
          {
            FirstSensor = 2;
            StartTime = millis();
          }

          AllreadyOnScreen = false;
        }
      }
      else    //Проведение опыта началось
      {
        if (EndTime == 0)   //Идет проведение опыта
        {
          AllreadyOnScreen = false;
          
          Interval = millis() - StartTime;      

          if (sensorFstState == LOW && sensorScndState == HIGH && FirstSensor == 2)   //Если сработал 1 сенсор (при учере, что 2 начал опыт)
          {
            EndTime = millis();   //И ставим временную отметку начала опыта
          }
          if (sensorFstState == HIGH && sensorScndState == LOW && FirstSensor == 1)   //Если сработал 2 сенсор (при учере, что 1 начал опыт)
          {
            EndTime = millis();
          }   
        }
        else    //Опыт завершен
        {
          Interval = EndTime - StartTime;    //Вычисляем итоговое время                  
        }

        if (!AllreadyOnScreen)
        {
          WriteOnScreen("Exp1", Interval);   //Вывод на экран  
          AllreadyOnScreen = true;
        }        
      }
    }

    if (ExpNumb == 2)   //Если опыт 2
    {
      if (StartTime == 0)   //Проведение опыта еще не началось
      {
        if (!AllreadyOnScreen)
        {
          WriteOnScreen("Exp2", 0);   //Вывод на экран  
          AllreadyOnScreen = true;
        }

        if (sensorFstState == LOW || sensorScndState == LOW)    //Если сработал один из сенсоров          
        {
          if (sensorFstState == LOW && sensorScndState == HIGH)   //Если сработал первый сенсор
          {
            FirstSensor = 1;    //Омечаем номер сенсора
            StartTime = millis();   //И ставим временную отметку начала опыта
          }
          if (sensorFstState == HIGH && sensorScndState == LOW)   //Если сработал второй сенсор
          {
            FirstSensor = 2;
            StartTime = millis();
          }

          AllreadyOnScreen = false;
        }
      }
      else
      {
        if (EndTime == 0)   //Идет проведение опыта
        {
          AllreadyOnScreen = false;
          
          Interval = millis() - StartTime; 

          if (FirstSensor == 1 && sensorFstState == LOW && sensorFstState != prevsensorFstState)    //1 датчик сработал второй раз
          {
            EndTime = millis();   //И ставим временную отметку начала опыта
          }
          if (FirstSensor == 2 && sensorScndState == LOW && sensorScndState != prevsensorScndState)   //2 датчик сработал второй раз
          {
            EndTime = millis();
          }
        }
        else
        {
          Interval = EndTime - StartTime;    //Вычисляем итоговое время 
        }
        
        if (!AllreadyOnScreen)
        {
          WriteOnScreen("Exp2", Interval);   //Вывод на экран  
          AllreadyOnScreen = true;
        }
      }
    }

    if (btnModeState == HIGH && prevbtnModeState != btnModeState)   //Если нажата кнопка режим
    {
      ExpNumb = -1;   //Обнуляем номер опыта
      Mode = 1;   //Возвращаемся в главное меню
      ZeroExp();
      AllreadyOnScreen = false;
      ModeBtnPressed = millis();
    }

    if (btnStartState == HIGH && prevbtnStartState != btnStartState)    //Если нажата кнопка старт
    {
      //Обнуляем данные таймеров - фактически рестартим опыт
      ZeroExp();
      AllreadyOnScreen = false;
    }
  }

//Запоминаем текущее состояние входных пинов
//Нужно это для того, чтобы при длительном нажатии на кнопку программа реагировала только на начало нажатия
//Для датчиков это нужно только для маятника, когда используется один сенсор и нужно отличать второе пересечение датчика от
//продолжающегося первого пересечения (т. е. пока груз летит мимо датчика, программа может несколько раз запросить его статус)
prevbtnModeState = btnModeState;
prevbtnStartState = btnStartState;
prevsensorFstState = sensorFstState;
prevsensorScndState = sensorScndState;
}

void WriteOnScreen(String Mode, unsigned long Val)
{ 
  if (Mode == "Main")   //вывод главного меню
  { 
    lcd.setCursor(0, 0);    //Курсор на первой строке
    
    if (Val == 1)   //Если 1 страница
    {
      lcd.print("ИНТЕРВАЛ"); //ИНТЕРВАЛ
      Serial.println("ИНТЕРВАЛ");
    }
    if (Val == 2)   //Если 2 страница
    {
      lcd.print("МАЯТНИК "); //МАЯТНИК
      Serial.println("МАЯТНИК");
    }

    lcd.setCursor(0, 1);    //Курсор на 2 строке
    lcd.print("        ");
  }

  if (Mode == "Exp1" || Mode == "Exp2")   //Вывод опыта
  {
    lcd.setCursor(0, 0);    //Курсор на 1 строке
    
    if (Mode == "Exp1")   //опыт про интервал
    {
      lcd.print("ВРЕМЯ   "); //ВРЕМЯ
      Serial.println("ВРЕМЯ");
    }

    if (Mode == "Exp2")   //опыт про маятник
    {
      lcd.print("ВРЕМЯ   "); //ВРЕМЯ
      Serial.println("ВРЕМЯ");
    }
    
    lcd.setCursor(0, 1);    //Курсор на 2 строке

    if (Val <= 9999)    //Если значение времени укладывается в 4 знака
    {
      String printer = String(Val) + "мс     ";
      lcd.print(printer); //xxxxмс
      Serial.println(printer);
    }
    else    //Если не укладывается в 4 знака - сообщаем об этом
    {
      lcd.print("----мс  "); //----мс
      Serial.println("----мс");
    }
  }
}

void ZeroExp()
{
  StartTime = 0;   
  EndTime = 0;
  FirstSensor = 0;
  Interval = 0;
}
