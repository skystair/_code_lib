#include "spi_flash.h"



static SPI_InitType SPI_InitStructure;
unsigned char Empty;

#define sFLASH_ID 0xC84019/*sFLASH_W25Q128_ID*/

//#define BufferSize (countof(Tx_Buffer)-1)
//#define countof(a) (sizeof(a) / sizeof(*(a)))

/**
 * @brief  FLASH DMA INIT
 */
DMA_InitType DMA_InitStructureRx;
DMA_InitType DMA_InitStructureTx;
void DMA_Flash_Init(void)
{
  //  DMA_InitType DMA_InitStructure;

    /*ENABLE DMA CLK*/
    RCC_EnableAHBPeriphClk(FLASH_DMA_CLK, ENABLE);

    /* SPI_FLASH_Rx_DMA_Channel configuration ---------------------------------------------*/
    DMA_DeInit(FLASH_RX_DMA);
    DMA_InitStructureRx.PeriphAddr     = (uint32_t)&(FLASH_SPI->DAT);
    DMA_InitStructureRx.MemAddr        = (uint32_t)0;
    
    DMA_InitStructureRx.BufSize        = 0;
    DMA_InitStructureRx.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructureRx.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructureRx.PeriphDataSize = DMA_PERIPH_DATA_SIZE_BYTE;
    DMA_InitStructureRx.MemDataSize    = DMA_MemoryDataSize_Byte;
    DMA_InitStructureRx.CircularMode   = DMA_MODE_NORMAL;
    DMA_InitStructureRx.Mem2Mem        = DMA_M2M_DISABLE;
	
	DMA_InitStructureRx.Direction      = DMA_DIR_PERIPH_SRC;
    DMA_InitStructureRx.Priority       = DMA_PRIORITY_VERY_HIGH;
    DMA_Init(FLASH_RX_DMA, &DMA_InitStructureRx);

    /* SPI_FLASH_Tx_DMA_Channel configuration ---------------------------------------------*/
    DMA_DeInit(FLASH_TX_DMA);
    DMA_InitStructureTx.PeriphAddr 		 = (uint32_t)&(FLASH_SPI->DAT);
    DMA_InitStructureTx.MemAddr    		 = (uint32_t)0;
    
		DMA_InitStructureTx.BufSize     	 = 0;
		DMA_InitStructureTx.PeriphInc      = DMA_PERIPH_INC_DISABLE;
		DMA_InitStructureTx.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructureTx.PeriphDataSize = DMA_PERIPH_DATA_SIZE_BYTE;
    DMA_InitStructureTx.MemDataSize  	 = DMA_MemoryDataSize_Byte;
    DMA_InitStructureTx.CircularMode 	 = DMA_MODE_NORMAL;
		DMA_InitStructureTx.Mem2Mem        = DMA_M2M_DISABLE;
		
	DMA_InitStructureTx.Direction  		 = DMA_DIR_PERIPH_DST;
    DMA_InitStructureTx.Priority   		 = DMA_PRIORITY_HIGH;
    DMA_Init(FLASH_TX_DMA, &DMA_InitStructureTx);   

    DMA_EnableChannel(FLASH_RX_DMA, DISABLE);
    DMA_EnableChannel(FLASH_TX_DMA, DISABLE);
}

/**
 * @brief  Initializes the peripherals used by the SPI FLASH driver.
 */
void sFLASH_LowLevel_Init(void)
{
    GPIO_InitType GPIO_InitStructure;

    /*!< FLASH_SPI Periph clock and sFLASH_SPI_GPIO Periph clock enable */
    FLASH_SPI_CLK_ENABLE();
		RCC_EnableAPB2PeriphClk(FLASH_GPIO_CLK, ENABLE);

    /*!< Configure FLASH_SPI pins: SCK */
    GPIO_InitStructure.Pin        = FLASH_PIN_CLK;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitPeripheral(FLASH_PORT_CLK, &GPIO_InitStructure);

    /*!< Configure FLASH_SPI pins: MOSI */
    GPIO_InitStructure.Pin = FLASH_PIN_MOSI;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitPeripheral(FLASH_PORT_MOSI, &GPIO_InitStructure);

    /*!< Configure FLASH_SPI pins: MISO */
    GPIO_InitStructure.Pin       = FLASH_PIN_MISO;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitPeripheral(FLASH_PORT_MISO, &GPIO_InitStructure);

    /*!< Configure GPIO_PIN_4 pin: sFLASH Card CS pin */
    GPIO_InitStructure.Pin       = FLASH_PIN_CS;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitPeripheral(FLASH_PORT_CS, &GPIO_InitStructure);
}

