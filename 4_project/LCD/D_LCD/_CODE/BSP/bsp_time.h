#ifndef _BSP_TIME_H_
#define _BSP_TIME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g45x.h"


#define PERIOD_VALUE	120

#define SET_PWM_DUTY_RATIO(x) 	TIM_SetCmp1(TIM1, PERIOD_VALUE*(x))







void timerXinit(void);

#ifdef __cplusplus
}
#endif

#endif /* _BSP_TIME_H_ */
