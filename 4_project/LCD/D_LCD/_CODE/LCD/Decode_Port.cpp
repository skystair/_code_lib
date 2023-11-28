#include "lcd_driver.h"
#include "spi_flash.h"
#include "bsp_Dma.h"
#include "IOconfig.h"
#include "Decode_Port.h"

unsigned short DecodePort::ReadHalfWordImmediately(unsigned int ReadAddr)
{
	unsigned short data;
	unsigned char* p = reinterpret_cast<unsigned char*>(&data);

	sFLASH_CS_HIGH();//防止上次读取后未结束
	sFLASH_CS_HIGH();
	sFLASH_CS_HIGH();	
	sFLASH_CS_LOW();

	sFLASH_SendByte(sFLASH_CMD_READ);

	sFLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
	sFLASH_SendByte((ReadAddr & 0xFF00) >> 8);
	sFLASH_SendByte(ReadAddr & 0xFF);

	*p = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
	p++;
	*p = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

	sFLASH_CS_HIGH();
	return data;
}

unsigned int DecodePort::ReadWordImmediately(unsigned int ReadAddr)
{
	unsigned int data;
	unsigned char* p = reinterpret_cast<unsigned char*>(&data);
	
	sFLASH_CS_HIGH();//防止上次读取后未结束
	sFLASH_CS_HIGH();
	sFLASH_CS_HIGH();	
	sFLASH_CS_LOW();

	sFLASH_SendByte(sFLASH_CMD_READ);

	sFLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
	sFLASH_SendByte((ReadAddr & 0xFF00) >> 8);
	sFLASH_SendByte(ReadAddr & 0xFF);
	
	*p = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
	p++;
	*p = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
	p++;
	*p = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
	p++;
	*p = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
	
	sFLASH_CS_HIGH();
	return data;
}

void DecodePort::CreatFlashReader(unsigned int ReadAddr)
{
	sFLASH_CS_HIGH();
	sFLASH_CS_HIGH();
	sFLASH_CS_HIGH();
	sFLASH_CS_LOW();

	sFLASH_SendByte(sFLASH_CMD_READ);

	sFLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
	sFLASH_SendByte((ReadAddr & 0xFF00) >> 8);
	sFLASH_SendByte(ReadAddr & 0xFF);
}

unsigned char DecodePort::GetByte(void)
{
	return sFLASH_SendByte(sFLASH_DUMMY_BYTE);
}

unsigned short DecodePort::GetHalfWord(void)
{
	unsigned short data;
	unsigned char* p = reinterpret_cast<unsigned char*>(&data);
	*p = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
	p++;
	*p = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

	return data;
}

int DecodePort::GetWord(void)
{
	int data;
	unsigned char* p = reinterpret_cast<unsigned char*>(&data);
	*p = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
	p++;
	*p = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
	p++;
	*p = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
	p++;
	*p = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

	return data;
}

void DecodePort::GetLengData(unsigned char* pBuffer, unsigned short NumByteToRead)
{

	while (NumByteToRead--) /*!< while there is data to be read */
	{
		/*!< Read a byte from the FLASH */
		*pBuffer = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
		/*!< Point to the next location where the byte read will be saved */
		pBuffer++;
	}
}

void DecodePort::CloseFlashReader(void)
{
	sFLASH_CS_HIGH();
}

void DecodePort::Decode_DrawPicture(unsigned short x_start, unsigned short y_start, 
																		unsigned short x_end, unsigned short y_end, 
																		unsigned short* color)
{
	LcdPos_t Pos;
	Pos.x_start = x_start;
	Pos.x_end = x_end-1;
	Pos.y_start = y_start;
	Pos.y_end = y_end-1;
	
	LcdDrawArea(&Pos, color);
}

void DecodePort::StartMemDma(unsigned int source, unsigned int target, unsigned int halfWordSize)
{
	bspMemDmaStart(source, target, halfWordSize);
}


void DecodePort::SetMemDmaCallback(MemDmaCallback callback)
{
	BspSetMemDmaIrqCallBack(callback);
}


