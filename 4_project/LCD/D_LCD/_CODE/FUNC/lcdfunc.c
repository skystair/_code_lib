#include "config.h"

unsigned char u8testflag = 0;

unsigned char u8LCDdelay;
unsigned char u8LCDsendingflag;
unsigned char u8LCDstate;
unsigned char u8LCDresettick;
unsigned char u8LCDbuff[240*240*2];//115200
unsigned char u8doubleflag;
unsigned char u8LCDpicnum;
unsigned char u8LCDpicnumnext;

unsigned char u8LCDchangeBGflag;
unsigned int u8LCDdipsize;

unsigned short int u16tmpRdata[4];
unsigned short int u16tmpGdata[4];
unsigned short int u16tmpBdata[4];
unsigned short int u16tmpdata[4];

void LCDvalueinit(void);
void funcLCD(void);
void LCDinit(void);
void LCDreset(void);
void lcd_set_zahyo(unsigned short int x1,unsigned short int x2,unsigned short int y1,unsigned short int y2);
void LCD_fresh(void);

void LCDvalueinit(void){
	u8LCDdelay = 0;
	u8LCDsendingflag = 0;
	u8LCDstate = 0;
	u8LCDresettick = 0;
	memset(u8LCDbuff,0x00,240*240*2);
	u8doubleflag = 0;
	u8LCDpicnum = 0;
	u8LCDpicnumnext = 0;
	u8LCDdipsize = 0;
	u8LCDchangeBGflag = 0;
}
void LCD_fresh(void){
	if(u8LCDchangeBGflag ==1){
		u8LCDchangeBGflag = 0;
		
	}
		if(u8LCDpicnumnext != u8LCDpicnum){
			if((u8Flashstep == 0)&&(u8LCDsendingflag == 0)){
				u8Flashstep = 3;
				
				u8LCDpicnum = u8LCDpicnumnext;
			}
		}
}
void funcLCD(void){
	LCD_fresh();
	
	switch(u8LCDstate){
		case 0://reset
			if(u8LCDresettick < 1){
				LCD_RST_SET();
			}else if(u8LCDresettick < 3){
				LCD_RST_CLR();
			}else if(u8LCDresettick <124){
				LCD_RST_SET();
			}else{
				u8LCDstate = 4;
			}
		break;
		case 1://on
			SET_PWM_DUTY_RATIO(1);
			u8LCDstate = 3;
			break;
		case 2://off
			SET_PWM_DUTY_RATIO(0);
			u8LCDstate = 3;
			break;
		case 3://idle;
			//--------------------------
			u8LCDresettick = 0;
			//u8LCDstate = 6;
//			if(u8LCDdelay >= 254){
//				u8LCDstate = 5;
//				tmpcolor++;
//			}
			if(u8flashcomp == 1){
				u8flashcomp = 0;
				u8LCDstate = 5;
			}else{
				if(u8testflag == 0){
					u8testflag = 1;
					u8LCDstate = 6;
				}
			}
		break;
		case 4://init
			LCDinit();
			u8LCDstate = 5;
		break;
		case 5://draw black
			if(u8LCDsendingflag == 0){
				u8LCDsendingflag = 1;
				if(u8doubleflag ==0){
					//memset(u8LCDbuff,tmpcolor,240*240*2);
					//zahyo
					lcd_set_zahyo(80,320,0,240);
					//data
					lcd_write_index(0x2C);//Memory Write
					LCD_DC_SET();  
					LCD_CS_CLR();
					
				}
//				for(unsigned int i = 0; i < 240 * 240*2; i++){
//					
//					LCD_SendByte(0);
//				}
//				LCD_CS_CLR();
	
				DMA_EnableChannel(LCD_TX_DMA, ENABLE);
				SPI_I2S_EnableDma(LCD_SPI, SPI_I2S_DMA_TX, ENABLE);
				
	//			LCD_CS_SET();
			}

			break;
		case 6://draw image
			//zahyo
//			lcd_set_zahyo(80,320,0,240);
			//data
//			lcd_write_index(0x2C);//Memory Write
			for(unsigned char j = 0; j < (240); j = j+2){
				for(unsigned short int i = 0; i < (240 *2 -2); i = i + 4){
					u16tmpdata[0] = (gImage_3[j*240+i+1] << 8) | gImage_3[j*240+i];
					u16tmpdata[1] = (gImage_3[j*240+i+3] << 8) | gImage_3[j*240+i+2];
					u16tmpdata[2] = (gImage_3[(j+2)*240+i+1] << 8) | gImage_3[(j+2)*240+i];
					u16tmpdata[3] = (gImage_3[(j+2)*240+i+3] << 8) | gImage_3[(j+2)*240+i+2];
					
					for(unsigned char k = 0; k < 4;k++){
						u16tmpBdata[k] = (u16tmpdata[k] & 0x001f);
						u16tmpGdata[k] = ((u16tmpdata[k] >> 5) & 0x003f);
						u16tmpRdata[k] = (u16tmpdata[k] >> 11);
					}
					
					u16tmpBdata[0] = (u16tmpBdata[0]+u16tmpBdata[1]+u16tmpBdata[2]+u16tmpBdata[3])/4;
					u16tmpGdata[0] = (u16tmpGdata[0]+u16tmpGdata[1]+u16tmpGdata[2]+u16tmpGdata[3])/4;
					u16tmpRdata[0] = (u16tmpRdata[0]+u16tmpRdata[1]+u16tmpRdata[2]+u16tmpRdata[3])/4;
					
					u16tmpdata[0] = u16tmpBdata[0] | (u16tmpGdata[0]<<5) | (u16tmpRdata[0]<<11);
					
					if(u16tmpdata[0] != 0){
						lcd_set_zahyo(80 +i/2,82 +i/2,0+j,j+2);
						lcd_write_index(0x2C);//Memory Write
						
						lcd_write_data((unsigned char)u16tmpdata[0]);
						lcd_write_data((unsigned char)(u16tmpdata[0]>>8));
						
						lcd_write_data((unsigned char)u16tmpdata[0]);
						lcd_write_data((unsigned char)(u16tmpdata[0]>>8));
						
						lcd_write_data((unsigned char)u16tmpdata[0]);
						lcd_write_data((unsigned char)(u16tmpdata[0]>>8));
						
						lcd_write_data((unsigned char)u16tmpdata[0]);
						lcd_write_data((unsigned char)(u16tmpdata[0]>>8));
					}else{
						
					}
				}
			}
			u8LCDstate = 1;
			u8LCDdelay = 0;
			break;
		case 7://draw image
			break;
	}
}

