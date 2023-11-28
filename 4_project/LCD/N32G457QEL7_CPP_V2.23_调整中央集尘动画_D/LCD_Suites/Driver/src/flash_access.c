#include "flash_access.h"
#include "bsp_iwdog.h"

void FlashAccessRead(unsigned char* buffer, unsigned int address, unsigned int numByteToWrite)
{
	unsigned char* sourcePoint = (unsigned char*)address;
	for(int i=0; i<numByteToWrite; i++)
	{
		buffer[i] = sourcePoint[i];
	}
}

void FlashAccessPageWrite(const unsigned char* buffer, unsigned int address, unsigned int numByteToWrite)
{	
	unsigned int count = (numByteToWrite+3) >> 2;//四字节对齐后的字数
	unsigned int* dataPoint = (unsigned int*)buffer;
	BspIwdogReload();
	FLASH_EraseOnePage(address);
	for(int i=0; i<count; i++)
	{
		FLASH_ProgramWord(address, dataPoint[i]);
		address += 4;
	}
}

#define ON_CHIP_FLASH_PAGE_SIZE		2048
void FlashAccessWrite(const unsigned char* buffer, unsigned int address, unsigned int numByteToWrite)
{
	uint8_t NumOfPage = 0, Addr = 0, NumOfSingle = 0, count = 0, temp = 0;
	Addr        = (uint8_t)(address % ON_CHIP_FLASH_PAGE_SIZE);
	count       = (uint8_t)(ON_CHIP_FLASH_PAGE_SIZE - Addr);
	NumOfPage   = (uint8_t)(numByteToWrite / ON_CHIP_FLASH_PAGE_SIZE);
	NumOfSingle = (uint8_t)(numByteToWrite % ON_CHIP_FLASH_PAGE_SIZE);
	
	FLASH_Unlock();
	if (Addr == 0) /*!< WriteAddr is sFLASH_PAGESIZE aligned  */
    {
        if (NumOfPage == 0) /*!< NumByteToWrite < sFLASH_PAGESIZE */
        {
						FlashAccessPageWrite(buffer, address, numByteToWrite);
        }
        else /*!< NumByteToWrite > sFLASH_PAGESIZE */
        {
            while (NumOfPage--)
            {
								FlashAccessPageWrite(buffer, address, ON_CHIP_FLASH_PAGE_SIZE);
                address += ON_CHIP_FLASH_PAGE_SIZE;
                buffer += ON_CHIP_FLASH_PAGE_SIZE;
            }
						FlashAccessPageWrite(buffer, address, NumOfSingle);
        }
    }
    else /*!< WriteAddr is not sFLASH_PAGESIZE aligned  */
    {
        if (NumOfPage == 0) /*!< NumByteToWrite < sFLASH_PAGESIZE */
        {
            if (NumOfSingle > count) /*!< (NumByteToWrite + WriteAddr) > sFLASH_PAGESIZE */
            {
                temp = NumOfSingle - count;
								FlashAccessPageWrite(buffer, address, count);
                address += count;
                buffer += count;
								FlashAccessPageWrite(buffer, address, temp);
            }
            else
            {
								FlashAccessPageWrite(buffer, address, numByteToWrite);
            }
        }
        else /*!< NumByteToWrite > sFLASH_PAGESIZE */
        {
            numByteToWrite -= count;
            NumOfPage   = numByteToWrite / ON_CHIP_FLASH_PAGE_SIZE;
            NumOfSingle = (uint8_t)(numByteToWrite % ON_CHIP_FLASH_PAGE_SIZE);

            FlashAccessPageWrite(buffer, address, count);
            address += count;
            buffer += count;

            while (NumOfPage--)
            {
                FlashAccessPageWrite(buffer, address, ON_CHIP_FLASH_PAGE_SIZE);
                address += ON_CHIP_FLASH_PAGE_SIZE;
                buffer += ON_CHIP_FLASH_PAGE_SIZE;
            }

            if (NumOfSingle != 0)
            {
                 FlashAccessPageWrite(buffer, address, NumOfSingle);
            }
        }
    }
	FLASH_Lock();
}


