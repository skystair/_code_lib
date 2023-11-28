#include "config.h"

unsigned short int u16FAN_duty;

void Fan_valueinit(void);
void Fan_func(void);


void Fan_valueinit(void){
	u16FAN_duty = 0;
}


void Fan_func(void){
	TIME2_DUTY_SET(u16FAN_duty);
}








