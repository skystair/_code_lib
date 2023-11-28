#include "spi_flash.h"
#include "IOconfig.h"


unsigned char Empty;

#define sFLASH_ID 0xC84019/*sFLASH_W25Q128_ID*/

//#define BufferSize (countof(Tx_Buffer)-1)
//#define countof(a) (sizeof(a) / sizeof(*(a)))


void sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, unsigned int NumByteToRead)
{
    /*!< Select the FLASH: Chip Select low */
    sFLASH_CS_LOW();

    /*!< Send "Read from Memory " instruction */
    sFLASH_SendByte(sFLASH_CMD_READ);

    /*!< Send ReadAddr high nibble address byte to read from */
    sFLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
    /*!< Send ReadAddr medium nibble address byte to read from */
    sFLASH_SendByte((ReadAddr & 0xFF00) >> 8);
    /*!< Send ReadAddr low nibble address byte to read from */
    sFLASH_SendByte(ReadAddr & 0xFF);
    
    while (NumByteToRead--) /*!< while there is data to be read */
    {
        /*!< Read a byte from the FLASH */
        *pBuffer = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
        /*!< Point to the next location where the byte read will be saved */
        pBuffer++;
    }

    /*!< Deselect the FLASH: Chip Select high */
    sFLASH_CS_HIGH();
}

void sFLASH_ReadBuffer16(uint16_t* pBuffer, uint32_t ReadAddr, unsigned int NumByteToRead)
{
    /*!< Select the FLASH: Chip Select low */
    sFLASH_CS_LOW();

    /*!< Send "Read from Memory " instruction */
    sFLASH_SendByte(sFLASH_CMD_READ);

    /*!< Send ReadAddr high nibble address byte to read from */
    sFLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
    /*!< Send ReadAddr medium nibble address byte to read from */
    sFLASH_SendByte((ReadAddr & 0xFF00) >> 8);
    /*!< Send ReadAddr low nibble address byte to read from */
    sFLASH_SendByte(ReadAddr & 0xFF);
    
    while (NumByteToRead--) /*!< while there is data to be read */
    {
		unsigned short int u16tmp;
        /*!< Read a byte from the FLASH */
        u16tmp = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
		u16tmp = u16tmp << 8;
		u16tmp += sFLASH_SendByte(sFLASH_DUMMY_BYTE);
		*pBuffer = u16tmp;
        /*!< Point to the next location where the byte read will be saved */
        pBuffer++;
    }

    /*!< Deselect the FLASH: Chip Select high */
    sFLASH_CS_HIGH();
}

/**
 * @brief  Reads FLASH identification.
 * @return FLASH identification
 */
uint32_t sFLASH_ReadID(void)
{
    uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

    /*!< Select the FLASH: Chip Select low */
    sFLASH_CS_LOW();

    /*!< Send "RDID " instruction */
    sFLASH_SendByte(0x9F);
    /*!< Read a byte from the FLASH */
    Temp0 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

    /*!< Read a byte from the FLASH */
    Temp1 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

    /*!< Read a byte from the FLASH */
    Temp2 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

    /*!< Deselect the FLASH: Chip Select high */
    sFLASH_CS_HIGH();

    Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;

    return Temp;
}


uint8_t sFLASH_ReadByte(void)
{
    return (sFLASH_SendByte(sFLASH_DUMMY_BYTE));
}


uint8_t sFLASH_SendByte(uint8_t byte)
{
	int timeout = 50000;
    /*!< Loop while DAT register in not emplty */
    while (SPI_I2S_GetStatus(FLASH_SPI, SPI_I2S_TE_FLAG) == RESET)
        ;

    /*!< Send byte through the FLASH_SPI peripheral */
    SPI_I2S_TransmitData(FLASH_SPI, byte);

    /*!< Wait to receive a byte */
    while (SPI_I2S_GetStatus(FLASH_SPI, SPI_I2S_RNE_FLAG) == RESET&&timeout>0)
        timeout--;

    /*!< Return the byte read from the SPI bus */
    return (uint8_t)SPI_I2S_ReceiveData(FLASH_SPI);
}


