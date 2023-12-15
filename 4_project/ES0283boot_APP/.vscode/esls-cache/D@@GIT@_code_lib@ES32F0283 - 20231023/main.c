#include "config.h"

//unsigned int  TESTduty = 400;
void SetKEY(void);
	
unsigned char testpage;
int main(void)
{
	__disable_irq();
	valueinit();
	bspinit();
	__enable_irq();
	
    while(1) {
//		Brush_Duty_Set(TESTduty);//0~800
//		DAC_ValueSet(TESTduty);//0~400
		
//		LCDpageSet(testpage);
		
		KeyFunc();
		
		
//		BatTxhandle();
//		MotTxfunc();
//		LCDfunc();
//		uartfunc();
//		
//		ModeFunc();
//		
//		DUSTfunc();
    }
}

