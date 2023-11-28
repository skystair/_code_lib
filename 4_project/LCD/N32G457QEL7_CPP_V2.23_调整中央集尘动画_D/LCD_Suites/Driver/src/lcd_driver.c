#include "lcd_driver.h"
#include "spi_lcd.h"
#include "delay.h"
#include "bsp_pwm.h"


volatile uint8_t LCD_StartDraw = 0;

void lcd_write_index(uint8_t index)
{
	LCD_DC_CLR();
	LCD_CS_CLR();
	LCD_SendByte(index);
	LCD_CS_SET();
}

void lcd_write_index_with_data(uint8_t index, uint8_t size, const uint8_t* buffer)
{
	LCD_CS_CLR();
	LCD_DC_CLR();
	LCD_SendByte(index);
	LCD_DC_SET();
	LCD_SenndMoreSequence(size, buffer);
	LCD_CS_SET();
}

void lcd_write_data(uint8_t data)
{
	LCD_DC_SET();  
	LCD_CS_CLR(); //片选
	LCD_SendByte(data);
	LCD_CS_SET();  //设置高
}


void lcd_write_data_16bit(uint8_t datah,uint8_t datal)
{
    lcd_write_data(datah);
    lcd_write_data(datal);
}

void lcd_write_data_more(uint8_t size, uint8_t* buffer)
{
	LCD_CS_CLR();	
	LCD_DC_SET(); 
	LCD_SenndMoreSequence(size, buffer);
	LCD_CS_SET();
}

static void lcd_reset(void)//pull down 40ms,wait 20ms;
{
	LCD_RST_SET();
	systick_delay_ms(1);
	LCD_RST_CLR();
	systick_delay_ms(2);
	LCD_RST_SET();
	systick_delay_ms(1);
}

#define BOTTOM_TO_TOP 						0x82
#define RIGHT_TO_LEFT						0x42
#define REVERSE_MODE						0x22
#define LCD_REFRESH_BOTTOM_TO_TOP			0x12
#define BGR									0x0A
#define LCD_REFRESH_RIGHT_TO_LEFT			0x06
#define MADCTL_NONE							0x02
void LCD_P2016_Init()
{
	systick_delay_ms(120);
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
//	lcd_write_index(0xbb);	//vcom
//	lcd_write_data(0x1f);//0x20
//	lcd_write_index(0xc0);	//LCM Control
//	lcd_write_data(0x2c);
//	lcd_write_index(0xc2);		//VDV and VRH Command Enable
//	lcd_write_data(0x01);
//	lcd_write_index(0xc4); 		//VDV Set
//	lcd_write_data(0x20);
//	lcd_write_index(0xc6);		//Frame Rate Control in Normal Mode
//	lcd_write_data(0x0f);
//	lcd_write_index(0xd0);		//Power Control 1
//	lcd_write_data(0xa4);
//	lcd_write_data(0xa1);
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
	
	const uint8_t Data_0x2a[] = {0x00,0x50,0x01,0x40};
	lcd_write_index_with_data(0x2a, 4, Data_0x2a);//Column Address Set.

	const uint8_t Data_0x2b[] = {0x00,0x00,0x00,0xF0};
	lcd_write_index_with_data(0x2b, 4, Data_0x2b);// Row Address Set

	lcd_write_index(0x21);//Display Inversion On
	lcd_write_index(0x29);//Display On
	lcd_write_index(0x2C);//Memory Write
	lcd_write_index(0x2C);
}

