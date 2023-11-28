#include "config.h"

//
unsigned char u8BrushOverIflag;
unsigned char u8BrushOverIDelay1;
unsigned char u8BrushOverIDelay2;

//
unsigned char u8DSG_Lbatflag;
unsigned char u8DSG_batdelay1;
unsigned char u8DSG_batdelay2;

//NTC
unsigned char u8NTCstate;
unsigned char u8NTCdelay1;
unsigned char u8NTCdelay2;
unsigned char u8NTCdelay3;

void idlevalueinit_AD(void);
void ad_valueInit(void);
void adfun_DSG(void);
void adfun_CHG(void);

void ad_valueInit(void){

	u8BrushOverIflag = 0;
	u8BrushOverIDelay1 = 0;
	u8BrushOverIDelay2 = 0;
	
	u8DSG_Lbatflag = 0;
	u8DSG_batdelay1 = 0;
	u8DSG_batdelay2 = 0;
	
	u8NTCstate = 0;
	u8NTCdelay1 = 0;
	u8NTCdelay2 = 0;
	u8NTCdelay3 = 0;
}

void adfun_DSG(void){
	//1.地刷电流---------------------------------------
	//short protection in adcx.c
	if(AD_I_BRUSH_AVG >= BRUSH_I_05A){//I short 2
		if(u8BrushOverIDelay2 >= TIME1MS_100MS){
			u8BrushOverIDelay2 = TIME1MS_100MS;
			#ifdef BRUSH_OVER_I2
				u8BrushOverIflag = 2;
			#endif
			u8BrushOverIDelay1 = TIME100MS_3S;
		}
	}else if(AD_I_BRUSH_AVG >= BRUSH_I_03A0){//I short 1
		if(u8BrushOverIDelay1 >= TIME100MS_3S){
			u8BrushOverIDelay1 = TIME100MS_3S;
			#ifdef BRUSH_OVER_I1
				u8BrushOverIflag = 1;
			#endif
		}
		u8BrushOverIDelay2 = 0;
	}else{
		u8BrushOverIflag = 0;
		u8BrushOverIDelay1 = 0;
		u8BrushOverIDelay2 = 0;
	}
	//2.NTC in trigger.c-----------------------------
	if((AD_HEATNTC >4000) || (AD_HEATNTC < 100)){
		if(u8NTCdelay1 >= 30){
			u8NTCdelay1 = 30;
			u8NTCstate = 5;
		}
		u8NTCdelay2 = 0;
		u8NTCdelay3 = 0;
	}else{
		u8NTCdelay1 = 0;
		
		if(AD_HEATNTC > AD_NTC_45C){//小于45C，全开
			u8NTCstate = 1;
			
			u8NTCdelay2 = 0;
			u8NTCdelay3 = 0;
		}else if(AD_HEATNTC >AD_NTC_50C){//45~50，	半开
			if(u8NTCdelay2 >10){
				u8NTCdelay2 = 10;
				u8NTCstate = 2;
			}
			
			u8NTCdelay3 = 0;
		}else if(AD_HEATNTC >AD_NTC_57C){//50~57，	保温
			if(u8NTCdelay3 >= 10){
				u8NTCdelay3 = 10;
				u8NTCstate = 3;
			}
			
			u8NTCdelay2 = 0;
		}else{
			u8NTCstate = 4;	//大于57				关
			
			u8NTCdelay2 = 0;
			u8NTCdelay3 = 0;
		}
	}
	
	//5.放电电压
	if(AD_V_BAT <= BAT_V_17V1){//低压2
		if(u8DSG_batdelay2 >= TIME100MS_1S){
			u8DSG_batdelay2 = TIME100MS_1S;
			u8DSG_Lbatflag = 2;
		}
		u8DSG_batdelay1 = 0;
	}else if(AD_V_BAT <= BAT_V_LOW1){//低压1
		if(u8DSG_batdelay1 >= TIME100MS_1S){
			u8DSG_batdelay1 = TIME100MS_1S;
			u8DSG_Lbatflag = 1;
		}
		u8DSG_batdelay2 = 0;
	}else{//正常电压
		u8DSG_batdelay1 = 0;
		u8DSG_batdelay2 = 0;
		u8DSG_Lbatflag = 0;
	}
}

void adfun_CHG(void){
	if(AD_I_CHGR > CHG_CUT_I){
		if(ucCHGoverIdelay >= 100){
			ucCHGoverIdelay = 100;
			
			ucCHGoverIflag = 1;
		}
	}else{
		ucCHGoverIdelay = 0;
	}
}
void adhandle(void){
	//0.key in key.c
//=============================================================
	
	
	if(ucWorkMode == WORKMODE_DSG){
		//3.HWDUST in dust.c---------------------------------
		//4.V_CHG in key.c-----------------------------------
	}
}
