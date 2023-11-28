/*****************************************************************************
* | File      	:		LCD_Driver.c
* | Author      :   Waveshare team
* | Function    :   LCD Driver
* | Info        :
*----------------
* |	This version:   V1.2
* | Date        :   2019-08-16
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/

#include "LCD_Driver.h"
#include "math.h"
#include <stdlib.h>
#include "../Common/fonts.c"

static sFONT *LCD_Currentfonts;

  /* Global variables to set the written text color */
static __IO uint16_t TextColor = 0x0000, BackColor = 0xFFFF;

/******************************************************************************
function :	initial SPI1
parameter:
******************************************************************************/
void spi1_init(void)
{
	
	SPI_InitTypeDef SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);
 	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);

	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin =GPIO_Pin_6| GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	SPI_I2S_DeInit(SPI1);
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(SPI1, &SPI_InitStructure); 
	
	SPI_Cmd(SPI1, ENABLE);
	
}

/******************************************************************************
function :	SPI1 send data
parameter:
send_char:	sned data
******************************************************************************/
uint8_t spi1_communication(uint8_t send_char)
{
	uint8_t chRetry = 0;
	uint8_t chTemp = 0;

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) {
		if (++ chRetry > 200) {
			return 0;
		}
	}

	SPI_I2S_SendData(SPI1, send_char);

	chRetry=0;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) {
		if (++ chRetry > 200) {
			return 0;
		}
	}

	chTemp = SPI_I2S_ReceiveData(SPI1);

	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) != RESET) {
	
	}
	
	return chTemp;
}

/******************************************************************************
function :	write eight bits' data to LCD
parameter:
  chByte : send data
  chCmd  : command or data
******************************************************************************/
void lcd_write_byte(uint8_t chByte, uint8_t chCmd)
{
    if (chCmd) {
        LCD_DC_H();
    } else {
        LCD_DC_L();
    }
    
    LCD_CS_L();
    spi1_communication(chByte);
    LCD_CS_H();
}

/******************************************************************************
function :	write sixteen bits' data to LCD
parameter:
  chByte : send data
  chCmd  : command or data
******************************************************************************/
void lcd_write_data(uint16_t hwData)
{
    LCD_DC_H();
    LCD_CS_L();
    spi1_communication(hwData >> 8);
    spi1_communication(hwData & 0xFF);
    LCD_CS_H();
}

/******************************************************************************
function :	write data to LCD register
parameter:
     chByte : send data
		 chCmd  : command or data
******************************************************************************/
void lcd_write_command(uint8_t chRegister, uint8_t chValue)
{
	lcd_write_byte(chRegister, LCD_CMD);
	lcd_write_byte(chValue, LCD_DATA);
}

/********************************************************************************
Function Name  : initials lcd control pin 
			parameter:
********************************************************************************/
void lcd_ctrl_port_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_6 | GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
}

/******************************************************************************
Function Name  : delay
			parameter: ms
******************************************************************************/
void delay_ms(uint32_t ms)
{
	uint32_t j=5000;
	for(;ms>2;ms--)
		for(;j>2;j--){
			
		}
}

