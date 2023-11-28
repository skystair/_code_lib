#include "config.h"

//float changeV(int code);
unsigned int uirundelay;

int main(void)
{
	HAL_Init();
	SystemClock_Config();//32M	

	MX_GPIO_Init();
	IIC_Init();
	
	MX_SPI1_Init();
	MX_SPI2_Init();
	MX_TIM1_Init();	//1k timer
	MX_TIM2_Init();	//1k pwm
	
	MX_USART1_UART_Init();

	u16FAN_duty = 800;
	printf("APP run...\r\n");	
	
//	if (ad7124_app_initialize(AD7124_CONFIG_A) < 0 ) {while(1);}

	OLED_init();
	while (1)
	{
		if(uirundelay <= 100){
			func_adc(pAd7124_dev);
		}else{
			Deal_HT();
			OLED_func();
			for(unsigned char i = 0;i < 8;i++){
			Vad[i] += 1;
			
			uirundelay = 0;
			}
		}
	}
}






//float changeV(int code)
//{
//	float vo=0;
//	vo = 2500.0*(code - 0x800000)/(4.0*0x800000);
//	return vo;
//}


	//TIM1ŚՋѐì1MS/============================================
//		Fan_func();
//		LED_func();
//		key_func();

//		OLED_func();


//		HAL_GPIO_TogglePin( TEST_LED_GPIO_Port, TEST_LED_Pin);
//		HAL_Delay(1000);

//	MX_IWDG_Init();
//		IWDG->KR = IWDG_KEY_RELOAD;

