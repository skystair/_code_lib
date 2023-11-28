#ifndef __CONFIG_H__
#define __CONFIG_H__

//bsp Connection
#include "BSP2DEVICE.h"
//lib
#include <stdio.h>
#include <string.h>

#include "gd32f3x0.h"
#include "gd32f3x0_libopt.h"
#include "systick.h"

//BSP---------------------------------------------------------
#include "gpiox.h"
#include "exitx.h"
#include "adcx.h"
#include "uartx.h"
#include "timerx.h"
//#include "bsp_led.h"
//DEVICE-------------------------------------------------------
#include "key.h"
#include "led.h"
#include "trigger.h"
#include "Voice.h"
//#include "dustfunc.h"
#include "Dust.h"
#include "Dust_Analog.h"
#include "Dust_Caculate.h"
//FUNCTION---------------------------------------------------------
#include "MainFunc.h"
#include "adhandle.h"
#include "BatCap.h"
#include "flashdatafunc.h"

//rtt
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"

//*** <<< Use Configuration Wizard in Context Menu >>> ***

//<s.12> ver
#define VERSION  "V2318_2023_6_8_V01"

//<h> function select

//<c1> IWDG_ENABLE

//#define IWDG_EN
//</c>

//</h>

//<h> Protect select

//P4----------------------------------------
//<c> 4.MOT OVER I1
#define MMOT_OVER_I1
//</c>
//P5----------------------------------------
//<c> 5.MOT OVER I2
#define MMOT_OVER_I2
//</c>
//P6----------------------------------------
//<c> 6.MOT LOW I
#define MMOT_LOST_I
//</c>
//P7----------------------------------------
//<c> 7.BAT LOW V
#define BAT_LOW_V_OFF
//</c>
//P11----------------------------------------
//<c> 11.BRUSH OVER I1
#define BRUSH_OVER_I1
//</c>
//P12----------------------------------------
//<c> 12.BRUSH OVER I2
#define BRUSH_OVER_I2
//</c>

//<c> 13.BRUSH old
#define BRUSHOLD
//</c>


//------------------------------------------
//</h>
//*** <<< end of configuration section >>>    ***

extern void valueinit(void);
extern void bspinit(void);

#endif


