/**********************************************************************************
 *
 * @file    ald_conf.h
 * @brief   Enable/Disable the peripheral module.
 *
 * @date    23 Nov 2021
 * @author  AE Team
 * @note
 *          Change Logs:
 *          Date            Author          Notes
 *          23 June 2021    Ginger          the first version
 *
 * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 **********************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ALD_CONF_H__
#define __ALD_CONF_H__


#define ALD_FC
#define ALD_ADC
#define ALD_DMA
//#define ALD_EXTI
#define ALD_GPIO
#define ALD_RCU
#define ALD_TICK
#define ALD_TIMER
#define ALD_UART
//#define ALD_WWDT


//#define ALD_DMA
//#define ALD_AES
//#define ALD_CRC
//#define ALD_CALC
//#define ALD_KBCU
//#define ALD_CSU
//#define ALD_RTC

//#define ALD_SPI
//#define ALD_I2C

//#define ALD_IWDT
//#define ALD_CMP

/* Includes -------------------------------------------------------*/
#include "utils.h"

#ifdef ALD_TICK
    #include "ald_tick.h"
#endif

#ifdef ALD_RCU
    #include "ald_rcu.h"
#endif

#ifdef ALD_FC
    #include "ald_fc.h"
#endif

#ifdef ALD_GPIO
    #include "ald_gpio.h"
#endif

#ifdef ALD_DMA
    #include "ald_dma.h"
#endif

#ifdef ALD_AES
    #include "ald_aes.h"
#endif

#ifdef ALD_CRC
    #include "ald_crc.h"
#endif

#ifdef ALD_CALC
    #include "ald_calc.h"
#endif

#ifdef ALD_KBCU
    #include "ald_kbcu.h"
#endif

#ifdef ALD_CSU
    #include "ald_csu.h"
#endif

#ifdef ALD_RTC
    #include "ald_rtc.h"
#endif


#ifdef ALD_EXTI
    #include "ald_exti.h"
#endif

#ifdef ALD_UART
    #include "ald_uart.h"
#endif

#ifdef ALD_SPI
    #include "ald_spi.h"
#endif

#ifdef ALD_I2C
    #include "ald_i2c.h"
#endif

#ifdef ALD_TIMER
    #include "ald_timer.h"
#endif

#ifdef ALD_WWDT
    #include "ald_wwdt.h"
#endif

#ifdef ALD_IWDT
    #include "ald_iwdt.h"
#endif

#ifdef ALD_ADC
    #include "ald_adc.h"
#endif

#ifdef ALD_IWDT
    #include "ald_iwdt.h"
#endif

#ifdef ALD_CMP
    #include "ald_cmp.h"
#endif

#include "interrupt.h"
#include "stdio.h"
#include "string.h"

#define TICK_INT_PRIORITY 3

#endif
/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/

