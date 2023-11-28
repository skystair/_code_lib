#ifndef _DECODE_FONT_H_
#define _DECODE_FONT_H_

#include "DecodeLocate.h"
#include "Decode_Memory.h"

/*********************字体解码类型*******************************/
//注意：正向必须为偶数，反向必须为奇数
typedef enum
{
	//多行文本
	RollType_Order_Center    			= 0,//从左到右获取字符串 多行文本居中---多行文本默认状态 选择非多行文本状态 都会转到这个状态
	RollType_Inverted_Center 			= 1,//从右到左获取字符串 多行文本居中
	
	//单行文本
	RollType_Order_None						= 2,//从左到右获取字符串 依次显示在文本中
	RollType_Inverted_None				= 3,//从右到左获取字符串 依次显示在文本中
	RollType_Order_Left						=	4,//从左到右获取字符串 文本向左移动	
	RollType_Inverted_Left				= 5,//从右到左获取字符串 文本向左移动		
	RollType_Order_Center_Left		= 6,//从左到右获取字符串 单行文本 向左滚动	
	RollType_Inverted_Center_Left	= 7,//从右到左获取字符串 单行文本 向左滚动
	
	RollType_Order_Right					= 8,//从左到右获取字符串 文本向右移动
	RollType_Inverted_Right				= 9,//从右到左获取字符串 文本向右移动
	RollType_Order_Center_Right		= 10,//从左到右获取字符串 单行文本 向左滚动
	RollType_Inverted_Center_Right=	11,//从右到左获取字符串 单行文本 向左滚动	
}RollType_en;

struct TextInfo
{
	const char* text;
	const char* fontPath;
	unsigned short x;
	unsigned short y;
	unsigned short width;
	short wordSpace;
	short SpaceGain;
	unsigned short color;
	RollType_en type;
};

class IDecodeText :protected DecodeLocate
{
public:
	IDecodeText()
	{
		next = reinterpret_cast<IDecodeText*>(0);
		BitmapTableLength = 0;
		wordSpace = 0;
		background = 0xFFFF;
		foreground = 0xFFFF;
		type = RollType_Order_Left;
		x = 0;
		y = 0;
		x_end = SCREEN_PIXEL_WIDTH - 1;
		sleep = false;
		pause = false;
		startDraw = false;
	}

	virtual ~IDecodeText(){}
	
	virtual void SetRollText(unsigned short x_new, unsigned short y_new, unsigned short width_new, const char* text, const char* fontPath, 
													short wordSpace_new, short SpaceGain_new, RollType_en type_new, unsigned short background_new, unsigned short foreground_new) = 0;
	virtual void SetRollText(const TextInfo& info) = 0;
	virtual void ChangeType(RollType_en type_new) = 0;
	virtual void ChangeText(const char* text, const char* fontPath) = 0;
	virtual void ChangeTextPos(unsigned short x_new, unsigned short y_new) = 0;
	virtual void ChangeTextPos(unsigned short x_new, unsigned short y_new, unsigned short width_new) = 0;
	virtual void ChangeTextPos(unsigned short x_new, unsigned short y_new, unsigned short width_new, short wordSpace_new) = 0;	
	virtual void ChangeColor(unsigned short background_new, unsigned short foreground_new) = 0;
	virtual bool DrawText(unsigned short* videoMemory, int line) = 0;
	virtual void RollText(void) = 0;
	virtual void ReadyToDraw(void);
	bool IsMultiLine(void);
	
	IDecodeText* next;
	bool sleep;
	bool pause;
	
protected:
	bool MultiLine;
	bool startDraw;	
	short wordSpace;//词间距		
	unsigned short x;//文本框X坐标
	unsigned short y;//文本框Y坐标
	unsigned short x_end;//文本框结束坐标
	unsigned short background;//背景色
	unsigned short foreground;//前景色
	short BitmapTableLength;//字符数
	
	int BitmapTable[ROLL_TEXT_STRING_MAX_LENGTH];//存储字符串对应的字典索引
	int BitmapCurrent[ROLL_TEXT_STRING_MAX_LENGTH];//存储解码到一半的下一个解码数据来源地址
	unsigned char LastCode[ROLL_TEXT_STRING_MAX_LENGTH];//存储上一次解码未完成部分的编码内容
		
	short StartIndex;//开始显示字符位置
	short SpaceGain;//空格增益 控制空格大小

	short char_x;
	short char_y;
	short char_end;
	unsigned short maxCharWidth;//输入字符的最大宽度 用来计算空格
	unsigned short CharHeight;
	unsigned short half;
	unsigned short quartern;
	short firstwidth;
	
	unsigned short CopyLine;//复制行 指定从哪一行开始复制
	unsigned short TargetLine;//目标行 指定复制到显存的哪一行
	unsigned short DrawLine;//本次绘制行数
	unsigned short CopyCount;//已复制行计数
	
	RollType_en type;
	
	void DrawRollCode(unsigned short* buffer, unsigned char type, unsigned char num);
	void DecodeRollTextAntiAliasing(unsigned short* videoMemory, short index, unsigned short drawLine, unsigned short targetLine, unsigned short charWidth);
	void DrawBackground(unsigned short* videoMemory, short width, unsigned short drawLine, unsigned short targetLine);
	
private:
};














#endif/*_DECODE_FONT_H_*/
