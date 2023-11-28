#ifndef __LCDFUNC_H__
#define __LCDFUNC_H__


#define BOTTOM_TO_TOP 						0x82
#define RIGHT_TO_LEFT						0x42
#define REVERSE_MODE						0x22
#define LCD_REFRESH_BOTTOM_TO_TOP			0x12
#define BGR									0x0A
#define LCD_REFRESH_RIGHT_TO_LEFT			0x06
#define MADCTL_NONE							0x02

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















extern unsigned char u8LCDpicnum;
extern unsigned char u8LCDdelay;
extern unsigned char u8LCDsendingflag;

extern unsigned char u8doubleflag;
extern unsigned char u8LCDbuff[240*240*2];
extern unsigned char u8LCDstate;
extern unsigned char u8LCDresettick;
extern unsigned int u8LCDdipsize;

extern void LCDvalueinit(void);
extern void funcLCD(void);
extern void LCDreset(void);
//extern void LCD_fresh(void);


#endif