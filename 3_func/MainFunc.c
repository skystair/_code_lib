#include "config.h"
#include "MainFunc.h"

unsigned char ucshitf;
unsigned char ucWorkMode;
unsigned char ucPWRdowndelay;

//DSG
unsigned int Discharge_Tick_1ms;
unsigned char u8BrushOverISDflag;	//地刷过流执行标志位

unsigned char u8BatLowSDflag;	//低压执行标志位
unsigned char u8BatLowSDdelay;	//低压关机延时

//CHG
unsigned short int u16CHG_delay;

unsigned char ucCHGcompleteFlag;	//充电完成标志
unsigned char ucCHGcompleteDelay1;	//充电完成延时1，大于24V用
unsigned char ucCHGcompleteDelay2;	//充电完成延时2，大于25.2V用
unsigned char ucCHGuplockflag;
unsigned char ucCHGoverIdelay;
unsigned char ucCHGoverIflag;

void Idlevalueinit_MOD(void);
void WorkModeValueInit(void);

void ModeFunc(void);

void Idlevalueinit_MOD(void){
	Discharge_Tick_1ms = 0;
	u8BrushOverISDflag = 0;
	u8BatLowSDflag = 0;
	u8BatLowSDdelay = 0;
	
	u16CHG_delay = 0;
	ucCHGcompleteFlag = 0;
	ucCHGcompleteDelay1 = 0;
	ucCHGcompleteDelay2 = 0;
	ucCHGuplockflag = 0;
	ucCHGoverIdelay = 0;
	ucCHGoverIflag = 0;
	
	ucshitf = SHIFT_AUTO;//档位
}
void WorkModeValueInit(void){
	ucWorkMode = 0;
	ucPWRdowndelay = 0;
//	;
	Idlevalueinit_MOD();
}

