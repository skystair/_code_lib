/**********************************************************************************
 *
 * @file    reg_gp16c4tn.h
 * @brief   GP16C4Tn Head File
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

#ifndef __GP16C4Tn_H__
#define __GP16C4Tn_H__


/******************************************************************************/
/*              Device Specific Peripheral registers structures               */
/******************************************************************************/

/*  Support for anonymous structures and unions.  */
#pragma anon_unions

/****************** Bit definition for GP16C4Tn_CON1 register ************************/

# define  GP16C4Tn_CON1_DBGSEL_POS 15U
# define  GP16C4Tn_CON1_DBGSEL_MSK BIT(GP16C4Tn_CON1_DBGSEL_POS)
# define  GP16C4Tn_CON1_DBGSEL     GP16C4Tn_CON1_DBGSEL_MSK

# define  GP16C4Tn_CON1_DFCKSEL_POSS 8U
# define  GP16C4Tn_CON1_DFCKSEL_POSE 9U
# define  GP16C4Tn_CON1_DFCKSEL_MSK  BITS(GP16C4Tn_CON1_DFCKSEL_POSS, GP16C4Tn_CON1_DFCKSEL_POSE)
# define  GP16C4Tn_CON1_DFCKSEL      GP16C4Tn_CON1_DFCKSEL_MSK

# define  GP16C4Tn_CON1_ARPEN_POS 7U
# define  GP16C4Tn_CON1_ARPEN_MSK BIT(GP16C4Tn_CON1_ARPEN_POS)
# define  GP16C4Tn_CON1_ARPEN     GP16C4Tn_CON1_ARPEN_MSK

# define  GP16C4Tn_CON1_CMSEL_POSS 5U
# define  GP16C4Tn_CON1_CMSEL_POSE 6U
# define  GP16C4Tn_CON1_CMSEL_MSK  BITS(GP16C4Tn_CON1_CMSEL_POSS, GP16C4Tn_CON1_CMSEL_POSE)
# define  GP16C4Tn_CON1_CMSEL      GP16C4Tn_CON1_CMSEL_MSK

# define  GP16C4Tn_CON1_DIRSEL_POS 4U
# define  GP16C4Tn_CON1_DIRSEL_MSK BIT(GP16C4Tn_CON1_DIRSEL_POS)
# define  GP16C4Tn_CON1_DIRSEL     GP16C4Tn_CON1_DIRSEL_MSK

# define  GP16C4Tn_CON1_SPMEN_POS 3U
# define  GP16C4Tn_CON1_SPMEN_MSK BIT(GP16C4Tn_CON1_SPMEN_POS)
# define  GP16C4Tn_CON1_SPMEN     GP16C4Tn_CON1_SPMEN_MSK

# define  GP16C4Tn_CON1_UERSEL_POS 2U
# define  GP16C4Tn_CON1_UERSEL_MSK BIT(GP16C4Tn_CON1_UERSEL_POS)
# define  GP16C4Tn_CON1_UERSEL     GP16C4Tn_CON1_UERSEL_MSK

# define  GP16C4Tn_CON1_DISUE_POS 1U
# define  GP16C4Tn_CON1_DISUE_MSK BIT(GP16C4Tn_CON1_DISUE_POS)
# define  GP16C4Tn_CON1_DISUE     GP16C4Tn_CON1_DISUE_MSK

# define  GP16C4Tn_CON1_CNTEN_POS 0U
# define  GP16C4Tn_CON1_CNTEN_MSK BIT(GP16C4Tn_CON1_CNTEN_POS)
# define  GP16C4Tn_CON1_CNTEN     GP16C4Tn_CON1_CNTEN_MSK

/****************** Bit definition for GP16C4Tn_CON2 register ************************/

# define  GP16C4Tn_CON2_I1SEL_POS 7U
# define  GP16C4Tn_CON2_I1SEL_MSK BIT(GP16C4Tn_CON2_I1SEL_POS)
# define  GP16C4Tn_CON2_I1SEL     GP16C4Tn_CON2_I1SEL_MSK

# define  GP16C4Tn_CON2_MMSEL_POSS 4U
# define  GP16C4Tn_CON2_MMSEL_POSE 6U
# define  GP16C4Tn_CON2_MMSEL_MSK  BITS(GP16C4Tn_CON2_MMSEL_POSS, GP16C4Tn_CON2_MMSEL_POSE)
# define  GP16C4Tn_CON2_MMSEL      GP16C4Tn_CON2_MMSEL_MSK

# define  GP16C4Tn_CON2_CCDMASEL_POS 3U
# define  GP16C4Tn_CON2_CCDMASEL_MSK BIT(GP16C4Tn_CON2_CCDMASEL_POS)
# define  GP16C4Tn_CON2_CCDMASEL     GP16C4Tn_CON2_CCDMASEL_MSK

/****************** Bit definition for GP16C4Tn_SMCON register ************************/

# define  GP16C4Tn_SMCON_TSSEL2_POSS 20U
# define  GP16C4Tn_SMCON_TSSEL2_POSE 21U
# define  GP16C4Tn_SMCON_TSSEL2_MSK  BITS(GP16C4Tn_SMCON_TSSEL2_POSS, GP16C4Tn_SMCON_TSSEL2_POSE)
# define  GP16C4Tn_SMCON_TSSEL2      GP16C4Tn_SMCON_TSSEL2_MSK

# define  GP16C4Tn_SMCON_ETPOL_POS 15U
# define  GP16C4Tn_SMCON_ETPOL_MSK BIT(GP16C4Tn_SMCON_ETPOL_POS)
# define  GP16C4Tn_SMCON_ETPOL     GP16C4Tn_SMCON_ETPOL_MSK

# define  GP16C4Tn_SMCON_ECM2EN_POS 14U
# define  GP16C4Tn_SMCON_ECM2EN_MSK BIT(GP16C4Tn_SMCON_ECM2EN_POS)
# define  GP16C4Tn_SMCON_ECM2EN     GP16C4Tn_SMCON_ECM2EN_MSK

# define  GP16C4Tn_SMCON_ETPRES_POSS 12U
# define  GP16C4Tn_SMCON_ETPRES_POSE 13U
# define  GP16C4Tn_SMCON_ETPRES_MSK  BITS(GP16C4Tn_SMCON_ETPRES_POSS, GP16C4Tn_SMCON_ETPRES_POSE)
# define  GP16C4Tn_SMCON_ETPRES      GP16C4Tn_SMCON_ETPRES_MSK

# define  GP16C4Tn_SMCON_ETFLT_POSS 8U
# define  GP16C4Tn_SMCON_ETFLT_POSE 11U
# define  GP16C4Tn_SMCON_ETFLT_MSK  BITS(GP16C4Tn_SMCON_ETFLT_POSS, GP16C4Tn_SMCON_ETFLT_POSE)
# define  GP16C4Tn_SMCON_ETFLT      GP16C4Tn_SMCON_ETFLT_MSK

# define  GP16C4Tn_SMCON_MSCFG_POS 7U
# define  GP16C4Tn_SMCON_MSCFG_MSK BIT(GP16C4Tn_SMCON_MSCFG_POS)
# define  GP16C4Tn_SMCON_MSCFG     GP16C4Tn_SMCON_MSCFG_MSK

