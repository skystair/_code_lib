#include "config.h"
#include "key.h"

//unsigned short int AD_ADKEY = 4095;
KeyStruct Key[KeyNUM];

void KeyValueInit(void);
void KeyFunc(void);
unsigned short int u16DCindelay2;//拔出延时
unsigned short int u16DCindelay3;//超压延时

void KeyValueInit(void)
{
	for(unsigned char i = 0;i< KeyNUM;i++){
		memset(&Key[i],0,KeyStructSize);
	}
	u16DCindelay2 = 0;
	u16DCindelay3 = 0;
}

void KeyFunc(void)	
{
	Key[0].u16Delay++;
	Key[1].u16Delay++;
	Key[2].u16Delay++;
	Key[3].u16Delay++;
	Key[4].u16Delay++;
	u16DCindelay2++;
//	//1主开关============================
//	if(KEY_PWR_READ == KEY_DOWN)
	if(AD_ADKEY <= AD_KEY_PWR){
		if(Key[0].u16Delay >= 20)
		{
			Key[0].u16Delay = 20;
			if(Key[0].keep != 1)
			{
				Key[0].keep = 1;
				Key[0].flag = PRESS_SHORT;
			}
		}
	}
	else
	{
		Key[0].flag = 0;
		Key[0].keep = 0;
		Key[0].u16Delay = 0;
	}
	
	//2模式开关============================
//	if(KEY_MODE_READ == KEY_DOWN)
	if((AD_ADKEY>AD_KEY_MODL)&&(AD_ADKEY<AD_KEY_MODH)){
			if(Key[1].u16Delay >= 20)
		{
			Key[1].u16Delay = 20;
			if(Key[1].keep != 1)
			{
				Key[1].keep = 1;
				Key[1].flag = PRESS_SHORT;
			}
		}
	}
	else
	{
		Key[1].flag = 0;
		Key[1].keep = 0;
		Key[1].u16Delay = 0;
	}
//3加热开关============================
//	if(KEY_MODE_READ == KEY_DOWN)
	if((AD_ADKEY>AD_KEY_HEATL)&&(AD_ADKEY<AD_KEY_HEATH)){
			if(Key[2].u16Delay >= 20)
		{
			Key[2].u16Delay = 20;
			if(Key[2].keep != 1)
			{
				Key[2].keep = 1;
				Key[2].flag = PRESS_SHORT;
			}
		}
	}
	else
	{
		Key[2].flag = 0;
		Key[2].keep = 0;
		Key[2].u16Delay = 0;
	}
	
//4	
	if((AD_ADKEY>AD_KEY_MICROL)&&(AD_ADKEY<AD_KEY_MICROH)){
		if(Key[3].u16Delay >= 20)
		{
			Key[3].u16Delay = 20;
			u8heattime = 0;
			if(Key[3].keep != 1)
			{
				Key[3].keep = 1;
				Key[3].flag = PRESS_SHORT;
			}
		}
	}
	else
	{
		Key[3].flag = 0;
		Key[3].keep = 0;
		Key[3].u16Delay = 0;
	}
//5DC in============================
	if(AD_V_CHGR >= CHG_V_28){//
		if(u16DCindelay3 >= TIME1MS_100MS){
			u16DCindelay3 = TIME1MS_100MS;
			Key[4].flag = 0xff;
		}
		Key[4].u16Delay = 0;
		u16DCindelay2 =0;
	}else if(AD_V_CHGR >= CHG_OVER_NOR){//
		if(Key[4].u16Delay >= TIME1MS_100MS){
			Key[4].u16Delay = TIME1MS_100MS;
			Key[4].flag = 1;
		}
		u16DCindelay2 =0;
		u16DCindelay3 =0;
	}else if(AD_V_CHGR <= CHG_CUT_V){
		if(u16DCindelay2 >= TIME1MS_100MS){
			u16DCindelay2 = TIME1MS_100MS;
			Key[4].flag = 0;
		}
		Key[4].u16Delay = 0;
		u16DCindelay3 =0;
	}
}


	
