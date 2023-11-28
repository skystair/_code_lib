#include "config.h"
#include "MainFunc.h"

unsigned char ucshitf;
unsigned char ucWorkMode;
unsigned char ucPWRdowndelay;

//DSG
unsigned char u8BrushOverISDflag;	//地刷过流执行标志位
unsigned char u8BatLowSDflag;	//低压执行标志位
unsigned char u8BatLowSDdelay;
//CHG
unsigned short int u16CHG_delay;

unsigned char ucCHGcompleteFlag;	//充电完成标志
unsigned char ucCHGcompleteDelay1;	//充电完成延时1，大于24V用
unsigned char ucCHGcompleteDelay2;	//充电完成延时2，大于25.2V用
unsigned char ucCHGledOFFdelay;		//关灯用
unsigned char ucCHGuplockflag;
	
void WorkModeValueInit(void);
void Shutdown(void);

void ModeFunc(void);


void WorkModeValueInit(void){
	ucWorkMode = 0;
	ucshitf = 0;//档位
	ucPWRdowndelay = 0;
//	;
	
	u8BrushOverISDflag = 0;
	u8BatLowSDflag = 0;
	u8BatLowSDdelay = 0;
	
	u16CHG_delay = 0;
	ucCHGcompleteFlag = 0;
	ucCHGcompleteDelay1 = 0;
	ucCHGcompleteDelay2 = 0;
	ucCHGuplockflag = 0;
}
void Shutdown(void){
	;
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
			ucL0flag = 0;
			ucEflag = 0;
		
			u8BrushOverIDelay1 = 0;
			u8BrushOverIDelay2 = 0;
			u8BrushOverISDflag = 0;
			u8BatLowSDflag = 0;
			u8BatLowSDdelay = 0;
		
			u8DSG_batdelay1 = 0;
			u8DSG_batdelay2 = 0;
		
			u16CHG_delay = 0;
			ucCHGcompleteFlag = 0;
			ucCHGcompleteDelay1 = 0;
			ucCHGcompleteDelay2 = 0;
			ucCHGuplockflag = 0;
		//out device
			LED_ValueInit();//息屏
			//关绿光显尘、主电机、加热、充电MOS、地刷
			memset(&ucloadState,0,LOADNUM);
			for(unsigned char i =0;i<LOADpwmNUM;i++){
				memset(&PWMLoad[i],0,PWMstructSize);
			}
			
		//func
			ucshitf = SHIFT_AUTO;//档位
		
			Discharge_Tick_1ms = 0;
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
			if(KeyDCin.flag == 1){
				ucWorkMode = WORKMODE_CHG;
				u8updataflag = 1;
				PWR_OFF;
				//BatCapPre();
//				if(AD_V_BAT > BAT_V_24V5){
//					ucCHGcompleteFlag = 1;
//					//u16Batfullflag = 1;
//				}
			}else if(KeyDCin.flag == 0xff){
				//报警----------------------------
			}
			break;
		case WORKMODE_DSG://放电===========================================================
			Discharge_Tick_1ms++;
			
			if((*(__IO unsigned short int*) DATA_SAVE_ADDR0) != 0xffff){
				u16Batfullflag = 0xffff;
			}
			
			ucPWRdowndelay = 0;
		//out-------------------------------------------------------
				//load------------------------
			//u8heatState = 1;	//只跟加热按键，不跟档位
			u8LedGState = 1;	//常开
			BrushStruct.ucState = 1;//非保护常开
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
				//dsp------------------------
			//led.c
			
			
		//in-----------------------------------------------------------
			//1.主1关
			if(KeyPWR.flag == 1){
				KeyPWR.flag = 0;
				
				ucshitf = 0;
				ucWorkMode = WORKMODE_IDLE;
//				uartDisable1();
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
			//3.加热------------------------------------
			if(KeyHEAT.flag == 1){
				KeyHEAT.flag = 0;
				
				if(u8heatState == 1){
					u8heatState = 0;
				}else{
					u8heatState = 1;
				}
			}
			//4.DCin------------------------------------
			if(KeyDCin.flag){
				ucWorkMode = WORKMODE_IDLE;
//				uartDisable1();
			}
		//保护---------------------------------------------------------
			//1.地刷堵转
			if(u8BrushOverIflag != 0){
				if(u8BrushOverISDflag == 0){
					
				}
				u8BrushOverISDflag = 1;
			}else{
				//不可恢复
			}
			if(u8BrushOverISDflag != 0){
				BrushStruct.ucState = 0;
				ucEflag = 1;
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
				//关所有负载
				memset(&ucloadState,0,LOADNUM);
				for(unsigned char i =0;i<LOADpwmNUM;i++){
					memset(&PWMLoad[i],0,PWMstructSize);
				}
				//显示L0
				ucL0flag = 1;
				if(u8BatLowSDdelay >= 50){
					u8BatLowSDdelay = 50;
					
					ucshitf = 0;
					ucWorkMode = WORKMODE_IDLE;
					
				}
			}else if(u8BatLowSDflag == 1){
				ucL0flag = 1;
				
				u8BatLowSDdelay = 0;
			}else{
				u8BatLowSDdelay = 0;
			}
			//3.灰尘感应 in MOT trigger
			
			break;
		case WORKMODE_CHG://充电===========================================================
			//PWR_ON;
		
			if((*(__IO unsigned short int*) DATA_SAVE_ADDR0) == 1){
				if(ucCHGcompleteFlag != 1){
					ucCHGcompleteFlag = 1;
					u16Batfullflag = 1;
				}
			}
			
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
					u8ChargeState = 1;
				}
				
				if(ucCHGcompleteDelay2 >= 60){
					ucCHGcompleteDelay2 = 60;
				}
			}else{//正在充电---------------------------------------------------------
				ucCHGledOFFdelay = 0;
				if(u16CHG_delay >= 1){
					if(u16CHG_delay >= 0xfff0){
						u16CHG_delay = 0xfff0;
					}
					u8ChargeState = 1;
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
				
				//显示
//				ucLED_num1 = num2data(u32BatPersent/100/100);
//				ucLED_num2 = num2data(u32BatPersent/100/10%10);
//				ucLED_num3 = num2data(u32BatPersent/100%10);
//				if(ucLED_num3 >0){
//					ucLED_numP = 1;
//				}
				
			}
			
			//输入
			//1.主1关
			if(KeyPWR.flag == 1){
				KeyPWR.flag = 0;
				ucCHGledOFFdelay = 0;
				ucCHGcompleteDelay2 = 0;
			}
			//2.充电器拔出
			if(KeyDCin.flag == 0)
			{
				ucWorkMode = 0;
			}
		
		
			break;
		default:
			break;
	}
	
}


