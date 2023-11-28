#include "config.h"

//pwm1 GP16C4T2_CH1
//pwm2 GP16C2T2_CH1

//timbase	AD16C4T1

//private------------------------------
unsigned char u8time1ms;
unsigned char u8time100ms;
unsigned int u32time1s;

unsigned char ccnumber;
unsigned short int count;
unsigned short int readvalue1, readvalue2;

//public ------------------------------
unsigned int u32Runtime;

unsigned int u32FGtick;
unsigned int u32FGtime;
unsigned char u8FGerrorflag;

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
	
	//-------------------------------------------------tick 0.1ms	T2
	timebaseinit(GP16C4T1, (24-1) ,(100-1));
	md_timer_enable_it_upd(GP16C4T1);
//	md_timer_set_master_trgout_select_mmsel(GP16C4T1, MD_TIMER_MASTERMODE_ENABLE);
	md_timer_set_master_trgout_select_mmsel(GP16C4T1, MD_TIMER_MASTERMODE_UPDATE);
	md_timer_enable_counter_cnten(GP16C4T1);
	
	//add by zhourx
	NVIC_SetPriority((IRQn_Type) GP16C4T1_IRQn, 0);
	NVIC_EnableIRQ((IRQn_Type) GP16C4T1_IRQn);
	//add by zhourx
	
	//-------------------------------------------------pwm GP16C2T2_CH1 12KHz brush
	timebaseinit(GP16C4T2, (2-1) ,(1000-1));
	
	md_timer_set_output_compare1_mode_ch1mod(GP16C4T2, MD_TIMER_OUTPUTMODE_PWMMODE1);
	md_timer_set_cc1_output_polarity_cc1pol(GP16C4T2, MD_TIMER_OUTPUTPOLARITY_HIGH);
	md_timer_set_capture_compare1_value_ccrv1(GP16C4T2, 0);
	md_timer_enable_cc1_output_cc1en(GP16C4T2);
	
	md_timer_enable_main_output_goen(GP16C4T2);
	md_timer_enable_counter_cnten(GP16C4T2);
	
	//-------------------------------------------------pwm GP16C4T2_CH1 24KHz	DAC
	timebaseinit(GP16C2T2, (1-1) ,(1000-1));
	md_timer_set_output_compare1_mode_ch1mod(GP16C2T2, MD_TIMER_OUTPUTMODE_PWMMODE1);
	md_timer_set_cc1_output_polarity_cc1pol(GP16C2T2, MD_TIMER_OUTPUTPOLARITY_HIGH);
	md_timer_set_capture_compare1_value_ccrv1(GP16C2T2, 0);
	
	md_timer_enable_cc1_output_cc1en(GP16C2T2);
	md_timer_enable_main_output_goen(GP16C2T2);
	md_timer_enable_counter_cnten(GP16C2T2);

}

void timxvalueinit(void){
	u8time1ms = 0;
	u8time100ms = 0;
	u32time1s = 0;
	
	ccnumber = 0;
	count = 0;
	readvalue1 = 0;
	readvalue2 = 0;
	
	u32FGtick = 0;
	u32FGtime = 0;
	u8FGerrorflag = 0;
	
	u32Runtime = 0;
}

void timebaseinit(TIMER_TypeDef *timx,uint32_t u8prescaler,uint32_t u16period){
	WRITE_REG(timx->PRES, u8prescaler);
	WRITE_REG(timx->AR, u16period);
}


void tick1ms(void){//----------------------------------
	//bsp-----------
//	uartTick();
	//device---------
//	DustdelayADD();
	KeydelayADD();
//	Brush_tick1ms();
//	//func----------
//	Mode_tick1ms();
	
}
void tick100ms(void){//----------------------------------
	//trig
	//uart
//	u8U0TxDelay++;
}


void tick1s(void){//----------------------------------
	
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


