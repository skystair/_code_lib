#include "config.h"

void valueinit(void);
void bspinit(void);
void bspCLKInit(void);
void SysCLKinit(void);

void valueinit(void){
//	//BSP
	ADCxvalueinit();
	timxvalueinit();
//	uartxvaluinit();
////	//device
//	Dustvalueinit();
//	KeyValueInit();
//	MotValueinit();
//	LCDvaluinit();
//	BatValueinit();
//	Brush_valueinit();
////	LED_ValueInit();
////	trigger_ValueInit();
////	//func
////	BatCapvalueinit();
//	WorkModeValueInit();
}

void bspinit(void){
	md_rcu_init_typedef	rcustructx;
	rcustructx.Hpre = MD_RCU_HPRE_SYSCLK_DIV_1;
	rcustructx.HS_Clock = (RCU_CON_HRCON | RCU_CON_PLL0ON);
	rcustructx.LS_Clock = 0;
	rcustructx.Mpre = MD_RCU_MPRE_MCO_DIV1;
	rcustructx.Msw = MD_RCU_MSW_MCO_DISABLE;
	rcustructx.Pllclk = MD_RCU_PLLCLK_24M;
	rcustructx.PllSrc = MD_RCU_PLLSRC_HRC;
	rcustructx.Ppre = MD_RCU_PPRE_HCLK_DIV_1;
	rcustructx.Sw = MD_RCU_SW_SYSCLK_PLL0;
	
	md_rcu_pll0_init(RCU, &rcustructx);
	md_rcu_sys_init(RCU, &rcustructx);
	
	bspCLKInit();
	
    GpioxInit();
	ExitxInit();
	ADCxinit();
//    uartxinit();
////  
	timxinit();
}

void bspCLKInit(void)
{
	md_rcu_enable_gpiod(RCU);
    md_rcu_enable_gpioc(RCU);
    md_rcu_enable_gpiob(RCU);
    md_rcu_enable_gpioa(RCU);

    md_rcu_enable_uart1(RCU);
	md_rcu_enable_uart3(RCU);
	md_rcu_enable_uart4(RCU);
    md_rcu_enable_adc(RCU);
	md_rcu_enable_dma1(RCU);
	
	
	md_rcu_enable_ad16c4t1(RCU);
	
	md_rcu_enable_gp16c2t2(RCU);
	md_rcu_enable_gp16c4t1(RCU);
	md_rcu_enable_gp16c4t2(RCU);
}