void LCDreset(void){
	u8LCDresettick = 0;
	u8LCDstate = 0;
}

void LCDinit(void){
	lcd_write_index(0x11);	//sleep out
	lcd_write_index(0x36);  //Memory data access control:MY MX MV ML RGB MH
	//order
	//7.MY-Page Address Bottom to Top;;6.MX-Column Address Left to Right;;5,MV-EN 7~6;;	4.ML-line Top to Bottom
	//3.RGB;;	2.MH-data  Left to Right;;	1.x;;0.x;;
	lcd_write_data(0xA0); 	
	
	lcd_write_index(0x3A);  //Interface pixel format 
	lcd_write_data(0x55);	//65K 16bit(565)
	//-------------------------------- Frame rate setting----------------------------------//
	const uint8_t Data_0xB2[]	= {0x0c,0x0c,0x00,0x33,0x33};
	lcd_write_index_with_data(0xb2, 5, Data_0xB2);//Porch Setting

	lcd_write_index(0xb7);//gate control
	lcd_write_data(0x75);

	//--------------------------------- Power setting--------------------------------------//
//DEFAULT
	lcd_write_index(0xc3);   //GVDD	VRH Set
	lcd_write_data(0x16);//亮度调节 0x00-0x19之间

	lcd_write_index(0xd6);		//??
	lcd_write_data(0xa1);

	lcd_write_index(0xbb);		//VCOM Setting
	lcd_write_data(0x3b);

	//--------------------------------
	const uint8_t Data_0xe0[]	= {0xf0,0x0b,0x11,0x0e,0x0d,0x19,0x36,0x33,0x4b,0x07,0x14,0x14,0x2c,0x2e};
	lcd_write_index_with_data(0xe0, 14, Data_0xe0);//Positive Voltage Gamma Control

	const uint8_t Data_0xe1[]	= {0xf0,0x0d,0x12,0x0b,0x09,0x03,0x32,0x44,0x48,0x39,0x16,0x16,0x2d,0x30};
	lcd_write_index_with_data(0xe1, 14, Data_0xe1);//Negative Voltage Gamma Control
	
//	const uint8_t Data_0x2a[] = {0x00,0x50,0x01,0x40};
//	lcd_write_index_with_data(0x2a, 4, Data_0x2a);//Column Address Set.

//	const uint8_t Data_0x2b[] = {0x00,0x00,0x00,0xF0};
//	lcd_write_index_with_data(0x2b, 4, Data_0x2b);// Row Address Set

	lcd_write_index(0x21);//Display Inversion On
	lcd_write_index(0x29);//Display On
}

void lcd_set_zahyo(unsigned short int x1,unsigned short int x2,unsigned short int y1,unsigned short int y2){
	lcd_write_index(0x2a);
	lcd_write_data(x1/256);
	lcd_write_data(x1%256);
	lcd_write_data(x2/256);
	lcd_write_data(x2%256);
	
	lcd_write_index(0x2b);
	lcd_write_data(y1/256);
	lcd_write_data(y1%256);
	lcd_write_data(y2/256);
	lcd_write_data(y2%256);
}