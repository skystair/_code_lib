#include "config.h"



int main(void){
	bspinit();
	LCDvalueinit();
	FlashAccessValueinit();
	
	BspIwdogInit();//必须在RTC启动后，RTC启动在draw模块构造函数内
	
	if(!BspIsIwdogReset())
	{//²»ÊÇÓÉ¿´ÃÅ¹·ÒýÆðµÄ¸´Î» ³õÊ¼»¯Êý¾Ý
		//draw->Init();
	}
	else
	{
		//draw->ReloadPage();
	}
	LCDreset();
	
	u8LCDsendingflag = 0;
	while(1)
	{
//		LCD_fresh();
		funcLCD();
		FlashAccessfunc();
		
	}
}
