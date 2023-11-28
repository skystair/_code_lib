#include "config.h"

unsigned char u8LEDflag;

void LED_valueinit(void);
void LED_func(void);


void LED_valueinit(void){
	u8LEDflag = 0;
}


void LED_func(void){
	if(u8LEDflag == 1){
		LED_ON;
	}else{
		LED_OFF;
	}
}








