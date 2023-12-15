//#include "config.h"
#include "Bat.h" 

BatTxStruct BatTxS;
BatRxStruct BatRxS;

unsigned char u8BATRxDATA[UartBATrxDNUM];
unsigned char u8BATTxDATA[UartBATtxDNUM];
//CHG
unsigned char u8CHGcompleteflag;
unsigned char u8BatCOMfailflag;
unsigned char BaterrFlag;

void BatValueinit(void);
void BatValueRefresh(void);
void BatSetPWR(unsigned char state);

void u8Bat_IDLE_errCHK(void);
void u8Bat_DSG_errCHK(void);
void u8Bat_CHG_errCHK(void);

void BatValueinit(void){
	memset(&u8BATRxDATA,0,UartBATrxDNUM);
	memset(&u8BATTxDATA,0,UartBATtxDNUM);
	u8BATTxDATA[0] = 0xac;
	u8BATTxDATA[1] = 0;
	u8BATTxDATA[2] = 2;
	
	BatTxS.u8powerON = 1;
	
	BatRxS.u8Cap = 100;
	BatRxS.u8Vpl5 = 120;
	BatRxS.u8CHGstate = 0;
	BatRxS.u8errflag = 0;
	
	u8CHGcompleteflag = 0;
	u8BatCOMfailflag = 0;
	BaterrFlag = 0;
}
void BatValueRefresh(void){
	if(u8BATRxDATA[3] <= 100){
		BatRxS.u8Cap = u8BATRxDATA[3];
	}
	if(u8BATRxDATA[4] > 0){
		BatRxS.u8Vpl5 = u8BATRxDATA[4];
	}
	if(u8BATRxDATA[5] < 4){
		BatRxS.u8CHGstate = u8BATRxDATA[5];
	}
	BatRxS.u8errflag = u8BATRxDATA[6];
}

void u8Bat_IDLE_errCHK(void){
	BaterrFlag = 0;
	//1.通信
	#ifdef BATCOM_CHK_EN
	if(u8BatCOMfailflag == 1){
		BaterrFlag =  BAT_ERR_COM;
	}
	#endif
	//2.ntc
	#ifdef BATNTC_CHK_EN
	if(BatRxS.u8errflag & (batBIT(0))){
		BaterrFlag =  BAT_ERR_NTC;
	}
	#endif
	//3.电芯
	#ifdef BATxin_CHK_EN
	if(BatRxS.u8errflag & (batBIT(6))){
		BaterrFlag =  BAT_ERR_BAT;
	}
	#endif
	//9.亏电
	#ifdef BAT_V_LOW0
	if(BatRxS.u8Cap <= 0){
		BaterrFlag = BAT_ERR_DSG_NoV;
	}
	#endif
}
void u8Bat_CHG_errCHK(void){
	u8Bat_IDLE_errCHK();
	if(BaterrFlag == BAT_ERR_DSG_NoV){
		BaterrFlag = 0;
	}
	//4充电过流
	#ifdef BAT_CHGI_CHK_EN
	if(BatRxS.u8errflag & (batBIT(3))){
		BaterrFlag =  BAT_ERR_CHG_I;
	}
	#endif
	//5充电超时
	#ifdef BAT_CHGT_CHK_EN
	if(BatRxS.u8errflag & (batBIT(5))){
		BaterrFlag =  BAT_ERR_CHG_Tim;
	}
	#endif
	//6充电器电压
	#ifdef BATDCin_CHK_EN
	if(BatRxS.u8errflag & (batBIT(4))){
		BaterrFlag = BAT_ERR_DCin;
	}
	#endif
}
void u8Bat_DSG_errCHK(void){
	u8Bat_IDLE_errCHK();
	//7.放电过温
	#ifdef BATtmp_CHK_EN
	if(BatRxS.u8errflag & (batBIT(1))){
		BaterrFlag =  BAT_ERR_DSG_T;
	}
	#endif
	//8.放电空载
	#ifdef BATI_CHK_EN
	if(BatRxS.u8errflag & (batBIT(2))){
		BaterrFlag = BAT_ERR_DSG_0A;
	}
	#endif
	if(BaterrFlag == 0){
		//10.低压
		#ifdef BAT_V_LOW1
		if(BatRxS.u8Cap <= 10){
			BaterrFlag = BAT_ERR_DSG_LowV;
		}
		#endif
	}
}

void BatSetPWR(unsigned char state){
	BatTxS.u8powerON = state;
}