/******************************************************************************
Function Name  : initials lcd control pin 
			parameter:
******************************************************************************/
void lcd_init(void)
{
  lcd_ctrl_port_init();
	LCD_RST_H();
  spi1_init();
	
	LCD_CS_H();
	LCD_BKL_H();
#ifdef 	ST7789_DEVICE
	LCD_RST_H();
	delay_ms(5);
	LCD_RST_L();
	delay_ms(5);
	LCD_RST_H();
	delay_ms(5);
	LCD_CS_H();
#endif
	
#ifdef HX8347D_DEVICE	
	lcd_write_command(0xEA,0x00);
	lcd_write_command(0xEB,0x20);
	lcd_write_command(0xEC,0x0C);
	lcd_write_command(0xED,0xC4);
	lcd_write_command(0xE8,0x38);
	lcd_write_command(0xE9,0x10);
	lcd_write_command(0xF1,0x01);
	lcd_write_command(0xF2,0x10);
	lcd_write_command(0x40,0x01); 
	lcd_write_command(0x41,0x00); 
	lcd_write_command(0x42,0x00); 
	lcd_write_command(0x43,0x10); 
	lcd_write_command(0x44,0x0E); 
	lcd_write_command(0x45,0x24); 
	lcd_write_command(0x46,0x04); 
	lcd_write_command(0x47,0x50); 
	lcd_write_command(0x48,0x02); 
	lcd_write_command(0x49,0x13); 
	lcd_write_command(0x4A,0x19); 
	lcd_write_command(0x4B,0x19); 
	lcd_write_command(0x4C,0x16); 
	lcd_write_command(0x50,0x1B); 
	lcd_write_command(0x51,0x31); 
	lcd_write_command(0x52,0x2F); 
	lcd_write_command(0x53,0x3F); 
	lcd_write_command(0x54,0x3F); 
	lcd_write_command(0x55,0x3E); 
	lcd_write_command(0x56,0x2F); 
	lcd_write_command(0x57,0x7B); 
	lcd_write_command(0x58,0x09); 
	lcd_write_command(0x59,0x06); 
	lcd_write_command(0x5A,0x06); 
	lcd_write_command(0x5B,0x0C); 
	lcd_write_command(0x5C,0x1D); 
	lcd_write_command(0x5D,0xCC); 
	lcd_write_command(0x1B,0x1B);
	lcd_write_command(0x1A,0x01);
	lcd_write_command(0x24,0x2F);
	lcd_write_command(0x25,0x57);
	lcd_write_command(0x23,0x88);
	lcd_write_command(0x18,0x34);
	lcd_write_command(0x19,0x01);
	lcd_write_command(0x01,0x00);
	lcd_write_command(0x1F,0x88);
	lcd_write_command(0x1F,0x80);
	lcd_write_command(0x1F,0x90);
	lcd_write_command(0x1F,0xD0);
	lcd_write_command(0x17,0x05); 
	lcd_write_command(0x36,0x02); 
	lcd_write_command(0x28,0x38);
	lcd_write_command(0x28,0x3F);
	lcd_write_command(0x16,0x18); 
	lcd_write_command(0x02,0x00);
	lcd_write_command(0x03,0x00);
	lcd_write_command(0x04,0x00);
	lcd_write_command(0x05,0xEF);
	lcd_write_command(0x06,0x00);
	lcd_write_command(0x07,0x00);
	lcd_write_command(0x08,0x01);
	lcd_write_command(0x09,0x3F);
#elif defined ST7789_DEVICE
	lcd_write_byte(0x11,LCD_CMD);
	delay_ms(10);
	lcd_write_command(0x36,0x00);
	lcd_write_command(0x3a,0x05);
	lcd_write_byte(0xb2,LCD_CMD);
	lcd_write_byte(0x0c,LCD_DATA);
	lcd_write_byte(0x0c,LCD_DATA);
	lcd_write_byte(0x00,LCD_DATA);
	lcd_write_byte(0x33,LCD_DATA);
	lcd_write_byte(0x33,LCD_DATA);
	lcd_write_command(0xb7,0x35);
	lcd_write_command(0xbb,0x28);
	lcd_write_command(0xc0,0x3c);
	lcd_write_command(0xc2,0x01);
	lcd_write_command(0xc3,0x0b);
	lcd_write_command(0xc4,0x20);
	lcd_write_command(0xc6,0x0f);
	lcd_write_byte(0xD0,LCD_CMD);
	lcd_write_byte(0xa4,LCD_DATA);
	lcd_write_byte(0xa1,LCD_DATA);
	lcd_write_byte(0xe0,LCD_CMD);
	lcd_write_byte(0xd0,LCD_DATA);
	lcd_write_byte(0x01,LCD_DATA);
	lcd_write_byte(0x08,LCD_DATA);
	lcd_write_byte(0x0f,LCD_DATA);
	lcd_write_byte(0x11,LCD_DATA);
	lcd_write_byte(0x2a,LCD_DATA);
	lcd_write_byte(0x36,LCD_DATA);
	lcd_write_byte(0x55,LCD_DATA);
	lcd_write_byte(0x44,LCD_DATA);
	lcd_write_byte(0x3a,LCD_DATA);
	lcd_write_byte(0x0b,LCD_DATA);
	lcd_write_byte(0x06,LCD_DATA);
	lcd_write_byte(0x11,LCD_DATA);
	lcd_write_byte(0x20,LCD_DATA);
	lcd_write_byte(0xe1,LCD_CMD);
	lcd_write_byte(0xd0,LCD_DATA);
	lcd_write_byte(0x02,LCD_DATA);
	lcd_write_byte(0x07,LCD_DATA);
	lcd_write_byte(0x0a,LCD_DATA);
	lcd_write_byte(0x0b,LCD_DATA);
	lcd_write_byte(0x18,LCD_DATA);
	lcd_write_byte(0x34,LCD_DATA);
	lcd_write_byte(0x43,LCD_DATA);
	lcd_write_byte(0x4a,LCD_DATA);
	lcd_write_byte(0x2b,LCD_DATA);
	lcd_write_byte(0x1b,LCD_DATA);
	lcd_write_byte(0x1c,LCD_DATA);
	lcd_write_byte(0x22,LCD_DATA);
	lcd_write_byte(0x1f,LCD_DATA);
	lcd_write_byte(0x29,LCD_CMD);
	lcd_write_command(0x51,0xff);
	lcd_write_command(0x55,0xB0);
#endif
	lcd_set_font(&LCD_DEFAULT_FONT);
}

