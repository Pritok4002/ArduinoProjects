//============================================
// ADC demo for Larduino w/ LGT8F328D
// Using new added internal 2.56V reference
//============================================

int16_t sensor1 = 0;
int16_t sensor2 = 0;
int16_t sensor3 = 0;
int16_t sensor4 = 0;
void setup() {
  // put your setup code here, to run once:
  //analogReference(EXTERNAL);
  analogReadResolution(12);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
 
  Serial.begin(489600);
  
}


void loop() {
  sensor1 = analogRead(A0);
  sensor2 = analogRead(A1);
  sensor3 = analogRead(A2);
  sensor4 = analogRead(A3);
  
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
  
 /* Serial.print(first, BIN);
  Serial.print("!");
  Serial.print(second, BIN);
 
  Serial.print(" - ");
  Serial.print(value);
  Serial.print(" - ");
  Serial.println(value, BIN);
  */
  delay(1);
}
