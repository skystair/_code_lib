#ifndef _DSP_LED_H_
#define _DSP_LED_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g45x.h"

#define LED_CHANGE_GPIO		1
	
#define LED_GPIO_CLK		(RCC_APB2_PERIPH_GPIOB|RCC_APB2_PERIPH_GPIOA)

#define LED_RED_PORT		GPIOB
#define LED_RED_PIN			GPIO_PIN_1

#if LED_CHANGE_GPIO
#define LED_GREEN_PORT	GPIOA
#define LED_GREEN_PIN		GPIO_PIN_10
	
#else
#define LED_GREEN_PORT	GPIOB
#define LED_GREEN_PIN		GPIO_PIN_2

#endif
	

#define LED_RED_ON			GPIO_SetBits(LED_RED_PORT, LED_RED_PIN)
#define LED_RED_OFF			GPIO_ResetBits(LED_RED_PORT, LED_RED_PIN)
#define LED_GREEN_ON		GPIO_SetBits(LED_GREEN_PORT, LED_GREEN_PIN)
#define LED_GREEN_OFF		GPIO_ResetBits(LED_GREEN_PORT, LED_GREEN_PIN)



void BspLedInit(void);

#ifdef __cplusplus
}
#endif

#endif /* _DSP_LED_H_ */
