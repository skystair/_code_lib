#include "config.h"

//private-----------------------------

//public------------------------------

void GpioxInit(void);
//PB6: UART1_TX.
//PB7: UART1_RX (Internal weak pull-up).
//PC5: ANIN15.

void GpioxAF(uint32_t gpio_periph, uint32_t alt_func_num, uint32_t pin){
	gpio_af_set(gpio_periph, alt_func_num, pin);
	gpio_mode_set(gpio_periph, GPIO_MODE_AF, GPIO_PUPD_PULLUP, pin);
    gpio_output_options_set(gpio_periph, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, pin);
}
void GpioxOUTpp(uint32_t gpio_periph, uint32_t pin){
	gpio_mode_set(gpio_periph, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, pin);
    gpio_output_options_set(gpio_periph, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, pin);
}


void GpioxInit(void){
	
//MODfunc AFx-----------------------------------------------
	/* connect port to USARTx_Tx */
	GpioxAF(PORT_UART0TX, AF_UART0TX, PIN_UART0TX);
	GpioxAF(PORT_BRUSHPWM, GPIO_AF_2, PIN_BRUSHPWM);
	GpioxAF(PORT_HWPWM, GPIO_AF_2, PIN_HWPWM);
	GpioxAF(PORT_MOTPWM, GPIO_AF_1, PIN_MOTPWM);
	GpioxAF(PORT_MOTFG, GPIO_AF_2, PIN_MOTFG);
//MODad AF0-----------------------------------------------
	//ad	ch--------------------------------------------------0---------1-------------2------------3----------5----------6----------7
	gpio_mode_set(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, PIN_ADKEY |PIN_I_HEAT |PIN_HEATNTC |PIN_HWDUST |PIN_V_CHGR |PIN_V_BAT |PIN_I_BRUSH);
	//ad	ch--------------------------------------------------8---------
	gpio_mode_set(GPIOB, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, PIN_L_PHOTO | PIN_R_PHOTO);
//MOD IO af0-----------------------------------------------
	//out
	GpioxOUTpp(PORT_PWRLCK,PIN_PWRLCK);
	GpioxOUTpp(PORT_CHGON,PIN_CHGON);
	GpioxOUTpp(PORT_HEATON,PIN_HEATON);
	GpioxOUTpp(PORT_MOTEN,PIN_MOTEN);
	GpioxOUTpp(PORT_LEDG,PIN_LEDG);
	GpioxOUTpp(PORT_UV,PIN_UV);
	GpioxOUTpp(PORT_L_IR,PIN_L_IR);
	GpioxOUTpp(PORT_R_IR,PIN_R_IR);
	
	
	GpioxOUTpp(GPIOA, GPIO_PIN_9);
	//in--------------------------------------------------------------------------------
	gpio_mode_set(PORT_HWEXIT, GPIO_MODE_INPUT, GPIO_PUPD_NONE, PIN_HWEXIT);
//exti-------------------------------------------------------
	
	EN_MOT_ON;
}