/**
 * @brief  Initializes the peripherals used by the SPI FLASH driver.
 */
void sFLASH_Init(void)
{	
    sFLASH_LowLevel_Init();

    /*!< Deselect the FLASH: Chip Select high */
    sFLASH_CS_HIGH();
		
    /*!< SPI configuration */
    SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    SPI_InitStructure.SpiMode       = SPI_MODE_MASTER;
    SPI_InitStructure.DataLen       = SPI_DATA_SIZE_8BITS;
    SPI_InitStructure.CLKPOL        = SPI_CLKPOL_HIGH;
    SPI_InitStructure.CLKPHA        = SPI_CLKPHA_SECOND_EDGE;
    SPI_InitStructure.NSS           = SPI_NSS_SOFT;

    SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_2;

    SPI_InitStructure.FirstBit = SPI_FB_MSB;
    SPI_InitStructure.CRCPoly  = 7;
    SPI_Init(FLASH_SPI, &SPI_InitStructure);

    /*!< Enable the FLASH_SPI  */
    SPI_Enable(FLASH_SPI, ENABLE);
		
		SPI_I2S_EnableDma(FLASH_SPI, SPI_I2S_DMA_TX, DISABLE);
		SPI_I2S_EnableDma(FLASH_SPI, SPI_I2S_DMA_RX, DISABLE);
		DMA_Flash_Init();
}

/**
 * @brief  Erases the specified FLASH sector.
 * @param SectorAddr address of the sector to erase.
 */
void sFLASH_EraseSector(uint32_t SectorAddr)
{
    /*!< Send write enable instruction */
    sFLASH_WriteEnable();

    /*!< Sector Erase */
    /*!< Select the FLASH: Chip Select low */
    sFLASH_CS_LOW();
    /*!< Send Sector Erase instruction */
    sFLASH_SendByte(sFLASH_CMD_SE);
    /*!< Send SectorAddr high nibble address byte */
    sFLASH_SendByte((SectorAddr & 0xFF0000) >> 16);
    /*!< Send SectorAddr medium nibble address byte */
    sFLASH_SendByte((SectorAddr & 0xFF00) >> 8);
    /*!< Send SectorAddr low nibble address byte */
    sFLASH_SendByte(SectorAddr & 0xFF);
    /*!< Deselect the FLASH: Chip Select high */
    sFLASH_CS_HIGH();

    /*!< Wait the end of Flash writing */
    sFLASH_WaitForWriteEnd();
}

/**
 * @brief  Erases the entire FLASH.
 */
void sFLASH_EraseBulk(void)
{
    /*!< Send write enable instruction */
    sFLASH_WriteEnable();

    /*!< Bulk Erase */
    /*!< Select the FLASH: Chip Select low */
    sFLASH_CS_LOW();
    /*!< Send Bulk Erase instruction  */
    sFLASH_SendByte(sFLASH_CMD_BE);
    /*!< Deselect the FLASH: Chip Select high */
    sFLASH_CS_HIGH();

    /*!< Wait the end of Flash writing */
    sFLASH_WaitForWriteEnd();
}

/**
 * @brief  Writes more than one byte to the FLASH with a single WRITE cycle
 *         (Page WRITE sequence).
 * @note   The number of byte can't exceed the FLASH page size.
 * @param pBuffer pointer to the buffer  containing the data to be written
 *         to the FLASH.
 * @param WriteAddr FLASH's internal address to write to.
 * @param NumByteToWrite number of bytes to write to the FLASH, must be equal
 *         or less than "sFLASH_PAGESIZE" value.
 */
void sFLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    /*!< Enable the write access to the FLASH */
    sFLASH_WriteEnable();

    /*!< Select the FLASH: Chip Select low */
    sFLASH_CS_LOW();
    /*!< Send "Write to Memory " instruction */
    sFLASH_SendByte(sFLASH_CMD_WRITE);
    /*!< Send WriteAddr high nibble address byte to write to */
    sFLASH_SendByte((WriteAddr & 0xFF0000) >> 16);
    /*!< Send WriteAddr medium nibble address byte to write to */
    sFLASH_SendByte((WriteAddr & 0xFF00) >> 8);
    /*!< Send WriteAddr low nibble address byte to write to */
    sFLASH_SendByte(WriteAddr & 0xFF);

    /*!< while there is data to be written on the FLASH */
    while (NumByteToWrite--)
    {
        /*!< Send the current byte */
        sFLASH_SendByte(*pBuffer);
        /*!< Point on the next byte to be written */
        pBuffer++;
    }

    /*!< Deselect the FLASH: Chip Select high */
    sFLASH_CS_HIGH();

    /*!< Wait the end of Flash writing */
    sFLASH_WaitForWriteEnd();
}

