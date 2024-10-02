String Morze = ".--. .-. .. - --- -.-";
const long interval1 = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  for(int i = 0; i < Morze.length(); i++)
  {
    if (Morze[i]=='.') {
      digitalWrite(LED_BUILTIN, 1);
      delay(interval1);
      digitalWrite(LED_BUILTIN, 0);
    }
    else if (Morze[i]=='-'){
      digitalWrite(LED_BUILTIN, 1);
      delay(interval1*3);
      digitalWrite(LED_BUILTIN, 0);
    }
    delay(interval1);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