# define  GP16C4Tn_SMCON_TSSEL1_POSS 4U
# define  GP16C4Tn_SMCON_TSSEL1_POSE 6U
# define  GP16C4Tn_SMCON_TSSEL1_MSK  BITS(GP16C4Tn_SMCON_TSSEL1_POSS, GP16C4Tn_SMCON_TSSEL1_POSE)
# define  GP16C4Tn_SMCON_TSSEL1      GP16C4Tn_SMCON_TSSEL1_MSK

# define  GP16C4Tn_SMCON_SMODS_POSS 0U
# define  GP16C4Tn_SMCON_SMODS_POSE 2U
# define  GP16C4Tn_SMCON_SMODS_MSK  BITS(GP16C4Tn_SMCON_SMODS_POSS, GP16C4Tn_SMCON_SMODS_POSE)
# define  GP16C4Tn_SMCON_SMODS      GP16C4Tn_SMCON_SMODS_MSK

/****************** Bit definition for GP16C4Tn_IER register ************************/

# define  GP16C4Tn_IER_CH4OV_POS 12U
# define  GP16C4Tn_IER_CH4OV_MSK BIT(GP16C4Tn_IER_CH4OV_POS)
# define  GP16C4Tn_IER_CH4OV     GP16C4Tn_IER_CH4OV_MSK

# define  GP16C4Tn_IER_CH3OV_POS 11U
# define  GP16C4Tn_IER_CH3OV_MSK BIT(GP16C4Tn_IER_CH3OV_POS)
# define  GP16C4Tn_IER_CH3OV     GP16C4Tn_IER_CH3OV_MSK

# define  GP16C4Tn_IER_CH2OV_POS 10U
# define  GP16C4Tn_IER_CH2OV_MSK BIT(GP16C4Tn_IER_CH2OV_POS)
# define  GP16C4Tn_IER_CH2OV     GP16C4Tn_IER_CH2OV_MSK

# define  GP16C4Tn_IER_CH1OV_POS 9U
# define  GP16C4Tn_IER_CH1OV_MSK BIT(GP16C4Tn_IER_CH1OV_POS)
# define  GP16C4Tn_IER_CH1OV     GP16C4Tn_IER_CH1OV_MSK

# define  GP16C4Tn_IER_TRGI_POS 6U
# define  GP16C4Tn_IER_TRGI_MSK BIT(GP16C4Tn_IER_TRGI_POS)
# define  GP16C4Tn_IER_TRGI     GP16C4Tn_IER_TRGI_MSK

# define  GP16C4Tn_IER_CH4_POS 4U
# define  GP16C4Tn_IER_CH4_MSK BIT(GP16C4Tn_IER_CH4_POS)
# define  GP16C4Tn_IER_CH4     GP16C4Tn_IER_CH4_MSK

# define  GP16C4Tn_IER_CH3_POS 3U
# define  GP16C4Tn_IER_CH3_MSK BIT(GP16C4Tn_IER_CH3_POS)
# define  GP16C4Tn_IER_CH3     GP16C4Tn_IER_CH3_MSK

# define  GP16C4Tn_IER_CH2_POS 2U
# define  GP16C4Tn_IER_CH2_MSK BIT(GP16C4Tn_IER_CH2_POS)
# define  GP16C4Tn_IER_CH2     GP16C4Tn_IER_CH2_MSK

# define  GP16C4Tn_IER_CH1_POS 1U
# define  GP16C4Tn_IER_CH1_MSK BIT(GP16C4Tn_IER_CH1_POS)
# define  GP16C4Tn_IER_CH1     GP16C4Tn_IER_CH1_MSK

# define  GP16C4Tn_IER_UPD_POS 0U
# define  GP16C4Tn_IER_UPD_MSK BIT(GP16C4Tn_IER_UPD_POS)
# define  GP16C4Tn_IER_UPD     GP16C4Tn_IER_UPD_MSK

/****************** Bit definition for GP16C4Tn_IDR register ************************/

# define  GP16C4Tn_IDR_CH4OV_POS 12U
# define  GP16C4Tn_IDR_CH4OV_MSK BIT(GP16C4Tn_IDR_CH4OV_POS)
# define  GP16C4Tn_IDR_CH4OV     GP16C4Tn_IDR_CH4OV_MSK

# define  GP16C4Tn_IDR_CH3OV_POS 11U
# define  GP16C4Tn_IDR_CH3OV_MSK BIT(GP16C4Tn_IDR_CH3OV_POS)
# define  GP16C4Tn_IDR_CH3OV     GP16C4Tn_IDR_CH3OV_MSK

# define  GP16C4Tn_IDR_CH2OV_POS 10U
# define  GP16C4Tn_IDR_CH2OV_MSK BIT(GP16C4Tn_IDR_CH2OV_POS)
# define  GP16C4Tn_IDR_CH2OV     GP16C4Tn_IDR_CH2OV_MSK

# define  GP16C4Tn_IDR_CH1OV_POS 9U
# define  GP16C4Tn_IDR_CH1OV_MSK BIT(GP16C4Tn_IDR_CH1OV_POS)
# define  GP16C4Tn_IDR_CH1OV     GP16C4Tn_IDR_CH1OV_MSK

# define  GP16C4Tn_IDR_TRGI_POS 6U
# define  GP16C4Tn_IDR_TRGI_MSK BIT(GP16C4Tn_IDR_TRGI_POS)
# define  GP16C4Tn_IDR_TRGI     GP16C4Tn_IDR_TRGI_MSK

# define  GP16C4Tn_IDR_CH4_POS 4U
# define  GP16C4Tn_IDR_CH4_MSK BIT(GP16C4Tn_IDR_CH4_POS)
# define  GP16C4Tn_IDR_CH4     GP16C4Tn_IDR_CH4_MSK

# define  GP16C4Tn_IDR_CH3_POS 3U
# define  GP16C4Tn_IDR_CH3_MSK BIT(GP16C4Tn_IDR_CH3_POS)
# define  GP16C4Tn_IDR_CH3     GP16C4Tn_IDR_CH3_MSK

# define  GP16C4Tn_IDR_CH2_POS 2U
# define  GP16C4Tn_IDR_CH2_MSK BIT(GP16C4Tn_IDR_CH2_POS)
# define  GP16C4Tn_IDR_CH2     GP16C4Tn_IDR_CH2_MSK

# define  GP16C4Tn_IDR_CH1_POS 1U
# define  GP16C4Tn_IDR_CH1_MSK BIT(GP16C4Tn_IDR_CH1_POS)
# define  GP16C4Tn_IDR_CH1     GP16C4Tn_IDR_CH1_MSK

# define  GP16C4Tn_IDR_UPD_POS 0U
# define  GP16C4Tn_IDR_UPD_MSK BIT(GP16C4Tn_IDR_UPD_POS)
# define  GP16C4Tn_IDR_UPD     GP16C4Tn_IDR_UPD_MSK

/****************** Bit definition for GP16C4Tn_IVS register ************************/

# define  GP16C4Tn_IVS_CH4OV_POS 12U
# define  GP16C4Tn_IVS_CH4OV_MSK BIT(GP16C4Tn_IVS_CH4OV_POS)
# define  GP16C4Tn_IVS_CH4OV     GP16C4Tn_IVS_CH4OV_MSK

# define  GP16C4Tn_IVS_CH3OV_POS 11U
# define  GP16C4Tn_IVS_CH3OV_MSK BIT(GP16C4Tn_IVS_CH3OV_POS)
# define  GP16C4Tn_IVS_CH3OV     GP16C4Tn_IVS_CH3OV_MSK

