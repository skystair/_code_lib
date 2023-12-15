#include "config.h"

unsigned char Startdownloadflag = 0;
unsigned int StartdownloadDelay = 0;



void Valueinit(void){
	Startdownloadflag = 0;
	StartdownloadDelay = 0;
	
	RXposition =0;
	RXheadReadyFlag = 0;
	RXADDRheadReadyFlag = 0;
	LastlineSize = 0;
	LastlineFlag = 0;
	
	u32Addr = 0x8000;
}

int main(void)//8M
{
//	Sysctrl_ClkSourceEnable(SysctrlClkRCH, 1);//Select RCH
//	Sysctrl_SetRCHTrim(SysctrlRchFreq8MHz);//RCH 8MHz

	SysClkInit();	//32M
	CLK_EN();		//GPIO,UART
	
	GPIO_init();	//USER_LED_KEY,UART PA9
	Timer_init();	//1msINT
	Uart_init();	//115200uart
	
	while(Ok != Flash_Init(8, TRUE))
    {
        ;
    }
	
	if ((*(__IO uint8_t *)MAX_ADDR) != 0xff){
		flashclear();
		
		printf("Reset!\r\n");
		__NVIC_SystemReset();
		//while(1);
	}
	Interrupt_EN();
	
	while(1)
	{
		
		//flashdownload();
		flashdownloadLine();
		
		if(HexEndFlag == 1){
			RXposition =0;
			RXheadReadyFlag = 0;
			RXADDRheadReadyFlag = 0;
			LastlineSize = 0;
			LastlineFlag = 0;
		}
		
		//发送完毕或超时跳转
		if (((*(__IO uint32_t *)APPLICATION_ADDRESS) & 0x2FFE0000) == 0x20000000)//首地址
		{
			if(((Startdownloadflag==0)&&(Flag_Time1ms >= 50)) ||(HexEndFlag == 1)){
				Interrupt_DisEN();
				
				Uart_Deinit();
				Timer_Deinit();
				GPIO_Deinit();
				CLK_DisableAll();
				Sysctrl_ClkDeInit();
				
				JumpFunc();				

			}
		}
		
		//接收到数据后10S未完成，擦除
		if(Startdownloadflag == 1){
			if(StartdownloadDelay >= 10000){
				Valueinit();
				
				flashclear();				
			}
		}else{
			StartdownloadDelay = 0;
		}
	}
}
