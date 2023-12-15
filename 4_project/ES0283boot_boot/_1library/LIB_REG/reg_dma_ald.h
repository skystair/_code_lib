/**********************************************************************************
 *
 * @file    reg_dma.h
 * @brief   DMA Head File
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

#ifndef __DMA_H__
#define __DMA_H__


/******************************************************************************/
/*              Device Specific Peripheral registers structures               */
/******************************************************************************/

/*  Support for anonymous structures and unions.  */
#pragma anon_unions

/****************** Bit definition for DMA_STATUS register ************************/

# define  DMA_STATUS_CHNLS_MINUS1_POSS 16U
# define  DMA_STATUS_CHNLS_MINUS1_POSE 20U
# define  DMA_STATUS_CHNLS_MINUS1_MSK  BITS(DMA_STATUS_CHNLS_MINUS1_POSS, DMA_STATUS_CHNLS_MINUS1_POSE)
# define  DMA_STATUS_CHNLS_MINUS1      DMA_STATUS_CHNLS_MINUS1_MSK

# define  DMA_STATUS_STATUS_POSS 4U
# define  DMA_STATUS_STATUS_POSE 7U
# define  DMA_STATUS_STATUS_MSK  BITS(DMA_STATUS_STATUS_POSS, DMA_STATUS_STATUS_POSE)
# define  DMA_STATUS_STATUS      DMA_STATUS_STATUS_MSK

# define  DMA_STATUS_MASTER_ENABLE_POS 0U
# define  DMA_STATUS_MASTER_ENABLE_MSK BIT(DMA_STATUS_MASTER_ENABLE_POS)
# define  DMA_STATUS_MASTER_ENABLE     DMA_STATUS_MASTER_ENABLE_MSK

/****************** Bit definition for DMA_CFG register ************************/

# define  DMA_CFG_CHNL_PROT_CTRL_POSS 5U
# define  DMA_CFG_CHNL_PROT_CTRL_POSE 7U
# define  DMA_CFG_CHNL_PROT_CTRL_MSK  BITS(DMA_CFG_CHNL_PROT_CTRL_POSS, DMA_CFG_CHNL_PROT_CTRL_POSE)
# define  DMA_CFG_CHNL_PROT_CTRL      DMA_CFG_CHNL_PROT_CTRL_MSK

# define  DMA_CFG_MASTER_ENABLE_POS 0U
# define  DMA_CFG_MASTER_ENABLE_MSK BIT(DMA_CFG_MASTER_ENABLE_POS)
# define  DMA_CFG_MASTER_ENABLE     DMA_CFG_MASTER_ENABLE_MSK

/****************** Bit definition for DMA_CHWAITSTATUS register ************************/

# define  DMA_CHWAITSTATUS_DMA_WAITONREQ_STATUS_POSS 0U
# define  DMA_CHWAITSTATUS_DMA_WAITONREQ_STATUS_POSE 5U
# define  DMA_CHWAITSTATUS_DMA_WAITONREQ_STATUS_MSK  BITS(DMA_CHWAITSTATUS_DMA_WAITONREQ_STATUS_POSS, DMA_CHWAITSTATUS_DMA_WAITONREQ_STATUS_POSE)
# define  DMA_CHWAITSTATUS_DMA_WAITONREQ_STATUS      DMA_CHWAITSTATUS_DMA_WAITONREQ_STATUS_MSK

/****************** Bit definition for DMA_CHSWREQ register ************************/

# define  DMA_CHSWREQ_CHSWREQ_POSS 0U
# define  DMA_CHSWREQ_CHSWREQ_POSE 5U
# define  DMA_CHSWREQ_CHSWREQ_MSK  BITS(DMA_CHSWREQ_CHSWREQ_POSS, DMA_CHSWREQ_CHSWREQ_POSE)
# define  DMA_CHSWREQ_CHSWREQ      DMA_CHSWREQ_CHSWREQ_MSK

/****************** Bit definition for DMA_CHUSEBURSTSET register ************************/

# define  DMA_CHUSEBURSTSET_CHNL_USEBURST_SET_POSS 0U
# define  DMA_CHUSEBURSTSET_CHNL_USEBURST_SET_POSE 5U
# define  DMA_CHUSEBURSTSET_CHNL_USEBURST_SET_MSK  BITS(DMA_CHUSEBURSTSET_CHNL_USEBURST_SET_POSS, DMA_CHUSEBURSTSET_CHNL_USEBURST_SET_POSE)
# define  DMA_CHUSEBURSTSET_CHNL_USEBURST_SET      DMA_CHUSEBURSTSET_CHNL_USEBURST_SET_MSK

/****************** Bit definition for DMA_CHUSEBURSTCLR register ************************/

# define  DMA_CHUSEBURSTCLR_CHNL_USEBURST_CLR_POSS 0U
# define  DMA_CHUSEBURSTCLR_CHNL_USEBURST_CLR_POSE 5U
# define  DMA_CHUSEBURSTCLR_CHNL_USEBURST_CLR_MSK  BITS(DMA_CHUSEBURSTCLR_CHNL_USEBURST_CLR_POSS, DMA_CHUSEBURSTCLR_CHNL_USEBURST_CLR_POSE)
# define  DMA_CHUSEBURSTCLR_CHNL_USEBURST_CLR      DMA_CHUSEBURSTCLR_CHNL_USEBURST_CLR_MSK

/****************** Bit definition for DMA_CHREQMASKSET register ************************/

# define  DMA_CHREQMASKSET_CHNL_REQ_MASK_SET_POSS 0U
# define  DMA_CHREQMASKSET_CHNL_REQ_MASK_SET_POSE 5U
# define  DMA_CHREQMASKSET_CHNL_REQ_MASK_SET_MSK  BITS(DMA_CHREQMASKSET_CHNL_REQ_MASK_SET_POSS, DMA_CHREQMASKSET_CHNL_REQ_MASK_SET_POSE)
# define  DMA_CHREQMASKSET_CHNL_REQ_MASK_SET      DMA_CHREQMASKSET_CHNL_REQ_MASK_SET_MSK

/****************** Bit definition for DMA_CHREQMASKCLR register ************************/

# define  DMA_CHREQMASKCLR_CHNL_REQ_MASK_CLR_POSS 0U
# define  DMA_CHREQMASKCLR_CHNL_REQ_MASK_CLR_POSE 5U
# define  DMA_CHREQMASKCLR_CHNL_REQ_MASK_CLR_MSK  BITS(DMA_CHREQMASKCLR_CHNL_REQ_MASK_CLR_POSS, DMA_CHREQMASKCLR_CHNL_REQ_MASK_CLR_POSE)
# define  DMA_CHREQMASKCLR_CHNL_REQ_MASK_CLR      DMA_CHREQMASKCLR_CHNL_REQ_MASK_CLR_MSK

/****************** Bit definition for DMA_CHENSET register ************************/

# define  DMA_CHENSET_CHNL_ENABLE_SET_POSS 0U
# define  DMA_CHENSET_CHNL_ENABLE_SET_POSE 5U
# define  DMA_CHENSET_CHNL_ENABLE_SET_MSK  BITS(DMA_CHENSET_CHNL_ENABLE_SET_POSS, DMA_CHENSET_CHNL_ENABLE_SET_POSE)
# define  DMA_CHENSET_CHNL_ENABLE_SET      DMA_CHENSET_CHNL_ENABLE_SET_MSK

/****************** Bit definition for DMA_CHENCLR register ************************/

# define  DMA_CHENCLR_CHNL_ENABLE_CLR_POSS 0U
# define  DMA_CHENCLR_CHNL_ENABLE_CLR_POSE 5U
# define  DMA_CHENCLR_CHNL_ENABLE_CLR_MSK  BITS(DMA_CHENCLR_CHNL_ENABLE_CLR_POSS, DMA_CHENCLR_CHNL_ENABLE_CLR_POSE)
# define  DMA_CHENCLR_CHNL_ENABLE_CLR      DMA_CHENCLR_CHNL_ENABLE_CLR_MSK

/****************** Bit definition for DMA_CHPRIALTSET register ************************/

# define  DMA_CHPRIALTSET_CHNL_PRI_ALT_SET_POSS 0U
# define  DMA_CHPRIALTSET_CHNL_PRI_ALT_SET_POSE 5U
# define  DMA_CHPRIALTSET_CHNL_PRI_ALT_SET_MSK  BITS(DMA_CHPRIALTSET_CHNL_PRI_ALT_SET_POSS, DMA_CHPRIALTSET_CHNL_PRI_ALT_SET_POSE)
# define  DMA_CHPRIALTSET_CHNL_PRI_ALT_SET      DMA_CHPRIALTSET_CHNL_PRI_ALT_SET_MSK

/****************** Bit definition for DMA_CHPRIALTCLR register ************************/

# define  DMA_CHPRIALTCLR_CHNL_PRI_ALT_CLR_POSS 0U
# define  DMA_CHPRIALTCLR_CHNL_PRI_ALT_CLR_POSE 5U
# define  DMA_CHPRIALTCLR_CHNL_PRI_ALT_CLR_MSK  BITS(DMA_CHPRIALTCLR_CHNL_PRI_ALT_CLR_POSS, DMA_CHPRIALTCLR_CHNL_PRI_ALT_CLR_POSE)
# define  DMA_CHPRIALTCLR_CHNL_PRI_ALT_CLR      DMA_CHPRIALTCLR_CHNL_PRI_ALT_CLR_MSK

/****************** Bit definition for DMA_CHPRSET register ************************/

# define  DMA_CHPRSET_CHNL_PRIORITY_SET_POSS 0U
# define  DMA_CHPRSET_CHNL_PRIORITY_SET_POSE 5U
# define  DMA_CHPRSET_CHNL_PRIORITY_SET_MSK  BITS(DMA_CHPRSET_CHNL_PRIORITY_SET_POSS, DMA_CHPRSET_CHNL_PRIORITY_SET_POSE)
# define  DMA_CHPRSET_CHNL_PRIORITY_SET      DMA_CHPRSET_CHNL_PRIORITY_SET_MSK

/****************** Bit definition for DMA_CHPRCLR register ************************/

# define  DMA_CHPRCLR_CHNL_PRIORITY_CLR_POSS 0U
# define  DMA_CHPRCLR_CHNL_PRIORITY_CLR_POSE 5U
# define  DMA_CHPRCLR_CHNL_PRIORITY_CLR_MSK  BITS(DMA_CHPRCLR_CHNL_PRIORITY_CLR_POSS, DMA_CHPRCLR_CHNL_PRIORITY_CLR_POSE)
# define  DMA_CHPRCLR_CHNL_PRIORITY_CLR      DMA_CHPRCLR_CHNL_PRIORITY_CLR_MSK

/****************** Bit definition for DMA_ERRCLR register ************************/

# define  DMA_ERRCLR_ERR_CLR_POS 0U
# define  DMA_ERRCLR_ERR_CLR_MSK  BIT(DMA_ERRCLR_ERR_CLR_POS)
# define  DMA_ERRCLR_ERR_CLR      DMA_ERRCLR_ERR_CLR_MSK

/****************** Bit definition for DMA_IER register ************************/

# define  DMA_IER_CH5DONE_POS 5U
# define  DMA_IER_CH5DONE_MSK BIT(DMA_IER_CH5DONE_POS)
# define  DMA_IER_CH5DONE     DMA_IER_CH5DONE_MSK

# define  DMA_IER_CH4DONE_POS 4U
# define  DMA_IER_CH4DONE_MSK BIT(DMA_IER_CH4DONE_POS)
# define  DMA_IER_CH4DONE     DMA_IER_CH4DONE_MSK

# define  DMA_IER_CH3DONE_POS 3U
# define  DMA_IER_CH3DONE_MSK BIT(DMA_IER_CH3DONE_POS)
# define  DMA_IER_CH3DONE     DMA_IER_CH3DONE_MSK

# define  DMA_IER_CH2DONE_POS 2U
# define  DMA_IER_CH2DONE_MSK BIT(DMA_IER_CH2DONE_POS)
# define  DMA_IER_CH2DONE     DMA_IER_CH2DONE_MSK

# define  DMA_IER_CH1DONE_POS 1U
# define  DMA_IER_CH1DONE_MSK BIT(DMA_IER_CH1DONE_POS)
# define  DMA_IER_CH1DONE     DMA_IER_CH1DONE_MSK

# define  DMA_IER_CH0DONE_POS 0U
# define  DMA_IER_CH0DONE_MSK BIT(DMA_IER_CH0DONE_POS)
# define  DMA_IER_CH0DONE     DMA_IER_CH0DONE_MSK

/****************** Bit definition for DMA_IDR register ************************/

# define  DMA_IDR_CH5DONE_POS 5U
# define  DMA_IDR_CH5DONE_MSK BIT(DMA_IDR_CH5DONE_POS)
# define  DMA_IDR_CH5DONE     DMA_IDR_CH5DONE_MSK

# define  DMA_IDR_CH4DONE_POS 4U
# define  DMA_IDR_CH4DONE_MSK BIT(DMA_IDR_CH4DONE_POS)
# define  DMA_IDR_CH4DONE     DMA_IDR_CH4DONE_MSK

# define  DMA_IDR_CH3DONE_POS 3U
# define  DMA_IDR_CH3DONE_MSK BIT(DMA_IDR_CH3DONE_POS)
# define  DMA_IDR_CH3DONE     DMA_IDR_CH3DONE_MSK

# define  DMA_IDR_CH2DONE_POS 2U
# define  DMA_IDR_CH2DONE_MSK BIT(DMA_IDR_CH2DONE_POS)
# define  DMA_IDR_CH2DONE     DMA_IDR_CH2DONE_MSK

# define  DMA_IDR_CH1DONE_POS 1U
# define  DMA_IDR_CH1DONE_MSK BIT(DMA_IDR_CH1DONE_POS)
# define  DMA_IDR_CH1DONE     DMA_IDR_CH1DONE_MSK

# define  DMA_IDR_CH0DONE_POS 0U
# define  DMA_IDR_CH0DONE_MSK BIT(DMA_IDR_CH0DONE_POS)
# define  DMA_IDR_CH0DONE     DMA_IDR_CH0DONE_MSK

/****************** Bit definition for DMA_IVS register ************************/