void ILI9341_GramScan ( uint8_t ucOption )
{	
	//参数检查，只可输入0-7
	if(ucOption >7 )
		return;

	//0x36命令参数的高3位可用于设置GRAM扫描方向	
	lcd_write_index ( 0x36 ); 
	lcd_write_data ( 0x08 |(ucOption<<5));//根据ucOption的值设置LCD参数，共0-7种模式
	lcd_write_index ( 0x2A ); 
	lcd_write_data ( 0x00 );		/* x 起始坐标高8位 */
	lcd_write_data ( 0x00 );		/* x 起始坐标低8位 */
	lcd_write_data ( ((240-1)>>8)&0xFF ); /* x 结束坐标高8位 */	
	lcd_write_data ( (240-1)&0xFF );				/* x 结束坐标低8位 */

	lcd_write_index ( 0x2B ); 
	lcd_write_data ( 0x00 );		/* y 起始坐标高8位 */
	lcd_write_data ( 0x00 );		/* y 起始坐标低8位 */
	lcd_write_data ( ((240-1)>>8)&0xFF );	/* y 结束坐标高8位 */	 
	lcd_write_data ( (240-1)&0xFF );				/* y 结束坐标低8位 */

	/* write gram start */
	lcd_write_index ( 0x2C );	
}


void LCD_Init(void)
{
	TIM_PWM_Intial();
	
	LCD_SPI_Init();

	lcd_reset();
	
	LCD_P2016_Init();
	
	LCD_StartDraw = 0;
}

/*!
    \brief      set lcd display region
    \param[in]  x_start: the x position of the start point
    \param[in]  y_start: the y position of the start point
    \param[in]  x_end: the x position of the end point
    \param[in]  y_end: the y position of the end point
    \param[out] none
    \retval     none
*/


void LcdSetRegion(LcdPos_t* Pos)
{
	Pos->x_end += 0x50;
	Pos->x_start += 0x50;
	
	lcd_write_index(0x2a);
	LCD_CS_CLR();
	LCD_DC_SET();
	LCD_SenndMoreReversed(4, (uint8_t*)&(Pos->x_end));
	LCD_CS_SET();
	
	lcd_write_index(0x2b);
	LCD_CS_CLR();
	LCD_DC_SET();
	LCD_SenndMoreReversed(4, (uint8_t*)&(Pos->y_end));
	LCD_CS_SET();

	lcd_write_index(0x2c);
	Pos->x_end -= 0x50;
	Pos->x_start -= 0x50;
}

void LcdClearScreen(uint16_t color)
{
	LcdPos_t Pos = {
		.x_start = 0,
		.x_end = 240-1,
		.y_start = 0,
		.y_end = 240-1
	};
	LcdSetRegion(&Pos);
	LCD_CS_CLR();
	LCD_DC_SET();
	for(int i = 0; i < 240 * 240; i++)
	{
		LCD_SenndMoreReversed(2, (uint8_t*)&color);
	}
	LCD_CS_SET();
}

void LcdDrawArea(LcdPos_t* Pos, const uint16_t* color)
{
#if	(!DMA_DELAY)
	uint32_t time_out_count = 0;
	while(LCD_StartDraw||time_out_count > 60000)
		time_out_count++;
	LCD_StartDraw = 1;
#endif
	int total = (Pos->x_end - Pos->x_start + 1)*(Pos->y_end - Pos->y_start + 1);
	LcdSetRegion(Pos);
	LCD_CS_CLR();
	LCD_DC_SET();
//	LCD_SenndMoreSequenceU16(total, color);
//	LCD_CS_SET();
	SPI_LCD_DMA_Write(color,total);
}

//void BlockWrite(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend) 
//{
//	LCD_CS_CLR();
//	Xstart=Xstart+0x50;
//	Xend=Xend+0x50;
//	lcd_write_index(0x2a);    //
//	lcd_write_data((Xstart>>8)&0xff);   //???
//	lcd_write_data(Xstart&0xff); 	
//	lcd_write_data((Xend>>8)&0xff); 
//	lcd_write_data(Xend&0xff);	//7f
//	
//	lcd_write_index(0x2b);    //
//	lcd_write_data((Ystart>>8)&0xff); 
//	lcd_write_data(Ystart&0xff); 
//	lcd_write_data((Yend>>8)&0xff); 
//	lcd_write_data(Yend&0xff);  //a0