/******************************************************************************
Function Name  : clear lcd screen
			parameter:
				hwColor: background color
******************************************************************************/
void lcd_clear_screen(uint16_t hwColor)
{
	uint32_t i, wCount = LCD_WIDTH;
	wCount *= LCD_HEIGHT;
	
#ifdef HX8347D_DEVICE
	lcd_set_cursor(0, 0);
	lcd_write_byte(0x22, LCD_CMD);
#elif defined ST7789_DEVICE
	lcd_write_byte(0x2A,LCD_CMD);
	lcd_write_byte(0x00,LCD_DATA);
	lcd_write_byte(0x00,LCD_DATA);
	lcd_write_byte(0x00,LCD_DATA);
	lcd_write_byte((LCD_WIDTH-1)&0xff,LCD_DATA);
	lcd_write_byte(0x2B,LCD_CMD);
	lcd_write_byte(0x00,LCD_DATA);
	lcd_write_byte(0x00,LCD_DATA);
	lcd_write_byte(((LCD_HEIGHT-1)>>8)&0xff,LCD_DATA);
	lcd_write_byte((LCD_HEIGHT-1)&0xff,LCD_DATA);
	lcd_write_byte(0x2C,LCD_CMD);
#endif
	LCD_DC_H();
	LCD_CS_L();	
	for(i=0;i<wCount;i++){
#ifdef HX8347D_DEVICE
		spi1_communication((uint8_t)(hwColor&0xff));
		spi1_communication(hwColor>>8);
#elif defined ST7789_DEVICE
		spi1_communication(hwColor>>8);
		spi1_communication((uint8_t)(hwColor&0xff));
#endif
	}
	LCD_CS_H();	
}

/******************************************************************************
Function Name  : set lcd cursor
			parameter:
				 hwXpos: x axis position
				 hwYpos: y axis position
******************************************************************************/
void lcd_set_cursor(uint16_t hwXpos, uint16_t hwYpos)
{
	if (hwXpos >= LCD_WIDTH || hwYpos >= LCD_HEIGHT) {
		return;
	}
#ifdef HX8347D_DEVICE
	lcd_write_command(0x02, hwXpos >> 8);
	lcd_write_command(0x03, hwXpos & 0xFF); 
	lcd_write_command(0x06, hwYpos >> 8);
	lcd_write_command(0x07, hwYpos & 0xFF); 
#elif defined ST7789_DEVICE
	lcd_write_byte(0x2A,LCD_CMD);
	lcd_write_byte(0x00,LCD_DATA);
	lcd_write_byte(hwXpos,LCD_DATA);
	lcd_write_byte(0x2B,LCD_CMD);
	lcd_write_byte((hwYpos>>8)&0xff,LCD_DATA);
	lcd_write_byte(hwYpos&0xff,LCD_DATA);	
#endif
}

