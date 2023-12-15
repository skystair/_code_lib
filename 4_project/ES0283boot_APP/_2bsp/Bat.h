#ifndef __BAT_H__
#define __BAT_H__

#include "string.h" 
#define batBIT(x)                   ((unsigned int)((unsigned int)0x01U<<(x)))

//故障使能====================================
//#define BATCOM_CHK_EN			//电池通信
#define BATNTC_CHK_EN			//电池ntc
#define BATxin_CHK_EN			//电芯
#define BATDCin_CHK_EN			//适配器

#define BATtmp_CHK_EN			//放电过温
#define BATI_CHK_EN				//放电空载
#define BAT_V_LOW0				//电池没电
#define BAT_V_LOW1				//低电量
#define BAT_CHGI_CHK_EN			//充电电流
#define BAT_CHGT_CHK_EN			//充电时间

//BAT==================================================UI
	//全局-------------------------
#define BAT_ERR_COM			1	//通信异常
#define BAT_ERR_NTC			2	//ntc异常
#define BAT_ERR_BAT			3	//电芯异常
	//充电
#define BAT_ERR_CHG_I		4	//充电过流
#define BAT_ERR_CHG_Tim		5	//充电超时
#define BAT_ERR_DCin		6	//充电电压异常
	//放电
#define BAT_ERR_DSG_T		7	//放电过温
#define BAT_ERR_DSG_0A		8	//放电空载
#define BAT_ERR_DSG_NoV		9	//放电低压2
#define BAT_ERR_DSG_LowV	10	//放电低压1



#define UartBATtxDNUM	(7)
#define UartBATrxDNUM	(12)

#define BatTxStruct_SIZE	1
typedef struct{
	unsigned char u8powerON;
	
}BatTxStruct;

#define BatRxStruct_SIZE	4
typedef struct{
	unsigned char u8Cap;
	unsigned char u8Vpl5;
	unsigned char u8CHGstate;
	unsigned char u8errflag;
}BatRxStruct;

extern unsigned char u8CHGcompleteflag;
extern BatTxStruct BatTxS;
extern BatRxStruct BatRxS;
extern unsigned char u8BatCOMfailflag;
extern unsigned char BaterrFlag;

extern unsigned char u8BATRxDATA[UartBATrxDNUM];
extern unsigned char u8BATTxDATA[UartBATtxDNUM];

void BatValueinit(void);
void BatValueRefresh(void);
void BatSetPWR(unsigned char state);

void u8Bat_IDLE_errCHK(void);
void u8Bat_DSG_errCHK(void);
void u8Bat_CHG_errCHK(void);
#endif