//	lcd_write_index(0x2c);

//	
//	LCD_CS_SET();
//}


void lcd_clear(uint16_t color)
{
  uint16_t i;
	uint8_t j[2]={0,0};
	j[0]=(color>>8) & 0xff;  //高位
	j[1]=color & 0xff;
	
//	BlockWrite(0,(240-1),0,(240-1));
	for(i = 0; i < 240 * 240; i++)
	{
		lcd_write_data_16bit(j[0],j[1]);
	}
}
//void lcd_set_xy(uint16_t x,uint16_t y)
//{
//    /* write the register address 0x2A*/
//    lcd_write_index(0x2A);
//    LCD_DC_SET();
//    LCD_SendByte(x >> 8);
//    LCD_SendByte(x);
//    LCD_SendByte(x >> 8);
//    LCD_SendByte(x);

//    /* write the register address 0x2B*/
//    lcd_write_index(0x2B);
//    LCD_DC_SET();
//    LCD_SendByte(y >> 8);
//    LCD_SendByte(y);
//    LCD_SendByte(y >> 8);
//    LCD_SendByte(y);

//    /* write the register address 0x2C*/
//    lcd_write_index(0x2C);
//}

///*!
//    \brief      draw a point on the lcd
//    \param[in]  x: the x position of the point 
//    \param[in]  y: the y position of the point 
//    \param[in]  data: write the register data
//    \param[out] none
//    \retval     none
//*/
//void lcd_point_set(uint16_t x,uint16_t y,uint16_t data)
//{
//    lcd_set_xy(x+0x50,y);
//    lcd_write_data(data >> 8);
//    lcd_write_data(data);
//}

//void ILI9341_REG_Config( void )
//{
//	/*  Power control B (CFh)  */
//	lcd_write_index ( 0xCF  );
//	lcd_write_data ( 0x00  );
//	lcd_write_data ( 0x81  );
//	lcd_write_data ( 0x30  );
//	
//	/*  Power on sequence control (EDh) */
//	lcd_write_index ( 0xED );
//	lcd_write_data ( 0x64 );
//	lcd_write_data ( 0x03 );
//	lcd_write_data ( 0x12 );
//	lcd_write_data ( 0x81 );
//	
//	/*  Driver timing control A (E8h) */
//	lcd_write_index ( 0xE8 );
//	lcd_write_data ( 0x85 );
//	lcd_write_data ( 0x10 );
//	lcd_write_data ( 0x78 );
//	
//	/*  Power control A (CBh) */
//	lcd_write_index ( 0xCB );
//	lcd_write_data ( 0x39 );
//	lcd_write_data ( 0x2C );
//	lcd_write_data ( 0x00 );
//	lcd_write_data ( 0x34 );
//	lcd_write_data ( 0x02 );
//	
//	/* Pump ratio control (F7h) */
//	lcd_write_index ( 0xF7 );
//	lcd_write_data ( 0x20 );
//	
//	/* Driver timing control B */
//	lcd_write_index ( 0xEA );
//	lcd_write_data ( 0x00 );
//	lcd_write_data ( 0x00 );
//	
//	/* Frame Rate Control (In Normal Mode/Full Colors) (B1h) */

