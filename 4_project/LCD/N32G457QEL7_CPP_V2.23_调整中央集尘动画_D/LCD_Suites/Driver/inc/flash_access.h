#ifndef _FLASH_ACCESS_H_
#define _FLASH_ACCESS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g45x.h"









void FlashAccessRead(unsigned char* buffer, unsigned int address, unsigned int numByteToWrite);
void FlashAccessWrite(const unsigned char* buffer, unsigned int address, unsigned int numByteToWrite);

#ifdef __cplusplus
}
#endif
	
#endif /* _FLASH_ACCESS_H_ */
