#include "config.c"

#define BIT(x)	(1<<(x))

unsigned int uiIRLogicdelay;
unsigned int uiIRdelay;
unsigned int uiIRLtim;
unsigned char u8IRingflag;

unsigned char ucIRstep;
unsigned char ucIRdatastep;

unsigned char u8IRaddr = 0x5a;
unsigned char u8IRNaddr = 0xa5;

unsigned char u8IRdata;
unsigned char u8IRNdata;
void IRstart(unsigned char ucdata){
	u8IRingflag = 1;
	IRstep = 1;
	
	u8IRdata = ucdata;
	u8IRNdata = ~ucdata;
}

unsigned int IRgetHL(unsigned char ucdata,unsigned char bitx){
	if(ucdata & BIT(bitx) == BIT(bitx)){
		return TIM10us_2250US;
	}else{
		return TIM10us_1120US;
	}
}

void IRrunHL(unsigned int uiT){
	if(uiIRLogicdelay <= TIM10us_560US){
		setIRduty(300);
	}else if(uiIRLogicdelay <= uiT){
		setIRduty(0);
	}else{
		ucIRdatastep++;
		uiIRLogicdelay = 0;
	}
}

void IRfunc(void){
	switch(ucIRstep){
		case 0://idle
		
			break;
		//1.start================================
		case 1://9ms H  4.5ms L
			u8IRingflag = 1;
			if(uiIRLogicdelay < TIM10us_9MS){
				setIRduty(300);//30%
			}else if(uiIRLogicdelay < TIM10us_13MS5){
				setIRduty(0);
			}else{
				IRstep++;
				uiIRLogicdelay = 0;
				ucIRdatastep = 0;
			}
			break;
		//2.ADDR================================
		case 3://ADDR
			if(ucIRdatastep <=7){
				uiIRLtim = IRgetHL(u8IRaddr,ucIRdatastep);
				IRrunHL(uiIRLtim);
			}else{
				IRstep++;
				ucIRdatastep = 0;
			}
			break;
		case 4://NADDR
			if(ucIRdatastep <=7){
				uiIRLtim = IRgetHL(u8IRNaddr,ucIRdatastep);
				IRrunHL(uiIRLtim);
			}else{
				IRstep++;
				ucIRdatastep = 0;
			}
			break;
		case 5://data
			if(ucIRdatastep <=7){
				uiIRLtim = IRgetHL(u8IRdata,ucIRdatastep);
				IRrunHL(uiIRLtim);
			}else{
				IRstep++;
				ucIRdatastep = 0;
			}
			break;
		case 6://Ndata
			if(ucIRdatastep <=7){
				uiIRLtim = IRgetHL(u8IRNdata,ucIRdatastep);
				IRrunHL(uiIRLtim);
			}else{
				IRstep = 0;
				ucIRdatastep = 0;
				
				u8IRingflag = 0;
			}
			break;
		default:break;
	}
	
}