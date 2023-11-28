#include "config.h"


void lcd_write_index(uint8_t index);
void lcd_write_data(uint8_t data);
void lcd_write_data_16bit(uint8_t datah,uint8_t datal);
void lcd_write_index_with_data(uint8_t index, uint8_t size, const uint8_t* buffer);

void lcd_set_xy(uint16_t x,uint16_t y);


void lcd_write_index(uint8_t index)
{
	LCD_DC_CLR();
	LCD_CS_SET(); 
	LCD_CS_CLR();
	LCD_SendByte(index);
	LCD_CS_SET();
}
void lcd_write_data(uint8_t data)
{
	LCD_DC_SET();  
	LCD_CS_CLR(); //∆¨—°
	LCD_SendByte(data);
	LCD_CS_SET();  //…Ë÷√∏ﬂ
}

void lcd_write_data_16bit(uint8_t datah,uint8_t datal)
{
	LCD_DC_SET();
	LCD_CS_SET(); 
	LCD_CS_CLR();
    LCD_SendByte(datah);
    LCD_SendByte(datal);
	LCD_CS_SET();
}


void lcd_write_index_with_data(uint8_t index, uint8_t size, const uint8_t* buffer)
{
	LCD_DC_CLR();
	LCD_CS_SET(); 
	LCD_CS_CLR();
	LCD_SendByte(index);
	LCD_DC_SET();
	LCD_SenndMoreSequence(size, buffer);
	LCD_CS_SET();
}