# define  DMA_IVS_CH5DONE_POS 5U
# define  DMA_IVS_CH5DONE_MSK BIT(DMA_IVS_CH5DONE_POS)
# define  DMA_IVS_CH5DONE     DMA_IVS_CH5DONE_MSK

# define  DMA_IVS_CH4DONE_POS 4U
# define  DMA_IVS_CH4DONE_MSK BIT(DMA_IVS_CH4DONE_POS)
# define  DMA_IVS_CH4DONE     DMA_IVS_CH4DONE_MSK

# define  DMA_IVS_CH3DONE_POS 3U
# define  DMA_IVS_CH3DONE_MSK BIT(DMA_IVS_CH3DONE_POS)
# define  DMA_IVS_CH3DONE     DMA_IVS_CH3DONE_MSK

# define  DMA_IVS_CH2DONE_POS 2U
# define  DMA_IVS_CH2DONE_MSK BIT(DMA_IVS_CH2DONE_POS)
# define  DMA_IVS_CH2DONE     DMA_IVS_CH2DONE_MSK

# define  DMA_IVS_CH1DONE_POS 1U
# define  DMA_IVS_CH1DONE_MSK BIT(DMA_IVS_CH1DONE_POS)
# define  DMA_IVS_CH1DONE     DMA_IVS_CH1DONE_MSK

# define  DMA_IVS_CH0DONE_POS 0U
# define  DMA_IVS_CH0DONE_MSK BIT(DMA_IVS_CH0DONE_POS)
# define  DMA_IVS_CH0DONE     DMA_IVS_CH0DONE_MSK

/****************** Bit definition for DMA_RIF register ************************/

# define  DMA_RIF_CH5DONE_POS 5U
# define  DMA_RIF_CH5DONE_MSK BIT(DMA_RIF_CH5DONE_POS)
# define  DMA_RIF_CH5DONE     DMA_RIF_CH5DONE_MSK

# define  DMA_RIF_CH4DONE_POS 4U
# define  DMA_RIF_CH4DONE_MSK BIT(DMA_RIF_CH4DONE_POS)
# define  DMA_RIF_CH4DONE     DMA_RIF_CH4DONE_MSK

# define  DMA_RIF_CH3DONE_POS 3U
# define  DMA_RIF_CH3DONE_MSK BIT(DMA_RIF_CH3DONE_POS)
# define  DMA_RIF_CH3DONE     DMA_RIF_CH3DONE_MSK

# define  DMA_RIF_CH2DONE_POS 2U
# define  DMA_RIF_CH2DONE_MSK BIT(DMA_RIF_CH2DONE_POS)
# define  DMA_RIF_CH2DONE     DMA_RIF_CH2DONE_MSK

# define  DMA_RIF_CH1DONE_POS 1U
# define  DMA_RIF_CH1DONE_MSK BIT(DMA_RIF_CH1DONE_POS)
# define  DMA_RIF_CH1DONE     DMA_RIF_CH1DONE_MSK

# define  DMA_RIF_CH0DONE_POS 0U
# define  DMA_RIF_CH0DONE_MSK BIT(DMA_RIF_CH0DONE_POS)
# define  DMA_RIF_CH0DONE     DMA_RIF_CH0DONE_MSK

/****************** Bit definition for DMA_IFM register ************************/

# define  DMA_IFM_CH5DONE_POS 5U
# define  DMA_IFM_CH5DONE_MSK BIT(DMA_IFM_CH5DONE_POS)
# define  DMA_IFM_CH5DONE     DMA_IFM_CH5DONE_MSK

# define  DMA_IFM_CH4DONE_POS 4U
# define  DMA_IFM_CH4DONE_MSK BIT(DMA_IFM_CH4DONE_POS)
# define  DMA_IFM_CH4DONE     DMA_IFM_CH4DONE_MSK

# define  DMA_IFM_CH3DONE_POS 3U
# define  DMA_IFM_CH3DONE_MSK BIT(DMA_IFM_CH3DONE_POS)
# define  DMA_IFM_CH3DONE     DMA_IFM_CH3DONE_MSK

# define  DMA_IFM_CH2DONE_POS 2U
# define  DMA_IFM_CH2DONE_MSK BIT(DMA_IFM_CH2DONE_POS)
# define  DMA_IFM_CH2DONE     DMA_IFM_CH2DONE_MSK

# define  DMA_IFM_CH1DONE_POS 1U
# define  DMA_IFM_CH1DONE_MSK BIT(DMA_IFM_CH1DONE_POS)
# define  DMA_IFM_CH1DONE     DMA_IFM_CH1DONE_MSK

# define  DMA_IFM_CH0DONE_POS 0U
# define  DMA_IFM_CH0DONE_MSK BIT(DMA_IFM_CH0DONE_POS)
# define  DMA_IFM_CH0DONE     DMA_IFM_CH0DONE_MSK

/****************** Bit definition for DMA_ICR register ************************/

# define  DMA_ICR_CH5DONE_POS 5U
# define  DMA_ICR_CH5DONE_MSK BIT(DMA_ICR_CH5DONE_POS)
# define  DMA_ICR_CH5DONE     DMA_ICR_CH5DONE_MSK

# define  DMA_ICR_CH4DONE_POS 4U
# define  DMA_ICR_CH4DONE_MSK BIT(DMA_ICR_CH4DONE_POS)
# define  DMA_ICR_CH4DONE     DMA_ICR_CH4DONE_MSK

# define  DMA_ICR_CH3DONE_POS 3U
# define  DMA_ICR_CH3DONE_MSK BIT(DMA_ICR_CH3DONE_POS)
# define  DMA_ICR_CH3DONE     DMA_ICR_CH3DONE_MSK

# define  DMA_ICR_CH2DONE_POS 2U
# define  DMA_ICR_CH2DONE_MSK BIT(DMA_ICR_CH2DONE_POS)
# define  DMA_ICR_CH2DONE     DMA_ICR_CH2DONE_MSK

# define  DMA_ICR_CH1DONE_POS 1U
# define  DMA_ICR_CH1DONE_MSK BIT(DMA_ICR_CH1DONE_POS)
# define  DMA_ICR_CH1DONE     DMA_ICR_CH1DONE_MSK

# define  DMA_ICR_CH0DONE_POS 0U
# define  DMA_ICR_CH0DONE_MSK BIT(DMA_ICR_CH0DONE_POS)
# define  DMA_ICR_CH0DONE     DMA_ICR_CH0DONE_MSK

/****************** Bit definition for DMA_CH0_SELCON register ************************/

# define  DMA_CH0_SELCON_MSIGSEL_POSS 0U
# define  DMA_CH0_SELCON_MSIGSEL_POSE 6U
# define  DMA_CH0_SELCON_MSIGSEL_MSK  BITS(DMA_CH0_SELCON_MSIGSEL_POSS, DMA_CH0_SELCON_MSIGSEL_POSE)
# define  DMA_CH0_SELCON_MSIGSEL      DMA_CH0_SELCON_MSIGSEL_MSK

/****************** Bit definition for DMA_CH1_SELCON register ************************/

# define  DMA_CH1_SELCON_MSIGSEL_POSS 0U
# define  DMA_CH1_SELCON_MSIGSEL_POSE 6U
# define  DMA_CH1_SELCON_MSIGSEL_MSK  BITS(DMA_CH1_SELCON_MSIGSEL_POSS, DMA_CH1_SELCON_MSIGSEL_POSE)
# define  DMA_CH1_SELCON_MSIGSEL      DMA_CH1_SELCON_MSIGSEL_MSK

/****************** Bit definition for DMA_CH2_SELCON register ************************/

# define  DMA_CH2_SELCON_MSIGSEL_POSS 0U
# define  DMA_CH2_SELCON_MSIGSEL_POSE 6U
# define  DMA_CH2_SELCON_MSIGSEL_MSK  BITS(DMA_CH2_SELCON_MSIGSEL_POSS, DMA_CH2_SELCON_MSIGSEL_POSE)
# define  DMA_CH2_SELCON_MSIGSEL      DMA_CH2_SELCON_MSIGSEL_MSK

/****************** Bit definition for DMA_CH3_SELCON register ************************/

# define  DMA_CH3_SELCON_MSIGSEL_POSS 0U
# define  DMA_CH3_SELCON_MSIGSEL_POSE 6U
# define  DMA_CH3_SELCON_MSIGSEL_MSK  BITS(DMA_CH3_SELCON_MSIGSEL_POSS, DMA_CH3_SELCON_MSIGSEL_POSE)
# define  DMA_CH3_SELCON_MSIGSEL      DMA_CH3_SELCON_MSIGSEL_MSK

/****************** Bit definition for DMA_CH4_SELCON register ************************/

# define  DMA_CH4_SELCON_MSIGSEL_POSS 0U
# define  DMA_CH4_SELCON_MSIGSEL_POSE 6U
# define  DMA_CH4_SELCON_MSIGSEL_MSK  BITS(DMA_CH4_SELCON_MSIGSEL_POSS, DMA_CH4_SELCON_MSIGSEL_POSE)
# define  DMA_CH4_SELCON_MSIGSEL      DMA_CH4_SELCON_MSIGSEL_MSK

/****************** Bit definition for DMA_CH5_SELCON register ************************/

# define  DMA_CH5_SELCON_MSIGSEL_POSS 0U
# define  DMA_CH5_SELCON_MSIGSEL_POSE 6U
# define  DMA_CH5_SELCON_MSIGSEL_MSK  BITS(DMA_CH5_SELCON_MSIGSEL_POSS, DMA_CH5_SELCON_MSIGSEL_POSE)
# define  DMA_CH5_SELCON_MSIGSEL      DMA_CH5_SELCON_MSIGSEL_MSK

/****************** Bit definition for PRI_CH00_SRC_DATA_END_PTR register ************************/

# define  PRI_CH00_SRC_DATA_END_PTR_src_data_end_ptr_POSS 0U
# define  PRI_CH00_SRC_DATA_END_PTR_src_data_end_ptr_POSE 31U
# define  PRI_CH00_SRC_DATA_END_PTR_src_data_end_ptr_MSK  BITS(PRI_CH00_SRC_DATA_END_PTR_src_data_end_ptr_POSS, PRI_CH00_SRC_DATA_END_PTR_src_data_end_ptr_POSE)
# define  PRI_CH00_SRC_DATA_END_PTR_src_data_end_ptr      PRI_CH00_SRC_DATA_END_PTR_src_data_end_ptr_MSK

/****************** Bit definition for PRI_CH00_DST_DATA_END_PTR register ************************/

# define  PRI_CH00_DST_DATA_END_PTR_dst_data_end_ptr_POSS 0U
# define  PRI_CH00_DST_DATA_END_PTR_dst_data_end_ptr_POSE 31U
# define  PRI_CH00_DST_DATA_END_PTR_dst_data_end_ptr_MSK  BITS(PRI_CH00_DST_DATA_END_PTR_dst_data_end_ptr_POSS, PRI_CH00_DST_DATA_END_PTR_dst_data_end_ptr_POSE)
# define  PRI_CH00_DST_DATA_END_PTR_dst_data_end_ptr      PRI_CH00_DST_DATA_END_PTR_dst_data_end_ptr_MSK

/****************** Bit definition for PRI_CH00_CHANNEL_CFG register ************************/

# define  PRI_CH00_CHANNEL_CFG_dst_inc_POSS 30U
# define  PRI_CH00_CHANNEL_CFG_dst_inc_POSE 31U
# define  PRI_CH00_CHANNEL_CFG_dst_inc_MSK  BITS(PRI_CH00_CHANNEL_CFG_dst_inc_POSS, PRI_CH00_CHANNEL_CFG_dst_inc_POSE)
# define  PRI_CH00_CHANNEL_CFG_dst_inc      PRI_CH00_CHANNEL_CFG_dst_inc_MSK

# define  PRI_CH00_CHANNEL_CFG_dst_size_POSS 28U
# define  PRI_CH00_CHANNEL_CFG_dst_size_POSE 29U
# define  PRI_CH00_CHANNEL_CFG_dst_size_MSK  BITS(PRI_CH00_CHANNEL_CFG_dst_size_POSS, PRI_CH00_CHANNEL_CFG_dst_size_POSE)
# define  PRI_CH00_CHANNEL_CFG_dst_size      PRI_CH00_CHANNEL_CFG_dst_size_MSK

# define  PRI_CH00_CHANNEL_CFG_src_inc_POSS 26U
# define  PRI_CH00_CHANNEL_CFG_src_inc_POSE 27U
# define  PRI_CH00_CHANNEL_CFG_src_inc_MSK  BITS(PRI_CH00_CHANNEL_CFG_src_inc_POSS, PRI_CH00_CHANNEL_CFG_src_inc_POSE)
# define  PRI_CH00_CHANNEL_CFG_src_inc      PRI_CH00_CHANNEL_CFG_src_inc_MSK

# define  PRI_CH00_CHANNEL_CFG_src_size_POSS 24U
# define  PRI_CH00_CHANNEL_CFG_src_size_POSE 25U
# define  PRI_CH00_CHANNEL_CFG_src_size_MSK  BITS(PRI_CH00_CHANNEL_CFG_src_size_POSS, PRI_CH00_CHANNEL_CFG_src_size_POSE)
# define  PRI_CH00_CHANNEL_CFG_src_size      PRI_CH00_CHANNEL_CFG_src_size_MSK

# define  PRI_CH00_CHANNEL_CFG_dst_prot_ctrl_POSS 21U
# define  PRI_CH00_CHANNEL_CFG_dst_prot_ctrl_POSE 23U
# define  PRI_CH00_CHANNEL_CFG_dst_prot_ctrl_MSK  BITS(PRI_CH00_CHANNEL_CFG_dst_prot_ctrl_POSS, PRI_CH00_CHANNEL_CFG_dst_prot_ctrl_POSE)
# define  PRI_CH00_CHANNEL_CFG_dst_prot_ctrl      PRI_CH00_CHANNEL_CFG_dst_prot_ctrl_MSK

