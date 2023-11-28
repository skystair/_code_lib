#include "config.h"
#include "trigger.h"

unsigned short int u16waitNtick = 0;
	
unsigned char u8Brush_isONflag;

unsigned char u8heatstep;
unsigned char u8heatdelay;
unsigned char u8heattime;
unsigned char u8heatcomleteflag;
// Load 1/0
unsigned char ucloadState[LOADNUM];
unsigned short int u16Mmotor_PWM_duty;
// Load PWM
PWMLoadStruct PWMLoad[LOADpwmNUM];
void trigger_ValueInit(void);
void Trigger_control(void);
void HeatOFF_T(unsigned char u8OFFtimeS,unsigned char u8periodS);
	
void trigger_ValueInit(void)
{
	u16waitNtick = 0;
	u8Brush_isONflag = 0;
	u8heatstep = 0;
	u8heatdelay = 0;
	u8heattime = 0;
	u8heatcomleteflag = 0;
	
	memset(&ucloadState,0,LOADNUM);
	for(unsigned char i =0;i<LOADpwmNUM;i++){
		memset(&PWMLoad[i],0,PWMstructSize);
	}
}
unsigned int u32tempduty = 1000;

void Trigger_control(void){
	
//GTC==============================================
	if(adc_result[0] <=500){
		BrushStruct.u16_duty = 1000;
	}else if(adc_result[0] <2000){
		BrushStruct.u16_duty = (2000- adc_result[0]) *10/15;
	}else{
		BrushStruct.u16_duty = 0;
	}
	if(BrushStruct.u16_duty <= 10){
		BrushStruct.u16_duty = 10;
	}
	if(BrushStruct.u16_duty > 1000){
		BrushStruct.u16_duty = 1000;
	}
//IIC=========================================
//	if(u16data1 <200){
//		u32tempduty = 0;
//	 }else 
	Brush_Duty_Set(BrushStruct.u16_duty);
	
	if(u16data1 <7000){
		u32tempduty = u16data1/7;
	}else{
		u32tempduty = 1000;
	}
	if(u32tempduty > u16Mmotor_PWM_duty){
		u16Mmotor_PWM_duty++;
	}else{
		u16Mmotor_PWM_duty--;
	}
	if(u16Mmotor_PWM_duty > 1000){
		u16Mmotor_PWM_duty = 1000;
	}
	if(u16Mmotor_PWM_duty <= 10){
		u16Mmotor_PWM_duty = 10;
	}
	Mot_Duty_Set(u16Mmotor_PWM_duty); 
	 
	//PWM1---------------------------------------
	//brush
	
	 
}

