#include "config.h"
#include "LED.h"

unsigned char ucLED_State[LED_NUM];
unsigned char ucEflag;
//unsigned char ucLED_flash_Delay[LED_NUM];


void LED_ValueInit(void);
void LED_numON(void);
void LED_numOFF(void);
void LED_showERR(void);
void LED_IDLE(void);
void LED_DSG(void);
void LED_CHG(void);
void LED_Func(void);
unsigned char num2data(unsigned char num);

void LED_ValueInit(void)
{
	ucEflag = 0;
	memset(&ucLED_State,0,LED_NUM);
}

void LED_numON(void){
	if(u32BatPersent >= 10000){
		ucLED_num1 = 1;
	}else{
		ucLED_num1 = 0;
	}
	if(u32BatPersent >= 1000){
		ucLED_num2 = num2data(u32BatPersent/100/10%10);
	}else{
		ucLED_num2 = 0;
	}
	ucLED_num3 = num2data(u32BatPersent/100%10);
	if(ucLED_num3 > 0){
		ucLED_numP = 1;
	}
}
void LED_numOFF(void){
	ucLED_num1 = 0;
	ucLED_num2 = 0;
	ucLED_num3 = 0;
	ucLED_numP = 0;
}
void LED_showERR(void){
	ucLED_numP = 0;
	ucLED_num1 = 0;
	ucLED_num2 = num2data('E');
	ucLED_num3 = num2data(ucEflag);
}

void LED_IDLE(void){
	//DUST
	ucLED_dustG_duty = 0;
	ucLED_dustR_duty = 0;
	//THUNDER + NUM		
	ucLED_Gthunder_State = 0;
	if(KeyDCin.flag == 0xff){
		ucEflag = 6;
		ucLED_Rthunder_State = LED_STATE_FLASH;
		LED_showERR();
	}else{
		ucLED_Rthunder_State = 0;
		LED_numOFF();
		ucEflag = 0;
	}
	//MAX
	ucLED_MAX_State = 0;
	//HEAT
	ucLED_heat = 0;
}
void LED_DSG(void){
	//error CHK
	if(u8BrushOverISDflag != 0){
		ucEflag = 1;
	}
	if(u8NTCstate == 5){
		ucEflag = 2;
	}
	if(u8HeatIshortflag == 1){
		ucEflag = 3;
	}
	
	if(u8FGerrorflag == 1){
		ucEflag = 4;
	}
	if(u8DSG_Lbatflag != 0){
		ucEflag = 77;
	}
	//DUST
	if (Dust.Num_1s <= DUST_VALUE_MIN)        // 灰尘很少 0
	{
		ucLED_dustG_duty = 100;
		ucLED_dustR_duty = 0;
	}
	else if (Dust.Num_1s <= 100)   // 灰尘适中 1~300
	{
		ucLED_dustR_duty = Dust.Num_1s;
		ucLED_dustG_duty = 100 - ucLED_dustR_duty;
	}
	else		// 灰尘很多 >300
	{
		ucLED_dustR_duty = 100;
		ucLED_dustG_duty = 0;
	}
	//THUNDER
	if(ucEflag != 77){
		ucLED_Gthunder_State = 1;
		ucLED_Rthunder_State = 0;
	}else{
		ucLED_Gthunder_State = 0;
		ucLED_Rthunder_State = LED_STATE_FLASH;
	}
	//MAX
	ucLED_MAX_State = ucshitf/2;
	//HEAT
	if(u8heatcomleteflag == 1){
		ucLED_heat = 3;
	}else{
		ucLED_heat = u8heatstep;
	}
	
	//NUM
	if(ucEflag == 0){
		if(Discharge_Tick_1ms >=100){
			LED_numON();
		}
	}else{
		if(ucEflag == 77){
			ucLED_numP = 0;
			ucLED_num1 = 0;
			ucLED_num2 = num2data('L');
			ucLED_num3 = num2data(0);
		}else{
			LED_showERR();
		}
			
	}
}
void LED_CHG(void){
	if(ucCHGoverIflag == 1){
		ucEflag = 5;
	}
	//DUST
	ucLED_dustG_duty = 0;
	ucLED_dustR_duty = 0;
	//THUNDER + NUM
	if(ucCHGcompleteFlag == 1){
		if(ucCHGcompleteDelay2 >= 15){
			LED_numOFF();
		}else{
			LED_numON();
		}
		ucLED_Gthunder_State = 0;
		ucLED_Rthunder_State = 0;
	}else{
		if(ucEflag == 0){
			LED_numON();
			if(u32BatPersent > 1099){
				ucLED_Gthunder_State = LED_STATE_BREATH;
				ucLED_Rthunder_State = 0;
			}else{
				ucLED_Gthunder_State = 0;
				ucLED_Rthunder_State = LED_STATE_BREATH;
			}
		}else{
			LED_showERR();
			
			ucLED_Gthunder_State = 0;
			ucLED_Rthunder_State = 0;
		}
	}
	//MAX
	ucLED_MAX_State = 0;
	//HEAT
	ucLED_heat = 0;
}

void LED_Func(void)
{
	u8U3txDATA[3] = ucLED_dustG_duty;
	u8U3txDATA[4] = ucLED_dustR_duty;
	u8U3txDATA[5] = (ucLED_num1<<7) + ucLED_num2;
	u8U3txDATA[6] = (ucLED_numP<<7) + ucLED_num3;
	u8U3txDATA[7] = (ucLED_MAX_State <<6) + (ucLED_Rthunder_State<<4) +(ucLED_Gthunder_State<<2) +ucLED_heat;
}

unsigned char num2data(unsigned char num){
	unsigned char data;
	if(num == 0){
		data = 0x3f;
	}else if(num == 1){
		data = 0x06;
	}else if(num == 2){
		data = 0x5b;
	}else if(num == 3){
		data = 0x4f;
	}else if(num == 4){
		data = 0x66;
	}else if(num == 5){
		data = 0x6d;
	}else if(num == 6){
		data = 0x7d;
	}else if(num == 7){
		data = 0x07;
	}else if(num == 8){
		data = 0x7f;
	}else if(num == 9){
		data = 0x6f;
	}else if(num == 'L'){
		data = 0x38;
	}else if(num == 'E'){
		data = 0x79;
	}
	return data;
}