# define  PRI_CH00_CHANNEL_CFG_src_prot_ctrl_POSS 18U
# define  PRI_CH00_CHANNEL_CFG_src_prot_ctrl_POSE 20U
# define  PRI_CH00_CHANNEL_CFG_src_prot_ctrl_MSK  BITS(PRI_CH00_CHANNEL_CFG_src_prot_ctrl_POSS, PRI_CH00_CHANNEL_CFG_src_prot_ctrl_POSE)
# define  PRI_CH00_CHANNEL_CFG_src_prot_ctrl      PRI_CH00_CHANNEL_CFG_src_prot_ctrl_MSK

# define  PRI_CH00_CHANNEL_CFG_R_power_POSS 14U
# define  PRI_CH00_CHANNEL_CFG_R_power_POSE 17U
# define  PRI_CH00_CHANNEL_CFG_R_power_MSK  BITS(PRI_CH00_CHANNEL_CFG_R_power_POSS, PRI_CH00_CHANNEL_CFG_R_power_POSE)
# define  PRI_CH00_CHANNEL_CFG_R_power      PRI_CH00_CHANNEL_CFG_R_power_MSK

# define  PRI_CH00_CHANNEL_CFG_n_minus_1_POSS 4U
# define  PRI_CH00_CHANNEL_CFG_n_minus_1_POSE 13U
# define  PRI_CH00_CHANNEL_CFG_n_minus_1_MSK  BITS(PRI_CH00_CHANNEL_CFG_n_minus_1_POSS, PRI_CH00_CHANNEL_CFG_n_minus_1_POSE)
# define  PRI_CH00_CHANNEL_CFG_n_minus_1      PRI_CH00_CHANNEL_CFG_n_minus_1_MSK

# define  PRI_CH00_CHANNEL_CFG_next_useburst_POS 3U
# define  PRI_CH00_CHANNEL_CFG_next_useburst_MSK BIT(PRI_CH00_CHANNEL_CFG_next_useburst_POS)
# define  PRI_CH00_CHANNEL_CFG_next_useburst     PRI_CH00_CHANNEL_CFG_next_useburst_MSK

# define  PRI_CH00_CHANNEL_CFG_cycle_ctrl_POSS 0U
# define  PRI_CH00_CHANNEL_CFG_cycle_ctrl_POSE 2U
# define  PRI_CH00_CHANNEL_CFG_cycle_ctrl_MSK  BITS(PRI_CH00_CHANNEL_CFG_cycle_ctrl_POSS, PRI_CH00_CHANNEL_CFG_cycle_ctrl_POSE)
# define  PRI_CH00_CHANNEL_CFG_cycle_ctrl      PRI_CH00_CHANNEL_CFG_cycle_ctrl_MSK

/****************** Bit definition for PRI_CH01_SRC_DATA_END_PTR register ************************/

# define  PRI_CH01_SRC_DATA_END_PTR_src_data_end_ptr_POSS 0U
# define  PRI_CH01_SRC_DATA_END_PTR_src_data_end_ptr_POSE 31U
# define  PRI_CH01_SRC_DATA_END_PTR_src_data_end_ptr_MSK  BITS(PRI_CH01_SRC_DATA_END_PTR_src_data_end_ptr_POSS, PRI_CH01_SRC_DATA_END_PTR_src_data_end_ptr_POSE)
# define  PRI_CH01_SRC_DATA_END_PTR_src_data_end_ptr      PRI_CH01_SRC_DATA_END_PTR_src_data_end_ptr_MSK

/****************** Bit definition for PRI_CH01_DST_DATA_END_PTR register ************************/

# define  PRI_CH01_DST_DATA_END_PTR_dst_data_end_ptr_POSS 0U
# define  PRI_CH01_DST_DATA_END_PTR_dst_data_end_ptr_POSE 31U
# define  PRI_CH01_DST_DATA_END_PTR_dst_data_end_ptr_MSK  BITS(PRI_CH01_DST_DATA_END_PTR_dst_data_end_ptr_POSS, PRI_CH01_DST_DATA_END_PTR_dst_data_end_ptr_POSE)
# define  PRI_CH01_DST_DATA_END_PTR_dst_data_end_ptr      PRI_CH01_DST_DATA_END_PTR_dst_data_end_ptr_MSK

/****************** Bit definition for PRI_CH01_CHANNEL_CFG register ************************/

# define  PRI_CH01_CHANNEL_CFG_dst_inc_POSS 30U
# define  PRI_CH01_CHANNEL_CFG_dst_inc_POSE 31U
# define  PRI_CH01_CHANNEL_CFG_dst_inc_MSK  BITS(PRI_CH01_CHANNEL_CFG_dst_inc_POSS, PRI_CH01_CHANNEL_CFG_dst_inc_POSE)
# define  PRI_CH01_CHANNEL_CFG_dst_inc      PRI_CH01_CHANNEL_CFG_dst_inc_MSK

# define  PRI_CH01_CHANNEL_CFG_dst_size_POSS 28U
# define  PRI_CH01_CHANNEL_CFG_dst_size_POSE 29U
# define  PRI_CH01_CHANNEL_CFG_dst_size_MSK  BITS(PRI_CH01_CHANNEL_CFG_dst_size_POSS, PRI_CH01_CHANNEL_CFG_dst_size_POSE)
# define  PRI_CH01_CHANNEL_CFG_dst_size      PRI_CH01_CHANNEL_CFG_dst_size_MSK

# define  PRI_CH01_CHANNEL_CFG_src_inc_POSS 26U
# define  PRI_CH01_CHANNEL_CFG_src_inc_POSE 27U
# define  PRI_CH01_CHANNEL_CFG_src_inc_MSK  BITS(PRI_CH01_CHANNEL_CFG_src_inc_POSS, PRI_CH01_CHANNEL_CFG_src_inc_POSE)
# define  PRI_CH01_CHANNEL_CFG_src_inc      PRI_CH01_CHANNEL_CFG_src_inc_MSK

# define  PRI_CH01_CHANNEL_CFG_src_size_POSS 24U
# define  PRI_CH01_CHANNEL_CFG_src_size_POSE 25U
# define  PRI_CH01_CHANNEL_CFG_src_size_MSK  BITS(PRI_CH01_CHANNEL_CFG_src_size_POSS, PRI_CH01_CHANNEL_CFG_src_size_POSE)
# define  PRI_CH01_CHANNEL_CFG_src_size      PRI_CH01_CHANNEL_CFG_src_size_MSK

# define  PRI_CH01_CHANNEL_CFG_dst_prot_ctrl_POSS 21U
# define  PRI_CH01_CHANNEL_CFG_dst_prot_ctrl_POSE 23U
# define  PRI_CH01_CHANNEL_CFG_dst_prot_ctrl_MSK  BITS(PRI_CH01_CHANNEL_CFG_dst_prot_ctrl_POSS, PRI_CH01_CHANNEL_CFG_dst_prot_ctrl_POSE)
# define  PRI_CH01_CHANNEL_CFG_dst_prot_ctrl      PRI_CH01_CHANNEL_CFG_dst_prot_ctrl_MSK

# define  PRI_CH01_CHANNEL_CFG_src_prot_ctrl_POSS 18U
# define  PRI_CH01_CHANNEL_CFG_src_prot_ctrl_POSE 20U
# define  PRI_CH01_CHANNEL_CFG_src_prot_ctrl_MSK  BITS(PRI_CH01_CHANNEL_CFG_src_prot_ctrl_POSS, PRI_CH01_CHANNEL_CFG_src_prot_ctrl_POSE)
# define  PRI_CH01_CHANNEL_CFG_src_prot_ctrl      PRI_CH01_CHANNEL_CFG_src_prot_ctrl_MSK

# define  PRI_CH01_CHANNEL_CFG_R_power_POSS 14U
# define  PRI_CH01_CHANNEL_CFG_R_power_POSE 17U
# define  PRI_CH01_CHANNEL_CFG_R_power_MSK  BITS(PRI_CH01_CHANNEL_CFG_R_power_POSS, PRI_CH01_CHANNEL_CFG_R_power_POSE)
# define  PRI_CH01_CHANNEL_CFG_R_power      PRI_CH01_CHANNEL_CFG_R_power_MSK

# define  PRI_CH01_CHANNEL_CFG_n_minus_1_POSS 4U
# define  PRI_CH01_CHANNEL_CFG_n_minus_1_POSE 13U
# define  PRI_CH01_CHANNEL_CFG_n_minus_1_MSK  BITS(PRI_CH01_CHANNEL_CFG_n_minus_1_POSS, PRI_CH01_CHANNEL_CFG_n_minus_1_POSE)
# define  PRI_CH01_CHANNEL_CFG_n_minus_1      PRI_CH01_CHANNEL_CFG_n_minus_1_MSK

# define  PRI_CH01_CHANNEL_CFG_next_useburst_POS 3U
# define  PRI_CH01_CHANNEL_CFG_next_useburst_MSK BIT(PRI_CH01_CHANNEL_CFG_next_useburst_POS)
# define  PRI_CH01_CHANNEL_CFG_next_useburst     PRI_CH01_CHANNEL_CFG_next_useburst_MSK

# define  PRI_CH01_CHANNEL_CFG_cycle_ctrl_POSS 0U
# define  PRI_CH01_CHANNEL_CFG_cycle_ctrl_POSE 2U
# define  PRI_CH01_CHANNEL_CFG_cycle_ctrl_MSK  BITS(PRI_CH01_CHANNEL_CFG_cycle_ctrl_POSS, PRI_CH01_CHANNEL_CFG_cycle_ctrl_POSE)
# define  PRI_CH01_CHANNEL_CFG_cycle_ctrl      PRI_CH01_CHANNEL_CFG_cycle_ctrl_MSK


/****************** Bit definition for PRI_CH02_SRC_DATA_END_PTR register ************************/

# define  PRI_CH02_SRC_DATA_END_PTR_src_data_end_ptr_POSS 0U
# define  PRI_CH02_SRC_DATA_END_PTR_src_data_end_ptr_POSE 31U
# define  PRI_CH02_SRC_DATA_END_PTR_src_data_end_ptr_MSK  BITS(PRI_CH02_SRC_DATA_END_PTR_src_data_end_ptr_POSS, PRI_CH02_SRC_DATA_END_PTR_src_data_end_ptr_POSE)
# define  PRI_CH02_SRC_DATA_END_PTR_src_data_end_ptr      PRI_CH02_SRC_DATA_END_PTR_src_data_end_ptr_MSK

/****************** Bit definition for PRI_CH02_DST_DATA_END_PTR register ************************/

# define  PRI_CH02_DST_DATA_END_PTR_dst_data_end_ptr_POSS 0U
# define  PRI_CH02_DST_DATA_END_PTR_dst_data_end_ptr_POSE 31U
# define  PRI_CH02_DST_DATA_END_PTR_dst_data_end_ptr_MSK  BITS(PRI_CH02_DST_DATA_END_PTR_dst_data_end_ptr_POSS, PRI_CH02_DST_DATA_END_PTR_dst_data_end_ptr_POSE)
# define  PRI_CH02_DST_DATA_END_PTR_dst_data_end_ptr      PRI_CH02_DST_DATA_END_PTR_dst_data_end_ptr_MSK

/****************** Bit definition for PRI_CH02_CHANNEL_CFG register ************************/

# define  PRI_CH02_CHANNEL_CFG_dst_inc_POSS 30U
# define  PRI_CH02_CHANNEL_CFG_dst_inc_POSE 31U
# define  PRI_CH02_CHANNEL_CFG_dst_inc_MSK  BITS(PRI_CH02_CHANNEL_CFG_dst_inc_POSS, PRI_CH02_CHANNEL_CFG_dst_inc_POSE)
# define  PRI_CH02_CHANNEL_CFG_dst_inc      PRI_CH02_CHANNEL_CFG_dst_inc_MSK

# define  PRI_CH02_CHANNEL_CFG_dst_size_POSS 28U
# define  PRI_CH02_CHANNEL_CFG_dst_size_POSE 29U
# define  PRI_CH02_CHANNEL_CFG_dst_size_MSK  BITS(PRI_CH02_CHANNEL_CFG_dst_size_POSS, PRI_CH02_CHANNEL_CFG_dst_size_POSE)
# define  PRI_CH02_CHANNEL_CFG_dst_size      PRI_CH02_CHANNEL_CFG_dst_size_MSK

# define  PRI_CH02_CHANNEL_CFG_src_inc_POSS 26U
# define  PRI_CH02_CHANNEL_CFG_src_inc_POSE 27U
# define  PRI_CH02_CHANNEL_CFG_src_inc_MSK  BITS(PRI_CH02_CHANNEL_CFG_src_inc_POSS, PRI_CH02_CHANNEL_CFG_src_inc_POSE)
# define  PRI_CH02_CHANNEL_CFG_src_inc      PRI_CH02_CHANNEL_CFG_src_inc_MSK

# define  PRI_CH02_CHANNEL_CFG_src_size_POSS 24U
# define  PRI_CH02_CHANNEL_CFG_src_size_POSE 25U
# define  PRI_CH02_CHANNEL_CFG_src_size_MSK  BITS(PRI_CH02_CHANNEL_CFG_src_size_POSS, PRI_CH02_CHANNEL_CFG_src_size_POSE)
# define  PRI_CH02_CHANNEL_CFG_src_size      PRI_CH02_CHANNEL_CFG_src_size_MSK

# define  PRI_CH02_CHANNEL_CFG_dst_prot_ctrl_POSS 21U
# define  PRI_CH02_CHANNEL_CFG_dst_prot_ctrl_POSE 23U
# define  PRI_CH02_CHANNEL_CFG_dst_prot_ctrl_MSK  BITS(PRI_CH02_CHANNEL_CFG_dst_prot_ctrl_POSS, PRI_CH02_CHANNEL_CFG_dst_prot_ctrl_POSE)
# define  PRI_CH02_CHANNEL_CFG_dst_prot_ctrl      PRI_CH02_CHANNEL_CFG_dst_prot_ctrl_MSK

# define  PRI_CH02_CHANNEL_CFG_src_prot_ctrl_POSS 18U
# define  PRI_CH02_CHANNEL_CFG_src_prot_ctrl_POSE 20U
# define  PRI_CH02_CHANNEL_CFG_src_prot_ctrl_MSK  BITS(PRI_CH02_CHANNEL_CFG_src_prot_ctrl_POSS, PRI_CH02_CHANNEL_CFG_src_prot_ctrl_POSE)
# define  PRI_CH02_CHANNEL_CFG_src_prot_ctrl      PRI_CH02_CHANNEL_CFG_src_prot_ctrl_MSK

