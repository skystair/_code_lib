#ifndef _BSP_IWDOG_H_
#define _BSP_IWDOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g45x.h"



#define ENABLE_BSP_IWDOG	0


void BspIwdogInit(void);
void BspIwdogReload(void);
int BspIsIwdogReset(void);
	
	
#ifdef __cplusplus
}
#endif

#endif/*_BSP_IWDOG_H_*/
