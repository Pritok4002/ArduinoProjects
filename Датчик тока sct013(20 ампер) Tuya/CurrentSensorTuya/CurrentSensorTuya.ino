const float FACTOR = 20; //20A/1V
const float ADCV = 3.3;  //For Vcc

const float VMIN = 1.638 - 1.414;
const float VMAX = 1.638 + 1.414;

const int N = 90;
float peekCurrent[N];
int peekCurrentPointer = 0;

const int rmsBufferSize =30;
float rmsBuffer[rmsBufferSize];
int rmsBufferPointer = 0;
float rmsMid = 0;
bool rmsFlag = false;

long timer1 = 0;
long timer2 = 0;

float maxCurrent = 0;
float minCurrent = 0;
float RMS = 0;

#include "LiquidCrystalRus-master/LiquidCrystalRus.cpp"
//#include <LiquidCrystalRus.h>
LiquidCrystalRus lcd(7, 6, 5, 4, 3, 2);


#include "tuya-wifi-mcu-sdk/src/TuyaWifi.cpp"
#include "tuya-wifi-mcu-sdk/src/TuyaTools.cpp"
#include "tuya-wifi-mcu-sdk/src/TuyaDataPoint.cpp"
#include "tuya-wifi-mcu-sdk/src/TuyaExtras.cpp"
#include "tuya-wifi-mcu-sdk/src/TuyaUart.cpp"
TuyaWifi my_device;
unsigned char pid[] = { "shdvewg2m7gnaj70" };
unsigned char mcu_ver[] = { "1.0.0" };
/* Current LED status */
int led_state = 0;
/* Connect network button pin */
int wifi_key_pin = 12;
int outputPin = 11;

unsigned long last_time = 0;
unsigned long last_time2 = 0;
bool ButtonFlagState;
unsigned long ButtonTime = 0;

#define DPID_CurrentSensor 101
#define DPID_OutputPin 102
unsigned char dp_array[][2] = {
  { DPID_CurrentSensor, DP_TYPE_VALUE },
  { DPID_OutputPin, DP_TYPE_BOOL }
};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  lcd.begin(8, 2);


  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(outputPin, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  //Initialize networking keys.
  pinMode(wifi_key_pin, INPUT_PULLUP);

  my_device.init(pid, mcu_ver);
  my_device.set_dp_cmd_total(dp_array, 2);
  my_device.dp_process_func_register(dp_process);
}

