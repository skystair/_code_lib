#include "spi_lcd.h"
#include "IOconfig.h"


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