# define  PRI_CH02_CHANNEL_CFG_R_power_POSS 14U
# define  PRI_CH02_CHANNEL_CFG_R_power_POSE 17U
# define  PRI_CH02_CHANNEL_CFG_R_power_MSK  BITS(PRI_CH02_CHANNEL_CFG_R_power_POSS, PRI_CH02_CHANNEL_CFG_R_power_POSE)
# define  PRI_CH02_CHANNEL_CFG_R_power      PRI_CH02_CHANNEL_CFG_R_power_MSK

# define  PRI_CH02_CHANNEL_CFG_n_minus_1_POSS 4U
# define  PRI_CH02_CHANNEL_CFG_n_minus_1_POSE 13U
# define  PRI_CH02_CHANNEL_CFG_n_minus_1_MSK  BITS(PRI_CH02_CHANNEL_CFG_n_minus_1_POSS, PRI_CH02_CHANNEL_CFG_n_minus_1_POSE)
# define  PRI_CH02_CHANNEL_CFG_n_minus_1      PRI_CH02_CHANNEL_CFG_n_minus_1_MSK

# define  PRI_CH02_CHANNEL_CFG_next_useburst_POS 3U
# define  PRI_CH02_CHANNEL_CFG_next_useburst_MSK BIT(PRI_CH02_CHANNEL_CFG_next_useburst_POS)
# define  PRI_CH02_CHANNEL_CFG_next_useburst     PRI_CH02_CHANNEL_CFG_next_useburst_MSK

# define  PRI_CH02_CHANNEL_CFG_cycle_ctrl_POSS 0U
# define  PRI_CH02_CHANNEL_CFG_cycle_ctrl_POSE 2U
# define  PRI_CH02_CHANNEL_CFG_cycle_ctrl_MSK  BITS(PRI_CH02_CHANNEL_CFG_cycle_ctrl_POSS, PRI_CH02_CHANNEL_CFG_cycle_ctrl_POSE)
# define  PRI_CH02_CHANNEL_CFG_cycle_ctrl      PRI_CH02_CHANNEL_CFG_cycle_ctrl_MSK


/****************** Bit definition for PRI_CH03_SRC_DATA_END_PTR register ************************/

# define  PRI_CH03_SRC_DATA_END_PTR_src_data_end_ptr_POSS 0U
# define  PRI_CH03_SRC_DATA_END_PTR_src_data_end_ptr_POSE 31U
# define  PRI_CH03_SRC_DATA_END_PTR_src_data_end_ptr_MSK  BITS(PRI_CH03_SRC_DATA_END_PTR_src_data_end_ptr_POSS, PRI_CH03_SRC_DATA_END_PTR_src_data_end_ptr_POSE)
# define  PRI_CH03_SRC_DATA_END_PTR_src_data_end_ptr      PRI_CH03_SRC_DATA_END_PTR_src_data_end_ptr_MSK

/****************** Bit definition for PRI_CH03_DST_DATA_END_PTR register ************************/

# define  PRI_CH03_DST_DATA_END_PTR_dst_data_end_ptr_POSS 0U
# define  PRI_CH03_DST_DATA_END_PTR_dst_data_end_ptr_POSE 31U
# define  PRI_CH03_DST_DATA_END_PTR_dst_data_end_ptr_MSK  BITS(PRI_CH03_DST_DATA_END_PTR_dst_data_end_ptr_POSS, PRI_CH03_DST_DATA_END_PTR_dst_data_end_ptr_POSE)
# define  PRI_CH03_DST_DATA_END_PTR_dst_data_end_ptr      PRI_CH03_DST_DATA_END_PTR_dst_data_end_ptr_MSK

/****************** Bit definition for PRI_CH03_CHANNEL_CFG register ************************/

# define  PRI_CH03_CHANNEL_CFG_dst_inc_POSS 30U
# define  PRI_CH03_CHANNEL_CFG_dst_inc_POSE 31U
# define  PRI_CH03_CHANNEL_CFG_dst_inc_MSK  BITS(PRI_CH03_CHANNEL_CFG_dst_inc_POSS, PRI_CH03_CHANNEL_CFG_dst_inc_POSE)
# define  PRI_CH03_CHANNEL_CFG_dst_inc      PRI_CH03_CHANNEL_CFG_dst_inc_MSK

# define  PRI_CH03_CHANNEL_CFG_dst_size_POSS 28U
# define  PRI_CH03_CHANNEL_CFG_dst_size_POSE 29U
# define  PRI_CH03_CHANNEL_CFG_dst_size_MSK  BITS(PRI_CH03_CHANNEL_CFG_dst_size_POSS, PRI_CH03_CHANNEL_CFG_dst_size_POSE)
# define  PRI_CH03_CHANNEL_CFG_dst_size      PRI_CH03_CHANNEL_CFG_dst_size_MSK

# define  PRI_CH03_CHANNEL_CFG_src_inc_POSS 26U
# define  PRI_CH03_CHANNEL_CFG_src_inc_POSE 27U
# define  PRI_CH03_CHANNEL_CFG_src_inc_MSK  BITS(PRI_CH03_CHANNEL_CFG_src_inc_POSS, PRI_CH03_CHANNEL_CFG_src_inc_POSE)
# define  PRI_CH03_CHANNEL_CFG_src_inc      PRI_CH03_CHANNEL_CFG_src_inc_MSK

# define  PRI_CH03_CHANNEL_CFG_src_size_POSS 24U
# define  PRI_CH03_CHANNEL_CFG_src_size_POSE 25U
# define  PRI_CH03_CHANNEL_CFG_src_size_MSK  BITS(PRI_CH03_CHANNEL_CFG_src_size_POSS, PRI_CH03_CHANNEL_CFG_src_size_POSE)
# define  PRI_CH03_CHANNEL_CFG_src_size      PRI_CH03_CHANNEL_CFG_src_size_MSK

# define  PRI_CH03_CHANNEL_CFG_dst_prot_ctrl_POSS 21U
# define  PRI_CH03_CHANNEL_CFG_dst_prot_ctrl_POSE 23U
# define  PRI_CH03_CHANNEL_CFG_dst_prot_ctrl_MSK  BITS(PRI_CH03_CHANNEL_CFG_dst_prot_ctrl_POSS, PRI_CH03_CHANNEL_CFG_dst_prot_ctrl_POSE)
# define  PRI_CH03_CHANNEL_CFG_dst_prot_ctrl      PRI_CH03_CHANNEL_CFG_dst_prot_ctrl_MSK

# define  PRI_CH03_CHANNEL_CFG_src_prot_ctrl_POSS 18U
# define  PRI_CH03_CHANNEL_CFG_src_prot_ctrl_POSE 20U
# define  PRI_CH03_CHANNEL_CFG_src_prot_ctrl_MSK  BITS(PRI_CH03_CHANNEL_CFG_src_prot_ctrl_POSS, PRI_CH03_CHANNEL_CFG_src_prot_ctrl_POSE)
# define  PRI_CH03_CHANNEL_CFG_src_prot_ctrl      PRI_CH03_CHANNEL_CFG_src_prot_ctrl_MSK

# define  PRI_CH03_CHANNEL_CFG_R_power_POSS 14U
# define  PRI_CH03_CHANNEL_CFG_R_power_POSE 17U
# define  PRI_CH03_CHANNEL_CFG_R_power_MSK  BITS(PRI_CH03_CHANNEL_CFG_R_power_POSS, PRI_CH03_CHANNEL_CFG_R_power_POSE)
# define  PRI_CH03_CHANNEL_CFG_R_power      PRI_CH03_CHANNEL_CFG_R_power_MSK

# define  PRI_CH03_CHANNEL_CFG_n_minus_1_POSS 4U
# define  PRI_CH03_CHANNEL_CFG_n_minus_1_POSE 13U
# define  PRI_CH03_CHANNEL_CFG_n_minus_1_MSK  BITS(PRI_CH03_CHANNEL_CFG_n_minus_1_POSS, PRI_CH03_CHANNEL_CFG_n_minus_1_POSE)
# define  PRI_CH03_CHANNEL_CFG_n_minus_1      PRI_CH03_CHANNEL_CFG_n_minus_1_MSK

# define  PRI_CH03_CHANNEL_CFG_next_useburst_POS 3U
# define  PRI_CH03_CHANNEL_CFG_next_useburst_MSK BIT(PRI_CH03_CHANNEL_CFG_next_useburst_POS)
# define  PRI_CH03_CHANNEL_CFG_next_useburst     PRI_CH03_CHANNEL_CFG_next_useburst_MSK

# define  PRI_CH03_CHANNEL_CFG_cycle_ctrl_POSS 0U
# define  PRI_CH03_CHANNEL_CFG_cycle_ctrl_POSE 2U
# define  PRI_CH03_CHANNEL_CFG_cycle_ctrl_MSK  BITS(PRI_CH03_CHANNEL_CFG_cycle_ctrl_POSS, PRI_CH03_CHANNEL_CFG_cycle_ctrl_POSE)
# define  PRI_CH03_CHANNEL_CFG_cycle_ctrl      PRI_CH03_CHANNEL_CFG_cycle_ctrl_MSK

/****************** Bit definition for PRI_CH04_SRC_DATA_END_PTR register ************************/

# define  PRI_CH04_SRC_DATA_END_PTR_src_data_end_ptr_POSS 0U
# define  PRI_CH04_SRC_DATA_END_PTR_src_data_end_ptr_POSE 31U
# define  PRI_CH04_SRC_DATA_END_PTR_src_data_end_ptr_MSK  BITS(PRI_CH04_SRC_DATA_END_PTR_src_data_end_ptr_POSS, PRI_CH04_SRC_DATA_END_PTR_src_data_end_ptr_POSE)
# define  PRI_CH04_SRC_DATA_END_PTR_src_data_end_ptr      PRI_CH04_SRC_DATA_END_PTR_src_data_end_ptr_MSK

/****************** Bit definition for PRI_CH04_DST_DATA_END_PTR register ************************/

# define  PRI_CH04_DST_DATA_END_PTR_dst_data_end_ptr_POSS 0U
# define  PRI_CH04_DST_DATA_END_PTR_dst_data_end_ptr_POSE 31U
# define  PRI_CH04_DST_DATA_END_PTR_dst_data_end_ptr_MSK  BITS(PRI_CH04_DST_DATA_END_PTR_dst_data_end_ptr_POSS, PRI_CH04_DST_DATA_END_PTR_dst_data_end_ptr_POSE)
# define  PRI_CH04_DST_DATA_END_PTR_dst_data_end_ptr      PRI_CH04_DST_DATA_END_PTR_dst_data_end_ptr_MSK

/****************** Bit definition for PRI_CH04_CHANNEL_CFG register ************************/

# define  PRI_CH04_CHANNEL_CFG_dst_inc_POSS 30U
# define  PRI_CH04_CHANNEL_CFG_dst_inc_POSE 31U
# define  PRI_CH04_CHANNEL_CFG_dst_inc_MSK  BITS(PRI_CH04_CHANNEL_CFG_dst_inc_POSS, PRI_CH04_CHANNEL_CFG_dst_inc_POSE)
# define  PRI_CH04_CHANNEL_CFG_dst_inc      PRI_CH04_CHANNEL_CFG_dst_inc_MSK

# define  PRI_CH04_CHANNEL_CFG_dst_size_POSS 28U
# define  PRI_CH04_CHANNEL_CFG_dst_size_POSE 29U
# define  PRI_CH04_CHANNEL_CFG_dst_size_MSK  BITS(PRI_CH04_CHANNEL_CFG_dst_size_POSS, PRI_CH04_CHANNEL_CFG_dst_size_POSE)
# define  PRI_CH04_CHANNEL_CFG_dst_size      PRI_CH04_CHANNEL_CFG_dst_size_MSK

# define  PRI_CH04_CHANNEL_CFG_src_inc_POSS 26U
# define  PRI_CH04_CHANNEL_CFG_src_inc_POSE 27U
# define  PRI_CH04_CHANNEL_CFG_src_inc_MSK  BITS(PRI_CH04_CHANNEL_CFG_src_inc_POSS, PRI_CH04_CHANNEL_CFG_src_inc_POSE)
# define  PRI_CH04_CHANNEL_CFG_src_inc      PRI_CH04_CHANNEL_CFG_src_inc_MSK

# define  PRI_CH04_CHANNEL_CFG_src_size_POSS 24U
# define  PRI_CH04_CHANNEL_CFG_src_size_POSE 25U
# define  PRI_CH04_CHANNEL_CFG_src_size_MSK  BITS(PRI_CH04_CHANNEL_CFG_src_size_POSS, PRI_CH04_CHANNEL_CFG_src_size_POSE)
# define  PRI_CH04_CHANNEL_CFG_src_size      PRI_CH04_CHANNEL_CFG_src_size_MSK

# define  PRI_CH04_CHANNEL_CFG_dst_prot_ctrl_POSS 21U
# define  PRI_CH04_CHANNEL_CFG_dst_prot_ctrl_POSE 23U
# define  PRI_CH04_CHANNEL_CFG_dst_prot_ctrl_MSK  BITS(PRI_CH04_CHANNEL_CFG_dst_prot_ctrl_POSS, PRI_CH04_CHANNEL_CFG_dst_prot_ctrl_POSE)
# define  PRI_CH04_CHANNEL_CFG_dst_prot_ctrl      PRI_CH04_CHANNEL_CFG_dst_prot_ctrl_MSK

# define  PRI_CH04_CHANNEL_CFG_src_prot_ctrl_POSS 18U
# define  PRI_CH04_CHANNEL_CFG_src_prot_ctrl_POSE 20U
# define  PRI_CH04_CHANNEL_CFG_src_prot_ctrl_MSK  BITS(PRI_CH04_CHANNEL_CFG_src_prot_ctrl_POSS, PRI_CH04_CHANNEL_CFG_src_prot_ctrl_POSE)
# define  PRI_CH04_CHANNEL_CFG_src_prot_ctrl      PRI_CH04_CHANNEL_CFG_src_prot_ctrl_MSK

