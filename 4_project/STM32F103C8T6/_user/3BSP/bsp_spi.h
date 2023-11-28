#ifndef __BSP_SPI_H
#define __BSP_SPI_H

#include "stm32f1xx_hal_spi.h"
 










extern SPI_HandleTypeDef	hspi1;
extern SPI_HandleTypeDef	hspi2;

extern void MX_SPI1_Init(void);
extern void MX_SPI2_Init(void);


#endif
