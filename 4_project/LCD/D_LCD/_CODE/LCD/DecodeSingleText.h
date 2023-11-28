#ifndef _DECODE_SINGLE_TEXT_H_
#define _DECODE_SINGLE_TEXT_H_

#include "DecodeFont.h"

class DecodeSingleText :public IDecodeText
{
public:
	DecodeSingleText():IDecodeText()
	{
		MultiLine = false;
	}
	virtual void SetRollText(unsigned short x_new, unsigned short y_new, unsigned short width_new, const char* text, const char* fontPath, 
													short wordSpace_new, short SpaceGain_new, RollType_en type_new, unsigned short background_new, unsigned short foreground_new);
	virtual void SetRollText(const TextInfo& info);
	virtual void ChangeType(RollType_en type_new);
	virtual void ChangeText(const char* text, const char* fontPath);
	virtual void ChangeTextPos(unsigned short x_new, unsigned short y_new);
	virtual void ChangeTextPos(unsigned short x_new, unsigned short y_new, unsigned short width_new);
	virtual void ChangeTextPos(unsigned short x_new, unsigned short y_new, unsigned short width_new, short wordSpace_new);	
	virtual void ChangeColor(unsigned short background_new, unsigned short foreground_new);
	virtual bool DrawText(unsigned short* videoMemory, int line);
	virtual void RollText(void);
protected:

private:	
	short context_x;//文本内容起始坐标	
	short LineMargin;//记录行剩余空间长度，仅用于居中对齐
	short LineStart;//记录行起始位置，仅用于居中对齐
};










#endif/*_DECODE_SINGLE_TEXT_H_*/
