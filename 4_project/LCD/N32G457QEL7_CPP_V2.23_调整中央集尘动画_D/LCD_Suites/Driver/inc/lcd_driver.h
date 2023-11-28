#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "n32g45x.h"


#define RED             (uint16_t)0xF800
#define GREEN           (uint16_t)0x07E0
#define BLUE            (uint16_t)0x001F
#define WHITE           (uint16_t)0xFFFF
#define BLACK           (uint16_t)0x0000
#define YELLOW          (uint16_t)0xFFE0

/* grays */
#define GRAY0           (uint16_t)0xEF7D
#define GRAY1           (uint16_t)0x8410
#define GRAY2           (uint16_t)0x4208



#ifdef H_VIEW
    #define X_MAX_PIXEL         (uint16_t)320
    #define Y_MAX_PIXEL         (uint16_t)240
#else
    #define X_MAX_PIXEL         (uint16_t)240
    #define Y_MAX_PIXEL         (uint16_t)240
#endif

#define	LCD_CMD_SLEEP_OUT	0x11
#define	LCD_CMD_MEM_ACCESS	0x36


typedef struct
{
	uint16_t x_end;
	uint16_t x_start;
	uint16_t y_end;
	uint16_t y_start;
}LcdPos_t;

extern volatile uint8_t LCD_StartDraw;
void lcd_write_data(uint8_t data);
/* lcd init */
void LCD_Init(void);
void LcdClearScreen(uint16_t color);
void LcdDrawArea(LcdPos_t* Pos, const uint16_t* color);
void LcdClearScreenTest(void);
void LcdClearScreenTest2(void);
/* clear the lcd */
void lcd_clear(uint16_t color);
/* set the start display point of lcd */
void lcd_set_xy(uint16_t x,uint16_t y);
/* draw a point on the lcd */
void lcd_point_set(uint16_t x,uint16_t y,uint16_t data);

//void lcd_picture_draw(uint16_t start_x,uint16_t start_y,uint16_t end_x,uint16_t end_y,uint8_t *pic);
//void lcd_write_index(uint8_t index);
//void lcd_line_draw( uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1 , uint16_t color );
void lcd_rectangle_fill(uint16_t start_x,uint16_t start_y,uint16_t end_x,uint16_t end_y,uint16_t color);
void lcd_circle_fill(uint16_t x0,uint16_t y0,uint16_t r,uint16_t color);


//用于Ugui 系统
//void UserPixelSetFunction(UG_S16 x,UG_S16 y,UG_COLOR c);

#ifdef __cplusplus
}
#endif

#endif /* LCD_DRIVER_H */