/******************************************************************************
Function Name  : lcd display char
			parameter:
				 hwXpos: x axis position
				 hwYpos: y axis position
				  chChr: display character
				 chSize: character size
			  hwColor: character color
******************************************************************************/
void lcd_draw_char(  uint16_t hwXpos, uint16_t hwYpos, const uint16_t *c)
{      	
	uint32_t index = 0, i = 0;
	if(hwXpos >= 240 || hwYpos >= 320)
		return;
#ifdef HX8347D_DEVICE	
	lcd_set_cursor(hwXpos, hwYpos);
	lcd_write_command(0x04, (hwXpos+LCD_Currentfonts->Width-1) >> 8);
	lcd_write_command(0x05, (hwXpos+LCD_Currentfonts->Width-1) & 0xFF); 
	lcd_write_command(0x08, (hwYpos+LCD_Currentfonts->Height-1) >> 8);
	lcd_write_command(0x09, (hwYpos+LCD_Currentfonts->Height-1) & 0xFF);
	lcd_write_command(0x0A, hwYpos >> 8);
	lcd_write_command(0x0B, hwYpos & 0xFF);
	lcd_write_command(0x0C, (hwYpos+LCD_Currentfonts->Height)  >> 8);
	lcd_write_command(0x0D, (hwYpos+LCD_Currentfonts->Height)  & 0xFF); 
	lcd_write_byte(0x22, LCD_CMD);
#elif defined ST7789_DEVICE
	lcd_write_byte(0x2A,LCD_CMD);
	lcd_write_byte(0x00,LCD_DATA);
	lcd_write_byte(hwXpos,LCD_DATA);
	lcd_write_byte((hwXpos+LCD_Currentfonts->Width-1) >> 8,LCD_DATA);
	lcd_write_byte((hwXpos+LCD_Currentfonts->Width-1) & 0xFF,LCD_DATA);

	lcd_write_byte(0x2B,LCD_CMD);
	lcd_write_byte(hwYpos >> 8,LCD_DATA);
	lcd_write_byte(hwYpos & 0xFF,LCD_DATA);
	lcd_write_byte((hwYpos+LCD_Currentfonts->Height-1) >> 8,LCD_DATA);
	lcd_write_byte((hwYpos+LCD_Currentfonts->Height-1) & 0xFF,LCD_DATA);
	lcd_write_byte(0x2C, LCD_CMD);
#endif
	LCD_DC_H();
	LCD_CS_L();
	
	for(index = 0; index < LCD_Currentfonts->Height; index++){
	for(i = 0; i < LCD_Currentfonts->Width; i++)
	{
		if((((c[index] & ((0x80 << ((LCD_Currentfonts->Width / 12 ) * 8 ) ) >> i)) == 0x00) &&(LCD_Currentfonts->Width <= 12))||
			(((c[index] & (0x1 << i)) == 0x00)&&(LCD_Currentfonts->Width > 12 )))

		{
			spi1_communication(BackColor >> 8);
			spi1_communication(BackColor& 0xFF);
		}
		else
		{
			spi1_communication(TextColor >> 8);
			spi1_communication(TextColor & 0xFF);
		}
	}
}
	LCD_CS_H();
}
/******************************************************************************
Function Name  : lcd display string
			parameter:
				 hwXpos: x axis position
				 hwYpos: y axis position
		  pchString: display string
				 chSize: string size
			  hwColor: string color
******************************************************************************/
void lcd_display_string(	uint16_t hwXpos, uint16_t hwYpos, 
													const uint8_t *pchString, uint8_t chSize,    
													uint16_t hwColor) 
{

	if (hwXpos >= LCD_WIDTH || hwYpos >= LCD_HEIGHT) {
		return;
	}
	
    while (*pchString != '\0') {       
        if (hwXpos > (LCD_WIDTH - chSize / 2)) {
					hwXpos = 0;
					hwYpos += chSize;
					if (hwYpos > (LCD_HEIGHT - chSize)) {
						hwYpos = hwXpos = 0;
						lcd_clear_screen(0x00);
					}
				}
		
        lcd_dispaly_char(hwXpos, hwYpos, (uint8_t)*pchString);
        hwXpos += chSize / 2;
        pchString ++;
    } 
}

/******************************************************************************
Function Name  : lcd draw a dot
			parameter:
				 hwXpos: x axis position
				 hwYpos: y axis position
				hwColor:	dot color
******************************************************************************/
void lcd_draw_dot(uint16_t hwXpos, uint16_t hwYpos, uint16_t hwColor)
{
	if (hwXpos >= LCD_WIDTH || hwYpos >= LCD_HEIGHT) {
		return;
	}
	lcd_set_cursor(hwXpos, hwYpos);
#ifdef HX8347D_DEVICE
	lcd_write_byte(0x22, LCD_CMD);
#elif defined ST7789_DEVICE
	lcd_write_byte(0x2C, LCD_CMD);
#endif
	lcd_write_data(hwColor);

}

