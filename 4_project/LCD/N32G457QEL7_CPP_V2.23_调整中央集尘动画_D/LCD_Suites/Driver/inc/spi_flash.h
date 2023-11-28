#ifndef __SPI_FLASH_H__
#define __SPI_FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g45x.h"

#define FLASH_SPI_SELCETED 2

#if FLASH_SPI_SELCETED == 1
#define FLASH_SPI								SPI1

#define FLASH_PORT_CS						GPIOA
#define FLASH_PIN_CS						GPIO_PIN_4
#define FLASH_PORT_MOSI					GPIOA
#define FLASH_PIN_MOSI					GPIO_PIN_7
#define FLASH_PORT_MISO					GPIOA
#define FLASH_PIN_MISO					GPIO_PIN_6
#define FLASH_PORT_CLK					GPIOA
#define FLASH_PIN_CLK						GPIO_PIN_5

#define FLASH_DMA								DMA1
#define FLASH_TX_DMA						DMA1_CH3
#define FLASH_RX_DMA						DMA1_CH2
#define FLASH_DMA_TX_TC					DMA1_FLAG_TC3
#define FLASH_DMA_RX_TC 				DMA1_FLAG_TC2

#define FLASH_DMA_CLK						RCC_AHB_PERIPH_DMA1
#define FLASH_GPIO_CLK					RCC_APB2_PERIPH_GPIOA|RCC_APB2_PERIPH_AFIO
#define FLASH_SPI_CLK_ENABLE()	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_SPI1, ENABLE)
//#define FLASH_SPI_CLK_DISABLE()	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_SPI1, DISABLE);

#elif FLASH_SPI_SELCETED == 2
#define FLASH_SPI								SPI2

#define FLASH_PORT_CS						GPIOB
#define FLASH_PIN_CS						GPIO_PIN_12
#define FLASH_PORT_MOSI					GPIOB
#define FLASH_PIN_MOSI					GPIO_PIN_15
#define FLASH_PORT_MISO					GPIOB
#define FLASH_PIN_MISO					GPIO_PIN_14
#define FLASH_PORT_CLK					GPIOB
#define FLASH_PIN_CLK						GPIO_PIN_13

#define FLASH_DMA								DMA1
#define FLASH_TX_DMA						DMA1_CH5
#define FLASH_RX_DMA						DMA1_CH4
#define FLASH_DMA_TX_TC					DMA1_FLAG_TC5
#define FLASH_DMA_RX_TC 				DMA1_FLAG_TC4

#define FLASH_DMA_CLK						RCC_AHB_PERIPH_DMA1
#define FLASH_GPIO_CLK					RCC_APB2_PERIPH_GPIOB|RCC_APB2_PERIPH_AFIO
#define FLASH_SPI_CLK_ENABLE()	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_SPI2, ENABLE)

#endif

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

/** @addtogroup SPI_FLASH_Exported_Functions
 * @{
 */
/**
 * @brief  High layer functions
 */
void sFLASH_DeInit(void);
void sFLASH_EraseBulk(void);
void sFLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void sFLASH_StartReadSequence(uint32_t ReadAddr);

/**
 * @brief  Low layer functions
 */
void SPI_Read_Write_Flash_Test(void);
uint8_t sFLASH_ReadByte(void);
uint8_t sFLASH_SendByte(uint8_t byte);
uint16_t sFLASH_SendHalfWord(uint16_t HalfWord);
void sFLASH_WriteEnable(void);
void sFLASH_WaitForWriteEnd(void);


void sFLASH_Init(void);
void DMA_Flash_Init(void);

uint32_t sFLASH_ReadID(void);

void sFLASH_EraseSector(uint32_t SectorAddr);

void sFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);

void SPI_DMA_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void SPI_DMA_BufferRead(uint8_t* pbuffer, uint32_t ReadAddr, uint16_t num_byte_to_read);


#ifdef __cplusplus
}
#endif

#endif
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
