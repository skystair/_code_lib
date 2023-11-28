#ifndef _BSP_BKP_H_
#define _BSP_BKP_H_

#ifdef __cplusplus
extern "C" {
#endif
	
#include "n32g45x.h"




void BspBkpInit(void);
void BspBkpRead(unsigned char* buffer, unsigned int address, unsigned int numByteToWrite);
void BspBkpWrite(const unsigned char* buffer, unsigned int address, unsigned int numByteToWrite);



#ifdef __cplusplus
}
#endif

#endif /* _BSP_BKP_H_ */
