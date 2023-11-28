#include "bsp_pvd.h"

void BspPvdInit(void)
{
	EXTI_InitType EXTI_InitStructure;
	NVIC_InitType NVIC_InitStructure;
	
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR | RCC_APB1_PERIPH_BKP, ENABLE);
	
	EXTI_ClrITPendBit(EXTI_LINE16);
	EXTI_InitStructure.EXTI_Line    = EXTI_LINE16;
	EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitPeripheral(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel                   = PVD_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 5;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	PWR_PvdRangeConfig(PWR_PVDRANGRE_2V2);
	PWR_PvdEnable(ENABLE);
}