void sFLASH_WriteEnable(void)
{
    /*!< Select the FLASH: Chip Select low */
    sFLASH_CS_LOW();

    /*!< Send "Write Enable" instruction */
    sFLASH_SendByte(sFLASH_CMD_WREN);

    /*!< Deselect the FLASH: Chip Select high */
    sFLASH_CS_HIGH();
}

void sFLASH_WaitForWriteEnd(void)
{
    uint8_t flashstatus = 0;

    /*!< Select the FLASH: Chip Select low */
    sFLASH_CS_LOW();

    /*!< Send "Read Status Register" instruction */
    sFLASH_SendByte(sFLASH_CMD_RDSR);

    /*!< Loop as long as the memory is busy with a write cycle */
    do
    {
        /*!< Send a dummy byte to generate the clock needed by the FLASH
        and put the value of the status register in FLASH_STS variable */
        flashstatus = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

    } while ((flashstatus & sFLASH_WIP_FLAG) == SET); /* Write in progress */

    /*!< Deselect the FLASH: Chip Select high */
    sFLASH_CS_HIGH();
}

void SPI_DMA_BufferRead(uint8_t* pbuffer, uint32_t ReadAddr, uint16_t num_byte_to_read)
{
	if(num_byte_to_read == 0)
	{
		return;
	}
	Empty = sFLASH_DUMMY_BYTE;
	FLASH_TX_DMA->TXNUM = num_byte_to_read;
	FLASH_TX_DMA->MADDR = (uint32_t)&Empty;
	FLASH_TX_DMA->CHCFG &= ~DMA_MEM_INC_ENABLE;	

	FLASH_RX_DMA->TXNUM = num_byte_to_read;
	FLASH_RX_DMA->MADDR = (uint32_t)pbuffer;
	FLASH_RX_DMA->CHCFG |= DMA_MEM_INC_ENABLE;	

	/* Select the FLASH: Chip Select low */
	sFLASH_CS_LOW();

	/* Send "Read from Memory " instruction */
	sFLASH_SendByte(sFLASH_CMD_READ);

	/* Send ReadAddr high nibble address byte to read from */
	sFLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
	/* Send ReadAddr medium nibble address byte to read from */
	sFLASH_SendByte((ReadAddr& 0xFF00) >> 8);
	/* Send ReadAddr low nibble address byte to read from */
	sFLASH_SendByte(ReadAddr & 0xFF);
		 
	//DMA_EnableChannel(FLASH_RX_DMA, ENABLE);
	DMA_EnableChannel(FLASH_TX_DMA, ENABLE);
	//SPI_I2S_EnableDma(FLASH_SPI, SPI_I2S_DMA_RX, ENABLE);
	SPI_I2S_EnableDma(FLASH_SPI, SPI_I2S_DMA_TX, ENABLE);
	
	/* Wait for FLASH_DMA_RX_TC transfer complete */
	while (!DMA_GetFlagStatus(FLASH_DMA_RX_TC, FLASH_DMA)){};

	/* Deselect the FLASH: Chip Select high */
	sFLASH_CS_HIGH();

	DMA_EnableChannel(FLASH_RX_DMA, DISABLE);
	DMA_EnableChannel(FLASH_TX_DMA, DISABLE);
	SPI_I2S_EnableDma(FLASH_SPI, SPI_I2S_DMA_RX, DISABLE);
	SPI_I2S_EnableDma(FLASH_SPI, SPI_I2S_DMA_TX, DISABLE);
	
	FLASH_SPI->DAT;
	
			/*!< Wait the end of Flash writing */
	sFLASH_WaitForWriteEnd();
		
	DMA_ClearFlag(FLASH_DMA_RX_TC,FLASH_DMA);
	DMA_ClearFlag(FLASH_DMA_TX_TC,FLASH_DMA);
}

