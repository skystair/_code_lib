#include "config.h"

unsigned int u32FGtick;
unsigned int u32FGtime;

void gpioxinit(void);
void EXTI_setting(void);
//PB6: UART1_TX.
//PB7: UART1_RX (Internal weak pull-up).
//PC5: ANIN15.

void gpioxinit(void){
	
//MODfunc AFx-----------------------------------------------
	/* connect port to USARTx_Tx */
    gpio_af_set(PORT_UART0TX, AF_UART0TX, PIN_UART0TX);
	gpio_mode_set(PORT_UART0TX, GPIO_MODE_AF, GPIO_PUPD_PULLUP, PIN_UART0TX);
    gpio_output_options_set(PORT_UART0TX, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, PIN_UART0TX);
	
	gpio_mode_set(PORT_BRUSHPWM, GPIO_MODE_AF, GPIO_PUPD_NONE, PIN_BRUSHPWM);
    gpio_output_options_set(PORT_BRUSHPWM, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,PIN_BRUSHPWM);
    gpio_af_set(PORT_BRUSHPWM, GPIO_AF_2, PIN_BRUSHPWM);
	
	gpio_mode_set(PORT_HWPWM, GPIO_MODE_AF, GPIO_PUPD_NONE, PIN_HWPWM);
    gpio_output_options_set(PORT_HWPWM, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,PIN_HWPWM);
    gpio_af_set(PORT_HWPWM, GPIO_AF_2, PIN_HWPWM);
	
	gpio_mode_set(PORT_MOTPWM, GPIO_MODE_AF, GPIO_PUPD_NONE, PIN_MOTPWM);
    gpio_output_options_set(PORT_MOTPWM, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,PIN_MOTPWM);
    gpio_af_set(PORT_MOTPWM, GPIO_AF_1, PIN_MOTPWM);
	
//MODad AF0-----------------------------------------------
	//ad	ch--------------------------------------------------0---------1-------------2------------3----------5----------6----------7
	gpio_mode_set(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, PIN_ADKEY |PIN_I_HEAT |PIN_HEATNTC |PIN_HWDUST |PIN_V_CHGR |PIN_V_BAT |PIN_I_BRUSH);
	//ad	ch--------------------------------------------------8---------
	gpio_mode_set(GPIOB, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, PIN_L_PHOTO | PIN_R_PHOTO);
//MOD IO af0-----------------------------------------------
	//out
		//1
	gpio_mode_set(PORT_PWRLCK, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_PWRLCK);
    gpio_output_options_set(PORT_PWRLCK, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, PIN_PWRLCK);
		//2
	gpio_mode_set(PORT_CHGON, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_CHGON);
    gpio_output_options_set(PORT_CHGON, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, PIN_CHGON);
		//3
	gpio_mode_set(PORT_HEATON, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_HEATON);
    gpio_output_options_set(PORT_HEATON, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, PIN_HEATON);
		//4
	gpio_mode_set(PORT_MOTEN, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_MOTEN);
    gpio_output_options_set(PORT_MOTEN, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, PIN_MOTEN);
		//5
	gpio_mode_set(PORT_LEDG, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_LEDG);
    gpio_output_options_set(PORT_LEDG, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, PIN_LEDG);
		//6
	gpio_mode_set(PORT_UV, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_UV);
    gpio_output_options_set(PORT_UV, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, PIN_UV);	
		//7
	gpio_mode_set(PORT_L_IR, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_L_IR);
    gpio_output_options_set(PORT_L_IR, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, PIN_L_IR);	
		//8
	gpio_mode_set(PORT_R_IR, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_R_IR);
    gpio_output_options_set(PORT_R_IR, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, PIN_R_IR);
	//in
	gpio_mode_set(PORT_HWEXIT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, PIN_HWEXIT);
	gpio_mode_set(PORT_MOTFG, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, PIN_MOTFG);
	

//exti-------------------------------------------------------
//	EXTI_setting();
	
	EN_MOT_ON;
}


void EXTI_setting(void){
	/* enable and set key EXTI interrupt to the lowest priority */
    nvic_irq_enable(EXTI4_15_IRQn, 2U, 0U);
    /* connect key EXTI line to key GPIO pin */
	syscfg_exti_line_config(EXTI_SOURCE_GPIOB, EXTI_SOURCE_PIN9);
    syscfg_exti_line_config(EXTI_SOURCE_GPIOB, EXTI_SOURCE_PIN13);
    /* configure key EXTI line */
	exti_interrupt_flag_clear(EXTI_9);
    exti_interrupt_flag_clear(EXTI_13);
	
	exti_init(EXTI_9, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
    exti_init(EXTI_13, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
}



unsigned int EXTIx_Cnt = 0;
void EXTI4_15_IRQHandler(void)
{
	if(RESET != exti_interrupt_flag_get(EXTI_9)){
        u32FGtime = u32FGtick;
		u32FGtick = 0;
		exti_interrupt_flag_clear(EXTI_9);
    }
	
    if(RESET != exti_interrupt_flag_get(EXTI_13)){
        
		
		EXTIx_Cnt++;
		Dust_EXTI_Irq();
		
		exti_interrupt_flag_clear(EXTI_13);
    }
}