/******************************************************************************
Function Name  : lcd draw a big dot
			parameter:
	  color_front:	dot color
		  	 hwXpos: x axis position
				h wYpos: y axis position
******************************************************************************/
void lcd_draw_bigdot(uint32_t   color_front,
                     uint32_t    x,
                     uint32_t    y )
{
    lcd_draw_dot(color_front,x,y);
    lcd_draw_dot(color_front,x,y+1);
    lcd_draw_dot(color_front,x,y-1);

    lcd_draw_dot(color_front,x+1,y);
    lcd_draw_dot(color_front,x+1,y+1);
    lcd_draw_dot(color_front,x+1,y-1);
    
    lcd_draw_dot(color_front,x-1,y);    
    lcd_draw_dot(color_front,x-1,y+1);
    lcd_draw_dot(color_front,x-1,y-1);
    
}

/******************************************************************************
Function Name  : calculate N power
			parameter:
						 m :	valure
					   n :  exponent
******************************************************************************/
static uint32_t _pow(uint8_t m, uint8_t n)
{
	uint32_t result = 1;
	
	while(n --) result *= m;    
	return result;
}

/******************************************************************************
Function Name  : lcd display number
			parameter:
				 hwXpos: x axis position
				 hwYpos: y axis position
				  chNum: number
				  chLen: number length  
				 chSize: number size
				hwColor: number color
******************************************************************************/
void lcd_display_num(			uint16_t hwXpos, uint16_t hwYpos, 
                          uint32_t chNum,  uint8_t chLen,   
                          uint8_t chSize,  uint16_t hwColor)
{         	
	uint8_t i;
	uint8_t chTemp, chShow = 0;

	if (hwXpos >= LCD_WIDTH || hwYpos >= LCD_HEIGHT) {
		return;
	}
	
	for(i = 0; i < chLen; i ++) {
		chTemp = (chNum / _pow(10, chLen - i - 1)) % 10;
		if(chShow == 0 && i < (chLen - 1)) {
			if(chTemp == 0) {
				lcd_dispaly_char(hwXpos + (chSize / 2) * i, hwYpos, ' ');
				continue;
			} else {
				chShow = 1;
			}	 
		}
	 	lcd_dispaly_char(hwXpos + (chSize / 2) * i, hwYpos, chTemp + '0'); 
	}
} 

/******************************************************************************
Function Name  : lcd draw a line
			parameter:
				hwXpos0: x axis start position
				hwYpos0: y axis start position
				hwXpos1: x axis end position
				hwYpos1: y axis end position
				hwColor: line color
******************************************************************************/
uint8_t lcd_draw_line(		uint16_t x0,uint16_t y0, 
													uint16_t x1,uint16_t y1, 
													uint16_t color) 
{
	short dx,dy;
  short temp;

  if( x0 > x1 )
  {
    temp = x1;
    x1 = x0;
    x0 = temp;   
  }
  if( y0 > y1 )
  {
    temp = y1;
    y1 = y0;
    y0 = temp;   
  }

  dx = x1-x0;
  dy = y1-y0;

  if( dx == 0 )
  {
    do
    { 
      lcd_draw_dot(x0, y0, color);
      y0++;
    }while( y1 >= y0 ); 
    return 0; 
  }
  if( dy == 0 )
  {
    do
    {
      lcd_draw_dot(x0, y0, color);
      x0++;
    }
    while( x1 >= x0 ); 
		return 0;
  }

	/* Bresenham's line algorithm  */
  if( dx > dy )
  {
    temp = 2 * dy - dx;
    while( x0 != x1 )
    {
	    lcd_draw_dot(x0,y0,color);
	    x0++;
	    if( temp > 0 )
	    {
	      y0++;
	      temp += 2 * dy - 2 * dx; 
	 	  }
      else         
      {
			  temp += 2 * dy;
			}       
    }
    lcd_draw_dot(x0,y0,color);
  }  
  else
  {
    temp = 2 * dx - dy;
    while( y0 != y1 )
    {
	 	  lcd_draw_dot(x0,y0,color);     
      y0++;                 
      if( temp > 0 )           
      {
        x0++;               
        temp+=2*dy-2*dx; 
      }
      else
			{
        temp += 2 * dy;
			}
    } 
    lcd_draw_dot(x0,y0,color);
	}		
	return 0;
}

