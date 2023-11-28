#include "config.h"
#include "Dust_Caculate.h"

unsigned short int U16_Add_One(unsigned short int Num)
{
    if (Num < UINT16_MAX - 1)
    {
        Num++;
    }
    //
    return(Num);
}

unsigned int U32_Add_One(unsigned int Num)
{
    if (Num < UINT32_MAX - 1)
    {
        Num++;
    }
    //
    return(Num);
}

unsigned int U32_Add(unsigned int Num, unsigned int Step, unsigned int Max)
{
    if (Max - Num <= Step)
    {
        Num = Max;
    }
    else
    {
        Num += Step;
    }
    //
    return Num;
}

void Dust_EXTI_Irq(void)
{
    //////// 关中断
    Dust_Int_Disable();

    //////// 累加灰尘个数
//    if (AppState_Tester == App.State)   // 测试机
//    {
//        Dust.Num_Discharge++;
//    }
    
//    else if ((DustState_Caculate == Dust.State) || (DustState_SurroundingHighLight == Dust.State))
	if ((DustState_Caculate == Dust.State) || (DustState_SurroundingHighLight == Dust.State))
    {
        if (Discharge_Tick_1ms > 2000)   // 2秒之后再统计
        {
			Discharge_Tick_1ms = 2000;
            Dust.Num_200ms = U16_Add_One(Dust.Num_200ms);   // 中断一次，个数+1
            Dust.Num_Discharge = U32_Add_One(Dust.Num_Discharge);       // 本次放电的个数

            unsigned int Multiply = Dust_Get_Multiply();                                                    // 1个灰尘放大M倍
            Dust.Num_Discharge_M = U32_Add(Dust.Num_Discharge_M, Multiply, UINT32_MAX - 1);                             // 本次累计的灰尘M个数
            //Log_Data.u64_Dust_Num_Total = U64_Add(Log_Data.u64_Dust_Num_Total, Multiply, UINT64_MAX - 1);   // 历史累计的灰尘M个数
        }
    }
    else
    {
        Dust.Num_200ms = 0;
    }
}


unsigned short int Dust_Get_Multiply(void)
{
    unsigned short int Dust_MQ4;
    //
    if (Dust.Num_1s < 5)
    {
        Dust_MQ4 = 1;
    }
    else if (Dust.Num_1s < 250)
    {
        Dust_MQ4 = (uint64_t)Dust.Num_1s * Dust.Num_1s / 25;
    }
    else
    {
        Dust_MQ4 = 2500;
    }
    //
    return (Dust_MQ4);
}

void Dust_Caculate(void)
{
    switch (Dust.State)
    {
        case DustState_Stop:
        case DustState_Start:
            //////// Phone
            //Phone_Dust_Value_Set(0);
            break;

        case DustState_CheckLow:
        case DustState_CheckHigh:
        case DustState_Calibrate:
        case DustState_Caculate:
        case DustState_SurroundingHighLight:
            Dust.Tick_200ms++;
            if (Dust.Tick_200ms >= 200)
            {
                Dust.Tick_200ms = 0;

                //////// 计算1s的灰尘个数
                Dust.NumRecord[4] = Dust.NumRecord[3];
                Dust.NumRecord[3] = Dust.NumRecord[2];
                Dust.NumRecord[2] = Dust.NumRecord[1];
                Dust.NumRecord[1] = Dust.NumRecord[0];
                Dust.NumRecord[0] = Dust.Num_200ms;
                Dust.Num_200ms = 0;                     // 在中断里累加
                //
                Dust.Num_1s = Dust.NumRecord[0] + Dust.NumRecord[1] + Dust.NumRecord[2] + Dust.NumRecord[3] + Dust.NumRecord[4];

                //////// Phone
                //Phone_Dust_Value_Cycle_Set(Dust.Num_1s);
            }
            break;

        default:
            break;
    }
}
