#define DT_IN  12
#define SCK_IN 2

volatile int counter = 0;  // переменная-счётчик
union
{
int32_t Value = 0x00FDE7C3;
byte data[4];
}v;


void setup() {
  // put your setup code here, to run once:
pinMode(SCK_IN, INPUT);
pinMode(DT_IN, OUTPUT);

digitalWrite(DT_IN,HIGH);
attachInterrupt(0, clkIsr, RISING);
}

void clkIsr() {
  if(++counter<=25)
  v.Value = shiftOut(DT_IN, 13,MSBFIRST);
  if(counter==27)counter = 0;
  
}


void loop() {
  // put your main code here, to run repeatedly:
  delay(10000);
  digitalWrite(DT_IN,LOW);
}
