#include "config.h"
#include "BatCap.h"

//放电------------------------------------------------------------------
	//1.根据主电机功率倒计时
	//2.倒计时前判电压是否降低

unsigned char uclock001flag;
unsigned int u32BatPersent;
unsigned int u32tmpBatPersent;
unsigned short int u16BatChangeDelay;
unsigned short int u16CHGcount;


void BatCapvalueinit(void);
void BatCapPre(void);
void BatCapDSG(void);
void BatCapfun(void);

void BatCapvalueinit(void){
	u16BatChangeDelay = 0;
	//u32BatPersent
	u32tmpBatPersent = 0;
	u16CHGcount = 0;
	uclock001flag = 0;
}

void BatCapPre(void){
	if((*(__IO unsigned short int*) DATA_SAVE_ADDR1) > 10099){
		if(AD_V_BAT > BAT_V_17V1){
			u32BatPersent = (AD_V_BAT - BAT_V_17V1)*10000/(BAT_V_25V2 - BAT_V_17V1);
			if(u32BatPersent > 10099){
				u32BatPersent = 10099;
			}
		}else{
//			u32BatPersent = 199;
		}
	}else{
		u32BatPersent = (*(__IO unsigned short int*) DATA_SAVE_ADDR1);
	}
}


void BatCapDSG(void){
	if(AD_V_BAT > BAT_V_18V0){	//>2026
			u32tmpBatPersent = 1477*AD_V_BAT/100 -29885;//29*1453 -41162;//
			if(u32tmpBatPersent >= 10099){
				u32tmpBatPersent = 10099;
			}
			if(u32tmpBatPersent <= 199){
				u32tmpBatPersent = 199;
			}
			if(u32tmpBatPersent < u32BatPersent-100){
				u32BatPersent -= 100;
				u8updataflag = 1;
			}
			uclock001flag = 0;
		}else{
			if(uclock001flag == 0){
				uclock001flag = 1;
				u8updataflag = 1;
			}
			u32tmpBatPersent = 199;
			u32BatPersent = 199;
		}
}

void BatCapfun(void){//计算电量 //1S CHK一次
	
	//flash内无电量，快速估算负载状态电量
	if((Discharge_Tick_1ms >10)&&(Discharge_Tick_1ms <100)){
		BatCapDSG();
	}
	
	//放电0.5S后~关机前3S，每2S更新一次
	if(u16BatChangeDelay >= 20){
		u16BatChangeDelay = 0;
		if(ucWorkMode == WORKMODE_DSG){//17~22.2---------&&(u16DSGtime >= 500)
			BatCapDSG();
		}else if(ucWorkMode == WORKMODE_CHG){
			u16CHGcount++;
			if(u16CHGcount >=180){
				u16CHGcount = 0;
				if(u32BatPersent <9900){
					u32BatPersent += 100;
					
					u8updataflag = 1;
				}else{
					u32BatPersent = 10099;
				}
			}
		}else{
			u16BatChangeDelay = 0;
		}
	}
	
}



