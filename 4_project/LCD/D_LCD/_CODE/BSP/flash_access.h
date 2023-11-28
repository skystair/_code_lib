#ifndef _FLASH_ACCESS_H_
#define _FLASH_ACCESS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g45x.h"






extern unsigned char u8Flashstep;
extern unsigned char u8flashcomp;

void FlashAccessValueinit(void);
void FlashAccessfunc(void);
#ifdef __cplusplus
}
#endif
	
#endif /* _FLASH_ACCESS_H_ */