# define  GP16C4Tn_IVS_CH2OV_POS 10U
# define  GP16C4Tn_IVS_CH2OV_MSK BIT(GP16C4Tn_IVS_CH2OV_POS)
# define  GP16C4Tn_IVS_CH2OV     GP16C4Tn_IVS_CH2OV_MSK

# define  GP16C4Tn_IVS_CH1OV_POS 9U
# define  GP16C4Tn_IVS_CH1OV_MSK BIT(GP16C4Tn_IVS_CH1OV_POS)
# define  GP16C4Tn_IVS_CH1OV     GP16C4Tn_IVS_CH1OV_MSK

# define  GP16C4Tn_IVS_TRGI_POS 6U
# define  GP16C4Tn_IVS_TRGI_MSK BIT(GP16C4Tn_IVS_TRGI_POS)
# define  GP16C4Tn_IVS_TRGI     GP16C4Tn_IVS_TRGI_MSK

# define  GP16C4Tn_IVS_CH4_POS 4U
# define  GP16C4Tn_IVS_CH4_MSK BIT(GP16C4Tn_IVS_CH4_POS)
# define  GP16C4Tn_IVS_CH4     GP16C4Tn_IVS_CH4_MSK

# define  GP16C4Tn_IVS_CH3_POS 3U
# define  GP16C4Tn_IVS_CH3_MSK BIT(GP16C4Tn_IVS_CH3_POS)
# define  GP16C4Tn_IVS_CH3     GP16C4Tn_IVS_CH3_MSK

# define  GP16C4Tn_IVS_CH2_POS 2U
# define  GP16C4Tn_IVS_CH2_MSK BIT(GP16C4Tn_IVS_CH2_POS)
# define  GP16C4Tn_IVS_CH2     GP16C4Tn_IVS_CH2_MSK

# define  GP16C4Tn_IVS_CH1_POS 1U
# define  GP16C4Tn_IVS_CH1_MSK BIT(GP16C4Tn_IVS_CH1_POS)
# define  GP16C4Tn_IVS_CH1     GP16C4Tn_IVS_CH1_MSK

# define  GP16C4Tn_IVS_UPD_POS 0U
# define  GP16C4Tn_IVS_UPD_MSK BIT(GP16C4Tn_IVS_UPD_POS)
# define  GP16C4Tn_IVS_UPD     GP16C4Tn_IVS_UPD_MSK

/****************** Bit definition for GP16C4Tn_RIF register ************************/

# define  GP16C4Tn_RIF_CH4OV_POS 12U
# define  GP16C4Tn_RIF_CH4OV_MSK BIT(GP16C4Tn_RIF_CH4OV_POS)
# define  GP16C4Tn_RIF_CH4OV     GP16C4Tn_RIF_CH4OV_MSK

# define  GP16C4Tn_RIF_CH3OV_POS 11U
# define  GP16C4Tn_RIF_CH3OV_MSK BIT(GP16C4Tn_RIF_CH3OV_POS)
# define  GP16C4Tn_RIF_CH3OV     GP16C4Tn_RIF_CH3OV_MSK

# define  GP16C4Tn_RIF_CH2OV_POS 10U
# define  GP16C4Tn_RIF_CH2OV_MSK BIT(GP16C4Tn_RIF_CH2OV_POS)
# define  GP16C4Tn_RIF_CH2OV     GP16C4Tn_RIF_CH2OV_MSK

# define  GP16C4Tn_RIF_CH1OV_POS 9U
# define  GP16C4Tn_RIF_CH1OV_MSK BIT(GP16C4Tn_RIF_CH1OV_POS)
# define  GP16C4Tn_RIF_CH1OV     GP16C4Tn_RIF_CH1OV_MSK

# define  GP16C4Tn_RIF_TRGI_POS 6U
# define  GP16C4Tn_RIF_TRGI_MSK BIT(GP16C4Tn_RIF_TRGI_POS)
# define  GP16C4Tn_RIF_TRGI     GP16C4Tn_RIF_TRGI_MSK

# define  GP16C4Tn_RIF_CH4_POS 4U
# define  GP16C4Tn_RIF_CH4_MSK BIT(GP16C4Tn_RIF_CH4_POS)
# define  GP16C4Tn_RIF_CH4     GP16C4Tn_RIF_CH4_MSK

# define  GP16C4Tn_RIF_CH3_POS 3U
# define  GP16C4Tn_RIF_CH3_MSK BIT(GP16C4Tn_RIF_CH3_POS)
# define  GP16C4Tn_RIF_CH3     GP16C4Tn_RIF_CH3_MSK

# define  GP16C4Tn_RIF_CH2_POS 2U
# define  GP16C4Tn_RIF_CH2_MSK BIT(GP16C4Tn_RIF_CH2_POS)
# define  GP16C4Tn_RIF_CH2     GP16C4Tn_RIF_CH2_MSK

# define  GP16C4Tn_RIF_CH1_POS 1U
# define  GP16C4Tn_RIF_CH1_MSK BIT(GP16C4Tn_RIF_CH1_POS)
# define  GP16C4Tn_RIF_CH1     GP16C4Tn_RIF_CH1_MSK

# define  GP16C4Tn_RIF_UPD_POS 0U
# define  GP16C4Tn_RIF_UPD_MSK BIT(GP16C4Tn_RIF_UPD_POS)
# define  GP16C4Tn_RIF_UPD     GP16C4Tn_RIF_UPD_MSK

/****************** Bit definition for GP16C4Tn_IFM register ************************/

# define  GP16C4Tn_IFM_CH4OV_POS 12U
# define  GP16C4Tn_IFM_CH4OV_MSK BIT(GP16C4Tn_IFM_CH4OV_POS)
# define  GP16C4Tn_IFM_CH4OV     GP16C4Tn_IFM_CH4OV_MSK

# define  GP16C4Tn_IFM_CH3OV_POS 11U
# define  GP16C4Tn_IFM_CH3OV_MSK BIT(GP16C4Tn_IFM_CH3OV_POS)
# define  GP16C4Tn_IFM_CH3OV     GP16C4Tn_IFM_CH3OV_MSK

# define  GP16C4Tn_IFM_CH2OV_POS 10U
# define  GP16C4Tn_IFM_CH2OV_MSK BIT(GP16C4Tn_IFM_CH2OV_POS)
# define  GP16C4Tn_IFM_CH2OV     GP16C4Tn_IFM_CH2OV_MSK

# define  GP16C4Tn_IFM_CH1OV_POS 9U
# define  GP16C4Tn_IFM_CH1OV_MSK BIT(GP16C4Tn_IFM_CH1OV_POS)
# define  GP16C4Tn_IFM_CH1OV     GP16C4Tn_IFM_CH1OV_MSK

# define  GP16C4Tn_IFM_TRGI_POS 6U
# define  GP16C4Tn_IFM_TRGI_MSK BIT(GP16C4Tn_IFM_TRGI_POS)
# define  GP16C4Tn_IFM_TRGI     GP16C4Tn_IFM_TRGI_MSK

# define  GP16C4Tn_IFM_CH4_POS 4U
# define  GP16C4Tn_IFM_CH4_MSK BIT(GP16C4Tn_IFM_CH4_POS)
# define  GP16C4Tn_IFM_CH4     GP16C4Tn_IFM_CH4_MSK

# define  GP16C4Tn_IFM_CH3_POS 3U
# define  GP16C4Tn_IFM_CH3_MSK BIT(GP16C4Tn_IFM_CH3_POS)
# define  GP16C4Tn_IFM_CH3     GP16C4Tn_IFM_CH3_MSK

