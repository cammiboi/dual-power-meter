#include <Arduino.h>
#include <Adafruit_ADS1015.h>
#include <Adafruit_INA219.h>

Adafruit_ADS1115 ADC;
Adafruit_INA219 INA1(0x40);
Adafruit_INA219 INA2(0x41);

const float ADC_V_PER_COUNT = 0.0000625; // multiply by ADC count to get voltage on ADC pin, based on ADC gain setting
const float ADC_V_PER_V_IN_1 = (11 / 1); // resistor divider on channel 1
const float ADC_V_PER_V_IN_2 = (11 / 1); // resistor divider on channel 2

float get_mV(uint8_t chan)
{
  float v = 0.0;

  if (chan == 0)
  {
    v = ADC.readADC_Differential_0_1() * ADC_V_PER_COUNT * ADC_V_PER_V_IN_1;
  }
  else if (chan == 1)
  {
    v = ADC.readADC_Differential_2_3() * ADC_V_PER_COUNT * ADC_V_PER_V_IN_2;
  }

  return v;
}

float get_mA(uint8_t chan)
{
  float i = 0.0;

  if (chan == 0)
  {
    i = INA1.getCurrent_mA();
  }
  else if (chan == 1)
  {
    i = INA2.getCurrent_mA();
  }

  return i;
}

void send_all_readings()
{
  Serial.println(get_mV(0));
  Serial.println(get_mA(0));
  Serial.println(get_mV(1));
  Serial.println(get_mA(1));
}

void setup()
{
  Serial.begin(115200);

  ADC.setGain(GAIN_TWO);
  ADC.begin();

  INA1.setCalibration_32V_2A();
  INA2.setCalibration_32V_2A();

  INA1.begin();
  INA2.begin();
}

void loop()
{
  if (Serial.available() > 0)
  {
    char byte = Serial.read();
    if (byte == 'R')
    {
      send_all_readings();
    }
  }
}