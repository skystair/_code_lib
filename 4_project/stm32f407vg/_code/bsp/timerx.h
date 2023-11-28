#ifndef __TIMERX_H__
#define __TIMERX_H__


#define TIM1_PERIOD		6000	//20MS

#define TIM2_PERIOD		300		//0.1MS
#define TIM3_PERIOD		3000	//1ms
#define TIM14_PERIOD	6000
#define TIM16_PERIOD	3000
#define TIM17_PERIOD	3000

//100US
#define TIME100US_100US		1
#define TIME100US_1MS   	10
#define TIME100US_10MS		100
#define TIME100US_20MS		200

//1MS
#define TIME1MS				1
#define TIME1MS_5MS			5
#define TIME1MS_10MS		10
#define TIME1MS_20MS		20
#define TIME1MS_50MS		50
#define TIME1MS_80MS		80
#define TIME1MS_100MS		100
#define TIME1MS_200MS		200
#define TIME1MS_300MS		300
#define TIME1MS_400MS		400

#define TIME1MS_1S			1000
//#define TIME1MS_1S5			1500
#define TIME1MS_2S			2000
#define TIME1MS_3S			3000
#define TIME1MS_5S			5000
#define TIME1MS_15S			15000

//10MS
#define TIME10MS_50MS		5
#define TIME10MS_60MS		6
#define TIME10MS_80MS		8
#define TIME10MS_90MS		9
#define TIME10MS_100MS		10
#define TIME10MS_150MS		15
#define TIME10MS_200MS		20
#define TIME10MS_300MS		30
#define TIME10MS_500MS		50
#define TIME10MS_800MS		80
#define TIME10MS_1S			100
#define TIME10MS_2S			200


#define TIME100MS_200MS		2
#define TIME100MS_300MS		3
#define TIME100MS_400MS		4
#define TIME100MS_500MS		5
#define TIME100MS_600MS		6
#define TIME100MS_700MS		7
#define TIME100MS_800MS		8
#define TIME100MS_900MS		9
#define TIME100MS_1S		10
#define TIME100MS_2S		20
#define TIME100MS_3S		30
#define TIME100MS_4S		40
#define TIME100MS_5S		50
#define TIME100MS_1S5		15


#define TIME1S_2S			2
#define TIME1S_3S			3
#define TIME1S_5S			5
#define TIME1S_9S			9
#define TIME1S_10S			10
#define TIME1S_11S			11
#define TIME1S_15S			15
#define TIME1S_20S			20
#define TIME1S_30S			30
#define TIME1S_40S			40
#define TIME1S_60S			60
#define TIME1S_180S			180
#define TIME1S_298S			298
#define TIME1S_299S			299
#define TIME1S_300S			300

#define TIME1S_8H			28800

#define TIME1MIN_2MIN		2
#define TIME1MIN_10MIN		10
#define TIME1MIN_60MIN		60
#define TIME1MIN_240MIN		240

#define TIME1H_6H			6




extern void timxvalueinit(void);
extern void timxinit(void);

#endif




