#include "config.h"


unsigned int u32flashdata;
unsigned char u8Flashupdataflag;

unsigned char u8LCDyuyan;
unsigned char u8GaohaibaFlag;
unsigned char u8IAPFlag;

void flashRefresh(void);
void flashvalueinit(void);


void flashvalueinit(void){
	u32flashdata = 0;
	u8Flashupdataflag = 0;
	u8IAPFlag = 0;
	
	if((*(unsigned char *)DATA_YUYAN_ADDR <= 12)){
		u8LCDyuyan = *(unsigned int *)DATA_YUYAN_ADDR;
	}else{
		u8LCDyuyan = 0;
	}
	if((*(unsigned char *)DATA_HAIBA_ADDR <= 1)){
		u8GaohaibaFlag = *(unsigned int *)DATA_HAIBA_ADDR;
	}else{
		u8GaohaibaFlag = 0;
	}
}

void flashRefresh(void){
	u8Flashupdataflag = 1;
}
void flashfunc(void){
	u32flashdata = u8LCDyuyan | (u8GaohaibaFlag <<8) | (u8IAPFlag<<16);
	
	if(u8Flashupdataflag == 1){
		md_rcu_disable_adc(RCU);
		//1.解锁
		md_fc_unlock();
			/* Check the status not lock */
		if (!md_fc_is_active_flag_flash_unlock(FC))
			return;
		//设地址擦除
		md_fc_disable_info_region(FC);
		md_fc_set_program_address(FC, DATA_YUYAN_ADDR);
		md_fc_set_flash_command(FC, MD_FC_CMD_PAGE_ERASE);
		//设地址
		md_fc_set_program_counter(FC, 1);
		md_fc_set_program_address(FC, DATA_YUYAN_ADDR);
		//写入
		md_fc_set_program_data(FC, u32flashdata);
        md_fc_set_flash_command(FC, MD_FC_CMD_PROG_EFLASH);
		
		md_fc_lock();
		md_rcu_enable_adc(RCU);
		u8Flashupdataflag = 0;
	}
	
	if(u8IAPFlag == 1){
		if(*(unsigned char *)DATA_IAP_ADDR == 1){
			__NVIC_SystemReset();
		}
	}
}

