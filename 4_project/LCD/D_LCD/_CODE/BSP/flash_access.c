#include "config.h"
unsigned int u8flashtest;
unsigned char u8Flashstep;
unsigned char u8flashcomp;

void FlashAccessValueinit(void);
void FlashAccessfunc(void);


void FlashAccessValueinit(void){
	u8flashtest =0;
	u8Flashstep = 0;
	u8flashcomp = 0;
}
void FlashAccessfunc(void){
	switch(u8Flashstep){
		case 0:
			break;
		case 1:
			u8flashtest = sFLASH_ReadID();
			u8Flashstep = 0;
			break;
		case 2:
			u8flashtest = sFLASH_ReadByte();
			u8Flashstep = 0;
			break;
		case 3://get picture
			u8LCDdipsize = 0xe100;
			sFLASH_ReadBuffer((unsigned char *)&u8LCDbuff,u8LCDpicnum*0x1c200,u8LCDdipsize*2);
		
//			sFLASH_ReadBuffer16((unsigned short int *)&u8LCDbuff,0,u8LCDdipsize);
		
//			memset(u8LCDbuff,0x77,240*240*2);
			u8flashcomp = 1;
			u8Flashstep = 0;
			break;
		default:
			u8Flashstep = 0;
			break;
	}
}