/******************************************************************************
Function Name  : lcd draw a circle
			parameter:
				hwXpos: x axis  position
				hwYpos: y axis  position
			 hwRadius: circle radius
				hwColor: cirlce color
******************************************************************************/
void lcd_draw_circle(		uint16_t hwXpos,uint16_t hwYpos, 
                        uint16_t hwRadius,uint16_t hwColor) 
{
	int x = -hwRadius, y = 0, err = 2 - 2 * hwRadius, e2;

	if (hwXpos >= LCD_WIDTH || hwYpos >= LCD_HEIGHT) {
		return;
	}
	
    do {
        lcd_draw_dot(hwXpos - x, hwYpos + y, hwColor);
        lcd_draw_dot(hwXpos + x, hwYpos + y, hwColor);
        lcd_draw_dot(hwXpos + x, hwYpos - y, hwColor);
        lcd_draw_dot(hwXpos - x, hwYpos - y, hwColor);
        e2 = err;
        if (e2 <= y) {
            err += ++ y * 2 + 1;
            if(-x == y && e2 <= x) e2 = 0;
        }
        if(e2 > x) err += ++ x * 2 + 1;
    } while(x <= 0);
}

/******************************************************************************
Function Name  :  fill a rectangle on lcd
			parameter:
				 hwXpos: x axis  position
				 hwYpos: y axis  position
			  hwWidth: rectangle width
			 hwHeight: rectangle height
			  hwColor: rectangle color
******************************************************************************/
void lcd_draw_full_rect( uint16_t hwXpos,uint16_t hwYpos, 
											   uint16_t hwWidth,uint16_t hwHeight)
{
	uint32_t  i = 0,j=0;
	if (hwXpos >= LCD_WIDTH || hwYpos >= LCD_HEIGHT) {
		return;
	}	
	lcd_set_cursor(hwXpos, hwYpos);
	lcd_write_command(0x04, (hwXpos+LCD_Currentfonts->Width-1) >> 8);
	lcd_write_command(0x05, (hwXpos+LCD_Currentfonts->Width-1) & 0xFF);
	lcd_write_command(0x08, (hwYpos+LCD_Currentfonts->Height-1) >> 8);
	lcd_write_command(0x09, (hwYpos+LCD_Currentfonts->Height-1) & 0xFF);
	
	lcd_write_command(0x0A, hwYpos >> 8);
	lcd_write_command(0x0B, hwYpos & 0xFF);
	lcd_write_command(0x0C, (hwYpos+LCD_Currentfonts->Height)  >> 8);
	lcd_write_command(0x0D, (hwYpos+LCD_Currentfonts->Height)  & 0xFF);
	
	lcd_write_byte(0x22, LCD_CMD);

	LCD_DC_H();
	LCD_CS_L();
	
	for( i = 0; i < hwHeight; i++ )
	{
		for( j = 0; j < hwWidth; j++ )
		{
			lcd_write_data(TextColor);// 0x0000

		}
	}
	LCD_CS_H();
	
}

/******************************************************************************
Function Name  : draw a vertical line at the specified position on lcd
			parameter:
				 hwXpos: x axis  position
				 hwYpos: y axis  position
			 hwHeight: line height
			  hwColor: vertical linc color
******************************************************************************/
void lcd_draw_v_line(		uint16_t hwXpos,uint16_t hwYpos, 
                        uint16_t hwHeight,uint16_t hwColor)  
{	
	uint16_t i, y1 = MIN(hwYpos + hwHeight, LCD_HEIGHT - 1);

	if (hwXpos >= LCD_WIDTH || hwYpos >= LCD_HEIGHT) {
		return;
	}
	
    for (i = hwYpos; i < y1; i ++) {
        lcd_draw_dot(hwXpos, i, hwColor);
    }
}

/******************************************************************************
Function Name  : draw a horizonal line at the specified position on lcd
			parameter:
				 hwXpos: x axis  position
				 hwYpos: y axis  position
			  hwWidth: line width
			  hwColor: horizonal linc color
******************************************************************************/
void lcd_draw_h_line(		uint16_t hwXpos,uint16_t hwYpos,  
                        uint16_t hwWidth,uint16_t hwColor)
{	
	uint16_t i, x1 = MIN(hwXpos + hwWidth, LCD_WIDTH - 1);

	if (hwXpos >= LCD_WIDTH || hwYpos >= LCD_HEIGHT) {
		return;
	}
	
    for (i = hwXpos; i < x1; i ++) {
        lcd_draw_dot(i, hwYpos, hwColor);
    }
}