# define  PRI_CH04_CHANNEL_CFG_R_power_POSS 14U
# define  PRI_CH04_CHANNEL_CFG_R_power_POSE 17U
# define  PRI_CH04_CHANNEL_CFG_R_power_MSK  BITS(PRI_CH04_CHANNEL_CFG_R_power_POSS, PRI_CH04_CHANNEL_CFG_R_power_POSE)
# define  PRI_CH04_CHANNEL_CFG_R_power      PRI_CH04_CHANNEL_CFG_R_power_MSK

# define  PRI_CH04_CHANNEL_CFG_n_minus_1_POSS 4U
# define  PRI_CH04_CHANNEL_CFG_n_minus_1_POSE 13U
# define  PRI_CH04_CHANNEL_CFG_n_minus_1_MSK  BITS(PRI_CH04_CHANNEL_CFG_n_minus_1_POSS, PRI_CH04_CHANNEL_CFG_n_minus_1_POSE)
# define  PRI_CH04_CHANNEL_CFG_n_minus_1      PRI_CH04_CHANNEL_CFG_n_minus_1_MSK

# define  PRI_CH04_CHANNEL_CFG_next_useburst_POS 3U
# define  PRI_CH04_CHANNEL_CFG_next_useburst_MSK BIT(PRI_CH04_CHANNEL_CFG_next_useburst_POS)
# define  PRI_CH04_CHANNEL_CFG_next_useburst     PRI_CH04_CHANNEL_CFG_next_useburst_MSK

# define  PRI_CH04_CHANNEL_CFG_cycle_ctrl_POSS 0U
# define  PRI_CH04_CHANNEL_CFG_cycle_ctrl_POSE 2U
# define  PRI_CH04_CHANNEL_CFG_cycle_ctrl_MSK  BITS(PRI_CH04_CHANNEL_CFG_cycle_ctrl_POSS, PRI_CH04_CHANNEL_CFG_cycle_ctrl_POSE)
# define  PRI_CH04_CHANNEL_CFG_cycle_ctrl      PRI_CH04_CHANNEL_CFG_cycle_ctrl_MSK

/****************** Bit definition for PRI_CH05_SRC_DATA_END_PTR register ************************/

# define  PRI_CH05_SRC_DATA_END_PTR_src_data_end_ptr_POSS 0U
# define  PRI_CH05_SRC_DATA_END_PTR_src_data_end_ptr_POSE 31U
# define  PRI_CH05_SRC_DATA_END_PTR_src_data_end_ptr_MSK  BITS(PRI_CH05_SRC_DATA_END_PTR_src_data_end_ptr_POSS, PRI_CH05_SRC_DATA_END_PTR_src_data_end_ptr_POSE)
# define  PRI_CH05_SRC_DATA_END_PTR_src_data_end_ptr      PRI_CH05_SRC_DATA_END_PTR_src_data_end_ptr_MSK

/****************** Bit definition for PRI_CH05_DST_DATA_END_PTR register ************************/

# define  PRI_CH05_DST_DATA_END_PTR_dst_data_end_ptr_POSS 0U
# define  PRI_CH05_DST_DATA_END_PTR_dst_data_end_ptr_POSE 31U
# define  PRI_CH05_DST_DATA_END_PTR_dst_data_end_ptr_MSK  BITS(PRI_CH05_DST_DATA_END_PTR_dst_data_end_ptr_POSS, PRI_CH05_DST_DATA_END_PTR_dst_data_end_ptr_POSE)
# define  PRI_CH05_DST_DATA_END_PTR_dst_data_end_ptr      PRI_CH05_DST_DATA_END_PTR_dst_data_end_ptr_MSK

/****************** Bit definition for PRI_CH05_CHANNEL_CFG register ************************/

# define  PRI_CH05_CHANNEL_CFG_dst_inc_POSS 30U
# define  PRI_CH05_CHANNEL_CFG_dst_inc_POSE 31U
# define  PRI_CH05_CHANNEL_CFG_dst_inc_MSK  BITS(PRI_CH05_CHANNEL_CFG_dst_inc_POSS, PRI_CH05_CHANNEL_CFG_dst_inc_POSE)
# define  PRI_CH05_CHANNEL_CFG_dst_inc      PRI_CH05_CHANNEL_CFG_dst_inc_MSK

# define  PRI_CH05_CHANNEL_CFG_dst_size_POSS 28U
# define  PRI_CH05_CHANNEL_CFG_dst_size_POSE 29U
# define  PRI_CH05_CHANNEL_CFG_dst_size_MSK  BITS(PRI_CH05_CHANNEL_CFG_dst_size_POSS, PRI_CH05_CHANNEL_CFG_dst_size_POSE)
# define  PRI_CH05_CHANNEL_CFG_dst_size      PRI_CH05_CHANNEL_CFG_dst_size_MSK

# define  PRI_CH05_CHANNEL_CFG_src_inc_POSS 26U
# define  PRI_CH05_CHANNEL_CFG_src_inc_POSE 27U
# define  PRI_CH05_CHANNEL_CFG_src_inc_MSK  BITS(PRI_CH05_CHANNEL_CFG_src_inc_POSS, PRI_CH05_CHANNEL_CFG_src_inc_POSE)
# define  PRI_CH05_CHANNEL_CFG_src_inc      PRI_CH05_CHANNEL_CFG_src_inc_MSK

# define  PRI_CH05_CHANNEL_CFG_src_size_POSS 24U
# define  PRI_CH05_CHANNEL_CFG_src_size_POSE 25U
# define  PRI_CH05_CHANNEL_CFG_src_size_MSK  BITS(PRI_CH05_CHANNEL_CFG_src_size_POSS, PRI_CH05_CHANNEL_CFG_src_size_POSE)
# define  PRI_CH05_CHANNEL_CFG_src_size      PRI_CH05_CHANNEL_CFG_src_size_MSK

# define  PRI_CH05_CHANNEL_CFG_dst_prot_ctrl_POSS 21U
# define  PRI_CH05_CHANNEL_CFG_dst_prot_ctrl_POSE 23U
# define  PRI_CH05_CHANNEL_CFG_dst_prot_ctrl_MSK  BITS(PRI_CH05_CHANNEL_CFG_dst_prot_ctrl_POSS, PRI_CH05_CHANNEL_CFG_dst_prot_ctrl_POSE)
# define  PRI_CH05_CHANNEL_CFG_dst_prot_ctrl      PRI_CH05_CHANNEL_CFG_dst_prot_ctrl_MSK

# define  PRI_CH05_CHANNEL_CFG_src_prot_ctrl_POSS 18U
# define  PRI_CH05_CHANNEL_CFG_src_prot_ctrl_POSE 20U
# define  PRI_CH05_CHANNEL_CFG_src_prot_ctrl_MSK  BITS(PRI_CH05_CHANNEL_CFG_src_prot_ctrl_POSS, PRI_CH05_CHANNEL_CFG_src_prot_ctrl_POSE)
# define  PRI_CH05_CHANNEL_CFG_src_prot_ctrl      PRI_CH05_CHANNEL_CFG_src_prot_ctrl_MSK

# define  PRI_CH05_CHANNEL_CFG_R_power_POSS 14U
# define  PRI_CH05_CHANNEL_CFG_R_power_POSE 17U
# define  PRI_CH05_CHANNEL_CFG_R_power_MSK  BITS(PRI_CH05_CHANNEL_CFG_R_power_POSS, PRI_CH05_CHANNEL_CFG_R_power_POSE)
# define  PRI_CH05_CHANNEL_CFG_R_power      PRI_CH05_CHANNEL_CFG_R_power_MSK

# define  PRI_CH05_CHANNEL_CFG_n_minus_1_POSS 4U
# define  PRI_CH05_CHANNEL_CFG_n_minus_1_POSE 13U
# define  PRI_CH05_CHANNEL_CFG_n_minus_1_MSK  BITS(PRI_CH05_CHANNEL_CFG_n_minus_1_POSS, PRI_CH05_CHANNEL_CFG_n_minus_1_POSE)
# define  PRI_CH05_CHANNEL_CFG_n_minus_1      PRI_CH05_CHANNEL_CFG_n_minus_1_MSK

# define  PRI_CH05_CHANNEL_CFG_next_useburst_POS 3U
# define  PRI_CH05_CHANNEL_CFG_next_useburst_MSK BIT(PRI_CH05_CHANNEL_CFG_next_useburst_POS)
# define  PRI_CH05_CHANNEL_CFG_next_useburst     PRI_CH05_CHANNEL_CFG_next_useburst_MSK

# define  PRI_CH05_CHANNEL_CFG_cycle_ctrl_POSS 0U
# define  PRI_CH05_CHANNEL_CFG_cycle_ctrl_POSE 2U
# define  PRI_CH05_CHANNEL_CFG_cycle_ctrl_MSK  BITS(PRI_CH05_CHANNEL_CFG_cycle_ctrl_POSS, PRI_CH05_CHANNEL_CFG_cycle_ctrl_POSE)
# define  PRI_CH05_CHANNEL_CFG_cycle_ctrl      PRI_CH05_CHANNEL_CFG_cycle_ctrl_MSK

/****************** Bit definition for ALT_CH00_SRC_DATA_END_PTR register ************************/

# define  ALT_CH00_SRC_DATA_END_PTR_src_data_end_ptr_POSS 0U
# define  ALT_CH00_SRC_DATA_END_PTR_src_data_end_ptr_POSE 31U
# define  ALT_CH00_SRC_DATA_END_PTR_src_data_end_ptr_MSK  BITS(ALT_CH00_SRC_DATA_END_PTR_src_data_end_ptr_POSS, ALT_CH00_SRC_DATA_END_PTR_src_data_end_ptr_POSE)
# define  ALT_CH00_SRC_DATA_END_PTR_src_data_end_ptr      ALT_CH00_SRC_DATA_END_PTR_src_data_end_ptr_MSK

/****************** Bit definition for ALT_CH00_DST_DATA_END_PTR register ************************/

# define  ALT_CH00_DST_DATA_END_PTR_dst_data_end_ptr_POSS 0U
# define  ALT_CH00_DST_DATA_END_PTR_dst_data_end_ptr_POSE 31U
# define  ALT_CH00_DST_DATA_END_PTR_dst_data_end_ptr_MSK  BITS(ALT_CH00_DST_DATA_END_PTR_dst_data_end_ptr_POSS, ALT_CH00_DST_DATA_END_PTR_dst_data_end_ptr_POSE)
# define  ALT_CH00_DST_DATA_END_PTR_dst_data_end_ptr      ALT_CH00_DST_DATA_END_PTR_dst_data_end_ptr_MSK

/****************** Bit definition for ALT_CH00_CHANNEL_CFG register ************************/

# define  ALT_CH00_CHANNEL_CFG_dst_inc_POSS 30U
# define  ALT_CH00_CHANNEL_CFG_dst_inc_POSE 31U
# define  ALT_CH00_CHANNEL_CFG_dst_inc_MSK  BITS(ALT_CH00_CHANNEL_CFG_dst_inc_POSS, ALT_CH00_CHANNEL_CFG_dst_inc_POSE)
# define  ALT_CH00_CHANNEL_CFG_dst_inc      ALT_CH00_CHANNEL_CFG_dst_inc_MSK

# define  ALT_CH00_CHANNEL_CFG_dst_size_POSS 28U
# define  ALT_CH00_CHANNEL_CFG_dst_size_POSE 29U
# define  ALT_CH00_CHANNEL_CFG_dst_size_MSK  BITS(ALT_CH00_CHANNEL_CFG_dst_size_POSS, ALT_CH00_CHANNEL_CFG_dst_size_POSE)
# define  ALT_CH00_CHANNEL_CFG_dst_size      ALT_CH00_CHANNEL_CFG_dst_size_MSK

# define  ALT_CH00_CHANNEL_CFG_src_inc_POSS 26U
# define  ALT_CH00_CHANNEL_CFG_src_inc_POSE 27U
# define  ALT_CH00_CHANNEL_CFG_src_inc_MSK  BITS(ALT_CH00_CHANNEL_CFG_src_inc_POSS, ALT_CH00_CHANNEL_CFG_src_inc_POSE)
# define  ALT_CH00_CHANNEL_CFG_src_inc      ALT_CH00_CHANNEL_CFG_src_inc_MSK

# define  ALT_CH00_CHANNEL_CFG_src_size_POSS 24U
# define  ALT_CH00_CHANNEL_CFG_src_size_POSE 25U
# define  ALT_CH00_CHANNEL_CFG_src_size_MSK  BITS(ALT_CH00_CHANNEL_CFG_src_size_POSS, ALT_CH00_CHANNEL_CFG_src_size_POSE)
# define  ALT_CH00_CHANNEL_CFG_src_size      ALT_CH00_CHANNEL_CFG_src_size_MSK

# define  ALT_CH00_CHANNEL_CFG_dst_prot_ctrl_POSS 21U
# define  ALT_CH00_CHANNEL_CFG_dst_prot_ctrl_POSE 23U
# define  ALT_CH00_CHANNEL_CFG_dst_prot_ctrl_MSK  BITS(ALT_CH00_CHANNEL_CFG_dst_prot_ctrl_POSS, ALT_CH00_CHANNEL_CFG_dst_prot_ctrl_POSE)
# define  ALT_CH00_CHANNEL_CFG_dst_prot_ctrl      ALT_CH00_CHANNEL_CFG_dst_prot_ctrl_MSK

# define  ALT_CH00_CHANNEL_CFG_src_prot_ctrl_POSS 18U
# define  ALT_CH00_CHANNEL_CFG_src_prot_ctrl_POSE 20U
# define  ALT_CH00_CHANNEL_CFG_src_prot_ctrl_MSK  BITS(ALT_CH00_CHANNEL_CFG_src_prot_ctrl_POSS, ALT_CH00_CHANNEL_CFG_src_prot_ctrl_POSE)
# define  ALT_CH00_CHANNEL_CFG_src_prot_ctrl      ALT_CH00_CHANNEL_CFG_src_prot_ctrl_MSK

# define  ALT_CH00_CHANNEL_CFG_R_power_POSS 14U
# define  ALT_CH00_CHANNEL_CFG_R_power_POSE 17U
# define  ALT_CH00_CHANNEL_CFG_R_power_MSK  BITS(ALT_CH00_CHANNEL_CFG_R_power_POSS, ALT_CH00_CHANNEL_CFG_R_power_POSE)
# define  ALT_CH00_CHANNEL_CFG_R_power      ALT_CH00_CHANNEL_CFG_R_power_MSK

