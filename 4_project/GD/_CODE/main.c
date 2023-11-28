
#include "config.h"
unsigned short int u16Resetvalue;

int main(void)
{
	#ifdef IWDG_EN
    rcu_osci_on(RCU_IRC40K);
	fwdgt_config(2 * 500, FWDGT_PSC_DIV64);//40KHz(IRC40K) / 64 = 0.625 KHz */
    /* after 1.6 seconds to generate a reset */
    fwdgt_enable();
	#endif
	if(u16Resetvalue != 0x5aa5){
		valueinit();
		u16Resetvalue = 0x5aa5;
	}
    bspinit();
//	__enable_irq();
	PWR_ON;
    while (1)
    {
		#ifdef IWDG_EN
			fwdgt_counter_reload();
		#endif
		
//		uartfunc();
//		Dust_Task();
//		ModeFunc();
//		
//		LED_Func();
//		Trigger_Calculate();
//		flashdatafunc();
		
		VoiceFunc();
    }
}


