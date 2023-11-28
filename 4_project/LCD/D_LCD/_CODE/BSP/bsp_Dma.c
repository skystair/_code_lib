#include "config.h"

volatile uint8_t MEM_StartDraw = 0;

MemIrqCallback MemDmaCallback = ((MemIrqCallback)0);


//MEM_DMA_CH  DMA2_CH1

//#define FLASH_DMA			DMA1
//#define FLASH_TX_DMA		DMA1_CH5
//#define FLASH_RX_DMA		DMA1_CH4

//#define LCD_DMA			DMA1
//#define LCD_TX_DMA		DMA1_CH3
//#define LCD_RX_DMA		DMA1_CH2



void dmaXinit(void);

void DMA_Flash_Init(void);
void DMA_LCD_Init(void);
void BspMemDmaInit(void);

void bspMemDmaStart(uint32_t source, uint32_t target, uint32_t halfWordSize);
void BspSetMemDmaIrqCallBack(MemIrqCallback callback);



void dmaXinit(void){
	DMA_LCD_Init();
//	DMA_Flash_Init();
	
	BspMemDmaInit();
}

//-----------------------------------------------------------
void DMA_Flash_Init(void)
{
	DMA_InitType DMA_InitStructurex;
	
	DMA_DeInit(FLASH_RX_DMA);
	DMA_DeInit(FLASH_TX_DMA);
    /* SPI_FLASH_Rx_DMA_Channel configuration ---------------------------------------------*/
    
    DMA_InitStructurex.PeriphAddr     = (uint32_t)&(FLASH_SPI->DAT);
    DMA_InitStructurex.MemAddr        = (uint32_t)u8LCDbuff;
    DMA_InitStructurex.BufSize        = 0xe100;
    DMA_InitStructurex.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructurex.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructurex.PeriphDataSize = DMA_PERIPH_DATA_SIZE_BYTE;
    DMA_InitStructurex.MemDataSize    = DMA_MemoryDataSize_Byte;
    DMA_InitStructurex.CircularMode   = DMA_MODE_NORMAL;
    DMA_InitStructurex.Mem2Mem        = DMA_M2M_DISABLE;
	
	DMA_InitStructurex.Direction      = DMA_DIR_PERIPH_SRC;
	DMA_InitStructurex.Priority       = DMA_PRIORITY_VERY_HIGH;
	
    DMA_Init(FLASH_RX_DMA, &DMA_InitStructurex);

    /* SPI_FLASH_Tx_DMA_Channel configuration ---------------------------------------------*/
	
	DMA_InitStructurex.Priority   		 = DMA_PRIORITY_HIGH;
	DMA_InitStructurex.Direction  		 = DMA_DIR_PERIPH_DST;
    DMA_Init(FLASH_TX_DMA, &DMA_InitStructurex);   

    DMA_EnableChannel(FLASH_RX_DMA, DISABLE);
    DMA_EnableChannel(FLASH_TX_DMA, DISABLE);
}

//-----------------------------------------------------------
void DMA_LCD_Init(void)
{
	DMA_InitType DMA_InitStructure;
	/* SPI_LCD_Tx_DMA_Channel configuration ---------------------------------------------*/
	DMA_DeInit(LCD_TX_DMA);
	DMA_InitStructure.PeriphAddr     = (uint32_t)&(LCD_SPI->DAT);
	DMA_InitStructure.MemAddr        = (uint32_t)u8LCDbuff;
	DMA_InitStructure.Direction      = DMA_DIR_PERIPH_DST;
	DMA_InitStructure.BufSize        = 0xe100;
	DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
	DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
	DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_BYTE;
	DMA_InitStructure.MemDataSize    = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.CircularMode   = DMA_MODE_NORMAL;
	DMA_InitStructure.Priority       = DMA_PRIORITY_VERY_HIGH;
	DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;
	DMA_Init(LCD_TX_DMA, &DMA_InitStructure);
	
#if (!DMA_DELAY)
	DMA_ConfigInt(LCD_TX_DMA, DMA_INT_TXC, ENABLE);

	NVIC_InitType NVIC_InitStructure;
	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel                   = LCD_DMA_TX_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif
}


