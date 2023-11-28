#include "n32g45x.h"
#include "spi_lcd.h"
#include "lcd_driver.h"

#include "Draw.h"

extern Draw* draw;

extern unsigned int ReflashCount;
extern "C" void TIM2_IRQHandler(void)
{
	if (TIM_GetIntStatus(TIM2, TIM_INT_UPDATE) != RESET)
	{
		TIM_ClrIntPendingBit(TIM2, TIM_INT_UPDATE);

		ReflashCount++;
		draw->Tick(1);
//		V2205DrawTick(1);
	}
}

uint8_t RXdatabyte;
uint8_t RXdata[20];  
extern "C" void USART3_IRQHandler()
{
	static	uint8_t RX_data_cun=0, RX_stat=0;
	uint8_t i,j=15;
	uint16_t aRxBuffer_SUM=0;
	if(USART_GetFlagStatus(USART3, USART_FLAG_OREF) != RESET) //中断溢出中断
	{
		
	}
	if(USART_GetFlagStatus(USART3, USART_FLAG_NEF) != RESET) //噪声错误中断
	{
		
	}
	if(USART_GetFlagStatus(USART3, USART_FLAG_FEF) != RESET) //帧错误中断
	{
		
	}
	
	if(USART_GetFlagStatus(USART3, USART_FLAG_RXDNE) != RESET)
	{
		USART_ClrFlag(USART3, USART_FLAG_RXDNE);
		USART_ClrIntPendingBit(USART3, USART_INT_RXDNE);
		RXdatabyte = (uint8_t)USART_ReceiveData(USART3);
		if((RXdatabyte==0xAC)&&(RX_stat==0))  //判断接收头  0xAC
		{  
			RX_data_cun=0;
			RX_stat=1;
			RXdata[RX_data_cun]=0xAC;
			RX_data_cun++;
		}
		else if(RX_stat)
		{
			RXdata[RX_data_cun]=RXdatabyte; 
			if((RXdata[0]!=0xAC)||(RXdata[1]!=0x03)) //检查前两个数据接收数据错误  0xAC 和0X03
			{
				RX_data_cun=0;   //接收错误
				RX_stat=0;
				for(i=0;i<j;i++)
				{
					RXdata[i]=0;
				}
			}
			else
				RX_data_cun++; //继续接收
			
			if(RX_data_cun>=j)  //接收完成12组数据
			{
				RX_data_cun=0;
				RX_stat=0;
				for(i=1;i<=12;i++) //计算校验和
				{
					aRxBuffer_SUM+=RXdata[i];  //取地址为后面的检验和
				}
				if((((uint8_t)(aRxBuffer_SUM>>8)&0xff)==RXdata[13])&&((uint8_t)(aRxBuffer_SUM&0xFF)==RXdata[14])) //判断校验和
				{
//				   V2205DrawRefresh(RXdata);
					draw->Refresh(RXdata);
				}
				else
				{
					for(i=0;i<j;i++)
					{
						RXdata[i]=0; //清除接收的数据
					}
				}
			}
		 }		
	}	
}
extern "C" void DMA1_Channel2_IRQHandler()
{

}
extern "C" void DMA1_Channel3_IRQHandler()
{
#if (LCD_SPI_SELCETED == 1)
	SPI_LCD_DMA_Write_END();
	LCD_StartDraw = 0;
#endif
}
extern "C" void DMA1_Channel4_IRQHandler()
{

}
extern "C" void DMA1_Channel5_IRQHandler()
{
#if (LCD_SPI_SELCETED == 2)
	SPI_LCD_DMA_Write_END();
	LCD_StartDraw = 0;
#endif
}

extern "C" void PVD_IRQHandler()
{
	NVIC_SystemReset();
}


