#ifndef __CONFIG_H
#define __CONFIG_H

#include "stm32f1xx_hal.h"
#include "boardIO.h"

#include "stdio.h"
#include <stdlib.h> // malloc() free()
#include <math.h>
#include <stdint.h>
#include <stdbool.h>

#include "usbd.h"
#include "usbd_def.h"
#include "usbd_desc.h"
#include "usbd_hid.h"
#include "usbd_core.h"


//bsp===============================


//device===============================

//FUNCTION

//#define TRUE 1
//#define FALSE 0
//typedef enum {FALSE = 0,TRUE = 1} bool;



#define LED_ON	HAL_GPIO_WritePin(TEST_LED_GPIO_Port, TEST_LED_Pin, GPIO_PIN_SET);
#define LED_OFF	HAL_GPIO_WritePin(TEST_LED_GPIO_Port, TEST_LED_Pin, GPIO_PIN_RESET);
#define LED_TO	HAL_GPIO_TogglePin(TEST_LED_GPIO_Port, TEST_LED_Pin);

#define KEY_STATE	HAL_GPIO_ReadPin(TEST_KEY_GPIO_Port,TEST_KEY_Pin)



#endif
