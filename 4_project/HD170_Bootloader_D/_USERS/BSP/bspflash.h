#ifndef _BSP_FLASH_H
#define _BSP_FLASH_H
#include "config.h"

void Flash_Write32(uint32_t FlashAddr, uint32_t * pDataBuf, uint32_t Len);

void Flash_Pro(void);
void Flash_Earse(void);
#endif