# define  GP16C4Tn_IFM_CH2_POS 2U
# define  GP16C4Tn_IFM_CH2_MSK BIT(GP16C4Tn_IFM_CH2_POS)
# define  GP16C4Tn_IFM_CH2     GP16C4Tn_IFM_CH2_MSK

# define  GP16C4Tn_IFM_CH1_POS 1U
# define  GP16C4Tn_IFM_CH1_MSK BIT(GP16C4Tn_IFM_CH1_POS)
# define  GP16C4Tn_IFM_CH1     GP16C4Tn_IFM_CH1_MSK

# define  GP16C4Tn_IFM_UPD_POS 0U
# define  GP16C4Tn_IFM_UPD_MSK BIT(GP16C4Tn_IFM_UPD_POS)
# define  GP16C4Tn_IFM_UPD     GP16C4Tn_IFM_UPD_MSK

/****************** Bit definition for GP16C4Tn_ICR register ************************/

# define  GP16C4Tn_ICR_CH4OV_POS 12U
# define  GP16C4Tn_ICR_CH4OV_MSK BIT(GP16C4Tn_ICR_CH4OV_POS)
# define  GP16C4Tn_ICR_CH4OV     GP16C4Tn_ICR_CH4OV_MSK

# define  GP16C4Tn_ICR_CH3OV_POS 11U
# define  GP16C4Tn_ICR_CH3OV_MSK BIT(GP16C4Tn_ICR_CH3OV_POS)
# define  GP16C4Tn_ICR_CH3OV     GP16C4Tn_ICR_CH3OV_MSK

# define  GP16C4Tn_ICR_CH2OV_POS 10U
# define  GP16C4Tn_ICR_CH2OV_MSK BIT(GP16C4Tn_ICR_CH2OV_POS)
# define  GP16C4Tn_ICR_CH2OV     GP16C4Tn_ICR_CH2OV_MSK

# define  GP16C4Tn_ICR_CH1OV_POS 9U
# define  GP16C4Tn_ICR_CH1OV_MSK BIT(GP16C4Tn_ICR_CH1OV_POS)
# define  GP16C4Tn_ICR_CH1OV     GP16C4Tn_ICR_CH1OV_MSK

# define  GP16C4Tn_ICR_TRGI_POS 6U
# define  GP16C4Tn_ICR_TRGI_MSK BIT(GP16C4Tn_ICR_TRGI_POS)
# define  GP16C4Tn_ICR_TRGI     GP16C4Tn_ICR_TRGI_MSK

# define  GP16C4Tn_ICR_CH4_POS 4U
# define  GP16C4Tn_ICR_CH4_MSK BIT(GP16C4Tn_ICR_CH4_POS)
# define  GP16C4Tn_ICR_CH4     GP16C4Tn_ICR_CH4_MSK

# define  GP16C4Tn_ICR_CH3_POS 3U
# define  GP16C4Tn_ICR_CH3_MSK BIT(GP16C4Tn_ICR_CH3_POS)
# define  GP16C4Tn_ICR_CH3     GP16C4Tn_ICR_CH3_MSK

# define  GP16C4Tn_ICR_CH2_POS 2U
# define  GP16C4Tn_ICR_CH2_MSK BIT(GP16C4Tn_ICR_CH2_POS)
# define  GP16C4Tn_ICR_CH2     GP16C4Tn_ICR_CH2_MSK

# define  GP16C4Tn_ICR_CH1_POS 1U
# define  GP16C4Tn_ICR_CH1_MSK BIT(GP16C4Tn_ICR_CH1_POS)
# define  GP16C4Tn_ICR_CH1     GP16C4Tn_ICR_CH1_MSK

# define  GP16C4Tn_ICR_UPD_POS 0U
# define  GP16C4Tn_ICR_UPD_MSK BIT(GP16C4Tn_ICR_UPD_POS)
# define  GP16C4Tn_ICR_UPD     GP16C4Tn_ICR_UPD_MSK

/****************** Bit definition for GP16C4Tn_SGE register ************************/

# define  GP16C4Tn_SGE_SGTRGI_POS 6U
# define  GP16C4Tn_SGE_SGTRGI_MSK BIT(GP16C4Tn_SGE_SGTRGI_POS)
# define  GP16C4Tn_SGE_SGTRGI     GP16C4Tn_SGE_SGTRGI_MSK

# define  GP16C4Tn_SGE_SGCH4_POS 4U
# define  GP16C4Tn_SGE_SGCH4_MSK BIT(GP16C4Tn_SGE_SGCH4_POS)
# define  GP16C4Tn_SGE_SGCH4     GP16C4Tn_SGE_SGCH4_MSK

# define  GP16C4Tn_SGE_SGCH3_POS 3U
# define  GP16C4Tn_SGE_SGCH3_MSK BIT(GP16C4Tn_SGE_SGCH3_POS)
# define  GP16C4Tn_SGE_SGCH3     GP16C4Tn_SGE_SGCH3_MSK

# define  GP16C4Tn_SGE_SGCH2_POS 2U
# define  GP16C4Tn_SGE_SGCH2_MSK BIT(GP16C4Tn_SGE_SGCH2_POS)
# define  GP16C4Tn_SGE_SGCH2     GP16C4Tn_SGE_SGCH2_MSK

# define  GP16C4Tn_SGE_SGCH1_POS 1U
# define  GP16C4Tn_SGE_SGCH1_MSK BIT(GP16C4Tn_SGE_SGCH1_POS)
# define  GP16C4Tn_SGE_SGCH1     GP16C4Tn_SGE_SGCH1_MSK

# define  GP16C4Tn_SGE_SGUPD_POS 0U
# define  GP16C4Tn_SGE_SGUPD_MSK BIT(GP16C4Tn_SGE_SGUPD_POS)
# define  GP16C4Tn_SGE_SGUPD     GP16C4Tn_SGE_SGUPD_MSK

/****************** Bit definition for GP16C4Tn_CHMR1_OUTPUT register ************************/

# define  GP16C4Tn_CHMR1_OUTPUT_CH2OCLREN_POS 15U
# define  GP16C4Tn_CHMR1_OUTPUT_CH2OCLREN_MSK BIT(GP16C4Tn_CHMR1_OUTPUT_CH2OCLREN_POS)
# define  GP16C4Tn_CHMR1_OUTPUT_CH2OCLREN     GP16C4Tn_CHMR1_OUTPUT_CH2OCLREN_MSK

# define  GP16C4Tn_CHMR1_OUTPUT_CH2MOD_POSS 12U
# define  GP16C4Tn_CHMR1_OUTPUT_CH2MOD_POSE 14U
# define  GP16C4Tn_CHMR1_OUTPUT_CH2MOD_MSK  BITS(GP16C4Tn_CHMR1_OUTPUT_CH2MOD_POSS, GP16C4Tn_CHMR1_OUTPUT_CH2MOD_POSE)
# define  GP16C4Tn_CHMR1_OUTPUT_CH2MOD      GP16C4Tn_CHMR1_OUTPUT_CH2MOD_MSK

# define  GP16C4Tn_CHMR1_OUTPUT_CH2PEN_POS 11U
# define  GP16C4Tn_CHMR1_OUTPUT_CH2PEN_MSK BIT(GP16C4Tn_CHMR1_OUTPUT_CH2PEN_POS)
# define  GP16C4Tn_CHMR1_OUTPUT_CH2PEN     GP16C4Tn_CHMR1_OUTPUT_CH2PEN_MSK

