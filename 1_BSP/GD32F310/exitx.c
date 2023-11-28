#include "config.h"

//private-----------------------------
unsigned int EXTIx_Cnt;

//public------------------------------
unsigned int u32FGtick;
unsigned int u32FGtime;
unsigned char u8FGdelay;
unsigned char u8FGerrorflag;



void ExitxInit(void);
//PB6: UART1_TX.
//PB7: UART1_RX (Internal weak pull-up).
//PC5: ANIN15.

void ExitxValueInit(void){
	u32FGtick = 0;
	u32FGtime = 0;
	u8FGdelay = 0;
	EXTIx_Cnt = 0;
	u8FGerrorflag = 0;
}


void ExitxInit(void){
    nvic_irq_enable(EXTI4_15_IRQn, 2U, 0U);
    syscfg_exti_line_config(EXTI_SOURCE_GPIOB, EXTI_SOURCE_PIN13);
    exti_interrupt_flag_clear(EXTI_13);
	

    exti_init(EXTI_13, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
}


void EXTI4_15_IRQHandler(void)
{
	//dust-------------------------------------------
    if(RESET != exti_interrupt_flag_get(EXTI_13)){
//		if(ucWorkMode != 1){
//			EXTIx_Cnt = 0;
//		}else{
//			if(EXTIx_Cnt < 255){
//				EXTIx_Cnt++;
//			}
//		}
		EXTIx_Cnt++;
		Dust_EXTI_Irq();
		
		exti_interrupt_flag_clear(EXTI_13);
    }
}


