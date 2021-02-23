#include <Arduino.h>
#include <Adafruit_ADS1015.h>
#include <Adafruit_INA219.h>

Adafruit_ADS1115 ADC;
Adafruit_INA219 INA1(0x40);
Adafruit_INA219 INA2(0x41);

float adc_v_per_count;                   // multiply by ADC count to get voltage on ADC pin, based on ADC gain setting
const float ADC_V_PER_V_IN_1 = (11 / 1); // resistor divider on channel 1
const float ADC_V_PER_V_IN_2 = (11 / 1); // resistor divider on channel 2

void set_range_i_400mA()
{
  INA1.setCalibration_16V_400mA();
  INA2.setCalibration_16V_400mA();
}

void set_range_i_2000mA(){
  INA1.setCalibration_32V_2A();
  INA2.setCalibration_32V_2A();
}

void set_range_v_45V()
{
  ADC.setGain(GAIN_ONE);
  adc_v_per_count = 0.000125;
}

void set_range_v_22V()
{
  ADC.setGain(GAIN_TWO);
  adc_v_per_count = 0.0000625;
}

void set_range_v_11V()
{
  ADC.setGain(GAIN_FOUR);
  adc_v_per_count = 0.00003125;
}

void set_range_v_5V()
{
  ADC.setGain(GAIN_EIGHT);
  adc_v_per_count = 0.000015625;
}

float get_mV(uint8_t chan)
{
  float v = 0.0;

  if (chan == 0)
  {
    v = ADC.readADC_Differential_0_1() * adc_v_per_count * ADC_V_PER_V_IN_1;
  }
  else if (chan == 1)
  {
    v = ADC.readADC_Differential_2_3() * adc_v_per_count * ADC_V_PER_V_IN_2;
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

  set_range_i_2000mA();
  set_range_v_22V();

  ADC.begin();

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

    else if (byte == 'i'){
      set_range_i_400mA();
    }

    else if (byte == 'I'){
      set_range_i_2000mA();
    }

    else if (byte == 'v'){
      set_range_v_22V();
    }

    else if (byte == 'V'){
      set_range_v_45V();
    }
  }
}