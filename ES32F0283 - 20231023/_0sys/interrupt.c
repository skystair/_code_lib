/**********************************************************************************
 *
 * @file    interrupt.c
 * @brief   Interrupt C file
 *
 * @date    23 Nov 2021
 * @author  AE Team
 * @note
 *          Change Logs:
 *          Date            Author          Notes
 *          23 Nov  2021    Ginger          the first version
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

#define isr_GLOBALS

#include "Interrupt.h"
#include "config.h"

/** @addtogroup Projects_Examples
  * @{
  */

/** @addtogroup INTERRUPT
  * @{
  */

/* Includes -------------------------------------------------------------------*/
/* Public Functions -----------------------------------------------------------*/
/* Public Init Structure ------------------------------------------------------*/
/* Public Macros --------------------------------------------------------------*/
/* Public Constants -----------------------------------------------------------*/
/* Private Variables ----------------------------------------------------------*/
/* Private Macros -------------------------------------------------------------*/
/* Private Constants-----------------------------------------------------------*/
/* Private Functions ----------------------------------------------------------*/

/** @addtogroup Exceptions Handlers
  * @{
  */

/******************************************************************/
/*                Core Processor Exceptions Handlers           */
/******************************************************************/
//unsigned char ADCi = 0;

void NMI_Handler(void)
{
}

void HARDFAULT_Handler(void)
{
    while (1);

}

void SVC_Handler(void)
{
}

void PENDSV_Handler(void)
{
}

void SYSTICK_Handler(void)
{
}

/******************************************************************/
/*              External Processor Exceptions Handlers            */
/******************************************************************/


void USB_IRQHandler(void)           /*  IRQ 31  */
{
    while (1);
}

void SPI2_IRQHandler(void)          /*  IRQ 26 */
{
    while (1);
}

void SPI1_IRQHandler(void)          /*  IRQ 25  */
{
    while (1);
}

void I2C2_IRQHandler(void)          /*  IRQ 24  */
{
    while (1);
}

void I2C1_IRQHandler(void)          /*  IRQ 23  */
{
    while (1);
}

void GP16C2T4_IRQHandler(void)      /*  IRQ 22  */
{
    while (1);
}

void GP16C2T3_IRQHandler(void)      /*  IRQ 21  */
{
    while (1);
}

void GP16C2T2_IRQHandler(void)      /*  IRQ 20  */
{
    while (1);
}

void GP16C2T1_IRQHandler(void)      /*  IRQ 19  */
{
    while (1);
}

void GP16C4T3_IRQHandler(void)      /*  IRQ 18  */
{
    while (1);
}

void GP16C4T2_IRQHandler(void)      /*  IRQ 17  */
{
    while (1);
}

void GP32C4T1_IRQHandler(void)      /*  IRQ 15  */
{
    while (1);
}

void BS16T1_IRQHandler(void)        /*  IRQ 14  */
{
    while (1);
}

void DMA1_CH345_IRQHandler(void)    /*  IRQ 11  */
{
    while (1);
}

void DMA1_CH12_IRQHandler(void)     /*  IRQ 10  */
{
    while (1);
}



void SPI3_IRQHandler(void)          /*  IRQ 8   */
{
    while (1);
}



void EXTI_2to3_IRQHandler(void)     /*  IRQ 6   */
{
    while (1);
}

void RCU_CSU_IRQHandler(void)      /*  IRQ 4    */
{
    while (1);
}

void WAKEUP_IRQHandler(void)       /*  IRQ 3    */
{
    while (1);
}

void RTC_IRQHandler(void)          /*  IRQ 2    */
{
    while (1);
}

void PVD_IRQHandler(void)          /*  IRQ 1    */
{
    while (1);
}

void WWDT_IRQHandler(void)         /*  IRQ 0    */
{
    while (1);
}

/**
  * @} Exceptions Handlers
  */

/**
  * @} INTERRUPT
  */

/**
  * @} Projects_Examples
  */
/******************* (C) COPYRIGHT Eastsoft Microelectronics END OF FILE****/
