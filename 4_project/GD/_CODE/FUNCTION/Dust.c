#include "config.h"


Dust_t Dust = {0};

void Dust_Start(void)
{
    Dust.Tick = 0;
    Dust.Analog_Error_Tick = 0;
    Dust_DacSet(DUST_DAC_OutputLow_InputHigh);
    Dust.State = DustState_CheckLow;
    //
    Dust.Num_200ms = 0;
    Dust.NumRecord[0] = 0;
    Dust.NumRecord[1] = 0;
    Dust.NumRecord[2] = 0;
    Dust.NumRecord[3] = 0;
    Dust.NumRecord[4] = 0;
    //
    Dust.Num_Discharge = 0;     // 本次放电灰尘中断个数
    Dust.Num_Discharge_M = 0;   // 乘法系数加成
    //
    Dust.ADC_Value_Check_Low = 0;
    Dust.ADC_Value_Check_High = 0;
	Discharge_Tick_1ms = 0;
}
void Dust_ReStart(void)
{
    Dust.Tick = 0;
    Dust.Analog_Error_Tick = 0;
    Dust_DacSet(DUST_DAC_OutputLow_InputHigh);
    Dust.State = DustState_CheckLow;
}

void Dust_Stop(void)
{
    Dust_DacSet(0);
    Dust_Error_Clear();
    Dust.State = DustState_Stop;
}


void Dust_Error_Clear(void)
{
    Dust.Error = 0;
    //
}
void Dust_Error_Set(void)
{
    Dust.Error = 1;
    //
}



void Dust_Task(void)
{
	Dust_AdcValue_Read();

	switch (Dust.State)
	{
		case DustState_Stop:
			break;

		case DustState_Start:
			break;

		case DustState_CheckLow:
			if (Dust.Tick < 10)
			{
				Dust.Tick++;
			}
			else
			{
				if (Dust.Tick < DUST_ERROR_DELAY)
				{
					Dust.Tick++;
				}
				else
				{
					Dust_Error_Set();
				}

				////
				if (0 == DustVoltage_IsDiff3(Dust.AdcValue_Buf))    // 已经稳定，跳转
				{
					Dust.ADC_Value_Check_Low = Dust.AdcValue_Buf[0];
					if (AD_HWDUST < DUST_ADC_OutputLow_InputHigh)	//2233 输入正常，小于1.8V
					{
						Dust.Tick = 0;
						Dust_DacSet(DUST_DAC_OutputHigh_InputLow);
						Dust.State = DustState_CheckHigh;
					}
					else									                // 输入超压，环境光太强
					{
						Dust.Tick = 0;
						Dust_DacSet(DUST_DAC_STANDARD);
						Dust.State = DustState_SurroundingHighLight;
					}
				}
			}
			break;

		case DustState_CheckHigh:
			if (Dust.Tick < 10)
			{
				Dust.Tick++;
			}
			else
			{
				if (Dust.Tick < DUST_ERROR_DELAY)
				{
					Dust.Tick++;   
				}
				else
				{
					Dust_Error_Set();
				}
				//
				if (0 == DustVoltage_IsDiff3(Dust.AdcValue_Buf))    // 已稳定，跳转
				{
					if (AD_HWDUST < DUST_ADC_OutputHigh_InputLow)	// 输入欠压
					{
						// 卡住不要跳转
					}
					else									// 输入正常
					{
						Dust.Tick = 0;
						Dust_DacSet(DUST_DAC_STANDARD);
						Dust.State = DustState_Calibrate;

						Dust.ADC_Value_Check_High = Dust.AdcValue_Buf[0];
					}
				}
			}
			break;

		case DustState_Calibrate:
			if (Dust.Tick < 10)
			{
				Dust.Tick++;
			}
			else
			{
				if (0 == Dust_Analog_Regulate())    // 校准完成
				{
					Dust.Tick = 0;
					Dust_Error_Clear();
					Dust.State = DustState_Caculate;
				}
				else                                // 校准未完成
				{
					if (Dust.Tick < DUST_ERROR_DELAY)
					{
						Dust.Tick++;
					}
					else
					{
						if (AD_HWDUST > DUST_ADC_OutputLow_InputHigh)	// 输入超压
						{
							Dust.Tick = 0;
							Dust_DacSet(DUST_DAC_STANDARD);
							Dust.State = DustState_SurroundingHighLight;
						}
						else
						{
							Dust_Error_Set();
						}
						
					}
				}
			}
			
			break;

		case DustState_Caculate:
			if (Dust.Tick < 10)
			{
				Dust.Tick++;
				
			}
			else
			{
				Dust_Int_Enable();              // 开中断


				//// 电压异常检测
				if (0 != DustVoltage_NotStandardCheck())    // 存在异常
				{
					Dust_ReStart();
				}
			}
			
			break;

		case DustState_SurroundingHighLight:
			if (Dust.Tick < 10)     // 等待10ms
			{
				Dust.Tick++;
			}
			else
			{
				Dust_Int_Enable();              // 开中断


				if (AD_HWDUST < (DUST_ADC_OutputLow_InputHigh - VOLTAGE_2_ADC(50)))	// 输入正常
				{
					Dust_ReStart();
				}
			}
			break;

		default:
			break;
	}
	//////// 
	Dust_Caculate();
}

