#include "config.h"

void valueinit(void);
void bspinit(void);
void SysPeriInit(void);
void SysCLKinit(void);


void valueinit(void){
	//BSP
	ADCxvalueinit();
	uartxvaluinit();
	timxvalueinit();
	//device
	KeyValueInit();
	LED_ValueInit();
	trigger_ValueInit();
	//func
	ad_valueInit();
	BatCapvalueinit();
	flashvalueinit();
	WorkModeValueInit();
}

void bspinit(void){
	//SystemInit(); //__SYSTEM_CLOCK_72M_PLL_IRC8M_DIV2
	SysPeriInit();
	systick_config();
	
    gpioxinit();
	IIC_Init();
//	ADCxinit();
    uartxinit();
//    
//	
	timxinit();
}



void SysPeriInit(void)
{
	rcu_periph_clock_enable(RCU_CFGCMP);
	
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_GPIOC);
	rcu_periph_clock_enable(RCU_GPIOF);
	
//	/* ADCCLK = PCLK2/6 */
//    rcu_adc_clock_config(RCU_ADCCK_APB2_DIV6);

    /* enable DMA clock */
    rcu_periph_clock_enable(RCU_DMA);

    /* enable ADC clock */
    rcu_periph_clock_enable(RCU_ADC);

	rcu_periph_clock_enable(RCU_USART0);
//	rcu_periph_clock_enable(RCU_USART1);
	
    /* enable TIMER0 clock */
    rcu_periph_clock_enable(RCU_TIMER0);
	rcu_periph_clock_enable(RCU_TIMER2);
	rcu_periph_clock_enable(RCU_TIMER13);
	rcu_periph_clock_enable(RCU_TIMER14);
	rcu_periph_clock_enable(RCU_TIMER15);
	
	/* config ADC clock */
    rcu_adc_clock_config(RCU_ADCCK_APB2_DIV6);
//	
//	md_rcu_enable_ad16c4t1(RCU);
//	md_rcu_enable_gp16c2t1(RCU);
//	md_rcu_enable_gp16c2t2(RCU);
}