//-----------------------------------------------------------
void BspMemDmaInit(void)
{
	DMA_InitType DMA_InitStructure;
	
	DMA_DeInit(MEM_DMA_CH);
	
	DMA_InitStructure.PeriphAddr     = ((uint32_t)0);//Ä¿±ê
	DMA_InitStructure.MemAddr        = ((uint32_t)0);//Ô´
	DMA_InitStructure.Direction      = DMA_DIR_PERIPH_DST;
	DMA_InitStructure.BufSize        = ((uint32_t)0);
	DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_ENABLE;
	DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
	DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_HALFWORD;
	DMA_InitStructure.MemDataSize    = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.CircularMode   = DMA_MODE_NORMAL;
	DMA_InitStructure.Priority       = DMA_PRIORITY_VERY_HIGH;
	DMA_InitStructure.Mem2Mem        = DMA_M2M_ENABLE;
	DMA_Init(MEM_DMA_CH, &DMA_InitStructure);
	
	DMA_ConfigInt(MEM_DMA_CH, MEM_DMA_TC, ENABLE);

	NVIC_InitType NVIC_InitStructure;
	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel                   = MEM_DMA_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	MEM_StartDraw = 0;
}



//-----------------------------------------------------------
//-----------------------------------------------------------
void bspMemDmaStart(uint32_t source, uint32_t target, uint32_t halfWordSize)
{
	uint32_t time_out_count = 0;
	while(MEM_StartDraw||time_out_count > 60000)
		time_out_count++;
	MEM_StartDraw = 1;
	
	MEM_DMA_CH->MADDR = source; 
	MEM_DMA_CH->PADDR = target;
	MEM_DMA_CH->TXNUM = halfWordSize;
	DMA_EnableChannel(MEM_DMA_CH, ENABLE);
}

void BspSetMemDmaIrqCallBack(MemIrqCallback callback)
{
	MemDmaCallback = callback;
}



//-----------------------------------------------------------
void DMA2_Channel1_IRQHandler()
{
	DMA_EnableChannel(MEM_DMA_CH, DISABLE);
	
	DMA_ClearFlag(MEM_DMA_TC, MEM_DMA);
	DMA_ClrIntPendingBit(MEM_DMA_TC, MEM_DMA);
	
	MEM_StartDraw = 0;
	if(MemDmaCallback)
	{
		MemDmaCallback();
	}
}

void DMA1_Channel2_IRQHandler()
{

}
void DMA1_Channel3_IRQHandler()
{
	DMA_ClearFlag(LCD_DMA_TX_TC,LCD_DMA);
	
	DMA_EnableChannel(LCD_TX_DMA, DISABLE);
	SPI_I2S_EnableDma(LCD_SPI, SPI_I2S_DMA_TX, DISABLE);
	
	LCD_TX_DMA->TXNUM = 0xe100;
	
	u8doubleflag++;
	LCD_TX_DMA->MADDR = (uint32_t)u8LCDbuff + 0xe100;
	
	if(u8doubleflag ==2){
		u8LCDstate = 1;
		u8doubleflag = 0;
		LCD_CS_SET();
		LCD_TX_DMA->MADDR = (uint32_t)u8LCDbuff;
	}
	u8LCDsendingflag = 0;
	DMA_ClrIntPendingBit(LCD_DMA_TX_TC, LCD_DMA);
#if (LCD_SPI_SELCETED == 1)
//	SPI_LCD_DMA_Write_END();
//	LCD_StartDraw = 0;
#endif
}
void DMA1_Channel4_IRQHandler()
{

}
void DMA1_Channel5_IRQHandler()
{
#if (LCD_SPI_SELCETED == 2)
	SPI_LCD_DMA_Write_END();
	LCD_StartDraw = 0;
#endif
}