# define  GP16C4Tn_CHMR1_OUTPUT_CH2FEN_POS 10U
# define  GP16C4Tn_CHMR1_OUTPUT_CH2FEN_MSK BIT(GP16C4Tn_CHMR1_OUTPUT_CH2FEN_POS)
# define  GP16C4Tn_CHMR1_OUTPUT_CH2FEN     GP16C4Tn_CHMR1_OUTPUT_CH2FEN_MSK

# define  GP16C4Tn_CHMR1_OUTPUT_CC2SSEL_POSS 8U
# define  GP16C4Tn_CHMR1_OUTPUT_CC2SSEL_POSE 9U
# define  GP16C4Tn_CHMR1_OUTPUT_CC2SSEL_MSK  BITS(GP16C4Tn_CHMR1_OUTPUT_CC2SSEL_POSS, GP16C4Tn_CHMR1_OUTPUT_CC2SSEL_POSE)
# define  GP16C4Tn_CHMR1_OUTPUT_CC2SSEL      GP16C4Tn_CHMR1_OUTPUT_CC2SSEL_MSK

# define  GP16C4Tn_CHMR1_OUTPUT_CH1OCLREN_POS 7U
# define  GP16C4Tn_CHMR1_OUTPUT_CH1OCLREN_MSK BIT(GP16C4Tn_CHMR1_OUTPUT_CH1OCLREN_POS)
# define  GP16C4Tn_CHMR1_OUTPUT_CH1OCLREN     GP16C4Tn_CHMR1_OUTPUT_CH1OCLREN_MSK

# define  GP16C4Tn_CHMR1_OUTPUT_CH1MOD_POSS 4U
# define  GP16C4Tn_CHMR1_OUTPUT_CH1MOD_POSE 6U
# define  GP16C4Tn_CHMR1_OUTPUT_CH1MOD_MSK  BITS(GP16C4Tn_CHMR1_OUTPUT_CH1MOD_POSS, GP16C4Tn_CHMR1_OUTPUT_CH1MOD_POSE)
# define  GP16C4Tn_CHMR1_OUTPUT_CH1MOD      GP16C4Tn_CHMR1_OUTPUT_CH1MOD_MSK

# define  GP16C4Tn_CHMR1_OUTPUT_CH1PEN_POS 3U
# define  GP16C4Tn_CHMR1_OUTPUT_CH1PEN_MSK BIT(GP16C4Tn_CHMR1_OUTPUT_CH1PEN_POS)
# define  GP16C4Tn_CHMR1_OUTPUT_CH1PEN     GP16C4Tn_CHMR1_OUTPUT_CH1PEN_MSK

# define  GP16C4Tn_CHMR1_OUTPUT_CH1FEN_POS 2U
# define  GP16C4Tn_CHMR1_OUTPUT_CH1FEN_MSK BIT(GP16C4Tn_CHMR1_OUTPUT_CH1FEN_POS)
# define  GP16C4Tn_CHMR1_OUTPUT_CH1FEN     GP16C4Tn_CHMR1_OUTPUT_CH1FEN_MSK

# define  GP16C4Tn_CHMR1_OUTPUT_CC1SSEL_POSS 0U
# define  GP16C4Tn_CHMR1_OUTPUT_CC1SSEL_POSE 1U
# define  GP16C4Tn_CHMR1_OUTPUT_CC1SSEL_MSK  BITS(GP16C4Tn_CHMR1_OUTPUT_CC1SSEL_POSS, GP16C4Tn_CHMR1_OUTPUT_CC1SSEL_POSE)
# define  GP16C4Tn_CHMR1_OUTPUT_CC1SSEL      GP16C4Tn_CHMR1_OUTPUT_CC1SSEL_MSK

/****************** Bit definition for GP16C4Tn_CHMR1_INPUT register ************************/

# define  GP16C4Tn_CHMR1_INPUT_I2FLT_POSS 12U
# define  GP16C4Tn_CHMR1_INPUT_I2FLT_POSE 15U
# define  GP16C4Tn_CHMR1_INPUT_I2FLT_MSK  BITS(GP16C4Tn_CHMR1_INPUT_I2FLT_POSS, GP16C4Tn_CHMR1_INPUT_I2FLT_POSE)
# define  GP16C4Tn_CHMR1_INPUT_I2FLT      GP16C4Tn_CHMR1_INPUT_I2FLT_MSK

# define  GP16C4Tn_CHMR1_INPUT_I2PRES_POSS 10U
# define  GP16C4Tn_CHMR1_INPUT_I2PRES_POSE 11U
# define  GP16C4Tn_CHMR1_INPUT_I2PRES_MSK  BITS(GP16C4Tn_CHMR1_INPUT_I2PRES_POSS, GP16C4Tn_CHMR1_INPUT_I2PRES_POSE)
# define  GP16C4Tn_CHMR1_INPUT_I2PRES      GP16C4Tn_CHMR1_INPUT_I2PRES_MSK

# define  GP16C4Tn_CHMR1_INPUT_CC2SSEL_POSS 8U
# define  GP16C4Tn_CHMR1_INPUT_CC2SSEL_POSE 9U
# define  GP16C4Tn_CHMR1_INPUT_CC2SSEL_MSK  BITS(GP16C4Tn_CHMR1_INPUT_CC2SSEL_POSS, GP16C4Tn_CHMR1_INPUT_CC2SSEL_POSE)
# define  GP16C4Tn_CHMR1_INPUT_CC2SSEL      GP16C4Tn_CHMR1_INPUT_CC2SSEL_MSK

# define  GP16C4Tn_CHMR1_INPUT_I1FLT_POSS 4U
# define  GP16C4Tn_CHMR1_INPUT_I1FLT_POSE 7U
# define  GP16C4Tn_CHMR1_INPUT_I1FLT_MSK  BITS(GP16C4Tn_CHMR1_INPUT_I1FLT_POSS, GP16C4Tn_CHMR1_INPUT_I1FLT_POSE)
# define  GP16C4Tn_CHMR1_INPUT_I1FLT      GP16C4Tn_CHMR1_INPUT_I1FLT_MSK

# define  GP16C4Tn_CHMR1_INPUT_I1PRES_POSS 2U
# define  GP16C4Tn_CHMR1_INPUT_I1PRES_POSE 3U
# define  GP16C4Tn_CHMR1_INPUT_I1PRES_MSK  BITS(GP16C4Tn_CHMR1_INPUT_I1PRES_POSS, GP16C4Tn_CHMR1_INPUT_I1PRES_POSE)
# define  GP16C4Tn_CHMR1_INPUT_I1PRES      GP16C4Tn_CHMR1_INPUT_I1PRES_MSK

# define  GP16C4Tn_CHMR1_INPUT_CC1SSEL_POSS 0U
# define  GP16C4Tn_CHMR1_INPUT_CC1SSEL_POSE 1U
# define  GP16C4Tn_CHMR1_INPUT_CC1SSEL_MSK  BITS(GP16C4Tn_CHMR1_INPUT_CC1SSEL_POSS, GP16C4Tn_CHMR1_INPUT_CC1SSEL_POSE)
# define  GP16C4Tn_CHMR1_INPUT_CC1SSEL      GP16C4Tn_CHMR1_INPUT_CC1SSEL_MSK

/****************** Bit definition for GP16C4Tn_CHMR2_OUTPUT register ************************/