void ModeFunc(void)
{	
	//掉电-------------------------------------------------------
	if(ucPWRdowndelay >=10){
		ucPWRdowndelay = 10;
		PWR_OFF;
	}else{
		
	}
	
	switch(ucWorkMode)
	{	
		case WORKMODE_IDLE://待机==========================================================
			BatCapPre();
			
			u8HeatIshortflag = 0;
		
			ad_valueInit();
			Idlevalueinit_MOD();
			
			u8FGdelay = 0;
			u8FGerrorflag = 0;
		
		//out device
			LED_IDLE();
			//关绿光显尘、主电机、加热、充电MOS、地刷
			trigger_ValueInit();

		//input
			//1.主1关
			if(KeyPWR.flag == 1){
				KeyPWR.flag = 0;
				//EN_MOT_ON;
				PWR_ON;
				ucPWRdowndelay = 0;
				ucWorkMode = WORKMODE_DSG;
				Dust_Start();
				u8heatState = 1;
				u8updataflag = 1;
				//BatCapPre();
//				uartEnable1();
			}
			//2.档位
			//3.加热
			//4.DC in
			if(KeyDCin.flag == 1){//报警in led.c
				ucWorkMode = WORKMODE_CHG;
				u8updataflag = 1;
				PWR_OFF;
				//BatCapPre();
//				if(AD_V_BAT > BAT_V_24V5){
//					ucCHGcompleteFlag = 1;
//					//u16Batfullflag = 1;
//				}
			}
			break;
		case WORKMODE_DSG://放电===========================================================
			Discharge_Tick_1ms++;
			ucPWRdowndelay = 0;
			adfun_DSG();
			if((*(__IO unsigned short int*) DATA_SAVE_ADDR0) != 0xffff){
				u16Batfullflag = 0xffff;
			}
		//out-------------------------------------------------------
			if((u8BatLowSDflag == 2)||(u8FGerrorflag ==1)){
				trigger_ValueInit();
			}else{
				if(u8BrushOverISDflag != 0){
					BrushStruct.ucState = 0;
				}else{
					if(BrushStruct.ucState == 0){
						BrushStruct.ucState = 1;//非保护常开
					}
				}
				u8LedGState = 1;	//常开
				u8MotState = ucshitf;
				u8L_IRState = 1;
				u8R_IRState = 1;
				
				if(AD_L_PHOTO <1200){
					if(AD_R_PHOTO <1200){
						u8UVState = 1;
					}else{
						u8UVState = 0;
					}
				}else{
					u8UVState = 0;
				}
				if((u8NTCstate != 5)&&(u8HeatIshortflag != 1)){//not NTCerror&Ishort
					if(KeyHEAT.flag == 1){
						KeyHEAT.flag = 0;
						
						if(u8heatState == 1){
							u8heatState = 0;
						}else{
							u8heatState = 1;
						}
					}
				}else{
					u8heatState = 0;
				}
			}
			//dsp------------------------
			LED_DSG();
		//in-----------------------------------------------------------
			//1.主1关
			if(KeyPWR.flag == 1){
				KeyPWR.flag = 0;
				
				ucshitf = 0;
				ucWorkMode = WORKMODE_IDLE;
			}
			//2.档位------------------------------------
			if(KeyMOD.flag == 1){
				KeyMOD.flag = 0;
				
				if(ucshitf == SHIFT_AUTO){
					ucshitf = SHIFT_MAX;
				}else{
					ucshitf = SHIFT_AUTO;
				}
			}
			//4.DCin------------------------------------
			if(KeyDCin.flag){
				ucWorkMode = WORKMODE_IDLE;
			}
		//保护---------------------------------------------------------
			//1.地刷堵转
			if(u8BrushOverIflag != 0){
				if(u8BrushOverISDflag == 0){
					//
				}
				u8BrushOverISDflag = 1;
			}else{
				//不可恢复
			}
			//2.低压
			if(u8DSG_Lbatflag == 2){
				u8BatLowSDflag = 2;
				
			}else if(u8DSG_Lbatflag == 1){
				if(u8BatLowSDflag == 0){
					u8BatLowSDflag = 1;
				}
			}
			if(u8BatLowSDflag == 2){
				if(u8BatLowSDdelay >= 50){
					u8BatLowSDdelay = 50;

					ucWorkMode = WORKMODE_IDLE;
				}
			}else if(u8BatLowSDflag == 1){
				u8BatLowSDdelay = 0;
			}else{
				u8BatLowSDdelay = 0;
			}
			//3.灰尘感应 in MOT trigger
			//4.MOT fg
			if(u32FGtime <= 60){
				if(u8FGdelay >= 50){
//					u8FGerrorflag = 1;
					
//					if(u8FGdelay >= 100){
//						u8FGdelay = 100;
//						
//						ucshitf = 0;
//						ucWorkMode = WORKMODE_IDLE;
//					}
				}
			}else{
				u8FGdelay = 0;
			}
			break;
		case WORKMODE_CHG://充电===========================================================
			adfun_CHG();
			//PWR_ON;
			if((*(__IO unsigned short int*) DATA_SAVE_ADDR0) == 1){
				if(ucCHGcompleteFlag != 1){
					ucCHGcompleteFlag = 1;
					u16Batfullflag = 1;
				}
			}
			LED_CHG();
			if(ucCHGcompleteFlag == 1){//充电完成-------------------------------------
				u32BatPersent = 10099;
				u16Batfullflag = 1;
				if(ucCHGuplockflag == 0){
					ucCHGuplockflag = 1;
					u8updataflag = 1;
				}
				//补电
				if(AD_V_BAT > BAT_V_24V9){//24.9
					u8ChargeState = 0;
				}else if(AD_V_BAT < BAT_V_24V7){	//24.7
					if(ucCHGoverIflag == 1){
						u8ChargeState = 0;
					}else{
						u8ChargeState = 1;
					}
				}
				
				if(ucCHGcompleteDelay2 >= 60){
					ucCHGcompleteDelay2 = 60;
				}
			}else{//正在充电---------------------------------------------------------
				if(ucCHGoverIflag == 1){
					u8ChargeState = 0;
				}else{
					if(u16CHG_delay >= 1){
						if(u16CHG_delay >= 0xfff0){
							u16CHG_delay = 0xfff0;
						}
						u8ChargeState = 1;
					}
				}
				if(AD_V_BAT >= BAT_V_25V0){//完成条件2	4.16*6
					if(ucCHGcompleteDelay2 >= 1){
						ucCHGcompleteDelay2 = 1;
						ucCHGcompleteFlag = 1;
					}
				}else if(AD_V_BAT >= BAT_V_24V9){//完成条件1 4.15*6
					if(ucCHGcompleteDelay1 >= 120){
						ucCHGcompleteDelay1 = 120;
						
						ucCHGcompleteFlag = 1;
					}
					ucCHGcompleteDelay2 = 0;
				}else{
					ucCHGcompleteDelay1 = 0;
					ucCHGcompleteDelay2 = 0;
				}				
			}
			
			//输入
			//1.主1关
			if(KeyPWR.flag == 1){
				KeyPWR.flag = 0;
				ucCHGcompleteDelay2 = 0;
			}
			//2.充电器拔出
			if(KeyDCin.flag != 1)
			{
				ucWorkMode = 0;
			}
			break;
		default:
			break;
	}
	
}


