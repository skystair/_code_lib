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
#include "LCD28/LCD_lib.h"
#include <stdio.h>
#include "User_systick.h"
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
	uint8_t i;
	lcd_init();
	lcd_display_string( 60,60,(uint8_t* )"CPU:STM32F405RGT6          ", FONT_1206, RED );
	lcd_display_string( 60,80,(uint8_t* )"www.WaveShare.net          ", FONT_1206, RED );
	for(i = 0;i<7;i++)
		lcd_display_GB2312( i,RED,60+i*16,100);
	
	lcd_draw_line(80,150,120,180,BLACK);
	lcd_draw_circle(120,210,20,BLUE);
	lcd_draw_rect(100,250,50,50,GREEN);
	lcd_fill_rect(30,220,50,50,RED);
 	while (1)
  	{

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

