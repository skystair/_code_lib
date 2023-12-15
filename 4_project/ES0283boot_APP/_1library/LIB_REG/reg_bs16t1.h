/**********************************************************************************
 *
 * @file    reg_bs16t1.h
 * @brief   BS16T1 Head File
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

#ifndef __BS16T1_H__
#define __BS16T1_H__


/******************************************************************************/
/*              Device Specific Peripheral registers structures               */
/******************************************************************************/

/*  Support for anonymous structures and unions.  */
#pragma anon_unions

/****************** Bit definition for BS16T1_CON1 register ************************/

# define  BS16T1_CON1_ARPEN_POS 7U
# define  BS16T1_CON1_ARPEN_MSK BIT(BS16T1_CON1_ARPEN_POS)
# define  BS16T1_CON1_ARPEN     BS16T1_CON1_ARPEN_MSK

# define  BS16T1_CON1_SPMEN_POS 3U
# define  BS16T1_CON1_SPMEN_MSK BIT(BS16T1_CON1_SPMEN_POS)
# define  BS16T1_CON1_SPMEN     BS16T1_CON1_SPMEN_MSK

# define  BS16T1_CON1_UERSEL_POS 2U
# define  BS16T1_CON1_UERSEL_MSK BIT(BS16T1_CON1_UERSEL_POS)
# define  BS16T1_CON1_UERSEL     BS16T1_CON1_UERSEL_MSK

# define  BS16T1_CON1_DISUE_POS 1U
# define  BS16T1_CON1_DISUE_MSK BIT(BS16T1_CON1_DISUE_POS)
# define  BS16T1_CON1_DISUE     BS16T1_CON1_DISUE_MSK

# define  BS16T1_CON1_CNTEN_POS 0U
# define  BS16T1_CON1_CNTEN_MSK BIT(BS16T1_CON1_CNTEN_POS)
# define  BS16T1_CON1_CNTEN     BS16T1_CON1_CNTEN_MSK

/****************** Bit definition for BS16T1_CON2 register ************************/

# define  BS16T1_CON2_MMSEL_POSS 4U
# define  BS16T1_CON2_MMSEL_POSE 6U
# define  BS16T1_CON2_MMSEL_MSK  BITS(BS16T1_CON2_MMSEL_POSS, BS16T1_CON2_MMSEL_POSE)
# define  BS16T1_CON2_MMSEL      BS16T1_CON2_MMSEL_MSK

/****************** Bit definition for BS16T1_IER register ************************/

# define  BS16T1_IER_UPD_POS 0U
# define  BS16T1_IER_UPD_MSK BIT(BS16T1_IER_UPD_POS)
# define  BS16T1_IER_UPD     BS16T1_IER_UPD_MSK

/****************** Bit definition for BS16T1_IDR register ************************/

# define  BS16T1_IDR_UPD_POS 0U
# define  BS16T1_IDR_UPD_MSK BIT(BS16T1_IDR_UPD_POS)
# define  BS16T1_IDR_UPD     BS16T1_IDR_UPD_MSK

/****************** Bit definition for BS16T1_IVS register ************************/

# define  BS16T1_IVS_UPD_POS 0U
# define  BS16T1_IVS_UPD_MSK BIT(BS16T1_IVS_UPD_POS)
# define  BS16T1_IVS_UPD     BS16T1_IVS_UPD_MSK

/****************** Bit definition for BS16T1_RIF register ************************/

# define  BS16T1_RIF_UPD_POS 0U
# define  BS16T1_RIF_UPD_MSK BIT(BS16T1_RIF_UPD_POS)
# define  BS16T1_RIF_UPD     BS16T1_RIF_UPD_MSK

/****************** Bit definition for BS16T1_IFM register ************************/

# define  BS16T1_IFM_UPD_POS 0U
# define  BS16T1_IFM_UPD_MSK BIT(BS16T1_IFM_UPD_POS)
# define  BS16T1_IFM_UPD     BS16T1_IFM_UPD_MSK

/****************** Bit definition for BS16T1_ICR register ************************/

# define  BS16T1_ICR_UPD_POS 0U
# define  BS16T1_ICR_UPD_MSK BIT(BS16T1_ICR_UPD_POS)
# define  BS16T1_ICR_UPD     BS16T1_ICR_UPD_MSK

/****************** Bit definition for BS16T1_SGE register ************************/

# define  BS16T1_SGE_SGUPD_POS 0U
# define  BS16T1_SGE_SGUPD_MSK BIT(BS16T1_SGE_SGUPD_POS)
# define  BS16T1_SGE_SGUPD     BS16T1_SGE_SGUPD_MSK

/****************** Bit definition for BS16T1_COUNT register ************************/

# define  BS16T1_COUNT_CNTV_POSS 0U
# define  BS16T1_COUNT_CNTV_POSE 15U
# define  BS16T1_COUNT_CNTV_MSK  BITS(BS16T1_COUNT_CNTV_POSS, BS16T1_COUNT_CNTV_POSE)
# define  BS16T1_COUNT_CNTV      BS16T1_COUNT_CNTV_MSK

/****************** Bit definition for BS16T1_PRES register ************************/

# define  BS16T1_PRES_PSCV_POSS 0U
# define  BS16T1_PRES_PSCV_POSE 15U
# define  BS16T1_PRES_PSCV_MSK  BITS(BS16T1_PRES_PSCV_POSS, BS16T1_PRES_PSCV_POSE)
# define  BS16T1_PRES_PSCV      BS16T1_PRES_PSCV_MSK

/****************** Bit definition for BS16T1_AR register ************************/

# define  BS16T1_AR_ARV_POSS 0U
# define  BS16T1_AR_ARV_POSE 15U
# define  BS16T1_AR_ARV_MSK  BITS(BS16T1_AR_ARV_POSS, BS16T1_AR_ARV_POSE)
# define  BS16T1_AR_ARV      BS16T1_AR_ARV_MSK

/****************** Bit definition for BS16T1_DMAEN register ************************/

# define  BS16T1_DMAEN_UPD_POS 0U
# define  BS16T1_DMAEN_UPD_MSK BIT(BS16T1_DMAEN_UPD_POS)
# define  BS16T1_DMAEN_UPD     BS16T1_DMAEN_UPD_MSK

typedef struct
{
  __IO uint32_t CON1;                     // 0x000
  __IO uint32_t CON2;                     // 0x004
  __IO uint32_t RESERVED0;                // 0x008
  __O  uint32_t IER;                      // 0x00c
  __O  uint32_t IDR;                      // 0x010
  __I  uint32_t IVS;                      // 0x014
  __I  uint32_t RIF;                      // 0x018
  __I  uint32_t IFM;                      // 0x01c
  __O  uint32_t ICR;                      // 0x020
  __O  uint32_t SGE;                      // 0x024
  __IO uint32_t RESERVED1[3];             // 0x028-0x030
  __IO uint32_t COUNT;                    // 0x034
  __IO uint32_t PRES;                     // 0x038
  __IO uint32_t AR;                       // 0x03c
  __IO uint32_t RESERVED2[6];             // 0x040-0x054
  __IO uint32_t DMAEN;                    // 0x058
} BS16T1_TypeDef;


#endif