/******************************************************************************
Function Name  : draw a rectangle on lcd
			parameter:
				 hwXpos: x axis  position
				 hwYpos: y axis  position
			  hwWidth: rectangle width
			 hwHeight: rectangle height
			  hwColor: rectangle color
******************************************************************************/
void lcd_draw_rect(		uint16_t hwXpos,uint16_t hwYpos,  
                      uint16_t hwWidth,uint16_t hwHeight)
{
	if (hwXpos >= LCD_WIDTH || hwYpos >= LCD_HEIGHT) {
		return;
	}
	lcd_draw_h_line(hwXpos, hwYpos, hwWidth, TextColor);
	lcd_draw_h_line(hwXpos, hwYpos + hwHeight, hwWidth, TextColor);
	lcd_draw_v_line(hwXpos, hwYpos, hwHeight, TextColor);
	lcd_draw_v_line(hwXpos + hwWidth, hwYpos, hwHeight + 1, TextColor);	
	
	
}

void lcd_clear_Rect(	uint32_t color_front,uint32_t x0, 
											uint32_t y0,uint32_t x1, 
											uint32_t y1)
{
		
	uint16_t i, j;

	if (x1 >= LCD_WIDTH || y1 >= LCD_HEIGHT) {
		return;
	}
	
	for(i = 0; i < y1-y0+1; i ++){
		for(j = 0; j < x1-x0+1; j ++){
			lcd_draw_dot(x0 + j, y0 + i, color_front);
		}
	}
}

void lcd_dispaly_char(uint16_t Line, uint16_t Column, uint8_t Ascii)
{
  Ascii -= 32;
  lcd_draw_char(Line, Column, &LCD_Currentfonts->table[Ascii * LCD_Currentfonts->Height]);
}

void lcd_display_string_line(uint16_t Line, uint8_t *ptr)
{
   uint16_t refcolumn =0;
  /* Send the string character by character on lCD */
  while ((*ptr != 0) )//& (((refcolumn + 1) & 0xFFFF) >= LCD_Currentfonts->Width)
  {
    /* Display one character on LCD */
    lcd_dispaly_char(refcolumn, Line, *ptr);
    /* Decrement the column position by 16 */
    refcolumn += LCD_Currentfonts->Width;	
    /* Point on the next character */
    ptr++;
  }
}

void lcd_clear_line(uint16_t Line)
{
  uint16_t refcolumn =0;
  /* Send the string character by character on lCD */
  while (refcolumn<=240)
  {
    /* Display one character on LCD */
    lcd_dispaly_char(refcolumn, Line, ' ');
    /* Decrement the column position by 16 */
    refcolumn += LCD_Currentfonts->Width;
  }
}

sFONT *lcd_get_font(void)
{
  return LCD_Currentfonts;
}

void lcd_set_font(sFONT *fonts)
{
  LCD_Currentfonts = fonts;
}


void lcd_set_back_color(__IO uint16_t Color)
{
  BackColor = Color;
}

void lcd_set_text_color(__IO uint16_t Color)
{
  TextColor = Color;
}

void lcd_display_image( const uint8_t *img, 
												uint8_t x,uint32_t y, 
												uint32_t width,
												uint32_t height )
{
	uint32_t i, j;
	uint32_t data16;

	if(x >= 240 || y >= 320){
		return;
	}

	lcd_set_cursor(x, y);													
	lcd_write_command(0x04, (x+width-1) >> 8);
	lcd_write_command(0x05, (x+width-1) & 0xFF);
	
	lcd_write_command(0x08, (y+height-1) >> 8);
	lcd_write_command(0x09, (y+height-1) & 0xFF);
	
	lcd_write_command(0x0A, y >> 8);
	lcd_write_command(0x0B, y & 0xFF);
	
	lcd_write_command(0x0C, (y+height)  >> 8);
	lcd_write_command(0x0D, (y+height)  & 0xFF);
	
	lcd_write_byte(0x22, LCD_CMD);

	LCD_DC_H();
	LCD_CS_L();
	for( i = 0; i < height; i++ )
	{
		for( j = 0; j < width; j++ )
		{
			//Be carful of MCU type, big endian or little endian
			//little endian
			data16 = ( *(img + 1) << 8 ) | (*img);
			spi1_communication( data16 >> 8 );
			spi1_communication( data16&0xff );
			img += 2;
		}
	}
	LCD_CS_H();
}

void lcd_write_ram_prepare(void)
{
	lcd_write_byte(0x22, LCD_CMD);	
}

/*-------------------------------END OF FILE-------------------------------*/
