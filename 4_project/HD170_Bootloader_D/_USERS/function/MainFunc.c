#include "config.h"

uint32_t u32Addr    = 0x8000;

void flashclear(void);


void flashdownloadLine(void);
void MainFunc(void);


void flashclear(void)
{ 
    for (uint32_t u32Addrtmp = 0x8000; u32Addr < MAX_ADDR; u32Addr+= 256)
    {
        while(Ok != Flash_SectorErase(u32Addr))
		{
			;
		}
    }
}

void flashdownloadLine(void){
	if(GetlineFlag == 1){
		for (unsigned char i = 0; i < RXdataPosition; i++,u32Addr++)
		{
			Flag_Time1ms = 0;
			///< FLASH 字节写、校验
			if (Ok == Flash_WriteByte(u32Addr, RXdata[i]))
			{
				while(*((volatile uint8_t*)u32Addr) != RXdata[i])
				{
					;
				}
			}
		}
		
		GetlineFlag = 0;
		RXdataPosition = 0;
		
		if(LastlineFlag == 1){
			RXposition =0;
			RXheadReadyFlag = 0;
			RXADDRheadReadyFlag = 0;
			LastlineSize = 0;
			LastlineFlag = 0;
			HexEndFlag = 1;
		}
	}
}



void MainFunc(void)
{
	
}


