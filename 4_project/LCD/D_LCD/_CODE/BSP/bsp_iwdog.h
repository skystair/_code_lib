#ifndef _BSP_IWDOG_H_
#define _BSP_IWDOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g45x.h"






void BspIwdogInit(void);
void BspIwdogReload(void);
int BspIsIwdogReset(void);
	
	
#ifdef __cplusplus
}
#endif

#endif/*_BSP_IWDOG_H_*/
