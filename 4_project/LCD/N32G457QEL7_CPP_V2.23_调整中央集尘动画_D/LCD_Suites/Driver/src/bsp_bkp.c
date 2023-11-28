#include "bsp_bkp.h"



void BspBkpInit(void)
{
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_BKP, ENABLE);
	PWR_BackupAccessEnable(ENABLE);
}

void BspBkpRead(unsigned char* buffer, unsigned int address, unsigned int numByteToWrite)
{
	uint16_t bkpAddress;
	uint16_t* dataBuffer = (uint16_t*)buffer;
	if(address < 22)
		bkpAddress = BKP_DAT1 + address*4;
	else if(address < 84)
		bkpAddress = BKP_DAT11 + (address-11)*4;
	else
		return;
	for(int i=0; i<numByteToWrite; i++)
	{
		dataBuffer[i] = BKP_ReadBkpData(bkpAddress);
		bkpAddress += 4;
		if(bkpAddress == 0x2C)
			bkpAddress =BKP_DAT11;
		if(bkpAddress > BKP_DAT42)
			return;
	}
}

void BspBkpWrite(const unsigned char* buffer, unsigned int address, unsigned int numByteToWrite)
{
	uint16_t bkpAddress;
	uint16_t* dataBuffer = (uint16_t*)buffer;
	if(address < 22)
		bkpAddress = BKP_DAT1 + address*4;
	else if(address < 84)
		bkpAddress = BKP_DAT11 + (address-11)*4;
	else
		return;
	for(int i=0; i<numByteToWrite; i++)
	{
		BKP_WriteBkpData(bkpAddress, dataBuffer[i]);
		bkpAddress += 4;
		if(bkpAddress == 0x2C)
			bkpAddress =BKP_DAT11;
		if(bkpAddress > BKP_DAT42)
			return;
	}
}