# define  ALT_CH00_CHANNEL_CFG_n_minus_1_POSS 4U
# define  ALT_CH00_CHANNEL_CFG_n_minus_1_POSE 13U
# define  ALT_CH00_CHANNEL_CFG_n_minus_1_MSK  BITS(ALT_CH00_CHANNEL_CFG_n_minus_1_POSS, ALT_CH00_CHANNEL_CFG_n_minus_1_POSE)
# define  ALT_CH00_CHANNEL_CFG_n_minus_1      ALT_CH00_CHANNEL_CFG_n_minus_1_MSK

# define  ALT_CH00_CHANNEL_CFG_next_useburst_POS 3U
# define  ALT_CH00_CHANNEL_CFG_next_useburst_MSK BIT(ALT_CH00_CHANNEL_CFG_next_useburst_POS)
# define  ALT_CH00_CHANNEL_CFG_next_useburst     ALT_CH00_CHANNEL_CFG_next_useburst_MSK

# define  ALT_CH00_CHANNEL_CFG_cycle_ctrl_POSS 0U
# define  ALT_CH00_CHANNEL_CFG_cycle_ctrl_POSE 2U
# define  ALT_CH00_CHANNEL_CFG_cycle_ctrl_MSK  BITS(ALT_CH00_CHANNEL_CFG_cycle_ctrl_POSS, ALT_CH00_CHANNEL_CFG_cycle_ctrl_POSE)
# define  ALT_CH00_CHANNEL_CFG_cycle_ctrl      ALT_CH00_CHANNEL_CFG_cycle_ctrl_MSK

/****************** Bit definition for ALT_CH01_SRC_DATA_END_PTR register ************************/

# define  ALT_CH01_SRC_DATA_END_PTR_src_data_end_ptr_POSS 0U
# define  ALT_CH01_SRC_DATA_END_PTR_src_data_end_ptr_POSE 31U
# define  ALT_CH01_SRC_DATA_END_PTR_src_data_end_ptr_MSK  BITS(ALT_CH01_SRC_DATA_END_PTR_src_data_end_ptr_POSS, ALT_CH01_SRC_DATA_END_PTR_src_data_end_ptr_POSE)
# define  ALT_CH01_SRC_DATA_END_PTR_src_data_end_ptr      ALT_CH01_SRC_DATA_END_PTR_src_data_end_ptr_MSK

/****************** Bit definition for ALT_CH01_DST_DATA_END_PTR register ************************/

# define  ALT_CH01_DST_DATA_END_PTR_dst_data_end_ptr_POSS 0U
# define  ALT_CH01_DST_DATA_END_PTR_dst_data_end_ptr_POSE 31U
# define  ALT_CH01_DST_DATA_END_PTR_dst_data_end_ptr_MSK  BITS(ALT_CH01_DST_DATA_END_PTR_dst_data_end_ptr_POSS, ALT_CH01_DST_DATA_END_PTR_dst_data_end_ptr_POSE)
# define  ALT_CH01_DST_DATA_END_PTR_dst_data_end_ptr      ALT_CH01_DST_DATA_END_PTR_dst_data_end_ptr_MSK

/****************** Bit definition for ALT_CH01_CHANNEL_CFG register ************************/

# define  ALT_CH01_CHANNEL_CFG_dst_inc_POSS 30U
# define  ALT_CH01_CHANNEL_CFG_dst_inc_POSE 31U
# define  ALT_CH01_CHANNEL_CFG_dst_inc_MSK  BITS(ALT_CH01_CHANNEL_CFG_dst_inc_POSS, ALT_CH01_CHANNEL_CFG_dst_inc_POSE)
# define  ALT_CH01_CHANNEL_CFG_dst_inc      ALT_CH01_CHANNEL_CFG_dst_inc_MSK

# define  ALT_CH01_CHANNEL_CFG_dst_size_POSS 28U
# define  ALT_CH01_CHANNEL_CFG_dst_size_POSE 29U
# define  ALT_CH01_CHANNEL_CFG_dst_size_MSK  BITS(ALT_CH01_CHANNEL_CFG_dst_size_POSS, ALT_CH01_CHANNEL_CFG_dst_size_POSE)
# define  ALT_CH01_CHANNEL_CFG_dst_size      ALT_CH01_CHANNEL_CFG_dst_size_MSK

# define  ALT_CH01_CHANNEL_CFG_src_inc_POSS 26U
# define  ALT_CH01_CHANNEL_CFG_src_inc_POSE 27U
# define  ALT_CH01_CHANNEL_CFG_src_inc_MSK  BITS(ALT_CH01_CHANNEL_CFG_src_inc_POSS, ALT_CH01_CHANNEL_CFG_src_inc_POSE)
# define  ALT_CH01_CHANNEL_CFG_src_inc      ALT_CH01_CHANNEL_CFG_src_inc_MSK

# define  ALT_CH01_CHANNEL_CFG_src_size_POSS 24U
# define  ALT_CH01_CHANNEL_CFG_src_size_POSE 25U
# define  ALT_CH01_CHANNEL_CFG_src_size_MSK  BITS(ALT_CH01_CHANNEL_CFG_src_size_POSS, ALT_CH01_CHANNEL_CFG_src_size_POSE)
# define  ALT_CH01_CHANNEL_CFG_src_size      ALT_CH01_CHANNEL_CFG_src_size_MSK

# define  ALT_CH01_CHANNEL_CFG_dst_prot_ctrl_POSS 21U
# define  ALT_CH01_CHANNEL_CFG_dst_prot_ctrl_POSE 23U
# define  ALT_CH01_CHANNEL_CFG_dst_prot_ctrl_MSK  BITS(ALT_CH01_CHANNEL_CFG_dst_prot_ctrl_POSS, ALT_CH01_CHANNEL_CFG_dst_prot_ctrl_POSE)
# define  ALT_CH01_CHANNEL_CFG_dst_prot_ctrl      ALT_CH01_CHANNEL_CFG_dst_prot_ctrl_MSK

# define  ALT_CH01_CHANNEL_CFG_src_prot_ctrl_POSS 18U
# define  ALT_CH01_CHANNEL_CFG_src_prot_ctrl_POSE 20U
# define  ALT_CH01_CHANNEL_CFG_src_prot_ctrl_MSK  BITS(ALT_CH01_CHANNEL_CFG_src_prot_ctrl_POSS, ALT_CH01_CHANNEL_CFG_src_prot_ctrl_POSE)
# define  ALT_CH01_CHANNEL_CFG_src_prot_ctrl      ALT_CH01_CHANNEL_CFG_src_prot_ctrl_MSK

# define  ALT_CH01_CHANNEL_CFG_R_power_POSS 14U
# define  ALT_CH01_CHANNEL_CFG_R_power_POSE 17U
# define  ALT_CH01_CHANNEL_CFG_R_power_MSK  BITS(ALT_CH01_CHANNEL_CFG_R_power_POSS, ALT_CH01_CHANNEL_CFG_R_power_POSE)
# define  ALT_CH01_CHANNEL_CFG_R_power      ALT_CH01_CHANNEL_CFG_R_power_MSK

# define  ALT_CH01_CHANNEL_CFG_n_minus_1_POSS 4U
# define  ALT_CH01_CHANNEL_CFG_n_minus_1_POSE 13U
# define  ALT_CH01_CHANNEL_CFG_n_minus_1_MSK  BITS(ALT_CH01_CHANNEL_CFG_n_minus_1_POSS, ALT_CH01_CHANNEL_CFG_n_minus_1_POSE)
# define  ALT_CH01_CHANNEL_CFG_n_minus_1      ALT_CH01_CHANNEL_CFG_n_minus_1_MSK

# define  ALT_CH01_CHANNEL_CFG_next_useburst_POS 3U
# define  ALT_CH01_CHANNEL_CFG_next_useburst_MSK BIT(ALT_CH01_CHANNEL_CFG_next_useburst_POS)
# define  ALT_CH01_CHANNEL_CFG_next_useburst     ALT_CH01_CHANNEL_CFG_next_useburst_MSK

# define  ALT_CH01_CHANNEL_CFG_cycle_ctrl_POSS 0U
# define  ALT_CH01_CHANNEL_CFG_cycle_ctrl_POSE 2U
# define  ALT_CH01_CHANNEL_CFG_cycle_ctrl_MSK  BITS(ALT_CH01_CHANNEL_CFG_cycle_ctrl_POSS, ALT_CH01_CHANNEL_CFG_cycle_ctrl_POSE)
# define  ALT_CH01_CHANNEL_CFG_cycle_ctrl      ALT_CH01_CHANNEL_CFG_cycle_ctrl_MSK

/****************** Bit definition for ALT_CH02_SRC_DATA_END_PTR register ************************/

# define  ALT_CH02_SRC_DATA_END_PTR_src_data_end_ptr_POSS 0U
# define  ALT_CH02_SRC_DATA_END_PTR_src_data_end_ptr_POSE 31U
# define  ALT_CH02_SRC_DATA_END_PTR_src_data_end_ptr_MSK  BITS(ALT_CH02_SRC_DATA_END_PTR_src_data_end_ptr_POSS, ALT_CH02_SRC_DATA_END_PTR_src_data_end_ptr_POSE)
# define  ALT_CH02_SRC_DATA_END_PTR_src_data_end_ptr      ALT_CH02_SRC_DATA_END_PTR_src_data_end_ptr_MSK

/****************** Bit definition for ALT_CH02_DST_DATA_END_PTR register ************************/

# define  ALT_CH02_DST_DATA_END_PTR_dst_data_end_ptr_POSS 0U
# define  ALT_CH02_DST_DATA_END_PTR_dst_data_end_ptr_POSE 31U
# define  ALT_CH02_DST_DATA_END_PTR_dst_data_end_ptr_MSK  BITS(ALT_CH02_DST_DATA_END_PTR_dst_data_end_ptr_POSS, ALT_CH02_DST_DATA_END_PTR_dst_data_end_ptr_POSE)
# define  ALT_CH02_DST_DATA_END_PTR_dst_data_end_ptr      ALT_CH02_DST_DATA_END_PTR_dst_data_end_ptr_MSK

/****************** Bit definition for ALT_CH02_CHANNEL_CFG register ************************/

# define  ALT_CH02_CHANNEL_CFG_dst_inc_POSS 30U
# define  ALT_CH02_CHANNEL_CFG_dst_inc_POSE 31U
# define  ALT_CH02_CHANNEL_CFG_dst_inc_MSK  BITS(ALT_CH02_CHANNEL_CFG_dst_inc_POSS, ALT_CH02_CHANNEL_CFG_dst_inc_POSE)
# define  ALT_CH02_CHANNEL_CFG_dst_inc      ALT_CH02_CHANNEL_CFG_dst_inc_MSK

# define  ALT_CH02_CHANNEL_CFG_dst_size_POSS 28U
# define  ALT_CH02_CHANNEL_CFG_dst_size_POSE 29U
# define  ALT_CH02_CHANNEL_CFG_dst_size_MSK  BITS(ALT_CH02_CHANNEL_CFG_dst_size_POSS, ALT_CH02_CHANNEL_CFG_dst_size_POSE)
# define  ALT_CH02_CHANNEL_CFG_dst_size      ALT_CH02_CHANNEL_CFG_dst_size_MSK

# define  ALT_CH02_CHANNEL_CFG_src_inc_POSS 26U
# define  ALT_CH02_CHANNEL_CFG_src_inc_POSE 27U
# define  ALT_CH02_CHANNEL_CFG_src_inc_MSK  BITS(ALT_CH02_CHANNEL_CFG_src_inc_POSS, ALT_CH02_CHANNEL_CFG_src_inc_POSE)
# define  ALT_CH02_CHANNEL_CFG_src_inc      ALT_CH02_CHANNEL_CFG_src_inc_MSK

# define  ALT_CH02_CHANNEL_CFG_src_size_POSS 24U
# define  ALT_CH02_CHANNEL_CFG_src_size_POSE 25U
# define  ALT_CH02_CHANNEL_CFG_src_size_MSK  BITS(ALT_CH02_CHANNEL_CFG_src_size_POSS, ALT_CH02_CHANNEL_CFG_src_size_POSE)
# define  ALT_CH02_CHANNEL_CFG_src_size      ALT_CH02_CHANNEL_CFG_src_size_MSK

# define  ALT_CH02_CHANNEL_CFG_dst_prot_ctrl_POSS 21U
# define  ALT_CH02_CHANNEL_CFG_dst_prot_ctrl_POSE 23U
# define  ALT_CH02_CHANNEL_CFG_dst_prot_ctrl_MSK  BITS(ALT_CH02_CHANNEL_CFG_dst_prot_ctrl_POSS, ALT_CH02_CHANNEL_CFG_dst_prot_ctrl_POSE)
# define  ALT_CH02_CHANNEL_CFG_dst_prot_ctrl      ALT_CH02_CHANNEL_CFG_dst_prot_ctrl_MSK

# define  ALT_CH02_CHANNEL_CFG_src_prot_ctrl_POSS 18U
# define  ALT_CH02_CHANNEL_CFG_src_prot_ctrl_POSE 20U
# define  ALT_CH02_CHANNEL_CFG_src_prot_ctrl_MSK  BITS(ALT_CH02_CHANNEL_CFG_src_prot_ctrl_POSS, ALT_CH02_CHANNEL_CFG_src_prot_ctrl_POSE)
# define  ALT_CH02_CHANNEL_CFG_src_prot_ctrl      ALT_CH02_CHANNEL_CFG_src_prot_ctrl_MSK

# define  ALT_CH02_CHANNEL_CFG_R_power_POSS 14U
# define  ALT_CH02_CHANNEL_CFG_R_power_POSE 17U
# define  ALT_CH02_CHANNEL_CFG_R_power_MSK  BITS(ALT_CH02_CHANNEL_CFG_R_power_POSS, ALT_CH02_CHANNEL_CFG_R_power_POSE)
# define  ALT_CH02_CHANNEL_CFG_R_power      ALT_CH02_CHANNEL_CFG_R_power_MSK

