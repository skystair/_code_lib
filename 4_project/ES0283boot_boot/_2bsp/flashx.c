#include "config.h"

unsigned int uiADDR;

void flashAPPerase(void);


void flashAPPerase(void){
	//1.解锁
	md_fc_unlock();
		/* Check the status not lock */
	if (!md_fc_is_active_flag_flash_unlock(FC))
		return;
	//设地址擦除
	md_fc_disable_info_region(FC);							//排除信息区
	uiADDR = DATA_APP_ADDR - SECTOR_APP_SIZE;
	for(char i = 0; i <= SECTOR_APP_SIZE ; i++){
		md_fc_set_program_address(FC, uiADDR);
		md_fc_set_flash_command(FC, MD_FC_CMD_SECTOR_ERASE);
		
		uiADDR += SECTOR_SIZE;
	}
	
	
//	//设地址
//	md_fc_set_program_counter(FC, 1);
//	md_fc_set_program_address(FC, DATA_YUYAN_ADDR);
//	//写入
//	md_fc_set_program_data(FC, u32flashdata);
//	md_fc_set_flash_command(FC, MD_FC_CMD_PROG_EFLASH);
	
	md_fc_lock();
}

