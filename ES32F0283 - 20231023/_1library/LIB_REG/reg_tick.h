/**********************************************************************************
 *
 * @file    reg_tick.h
 * @brief   TICK Head File
 *
 * @date    23 Nov 2021
 * @author  AE Team
 * @note
 *          Change Logs:
 *          Date            Author          Notes
 *          23 Nov 2021     Ginger          the first version
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

#ifndef __TICK_H__
#define __TICK_H__

/******************************************************************************/
/*              Device Specific Peripheral registers structures               */
/******************************************************************************/

/* #pragma anon_unions */

/****************** Bit definition for TICK_CSR register ************************/

#define TICK_CSR_ENABLE_POS  0U
#define TICK_CSR_ENABLE_MSK  BIT(TICK_CSR_ENABLE_POS)
#define TICK_CSR_ENABLE      TICK_CSR_ENABLE_MSK

#define TICK_CSR_TICKIE_POS 1U
#define TICK_CSR_TICKIE_MSK BIT(TICK_CSR_TICKIE_POS)
#define TICK_CSR_TICKIE     TICK_CSR_TICKIE_MSK

#define TICK_CSR_CLKSRC_POS 2U
#define TICK_CSR_CLKSRC_MSK BIT(TICK_CSR_CLKSRC_POS)
#define TICK_CSR_CLKSRC     TICK_CSR_CLKSRC_MSK

#define TICK_CSR_COUNT_POS 16U
#define TICK_CSR_COUNT_MSK BIT(TICK_CSR_COUNT_POS)
#define TICK_CSR_COUNT     TICK_CSR_COUNT_MSK

/****************** Bit definition for TICK_RVR register ************************/

#define TICK_RVR_RELOAD_POSS 0U
#define TICK_RVR_RELOAD_POSE 23U
#define TICK_RVR_RELOAD_MSK  BITS(TICK_RVR_RELOAD_POSS,TICK_RVR_RELOAD_POSE)
#define TICK_RVR_RELOAD      TICK_RVR_RELOAD_MSK

/****************** Bit definition for TICK_CVR register ************************/

#define TICK_CVR_CURRENT_POSS 0U
#define TICK_CVR_CURRENT_POSE 23U
#define TICK_CVR_CURRENT_MSK  BITS(TICK_CVR_CURRENT_POSS,TICK_CVR_CURRENT_POSE)
#define TICK_CVR_CURRENT      TICK_CVR_CURRENT_MSK

/****************** Bit definition for TICK_CALIB register ************************/

#define TICK_CALIB_TENMS_POSS 0U
#define TICK_CALIB_TENMS_POSE 23U
#define TICK_CALIB_TENMS_MSK  BITS(TICK_CALIB_TENMS_POSS,TICK_CALIB_TENMS_POSE)
#define TICK_CALIB_TENMS      TICK_CALIB_TENMS_MSK

#define TICK_CALIB_SKEW_POS 30U
#define TICK_CALIB_SKEW_MSK BIT(TICK_CALIB_SKEW_POS)
#define TICK_CALIB_SKEW     TICK_CALIB_SKEW_MSK

#define TICK_CALIB_NOREF_POS 31U
#define TICK_CALIB_NOREF_MSK BIT(TICK_CALIB_NOREF_POS)
#define TICK_CALIB_NOREF     TICK_CALIB_NOREF_MSK


/*  TICK Register  */
#define  pTICK    TICK

/*  TICK CSR Register(TICK_CSR)  */
#define CSR_COUNTFLAG(x)  (x<<16)  /*  Indicates whether the counter has counted to 0 since the last read of this register
                    0 timer has not counted to 0
                    1 timer has counted to 0  */
#define CSR_CLKSOURCE(x)  (x<<2)  /*  Indicates the SysTick clock source:
                    0 SysTick uses the optional external reference clock
                    1 SysTick uses the processor clock  */
#define CSR_TICKINT(x)    (x<<1)  /*  Indicates whether counting to 0 causes the status of the SysTick exception to change to pending:
                    0 count to 0 does not affect the SysTick exception status
                    1 count to 0 changes the SysTick exception status to pending  */
#define CSR_ENABLE(x)    (x<<0)  /*  /Indicates the enabled status of the SysTick counter:
                    0 counter is disabled
                    1 counter is operating  */


/*  TICK RVR Register(TICK_RVR)  */
#define RVR_RELOAD(x)    (x<<0)  /*  The value to load into the SYST_CVR register when the counter reaches 0  */


/*  TICK CVR Register(TICK_CVR)  */
#define CVR_CURRENT(x)    (x<<0)  /*  Current counter value
                    This is the value of the counter at the time it is sampled  */


/*  TICK CALIB Register(TICK_CALIB)  */
#define CALIB_NOREF(x)  (x<<31)    /*  Indicates whether the IMPLEMENTATION DEFINED reference clock is provided:
                    0 the reference clock is implemented
                    1 the reference clock is not implemented
                    When this bit is 1, the CLKSOURCE bit of the SYST_CSR register is forced to 1 and cannot be cleared to 0  */
#define CALIB_SKEW(x)  (x<<30)    /*  Indicates whether the 10ms calibration value is exact:
                    0 10ms calibration value is exact
                    1 10ms calibration value is inexact, because of the clock frequency  */
#define CALIB_TENMS(x)  (x<<0)    /*  Optionally, holds a reload value to be used for 10ms (100Hz) timing, subject to system clock skew errors.
                    If this field is zero, the calibration value is not known  */
typedef struct
{
    __IO uint32_t   CSR;            /*  0x0, Control and Status  */
    __IO uint32_t   RVR;            /*  0x4, Reload Value  */
    __IO uint32_t   CVR;            /*  0x8, Current Value  */
    __I  uint32_t   CALIB;          /*  0xC, Calibration  */
} TICK_TypeDef;


#else
/* */
#endif
