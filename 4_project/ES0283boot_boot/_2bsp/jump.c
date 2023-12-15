#include "config.h"

uint32_t jumpAddress;
pFunction Jump_To_App;


void JumpFunc(void);




void JumpFunc(void){
	memcpy((void*)0x20000000,(void*)0x00010000, 48*4);
	
//	MODIFY_REG(SYSCFG->REMAP, SYSCFG_REMAP_MEMMOD, 2 << SYSCFG_REMAP_MEMMOD_POSS);
//	MODIFY_REG(SYSCFG->REMAP, SYSCFG_REMAP_EFBASE, (0 << SYSCFG_REMAP_EFBASE_POSS));
//	SET_BIT(SYSCFG->REMAP, SYSCFG_REMAP_REMAP);
//	NVIC_SystemReset();
	// 设置主堆栈地址为APP程序堆栈地址
	__set_MSP(*(__IO uint32_t *)APP_ADDRESS);
	
	/*程序跳转到 App 的复位向量所指向的位置开始执行 App 程序，
	复位向量所指向的地址存储在 App 程序中断向量表的第二个 word。*/
	jumpAddress = *(__IO uint32_t *)(APP_ADDRESS + 4);
	Jump_To_App = (pFunction)jumpAddress;
	Jump_To_App();
}
