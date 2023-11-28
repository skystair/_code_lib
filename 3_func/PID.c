#include "config.h"


#define PID_VALUE_MIN	0
#define PID_VALUE_MAX	1000
#define PID_NUM			10
//u(t) = P * [delt(t) + sum(delt)/I + D*daoshu(delt(t))]
	unsigned char u8PIDFirstFlag;
	unsigned char u8PIDdeltPos;
//	float fPID_P,fPID_I,fPID_D;
	unsigned short int u16PID_P, u16PID_I,u16PID_D;			//PID参数
	unsigned short int u16PIDdelt;	
	unsigned short int u16PIDdeltline[PID_NUM];
	unsigned int u32PIDdeltsum;
//	unsigned int u16PIDoutvalue;
	
	
	void PID_vlaueinit(void);
	void PID_adj(void);
	
	void PID_vlaueinit(void){
		u8PIDFirstFlag = 0;
		u8PIDdeltPos = 0;
		u16PID_P = 9;
		u16PID_I = 100;
		u16PID_D = 0;
		
		u16PIDdelt = 0;
		memset(u16PIDdeltline,0,PID_NUM*2);
		u32PIDdeltsum = 0;
		
//		u16PIDoutvalue = 0;
	}
	
void PID_adj(unsigned int *u16PIDoutvalue){
	if(dangqianT >= mubiaoT){
		u16PIDoutvalue = 0;
	}else{
		u16PIDdelt = mubiaoAD - dangqianAD;
		if (u16PIDdelt >= 200 ){   //误差较大则全速输出。
			u16PIDoutvalue =  PID_VALUE_MAX; 
			return;
		}
	}
		if (u8PIDFirstFlag == 0){
			u8PIDFirstFlag = 1;
			for (unsigned char i = 0; i < PID_NUM; i++){         
				u16PIDdeltline[i] = u16PIDdelt;
			}
		}
		
		u16PIDdeltline[u8PIDdeltPos++] = u16PIDdelt;		//record new FIFO队列
		if(u8PIDdeltPos >= 10){
			u8PIDdeltPos = 0;
		}
		u32PIDdeltsum = 0;
		
		for(unsigned char i == 0;i<PID_NUM;i++){
			u32PIDdeltsum += u16PIDdeltline[i];
		}
		
		if(u16PIDdelt > 100){							//1~2高档
			//u16PID_P = u16PID_preP ;
		}else{//0~1低档
			u16PID_P = u16PID_P/2;//预置比例--
		}
		//-------------------P*e(t)----------------------------Se(t)*P/I--------------------------D(e(t))*P----------
		u16PIDoutvalue = u16PID_P*u16PIDdelt + u32PIDdeltsum*u16PID_P/u16PID_I - u16PID_D*u16PIDdelt*u16PID_P;
		if (u16PIDoutvalue > PID_VALUE_MAX){
			u16PIDoutvalue = PID_VALUE_MAX;
		}
	//	return u16PIDoutvalue;
}

