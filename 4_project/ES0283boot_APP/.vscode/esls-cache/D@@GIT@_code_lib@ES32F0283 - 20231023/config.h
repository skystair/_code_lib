#ifndef CONFIG_H
#define CONFIG_H

#include <string.h>
#include <stdio.h>
#include "es32f0283.h"

#include "BSP2DEVICE.h"

#include "md_tick.h"
#include "md_rcu.h"
#include "md_syscfg.h"
#include "md_fc.h"

#include "md_gpio.h"
#include "md_dma.h"

#include "md_exti.h"
#include "md_uart.h"
#include "md_timer.h"
#include "md_wwdt.h"
#include "md_adc.h"

//BSP-----------------------
#include "gpiox.h"
#include "exitx.h"
#include "adcx.h"
#include "timerx.h"
//#include "uartx.h"
//#include "uartxMS.h"
//#include "uartxBAT.h"
//#include "uartxBRUSH.h"

#include "key.h"
////#include "keylib.h"
//#include "Mot.h"
//#include "Bat.h"
//#include "LCD.h"

//#include "Brush.h"
//#include "dustfunc.h"
//func--------------------
//#include "MainFunc.h"


#define VERSION		1


//#define UartMStxDNUM	(UartLCDlen)




#define UbrushtxDNUM	(2+4)
#define UbrushrxDNUM	(3+4)




extern void valueinit(void);
extern void bspinit(void);


#endif
 
