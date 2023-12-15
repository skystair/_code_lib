#ifndef __CONFIG_H__
#define __CONFIG_H__

#define APPLICATION_ADDRESS     ((uint32_t)0x00008000U)

#define HD170	0

//#define HD196	0

#ifdef HD170
	#define MAX_ADDR 0x1ffff
#else
	#define MAX_ADDR 0x3ffff
#endif

#include "definition.h"
//HD
#include "gpio.h"
#include "timer3.h"
#include "uart.h"
#include "flash.h"
#include "wdt.h"

//BSP
#include "timer.h"
#include "uartx.h"

//DEVICE

//function
#include "mainuart.h"
#include "bspflash.h"

#include "jump.h"
#include "MainFunc.h"


#define LED_USER_ON()	Gpio_SetIO(STK_LED_PORT, STK_LED_PIN)
#define LED_USER_OFF()	Gpio_ClrIO(STK_LED_PORT, STK_LED_PIN)
#define LED_USER_TO()	ToggleIO(STK_LED_PORT, STK_LED_PIN)

extern uint32_t u32Addr;

extern unsigned char Startdownloadflag;
extern unsigned int StartdownloadDelay;


extern void GPIO_init(void);
extern void GPIO_Deinit(void);

extern void SysClkInit(void);

extern void CLK_EN(void);
extern void CLK_DisableAll(void);

extern void Interrupt_EN(void);
extern void Interrupt_DisEN(void);

#endif
