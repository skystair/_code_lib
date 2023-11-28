#include "config.h"


unsigned char u8time1ms;
unsigned char u8time100ms;
unsigned int u8time1s;

void timxvalueinit(void);
void timxinit(void);
void timfastinit(void);
void timbaseinit(void);
void PWM1init(void);//GP16C2T1_CH1 
void PWM2init(void);//GP16C2T2_CH2
void PWM3init(void);

void timxinit(void){
	timfastinit();	//0.1ms	T14
	
	timbaseinit();	//1ms	T13
	PWM1init();		//		T0
//	PWM2init();		//		T15
	PWM3init();		//		T2
//	//CAP			//		T16
}

void timxvalueinit(void){
	u8time1ms = 0;
	u8time100ms = 0;
	u8time1s = 0;
}

void timfastinit(void){
	timer_oc_parameter_struct timer_ocintpara;
    timer_parameter_struct timer_initpara;

    timer_deinit(TIMER14);
	
	/* TIMER0 configuration */
    timer_initpara.prescaler         = (24-1);
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
    timer_initpara.prescaler         = (72-1);
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = (1000-1);
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER13, &timer_initpara);
	
	timer_enable(TIMER13);

	nvic_irq_enable(TIMER13_IRQn, 2U, 0U);
	timer_interrupt_enable(TIMER13, TIMER_INT_UP);
}
 
void PWM1init(void){//PA8 T0CH0 BRUSH af2
	/* TIMER0 configuration: generate PWM signals with different duty cycles:
       TIMER0CLK = SystemCoreClock / 72 = 1MHz */
    timer_oc_parameter_struct timer_ocintpara;
    timer_parameter_struct timer_initpara;

    timer_deinit(TIMER0);

    /* TIMER0 configuration */
    timer_initpara.prescaler         = (7-1);
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = (1000-1);
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER0,&timer_initpara);

     /* CH0 configuration in PWM mode */
    timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
    timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
    timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
    timer_channel_output_config(TIMER0,TIMER_CH_0,&timer_ocintpara);

    timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_0,0);
    timer_channel_output_mode_config(TIMER0,TIMER_CH_0,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER0,TIMER_CH_0,TIMER_OC_SHADOW_DISABLE);

    timer_primary_output_config(TIMER0,ENABLE);
    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER0);
    timer_enable(TIMER0);

}

void PWM2init(void){//PB8 T15CH0 af2
	timer_oc_parameter_struct timer_ocintpara;
    timer_parameter_struct timer_initpara;

    timer_deinit(TIMER15);

    /* TIMER0 configuration */
    timer_initpara.prescaler         = (36-1);
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = (100-1);
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER15,&timer_initpara);

     /* CH0 configuration in PWM mode */
    timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
    timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
    timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
    timer_channel_output_config(TIMER15,TIMER_CH_0,&timer_ocintpara);

    timer_channel_output_pulse_value_config(TIMER15,TIMER_CH_0,0);
    timer_channel_output_mode_config(TIMER15,TIMER_CH_0,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER15,TIMER_CH_0,TIMER_OC_SHADOW_DISABLE);

    timer_primary_output_config(TIMER15,ENABLE);
    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER15);
    timer_enable(TIMER15);
}

void PWM3init(void){//PB4 T2CH0 af1
	timer_oc_parameter_struct timer_ocintpara;
    timer_parameter_struct timer_initpara;

    timer_deinit(TIMER2);

    /* TIMER0 configuration */
    timer_initpara.prescaler         = (7-1);
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = (1000-1);
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER2,&timer_initpara);

     /* CH0 configuration in PWM mode */
    timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
    timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
    timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
    timer_channel_output_config(TIMER2,TIMER_CH_0,&timer_ocintpara);

    timer_channel_output_pulse_value_config(TIMER2,TIMER_CH_0,1000-0);
    timer_channel_output_mode_config(TIMER2,TIMER_CH_0,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER2,TIMER_CH_0,TIMER_OC_SHADOW_DISABLE);

    timer_primary_output_config(TIMER2,ENABLE);
    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER2);
    timer_enable(TIMER2);
}

void TIMER13_IRQHandler(void){
	
	if(timer_flag_get(TIMER13,TIMER_INTF_UPIF)){
		//	//1ms--------------------------------------------
			//in
//		KeyFunc();
//			//handle
//		
//		ModeFunc();
//			//out
//		LED_Func();
		Trigger_control();
		
		DusttickDelay++;
		u8ADCsampletime++;
		
		u8BrushOverIDelay2++;
		
		u8uart3delay++;
		
		u8S32350delay++;
		u8time1ms++;		
		if(u8time1ms >= 100){
			u8time1ms = 0;
			//100ms----------------------------------------			
			u8BrushOverIDelay1++;
			u8DSG_batdelay1++;
			u8DSG_batdelay2++;
			
			u8heatdelay++;
			
			u8NTCdelay1++;
			u8NTCdelay2++;
			u8NTCdelay3++;
			
			u8BatLowSDdelay++;
			u16BatChangeDelay++;
			
			u8time100ms++;
			if(u8time100ms >= 10){
				u8time100ms = 0;
				//1S--------------------------------------
				ucPWRdowndelay++;
				u16CHG_delay++;
				ucCHGledOFFdelay++;
				ucCHGcompleteDelay1++;
				ucCHGcompleteDelay2++;

				
				
				u8flashfuncdelay++;
				
				u8heattime++;
				if(ucCHGcompleteFlag!= 1){
					u8time1s++;
				}
				
				if(u8time1s >= 60){
					//u8time1s = 0;
				//1min------------------------------------
					
				}
			}
		}
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