/**
 * @brief  Writes block of data to the FLASH. In this function, the number of
 *         WRITE cycles are reduced, using Page WRITE sequence.
 * @param pBuffer pointer to the buffer  containing the data to be written
 *         to the FLASH.
 * @param WriteAddr FLASH's internal address to write to.
 * @param NumByteToWrite number of bytes to write to the FLASH.
 */
void sFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint8_t NumOfPage = 0, Addr = 0, NumOfSingle = 0, count = 0, temp = 0;
    Addr        = (uint8_t)(WriteAddr % sFLASH_SPI_PAGESIZE);
    count       = (uint8_t)(sFLASH_SPI_PAGESIZE - Addr);
    NumOfPage   = (uint8_t)(NumByteToWrite / sFLASH_SPI_PAGESIZE);
    NumOfSingle = (uint8_t)(NumByteToWrite % sFLASH_SPI_PAGESIZE);

    if (Addr == 0) /*!< WriteAddr is sFLASH_PAGESIZE aligned  */
    {
        if (NumOfPage == 0) /*!< NumByteToWrite < sFLASH_PAGESIZE */
        {
            sFLASH_WritePage(pBuffer, WriteAddr, NumByteToWrite);
        }
        else /*!< NumByteToWrite > sFLASH_PAGESIZE */
        {
            while (NumOfPage--)
            {
                sFLASH_WritePage(pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE);
                WriteAddr += sFLASH_SPI_PAGESIZE;
                pBuffer += sFLASH_SPI_PAGESIZE;
            }

            sFLASH_WritePage(pBuffer, WriteAddr, NumOfSingle);
        }
    }
    else /*!< WriteAddr is not sFLASH_PAGESIZE aligned  */
    {
        if (NumOfPage == 0) /*!< NumByteToWrite < sFLASH_PAGESIZE */
        {
            if (NumOfSingle > count) /*!< (NumByteToWrite + WriteAddr) > sFLASH_PAGESIZE */
            {
                temp = NumOfSingle - count;

                sFLASH_WritePage(pBuffer, WriteAddr, count);
                WriteAddr += count;
                pBuffer += count;

                sFLASH_WritePage(pBuffer, WriteAddr, temp);
            }
            else
            {
                sFLASH_WritePage(pBuffer, WriteAddr, NumByteToWrite);
            }
        }
        else /*!< NumByteToWrite > sFLASH_PAGESIZE */
        {
            NumByteToWrite -= count;
            NumOfPage   = NumByteToWrite / sFLASH_SPI_PAGESIZE;
            NumOfSingle = (uint8_t)(NumByteToWrite % sFLASH_SPI_PAGESIZE);

            sFLASH_WritePage(pBuffer, WriteAddr, count);
            WriteAddr += count;
            pBuffer += count;

            while (NumOfPage--)
            {
                sFLASH_WritePage(pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE);
                WriteAddr += sFLASH_SPI_PAGESIZE;
                pBuffer += sFLASH_SPI_PAGESIZE;
            }

            if (NumOfSingle != 0)
            {
                sFLASH_WritePage(pBuffer, WriteAddr, NumOfSingle);
            }
        }
    }
}

/**
 * @brief  Reads a block of data from the FLASH.
 * @param pBuffer pointer to the buffer that receives the data read from the FLASH.
 * @param ReadAddr FLASH's internal address to read from.
 * @param NumByteToRead number of bytes to read from the FLASH.
 */
void sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
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

/**
 * @brief  Initiates a read data byte (READ) sequence from the Flash.
 *   This is done by driving the /CS line low to select the device, then the READ
 *   instruction is transmitted followed by 3 bytes address. This function exit
 *   and keep the /CS line low, so the Flash still being selected. With this
 *   technique the whole content of the Flash is read with a single READ instruction.
 * @param ReadAddr FLASH's internal address to read from.
 */
