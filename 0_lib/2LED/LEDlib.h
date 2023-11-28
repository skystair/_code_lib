#ifndef __LEDLIB_H__
#define __LEDLIB_H__

#include "string.h"

#define LED_STRUCT_SIZE		3

typedef struct{
	unsigned char u8state;
	unsigned short int u16Delay;
	
}LEDstruct;


#define LED_BREATH_PERIOD	1000
#define Set_LED_Breath_Duty(x)	;
typedef struct{
	unsigned char u8state;
	unsigned char flag;
	unsigned char changedelay;
	unsigned short int delay;
	unsigned short int u16duty;
}LEDbreathstruct;



#define LED_NUM	4

#define LED_BREATH_NUM	4

#define LED1_ON()	1
#define LED2_ON()	1
#define LED3_ON()	1
#define LED4_ON()	1

#define LED1_OFF()	0
#define LED2_OFF()	0
#define LED3_OFF()	0
#define LED4_OFF()	0


#define LED_STATE_OFF			0
#define LED_STATE_ON			1
#define LED_STATE_FLASH_200MS	2	//快闪
#define LED_STATE_FLASH_500MS	3	//闪烁
#define LED_STATE_FLASH_1S		4	//慢闪
#define LED_STATE_Breath		5



extern void LED_ValueInit(void);
extern void LED_DelayADD(void);
extern void LED_Func(void);

#endif
