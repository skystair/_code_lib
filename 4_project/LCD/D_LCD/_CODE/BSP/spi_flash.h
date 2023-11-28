#ifndef __SPI_FLASH_H__
#define __SPI_FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g45x.h"

/**
 * @brief  SPI Flash supported commands
 */
#define sFLASH_CMD_WRITE 0x02 /*!< Write to Memory instruction */
#define sFLASH_CMD_WRSR  0x01 /*!< Write Status Register instruction */
#define sFLASH_CMD_WREN  0x06 /*!< Write enable instruction */
#define sFLASH_CMD_READ  0x03 /*!< Read from Memory instruction */
#define sFLASH_CMD_RDSR  0x05 /*!< Read Status Register instruction  */
#define sFLASH_CMD_RDID  0x9F /*!< Read identification */
#define sFLASH_CMD_SE    0x20 /*!< Sector Erase instruction */
#define sFLASH_CMD_BE    0xC7 /*!< Bulk Erase instruction */

#define sFLASH_WIP_FLAG 0x01 /*!< Write In Progress (WIP) flag */

#define sFLASH_DUMMY_BYTE   0xA5
#define sFLASH_SPI_PAGESIZE 0x100


#define sFLASH_W25Q128_ID 0x00EF4018
#define sFLASH_M25P64_ID  0x202017

//#define SPI_MASTER_DR_Base 0x4001300C


/**
 * @brief  Select sFLASH: Chip Select pin low
 */
#define sFLASH_CS_LOW() GPIO_ResetBits(FLASH_PORT_CS, FLASH_PIN_CS)
/**
 * @brief  Deselect sFLASH: Chip Select pin high
 */
#define sFLASH_CS_HIGH() GPIO_SetBits(FLASH_PORT_CS, FLASH_PIN_CS)
/**
 * @}
 */


uint8_t sFLASH_ReadByte(void);
uint8_t sFLASH_SendByte(uint8_t byte);
uint16_t sFLASH_SendHalfWord(uint16_t HalfWord);

uint32_t sFLASH_ReadID(void);

void sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, unsigned int NumByteToRead);
void sFLASH_ReadBuffer16(uint16_t* pBuffer, uint32_t ReadAddr, unsigned int NumByteToRead);

void SPI_DMA_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void SPI_DMA_BufferRead(uint8_t* pbuffer, uint32_t ReadAddr, uint16_t num_byte_to_read);


#ifdef __cplusplus
}
#endif

#endif
