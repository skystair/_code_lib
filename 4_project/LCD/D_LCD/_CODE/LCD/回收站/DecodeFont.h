#ifndef _DECODE_FONT_H_
#define _DECODE_FONT_H_

#include "DecodeLocate.h"

#define ROLL_TEXT_STRING_MAX_LENGTH			100/*滚动文本支持的最长字符串长度*/
#define ROOL_SPEED											10/*文本滚动速度*/
#define ROOL_STRING_END_SPACE						3/*循环字符串结尾到新开始空格数量*/

typedef struct
{
	const unsigned char* bitmap;
	const unsigned short* dsc;
	const unsigned int* utf8_list;
	int listLength;
}FontDecode_FontStruct;

typedef enum
{
	RollType_Order_None,//从左到右获取字符串 依次显示在文本中
	RollType_Order_Left,//从左到右获取字符串 文本向左移动
	RollType_Order_Center,//从左到右获取字符串 多行文本居中
	RollType_Order_Center_Left,//从左到右获取字符串 单行文本 向左滚动
	
	RollType_Inverted_None,//从右到左获取字符串 依次显示在文本中
	RollType_Inverted_Left,//从右到左获取字符串 文本向左移动
	RollType_Inverted_Center,//从右到左获取字符串 多行文本居中
	RollType_Inverted_Center_Left,//从右到左获取字符串 单行文本 向左滚动
	
	RollType_Order_Right,//从左到右获取字符串 文本向右移动
	RollType_Order_Center_Right,//从左到右获取字符串 单行文本 向左滚动
	
	RollType_Inverted_Right,//从右到左获取字符串 文本向右移动
	RollType_Inverted_Center_Right,//从右到左获取字符串 单行文本 向左滚动
}RollType_en;

struct TextInfo
{
	const char* text;
	const char* fontPath;
	unsigned short x;
	unsigned short y;
	unsigned short width;
	short wordSpace;
	unsigned short color;
	RollType_en type;
};

class IDecodeText :protected DecodeLocate
{
public:
	IDecodeText()
	{
//		Buffer = buffer;
		next = (IDecodeText*)0;
		BitmapTableLength = 0;
		wordSpace = 0;
		background = 0xFFFF;
		foreground = 0xFFFF;
		type = RollType_Order_Left;
		x = 0;
		y = 0;
		x_end = SCREEN_PIXEL_WIDTH - 1;
		sleep = false;
	}

	virtual void SetRollText(unsigned short x, unsigned short y, unsigned short width, const char* text, const char* fontPath, 
													short wordSpace, RollType_en type, unsigned short background, unsigned short foreground);
	virtual void SetRollText(const TextInfo& info);
	virtual void ChangeType(RollType_en type);
	virtual void ChangeText(const char* text, const char* fontPath);
	virtual void ChangeTextPos(unsigned short x, unsigned short y);
	virtual void ChangeTextPos(unsigned short x, unsigned short y, unsigned short width);
	virtual void ChangeTextPos(unsigned short x, unsigned short y, unsigned short width, short wordSpace);	
	virtual void ChangeColor(unsigned short background, unsigned short foreground);
	
	virtual bool DrawText(unsigned short* videoMemory, int line);
	virtual bool RollText(void);
	
	virtual ~IDecodeText(){}
		
	IDecodeText* next;
	bool sleep;
	
protected:
	RollType_en type;
	short wordSpace;//词间距		
	unsigned short x;//文本框X坐标
	unsigned short y;//文本框Y坐标
	unsigned short x_end;//文本框结束坐标
	unsigned short background;//背景色
	unsigned short foreground;//前景色
	short BitmapTableLength;//字符数

	int BitmapTable[ROLL_TEXT_STRING_MAX_LENGTH];//存储字符串对应的字典索引
	int *BitmapTarget;//存储接下来需要解码的数据地址
	unsigned short *LastCode;//未完成的解码数据，0表示解码上次已完成
	//unsigned short* Buffer;
	bool MultiLine;

	short StartIndex;//开始显示字符位置
	
	short char_x;
	short char_y;
	short char_end;
	unsigned short maxCharWidth;//输入字符的最大宽度 用来计算空格
	unsigned short CharHeight;
	unsigned short half;
	unsigned short quartern;
	
	void DrawRollContinuous(int *x, int *y, unsigned short color, unsigned short num);
	void DecodeRollTextAntiAliasing(int address);
	void DecodeRollTextAntiAliasing_Right(int address);
	void DrawBackground(short width);
	
private:


};

class DecodeSingleText :public IDecodeText
{
public:
	DecodeSingleText():IDecodeText()
	{
		MultiLine = false;
	}
	virtual void SetRollText(unsigned short x, unsigned short y, unsigned short width, const char* text, const char* fontPath, 
									short wordSpace = 0, RollType_en type = RollType_Order_Right, unsigned short background = 0xFFFF, unsigned short foreground = 0xFFFF);
	virtual void SetRollText(const TextInfo& info);
	virtual void ChangeType(RollType_en type);
	virtual void ChangeText(const char* text, const char* fontPath);
	virtual void ChangeTextPos(unsigned short x, unsigned short y);
	virtual void ChangeTextPos(unsigned short x, unsigned short y, unsigned short width);
	virtual void ChangeTextPos(unsigned short x, unsigned short y, unsigned short width, short wordSpace);	
	virtual void ChangeColor(unsigned short background, unsigned short foreground);
	
	virtual bool DrawText(unsigned short* videoMemory, int line);
	virtual bool RollText(void);
	
protected:

private:	
	short context_x;//文本内容起始坐标	
	short LineMargin;//记录行剩余空间长度，仅用于居中对齐
	short LineStart;//记录行起始位置，仅用于居中对齐
};

class DecodeMultiLineText : public IDecodeText
{
public:
	DecodeMultiLineText(char line):IDecodeText()
	{
		MultiLine = true;
		MaxLineNumber = line;
		LineStart = new short[line];
		LineMargin = new short[line];
	}
	
	virtual void SetRollText(unsigned short x, unsigned short y, unsigned short width, const char* text, const char* fontPath, 
									short wordSpace = 0, RollType_en type = RollType_Order_Center, unsigned short background = 0xFFFF, unsigned short foreground = 0xFFFF);
	virtual void SetRollText(const TextInfo& info);
	virtual void ChangeType(RollType_en type);
	virtual void ChangeText(const char* text, const char* fontPath);
	virtual void ChangeTextPos(unsigned short x, unsigned short y);
	virtual void ChangeTextPos(unsigned short x, unsigned short y, unsigned short width);
	virtual void ChangeTextPos(unsigned short x, unsigned short y, unsigned short width, short wordSpace);	
	virtual void ChangeColor(unsigned short background, unsigned short foreground);
	
	virtual bool DrawText(unsigned short* videoMemory, int line);
	virtual bool RollText(void);
	
	void ChangeStartLine(char start);
	
protected:

private:
	unsigned short width;
	char MaxLineNumber;
	char LineIndex;
	char LineCount;
	short *LineStart;
	short *LineMargin;
	
};

class DecodeFont
{
public:
	DecodeFont(unsigned short* buffer)
	{
		Buffer = buffer;
		text = (IDecodeText*)0;
	}
	~DecodeFont()
	{
		
	}
	void CreatText(void);
	void CreatText(char line);
	IDecodeText& GetText(int index);
	
	void SleepAll();
	bool Handle(unsigned short* videoMemory, int line);
	
protected:
		

private:	
	//DecodeFont* next; 
	unsigned short* Buffer;
	IDecodeText* text;
	
};


















#endif/*_DECODE_FONT_H_*/
