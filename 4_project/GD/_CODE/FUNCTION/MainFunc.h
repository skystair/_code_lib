#ifndef __MAINFUNC_H__
#define __MAINFUNC_H__

#define SHIFT_OFF		0
#define SHIFT_1			1
#define SHIFT_2			2

#define SHIFT_AUTO		SHIFT_1	
#define SHIFT_MAX		SHIFT_2

#define WORKMODE_IDLE		0
#define WORKMODE_DSG		1
#define WORKMODE_CHG		2


#define ERROR1	1	//地刷堵转
#define ERROR2	2	//NTC开路/短路
#define ERROR3	3	//加热短路
#define ERROR4	4	//主电机无FG
#define ERROR5	5	//CHG_I
#define ERROR6	6	//CHG_V

#define ERROR77	77	//L0

extern unsigned char ucWorkMode;
extern unsigned char ucshitf;
extern unsigned char ucPWRdowndelay;
//DSG------------------------------
extern unsigned int Discharge_Tick_1ms;

extern unsigned char u8BatLowSDdelay;
extern unsigned char u8BrushOverISDflag;
//CHG-------------------------------------
extern unsigned char ucCHGcompleteFlag;
extern unsigned short int u16CHG_delay;
extern unsigned char ucCHGcompleteDelay1;	//充电完成延时1，大于24V用
extern unsigned char ucCHGcompleteDelay2;	//充电完成延时2，大于25.2V用
extern unsigned char ucCHGoverIdelay;
extern unsigned char ucCHGoverIflag;


extern void WorkModeValueInit(void);
extern void ModeFunc(void);

#endif

