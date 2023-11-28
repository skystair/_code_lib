#include "config.h"


void bspinit(void);

void CLKinit(void);



void bspinit(void){
//systeminit??PrefetchBuf_EN,iCache_EN
//	FLASH_PrefetchBufSet(FLASH_PrefetchBuf_EN);
//	FLASH_iCacheCmd(FLASH_iCache_EN);
	
	CLKinit();
	gpioinit();
	spixinit();	
	dmaXinit();
	Bsp_Usart_Init();		//USART3 PB10(t) 11(r)  RXint
	timerXinit();
	BspPvdInit();			//PWR_PVDRANGRE_2V2
}


void CLKinit(void){
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);	
	
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_SPI1, ENABLE);
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_SPI2, ENABLE);
//	
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USART3, ENABLE);
//	
	RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA1, ENABLE);
	RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA2, ENABLE);
	
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1 ,ENABLE);
	RCC_ConfigTim18Clk(RCC_TIM18CLK_SRC_SYSCLK);
	
	/* PCLK1 = HCLK/4   128/4=32MHz */
    RCC_ConfigPclk1(RCC_HCLK_DIV4);
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2, ENABLE);
}

