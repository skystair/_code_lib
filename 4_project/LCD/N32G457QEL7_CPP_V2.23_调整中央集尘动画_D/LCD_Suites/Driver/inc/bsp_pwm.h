#ifndef __BSP_PWM_H__
#define __BSP_PWM_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "n32g45x.h"

#define PERIOD_VALUE	120

#define SET_PWM_DUTY_RATIO(percentage) 	TIM_SetCmp1(TIM1, PERIOD_VALUE*percentage)

void TIM_PWM_Intial(void);


#ifdef __cplusplus
}
#endif

#endif



