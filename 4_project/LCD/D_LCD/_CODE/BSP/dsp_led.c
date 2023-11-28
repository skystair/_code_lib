#include "config.h"



void BspLedInit(void)
{
	GPIO_InitType GPIO_InitStructure;
//	RCC_EnableAPB2PeriphClk(LED_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.Pin        = LED_RED_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitPeripheral(LED_RED_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin        = LED_GREEN_PIN;
	GPIO_InitPeripheral(LED_GREEN_PORT, &GPIO_InitStructure);
}


