#include "config.h"

unsigned int Flag_Time1ms;

void TimerValueInit(void);
void Timer_init(void);
void Timer_Deinit(void);
void Tim3_IRQHandler(void);


void TimerValueInit(void)
{
	Flag_Time1ms = 0;
}
void Timer_init(void)
{
    stc_tim3_mode0_cfg_t     stcTim3BaseCfg = {0};
    
    stcTim3BaseCfg.enWorkMode = Tim3WorkMode0;              //定时器模式
    stcTim3BaseCfg.enCT       = Tim3Timer;                  //定时器功能，计数时钟为内部PCLK
    stcTim3BaseCfg.enPRS      = Tim3PCLKDiv32;              //PCLK/16
    stcTim3BaseCfg.enCntMode  = Tim316bitArrMode;           //自动重载16位计数器/定时器
    stcTim3BaseCfg.bEnTog     = FALSE;
    stcTim3BaseCfg.bEnGate    = FALSE;
    stcTim3BaseCfg.enGateP    = Tim3GatePositive;
    
    Tim3_Mode0_Init(&stcTim3BaseCfg);                       //TIM3 的模式0功能初始化
    
    Tim3_M0_ARRSet(0x10000 - U16PERIOD);                    //设置重载值(ARR = 0x10000 - 周期)
    Tim3_M0_Cnt16Set(0x10000 - U16PERIOD);                  //设置计数初值
    
    //Tim3_ClearIntFlag(Tim3UevIrq);                          //清中断标志
    //Tim3_Mode0_EnableIrq();	//使能TIM3中断(模式0时只有一个中断)
    //EnableNvic(TIM3_IRQn, IrqLevel3, TRUE);                 //TIM3 开中断
	
	Tim3_M0_Run();   //TIM3 运行
}

void Timer_Deinit(void){
	stc_tim3_mode0_cfg_t     stcTim3BaseCfg = {0};
	
	Tim3_M0_Stop();
	
	Tim3_Mode0_Init(&stcTim3BaseCfg);
}



void Tim3_IRQHandler(void)
{
    //Timer3 模式0 计时溢出中断 //100us
    if(TRUE == Tim3_GetIntFlag(Tim3UevIrq))
    {
		//1MS===============================================
		Wdt_Feed();
		Flag_Time1ms++;
		StartdownloadDelay++;
        Tim3_ClearIntFlag(Tim3UevIrq);  //Timer3模式0 中断标志清除
    }
}
