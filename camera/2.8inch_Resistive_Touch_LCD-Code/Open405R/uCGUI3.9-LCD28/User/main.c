/*********************************************************************************************************
*
* File                : main.c
* Hardware Environment: 
* Build Environment   : RealView MDK-ARM  Version: 4.20
* Version             : V1.0
* By                  : 
*
*                                  (c) Copyright 2005-2011, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "LCD28/LCD_Driver.h"
#include "LCD28/TIM3_PWM.h"
#include <stdio.h>
#include "includes.h"

void TIME_init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    TIM_DeInit(TIM2);            //��λ��ʱ��
    TIM_TimeBaseStructure.TIM_Period=20;  //   //2000Ϊ1S
    TIM_TimeBaseStructure.TIM_Prescaler=(6000-1);         //ʱ��Ԥ��Ƶ  120M/60000=20KHz
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;  // ʱ�ӷָ�
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);   //��ʼ����ʱ����ֵ
    TIM_ClearFlag(TIM2,TIM_FLAG_Update);               //�����ʱ���жϱ�־ 
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);  //ʹ���ж�
    TIM_Cmd(TIM2,ENABLE);            //����ʱ��
 
}


void NVIC_init(void)//Ƕ���ж�����
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_Init(&NVIC_InitStructure); 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);               
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;   //ѡ��TIM2�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;   //
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ��
    NVIC_Init(&NVIC_InitStructure); 

}
/*******************************************************************************
* Function Name  : Delay
* Description    : Delay Time
* Input          : - nCount: Delay Time
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void  Delay (uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}


/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
int main(void)
{
	NVIC_init();
	TIME_init();
	//SystemInit();
 	
	
	GUI_Init();
 	while (1)
  	{
		     GUIDEMO_main();	
   	}
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