//	lcd_write_index ( 0xB1 );
//	lcd_write_data ( 0x00 );
//	lcd_write_data ( 0x1B );
//	
//	/*  Display Function Control (B6h) */
//	lcd_write_index ( 0xB6 );
//	lcd_write_data ( 0x0A );
//	lcd_write_data ( 0xA2 );
//	
//	/* Power Control 1 (C0h) */
//	lcd_write_index ( 0xC0 );
//	lcd_write_data ( 0x35 );
//	
//	/* Power Control 2 (C1h) */
//	lcd_write_index ( 0xC1 );
//	lcd_write_data ( 0x11 );
//	
//	/* VCOM Control 1 (C5h) */
//	lcd_write_index ( 0xC5 );
//	lcd_write_data ( 0x45 );
//	lcd_write_data ( 0x45 );
//	
//	/*  VCOM Control 2 (C7h)  */
//	lcd_write_index ( 0xC7 );
//	lcd_write_data ( 0xA2 );
//	
//	/* Enable 3G (F2h) */
//	lcd_write_index ( 0xF2 );
//	lcd_write_data ( 0x00 );
//	
//	/* Gamma Set (26h) */
//	lcd_write_index ( 0x26 );
//	lcd_write_data ( 0x01 );
//	
//	/* Positive Gamma Correction */
//	lcd_write_index ( 0xE0 ); //Set Gamma
//	lcd_write_data ( 0x0F );
//	lcd_write_data ( 0x26 );
//	lcd_write_data ( 0x24 );
//	lcd_write_data ( 0x0B );
//	lcd_write_data ( 0x0E );
//	lcd_write_data ( 0x09 );
//	lcd_write_data ( 0x54 );
//	lcd_write_data ( 0xA8 );
//	lcd_write_data ( 0x46 );
//	lcd_write_data ( 0x0C );
//	lcd_write_data ( 0x17 );
//	lcd_write_data ( 0x09 );
//	lcd_write_data ( 0x0F );
//	lcd_write_data ( 0x07 );
//	lcd_write_data ( 0x00 );
//	
//	/* Negative Gamma Correction (E1h) */
//	lcd_write_index ( 0XE1 ); //Set Gamma
//	lcd_write_data ( 0x00 );
//	lcd_write_data ( 0x19 );
//	lcd_write_data ( 0x1B );
//	lcd_write_data ( 0x04 );
//	lcd_write_data ( 0x10 );
//	lcd_write_data ( 0x07 );
//	lcd_write_data ( 0x2A );
//	lcd_write_data ( 0x47 );
//	lcd_write_data ( 0x39 );
//	lcd_write_data ( 0x03 );
//	lcd_write_data ( 0x06 );
//	lcd_write_data ( 0x06 );
//	lcd_write_data ( 0x30 );
//	lcd_write_data ( 0x38 );
//	lcd_write_data ( 0x0F );
//	
//	/* memory access control set */
//	lcd_write_index ( 0x36 ); 	
//	lcd_write_data ( 0xC8 );    /*竖屏  左上角到 (起点)到右下角 (终点)扫描方式*/
//	
//	/* column address control set */
//	lcd_write_index ( 0x2A ); 
//	lcd_write_data ( 0x00 );
//	lcd_write_data ( 0x00 );
//	lcd_write_data ( 0x00 );
//	lcd_write_data ( 0xEF );
//	
//	/* page address control set */
//	lcd_write_index ( 0x2B ); 
//	lcd_write_data ( 0x00 );
//	lcd_write_data ( 0x00 );
//	lcd_write_data ( 0x01 );
//	lcd_write_data ( 0x3F );
//	
//	/*  Pixel Format Set (3Ah)  */
//	lcd_write_index ( 0x3a ); 
//	lcd_write_data ( 0x55 );
//	
//	/* Sleep Out (11h)  */
//	lcd_write_index ( 0x11 );	
//	systick_delay_ms(120);
//	
//	/* Display ON (29h) */
//	lcd_write_index ( 0x29 ); 
//}

//void lcd_line_draw( uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1 , uint16_t color )
//{
//    short dx,dy; 
//    short temp;

//    if( x0 > x1 ){
//        temp = x1;
//        x1 = x0;
//        x0 = temp;   
//    }
//    if( y0 > y1 ){
//        temp = y1;
//        y1 = y0;
//        y0 = temp;   
//    }
//  
//    dx = x1-x0; 
//    dy = y1-y0;   

