#ifndef _DUST_H
#define _DUST_H

#define DUST_ERROR_DELAY    (5000)	//5s

#define ucAD_Receive1	ADC_RECIEVE

typedef enum
{
    DustState_Stop,
    DustState_Start,
    DustState_CheckLow,
    DustState_CheckHigh,
    DustState_Calibrate,                // 校准
    DustState_Caculate,                 // 计算
    DustState_SurroundingHighLight      // 环境光太强
} Dust_State_t;


typedef struct 
{
    unsigned short int Tick;
    Dust_State_t State;
    unsigned char Error;

    signed short int Dac_Value;
    unsigned short int AdcValue_Buf[3];
    unsigned short int ADC_Value_Check_Low;
    unsigned short int ADC_Value_Check_High;
    unsigned short int Analog_Error_Tick;

    // 当前1s的灰尘个数
    unsigned short int Tick_200ms;
    unsigned short int Num_200ms;         // 灰尘个数累加。中断时加1，200ms读取一次并且清零
    unsigned short int NumRecord[5];      // 灰尘个数记录的缓冲,200ms一次
    unsigned short int Num_1s;            // 灰尘个数，1秒

    // 本次放电的灰尘个数
    unsigned int Num_Discharge;     // 本次放电的灰尘个数，原始值
    unsigned int Num_Discharge_M;   // 乘以放大系数
} Dust_t;
extern Dust_t Dust;

extern unsigned int Discharge_Tick_1ms;
extern unsigned int DusttickDelay;

void Dust_Start(void);
void Dust_Stop(void);

void Dust_Error_Clear(void);
void Dust_Error_Set(void);

void Dust_Task(void);



//#include "Dust_Analog.h"
//#include "Dust_Caculate.h"

#endif
