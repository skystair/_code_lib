//#include "config.h"
#include "LEDlib.h" 

LEDstruct LEDstructx[LED_NUM];
LEDbreathstruct	LEDbreatX;

void LED_ValueInit(void);
void LED_DelayADD(void);
void LED_ON(unsigned char ucLEDnumb);
void LED_OFF(unsigned char ucLEDnumb);
void LED_flash(unsigned char ucLEDnumb,unsigned short int u16flashdelay);
void LED_Breath(void);
void LED_Func(void);



void LED_ValueInit(void){
	memset(&LEDstructx,0,(LED_NUM * LED_STRUCT_SIZE));
	
}
void LED_DelayADD(void){
	unsigned char i;
	for(i = 0;i< LED_NUM;i++){
		LEDstructx[i].u16Delay++;
	}
}

void LED_ON(unsigned char ucLEDnumb){
	switch(ucLEDnumb)
	{
		case 0:
			LED1_ON();
			break;
		case 1:
			LED2_ON();
			break;
		case 2:
			LED3_ON();
			break;
		case 3:
			LED4_ON();
			break;
		
		default:
			break;
	}
}
void LED_OFF(unsigned char ucLEDnumb){
	switch(ucLEDnumb)
	{
		case 0:
			LED1_OFF();
			break;
		case 1:
			LED2_OFF();
			break;
		case 2:
			LED3_OFF();
			break;
		case 3:
			LED4_OFF();
			break;
		
		default:
			break;
	}
}

void LED_flash(unsigned char ucLEDnumb,unsigned short int u16flashdelay){
	if(LEDstructx[ucLEDnumb].u16Delay <= u16flashdelay)
	{
		LED_ON(ucLEDnumb);
	}
	else if(LEDstructx[ucLEDnumb].u16Delay <= (u16flashdelay *2) )
	{
		LED_OFF(ucLEDnumb);
	}
	else
	{
		LEDstructx[ucLEDnumb].u16Delay = 0;
	}
}

void LED_Breath(void){
	if(LEDbreatX.changedelay >= 1)
	{
		LEDbreatX.changedelay = 0;
		if(LEDbreatX.flag == 0)
			LEDbreatX.u16duty++;
		else
			LEDbreatX.u16duty--;
		
		if(LEDbreatX.u16duty >= LED_BREATH_PERIOD)
			LEDbreatX.flag = 1;
		
		if(LEDbreatX.u16duty <= 0)
			LEDbreatX.flag = 0;
		
		Set_LED_Breath_Duty(LEDbreatX.u16duty);
	}
}

void LED_Func(void)
{
	unsigned char i;
	for( i = 0; i <= LED_NUM ; i++ )
	{
		switch(LEDstructx[i].u8state)
		{
			case LED_STATE_OFF:
				LED_OFF(i);
				break;
			case LED_STATE_ON:
				LED_ON(i);
				break;
			case LED_STATE_FLASH_200MS:
				LED_flash(i,200);
				break;
			case LED_STATE_FLASH_500MS:
				LED_flash(i,500);
				break;
			case LED_STATE_FLASH_1S:
				LED_flash(i,1000);
				break;
			case LED_STATE_Breath:
				if(i == LED_BREATH_NUM){
					//LED_B_PWMEN();
					LED_Breath();
				}
				break;
			default:
				break;
		}
	}
}