//    if( dx == 0 ){
//        do{ 
//            lcd_point_set(x0, y0, color);
//            y0++;
//        }while( y1 >= y0 ); 
//        return; 
//    }
//    if( dy == 0 ){
//        do{
//            lcd_point_set(x0, y0, color); 
//            x0++;
//        }while( x1 >= x0 ); 
//        return;
//    }
//    /* Bresenham algorithm */
//    if( dx > dy ){
//        temp = 2 * dy - dx;  
//        while( x0 != x1 ){
//            lcd_point_set(x0,y0,color); 
//            x0++;
//            if( temp > 0 ){
//                y0++;         
//                temp += 2 * dy - 2 * dx; 
//            }else{
//                temp += 2 * dy;   
//            }       
//        }
//        lcd_point_set(x0,y0,color);
//    }else{
//        temp = 2 * dx - dy;
//        while( y0 != y1 ){
//            lcd_point_set(x0,y0,color);     
//            y0++;
//            if( temp > 0 ){
//                x0++;
//                temp+=2*dy-2*dx; 
//            }else{
//                temp += 2 * dy;
//            }
//        } 
//        lcd_point_set(x0,y0,color);
//    }
//} 


//void lcd_rectangle_fill(uint16_t start_x,uint16_t start_y,uint16_t end_x,uint16_t end_y,uint16_t color)
//{
//    uint16_t x, y;
//    x = start_x;
//    y = start_y;

//    BlockWrite(start_x,end_x-1,start_y,end_y);
//    
//    LCD_DC_SET();
//    for (x = start_x; x < end_x; x++) {
//        for (y = start_y; y < end_y; y++) {
//            LCD_SendByte(color>>8);
//            LCD_SendByte((uint8_t)color);
//        }
//    }

//}

//void lcd_circle_fill(uint16_t x0,uint16_t y0,uint16_t r,uint16_t color)
//{
//    int x,y;
//    int deltax,deltay;
//    int d;
//    int xi;
//    x=0;
//    y=r;
//    deltax=3;
//    deltay=2-r-r;
//    d=1-r;

//    lcd_point_set(x+x0,y+y0,color);
//    lcd_point_set(x+x0,-y+y0,color);
////    for(xi=-r+x0;xi<=r+x0;xi++){
////        lcd_point_set(xi,y0,color);
////    }
//    BlockWrite(-r+x0,r+x0,y0,y0);
//    
//    LCD_DC_SET();
//    for (xi = -r+x0; xi <= r+x0; xi++) {
//        LCD_SendByte(color>>8);
//        LCD_SendByte((uint8_t)color);
//    }
//    
//    while(x<y){
//        if(d<0){
//            d+=deltax;
//            deltax+=2;
//            x++;
//        }else{
//            d+=(deltax+deltay);
//            deltax+=2;
//            deltay+=2;
//            x++;
//            y--;
//        }
//        
//        for(xi=-x+x0;xi<=x+x0;xi++)
//        {
////            lcd_point_set(xi,-y+y0,color);
////            lcd_point_set(xi,y+y0,color);
//            
//            lcd_set_xy(xi+0x50,-y+y0);
//            LCD_DC_SET();
//            LCD_SendByte(color >> 8);
//            LCD_SendByte(color);
//            lcd_set_xy(xi+0x50,y+y0);
//            LCD_DC_SET();
//            LCD_SendByte(color >> 8);
//            LCD_SendByte(color);
//        }
//        
//        for(xi=-y+x0;xi<=y+x0;xi++)
//        {
////            lcd_point_set(xi,-x+y0,color);
////            lcd_point_set(xi,x+y0,color);
//            lcd_set_xy(xi+0x50,-x+y0);
//            LCD_DC_SET();
//            LCD_SendByte(color >> 8);
//            LCD_SendByte(color);
//            lcd_set_xy(xi+0x50,x+y0);
//            LCD_DC_SET();
//            LCD_SendByte(color >> 8);
//            LCD_SendByte(color);
//        }
//    }
//}



