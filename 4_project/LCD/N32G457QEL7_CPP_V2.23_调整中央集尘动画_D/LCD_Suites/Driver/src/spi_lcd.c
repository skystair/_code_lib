#include "spi_lcd.h"


void DMA_LCD_Init(void)
{
	DMA_InitType DMA_InitStructure;

	/*ENABLE DMA CLK*/
	RCC_EnableAHBPeriphClk(LCD_DMA_CLK, ENABLE);

	/* SPI_LCD_Tx_DMA_Channel configuration ---------------------------------------------*/
	DMA_DeInit(LCD_TX_DMA);
	DMA_InitStructure.PeriphAddr     = (uint32_t)&(LCD_SPI->DAT);
	DMA_InitStructure.MemAddr        = (uint32_t)0;
	DMA_InitStructure.Direction      = DMA_DIR_PERIPH_DST;
	DMA_InitStructure.BufSize        = 0;
	DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
	DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
	DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_HALFWORD;
	DMA_InitStructure.MemDataSize    = DMA_MemoryDataSize_HalfWord;
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

void sLCD_LowLevel_Init(void)
{
    GPIO_InitType GPIO_InitStructure;

    /*!< SPI1 Periph clock and sFLASH_SPI_GPIO Periph clock enable */
    RCC_EnableAPB2PeriphClk(LCD_GPIO_CLK, ENABLE);
		/*!< SPI2 Periph clock enable */
		LCD_SPI_CLK_ENABLE();
	
    /*!< Configure SPI2 pins: SCK */
    GPIO_InitStructure.Pin        = LCD_PIN_CLK;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitPeripheral(LCD_PORT_CLK, &GPIO_InitStructure);

    /*!< Configure SPI2 pins: MOSI */
    GPIO_InitStructure.Pin       = LCD_PIN_MOSI;
    GPIO_InitPeripheral(LCD_PORT_MOSI, &GPIO_InitStructure);

    /*!< Configure GPIOB_PIN_12 pin: sLCD Card CS pin */
    GPIO_InitStructure.Pin       = LCD_PIN_CS;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitPeripheral(LCD_PORT_CS, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
		/*!< Configure GPIOA_PIN_10 pin: sLCD Card D/C pin */
    GPIO_InitStructure.Pin       = LCD_PIN_DC;
    GPIO_InitPeripheral(LCD_PORT_DC, &GPIO_InitStructure);
		
		/*!< Configure GPIOB_PIN_0 pin: sLCD Card RST pin */
    GPIO_InitStructure.Pin       = LCD_PIN_RST;
    GPIO_InitPeripheral(LCD_PORT_RST, &GPIO_InitStructure);
}


void LCD_SPI_Init(void)
{
	sLCD_LowLevel_Init();	
	LCD_CS_SET();
	SPI_InitType SPI_InitStructure;
	
		/*!< SPI configuration */
	SPI_InitStructure.DataDirection = SPI_DIR_SINGLELINE_TX;
	SPI_InitStructure.SpiMode       = SPI_MODE_MASTER;
	SPI_InitStructure.DataLen       = SPI_DATA_SIZE_8BITS;
	SPI_InitStructure.CLKPOL        = SPI_CLKPOL_HIGH;//SPI_CLKPOL_LOW;//
	SPI_InitStructure.CLKPHA        = SPI_CLKPHA_SECOND_EDGE;//SPI_CLKPHA_FIRST_EDGE;//
	SPI_InitStructure.NSS           = SPI_NSS_HARD;

	SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_2;//SPI_BR_PRESCALER_4;//SPI_BR_PRESCALER_2;

	SPI_InitStructure.FirstBit = SPI_FB_MSB;
	SPI_InitStructure.CRCPoly  = 7;
	SPI_Init(LCD_SPI, &SPI_InitStructure);

	SPI_SSOutputEnable(LCD_SPI, ENABLE);
	SPI_EnableCalculateCrc(LCD_SPI, DISABLE);
	/*!< Enable the SPI1  */
	SPI_Enable(LCD_SPI, ENABLE);
//	SPI_SSOutputEnable(LCD_SPI, ENABLE);
//	SPI_SetNssLevel(LCD_SPI,SPI_NSS_HIGH);
	DMA_LCD_Init();
}

void LCD_SendByte(uint8_t byte)
{
	while (SPI_I2S_GetStatus(LCD_SPI, SPI_I2S_TE_FLAG) == RESET){};	
	SPI_I2S_TransmitData(LCD_SPI, byte);
	while (SPI_I2S_GetStatus(LCD_SPI, SPI_I2S_TE_FLAG) == RESET){};
	while (SPI_I2S_GetStatus(LCD_SPI, SPI_I2S_BUSY_FLAG) == SET){};
}

void LCD_SenndMoreSequence(uint8_t size, const uint8_t* buffer)
{
	while (SPI_I2S_GetStatus(LCD_SPI, SPI_I2S_TE_FLAG) == RESET){};
	for(int i=0; i<size; i++)
	{
		SPI_I2S_TransmitData(LCD_SPI,*(buffer+i));
		while (SPI_I2S_GetStatus(LCD_SPI, SPI_I2S_TE_FLAG) == RESET){};
	}
	while (SPI_I2S_GetStatus(LCD_SPI, SPI_I2S_BUSY_FLAG) == SET){};
}

void LCD_SenndMoreReversed(uint8_t size, const uint8_t* buffer)
{
		while (SPI_I2S_GetStatus(LCD_SPI, SPI_I2S_TE_FLAG) == RESET){};
	for(int i=size-1; i>=0; i--)
	{
		SPI_I2S_TransmitData(LCD_SPI, buffer[i]);
		while (SPI_I2S_GetStatus(LCD_SPI, SPI_I2S_TE_FLAG) == RESET){};
	}
	while (SPI_I2S_GetStatus(LCD_SPI, SPI_I2S_BUSY_FLAG) == SET){};
}

void LCD_SenndMoreSequenceU16(uint16_t size, const uint16_t* buffer)
{
	while (SPI_I2S_GetStatus(LCD_SPI, SPI_I2S_TE_FLAG) == RESET){};
	for(int i=0; i<size; i++)
	{
		SPI_I2S_TransmitData(LCD_SPI, (buffer[i]>>8)&0xff);
		while (SPI_I2S_GetStatus(LCD_SPI, SPI_I2S_TE_FLAG) == RESET){};
		SPI_I2S_TransmitData(LCD_SPI, buffer[i]&0xff);
		while (SPI_I2S_GetStatus(LCD_SPI, SPI_I2S_TE_FLAG) == RESET){};
	}
	while (SPI_I2S_GetStatus(LCD_SPI, SPI_I2S_BUSY_FLAG) == SET){};
}

uint8_t LCD_ReadByte(void)
{
	uint8_t result;
	SPI_Enable(LCD_SPI, DISABLE);
	SPI_ConfigBidirectionalMode(LCD_SPI, SPI_BIDIRECTION_RX);
	SPI_Enable(LCD_SPI, ENABLE);
	
	while (SPI_I2S_GetStatus(LCD_SPI, SPI_I2S_RNE_FLAG) == RESET){};
	SPI_Enable(LCD_SPI, DISABLE);
    /*!< Return the byte read from the SPI bus */
  result = (uint8_t)SPI_I2S_ReceiveData(LCD_SPI);
	
	SPI_ConfigBidirectionalMode(LCD_SPI, SPI_BIDIRECTION_TX);
	SPI_Enable(LCD_SPI, ENABLE);
	return result;
}

void LCD_ReadMore(uint8_t size, uint8_t* buffer)
{
	SPI_Enable(LCD_SPI, DISABLE);
	SPI_ConfigBidirectionalMode(LCD_SPI, SPI_BIDIRECTION_RX);
	
	SPI_Enable(LCD_SPI, ENABLE);
	for(int i=0; i<size; i++)
	{
		while (SPI_I2S_GetStatus(LCD_SPI, SPI_I2S_RNE_FLAG) == RESET){};
		*(buffer+i)	= (uint8_t)SPI_I2S_ReceiveData(LCD_SPI);
	}
	
	SPI_ConfigBidirectionalMode(LCD_SPI, SPI_BIDIRECTION_TX);
	SPI_Enable(LCD_SPI, ENABLE);
}

void SPI_LCD_DMA_Write_END()
{
#if (!DMA_DELAY)
while(!SPI_I2S_GetStatus(LCD_SPI, SPI_I2S_TE_FLAG));

DMA_EnableChannel(LCD_TX_DMA, DISABLE);
SPI_I2S_EnableDma(LCD_SPI, SPI_I2S_DMA_TX, DISABLE);

/*clear TX buff*/
LCD_SPI->DAT;

/* Deselect the FLASH: Chip Select high */
LCD_CS_SET();

DMA_ClearFlag(LCD_DMA_TX_TC,LCD_DMA);
DMA_ClrIntPendingBit(LCD_DMA_TX_TC, LCD_DMA);
SPI_ConfigDataLen(LCD_SPI, SPI_DATA_SIZE_8BITS);
#endif
}

void SPI_LCD_DMA_Write(const uint16_t* pbuffer, uint16_t num_byte_to_write)
{
	if(num_byte_to_write == 0)
	{
		return;
	}
	SPI_ConfigDataLen(LCD_SPI, SPI_DATA_SIZE_16BITS);
	
	/* DMA_Channel configuration */
	LCD_TX_DMA->TXNUM = num_byte_to_write;
	LCD_TX_DMA->MADDR = (uint32_t)pbuffer; 

	/* Select the FLASH: Chip Select low */
	LCD_CS_CLR();

	DMA_EnableChannel(LCD_TX_DMA, ENABLE);
	SPI_I2S_EnableDma(LCD_SPI, SPI_I2S_DMA_TX, ENABLE);
	
#if (DMA_DELAY)
	uint32_t time_out_count = 0;
	/* Wait for DMA channel transfer complete */
	while(!DMA_GetFlagStatus(LCD_DMA_TX_TC, LCD_DMA)||time_out_count > 600000)
		time_out_count++;
	/* Wait for SPI1 transfer complete */
	time_out_count = 0;
	while(!SPI_I2S_GetStatus(LCD_SPI, SPI_I2S_TE_FLAG)||time_out_count > 600000)
		time_out_count++;

	DMA_EnableChannel(LCD_TX_DMA, DISABLE);
	SPI_I2S_EnableDma(LCD_SPI, SPI_I2S_DMA_TX, DISABLE);

	/*clear TX buff*/
	LCD_SPI->DAT;

	/* Deselect the FLASH: Chip Select high */
	LCD_CS_SET();
	
	DMA_ClearFlag(LCD_DMA_TX_TC,LCD_DMA);

	SPI_ConfigDataLen(LCD_SPI, SPI_DATA_SIZE_8BITS);
#endif
}
