#define PeriodTime 10
#define BufferSize 256
uint16_t SensorBuffer[BufferSize];

void setup() {
  //Serial.begin(115200);
  Serial.begin(489600);
  // put your setup code here, to run once:
  /*for(uint16_t i = 0;i<BufferSize;i++)
    {
    SensorBuffer[i] = analogRead(0);
    Serial.println(SensorBuffer[i]);
    delay(PeriodTime/BufferSize*1000);
    }*/
}
int counter = 0;
uint32_t timer = 0;   // переменная таймера
#define T_PERIOD 10  // период переключения


int sensor1 = 0;
int sensor2 = 0;
void loop() {


  //
  int sensor3 = 0;
  int sensor4 = 0;
  //sensor1 = analogRead(A0)*4;

  if (millis() - timer >= T_PERIOD) { // таймер на millis()
    timer = millis(); // сброс
    sensor1 = analogRead(A0) * 4;
    SensorBuffer[counter++] = sensor1;
    if (counter >= BufferSize - 1)
    {
      counter = 0;  // закольцовываем изменение
      sensor2 = CalcMid();
    }
  }

  byte sensor1_first = sensor1 & 0b0000000001111111;
  byte sensor1_second = sensor1 >> 7;
  sensor1_second = sensor1_second & 0b00011111;
  sensor1_second = sensor1_second | 0b10000000;
  Serial.write(sensor1_first);
  Serial.write(sensor1_second);

  byte sensor2_first = sensor2 & 0b0000000001111111;
  byte sensor2_second = sensor2 >> 7;
  sensor2_second = sensor2_second & 0b00011111;
  sensor2_second = sensor2_second | 0b10100000;
  Serial.write(sensor2_first);
  Serial.write(sensor2_second);


  byte sensor3_first = sensor3 & 0b0000000001111111;
  byte sensor3_second = sensor3 >> 7;
  sensor3_second = sensor3_second & 0b00011111;
  sensor3_second = sensor3_second | 0b11000000;
  Serial.write(sensor3_first);
  Serial.write(sensor3_second);


  byte sensor4_first = sensor4 & 0b0000000001111111;
  byte sensor4_second = sensor4 >> 7;
  sensor4_second = sensor4_second & 0b00011111;
  sensor4_second = sensor4_second | 0b11100000;
  Serial.write(sensor4_first);
  Serial.write(sensor4_second);

  delayMicroseconds(800);

}
int CalcMid()// найти среднию точку массива
{
  uint32_t Result = 0;
  for (uint16_t i = 0; i < BufferSize; i++)
  {
    Result += SensorBuffer[i];
  }
  return Result / BufferSize;
}
int GetHBPS() {
  int BeatsCount = 0;
  bool BeatFlag = false;
  int Middle = CalcMid();
  for (int i = 0; i < BufferSize; i++)
  {
    if (SensorBuffer[i] > Middle && !BeatFlag)
    {
      BeatsCount++;
      BeatFlag = true;
    }
    else if (SensorBuffer[i] < Middle && BeatFlag)
    {
      BeatFlag = false;
    }
  }
}
