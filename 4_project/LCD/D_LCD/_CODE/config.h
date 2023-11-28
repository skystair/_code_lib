#ifndef __CONFIG_H__
#define __CONFIG_H__

//start
#include <stdio.h>
#include <string.h>

//sys


//lib
#include "n32g45x_conf.h"

//bsp
#include "IOconfig.h"
#include "bsp_gpio.h"
#include "bsp_pvd.h"
#include "bsp_time.h"
#include "bsp_spix.h"
#include "bsp_Dma.h"


#include "bsp_bkp.h"

#include "bsp_iwdog.h"

#include "bsp_rtc.h"

#include "bsp_usart.h"
#include "delay.h"


#include "spi_flash.h"
#include "spi_lcd.h"


//device
#include "lcd_driver.h"
#include "flash_access.h"
#include "image.h"

////func
#include "lcdfunc.h"
#define ENABLE_BSP_IWDOG	0

//extern void bspinit(void);
	#ifdef __cplusplus
		extern "C" {
	#endif
	//extern------------------------------
	void bspinit(void);

	#ifdef __cplusplus
		}
	#endif


#endif

//u16tmpdata[0] = (gImage_3[i+1] << 8) | gImage_3[i];
//				u16tmpdata[1] = (gImage_3[i+2+1] << 8) | gImage_3[i+2];
//				u16tmpdata[2] = (gImage_3[i+240*2+1] << 8) | gImage_3[i+240*2];
//				u16tmpdata[3] = (gImage_3[i+240*2+2+1] << 8) | gImage_3[i+240*2+2];
//				
//				for(unsigned char j = 0; j<4;j++){
//					u16tmpBdata[j] = (u16tmpdata[j] & 0x001f);
//					u16tmpGdata[j] = ((u16tmpdata[j] >> 5) & 0x003f);
//					u16tmpRdata[j] = (u16tmpdata[j] >> 11);
//				}
//				u16tmpBdata[0] = (u16tmpBdata[0]+u16tmpBdata[1]+u16tmpBdata[2]+u16tmpBdata[3])/4;
//				u16tmpGdata[0] = (u16tmpGdata[0]+u16tmpGdata[1]+u16tmpGdata[2]+u16tmpGdata[3])/4;
//				u16tmpRdata[0] = (u16tmpRdata[0]+u16tmpRdata[1]+u16tmpRdata[2]+u16tmpRdata[3])/4;
//				
//				u16tmpdata[0] = u16tmpBdata[0] | (u16tmpGdata[0]<<5) | (u16tmpRdata[0]<<11);
//				
//				lcd_write_data((unsigned char)u16tmpdata[0]);
//				lcd_write_data((unsigned char)(u16tmpdata[0]>>8));