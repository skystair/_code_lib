/**********************************************************************************
 *
 * @file    interrupt.h
 * @brief   Interrupt handler
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

#ifndef    _Interrupt_H
#define    _Interrupt_H

#ifdef ISR_GLOBALS
    #define ISR_PUBLIC
#else
    #define ISR_PUBLIC extern
#endif

//----------------------------------------------------------------------------------------
//*************************************//
//    Public function defined        //
//*************************************//



ISR_PUBLIC void Reset_Handler(void);                // vector NO:
ISR_PUBLIC void NMI_Handler(void);                  // vector NO:
ISR_PUBLIC void HARDFAULT_Handler(void);            // vector NO:
ISR_PUBLIC void SVC_Handler(void);                  // vector NO:
ISR_PUBLIC void PENDSV_Handler(void);              // vector  NO:
ISR_PUBLIC void SYSTICK_Handler(void);              // vector NO:
ISR_PUBLIC void WWDT_IRQHandler(void);              // vector NO: IRQ NO:0
ISR_PUBLIC void PVD_IRQHandler(void);               // vector NO: IRQ NO:1
ISR_PUBLIC void RTC_IRQHandler(void);               // vector NO: IRQ NO:2
ISR_PUBLIC void WAKEUP_IRQHandler(void);            // vector NO: IRQ NO:3
ISR_PUBLIC void RCU_CSU_IRQHandler(void);           // vector NO: IRQ NO:4
ISR_PUBLIC void EXTI_0to1_IRQHandler(void);         // vector NO: IRQ NO:5
ISR_PUBLIC void EXTI_2to3_IRQHandler(void);         // vector NO: IRQ NO:6
ISR_PUBLIC void EXTI_4to15_IRQHandler(void);        // vector NO: IRQ NO:7
ISR_PUBLIC void SPI3_IRQHandler(void);              // vector NO: IRQ NO:8
ISR_PUBLIC void DMA1_CH0_IRQHandler(void);          // vector NO: IRQ NO:9
ISR_PUBLIC void DMA1_CH12_IRQHandler(void);         // vector NO: IRQ NO:10
ISR_PUBLIC void DMA1_CH345_IRQHandler(void);        // vector NO: IRQ NO:11
ISR_PUBLIC void ADC_COMP_IRQHandler(void);          // vector NO: IRQ NO:12
ISR_PUBLIC void AD16C4T1_IRQHandler(void);          // vector NO: IRQ NO:13
ISR_PUBLIC void BS16T1_IRQHandler(void);            // vector NO: IRQ NO:14
ISR_PUBLIC void GP32C4T1_IRQHandler(void);          // vector NO: IRQ NO:15
ISR_PUBLIC void GP16C4T1_IRQHandler(void);          // vector NO: IRQ NO:16
ISR_PUBLIC void GP16C4T2_IRQHandler(void);          // vector NO: IRQ NO:17
ISR_PUBLIC void GP16C4T3_IRQHandler(void);          // vector NO: IRQ NO:18
ISR_PUBLIC void GP16C2T1_IRQHandler(void);          // vector NO: IRQ NO:19
ISR_PUBLIC void GP16C2T2_IRQHandler(void);          // vector NO: IRQ NO:20
ISR_PUBLIC void GP16C2T3_IRQHandler(void);          // vector NO: IRQ NO:21
ISR_PUBLIC void GP16C2T4_IRQHandler(void);          // vector NO: IRQ NO:22
ISR_PUBLIC void I2C1_IRQHandler(void);              // vector NO: IRQ NO:23
ISR_PUBLIC void I2C2_IRQHandler(void);              // vector NO: IRQ NO:24
ISR_PUBLIC void SPI1_IRQHandler(void);              // vector NO: IRQ NO:25
ISR_PUBLIC void SPI2_IRQHandler(void);              // vector NO: IRQ NO:26
ISR_PUBLIC void UART1_IRQHandler(void);             // vector NO: IRQ NO:27
ISR_PUBLIC void UART2_IRQHandler(void);             // vector NO: IRQ NO:28
ISR_PUBLIC void UART3_AES_IRQHandler(void);         // vector NO: IRQ NO:29
ISR_PUBLIC void UART4_KBCU_IRQHandler(void);        // vector NO: IRQ NO:30
ISR_PUBLIC void USB_IRQHandler(void);               // vector NO: IRQ NO:31
//**************************************//
//    Public variable defined            //
//**************************************//


#undef ISR_PUBLIC


#else
/* */
#endif
/******************* (C) COPYRIGHT Eastsoft Microelectronics END OF FILE****/
