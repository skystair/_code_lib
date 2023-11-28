#include "config.h"

unsigned short int u16dustdelt;
unsigned char u8dustCalcount;
unsigned char u8dustCaldelay;
unsigned char u8dustReCaldelay;

unsigned char u8duststep;
unsigned char u8dustpos;
unsigned char u8dustnum[10];
unsigned char u8dustdelay;
unsigned char u8dustERRdelay;

unsigned short int u16dustsum;
unsigned short int u16dustDAC;

void Dustvalueinit(void);
void DUSTfunc(void);

void Dustvalueinit(void){
	u8dustpos = 0;
	memset(u8dustnum,0,10);
	u8dustdelay = 0;
	u16dustDAC = 3200;
	u8dustCalcount =0;
}

unsigned int testnum;
unsigned short int tmpnum;

void dustcalculate(void){
	if(testnum< u16dustsum){
		testnum = u16dustsum;
	}
	if(u8dustdelay >= 100){
		u8dustdelay = 0;
		
		if(ucWorkMode == 1)
		{
			u16dustsum = 0;
			u8dustnum[u8dustpos++] = EXTIx_Cnt;		//record new
			if(u8dustpos >=10){
				u8dustpos = 0;
			}
			
			for(unsigned char i = 0;i<10;i++){
				u16dustsum += u8dustnum[i];
			}
//			u16dustsum = tmpnum;
			
//			if(u16dustsum >= u8dustnum[u8dustpos]){
//				u16dustsum -= u8dustnum[u8dustpos];

//			}
//			u8dustnum[u8dustpos++] = EXTIx_Cnt;
//			u16dustsum += EXTIx_Cnt;
			
			if(u8dustpos >=10){
				u8dustpos = 0;
			}
			EXTIx_Cnt= 0;
		}
		else{
//			u8duststep = 0;
//			u16dustsum = 0;
//			memset(u8dustnum,0,10);
		}
			
	}
}
unsigned int testtick = 0;
void DUSTfunc(void){
	DAC_ValueSet(DAC_VALUE(u16dustDAC));
	switch(u8duststep){
		case 0://jiaozhun
			if(u8dustCaldelay >= 1){
				u8dustCaldelay = 0;
				testtick++;
				if(adc_result[3] > 1200){
					u16dustdelt = adc_result[3]  - 1200;
					if(u16dustdelt > 1000){
						if(u16dustDAC <3200) u16dustDAC += 100;
					}else{
						u16dustDAC += 10;
					}
					u8dustCalcount = 0;
				}else{
					u16dustdelt = 1200 - adc_result[3] ;
					if(u16dustdelt > 1000){
						if(u16dustDAC >100) u16dustDAC -= 100;
						u8dustCalcount = 0;
					}
					if(u16dustdelt > 200){
						if(u16dustDAC >10) u16dustDAC -= 10;
						u8dustCalcount = 0;
					}
					if(u16dustdelt > 100){
						if(u16dustDAC >1) u16dustDAC -= 2;
						u8dustCalcount = 0;
					}else{
						u8dustCalcount++;
						if(u8dustCalcount>=5){
							u8duststep = 1;
							u16dustsum = 0;
							memset(u8dustnum,0,10);
							u8dustERRdelay = 0;
							u8dustReCaldelay = 0;
						}
						
					}
				}
			}
			if(u8dustERRdelay >=50){
				u8dustERRdelay = 50;
				
			}
			break;
		case 1:
			if(AD_HWDUST > 2000){
				if(u8dustERRdelay >=50){
					u8dustERRdelay = 50;
					u8duststep = 0;
				}
			}else if(AD_HWDUST >1200){
				if(u8dustReCaldelay >= 50){
					u8duststep = 0;
				}
				u8dustERRdelay = 0;
			}else{
				
				if(AD_HWDUST < 1000){
					if(u8dustERRdelay >=50){
						u8dustERRdelay = 0;
						u8duststep = 0;
					}
				}else{
					u8dustERRdelay = 0;
				}
			}
			
			dustcalculate();
			
			break;
		default:break;
	}
	
	
	
	
		
}









