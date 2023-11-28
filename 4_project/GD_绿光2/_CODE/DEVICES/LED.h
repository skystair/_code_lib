#ifndef __LED_H__
#define __LED_H__

#define LED_NUM		10

#define LED_B_BREATH_PERIOD		1500

#define LED_STATE_OFF			0
#define LED_STATE_ON			1
#define LED_STATE_FLASH			2	//0.8sON 0.4sOFF
#define LED_STATE_BREATH		3

//D1
#define ucLED_dustG_duty		ucLED_State[0]
#define ucLED_dustR_duty		ucLED_State[1]
//D2
#define ucLED_num1				ucLED_State[2]
#define ucLED_num2				ucLED_State[3]
//D3
#define ucLED_numP				ucLED_State[4]
#define ucLED_num3				ucLED_State[5]
//D4
#define ucLED_MAX_State			ucLED_State[6]
#define ucLED_Rthunder_State	ucLED_State[7]
#define ucLED_Gthunder_State	ucLED_State[8]
#define ucLED_heat				ucLED_State[9]

extern unsigned char ucEflag;
extern unsigned char ucL0flag;
extern unsigned char ucLED_State[LED_NUM];
//extern unsigned char ucLED_flash_Delay[LED_NUM];

extern void LED_ValueInit(void);
extern void LED_Func(void);
extern unsigned char num2data(unsigned char num);



#endif