void sFLASH_StartReadSequence(uint32_t ReadAddr)
{
    /*!< Select the FLASH: Chip Select low */
    sFLASH_CS_LOW();

    /*!< Send "Read from Memory " instruction */
    sFLASH_SendByte(sFLASH_CMD_READ);

    /*!< Send the 24-bit address of the address to read from -------------------*/
    /*!< Send ReadAddr high nibble address byte */
    sFLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
    /*!< Send ReadAddr medium nibble address byte */
    sFLASH_SendByte((ReadAddr & 0xFF00) >> 8);
    /*!< Send ReadAddr low nibble address byte */
    sFLASH_SendByte(ReadAddr & 0xFF);
}

/**
 * @brief  Reads a byte from the SPI Flash.
 * @note   This function must be used only if the Start_Read_Sequence function
 *         has been previously called.
 * @return Byte Read from the SPI Flash.
 */
uint8_t sFLASH_ReadByte(void)
{
    return (sFLASH_SendByte(sFLASH_DUMMY_BYTE));
}

/**
 * @brief  Sends a byte through the SPI interface and return the byte received
 *         from the SPI bus.
 * @param byte byte to send.
 * @return The value of the received byte.
 */
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

/**
 * @brief  Sends a Half Word through the SPI interface and return the Half Word
 *         received from the SPI bus.
 * @param HalfWord Half Word to send.
 * @return The value of the received Half Word.
 */
uint16_t sFLASH_SendHalfWord(uint16_t HalfWord)
{
    /*!< Loop while DAT register in not emplty */
    while (SPI_I2S_GetStatus(FLASH_SPI, SPI_I2S_TE_FLAG) == RESET)
        ;

    /*!< Send Half Word through the sFLASH peripheral */
    SPI_I2S_TransmitData(FLASH_SPI, HalfWord);

    /*!< Wait to receive a Half Word */
    while (SPI_I2S_GetStatus(FLASH_SPI, SPI_I2S_RNE_FLAG) == RESET)
        ;

    /*!< Return the Half Word read from the SPI bus */
    return SPI_I2S_ReceiveData(FLASH_SPI);
}

/**
 * @brief  Enables the write access to the FLASH.
 */
void sFLASH_WriteEnable(void)
{
    /*!< Select the FLASH: Chip Select low */
    sFLASH_CS_LOW();

    /*!< Send "Write Enable" instruction */
    sFLASH_SendByte(sFLASH_CMD_WREN);

    /*!< Deselect the FLASH: Chip Select high */
    sFLASH_CS_HIGH();
}

/**
 * @brief  Polls the status of the Write In Progress (WIP) flag in the FLASH's
 *         status register and loop until write opertaion has completed.
 */
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

/**
 * @brief  Writes block of data to the FLASH by DMA. 
 * @param WriteAddr FLASH's internal address to write to.
 */
void SPI_DMA_PageWrite(uint8_t* pbuffer, uint32_t WriteAddr, uint16_t num_byte_to_write)
{
		if(num_byte_to_write == 0)
		{
			return;
		}
    /* SPI_FLASH_Tx_DMA_Channel configuration ---------------------------------------------*/
    FLASH_TX_DMA->TXNUM = num_byte_to_write;
    FLASH_TX_DMA->MADDR = (uint32_t)pbuffer;
		FLASH_TX_DMA->CHCFG |= DMA_MEM_INC_ENABLE;	  
	
		FLASH_RX_DMA->TXNUM = num_byte_to_write;
    FLASH_RX_DMA->MADDR = (uint32_t)&Empty;
		FLASH_RX_DMA->CHCFG &= ~DMA_MEM_INC_ENABLE;	
    /* Enable the write access to the FLASH */
    sFLASH_WriteEnable();

    /* Select the FLASH: Chip Select low */
    sFLASH_CS_LOW();
    /* Send "Write to Memory " instruction */
    sFLASH_SendByte(sFLASH_CMD_WRITE);
    /*!< Send WriteAddr high nibble address byte to write to */
    sFLASH_SendByte((WriteAddr & 0xFF0000) >> 16);
    /*!< Send WriteAddr medium nibble address byte to write to */
    sFLASH_SendByte((WriteAddr & 0xFF00) >> 8);
    /*!< Send WriteAddr low nibble address byte to write to */
    sFLASH_SendByte(WriteAddr & 0xFF);

		DMA_EnableChannel(FLASH_RX_DMA, ENABLE);
		DMA_EnableChannel(FLASH_TX_DMA, ENABLE);
		SPI_I2S_EnableDma(FLASH_SPI, SPI_I2S_DMA_RX, ENABLE);
		SPI_I2S_EnableDma(FLASH_SPI, SPI_I2S_DMA_TX, ENABLE);

    /* Wait for FLAHS_DMA channel3 transfer complete */
    while(!DMA_GetFlagStatus(FLASH_DMA_TX_TC, FLASH_DMA));
    /* Wait for FLASH_SPI transfer complete */
    while(!SPI_I2S_GetStatus(FLASH_SPI, SPI_I2S_TE_FLAG));
                        
		DMA_EnableChannel(FLASH_RX_DMA, DISABLE);
		DMA_EnableChannel(FLASH_TX_DMA, DISABLE);
		SPI_I2S_EnableDma(FLASH_SPI, SPI_I2S_DMA_RX, DISABLE);
		SPI_I2S_EnableDma(FLASH_SPI, SPI_I2S_DMA_TX, DISABLE);

    /*clear TX buff*/
    FLASH_SPI->DAT;

    /* Deselect the FLASH: Chip Select high */
    sFLASH_CS_HIGH();
		
		/*!< Wait the end of Flash writing */
    sFLASH_WaitForWriteEnd();
		DMA_ClearFlag(FLASH_DMA_RX_TC,FLASH_DMA);
		DMA_ClearFlag(FLASH_DMA_TX_TC,FLASH_DMA);
}

