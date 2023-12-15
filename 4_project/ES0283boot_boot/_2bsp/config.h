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
#include "timerx.h"
#include "uartx.h"
#include "flashx.h"

//#include "uartxMS.h"
#include "uartxBAT.h"
//#include "uartxBRUSH.h"
#include "bat.h"
#include "jump.h"


#define VERSION		1





extern void valueinit(void);
extern void bspinit(void);


#endif
 
