#include "config.h"


void spixinit(void);


void spixinit(void){
	SPI_InitType SPI_InitStructure;
	//spi1----------------------------------------------------
		/*!< SPI configuration */
	SPI_InitStructure.DataDirection = SPI_DIR_SINGLELINE_TX;
	SPI_InitStructure.SpiMode       = SPI_MODE_MASTER;
	SPI_InitStructure.DataLen       = SPI_DATA_SIZE_8BITS;
	SPI_InitStructure.CLKPOL        = SPI_CLKPOL_HIGH;
	SPI_InitStructure.CLKPHA        = SPI_CLKPHA_SECOND_EDGE;
	SPI_InitStructure.NSS           = SPI_NSS_SOFT;
	SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_2;//SPI_BR_PRESCALER_4;//SPI_BR_PRESCALER_2;
	SPI_InitStructure.FirstBit = SPI_FB_MSB;
	SPI_InitStructure.CRCPoly  = 7;
	SPI_Init(LCD_SPI, &SPI_InitStructure);

//	SPI_SSOutputEnable(LCD_SPI, ENABLE);
	SPI_EnableCalculateCrc(LCD_SPI, DISABLE);
	/*!< Enable the SPI1  */
	SPI_Enable(LCD_SPI, ENABLE);
	
	//spi2------------------------------------------------------
	/*!< SPI configuration */
    SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
//    SPI_InitStructure.SpiMode       = SPI_MODE_MASTER;
//    SPI_InitStructure.DataLen       = SPI_DATA_SIZE_8BITS;
//    SPI_InitStructure.CLKPOL        = SPI_CLKPOL_HIGH;
//    SPI_InitStructure.CLKPHA        = SPI_CLKPHA_SECOND_EDGE;
//    SPI_InitStructure.NSS           = SPI_NSS_SOFT;
//    SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_2;
//    SPI_InitStructure.FirstBit = SPI_FB_MSB;
//    SPI_InitStructure.CRCPoly  = 7;
    SPI_Init(FLASH_SPI, &SPI_InitStructure);
	
    /*!< Enable the FLASH_SPI  */
    SPI_Enable(FLASH_SPI, ENABLE);
	SPI_ConfigDataLen(LCD_SPI, SPI_DATA_SIZE_8BITS);
	SPI_I2S_EnableDma(FLASH_SPI, SPI_I2S_DMA_TX, DISABLE);
	SPI_I2S_EnableDma(FLASH_SPI, SPI_I2S_DMA_RX, DISABLE);
	
}