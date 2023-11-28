#include "config.h"

unsigned char u8time1ms;
unsigned char u8time100ms;
unsigned int u32time1s;

unsigned char ccnumber;
unsigned short int count;
unsigned short int readvalue1, readvalue2;


void timxvalueinit(void);
void timxinit(void);
void timfastinit(void);
void timbaseinit(void);
void timxBaseinit(uint32_t timer_periph,uint8_t u8prescaler,uint16_t u16period);
void PWMxinit(uint32_t timer_periph,uint8_t u8prescaler,uint16_t u16period,uint16_t channel);
void CAPinit(void);

void timxinit(void){
	timfastinit();	//0.1ms	T14
	timbaseinit();	//1ms	T13
	CAPinit();
	//CAP			//		T16
	PWMxinit(TIMER0,7,1000,TIMER_CH_0);		//PA8 T0CH0 BRUSH af2
	PWMxinit(TIMER15,36,100,TIMER_CH_0);	//PB8 T15CH0 af2
	PWMxinit(TIMER2,72,1000,TIMER_CH_0);	//PB4 T2CH0 af1
}

void timxvalueinit(void){
	u8time1ms = 0;
	u8time100ms = 0;
	u32time1s = 0;
	
	ccnumber = 0;
	count = 0;
	readvalue1 = 0;
	readvalue2 = 0;
}
void timfastinit(void){
	timer_oc_parameter_struct timer_ocintpara;
    timer_parameter_struct timer_initpara;

    timer_deinit(TIMER14);
	
	/* TIMER0 configuration */
    timer_initpara.prescaler         = (36-1);
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = (100-1);
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER14,&timer_initpara);

     /* CH0 configuration in PWM mode */
    timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
    timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
    timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
    timer_channel_output_config(TIMER14,TIMER_CH_0,&timer_ocintpara);

    timer_channel_output_pulse_value_config(TIMER14,TIMER_CH_0,50-0);
    timer_channel_output_mode_config(TIMER14,TIMER_CH_0,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER14,TIMER_CH_0,TIMER_OC_SHADOW_DISABLE);

    timer_primary_output_config(TIMER14,ENABLE);
    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER14);
    timer_enable(TIMER14);
	
	
	nvic_irq_enable(TIMER14_IRQn, 3U, 1U);
	timer_interrupt_enable(TIMER14, TIMER_INT_CH0);
}
void timbaseinit(void){// 
	timer_oc_parameter_struct timer_ocintpara;
    timer_parameter_struct timer_initpara;

    timer_deinit(TIMER13);

    /* TIMER0 configuration */
    timer_initpara.prescaler         = (9-1);
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = (80-1);
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER13, &timer_initpara);
	
	timer_enable(TIMER13);

	nvic_irq_enable(TIMER13_IRQn, 2U, 0U);
	timer_interrupt_enable(TIMER13, TIMER_INT_UP);
}
void PWMxinit(uint32_t timer_periph,uint8_t u8prescaler,uint16_t u16period,uint16_t channel){
	timer_oc_parameter_struct timer_ocintpara;
    timer_parameter_struct timer_initpara;

    timer_deinit(timer_periph);

    /* TIMER0 configuration */
    timer_initpara.prescaler         = (u8prescaler-1);
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = (u16period-1);
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(timer_periph,&timer_initpara);

     /* CH0 configuration in PWM mode */
    timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
    timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
    timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
    timer_channel_output_config(timer_periph,channel,&timer_ocintpara);

    timer_channel_output_pulse_value_config(timer_periph,channel,0);
    timer_channel_output_mode_config(timer_periph,channel,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(timer_periph,channel,TIMER_OC_SHADOW_DISABLE);

    timer_primary_output_config(timer_periph,ENABLE);
    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(timer_periph);
    timer_enable(timer_periph);
}

void CAPinit(void){
    timer_ic_parameter_struct timer_icinitpara;
    timer_parameter_struct timer_initpara;

	timer_initpara.prescaler         = (72-1);
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 65535;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER16, &timer_initpara);

    /* TIMER2  configuration */
    /* TIMER2 CH0 input capture configuration */
    timer_icinitpara.icpolarity  = TIMER_IC_POLARITY_RISING;
    timer_icinitpara.icselection = TIMER_IC_SELECTION_DIRECTTI;
    timer_icinitpara.icprescaler = TIMER_IC_PSC_DIV1;
    timer_icinitpara.icfilter    = 0x0;
    timer_input_capture_config(TIMER16, TIMER_CH_0, &timer_icinitpara);

    timer_auto_reload_shadow_enable(TIMER16);
    timer_interrupt_flag_clear(TIMER16, TIMER_INT_CH0);
    timer_interrupt_enable(TIMER16, TIMER_INT_CH0);

    timer_enable(TIMER16);
	
	nvic_priority_group_set(NVIC_PRIGROUP_PRE1_SUB3);
    nvic_irq_enable(TIMER16_IRQn, 1, 1);
}
void tick1ms(void){//----------------------------------
	u8BrushOverIDelay2++;
	
	u8uart3delay++;
	ucCHGoverIdelay++;
	
	u16heatcnt++;
//	u8dustdelay++;
//	u8dustCaldelay++;
}
void tick100ms(void){//----------------------------------
	u8BrushOverIDelay1++;
	u8DSG_batdelay1++;
	u8DSG_batdelay2++;
		
	u8NTCdelay1++;
	u8NTCdelay2++;
	u8NTCdelay3++;
	
	u8BatLowSDdelay++;
	u16BatChangeDelay++;
	
//	u8dustERRdelay++;
	u8FGdelay++;
}
void tick1s(void){//----------------------------------
	ucPWRdowndelay++;
	u16CHG_delay++;
	ucCHGcompleteDelay1++;
	ucCHGcompleteDelay2++;
	
	u8flashfuncdelay++;

	u8heattime++;
	
//	SEGGER_RTT_printf(0,"TIMES %d\r\n",ucPWRdowndelay);
}
unsigned int u32timtick;
void TIMER13_IRQHandler(void){
	
	if(timer_flag_get(TIMER13,TIMER_INTF_UPIF)){
		u32timtick++;
		u8voice01Delay++;
		u16voiceStartDelay++;
		//	//1ms--------------------------------------------
		//in
//		KeyFunc();
//		Trigger_control();
//		
//		tick1ms();
//		u8time1ms++;		
//		if(u8time1ms >= 100){
//			u8time1ms = 0;
//			//100ms----------------------------------------			
//			tick100ms();
//			u8time100ms++;
//			
//			if(u8time100ms >= 10){
//				u8time100ms = 0;
//				//1S--------------------------------------
//				tick1s();
//				u32time1s++;
//			}
//		}
		
		
		timer_interrupt_flag_clear(TIMER13, TIMER_INTF_UPIF);
	}	
}

