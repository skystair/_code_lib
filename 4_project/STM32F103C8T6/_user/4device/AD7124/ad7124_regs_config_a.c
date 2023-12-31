/*!
 *****************************************************************************
  @file:  ad7124_regs_config_a.c

  @brief: Configuration file A for AD7124

  @details:
 -----------------------------------------------------------------------------
Copyright (c) 2019 Analog Devices, Inc.

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
  - Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
  - Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
	and/or other materials provided with the distribution.
  - Modified versions of the software must be conspicuously marked as such.
  - This software is licensed solely and exclusively for use with processors/
    products manufactured by or for Analog Devices, Inc.
  - This software may not be combined or merged with other code in any manner
    that would cause the software to become subject to terms and conditions
	which differ from those listed here.
  - Neither the name of Analog Devices, Inc. nor the names of its contributors
    may be used to endorse or promote products derived from this software without
    specific prior written permission.
  - The use of this software may or may not infringe the patent rights of one
    or more patent holders.  This license does not release you from the
	requirement that you obtain separate licenses from these patent holders
	to use this software.

THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES, INC. AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-
INFRINGEMENT, TITLE, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL ANALOG DEVICES, INC. OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, PUNITIVE OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, DAMAGES ARISING OUT OF
CLAIMS OF INTELLECTUAL PROPERTY RIGHTS INFRINGEMENT; PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

20180927-7CBSD SLA

*****************************************************************************/

#include "ad7124_regs.h"

const struct ad7124_st_reg ad7124_regs_config_a[AD7124_REG_NO] = {
	{0x00, 0x00,   1, 2}, /* AD7124_Status */		//default
	{0x01, 0x01c0, 2, 1}, /* AD7124_ADC_Control */	//REF_EN FullPWR
	{0x02, 0x0000, 3, 2}, /* AD7124_Data */			//default
	{0x03, 0x00, 3, 1}, /* AD7124_IOCon1 */			//default
	{0x04, 0x00, 2, 1}, /* AD7124_IOCon2 */			//default
	{0x05, 0x00,   1, 2}, /* AD7124_ID */
	{0x06, 0x0000, 3, 2}, /* AD7124_Error */
	{0x07, 0x0044, 3, 1}, /* AD7124_Error_En */
	{0x08, 0x00,   1, 2}, /* AD7124_Mclk_Count */
	{0x09, 0x800f, 2, 1}, /* AD7124_Channel_0 */ //0-1 //0x8001 //使能通道寄存器0,配置寄存器0,AIN0->AINP,AIN1->AINM
	{0x0A, 0x802f, 2, 1}, /* AD7124_Channel_1 */ //2-3	//0x8043
	{0x0B, 0x804f, 2, 1}, /* AD7124_Channel_2 */ //4-5	//0x8085
	{0x0C, 0x806f, 2, 1}, /* AD7124_Channel_3 */ //6-7	//0x80C7
	{0x0D, 0x808f, 2, 1}, /* AD7124_Channel_4 */ //8-9	//0x8109
	{0x0E, 0x80af, 2, 1}, /* AD7124_Channel_5 */ //10-11 0x814B
	{0x0F, 0x80cf, 2, 1}, /* AD7124_Channel_6 */ //12-13	0x018D
	{0x10, 0x80ef, 2, 1}, /* AD7124_Channel_7 */ //14-15	0x01CF
	{0x11, 0x0001, 2, 1}, /* AD7124_Channel_8 */
	{0x12, 0x0001, 2, 1}, /* AD7124_Channel_9 */
	{0x13, 0x0001, 2, 1}, /* AD7124_Channel_10 */
	{0x14, 0x0001, 2, 1}, /* AD7124_Channel_11 */
	{0x15, 0x0001, 2, 1}, /* AD7124_Channel_12 */
	{0x16, 0x0001, 2, 1}, /* AD7124_Channel_13 */
	{0x17, 0x0001, 2, 1}, /* AD7124_Channel_14 */
	{0x18, 0x0001, 2, 1}, /* AD7124_Channel_15 */
	{0x19, 0x0010, 2, 1}, /* AD7124_Config_0 */     //开启缓冲器 使用ref1 增益1
	{0x1A, 0x0010, 2, 1}, /* AD7124_Config_1 */
	{0x1B, 0x0010, 2, 1}, /* AD7124_Config_2 */
	{0x1C, 0x0010, 2, 1}, /* AD7124_Config_3 */
	{0x1D, 0x0010, 2, 1}, /* AD7124_Config_4 */
	{0x1E, 0x0010, 2, 1}, /* AD7124_Config_5 */
	{0x1F, 0x0010, 2, 1}, /* AD7124_Config_6 */
	{0x20, 0x0010, 2, 1}, /* AD7124_Config_7 */
	{0x21, 0x460780, 3, 1}, /* AD7124_Filter_0 */
	{0x22, 0x460780, 3, 1}, /* AD7124_Filter_1 */
	{0x23, 0x460780, 3, 1}, /* AD7124_Filter_2 */
	{0x24, 0x460780, 3, 1}, /* AD7124_Filter_3 */
	{0x25, 0x460780, 3, 1}, /* AD7124_Filter_4 */
	{0x26, 0x460780, 3, 1}, /* AD7124_Filter_5 */
	{0x27, 0x460780, 3, 1}, /* AD7124_Filter_6 */
	{0x28, 0x460780, 3, 1}, /* AD7124_Filter_7 */
	{0x29, 0x800000, 3, 1}, /* AD7124_Offset_0 */
	{0x2A, 0x800000, 3, 1}, /* AD7124_Offset_1 */
	{0x2B, 0x800000, 3, 1}, /* AD7124_Offset_2 */
	{0x2C, 0x800000, 3, 1}, /* AD7124_Offset_3 */
	{0x2D, 0x800000, 3, 1}, /* AD7124_Offset_4 */
	{0x2E, 0x800000, 3, 1}, /* AD7124_Offset_5 */
	{0x2F, 0x800000, 3, 1}, /* AD7124_Offset_6 */
	{0x30, 0x800000, 3, 1}, /* AD7124_Offset_7 */
	{0x31, 0x500000, 3, 1}, /* AD7124_Gain_0 */
	{0x32, 0x500000, 3, 1}, /* AD7124_Gain_1 */
	{0x33, 0x500000, 3, 1}, /* AD7124_Gain_2 */
	{0x34, 0x500000, 3, 1}, /* AD7124_Gain_3 */
	{0x35, 0x500000, 3, 1}, /* AD7124_Gain_4 */
	{0x36, 0x500000, 3, 1}, /* AD7124_Gain_5 */
	{0x37, 0x500000, 3, 1}, /* AD7124_Gain_6 */
	{0x38, 0x500000, 3, 1}, /* AD7124_Gain_7 */
};
