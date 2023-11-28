#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "math.h"
#include <stdlib.h>

#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "User_systick.h"

//bsp
#include "gpiox.h"
#include "timerx.h"
#include "uartx.h"

//device
#include "LCD_Driver.h"
#include "LCD_lib.h"

#include "dcmi_OV9655.h"
#include "SCCB.h"
//#include "DCMI_OV9655_INITTABLE.h"
//func
#include "uart3func.h"

extern unsigned char lineflag;
extern unsigned short int LCDdata[240];

void LCD_set0(void);
void LCD_startData(void);

void valueinit(void);
void BSPinit(void);




#endif