# define  GP16C4Tn_CHMR2_OUTPUT_CH4OCLREN_POS 15U
# define  GP16C4Tn_CHMR2_OUTPUT_CH4OCLREN_MSK BIT(GP16C4Tn_CHMR2_OUTPUT_CH4OCLREN_POS)
# define  GP16C4Tn_CHMR2_OUTPUT_CH4OCLREN     GP16C4Tn_CHMR2_OUTPUT_CH4OCLREN_MSK

# define  GP16C4Tn_CHMR2_OUTPUT_CH4MOD_POSS 12U
# define  GP16C4Tn_CHMR2_OUTPUT_CH4MOD_POSE 14U
# define  GP16C4Tn_CHMR2_OUTPUT_CH4MOD_MSK  BITS(GP16C4Tn_CHMR2_OUTPUT_CH4MOD_POSS, GP16C4Tn_CHMR2_OUTPUT_CH4MOD_POSE)
# define  GP16C4Tn_CHMR2_OUTPUT_CH4MOD      GP16C4Tn_CHMR2_OUTPUT_CH4MOD_MSK

# define  GP16C4Tn_CHMR2_OUTPUT_CH4PEN_POS 11U
# define  GP16C4Tn_CHMR2_OUTPUT_CH4PEN_MSK BIT(GP16C4Tn_CHMR2_OUTPUT_CH4PEN_POS)
# define  GP16C4Tn_CHMR2_OUTPUT_CH4PEN     GP16C4Tn_CHMR2_OUTPUT_CH4PEN_MSK

# define  GP16C4Tn_CHMR2_OUTPUT_CH4FEN_POS 10U
# define  GP16C4Tn_CHMR2_OUTPUT_CH4FEN_MSK BIT(GP16C4Tn_CHMR2_OUTPUT_CH4FEN_POS)
# define  GP16C4Tn_CHMR2_OUTPUT_CH4FEN     GP16C4Tn_CHMR2_OUTPUT_CH4FEN_MSK

# define  GP16C4Tn_CHMR2_OUTPUT_CC4SSEL_POSS 8U
# define  GP16C4Tn_CHMR2_OUTPUT_CC4SSEL_POSE 9U
# define  GP16C4Tn_CHMR2_OUTPUT_CC4SSEL_MSK  BITS(GP16C4Tn_CHMR2_OUTPUT_CC4SSEL_POSS, GP16C4Tn_CHMR2_OUTPUT_CC4SSEL_POSE)
# define  GP16C4Tn_CHMR2_OUTPUT_CC4SSEL      GP16C4Tn_CHMR2_OUTPUT_CC4SSEL_MSK

# define  GP16C4Tn_CHMR2_OUTPUT_CH3OCLREN_POS 7U
# define  GP16C4Tn_CHMR2_OUTPUT_CH3OCLREN_MSK BIT(GP16C4Tn_CHMR2_OUTPUT_CH3OCLREN_POS)
# define  GP16C4Tn_CHMR2_OUTPUT_CH3OCLREN     GP16C4Tn_CHMR2_OUTPUT_CH3OCLREN_MSK

# define  GP16C4Tn_CHMR2_OUTPUT_CH3MOD_POSS 4U
# define  GP16C4Tn_CHMR2_OUTPUT_CH3MOD_POSE 6U
# define  GP16C4Tn_CHMR2_OUTPUT_CH3MOD_MSK  BITS(GP16C4Tn_CHMR2_OUTPUT_CH3MOD_POSS, GP16C4Tn_CHMR2_OUTPUT_CH3MOD_POSE)
# define  GP16C4Tn_CHMR2_OUTPUT_CH3MOD      GP16C4Tn_CHMR2_OUTPUT_CH3MOD_MSK

# define  GP16C4Tn_CHMR2_OUTPUT_CH3PEN_POS 3U
# define  GP16C4Tn_CHMR2_OUTPUT_CH3PEN_MSK BIT(GP16C4Tn_CHMR2_OUTPUT_CH3PEN_POS)
# define  GP16C4Tn_CHMR2_OUTPUT_CH3PEN     GP16C4Tn_CHMR2_OUTPUT_CH3PEN_MSK

# define  GP16C4Tn_CHMR2_OUTPUT_CH3FEN_POS 2U
# define  GP16C4Tn_CHMR2_OUTPUT_CH3FEN_MSK BIT(GP16C4Tn_CHMR2_OUTPUT_CH3FEN_POS)
# define  GP16C4Tn_CHMR2_OUTPUT_CH3FEN     GP16C4Tn_CHMR2_OUTPUT_CH3FEN_MSK

# define  GP16C4Tn_CHMR2_OUTPUT_CC3SSEL_POSS 0U
# define  GP16C4Tn_CHMR2_OUTPUT_CC3SSEL_POSE 1U
# define  GP16C4Tn_CHMR2_OUTPUT_CC3SSEL_MSK  BITS(GP16C4Tn_CHMR2_OUTPUT_CC3SSEL_POSS, GP16C4Tn_CHMR2_OUTPUT_CC3SSEL_POSE)
# define  GP16C4Tn_CHMR2_OUTPUT_CC3SSEL      GP16C4Tn_CHMR2_OUTPUT_CC3SSEL_MSK

/****************** Bit definition for GP16C4Tn_CHMR2_INPUT register ************************/

# define  GP16C4Tn_CHMR2_INPUT_I4FLT_POSS 12U
# define  GP16C4Tn_CHMR2_INPUT_I4FLT_POSE 15U
# define  GP16C4Tn_CHMR2_INPUT_I4FLT_MSK  BITS(GP16C4Tn_CHMR2_INPUT_I4FLT_POSS, GP16C4Tn_CHMR2_INPUT_I4FLT_POSE)
# define  GP16C4Tn_CHMR2_INPUT_I4FLT      GP16C4Tn_CHMR2_INPUT_I4FLT_MSK

# define  GP16C4Tn_CHMR2_INPUT_I4PRES_POSS 10U
# define  GP16C4Tn_CHMR2_INPUT_I4PRES_POSE 11U
# define  GP16C4Tn_CHMR2_INPUT_I4PRES_MSK  BITS(GP16C4Tn_CHMR2_INPUT_I4PRES_POSS, GP16C4Tn_CHMR2_INPUT_I4PRES_POSE)
# define  GP16C4Tn_CHMR2_INPUT_I4PRES      GP16C4Tn_CHMR2_INPUT_I4PRES_MSK

# define  GP16C4Tn_CHMR2_INPUT_CC4SSEL_POSS 8U
# define  GP16C4Tn_CHMR2_INPUT_CC4SSEL_POSE 9U
# define  GP16C4Tn_CHMR2_INPUT_CC4SSEL_MSK  BITS(GP16C4Tn_CHMR2_INPUT_CC4SSEL_POSS, GP16C4Tn_CHMR2_INPUT_CC4SSEL_POSE)
# define  GP16C4Tn_CHMR2_INPUT_CC4SSEL      GP16C4Tn_CHMR2_INPUT_CC4SSEL_MSK

# define  GP16C4Tn_CHMR2_INPUT_I3FLT_POSS 4U
# define  GP16C4Tn_CHMR2_INPUT_I3FLT_POSE 7U
# define  GP16C4Tn_CHMR2_INPUT_I3FLT_MSK  BITS(GP16C4Tn_CHMR2_INPUT_I3FLT_POSS, GP16C4Tn_CHMR2_INPUT_I3FLT_POSE)
# define  GP16C4Tn_CHMR2_INPUT_I3FLT      GP16C4Tn_CHMR2_INPUT_I3FLT_MSK