# define  ALT_CH02_CHANNEL_CFG_n_minus_1_POSS 4U
# define  ALT_CH02_CHANNEL_CFG_n_minus_1_POSE 13U
# define  ALT_CH02_CHANNEL_CFG_n_minus_1_MSK  BITS(ALT_CH02_CHANNEL_CFG_n_minus_1_POSS, ALT_CH02_CHANNEL_CFG_n_minus_1_POSE)
# define  ALT_CH02_CHANNEL_CFG_n_minus_1      ALT_CH02_CHANNEL_CFG_n_minus_1_MSK

# define  ALT_CH02_CHANNEL_CFG_next_useburst_POS 3U
# define  ALT_CH02_CHANNEL_CFG_next_useburst_MSK BIT(ALT_CH02_CHANNEL_CFG_next_useburst_POS)
# define  ALT_CH02_CHANNEL_CFG_next_useburst     ALT_CH02_CHANNEL_CFG_next_useburst_MSK

# define  ALT_CH02_CHANNEL_CFG_cycle_ctrl_POSS 0U
# define  ALT_CH02_CHANNEL_CFG_cycle_ctrl_POSE 2U
# define  ALT_CH02_CHANNEL_CFG_cycle_ctrl_MSK  BITS(ALT_CH02_CHANNEL_CFG_cycle_ctrl_POSS, ALT_CH02_CHANNEL_CFG_cycle_ctrl_POSE)
# define  ALT_CH02_CHANNEL_CFG_cycle_ctrl      ALT_CH02_CHANNEL_CFG_cycle_ctrl_MSK

/****************** Bit definition for ALT_CH03_SRC_DATA_END_PTR register ************************/

# define  ALT_CH03_SRC_DATA_END_PTR_src_data_end_ptr_POSS 0U
# define  ALT_CH03_SRC_DATA_END_PTR_src_data_end_ptr_POSE 31U
# define  ALT_CH03_SRC_DATA_END_PTR_src_data_end_ptr_MSK  BITS(ALT_CH03_SRC_DATA_END_PTR_src_data_end_ptr_POSS, ALT_CH03_SRC_DATA_END_PTR_src_data_end_ptr_POSE)
# define  ALT_CH03_SRC_DATA_END_PTR_src_data_end_ptr      ALT_CH03_SRC_DATA_END_PTR_src_data_end_ptr_MSK

/****************** Bit definition for ALT_CH03_DST_DATA_END_PTR register ************************/

# define  ALT_CH03_DST_DATA_END_PTR_dst_data_end_ptr_POSS 0U
# define  ALT_CH03_DST_DATA_END_PTR_dst_data_end_ptr_POSE 31U
# define  ALT_CH03_DST_DATA_END_PTR_dst_data_end_ptr_MSK  BITS(ALT_CH03_DST_DATA_END_PTR_dst_data_end_ptr_POSS, ALT_CH03_DST_DATA_END_PTR_dst_data_end_ptr_POSE)
# define  ALT_CH03_DST_DATA_END_PTR_dst_data_end_ptr      ALT_CH03_DST_DATA_END_PTR_dst_data_end_ptr_MSK

/****************** Bit definition for ALT_CH03_CHANNEL_CFG register ************************/

# define  ALT_CH03_CHANNEL_CFG_dst_inc_POSS 30U
# define  ALT_CH03_CHANNEL_CFG_dst_inc_POSE 31U
# define  ALT_CH03_CHANNEL_CFG_dst_inc_MSK  BITS(ALT_CH03_CHANNEL_CFG_dst_inc_POSS, ALT_CH03_CHANNEL_CFG_dst_inc_POSE)
# define  ALT_CH03_CHANNEL_CFG_dst_inc      ALT_CH03_CHANNEL_CFG_dst_inc_MSK

# define  ALT_CH03_CHANNEL_CFG_dst_size_POSS 28U
# define  ALT_CH03_CHANNEL_CFG_dst_size_POSE 29U
# define  ALT_CH03_CHANNEL_CFG_dst_size_MSK  BITS(ALT_CH03_CHANNEL_CFG_dst_size_POSS, ALT_CH03_CHANNEL_CFG_dst_size_POSE)
# define  ALT_CH03_CHANNEL_CFG_dst_size      ALT_CH03_CHANNEL_CFG_dst_size_MSK

# define  ALT_CH03_CHANNEL_CFG_src_inc_POSS 26U
# define  ALT_CH03_CHANNEL_CFG_src_inc_POSE 27U
# define  ALT_CH03_CHANNEL_CFG_src_inc_MSK  BITS(ALT_CH03_CHANNEL_CFG_src_inc_POSS, ALT_CH03_CHANNEL_CFG_src_inc_POSE)
# define  ALT_CH03_CHANNEL_CFG_src_inc      ALT_CH03_CHANNEL_CFG_src_inc_MSK

# define  ALT_CH03_CHANNEL_CFG_src_size_POSS 24U
# define  ALT_CH03_CHANNEL_CFG_src_size_POSE 25U
# define  ALT_CH03_CHANNEL_CFG_src_size_MSK  BITS(ALT_CH03_CHANNEL_CFG_src_size_POSS, ALT_CH03_CHANNEL_CFG_src_size_POSE)
# define  ALT_CH03_CHANNEL_CFG_src_size      ALT_CH03_CHANNEL_CFG_src_size_MSK

# define  ALT_CH03_CHANNEL_CFG_dst_prot_ctrl_POSS 21U
# define  ALT_CH03_CHANNEL_CFG_dst_prot_ctrl_POSE 23U
# define  ALT_CH03_CHANNEL_CFG_dst_prot_ctrl_MSK  BITS(ALT_CH03_CHANNEL_CFG_dst_prot_ctrl_POSS, ALT_CH03_CHANNEL_CFG_dst_prot_ctrl_POSE)
# define  ALT_CH03_CHANNEL_CFG_dst_prot_ctrl      ALT_CH03_CHANNEL_CFG_dst_prot_ctrl_MSK

# define  ALT_CH03_CHANNEL_CFG_src_prot_ctrl_POSS 18U
# define  ALT_CH03_CHANNEL_CFG_src_prot_ctrl_POSE 20U
# define  ALT_CH03_CHANNEL_CFG_src_prot_ctrl_MSK  BITS(ALT_CH03_CHANNEL_CFG_src_prot_ctrl_POSS, ALT_CH03_CHANNEL_CFG_src_prot_ctrl_POSE)
# define  ALT_CH03_CHANNEL_CFG_src_prot_ctrl      ALT_CH03_CHANNEL_CFG_src_prot_ctrl_MSK

# define  ALT_CH03_CHANNEL_CFG_R_power_POSS 14U
# define  ALT_CH03_CHANNEL_CFG_R_power_POSE 17U
# define  ALT_CH03_CHANNEL_CFG_R_power_MSK  BITS(ALT_CH03_CHANNEL_CFG_R_power_POSS, ALT_CH03_CHANNEL_CFG_R_power_POSE)
# define  ALT_CH03_CHANNEL_CFG_R_power      ALT_CH03_CHANNEL_CFG_R_power_MSK

# define  ALT_CH03_CHANNEL_CFG_n_minus_1_POSS 4U
# define  ALT_CH03_CHANNEL_CFG_n_minus_1_POSE 13U
# define  ALT_CH03_CHANNEL_CFG_n_minus_1_MSK  BITS(ALT_CH03_CHANNEL_CFG_n_minus_1_POSS, ALT_CH03_CHANNEL_CFG_n_minus_1_POSE)
# define  ALT_CH03_CHANNEL_CFG_n_minus_1      ALT_CH03_CHANNEL_CFG_n_minus_1_MSK

# define  ALT_CH03_CHANNEL_CFG_next_useburst_POS 3U
# define  ALT_CH03_CHANNEL_CFG_next_useburst_MSK BIT(ALT_CH03_CHANNEL_CFG_next_useburst_POS)
# define  ALT_CH03_CHANNEL_CFG_next_useburst     ALT_CH03_CHANNEL_CFG_next_useburst_MSK

# define  ALT_CH03_CHANNEL_CFG_cycle_ctrl_POSS 0U
# define  ALT_CH03_CHANNEL_CFG_cycle_ctrl_POSE 2U
# define  ALT_CH03_CHANNEL_CFG_cycle_ctrl_MSK  BITS(ALT_CH03_CHANNEL_CFG_cycle_ctrl_POSS, ALT_CH03_CHANNEL_CFG_cycle_ctrl_POSE)
# define  ALT_CH03_CHANNEL_CFG_cycle_ctrl      ALT_CH03_CHANNEL_CFG_cycle_ctrl_MSK

/****************** Bit definition for ALT_CH04_SRC_DATA_END_PTR register ************************/

# define  ALT_CH04_SRC_DATA_END_PTR_src_data_end_ptr_POSS 0U
# define  ALT_CH04_SRC_DATA_END_PTR_src_data_end_ptr_POSE 31U
# define  ALT_CH04_SRC_DATA_END_PTR_src_data_end_ptr_MSK  BITS(ALT_CH04_SRC_DATA_END_PTR_src_data_end_ptr_POSS, ALT_CH04_SRC_DATA_END_PTR_src_data_end_ptr_POSE)
# define  ALT_CH04_SRC_DATA_END_PTR_src_data_end_ptr      ALT_CH04_SRC_DATA_END_PTR_src_data_end_ptr_MSK

/****************** Bit definition for ALT_CH04_DST_DATA_END_PTR register ************************/

# define  ALT_CH04_DST_DATA_END_PTR_dst_data_end_ptr_POSS 0U
# define  ALT_CH04_DST_DATA_END_PTR_dst_data_end_ptr_POSE 31U
# define  ALT_CH04_DST_DATA_END_PTR_dst_data_end_ptr_MSK  BITS(ALT_CH04_DST_DATA_END_PTR_dst_data_end_ptr_POSS, ALT_CH04_DST_DATA_END_PTR_dst_data_end_ptr_POSE)
# define  ALT_CH04_DST_DATA_END_PTR_dst_data_end_ptr      ALT_CH04_DST_DATA_END_PTR_dst_data_end_ptr_MSK

/****************** Bit definition for ALT_CH04_CHANNEL_CFG register ************************/

# define  ALT_CH04_CHANNEL_CFG_dst_inc_POSS 30U
# define  ALT_CH04_CHANNEL_CFG_dst_inc_POSE 31U
# define  ALT_CH04_CHANNEL_CFG_dst_inc_MSK  BITS(ALT_CH04_CHANNEL_CFG_dst_inc_POSS, ALT_CH04_CHANNEL_CFG_dst_inc_POSE)
# define  ALT_CH04_CHANNEL_CFG_dst_inc      ALT_CH04_CHANNEL_CFG_dst_inc_MSK

# define  ALT_CH04_CHANNEL_CFG_dst_size_POSS 28U
# define  ALT_CH04_CHANNEL_CFG_dst_size_POSE 29U
# define  ALT_CH04_CHANNEL_CFG_dst_size_MSK  BITS(ALT_CH04_CHANNEL_CFG_dst_size_POSS, ALT_CH04_CHANNEL_CFG_dst_size_POSE)
# define  ALT_CH04_CHANNEL_CFG_dst_size      ALT_CH04_CHANNEL_CFG_dst_size_MSK

# define  ALT_CH04_CHANNEL_CFG_src_inc_POSS 26U
# define  ALT_CH04_CHANNEL_CFG_src_inc_POSE 27U
# define  ALT_CH04_CHANNEL_CFG_src_inc_MSK  BITS(ALT_CH04_CHANNEL_CFG_src_inc_POSS, ALT_CH04_CHANNEL_CFG_src_inc_POSE)
# define  ALT_CH04_CHANNEL_CFG_src_inc      ALT_CH04_CHANNEL_CFG_src_inc_MSK

# define  ALT_CH04_CHANNEL_CFG_src_size_POSS 24U
# define  ALT_CH04_CHANNEL_CFG_src_size_POSE 25U
# define  ALT_CH04_CHANNEL_CFG_src_size_MSK  BITS(ALT_CH04_CHANNEL_CFG_src_size_POSS, ALT_CH04_CHANNEL_CFG_src_size_POSE)
# define  ALT_CH04_CHANNEL_CFG_src_size      ALT_CH04_CHANNEL_CFG_src_size_MSK

# define  ALT_CH04_CHANNEL_CFG_dst_prot_ctrl_POSS 21U
# define  ALT_CH04_CHANNEL_CFG_dst_prot_ctrl_POSE 23U
# define  ALT_CH04_CHANNEL_CFG_dst_prot_ctrl_MSK  BITS(ALT_CH04_CHANNEL_CFG_dst_prot_ctrl_POSS, ALT_CH04_CHANNEL_CFG_dst_prot_ctrl_POSE)
# define  ALT_CH04_CHANNEL_CFG_dst_prot_ctrl      ALT_CH04_CHANNEL_CFG_dst_prot_ctrl_MSK

# define  ALT_CH04_CHANNEL_CFG_src_prot_ctrl_POSS 18U
# define  ALT_CH04_CHANNEL_CFG_src_prot_ctrl_POSE 20U
# define  ALT_CH04_CHANNEL_CFG_src_prot_ctrl_MSK  BITS(ALT_CH04_CHANNEL_CFG_src_prot_ctrl_POSS, ALT_CH04_CHANNEL_CFG_src_prot_ctrl_POSE)
# define  ALT_CH04_CHANNEL_CFG_src_prot_ctrl      ALT_CH04_CHANNEL_CFG_src_prot_ctrl_MSK

# define  ALT_CH04_CHANNEL_CFG_R_power_POSS 14U
# define  ALT_CH04_CHANNEL_CFG_R_power_POSE 17U
# define  ALT_CH04_CHANNEL_CFG_R_power_MSK  BITS(ALT_CH04_CHANNEL_CFG_R_power_POSS, ALT_CH04_CHANNEL_CFG_R_power_POSE)
# define  ALT_CH04_CHANNEL_CFG_R_power      ALT_CH04_CHANNEL_CFG_R_power_MSK

