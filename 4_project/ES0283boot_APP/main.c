#include "config.h"

int main(void)
{
	__disable_irq();
	valueinit();
	bspinit();
	__enable_irq();
	
	
	WRITE_REG(UART1->TXDATA, 0x77);
//	printf("uart1 Tx test\n");
    while(1) {
//		TEST_L;
		UartBATRxchuli();
		flashfunc();
    }
}