void TIMER14_IRQHandler(void){
	if(timer_flag_get(TIMER14,TIMER_INTF_UPIF)){
		
		timer_interrupt_flag_clear(TIMER14, TIMER_INTF_UPIF);
	}
	
	if(timer_flag_get(TIMER14,TIMER_INTF_CH0IF)){
		
		timer_interrupt_flag_clear(TIMER14, TIMER_INTF_CH0IF);
	}
	
	if(timer_flag_get(TIMER14,TIMER_INTF_CH0OF)){
		
		timer_interrupt_flag_clear(TIMER14, TIMER_INTF_CH0OF);
	}
}

void TIMER16_IRQHandler(void)
{
    if(SET == timer_interrupt_flag_get(TIMER16, TIMER_INT_FLAG_CH0)) {
        /* clear channel 0 interrupt bit */
        timer_interrupt_flag_clear(TIMER16, TIMER_INT_FLAG_CH0);

        if(0 == ccnumber) {
            /* read channel 0 capture value */
            readvalue1 = timer_channel_capture_value_register_read(TIMER16, TIMER_CH_0);
            ccnumber = 1;
        } else if(1 == ccnumber) {
            /* read channel 0 capture value */
            readvalue2 = timer_channel_capture_value_register_read(TIMER16, TIMER_CH_0);

            if(readvalue2 > readvalue1) {
                u32FGtick = (readvalue2 - readvalue1);
            } else {
                u32FGtick = ((0xFFFF - readvalue1) + readvalue2);
            }
			
			u32FGtime = u32FGtick;
            u32FGtick = 0;
			ccnumber = 0;
        }
    }
}


