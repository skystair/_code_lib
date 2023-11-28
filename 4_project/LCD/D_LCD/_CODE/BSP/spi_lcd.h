#ifndef __SPI_LCD_H__
#define __SPI_LCD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g45x.h"

	
//#define SPI_MASTER_DR_Base 0x4001300C
	

	
void sLCD_LowLevel_DeInit(void);
void sLCD_LowLevel_Init(void);

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