# define  GP16C4Tn_CHMR2_INPUT_I3PRES_POSS 2U
# define  GP16C4Tn_CHMR2_INPUT_I3PRES_POSE 3U
# define  GP16C4Tn_CHMR2_INPUT_I3PRES_MSK  BITS(GP16C4Tn_CHMR2_INPUT_I3PRES_POSS, GP16C4Tn_CHMR2_INPUT_I3PRES_POSE)
# define  GP16C4Tn_CHMR2_INPUT_I3PRES      GP16C4Tn_CHMR2_INPUT_I3PRES_MSK

# define  GP16C4Tn_CHMR2_INPUT_CC3SSEL_POSS 0U
# define  GP16C4Tn_CHMR2_INPUT_CC3SSEL_POSE 1U
# define  GP16C4Tn_CHMR2_INPUT_CC3SSEL_MSK  BITS(GP16C4Tn_CHMR2_INPUT_CC3SSEL_POSS, GP16C4Tn_CHMR2_INPUT_CC3SSEL_POSE)
# define  GP16C4Tn_CHMR2_INPUT_CC3SSEL      GP16C4Tn_CHMR2_INPUT_CC3SSEL_MSK

/****************** Bit definition for GP16C4Tn_CCEP register ************************/

#define  GP16C4Tn_CCEP_CC4NPOL_POS  15U
#define  GP16C4Tn_CCEP_CC4NPOL_MSK  BIT(GP16C4Tn_CCEP_CC4NPOL_POS)
#define  GP16C4Tn_CCEP_CC4NPOL      GP16C4Tn_CCEP_CC4NPOL_MSK

#define  GP16C4Tn_CCEP_CC4POL_POS  13U
#define  GP16C4Tn_CCEP_CC4POL_MSK  BIT(GP16C4Tn_CCEP_CC4POL_POS)
#define  GP16C4Tn_CCEP_CC4POL      GP16C4Tn_CCEP_CC4POL_MSK

#define  GP16C4Tn_CCEP_CC4EN_POS  12U
#define  GP16C4Tn_CCEP_CC4EN_MSK  BIT(GP16C4Tn_CCEP_CC4EN_POS)
#define  GP16C4Tn_CCEP_CC4EN      GP16C4Tn_CCEP_CC4EN_MSK

#define  GP16C4Tn_CCEP_CC3NPOL_POS  11U
#define  GP16C4Tn_CCEP_CC3NPOL_MSK  BIT(GP16C4Tn_CCEP_CC3NPOL_POS)
#define  GP16C4Tn_CCEP_CC3NPOL      GP16C4Tn_CCEP_CC3NPOL_MSK

#define  GP16C4Tn_CCEP_CC3POL_POS  9U
#define  GP16C4Tn_CCEP_CC3POL_MSK  BIT(GP16C4Tn_CCEP_CC3POL_POS)
#define  GP16C4Tn_CCEP_CC3POL      GP16C4Tn_CCEP_CC3POL_MSK

#define  GP16C4Tn_CCEP_CC3EN_POS  8U
#define  GP16C4Tn_CCEP_CC3EN_MSK  BIT(GP16C4Tn_CCEP_CC3EN_POS)
#define  GP16C4Tn_CCEP_CC3EN      GP16C4Tn_CCEP_CC3EN_MSK

#define  GP16C4Tn_CCEP_CC2NPOL_POS  7U
#define  GP16C4Tn_CCEP_CC2NPOL_MSK  BIT(GP16C4Tn_CCEP_CC2NPOL_POS)
#define  GP16C4Tn_CCEP_CC2NPOL      GP16C4Tn_CCEP_CC2NPOL_MSK

#define  GP16C4Tn_CCEP_CC2POL_POS  5U
#define  GP16C4Tn_CCEP_CC2POL_MSK  BIT(GP16C4Tn_CCEP_CC2POL_POS)
#define  GP16C4Tn_CCEP_CC2POL      GP16C4Tn_CCEP_CC2POL_MSK

#define  GP16C4Tn_CCEP_CC2EN_POS  4U
#define  GP16C4Tn_CCEP_CC2EN_MSK  BIT(GP16C4Tn_CCEP_CC2EN_POS)
#define  GP16C4Tn_CCEP_CC2EN      GP16C4Tn_CCEP_CC2EN_MSK

#define  GP16C4Tn_CCEP_CC1NPOL_POS  3U
#define  GP16C4Tn_CCEP_CC1NPOL_MSK  BIT(GP16C4Tn_CCEP_CC1NPOL_POS)
#define  GP16C4Tn_CCEP_CC1NPOL      GP16C4Tn_CCEP_CC1NPOL_MSK

#define  GP16C4Tn_CCEP_CC1POL_POS  1U
#define  GP16C4Tn_CCEP_CC1POL_MSK  BIT(GP16C4Tn_CCEP_CC1POL_POS)
#define  GP16C4Tn_CCEP_CC1POL      GP16C4Tn_CCEP_CC1POL_MSK

#define  GP16C4Tn_CCEP_CC1EN_POS  0U
#define  GP16C4Tn_CCEP_CC1EN_MSK  BIT(GP16C4Tn_CCEP_CC1EN_POS)
#define  GP16C4Tn_CCEP_CC1EN      GP16C4Tn_CCEP_CC1EN_MSK

/****************** Bit definition for GP16C4Tn_COUNT register ************************/

#define  GP16C4Tn_COUNT_CNTV_POSS  0U
#define  GP16C4Tn_COUNT_CNTV_POSE  15U
#define  GP16C4Tn_COUNT_CNTV_MSK   BITS(GP16C4Tn_COUNT_CNTV_POSS,GP16C4Tn_COUNT_CNTV_POSE)
#define  GP16C4Tn_COUNT_CNTV       GP16C4Tn_COUNT_CNTV_MSK

/****************** Bit definition for GP16C4Tn_PRES register ************************/

#define  GP16C4Tn_PRES_PSCV_POSS  0U
#define  GP16C4Tn_PRES_PSCV_POSE  15U
#define  GP16C4Tn_PRES_PSCV_MSK   BITS(GP16C4Tn_PRES_PSCV_POSS,GP16C4Tn_PRES_PSCV_POSE)
#define  GP16C4Tn_PRES_PSCV       GP16C4Tn_PRES_PSCV_MSK

/****************** Bit definition for GP16C4Tn_AR register ************************/

#define  GP16C4Tn_AR_ARV_POSS  0U
#define  GP16C4Tn_AR_ARV_POSE  15U
#define  GP16C4Tn_AR_ARV_MSK   BITS(GP16C4Tn_AR_ARV_POSS,GP16C4Tn_AR_ARV_POSE)
#define  GP16C4Tn_AR_ARV       GP16C4Tn_AR_ARV_MSK

/****************** Bit definition for GP16C4Tn_CCVAL1 register ************************/

#define  GP16C4Tn_CCVAL1_CCRV1_POSS  0U
#define  GP16C4Tn_CCVAL1_CCRV1_POSE  15U
#define  GP16C4Tn_CCVAL1_CCRV1_MSK   BITS(GP16C4Tn_CCVAL1_CCRV1_POSS,GP16C4Tn_CCVAL1_CCRV1_POSE)
#define  GP16C4Tn_CCVAL1_CCRV1       GP16C4Tn_CCVAL1_CCRV1_MSK

/****************** Bit definition for GP16C4Tn_CCVAL2 register ************************/

