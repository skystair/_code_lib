#ifndef __BSP_TIMER_H
#define __BSP_TIMER_H

#define TIME1_DIV	(32 - 1)
#define TIME1_T		(1000 - 1)	// 1000us = 1ms

#define TIME2_DIV	(32 - 1)
#define TIME2_T		(1000 - 1)	// 1000us = 1ms


#define TIME2_DUTY_SET(x)	TIM2->CCR2 = (x);






extern void MX_TIM1_Init(void);
extern void MX_TIM2_Init(void);




#endif
