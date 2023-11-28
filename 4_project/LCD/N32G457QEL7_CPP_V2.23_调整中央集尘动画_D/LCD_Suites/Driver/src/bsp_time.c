#include "bsp_time.h"

void TIM_Configuration(void)
{
    TIM_TimeBaseInitType TIM_TimeBaseStructure;

    /* PCLK1 = HCLK/4   128/4=32MHz */
    RCC_ConfigPclk1(RCC_HCLK_DIV4);

    /* TIM2 clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2, ENABLE);
    
    /* Time base configuration */
    TIM_TimeBaseStructure.Period    = 32000;
    TIM_TimeBaseStructure.Prescaler = 0;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;

    TIM_InitTimeBase(TIM2, &TIM_TimeBaseStructure);

    /* Prescaler configuration */
    TIM_ConfigPrescaler(TIM2, 1, TIM_PSC_RELOAD_MODE_IMMEDIATE);

    /* TIM2 enable update irq */
    TIM_ConfigInt(TIM2, TIM_INT_UPDATE, ENABLE);

    /* TIM2 enable counter */
    TIM_Enable(TIM2, ENABLE);
}

void TIM_NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;

    /* Enable the TIM2 global Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
}

void Time1msInit(void)
{
	TIM_Configuration();
	TIM_NVIC_Configuration();
}

