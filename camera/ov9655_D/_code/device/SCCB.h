/*********************************************************************************************************
*
* File                : 24c02.h
* Hardware Environment: 
* Build Environment   : RealView MDK-ARM  Version: 4.20
* Version             : V1.0
* By                  : 
*
*                                  (c) Copyright 2005-2011, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SCCB_H
#define __SCCB_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
					  
/* Private define ------------------------------------------------------------*/
#define I2C_PAGESIZE	4



/* Maximum Timeout values for flags and events waiting loops. These timeouts are
   not based on accurate values, they just guarantee that the application will 
   not remain stuck if the I2C communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */   
#define SCCB_Open207_FLAG_TIMEOUT         10000
#define OV9655_DEVICE_WRITE_ADDRESS    0x60
#define OV9655_DEVICE_READ_ADDRESS     0x61


#define SCCB_SPEED               100000
#define SCCB_SLAVE_ADDRESS7      0xFE

/* Private function prototypes -----------------------------------------------*/
uint8_t DCMI_SingleRandomWrite(uint8_t Device, uint16_t Addr, uint8_t Data);
uint8_t DCMI_SingleRandomRead(uint8_t Device, uint16_t Addr,uint8_t *Data);

#endif 

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