void loop() {
  my_device.uart_service();

  if (micros() - timer1 > 350)
  {
    
    //Serial.println(micros()-timer1);
    timer1 = micros();
    peekCurrent[peekCurrentPointer] = ADC_To_Current(analogRead(0));
    
    peekCurrentPointer++;
    if (peekCurrentPointer == N)
    {
      peekCurrentPointer = 0;
      RMS=CalcRMS();
      rmsBuffer[rmsBufferPointer] = RMS;
      rmsBufferPointer++;
      if(rmsBufferPointer==rmsBufferSize)
      {
        rmsBufferPointer = 0;
        rmsFlag = true;
      }
    }
  }
    if(millis()-timer2>1000 && rmsFlag)
    {

    timer2=millis();
        float rmsSum  = 0;
        for(int i =0;i<rmsBufferSize;i++)
        {
          rmsSum +=rmsBuffer[i];
        }
        rmsMid = rmsSum/rmsBufferSize;
        lcd.setCursor(0, 1);
  lcd.print(rmsMid, 2);
  lcd.print(" ");
  int rmsint = (int)rmsMid*100;
  my_device.mcu_dp_update(DPID_CurrentSensor, rmsint, sizeof(rmsint));
   //Serial.println("\trms =" + (String)rmsMid);
    }

    //Enter the connection network mode when Pin7 is pressed.
  if (digitalRead(wifi_key_pin) == LOW) {

    if (ButtonTime + 5000 < millis()) {
      my_device.mcu_reset_wifi();
      delay(100);
      my_device.mcu_set_wifi_mode(SMART_CONFIG);
      //lcd.print(analogRead(2));
      ButtonTime = millis();
    }
  } else {
    ButtonTime = millis();
  }

  if (my_device.mcu_get_wifi_work_state() ==  AP_STATE) {
    lcd.setCursor(0, 0);
    //lcd.print("Сопряжение    ");
    if (millis() - last_time2 >= 1000) {

      last_time2 = millis();
      /* Toggle current LED status */
      if (led_state == LOW) {
        led_state = HIGH;
      } else {
        led_state = LOW;
      }
      digitalWrite(LED_BUILTIN, led_state);
    }
  }

  if (my_device.mcu_get_wifi_work_state() == SMART_CONFIG_STATE) {
    lcd.setCursor(0, 0);
    //lcd.print("Сопряжение    ");
    if (millis() - last_time >= 100) {

      last_time = millis();
      /* Toggle current LED status */
      if (led_state == LOW) {
        led_state = HIGH;
      } else {
        led_state = LOW;
      }
      digitalWrite(LED_BUILTIN, led_state);
    }
  }
    if (my_device.mcu_get_wifi_work_state() == WIFI_CONNECTED && my_device.mcu_get_wifi_work_state() != SMART_CONFIG_STATE) {
    digitalWrite(LED_BUILTIN, 1);
    //my_device.mcu_dp_update(temp_id, dp_value_value, sizeof(dp_value_value));
    //dp_update_all();
  }

}
float CalcRMS()
{
  //Serial.println("calcrms");
  double Sum = 0;
  float RMS = 0;
  for (int i = 0; i < N; i++)
  {
    Sum = Sum + peekCurrent[i]*peekCurrent[i];
    //Serial.print((String)peekCurrent[i]+"\t");
  }
  //Serial.println();
  RMS = sqrt((1.0/N)*Sum);
  return RMS;
}
/*
float CalcMax()
{
  //Serial.println("calcMax");
  float maxval = 0;
  for (int i = 0; i < N; i++)
  {
    if (maxval < peekCurrent[i])
    {
      //Serial.println((String)maxval+"<"+(String)peekCurrent[i]);
      maxval = peekCurrent[i];
    }
  }
  return maxval;
}
float CalcMin()
{
  float minval = 50;
  for (int i = 0; i < N; i++)
  {
    if (minval > peekCurrent[i])
    {
      minval = peekCurrent[i];
    }
  }
  return minval;
}
*/
float ADC_To_Current(int adc)
{
  float voltage = adc * ADCV / 1023.0-1.638;
  //float Current = fmap(voltage, VMIN, VMAX, -FACTOR, FACTOR);
  float Current = voltage*16;
  if(Current<0.5&&Current>-0.5)
  Current=0;
  return Current;
}
float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

unsigned char dp_process(unsigned char dpid, const unsigned char value[], unsigned short length) {
  switch (dpid) {
    case DPID_OutputPin:
      bool dp_bool_value = my_device.mcu_get_dp_download_data(dpid, value, length);
      lcd.setCursor(0, 0);
      lcd.print("Выход :");
      lcd.print((bool)dp_bool_value);
      lcd.print("        ");
      digitalWrite(outputPin, dp_bool_value);
      /* After processing the download DP command, the current status should be reported. */
      //my_device.mcu_dp_update(output_id, dp_bool_value, 1);
      break;
/*
    case temp_id:
      dp_value_value = my_device.mcu_get_dp_download_data(dpid, value, length);
      lcd.setCursor(0, 0);
      lcd.print("batt :");
      lcd.print((int)dp_value_value);
      lcd.print("        ");
      // After processing the download DP command, the current status should be reported. 
      my_device.mcu_dp_update(temp_id, dp_value_value, 1);
      break;
*/

    default:
      break;
  }

  return TY_SUCCESS;
}
