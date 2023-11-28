#ifndef __CONFIG_H
#define __CONFIG_H

#include "stm32f1xx_hal.h"
#include "boardIO.h"

#include "stdio.h"
#include <stdlib.h> // malloc() free()
#include <math.h>
#include <stdint.h>
#include <stdbool.h>

//bsp===============================
#include "bsp_gpio.h"
#include "bsp_spi.h"
#include "bsp_timer.h"
#include "bsp_uart.h"
#include "IIC.h"

//device===============================
#include "Fan.h"
#include "LED.h"
#include "key.h"
#include "SHT.h"
	//OLED lib--------------------
#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "ImageData.h"
#include "Debug.h"
#include "OLED_1in5_rgb.h"
//#include "test.h"
#include "OLED.h"
	//AD7124 lib--------------------
//#include "AD7124.h"
#include "ad7124_console_app.h"

//FUNCTION

//#define TRUE 1
//#define FALSE 0
//typedef enum {FALSE = 0,TRUE = 1} bool;



#define LED_ON	HAL_GPIO_WritePin(TEST_LED_GPIO_Port, TEST_LED_Pin, GPIO_PIN_SET);
#define LED_OFF	HAL_GPIO_WritePin(TEST_LED_GPIO_Port, TEST_LED_Pin, GPIO_PIN_RESET);
#define LED_TO	HAL_GPIO_TogglePin(TEST_LED_GPIO_Port, TEST_LED_Pin);

#define KEY_STATE	HAL_GPIO_ReadPin(TEST_KEY_GPIO_Port,TEST_KEY_Pin)



extern unsigned int uirundelay;

extern void ValueInit(void);
extern void SystemClock_Config(void);
extern void MX_IWDG_Init(void);

extern void Error_Handler(void);

#endif
