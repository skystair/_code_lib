#include "config.h"
#include "flashdatafunc.h"


unsigned char u8updataflag;
unsigned char u8flashfuncdelay;
unsigned char u8flashW_CapDelay;
unsigned char u8flashC_Capflag;
unsigned short int u16Batfullflag;
unsigned int	u32flashData;


//unsigned int	EFData[32];

void flashvalueinit(void);
void flashdatafunc(void);



void flashvalueinit(void){
	u16Batfullflag = (*(__IO unsigned short int*) DATA_SAVE_ADDR0);
	u8updataflag = 0;
	u8flashfuncdelay = 0;
	u8flashW_CapDelay = 0;
	u8flashC_Capflag = 0;
	u32flashData = 0;
}

void flashdatafunc(void){
	//u32tempData = 0;
	u32flashData = (u32BatPersent << 16) + u16Batfullflag;
	
	if(u8updataflag == 1){
		u8updataflag = 0;
		/* unlock the flash program/erase controller */
		fmc_unlock();
		
		fmc_page_erase(DATA_SAVE_ADDR0);
		fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);
		
		fmc_word_program(DATA_SAVE_ADDR0, u32flashData);
		fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);

		/* lock the main FMC after the program operation */
		fmc_lock();
	}
}
