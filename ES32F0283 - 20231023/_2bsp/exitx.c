#include "config.h"

//private-----------------------------

//public------------------------------




void ExitxInit(void);
//PB6: UART1_TX.
//PB7: UART1_RX (Internal weak pull-up).
//PC5: ANIN15.


void ExitxInit(void){
    md_exti_set_interrupt_pin_0_7(EXTI, MD_EXTI_GPIOB1);
	md_exti_enable_it_gpio_pin(EXTI, MD_EXTI_GPIO1);
//	md_exti_enable_rising_edge_trigger(EXTI, MD_EXTI_GPIO9);
	md_exti_enable_falling_edge_trigger(EXTI, MD_EXTI_GPIO1);
	NVIC_EnableIRQ((IRQn_Type) EXTI_0to1_IRQn);
}


__IO uint32_t    EXTI_INTR0to1;
void EXTI_0to1_IRQHandler(void)
{	
//	DustEXIT();
	
    EXTI_INTR0to1 = EXTI->IFM;
    EXTI->ICR = EXTI_INTR0to1;
}
