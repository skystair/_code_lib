#ifndef _DECODE_MULTILINE_TEXT_H_
#define _DECODE_MULTILINE_TEXT_H_

#include "DecodeFont.h"


class  DecodeMultiLineText : public IDecodeText
{
public:
	DecodeMultiLineText(char line):IDecodeText()
	{
		MultiLine = true;
		MaxLineNumber = line;
		LineStart = new short[line];
		LineMargin = new short[line];
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
	
	void ChangeStartLine(char start);
	
protected:

private:
	unsigned short width;
	char MaxLineNumber;
	char LineIndex;
	char LineCount;
	short *LineStart;
	short *LineMargin;

	bool NeedDraw(int decodeLine, int textLine, unsigned short& drawLine, unsigned short& targetLine, short& index);
};






#endif/*_DECODE_MULTILINE_TEXT_H_*/
