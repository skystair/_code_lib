#ifndef _BSP_RTC_H_
#define _BSP_RTC_H_

#ifdef __cplusplus
extern "C" {
#endif
	
#include "n32g45x.h"



int BspRtcInit(void);

uint32_t BspRtcGetTimestamp(void);

void BspRtcSetTimestamp(unsigned char year,unsigned char month, unsigned char day,
												unsigned char hour, unsigned char minute, unsigned char second);

#ifdef __cplusplus
}
#endif

#endif /* _BSP_RTC_H_ */
