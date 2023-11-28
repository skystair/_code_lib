#ifndef __ADCX_H__
#define __ADCX_H__

#define ADCNUM	10







extern unsigned char u8HeatIshortflag;

extern unsigned short int adc_average[ADCNUM];
extern unsigned short int adc_result[ADCNUM];
extern void ADCxValueInit(void);
extern void ADCxInit(void);
#endif
