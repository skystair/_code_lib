#include "config.h"

unsigned char u8keyflag;
unsigned char u8keydelay;
unsigned char u8keykeep;


void key_valueinit(void);
void key_func(void);


void key_valueinit(void){
	u8keyflag = 0;
	u8keydelay = 0;
	u8keykeep = 1;
}


void key_func(void){
	if(KEY_STATE == KEY_DOWN){
		if(u8keydelay >= 100){
			u8keydelay = 100;
			if(u8keykeep == 0){
				u8keykeep = 1;
				u8keyflag = 1;
			}
		}
	}else{
		u8keyflag = 0;
		u8keykeep = 0;
		u8keydelay = 0;
	}
}








