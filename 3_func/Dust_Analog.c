#include "config.h"
#include "Dust_Analog.h"


//////// DAC ////////
void Dust_DacSet(unsigned short int x)
{
    Dust.Dac_Value = x;
    DAC_ValueSet(x);
}


//////// ADC ////////
void Dust_AdcValue_Read(void)
{
    Dust.AdcValue_Buf[2] = Dust.AdcValue_Buf[1];
    Dust.AdcValue_Buf[1] = Dust.AdcValue_Buf[0];
    Dust.AdcValue_Buf[0] = AD_HWDUST;
}



unsigned short int DValue(unsigned short int v1, unsigned short int v2)
{
    unsigned short int dValue;
    if (v1 > v2)
    {
        dValue = v1 - v2;
    }
    else
    {
        dValue = v2 - v1;
    }
    return(dValue);
}



#define DUST_VOLTAGE_DIFF_MAX	(100)	//((unsigned short int)(0.03 *0xFFF/3.3))
// 0接近，1差异大
unsigned char DustVoltage_IsDiff3(unsigned short int *pV)
{
    if (DValue(pV[0], pV[1]) > DUST_VOLTAGE_DIFF_MAX)
    {
        return(1);
    }
    if (DValue(pV[1], pV[2]) > DUST_VOLTAGE_DIFF_MAX)
    {
        return(1);
    }

    return(0);
}



unsigned short int Dust_Analog_Tick = 0;
unsigned short int Dust_Analog_Interval = 1;     // 调节的tick间隔
// 0    正常范围 ±0.05V
// 1    调节范围 ±0.15V
unsigned char Dust_Analog_Regulate(void)
{
    unsigned char AdcValue_IsOutOfRange = 1;
    //
    Dust_Analog_Tick++;
    if (Dust_Analog_Tick >= Dust_Analog_Interval)
    {
        Dust_Analog_Tick = 0;
        //
        Dust_AdcValue_Read();
        if (0 == DustVoltage_IsDiff3(Dust.AdcValue_Buf))    // 电压稳定时才作为有效数据
        {
            //////// 微调
            if (AD_HWDUST < (DUST_ADC_STANDARD - VOLTAGE_2_ADC(50)))         // 电压偏小，应当调大
            {
                if (Dust.Dac_Value < DUST_DAC_MAX)
                {
                    if (DUST_ADC_STANDARD - AD_HWDUST < VOLTAGE_2_ADC(100))       // 偏差较小， (50mV, 100mV)
                    {
                        Dust_Analog_Interval = 5;
                        Dust.Dac_Value++;
                    }
                    else if (DUST_ADC_STANDARD - AD_HWDUST < VOLTAGE_2_ADC(300))  // 偏差中等， (100mV, 300mV)
                    {
                        Dust_Analog_Interval = 2;
                        Dust.Dac_Value += 2;
                    }
                    else
                    {
                        Dust_Analog_Interval = 1;
                        Dust.Dac_Value += 3;
                    }
                    
                    if (Dust.Dac_Value > DUST_DAC_MAX)
                    {
                        Dust.Dac_Value = DUST_DAC_MAX;
                    }
                }
            }
            else if (AD_HWDUST > (DUST_ADC_STANDARD + VOLTAGE_2_ADC(50)))
            {
                if (Dust.Dac_Value > DUST_DAC_MIN)
                {
                    if (AD_HWDUST - DUST_ADC_STANDARD < VOLTAGE_2_ADC(100))
                    {
                        Dust_Analog_Interval = 5;
                        Dust.Dac_Value--;
                    }
                    else if (AD_HWDUST - DUST_ADC_STANDARD < VOLTAGE_2_ADC(300))
                    {
                        Dust_Analog_Interval = 2;
                        Dust.Dac_Value -= 2;
                    }
                    else
                    {
                        Dust_Analog_Interval = 1;
                        Dust.Dac_Value -= 3;
                    }

                    if (Dust.Dac_Value < DUST_DAC_MIN)
                    {
                        Dust.Dac_Value = DUST_DAC_MIN;
                    }
                }
            }
            else    // 正常范围 ±50mV
            {
                AdcValue_IsOutOfRange = 0;
            }
            //
            DAC_ValueSet(Dust.Dac_Value);
        }
    }
    return (AdcValue_IsOutOfRange);
}




unsigned char DustVoltage_NotStandardCheck(void)
{
    unsigned char IsError = 0;
    //
    if ((AD_HWDUST < DUST_ADC_STANDARD - DUST_ADC_RANGE) 
        || (AD_HWDUST > DUST_ADC_STANDARD + DUST_ADC_RANGE))
    {
        if (Dust.Analog_Error_Tick < 1000)
        {
            Dust.Analog_Error_Tick++;
        }
        else
        {
            IsError = 1;
        }
    }
    else
    {
        Dust.Analog_Error_Tick = 0;
    }
    //
    return (IsError);
}

