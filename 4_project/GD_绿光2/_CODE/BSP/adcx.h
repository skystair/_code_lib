#ifndef __ADCX_H__
#define __ADCX_H__

#define ADCNUM	9










extern unsigned char u8ADCsampletime;
extern unsigned short int adc_average[ADCNUM];
extern unsigned short int adc_result[ADCNUM];
extern void ADCxvalueinit(void);
extern void ADCxinit(void);
extern void ADCxfunc(void);
#endif