#define  GP16C4Tn_CCVAL2_CCRV2_POSS  0U
#define  GP16C4Tn_CCVAL2_CCRV2_POSE  15U
#define  GP16C4Tn_CCVAL2_CCRV2_MSK   BITS(GP16C4Tn_CCVAL2_CCRV2_POSS,GP16C4Tn_CCVAL2_CCRV2_POSE)
#define  GP16C4Tn_CCVAL2_CCRV2       GP16C4Tn_CCVAL2_CCRV2_MSK

/****************** Bit definition for GP16C4Tn_CCVAL3 register ************************/

#define  GP16C4Tn_CCVAL3_CCRV3_POSS  0U
#define  GP16C4Tn_CCVAL3_CCRV3_POSE  15U
#define  GP16C4Tn_CCVAL3_CCRV3_MSK   BITS(GP16C4Tn_CCVAL3_CCRV3_POSS,GP16C4Tn_CCVAL3_CCRV3_POSE)
#define  GP16C4Tn_CCVAL3_CCRV3       GP16C4Tn_CCVAL3_CCRV3_MSK

/****************** Bit definition for GP16C4Tn_CCVAL4 register ************************/

#define  GP16C4Tn_CCVAL4_CCRV4_POSS  0U
#define  GP16C4Tn_CCVAL4_CCRV4_POSE  15U
#define  GP16C4Tn_CCVAL4_CCRV4_MSK   BITS(GP16C4Tn_CCVAL4_CCRV4_POSS,GP16C4Tn_CCVAL4_CCRV4_POSE)
#define  GP16C4Tn_CCVAL4_CCRV4       GP16C4Tn_CCVAL4_CCRV4_MSK

/****************** Bit definition for GP16C4Tn_DMAEN register ************************/

#define  GP16C4Tn_DMAEN_TRGI_POS  6U
#define  GP16C4Tn_DMAEN_TRGI_MSK  BIT(GP16C4Tn_DMAEN_TRGI_POS)
#define  GP16C4Tn_DMAEN_TRGI      GP16C4Tn_DMAEN_TRGI_MSK

#define  GP16C4Tn_DMAEN_CH4_POS  4U
#define  GP16C4Tn_DMAEN_CH4_MSK  BIT(GP16C4Tn_DMAEN_CH4_POS)
#define  GP16C4Tn_DMAEN_CH4      GP16C4Tn_DMAEN_CH4_MSK

#define  GP16C4Tn_DMAEN_CH3_POS  3U
#define  GP16C4Tn_DMAEN_CH3_MSK  BIT(GP16C4Tn_DMAEN_CH3_POS)
#define  GP16C4Tn_DMAEN_CH3      GP16C4Tn_DMAEN_CH3_MSK

#define  GP16C4Tn_DMAEN_CH2_POS  2U
#define  GP16C4Tn_DMAEN_CH2_MSK  BIT(GP16C4Tn_DMAEN_CH2_POS)
#define  GP16C4Tn_DMAEN_CH2      GP16C4Tn_DMAEN_CH2_MSK

#define  GP16C4Tn_DMAEN_CH1_POS  1U
#define  GP16C4Tn_DMAEN_CH1_MSK  BIT(GP16C4Tn_DMAEN_CH1_POS)
#define  GP16C4Tn_DMAEN_CH1      GP16C4Tn_DMAEN_CH1_MSK

#define  GP16C4Tn_DMAEN_UPD_POS  0U
#define  GP16C4Tn_DMAEN_UPD_MSK  BIT(GP16C4Tn_DMAEN_UPD_POS)
#define  GP16C4Tn_DMAEN_UPD      GP16C4Tn_DMAEN_UPD_MSK

/****************** Bit definition for GP16C4Tn_OPTR register ************************/

# define  GP16C4Tn_OPTR_ETR_RMP_POSS 8U
# define  GP16C4Tn_OPTR_ETR_RMP_POSE 9U
# define  GP16C4Tn_OPTR_ETR_RMP_MSK  BITS(GP16C4Tn_OPTR_ETR_RMP_POSS, GP16C4Tn_OPTR_ETR_RMP_POSE)
# define  GP16C4Tn_OPTR_ETR_RMP      GP16C4Tn_OPTR_ETR_RMP_MSK

# define  GP16C4Tn_OPTR_CH4_RMP_POSS 6U
# define  GP16C4Tn_OPTR_CH4_RMP_POSE 7U
# define  GP16C4Tn_OPTR_CH4_RMP_MSK  BITS(GP16C4Tn_OPTR_CH4_RMP_POSS, GP16C4Tn_OPTR_CH4_RMP_POSE)
# define  GP16C4Tn_OPTR_CH4_RMP      GP16C4Tn_OPTR_CH4_RMP_MSK

# define  GP16C4Tn_OPTR_CH3_RMP_POSS 4U
# define  GP16C4Tn_OPTR_CH3_RMP_POSE 5U
# define  GP16C4Tn_OPTR_CH3_RMP_MSK  BITS(GP16C4Tn_OPTR_CH3_RMP_POSS, GP16C4Tn_OPTR_CH3_RMP_POSE)
# define  GP16C4Tn_OPTR_CH3_RMP      GP16C4Tn_OPTR_CH3_RMP_MSK

# define  GP16C4Tn_OPTR_CH2_RMP_POSS 2U
# define  GP16C4Tn_OPTR_CH2_RMP_POSE 3U
# define  GP16C4Tn_OPTR_CH2_RMP_MSK  BITS(GP16C4Tn_OPTR_CH2_RMP_POSS, GP16C4Tn_OPTR_CH2_RMP_POSE)
# define  GP16C4Tn_OPTR_CH2_RMP      GP16C4Tn_OPTR_CH2_RMP_MSK

# define  GP16C4Tn_OPTR_CH1_RMP_POSS 0U
# define  GP16C4Tn_OPTR_CH1_RMP_POSE 1U
# define  GP16C4Tn_OPTR_CH1_RMP_MSK  BITS(GP16C4Tn_OPTR_CH1_RMP_POSS, GP16C4Tn_OPTR_CH1_RMP_POSE)
# define  GP16C4Tn_OPTR_CH1_RMP      GP16C4Tn_OPTR_CH1_RMP_MSK

typedef struct
{
  __IO uint32_t CON1;                     // 0x000
  __IO uint32_t CON2;                     // 0x004
  __IO uint32_t SMCON;                    // 0x008
  __O  uint32_t IER;                      // 0x00c
  __O  uint32_t IDR;                      // 0x010
  __I  uint32_t IVS;                      // 0x014
  __I  uint32_t RIF;                      // 0x018
  __I  uint32_t IFM;                      // 0x01c
  __O  uint32_t ICR;                      // 0x020
  __O  uint32_t SGE;                      // 0x024
  __IO uint32_t CHMR1;                    // 0x028
  __IO uint32_t CHMR2;                    // 0x02c
  __IO uint32_t CCEP;                     // 0x030
  __IO uint32_t COUNT;                    // 0x034
  __IO uint32_t PRES;                     // 0x038
  __IO uint32_t AR;                       // 0x03c
  __IO uint32_t RESERVED0;                // 0x040
  __IO uint32_t CCVAL1;                   // 0x044
  __IO uint32_t CCVAL2;                   // 0x048
  __IO uint32_t CCVAL3;                   // 0x04c
  __IO uint32_t CCVAL4;                   // 0x050
  __IO uint32_t RESERVED1;                // 0x054
  __IO uint32_t DMAEN;                    // 0x058
  __IO uint32_t OPTR;                     // 0x05c
} GP16C4Tn_TypeDef;


#endif