void SPI_DMA_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
  u8 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;
	
	/*mod运算求余，若writeAddr是SPI_FLASH_PageSize整数倍，运算结果Addr值为0*/
  Addr = WriteAddr % sFLASH_SPI_PAGESIZE;
	
	/*差count个数据值，刚好可以对齐到页地址*/
  count = sFLASH_SPI_PAGESIZE - Addr;
	/*计算出要写多少整数页*/
  NumOfPage =  NumByteToWrite / sFLASH_SPI_PAGESIZE;
	/*mod运算求余，计算出剩余不满一页的字节数*/
  NumOfSingle = NumByteToWrite % sFLASH_SPI_PAGESIZE;
	
	/* Addr=0,则WriteAddr 刚好按页对齐 aligned  */
  if (Addr == 0)
  {
		/* NumByteToWrite < SPI_FLASH_PageSize */
    if (NumOfPage == 0) 
    {
      SPI_DMA_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    { 
			/*先把整数页都写了*/
      while (NumOfPage--)
      {
        SPI_DMA_PageWrite(pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE);
        WriteAddr +=  sFLASH_SPI_PAGESIZE;
        pBuffer += sFLASH_SPI_PAGESIZE;
      }
			/*若有多余的不满一页的数据，把它写完*/
      SPI_DMA_PageWrite(pBuffer, WriteAddr, NumOfSingle);
    }
  }
	/* 若地址与 SPI_FLASH_PageSize 不对齐  */
  else 
  {
		/* NumByteToWrite < SPI_FLASH_PageSize */
    if (NumOfPage == 0)
    {
			/*当前页剩余的count个位置比NumOfSingle小，一页写不完*/
      if (NumOfSingle > count) 
      {
        temp = NumOfSingle - count;
				/*先写满当前页*/
        SPI_DMA_PageWrite(pBuffer, WriteAddr, count);
				
        WriteAddr +=  count;
        pBuffer += count;
				/*再写剩余的数据*/
        SPI_DMA_PageWrite(pBuffer, WriteAddr, temp);
      }
      else /*当前页剩余的count个位置能写完NumOfSingle个数据*/
      {
        SPI_DMA_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
      }
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    {
			/*地址不对齐多出的count分开处理，不加入这个运算*/
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / sFLASH_SPI_PAGESIZE;
      NumOfSingle = NumByteToWrite % sFLASH_SPI_PAGESIZE;
			
			/* 先写完count个数据，为的是让下一次要写的地址对齐 */
      SPI_DMA_PageWrite(pBuffer, WriteAddr, count);
			
			/* 接下来就重复地址对齐的情况 */
      WriteAddr +=  count;
      pBuffer += count;
			/*把整数页都写了*/
      while (NumOfPage--)
      {
        SPI_DMA_PageWrite(pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE);
        WriteAddr +=  sFLASH_SPI_PAGESIZE;
        pBuffer += sFLASH_SPI_PAGESIZE;
      }
			/*若有多余的不满一页的数据，把它写完*/
      if (NumOfSingle != 0)
      {
        SPI_DMA_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
}

/**
 * @brief  Reads a block of data from the FLASH by DMA.
 * @param ReadAddr FLASH's internal address to read from.
 */
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

/**
 * @}
 */


