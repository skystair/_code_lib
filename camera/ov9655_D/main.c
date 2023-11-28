#include "config.h"

unsigned short int LCDdata[240];
OV9655_IDTypeDef OV9655ID;

void LCD_set0(void){
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
}
void LCD_startData(void){
	lcd_write_byte(0x2C,LCD_CMD);
	LCD_DC_H();
}
unsigned char test;
unsigned char lineflag = 0;
unsigned char linecnt = 0;
int main(void){
	//SystemInit();
	valueinit();
	BSPinit();
	memset(&LCDdata,0x77,240*2);
	lcd_init();
	lcd_display_string( 60,60,(uint8_t* )"CPU:STM32F405RGT6          ", FONT_1206, RED );

//	if(DCMI_OV9655Config() == 0){
//		lcd_display_string( 60,80,(uint8_t* )"www.WaveShare.111          ", FONT_1206, RED );
//	}else{
//		lcd_display_string( 60,80,(uint8_t* )"www.WaveShare.222          ", FONT_1206, RED );
//	}
//	
//	DCMI_OV9655_ReadID(&OV9655ID);
//	DMA_Cmd(DMA2_Stream1, ENABLE);
//    /* Enable DCMI interface */
//    DCMI_Cmd(ENABLE); 
//    /* Start Image capture */ 
//    DCMI_CaptureCmd(ENABLE);
	
	LCD_set0();
	LCD_startData();	
	LCD_CS_L();	
	SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx,ENABLE);
////	DMA_Cmd(DMA2_Stream0, ENABLE);
	
//	for(unsigned int i=0;i<320*2;i++){
//		spi1_communication(LCDdata[i]>>8);
//		spi1_communication((uint8_t)(LCDdata[i]&0xff));
//	}
//	LCD_CS_H();

//	lineflag = 0;
//	if(lineflag == 1){
//		for(unsigned int i = 0;i<320*240;i++){
//				spi1_communication(LCDdata[i]>>8);
//				spi1_communication((uint8_t)(LCDdata[i]&0xff));
//			}
//		lineflag = 0;
//	}
	while(1){
//		LCD_set0();
//		LCD_startData();	
//		LCD_CS_L();	
		
//		LCD_CS_H();

	}
}

