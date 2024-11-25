#define DT_IN  10
#define SCK_IN 2


unsigned long timing = 0; 

volatile int counter = 0;  // переменная-счётчик
unsigned long timeout = 0;
volatile union
{
  int32_t Value = 0x00FDE7C3;
  byte data[4];
} v;


void setup() {
  // put your setup code here, to run once:
  pinMode(SCK_IN, INPUT);
  pinMode(DT_IN, OUTPUT);

  digitalWrite(DT_IN, HIGH);
  attachInterrupt(0, clkIsr, RISING);
  timing = millis();
}

void clkIsr() {
  timeout = micros();
  if (++counter <= 24) {
    digitalWrite(DT_IN, bitRead(24 - counter, v.Value));
  }
  else {
    digitalWrite(DT_IN, HIGH);
  }
  if (counter == 27)counter = 0;
}


void loop() {
  if (micros() - timeout > 100) {
    counter = 0;
  }
  
  if (millis() - timing > 10000){ // Вместо 10000 подставьте нужное вам значение паузы
    timing = millis();
    digitalWrite(DT_IN, LOW);
  }
}
