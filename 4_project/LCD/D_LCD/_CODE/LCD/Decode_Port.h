#ifndef _DECODE_PORT_H_
#define _DECODE_PORT_H_

#include "Decode_Config.h"

typedef enum
{
	DecodeState_OK,
	DecodeState_OpenFileFalse,
	DecodeState_ReadFileFalse,
	DecodeState_DecodeError,
	DecodeState_MultipleFilesError,
	DecodeState_End,
	DecodeState_BlockEnd,
}DecodeState;

typedef void (*MemDmaCallback)(void);

class DecodePort
{
public:
	//短程快速读取
	unsigned short ReadHalfWordImmediately(unsigned int ReadAddr);
	unsigned int ReadWordImmediately(unsigned int ReadAddr);

	//长程连续读取
	void CreatFlashReader(unsigned int ReadAddr);
	unsigned char GetByte(void);
	unsigned short GetHalfWord(void);
	int GetWord(void);
	void GetLengData(unsigned char* pBuffer, unsigned short NumByteToRead);
	void CloseFlashReader(void);
	//屏幕绘制
	void Decode_DrawPicture(unsigned short x_start, unsigned short y_start, 
													unsigned short x_end, unsigned short y_end, 
													unsigned short* color);

	static void StartMemDma(unsigned int source, unsigned int target, unsigned int halfWordSize);
	void SetMemDmaCallback(MemDmaCallback callback);
													
protected:
													
private:
	
};












#endif /* _DECODE_PORT_H_ */
