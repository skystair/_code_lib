#ifndef __SPI_LCD_H__
#define __SPI_LCD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g45x.h"
	
#define LCD_SPI_SELCETED 1
#if (LCD_SPI_SELCETED == 1)
#define LCD_SPI								SPI1

#define LCD_PORT_CS						GPIOA
#define LCD_PIN_CS						GPIO_PIN_4
#define LCD_PORT_MOSI					GPIOA
#define LCD_PIN_MOSI					GPIO_PIN_7
#define LCD_PORT_MISO					GPIOA
#define LCD_PIN_MISO					GPIO_PIN_6
#define LCD_PORT_CLK					GPIOA
#define LCD_PIN_CLK						GPIO_PIN_5
#define LCD_PORT_DC						GPIOA
#define LCD_PIN_DC						GPIO_PIN_3
#define LCD_PORT_RST					GPIOB
#define LCD_PIN_RST						GPIO_PIN_0

#define LCD_DMA								DMA1
#define LCD_TX_DMA						DMA1_CH3
#define LCD_RX_DMA						DMA1_CH2
#define LCD_DMA_TX_TC					DMA1_FLAG_TC3
#define LCD_DMA_RX_TC 				DMA1_FLAG_TC2
#define LCD_DMA_TX_IRQ				DMA1_Channel3_IRQn
#define LCD_DMA_RX_IRQ				DMA1_Channel2_IRQn

#define LCD_DMA_CLK						RCC_AHB_PERIPH_DMA1
#define LCD_GPIO_CLK					RCC_APB2_PERIPH_GPIOA|RCC_APB2_PERIPH_AFIO
#define LCD_SPI_CLK_ENABLE()	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_SPI1, ENABLE)

#elif (LCD_SPI_SELCETED == 2)
#define LCD_SPI								SPI2

#define LCD_PORT_CS						GPIOB
#define LCD_PIN_CS						GPIO_PIN_12
#define LCD_PORT_MOSI					GPIOB
#define LCD_PIN_MOSI					GPIO_PIN_15
#define LCD_PORT_MISO					GPIOB
#define LCD_PIN_MISO					GPIO_PIN_14
#define LCD_PORT_CLK					GPIOB
#define LCD_PIN_CLK						GPIO_PIN_13
#define LCD_PORT_DC						GPIOA
#define LCD_PIN_DC						GPIO_PIN_10
#define LCD_PORT_RST					GPIOB
#define LCD_PIN_RST						GPIO_PIN_0


#define LCD_DMA								DMA1
#define LCD_TX_DMA						DMA1_CH5
#define LCD_RX_DMA						DMA1_CH4
#define LCD_DMA_TX_TC					DMA1_FLAG_TC5//DMA1_INT_TXC5
#define LCD_DMA_RX_TC 				DMA1_FLAG_TC4
#define LCD_DMA_TX_TXC				DMA1_INT_TXC5
#define LCD_DMA_RX_TXC 				DMA1_INT_TXC4
#define LCD_DMA_TX_IRQ				DMA1_Channel5_IRQn
#define LCD_DMA_RX_IRQ				DMA1_Channel4_IRQn

#define LCD_DMA_CLK						RCC_AHB_PERIPH_DMA1
#define LCD_GPIO_CLK					RCC_APB2_PERIPH_GPIOB|RCC_APB2_PERIPH_GPIOA|RCC_APB2_PERIPH_AFIO
#define LCD_SPI_CLK_ENABLE()	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_SPI2, ENABLE)

#endif
	
//#define SPI_MASTER_DR_Base 0x4001300C
	
#define DMA_DELAY		0
	
void sLCD_LowLevel_DeInit(void);
void DMA_LCD_Init(void);
void sLCD_LowLevel_Init(void);
	
	

#define LCD_CS_CLR()	GPIO_ResetBits(LCD_PORT_CS, LCD_PIN_CS)
#define LCD_CS_SET()	GPIO_SetBits(LCD_PORT_CS, LCD_PIN_CS)

#define LCD_DC_CLR() GPIO_ResetBits(LCD_PORT_DC, LCD_PIN_DC)
#define LCD_DC_SET() GPIO_SetBits(LCD_PORT_DC, LCD_PIN_DC)

#define LCD_RST_CLR() GPIO_ResetBits(LCD_PORT_RST, LCD_PIN_RST)
#define LCD_RST_SET() GPIO_SetBits(LCD_PORT_RST, LCD_PIN_RST)


void LCD_SPI_Init(void);
void LCD_SendByte(uint8_t byte);
void LCD_SenndMoreSequence(uint8_t size, const uint8_t* buffer);
void LCD_SenndMoreReversed(uint8_t size, const uint8_t* buffer);
void LCD_SenndMoreSequenceU16(uint16_t size, const uint16_t* buffer);
void SPI_LCD_DMA_Write(const uint16_t* pbuffer, uint16_t num_byte_to_write);
uint8_t LCD_ReadByte(void);
void LCD_ReadMore(uint8_t size, uint8_t* buffer);


void SPI_LCD_DMA_Write_END(void);
	
#ifdef __cplusplus
}
#endif

#endif

