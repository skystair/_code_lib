#include "config.h"

unsigned short int u16time1MS;
unsigned short int u16time1S;

void MX_TIM1_Init(void);
void MX_TIM2_Init(void);

void MX_TIM1_Init(void)
{
//	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
//	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_HandleTypeDef	htim1;
	
	__HAL_RCC_TIM1_CLK_ENABLE();
	
	htim1.Instance = TIM1;
	htim1.Init.Prescaler = TIME1_DIV;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = TIME1_T;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
	{
		Error_Handler();
	}
//	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
//	if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
//	{
//		Error_Handler();
//	}
//	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
//	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
//	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
//	{
//		Error_Handler();
//	}
	
    /* TIM1 interrupt Init */
    HAL_NVIC_SetPriority(TIM1_UP_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);
	
//	HAL_TIM_Base_Start(&htim1);
	HAL_TIM_Base_Start_IT(&htim1);
}

void MX_TIM2_Init(void)
{
	TIM_HandleTypeDef	htim2;
//	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
//	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};
	
	__HAL_RCC_TIM2_CLK_ENABLE();
	
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = TIME2_DIV;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = TIME2_T;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}
//	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
//	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
//	{
//		Error_Handler();
//	}
	if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}
//	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
//	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
//	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
//	{
//		Error_Handler();
//	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}
	
//	HAL_TIM_Base_Start(&htim2);
//	HAL_TIM_OC_Start(&htim2,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);

}


void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{
  if(htim_base->Instance==TIM1)
  {
    __HAL_RCC_TIM1_CLK_DISABLE();
    /* TIM1 interrupt DeInit */
    HAL_NVIC_DisableIRQ(TIM1_UP_IRQn);
  }
  else if(htim_base->Instance==TIM2)
  {
    __HAL_RCC_TIM2_CLK_DISABLE();
  }

}


void TIM1_UP_IRQHandler(void)
{
	if((TIM1->SR &(TIM_FLAG_UPDATE)) == (TIM_FLAG_UPDATE))
	{
		if((TIM1->DIER & (TIM_IT_UPDATE)) == (TIM_IT_UPDATE))
		{
			//1MS================================================
			u16time1MS++;
			u8keydelay++;
			uirundelay++;
			
			if(u16time1MS >= 1000){
				u16time1MS = 0;
				
				u16time1S++;
				
			}
			
			
			
			
			
			Fan_func();
			LED_func();
			key_func();
			
			TIM1->SR = ~(TIM_IT_UPDATE);
		}
	}
}









