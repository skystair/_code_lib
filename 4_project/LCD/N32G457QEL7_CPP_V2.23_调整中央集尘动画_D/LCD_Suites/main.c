#include <stdio.h>
#include "bsp_bkp.h"
#include "bsp_Dma.h"
#include "bsp_IdleIO.h"
#include "bsp_iwdog.h"
#include "bsp_pvd.h"
#include "bsp_pwm.h"
#include "bsp_rtc.h"
#include "bsp_time.h"
#include "bsp_usart.h"
#include "delay.h"
#include "dsp_led.h"
#include "flash_access.h"
#include "lcd_driver.h"
#include "spi_flash.h"
#include "spi_lcd.h"
#include "Draw.h"
//#include "Decode.h"
//#include "DecodeFont.h"
//============================================

Draw* draw;
//Decode* decode;
unsigned int ReflashCount;
unsigned int ValidReflashCount;
unsigned int currentReflashCount;
unsigned int  ValidCount;
//float UsageRate;
//float SumUsageRate;
//float AverageUsageRate;

extern const unsigned char gImage_2[115200];
int main()
{
	FLASH_PrefetchBufSet(FLASH_PrefetchBuf_EN);
	FLASH_iCacheCmd(FLASH_iCache_EN);

	BSP_IdleIO_Init();
	
	sFLASH_Init();

	LCD_Init();
	lcd_clear(0);
	
	BspLedInit();
	
	Time1msInit();
	Bsp_Usart_Init();

	BspMemDmaInit();
	
	draw = new Draw;
	
	BspIwdogInit();//������RTC����֮�� RTC������Drawģ�鹹�캯���е���
	BspPvdInit();
	
	if(!BspIsIwdogReset())
	{//�����ɿ��Ź�����ĸ�λ ��ʼ������
		draw->Init();
	}
	else
	{
		draw->ReloadPage();
	}

	currentReflashCount = 0;
	ValidReflashCount = 0;
	ValidCount = 0;
//	SumUsageRate = 0;
	
	for(unsigned int i = 0; i < 115200; i++)
	{
		lcd_write_data(gImage_1[i]);
	}
	while(1)
	{
		SET_PWM_DUTY_RATIO(1);
//		ReflashCount = 0;
//		
//		draw->Handle();
//		
//		BspIwdogReload();
//		
//		currentReflashCount = ReflashCount;
//		if(currentReflashCount > 10)
//		{
//			ValidReflashCount = currentReflashCount;
////			UsageRate = 100 * ValidReflashCount/80.0;
////			SumUsageRate += UsageRate;
//			if(++ValidCount > 10)
//			{
////				AverageUsageRate = SumUsageRate / 10;
////				SumUsageRate = 0;
//				ValidCount = 0;
//			}
//		}

	}
}

