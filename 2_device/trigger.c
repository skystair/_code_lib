#include "config.h"
#include "trigger.h"

unsigned short int u16waitNtick = 0;

unsigned char u8heatstep;
unsigned char u8heattime;
unsigned char u8heatcomleteflag;

unsigned short int u16heatcnt;
unsigned short int u16heatcmp;
// Load 1/0
unsigned char ucloadState[LOADNUM];
unsigned short int u16Mmotor_PWM_duty;
// Load PWM
PWMLoadStruct PWMLoad[LOADpwmNUM];
unsigned int u32tempbrushduty;

void trigger_ValueInit(void);
void Trigger_Calculate(void);
void Trigger_control(void);
void HeatOFF_T(unsigned char u8OFFtimeS,unsigned char u8periodS);

void trigger_ValueInit(void)
{
	u16waitNtick = 0;
	memset(&ucloadState,0,LOADNUM);
	BrushStruct.ucState = 0;
	u32tempbrushduty = 1000;
	
	u16heatcnt = 0;
	u16heatcmp = 0;
	u8heatstep = 0;
	u8heattime = 0;
	u8heatcomleteflag = 0;
}


void Trigger_Calculate(void){
	//MOT-----------------------------------------------------
	if(u8MotState == 1){//shift1
		EN_MOT_ON;
		//auto
		if (Dust.Num_1s <= DUST_VALUE_MIN)        // 灰尘很少 0
		{
			u16Mmotor_PWM_duty = 450;//最低功率
		}
		else if (Dust.Num_1s <= DUST_VALUE_MAX)   // 灰尘适中 1~300
		{
			u16Mmotor_PWM_duty = 450
				   + (uint32_t)(Dust.Num_1s)
				   * (900 - 450) 
				   / DUST_VALUE_MAX;
		}
		else                                                    // 灰尘很多 >300
		{
			u16Mmotor_PWM_duty = 1000;//最高功率
		}
		if(u16waitNtick >=3){
			u16waitNtick = 3;
		}
	}else if(u8MotState == 2){//shift2
		EN_MOT_ON;
		u16Mmotor_PWM_duty = 900;//最高功率
		//max
		if(u16waitNtick >=3){
			u16waitNtick = 3;
		}
	}else{
		u32FGtime = 0;
//		u32FGtick = 0;
		u16Mmotor_PWM_duty = 0;
		
		if(u16waitNtick < 3){
			u16waitNtick = 0;
			EN_MOT_OFF;
		}else if(u16waitNtick <= 7000){
			//u16waitNtick = 0;
		}else{
			u16waitNtick = 0;
		}
	}
//HEAT-----------------------------------------------------
	if(u8heatState == 0){
		u16heatcnt = 0;
		u16heatcmp = 0;
		u8heatstep = 0;
		u8heattime = 0;
		u8heatcomleteflag = 0;
	}else{
		//加热2min后关闭
		if(u8heattime >= 120){
			u8heatState = 0;
		}
		
	//根据NTC状态选择加热功率---------------
		if(u8NTCstate == 5){
			u8heatState = 0;
		}else{
			u8heatstep = u8NTCstate;
			if(u8heatstep >= 3){
				u8heatcomleteflag = 1;
			}
		}
		//执行不同加热功率---------------
		if(u8heatstep == 1){	//全开
			u16heatcmp = 1000;
		}else if(u8heatstep == 2){//半开
			u16heatcmp = 1000;	//				T = 4s,off 0s
		}else if(u8heatstep == 3){//保温
			u16heatcmp = 500;
		}else{
			u16heatcmp = 0;
		}
	}
//BRUSH---------------------------------------------------------
	if(BrushStruct.ucState != 0){
				//计算恒压所需占空比-----------------
//1---------------------------------------------------
//		if(AD_V_BAT <BAT_V_19V5){
//			u32tempbrushduty = 8755 - 386 *AD_V_BAT/100;
//		}else{
//			u32tempbrushduty = 1519 - 354 *AD_V_BAT/1000;//5420 - (3522000 - 605*AD_V_BAT)/10*AD_V_BAT/100000;
//		}
//		if(u32tempbrushduty > 1000){
//			u32tempbrushduty = 1000;
//		}
		#ifdef BRUSHOLD
//2---------------------------------------------------		
		u32tempbrushduty = 1632 - 403 *AD_V_BAT/1000;
		if(u32tempbrushduty < 500){
			u32tempbrushduty = 500;
		}
		#else
//3---------------------------------------------------
		u32tempbrushduty = 1657 - 393 *AD_V_BAT/1000;
		if(u32tempbrushduty < 500){
			u32tempbrushduty = 500;
		}
		#endif
	}
}

void Trigger_control(void){
	u16waitNtick++;
	//1ledG---------------------------------------------
	if(u8LedGState == 0){
		LEDG_OFF;
	}else{
		LEDG_ON;
	}
	//2mot---------------------------------------------
	Mot_Duty_Set(u16Mmotor_PWM_duty);//1000 - 
	//MOT tx
	
	//3heat---------------------------------------------
	if(u16heatcnt < u16heatcmp){
		HEAT_ON;
	}else if(u16heatcnt <=1000){
		HEAT_OFF;
	}else{
		u16heatcnt = 0;
	}
	//4 UV
	if(u8UVState == 0){
		UV_OFF;
	}else{
		UV_ON;
	}
	//
	if(u8L_IRState == 0){
		L_PHOTO_OFF;
	}else{
		L_PHOTO_ON;
	}
	//
	if(u8R_IRState == 0){
		R_PHOTO_OFF;
	}else{
		R_PHOTO_ON;
	}
	//5chg---------------------------------------------
	if(u8ChargeState == 0){
		CHG_OFF;
	}else{
		CHG_ON;
	}
	
	//PWM1---------------------------------------
	//brush
	switch(BrushStruct.ucState){
		case 0:
			BrushStruct.u16_duty = 0;
			BrushStruct.u16_start_delay = 0;
			BrushStruct.ucstep_delay = 0;
		break;
		case 1:
			if(BrushStruct.u16_start_delay <= 1){
				BrushStruct.u16_duty = 1000;
			}else{
				BrushStruct.u16_duty = 100;
				BrushStruct.u16_start_duty = u32tempbrushduty;
				BrushStruct.ucState++;
			}
		break;
		case 2:
			
			if(BrushStruct.u16_start_delay <= TIME1MS_1S){
				if(BrushStruct.ucstep_delay >= TIME1MS_10MS)
				{
					BrushStruct.ucstep_delay = 0;
					if(BrushStruct.u16_duty <= BrushStruct.u16_start_duty)
						BrushStruct.u16_duty += BrushStruct.u16_start_duty / 100;
					else
						BrushStruct.u16_duty = BrushStruct.u16_start_duty;
				}
			}else{
				BrushStruct.u16_start_delay = TIME1MS_1S;
				//BrushStruct.u16_duty = BrushStruct.u16_start_duty;
				BrushStruct.u16_duty = u32tempbrushduty;
			}
		break;
		default:break;
	}
	BrushStruct.u16_start_delay++;
	BrushStruct.ucstep_delay++;
	Brush_Duty_Set(BrushStruct.u16_duty);
}
