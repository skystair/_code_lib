#include "dustfunc.h"

//private-------------------------------------
//----------------------------------
unsigned char u8duststep;
unsigned char u8dustCalcount;
unsigned char u8dustCaldelay;
unsigned short int u16dustReCaldelay;
unsigned short int u16dustdelt;

unsigned char u8dustdelay;
unsigned short int u16dustERRdelay;

unsigned short int u16dustduty;
//ADC
unsigned char dustsel;
unsigned short int u16tmpHWADmin;


unsigned char u8dustpos;
unsigned char u8EXTIx_Cnt[4];
//public-------------------------------------
//calculate-------------------------
unsigned char u8keli[4][10];
unsigned short int u16kelisum[4];
unsigned int u32kelitotal[4];
unsigned short int u16dustsum;


void Dustvalueinit(void);
void DustdelayADD(void);
void DustADC(void);
void DustEXIT(void);
void DUSTfunc(void);


//======================================================
void Dustvalueinit(void){
	u8duststep = 0;
	u8dustCalcount =0;
	u8dustCaldelay = 0;
	u16dustReCaldelay = 0;
	u16dustdelt = 0;
	
	u8dustdelay = 0;
	u16dustERRdelay = 0;
	u16dustduty = DustInitDuty;
	
	dustsel = 0;
	u16tmpHWADmin = 0;
	
	u8dustpos = 0;
	memset(&u8EXTIx_Cnt,0,4);
	memset(&u8keli,0,4*10);
	memset(&u16kelisum,0,2*4);
	memset(&u32kelitotal,0,4*4);
}

void DustdelayADD(void){
	u8dustdelay++;
	u16dustERRdelay++;
	
	u8dustCaldelay++;
	u16dustReCaldelay++;
}
void DustADC(void){
	if(u16tmpHWADmin > DUST_PHOTOad){
		u16tmpHWADmin = DUST_PHOTOad;
		
		if(u16tmpHWADmin < DustAD_LV4){
			dustsel = 4;
		}else if(u16tmpHWADmin < DustAD_LV3){
			dustsel = 3;
		}else if(u16tmpHWADmin < DustAD_LV2){
			dustsel = 2;
		}else{
			dustsel = 1;
		}
	}
}
void DustEXIT(void){
	if(u8duststep == 1){
		if(dustsel == 4){
			u8EXTIx_Cnt[3] +=3;
			//EXTIx_Cnt3 += 3;
			//EXTIx_Cnt2 += 3;
			//EXTIx_Cnt1 += 3;
		}else if(dustsel == 3){
			u8EXTIx_Cnt[2] += 3;
			//EXTIx_Cnt2 += 3;
			//EXTIx_Cnt1 += 3;
		}else if(dustsel == 2){
			u8EXTIx_Cnt[1] += 3;
			//EXTIx_Cnt1 += 3;
		}else{
			u8EXTIx_Cnt[0] += 3;
		}
	}
	
	u16tmpHWADmin = 0xffff;
}

void dustcalculate(void){
	unsigned char i;
	if(u8dustdelay >= 100){
		u8dustdelay = 0;
		u16dustsum = 0;
		memset(&u16kelisum,0,4*2);
		
		u8keli[0][u8dustpos] = u8EXTIx_Cnt[0];
		u8keli[1][u8dustpos] = u8EXTIx_Cnt[1];
		u8keli[2][u8dustpos] = u8EXTIx_Cnt[2];
		u8keli[3][u8dustpos] = u8EXTIx_Cnt[3];
		
		u8dustpos++;
		if(u8dustpos >=10){
			u8dustpos = 0;
		}
		
		for(i = 0;i<10;i++){
			u16kelisum[0] += u8keli[0][i];
			u16kelisum[1] += u8keli[1][i];
			u16kelisum[2] += u8keli[2][i];
			u16kelisum[3] += u8keli[3][i];
			u32kelitotal[0] += u8keli[0][i];
			u32kelitotal[1] += u8keli[1][i];
			u32kelitotal[2] += u8keli[2][i];
			u32kelitotal[3] += u8keli[3][i];
		}
		u16dustsum = u16kelisum[0]+u16kelisum[1]+u16kelisum[2]+u16kelisum[3];
		memset(&u8EXTIx_Cnt,0,4);
	}
}

unsigned int testValue = DUST_BASE_AD;
void DUSTfunc(void){
	testValue = DUST_BASE_AD;
	DUST_IR_DUTY_Set(u16dustduty);
	switch(u8duststep){
		case 0://jiaozhun
			if(u8dustCaldelay >= 1){
				u8dustCaldelay = 0;
//				testtick++;
				if(DUST_PHOTOad > DUST_BASE_AD){
					u16dustdelt = DUST_PHOTOad  - DUST_BASE_AD;
					if(u16dustdelt > DustAD_DELT1){
						if(u16dustduty > DustDutyADD1) u16dustduty -= DustDutyADD1;
						u8dustCalcount = 0;
					}else if(u16dustdelt > DustAD_DELT2){
						if(u16dustduty > DustDutyADD2) u16dustduty -= DustDutyADD2;
						u8dustCalcount = 0;
					}else if(u16dustdelt > DustAD_DELT3){
						if(u16dustduty > DUST_VALUE_MIN) u16dustduty--;
						u8dustCalcount = 0;
					}else{
						u8dustCalcount++;
						if(u8dustCalcount >= 5){
							u8duststep = 1;
							u16dustsum = 0;
							memset(&u8keli,0,4*10);
							u16dustERRdelay = 0;
							u16dustReCaldelay = 0;
						}
					}
					
				}else{
					u16dustdelt = DUST_BASE_AD - DUST_PHOTOad;
					if(u16dustdelt > DustAD_DELT1){
						if(u16dustduty < (DUST_VALUE_MAX - DustDutyADD1)) u16dustduty += DustDutyADD1;
						u8dustCalcount = 0;
						
					}else{
						u16dustduty += DustDutyADD2;
						u8dustCalcount = 0;
					}
				}
			}
			if(u16dustERRdelay >= DUST_ERR_TIM){
				u16dustERRdelay = DUST_ERR_TIM;
				
			}
			break;
		case 1:
			if(DUST_PHOTOad >  DUST_ERR_AD1){
				if(u16dustReCaldelay >= DUST_ERR_TIM){
					u8duststep = 0;
				}
				u16dustERRdelay = 0;
			}else{
				if(DUST_PHOTOad < DUST_ERR_AD2){
					if(u16dustERRdelay >=DUST_ERR_TIM){
						u16dustERRdelay = 0;
						u8duststep = 0;
					}
				}else{
					u16dustERRdelay = 0;
				}
			}
			dustcalculate();
			
			break;
		default:break;
	}
}