# define  ALT_CH04_CHANNEL_CFG_n_minus_1_POSS 4U
# define  ALT_CH04_CHANNEL_CFG_n_minus_1_POSE 13U
# define  ALT_CH04_CHANNEL_CFG_n_minus_1_MSK  BITS(ALT_CH04_CHANNEL_CFG_n_minus_1_POSS, ALT_CH04_CHANNEL_CFG_n_minus_1_POSE)
# define  ALT_CH04_CHANNEL_CFG_n_minus_1      ALT_CH04_CHANNEL_CFG_n_minus_1_MSK

# define  ALT_CH04_CHANNEL_CFG_next_useburst_POS 3U
# define  ALT_CH04_CHANNEL_CFG_next_useburst_MSK BIT(ALT_CH04_CHANNEL_CFG_next_useburst_POS)
# define  ALT_CH04_CHANNEL_CFG_next_useburst     ALT_CH04_CHANNEL_CFG_next_useburst_MSK

# define  ALT_CH04_CHANNEL_CFG_cycle_ctrl_POSS 0U
# define  ALT_CH04_CHANNEL_CFG_cycle_ctrl_POSE 2U
# define  ALT_CH04_CHANNEL_CFG_cycle_ctrl_MSK  BITS(ALT_CH04_CHANNEL_CFG_cycle_ctrl_POSS, ALT_CH04_CHANNEL_CFG_cycle_ctrl_POSE)
# define  ALT_CH04_CHANNEL_CFG_cycle_ctrl      ALT_CH04_CHANNEL_CFG_cycle_ctrl_MSK

/****************** Bit definition for ALT_CH05_SRC_DATA_END_PTR register ************************/

# define  ALT_CH05_SRC_DATA_END_PTR_src_data_end_ptr_POSS 0U
# define  ALT_CH05_SRC_DATA_END_PTR_src_data_end_ptr_POSE 31U
# define  ALT_CH05_SRC_DATA_END_PTR_src_data_end_ptr_MSK  BITS(ALT_CH05_SRC_DATA_END_PTR_src_data_end_ptr_POSS, ALT_CH05_SRC_DATA_END_PTR_src_data_end_ptr_POSE)
# define  ALT_CH05_SRC_DATA_END_PTR_src_data_end_ptr      ALT_CH05_SRC_DATA_END_PTR_src_data_end_ptr_MSK

/****************** Bit definition for ALT_CH05_DST_DATA_END_PTR register ************************/

# define  ALT_CH05_DST_DATA_END_PTR_dst_data_end_ptr_POSS 0U
# define  ALT_CH05_DST_DATA_END_PTR_dst_data_end_ptr_POSE 31U
# define  ALT_CH05_DST_DATA_END_PTR_dst_data_end_ptr_MSK  BITS(ALT_CH05_DST_DATA_END_PTR_dst_data_end_ptr_POSS, ALT_CH05_DST_DATA_END_PTR_dst_data_end_ptr_POSE)
# define  ALT_CH05_DST_DATA_END_PTR_dst_data_end_ptr      ALT_CH05_DST_DATA_END_PTR_dst_data_end_ptr_MSK

/****************** Bit definition for ALT_CH05_CHANNEL_CFG register ************************/

# define  ALT_CH05_CHANNEL_CFG_dst_inc_POSS 30U
# define  ALT_CH05_CHANNEL_CFG_dst_inc_POSE 31U
# define  ALT_CH05_CHANNEL_CFG_dst_inc_MSK  BITS(ALT_CH05_CHANNEL_CFG_dst_inc_POSS, ALT_CH05_CHANNEL_CFG_dst_inc_POSE)
# define  ALT_CH05_CHANNEL_CFG_dst_inc      ALT_CH05_CHANNEL_CFG_dst_inc_MSK

# define  ALT_CH05_CHANNEL_CFG_dst_size_POSS 28U
# define  ALT_CH05_CHANNEL_CFG_dst_size_POSE 29U
# define  ALT_CH05_CHANNEL_CFG_dst_size_MSK  BITS(ALT_CH05_CHANNEL_CFG_dst_size_POSS, ALT_CH05_CHANNEL_CFG_dst_size_POSE)
# define  ALT_CH05_CHANNEL_CFG_dst_size      ALT_CH05_CHANNEL_CFG_dst_size_MSK

# define  ALT_CH05_CHANNEL_CFG_src_inc_POSS 26U
# define  ALT_CH05_CHANNEL_CFG_src_inc_POSE 27U
# define  ALT_CH05_CHANNEL_CFG_src_inc_MSK  BITS(ALT_CH05_CHANNEL_CFG_src_inc_POSS, ALT_CH05_CHANNEL_CFG_src_inc_POSE)
# define  ALT_CH05_CHANNEL_CFG_src_inc      ALT_CH05_CHANNEL_CFG_src_inc_MSK

# define  ALT_CH05_CHANNEL_CFG_src_size_POSS 24U
# define  ALT_CH05_CHANNEL_CFG_src_size_POSE 25U
# define  ALT_CH05_CHANNEL_CFG_src_size_MSK  BITS(ALT_CH05_CHANNEL_CFG_src_size_POSS, ALT_CH05_CHANNEL_CFG_src_size_POSE)
# define  ALT_CH05_CHANNEL_CFG_src_size      ALT_CH05_CHANNEL_CFG_src_size_MSK

# define  ALT_CH05_CHANNEL_CFG_dst_prot_ctrl_POSS 21U
# define  ALT_CH05_CHANNEL_CFG_dst_prot_ctrl_POSE 23U
# define  ALT_CH05_CHANNEL_CFG_dst_prot_ctrl_MSK  BITS(ALT_CH05_CHANNEL_CFG_dst_prot_ctrl_POSS, ALT_CH05_CHANNEL_CFG_dst_prot_ctrl_POSE)
# define  ALT_CH05_CHANNEL_CFG_dst_prot_ctrl      ALT_CH05_CHANNEL_CFG_dst_prot_ctrl_MSK

# define  ALT_CH05_CHANNEL_CFG_src_prot_ctrl_POSS 18U
# define  ALT_CH05_CHANNEL_CFG_src_prot_ctrl_POSE 20U
# define  ALT_CH05_CHANNEL_CFG_src_prot_ctrl_MSK  BITS(ALT_CH05_CHANNEL_CFG_src_prot_ctrl_POSS, ALT_CH05_CHANNEL_CFG_src_prot_ctrl_POSE)
# define  ALT_CH05_CHANNEL_CFG_src_prot_ctrl      ALT_CH05_CHANNEL_CFG_src_prot_ctrl_MSK

# define  ALT_CH05_CHANNEL_CFG_R_power_POSS 14U
# define  ALT_CH05_CHANNEL_CFG_R_power_POSE 17U
# define  ALT_CH05_CHANNEL_CFG_R_power_MSK  BITS(ALT_CH05_CHANNEL_CFG_R_power_POSS, ALT_CH05_CHANNEL_CFG_R_power_POSE)
# define  ALT_CH05_CHANNEL_CFG_R_power      ALT_CH05_CHANNEL_CFG_R_power_MSK

# define  ALT_CH05_CHANNEL_CFG_n_minus_1_POSS 4U
# define  ALT_CH05_CHANNEL_CFG_n_minus_1_POSE 13U
# define  ALT_CH05_CHANNEL_CFG_n_minus_1_MSK  BITS(ALT_CH05_CHANNEL_CFG_n_minus_1_POSS, ALT_CH05_CHANNEL_CFG_n_minus_1_POSE)
# define  ALT_CH05_CHANNEL_CFG_n_minus_1      ALT_CH05_CHANNEL_CFG_n_minus_1_MSK

# define  ALT_CH05_CHANNEL_CFG_next_useburst_POS 3U
# define  ALT_CH05_CHANNEL_CFG_next_useburst_MSK BIT(ALT_CH05_CHANNEL_CFG_next_useburst_POS)
# define  ALT_CH05_CHANNEL_CFG_next_useburst     ALT_CH05_CHANNEL_CFG_next_useburst_MSK

# define  ALT_CH05_CHANNEL_CFG_cycle_ctrl_POSS 0U
# define  ALT_CH05_CHANNEL_CFG_cycle_ctrl_POSE 2U
# define  ALT_CH05_CHANNEL_CFG_cycle_ctrl_MSK  BITS(ALT_CH05_CHANNEL_CFG_cycle_ctrl_POSS, ALT_CH05_CHANNEL_CFG_cycle_ctrl_POSE)
# define  ALT_CH05_CHANNEL_CFG_cycle_ctrl      ALT_CH05_CHANNEL_CFG_cycle_ctrl_MSK


typedef struct
{
  __I  uint32_t STATUS;                       // 0x000
  __O  uint32_t CFG;                          // 0x004
  __IO uint32_t RESERVED0[2];                 // 0x008-0x00c
  __I  uint32_t CHWAITSTATUS;                 // 0x010
  __O  uint32_t CHSWREQ;                      // 0x014
  __IO uint32_t CHUSEBURSTSET;                // 0x018
  __O  uint32_t CHUSEBURSTCLR;                // 0x01c
  __IO uint32_t CHREQMASKSET;                 // 0x020
  __O  uint32_t CHREQMASKCLR;                 // 0x024
  __IO uint32_t CHENSET;                      // 0x028
  __O  uint32_t CHENCLR;                      // 0x02c
  __IO uint32_t CHPRIALTSET;                  // 0x030
  __O  uint32_t CHPRIALTCLR;                  // 0x034
  __IO uint32_t CHPRSET;                      // 0x038
  __O  uint32_t CHPRCLR;                      // 0x03c
  __IO uint32_t RESERVED1[3];                 // 0x040-0x048
  __IO uint32_t ERRCLR;                       // 0x04c
  __O  uint32_t IER;                          // 0x050
  __O  uint32_t IDR;                          // 0x054
  __I  uint32_t IVS;                          // 0x058
  __I  uint32_t RIF;                          // 0x05c
  __I  uint32_t IFM;                          // 0x060
  __O  uint32_t ICR;                          // 0x064
  __IO uint32_t RESERVED2[2];                 // 0x068-0x06c
  __IO uint32_t CH0_SELCON;                   // 0x070
  __IO uint32_t CH1_SELCON;                   // 0x074
  __IO uint32_t CH2_SELCON;                   // 0x078
  __IO uint32_t CH3_SELCON;                   // 0x07c
  __IO uint32_t CH4_SELCON;                   // 0x080
  __IO uint32_t CH5_SELCON;                   // 0x084
  __IO uint32_t RESERVED3[30];                // 0x088-0x0fc
  __IO uint32_t PRI_CH00_SRC_DATA_END_PTR;    // 0x100
  __IO uint32_t PRI_CH00_DST_DATA_END_PTR;    // 0x104
  __IO uint32_t PRI_CH00_CHANNEL_CFG;         // 0x108
  __IO uint32_t RESERVED4;                    // 0x10c
  __IO uint32_t PRI_CH01_SRC_DATA_END_PTR;    // 0x110
  __IO uint32_t PRI_CH01_DST_DATA_END_PTR;    // 0x114
  __IO uint32_t PRI_CH01_CHANNEL_CFG;         // 0x118
  __IO uint32_t RESERVED5;                    // 0x11c
  __IO uint32_t PRI_CH02_SRC_DATA_END_PTR;    // 0x120
  __IO uint32_t PRI_CH02_DST_DATA_END_PTR;    // 0x124
  __IO uint32_t PRI_CH02_CHANNEL_CFG;         // 0x128
  __IO uint32_t RESERVED6;                    // 0x12c
  __IO uint32_t PRI_CH03_SRC_DATA_END_PTR;    // 0x130
  __IO uint32_t PRI_CH03_DST_DATA_END_PTR;    // 0x134
  __IO uint32_t PRI_CH03_CHANNEL_CFG;         // 0x138
  __IO uint32_t RESERVED7;                    // 0x13c
  __IO uint32_t PRI_CH04_SRC_DATA_END_PTR;    // 0x140
  __IO uint32_t PRI_CH04_DST_DATA_END_PTR;    // 0x144
  __IO uint32_t PRI_CH04_CHANNEL_CFG;         // 0x148
  __IO uint32_t RESERVED8;                    // 0x14c
  __IO uint32_t PRI_CH05_SRC_DATA_END_PTR;    // 0x150
  __IO uint32_t PRI_CH05_DST_DATA_END_PTR;    // 0x154
  __IO uint32_t PRI_CH05_CHANNEL_CFG;         // 0x158
  __IO uint32_t RESERVED9[41];                // 0x15c-0x1fc
  __IO uint32_t ALT_CH00_SRC_DATA_END_PTR;    // 0x200
  __IO uint32_t ALT_CH00_DST_DATA_END_PTR;    // 0x204
  __IO uint32_t ALT_CH00_CHANNEL_CFG;         // 0x208
  __IO uint32_t RESERVED10;                   // 0x20c
  __IO uint32_t ALT_CH01_SRC_DATA_END_PTR;    // 0x210
  __IO uint32_t ALT_CH01_DST_DATA_END_PTR;    // 0x214
  __IO uint32_t ALT_CH01_CHANNEL_CFG;         // 0x218
  __IO uint32_t RESERVED11;                   // 0x21c
  __IO uint32_t ALT_CH02_SRC_DATA_END_PTR;    // 0x220
  __IO uint32_t ALT_CH02_DST_DATA_END_PTR;    // 0x224
  __IO uint32_t ALT_CH02_CHANNEL_CFG;         // 0x228
  __IO uint32_t RESERVED12;                   // 0x22c
  __IO uint32_t ALT_CH03_SRC_DATA_END_PTR;    // 0x230
  __IO uint32_t ALT_CH03_DST_DATA_END_PTR;    // 0x234
  __IO uint32_t ALT_CH03_CHANNEL_CFG;         // 0x238
  __IO uint32_t RESERVED13;                   // 0x23c
  __IO uint32_t ALT_CH04_SRC_DATA_END_PTR;    // 0x240
  __IO uint32_t ALT_CH04_DST_DATA_END_PTR;    // 0x244
  __IO uint32_t ALT_CH04_CHANNEL_CFG;         // 0x248
  __IO uint32_t RESERVED14;                   // 0x24c
  __IO uint32_t ALT_CH05_SRC_DATA_END_PTR;    // 0x250
  __IO uint32_t ALT_CH05_DST_DATA_END_PTR;    // 0x254
  __IO uint32_t ALT_CH05_CHANNEL_CFG;         // 0x258
} DMA_TypeDef;


#endif
