#ifndef __DUSTFUNC_H
#define __DUSTFUNC_H
#include "string.h"

//AD IN
#define DUST_PHOTOad	777//adc_result[1]
//DAC out
#define DUST_IR_DUTY_Set(x) 	;//DAC_Duty_Set(x)


#define DUST_ERR_TIM	5000					//5S

#define DUST_ERR_AD1	(DUST_BASE_AD + 100)	//5S limit	H
#define DUST_ERR_AD2	100						//5S limit	L


//calibrate Voltage		R2 /(R1+R2) * 4095
#define DustNinR1	1
#define DustNinR2	2
#define DustAD_JZH	45
#define DUST_BASE_AD	((unsigned short int)DustNinR2*4095/(DustNinR1 + DustNinR2) + DustAD_JZH)
//#define HWBASE_VAD	1400//(1365+50)	//
//#define HWBASE_VAD	2756//(2712+45)	//R1 = 5.1K ; R2 = 10K
//#define HWBASE_VAD	2775//(2730+45)	//R1 = 1K ; R2 = 2K


#define DustInitDuty	500

#define DustAD_LV4		2550
#define DustAD_LV3		2650
#define DustAD_LV2		2700

#define DustDutyADD1	50
#define DustDutyADD2	10
#define DustDutyADD3	1

#define DustAD_DELT1	(DustDutyADD1*30)
#define DustAD_DELT2	(DustDutyADD2*30)
#define DustAD_DELT3	30

#define DUST_VALUE_MIN  (0)
#define DUST_VALUE_MAX  (1000)

extern unsigned char u8keli[4][10];
extern unsigned short int u16kelisum[4];
extern unsigned int u32kelitotal[4];
extern unsigned short int u16dustsum;

extern void Dustvalueinit(void);
extern void DustdelayADD(void);
extern void DustADC(void);
extern void DustEXIT(void);
extern void DUSTfunc(void);

#endif



