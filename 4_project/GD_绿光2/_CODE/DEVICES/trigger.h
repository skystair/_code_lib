#ifndef _TRIGGER_H__
#define _TRIGGER_H__


#define LOADNUM			7
#define LOADpwmNUM		1

//
#define u8LedGState		ucloadState[0]
#define u8MotState		ucloadState[1]
#define u8heatState		ucloadState[2]
#define u8UVState		ucloadState[3]
#define u8L_IRState		ucloadState[4]
#define u8R_IRState		ucloadState[5]
#define u8ChargeState	ucloadState[6]
//
#define BrushStruct		PWMLoad[0]


#define PWMstructSize	8
typedef struct {
	unsigned char ucState;
	unsigned short int u16_duty;
	unsigned short int u16_start_duty;
	unsigned short int u16_start_delay;
	unsigned char ucstep_delay;
}PWMLoadStruct;

extern unsigned short int u16Mmotor_PWM_duty;

extern unsigned char u8heatstep;
extern unsigned char u8heatdelay;
extern unsigned char u8heattime;
extern unsigned char u8heatcomleteflag;

extern unsigned char ucloadState[LOADNUM];
extern PWMLoadStruct PWMLoad[LOADpwmNUM];

extern void trigger_ValueInit(void);
extern void Trigger_control(void);

#endif
