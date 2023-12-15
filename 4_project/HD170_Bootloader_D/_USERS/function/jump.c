#include "config.h"

uint32_t jumpAddress;
pFunction Jump_To_App;


void JumpFunc(void);




void JumpFunc(void){
	
	jumpAddress = *(__IO uint32_t *)(APP_ADDRESS + 4);

	
	Jump_To_App = (pFunction)jumpAddress;
	// 设置主堆栈地址为APP程序堆栈地址
	__set_MSP(*(__IO uint32_t *)APP_ADDRESS);
	// APP中断向量表复位异常处理
	Jump_To_App();
}
