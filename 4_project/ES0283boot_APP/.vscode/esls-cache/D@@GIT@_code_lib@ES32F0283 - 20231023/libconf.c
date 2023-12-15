#include "config.h"

const unsigned short int KEYshort_DELAY = KEYshortTIM;
#ifdef KEYLONG
		const unsigned short int KEYlong_DELAY = KEYlongTIM;
#endif
//key---------------------------------------------
unsigned char KEYREAD(unsigned char u8KeyCH){

	#ifdef KEYLONG
	#endif
	
	switch(u8KeyCH){
		case 0:
			if(KEY1_READ) return 1; else return 0;
			//break;
		case 1:
			if(KEY2_READ) return 1; else return 0;
			//break;
		case 2:
			if(KEY3_READ) return 1; else return 0;
			//break;
		case 3:
			if(KEY4_READ) return 1; else return 0;
			//break;
		case 4:
			if(KEY5_READ) return 1; else return 0;
			//break;
		case 5:
			if(KEYL_READ) return 1; else return 0;
			//break;
		default:break;
	}
	return 0;
}
//dust----------------------------------------------
//unsigned short int DUSTbaseAD = DustADbase;

//unsigned short int u16DUST_ERR_AD1 = DUST_ERR_AD1;
//unsigned short int u16DUST_ERR_AD2 = DUST_ERR_AD2;

//unsigned short int DustADget(void){
//	return DUST_PHOTOad;
//}

void DUST_IR_DUTY_Set(unsigned short int u16x){
	DAC_Duty_Set(u16x);
}
