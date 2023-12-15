#include "config.h"

//timbase	AD16C4T1
unsigned char u8time1ms;
unsigned char u8time100ms;
unsigned int u32time1s;


void timxvalueinit(void);
void timxinit(void);
void timbaseinit(void);
void timebaseinit(TIMER_TypeDef *timx,uint32_t u8prescaler,uint32_t u16period);
void PWMxinit(TIMER_TypeDef *timx,uint16_t channel,unsigned char Nsate);
void CAPinit(void);

void timxinit(void){
	//	timbaseinit();	//--------------------------------tick 1ms	T5
	timebaseinit(AD16C4T1, (24-1) ,(1000-1));
	md_timer_enable_it_upd(AD16C4T1);
	NVIC_EnableIRQ((IRQn_Type) AD16C4T1_IRQn);
	
//	md_timer_set_master_trgout_select_mmsel(AD16C4T1, MD_TIMER_MASTERMODE_ENABLE);
//	md_timer_set_master_trgout_select_mmsel(AD16C4T1, MD_TIMER_MASTERMODE_UPDATE);
	md_timer_enable_counter_cnten(AD16C4T1);
}

void timxvalueinit(void){
	u8time1ms = 0;
	u8time100ms = 0;
	u32time1s = 0;
}

void timebaseinit(TIMER_TypeDef *timx,uint32_t u8prescaler,uint32_t u16period){
	WRITE_REG(timx->PRES, u8prescaler);
	WRITE_REG(timx->AR, u16period);
}


void tick1ms(void){//----------------------------------

}
void tick100ms(void){//----------------------------------

}

unsigned char testflag;
void tick1s(void){//----------------------------------
	if(testflag == 0){
		testflag = 1;
		TEST_H;
	}else{
		testflag = 0;
		TEST_L;
	}
	
//	Mode_tick1s();
}



void AD16C4T1_IRQHandler(void){
	
	//	//1ms--------------------------------------------
	//in
	tick1ms();
	u8time1ms++;		
	if(u8time1ms >= 100){
		u8time1ms = 0;
		//100ms----------------------------------------			
		tick100ms();
		u8time100ms++;
		
		if(u8time100ms >= 10){
			u8time100ms = 0;
			//1S--------------------------------------
			tick1s();
			u32time1s++;
		}
	}
	md_timer_clear_it_upd(AD16C4T1);
}


