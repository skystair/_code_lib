#include "DecodeFont.h"

	void SetRollText(unsigned short x, unsigned short y, unsigned short width, const char* text, const char* fontPath, 
													short wordSpace, RollType_en type, unsigned short background, unsigned short foreground)
													
{
	(void)x;
	(void)y;
	(void)width;
	(void)text;
	(void)fontPath;
	(void)wordSpace;
	(void)type;
	(void)background;
	(void)foreground;
}
void SetRollText(const TextInfo& info)
{
	(void)info;
}

void ChangeType(RollType_en type)
{
	(void)type;
}

void ChangeText(const char* text, const char* fontPath)
{
	(void)text;
	(void)fontPath;
}

void ChangeTextPos(unsigned short x, unsigned short y)
{
	(void)x;
	(void)y;
}

void ChangeTextPos(unsigned short x, unsigned short y, unsigned short width)
{
	(void)x;
	(void)y;
	(void)width;
}

void ChangeTextPos(unsigned short x, unsigned short y, unsigned short width, short wordSpace)
{
	(void)x;
	(void)y;
	(void)width;
	(void)wordSpace;
}

void ChangeColor(unsigned short background, unsigned short foreground)
{
	(void)background;
	(void)foreground;
}

bool DrawText(int line)
{
	(void)line;
}

bool RollText(void)
{
	
}

/*--------------------------------------------------------------------------------------------------------*/
void IDecodeText::DrawRollContinuous(int *target_x, int *target_y, unsigned short color, unsigned short num)
{
	int x_local = (*target_x) << 1, y_local = *target_y;	
	int end = char_end << 1;
	int start_string = x << 1;
	int end_string = x_end << 1;
	if(y_local >= SCREEN_PIXEL_HEIGHT)
	{
		x_local = end;
		return;
	}
	unsigned short* target = 	Buffer + (y_local * SCREEN_PIXEL_WIDTH);//取行首地址
	for(int i=0; i<num; i++)
	{
		if(x_local >= start_string && x_local < end_string)
		{
			__asm volatile("STRH color,[target,x_local]");
		}
		x_local += 2;
		if(x_local >= end)
		{		
			if(++y_local >= SCREEN_PIXEL_HEIGHT)
			{
				break;
			}
			x_local = char_x << 1;
			target += SCREEN_PIXEL_WIDTH;//取行首地址
		}
	}
	*target_x = x_local >> 1;
	*target_y = y_local;
}

void IDecodeText::DecodeRollTextAntiAliasing(int address)
{
	CreatFlashReader((unsigned int)address);	
	short charWidth = GetHalfWord();
	short charHeight = GetHalfWord();
	short length = GetHalfWord();	
	char_end = char_x + charWidth;
	int x=char_x,y=char_y;
	for(int i=0; i<length; i++)
	{
		unsigned char flag = GetByte();
		if((flag&0xC0) == 0xC0)
		{
			DrawRollContinuous(&x, &y, (unsigned short)foreground, flag&0x3F);
		}
		else if((flag&0xC0) == 0x80)
		{
			DrawRollContinuous(&x, &y, (unsigned short)half, flag&0x3F);
		}
		else if((flag&0xC0) == 0x40)
		{
			DrawRollContinuous(&x, &y, (unsigned short)quartern, flag&0x3F);
		}
		else 
		{
			if(background != foreground)
			{//前景色与背景色不同 使用背景色
				DrawRollContinuous(&x, &y, (unsigned short)background , flag&0x3F);
			}
			else
			{//前景色与背景色相同 不使用背景色
				x += flag&0x3F;
				if(x >= char_end)
				{
					x -= char_x;
					y += x/charWidth;
					x = x%charWidth+char_x;			
				}
			}
		}
	}
	CloseFlashReader();
	
	char_x += charWidth + wordSpace;
}

void IDecodeText::DecodeRollTextAntiAliasing_Right(int address)
{
	CreatFlashReader((unsigned int)address);
	short charWidth = GetHalfWord();
	short charHeight = GetHalfWord();
	short length = GetHalfWord();
	char_end = char_x;
	char_x -= charWidth;
	int x = char_x;
	int y = char_y;
	for(int i=0; i<length; i++)
	{
		unsigned char flag = GetByte();
		if((flag&0xC0) == 0xC0)
		{
			DrawRollContinuous(&x, &y, (unsigned short)foreground, flag&0x3F);
		}
		else if((flag&0xC0) == 0x80)
		{
			DrawRollContinuous(&x, &y, (unsigned short)half, flag&0x3F);
		}
		else if((flag&0xC0) == 0x40)
		{
			DrawRollContinuous(&x, &y, (unsigned short)quartern, flag&0x3F);
		}
		else 
		{
			if(background != foreground)
			{//前景色与背景色不同 使用背景色
				DrawRollContinuous(&x, &y, (unsigned short)background , flag&0x3F);
			}
			else
			{//前景色与背景色相同 不使用背景色
				x += flag&0x3F;
				if(x >= char_end)
				{
					x -= char_x;
					y += x/charWidth;
					x = x%charWidth+char_x;			
				}
			}
		}
	}
	CloseFlashReader();
	
	char_x -= wordSpace;
}

void IDecodeText::DrawBackground(short width)
{
	short color = background;
	int start_string = x << 1;
	int end_string = x_end << 1;
	if(type == RollType_Order_Right || type == RollType_Inverted_Right)
	{		
		char_x -= width;//字符起始位置坐标左移当前字符宽度
		if(background != foreground)
		{
			for(int y=0; y<CharHeight; y++)
			{
				short local_y = char_y + y;
				if(local_y >= SCREEN_PIXEL_HEIGHT)
				{
					break;
				}
				unsigned short* target = 	Buffer + (local_y * SCREEN_PIXEL_WIDTH);//取行首地址
				for(int x=0; x<width; x++)
				{
					short local_x = x + char_x;
					local_x <<= 1;
					if(local_x >= start_string && local_x < end_string)
						__asm volatile("STRH color,[target,local_x]");
				}
			}		
		}	
	}
	else
	{
		if(background != foreground)
		{
			for(int y=0; y<CharHeight; y++)
			{
				short local_y = char_y + y;
				if(local_y >= SCREEN_PIXEL_HEIGHT)
				{
					break;
				}
				unsigned short* target = 	Buffer + (local_y * SCREEN_PIXEL_WIDTH);//取行首地址
				for(int x=0; x<width; x++)
				{
					short local_x = x + char_x;
					local_x <<= 1;
					if(local_x >= start_string && local_x < end_string)
						__asm volatile("STRH color,[target,local_x]");
				}
			}
		}
		char_x +=  width;//字符起始位置坐标右移当前字符宽度
		
	}	
}

/*******************************************************************************************/

void DecodeSingleText::ChangeType(RollType_en type)
{
	this->type = type;
	switch(type)
	{
		case RollType_Order_None:
			StartIndex = 0;
			context_x = x;	
			break;
		
		case RollType_Order_Right:
			StartIndex = 0;
			context_x = x_end;
			break;
		
		case RollType_Order_Center_Right:
			StartIndex = 0;
			LineStart = x_end - ((LineMargin - BitmapTableLength * wordSpace) >> 1);
			context_x = LineStart;
			break;
		
		case RollType_Order_Center_Left:
		case RollType_Order_Center:
			StartIndex = 0;
			LineStart += (LineMargin - BitmapTableLength * wordSpace) >> 1;
			context_x = LineStart;
			break;
		
		case RollType_Inverted_None:
			StartIndex = BitmapTableLength - 1;
			context_x = x;	
			break;
		
		case RollType_Inverted_Left:
			StartIndex = BitmapTableLength - 1;
			context_x = x;	
			break;
		
		case RollType_Inverted_Right:
			StartIndex = BitmapTableLength - 1;
			context_x = x_end;
			break;
		
		case RollType_Inverted_Center_Left:
		case RollType_Inverted_Center:
			StartIndex = BitmapTableLength - 1;
			LineStart += ((LineMargin - BitmapTableLength * wordSpace) >> 1);
			context_x = LineStart;
			break;
		
		case RollType_Inverted_Center_Right:
			StartIndex = BitmapTableLength - 1;
			LineStart = x_end - ((LineMargin - BitmapTableLength * wordSpace) >> 1);
			context_x = LineStart;
			break;
		
		case RollType_Order_Left:
		default:
			StartIndex = 0;
			context_x = x;
			break;
	}

}

void DecodeSingleText::ChangeText(const char* text, const char* fontPath)
{
	unsigned int address = GetFileAddress(fontPath);
	if(address == 0)
	{//没找到字库
		BitmapTableLength = 0;//标记字符串长度为0，停止句柄对此文本框的输出
		return;
	}
	int i = 0;
	int tableIndex = 0;
	LineMargin = x_end - x;
	LineStart = x;
	unsigned short fontlength = ReadHalfWordImmediately(address);
	address+=2;
	maxCharWidth = 0;
	while(text[i] != '\0')
	{
		int index = text[i];
		if(text[i]&0x80)
		{//多字节编码
			for(i++; (text[i]&0xC0)==0x80; i++)
			{
				index <<= 8;
				index |= text[i];
			}
		}
		else
			i++;
		
		//查找字库
		int bitmap = -1;
		CreatFlashReader(address);//开始传输
		for(int j=0; j<fontlength; j++)
		{
			int utf8 = GetWord();
			if(utf8 == index)
			{
				bitmap = address+(fontlength<<2)+(j<<1);//utf8开始地址+所有utf8列表长度+当前
				break;
			}
		}
		CloseFlashReader();//传输终止
		if(bitmap < 0)//能找到的大于等于0，找不到的为-1，绘制时所有-1绘制成空格	
		{
			BitmapTable[tableIndex] = -1;
		}
		else
		{
			BitmapTable[tableIndex] = address + ReadHalfWordImmediately(bitmap);
			unsigned short width = ReadHalfWordImmediately(BitmapTable[tableIndex]);		
			LineMargin -= width;
			if(LineMargin < 0)
			{
				LineMargin = 0;
			}
			if(maxCharWidth < width)
			{
				maxCharWidth = width;
			}
		}
		
		tableIndex++;
	}
	for(int i=0; i<tableIndex; i++)
	{
		if(BitmapTable[i] >= 0)
		{
			CharHeight = ReadHalfWordImmediately(BitmapTable[i]+2);		
			break;
		}
	}
	BitmapTableLength = tableIndex;
	ChangeType(type);
}

void DecodeSingleText::ChangeTextPos(unsigned short x, unsigned short y)
{
	unsigned short width = x_end - this->x;
	this->x = x;
	this->y = y;
	x_end = width + x;
	if(x >= SCREEN_PIXEL_WIDTH)
	{
		x_end = SCREEN_PIXEL_WIDTH - x - 1;
	}
}

void DecodeSingleText::ChangeTextPos(unsigned short x, unsigned short y, unsigned short width)
{
	this->x = x;
	this->y = y;
	this->x_end = width + x - 1;
	if(x_end >= SCREEN_PIXEL_WIDTH)
	{
		x_end = SCREEN_PIXEL_WIDTH - 1;
	}
	ChangeType(type);
}

void DecodeSingleText::ChangeTextPos(unsigned short x, unsigned short y, unsigned short width, short wordSpace)
{
	this->x = x;
	this->y = y;
	x_end = width + x - 1;
	if(x_end >= SCREEN_PIXEL_WIDTH)
	{
		x_end = SCREEN_PIXEL_WIDTH - 1;
	}
	this->wordSpace = wordSpace;	
	ChangeType(type);
}

void DecodeSingleText::ChangeColor(unsigned short background, unsigned short foreground)
{
	this->background = background;
	this->foreground = foreground;
	int R = (foreground & 0xF800)>>12;
	int G = (foreground & 0x7E0)>>6;
	int B = foreground & 0x1F>>1;
	if(foreground != background)
	{
		R += (background & 0xF800)>>12;
		G += (background & 0x7E0)>>6;
		B += background & 0x1F>>1;		
	}
	half = (R << 11) | (G << 5) | B;
	R >>= 1;
	G >>= 1;
	B >>= 1;
	quartern = (R << 11) | (G << 5) | B;
}

void DecodeSingleText::SetRollText(unsigned short x, unsigned short y, unsigned short width, const char* text, const char* fontPath, short wordSpace,
								RollType_en type, unsigned short background, unsigned short foreground)
{
	this->x = x;
	this->y = y;
	this->x_end = width + x - 1;
	if(x_end >= SCREEN_PIXEL_WIDTH)
	{
		x_end = SCREEN_PIXEL_WIDTH - 1;
	}
	this->wordSpace = wordSpace;
	this->type = type;
	this->background = background;
	this->foreground = foreground;
	int R = (foreground & 0xF800)>>11;
	int G = (foreground & 0x7E0)>>5;
	int B = foreground & 0x1F;
	int Rbg = (background & 0xF800)>>11;
	int Gbg = (background & 0x7E0)>>5;
	int Bbg =  background & 0x1F;

	if(foreground != background)
	{
		R += Rbg;
		G += Gbg;
		B += Bbg;
		R >>= 1;
		G >>= 1;
		B >>= 1;
		half = (R << 11) | (G << 5) | B;
		int Rd = (R - Rbg) >> 2;
		int Gd = (G - Gbg) >> 2;
		int Bd = (B - Bbg) >> 2;
		R -= Rd;
		G -= Gd;
		B -= Bd;
		quartern = (R << 11) | (G << 5) | B;
	}
	else
	{
		R >>= 1;
		G >>= 1;
		B >>= 1;
		half = (R << 11) | (G << 5) | B;
		R >>= 1;
		G >>= 1;
		B >>= 1;
		quartern = (R << 11) | (G << 5) | B;
	}
	
	ChangeText(text, fontPath);
}

void DecodeSingleText::SetRollText(const TextInfo& info)
{
	SetRollText(info.x, info.y, info.width, info.text, info.fontPath, info.wordSpace, info.type, info.color, info.color);
}

bool DecodeSingleText::DrawText(unsigned short* videoMemory, int line)
{
	if(!BitmapTableLength || sleep)
	{//没有存储需要显示文本 或休眠 的直接跳过
		return false;
	}
	char_x = context_x;
	char_y = y;		
	char_end = char_x;
	short index = StartIndex;
	int drawing = 1;
	while(drawing)
	{
		int	bitmapindex = BitmapTable[index];//获取字典索引

		short firstwidth, width;
		if(bitmapindex < 0)
		{
			width = maxCharWidth;//空格使用字符串全部文本最大宽度			
		}
		else
		{
			width = ReadHalfWordImmediately(bitmapindex);//普通字符直接获取宽度
		}
		width += wordSpace;//在字符宽度基础上增加字间距处理，获取增加字间距的字符宽度
		if(index == StartIndex)
		{//本次显示的第一个字符，需要额外处理
			firstwidth = width;//记录本次显示的第一个字符宽度
		}
		//控制绘制节奏
		switch(type)
		{
			case RollType_Order_None:
				if(++index >= BitmapTableLength //文本结束退出
					|| char_x >= x_end)//显示溢出退出
				{
					drawing = 0;//文本结束退出
					//sleep = true;
				}		
				break;
				
			case RollType_Order_Center_Right:
			case RollType_Order_Right:	
				if(++index >= BitmapTableLength)
				{
						index = 0;
				}
				if(index == StartIndex) /*文本第二次出现退出*/
				{
					drawing = 0;
					if(LineMargin == 0)
					{
						context_x += ROOL_SPEED;
						if(context_x - firstwidth >= x_end)
						{
							context_x = x_end -1;
							if(++StartIndex >= BitmapTableLength)
							{
								StartIndex = 0;
							}
						}
					}
				}
				if(char_x + firstwidth <= 0)/*显示溢出退出*/
				{
					drawing = 0;//退出本行文本刷新
					context_x += ROOL_SPEED;
					if(context_x - firstwidth >= x_end)
					{
						context_x = x_end -1;
						if(++StartIndex >= BitmapTableLength)
						{
							StartIndex = 0;
						}
					}
				}
				break;
				
			case RollType_Inverted_None:
				if(--index < 0 //文本结束退出
					|| char_x >= x_end)//显示溢出退出
				{
					drawing = 0;//文本结束退出
					//sleep = true;
				}			
				break;
				
			case RollType_Inverted_Center_Left:
			case RollType_Inverted_Center:
			case RollType_Inverted_Left:
				if(--index < 0)
				{
					index = BitmapTableLength - 1;
				}
				if(index == StartIndex) /*文本第二次出现退出*/
				{
					drawing = 0;//退出本行文本刷新
					if(LineMargin == 0)
					{
						context_x -= ROOL_SPEED;
						if(context_x + firstwidth <= x)
						{
							context_x = x;
							if(--StartIndex < 0)
							{
								StartIndex = BitmapTableLength - 1;
							}
						}
					}
				}	
				if(char_end >= x_end)/*显示溢出退出*/
				{
					drawing = 0;//退出本行文本刷新
					context_x -= ROOL_SPEED;
					if(context_x + firstwidth <= x)
					{
						context_x = x;
						if(--StartIndex < 0)
						{
							StartIndex = BitmapTableLength - 1;
						}
					}
				}
				break;
			
			case RollType_Inverted_Center_Right:
			case RollType_Inverted_Right:	
				if(--index < 0)
				{
					index = BitmapTableLength - 1;
				}
				if(index == StartIndex )/*文本第二次出现退出*/
				{
					drawing = 0;//退出本行文本刷新
					if(LineMargin == 0)
					{
						context_x += ROOL_SPEED;
						if(context_x - firstwidth >= x_end)
						{
							context_x -= firstwidth;
							if(--StartIndex < 0)
							{
								StartIndex = BitmapTableLength - 1;
							}
						}
					}
				}
				if(char_x + firstwidth <= 0)/*显示溢出退出*/
				{
					drawing = 0;//退出本行文本刷新
					context_x += ROOL_SPEED;
					if(context_x - firstwidth >= x_end)
					{
						context_x -= firstwidth;
						if(--StartIndex < 0)
						{
							StartIndex = BitmapTableLength - 1;
						}
					}
				}
				break;
				
			case RollType_Order_Center_Left:
			case RollType_Order_Center:
			case RollType_Order_Left:
			default:
				if(++index >= BitmapTableLength)
				{
					index = 0;//循环文本
				}
				
				if(index == StartIndex) /*文本第二次出现退出*/
				{
					drawing = 0;//退出本行文本刷新
					if(LineMargin == 0)
					{
						context_x -= ROOL_SPEED;
						if(context_x + firstwidth <= x)
						{
							context_x = x;
							if(++StartIndex >= BitmapTableLength)
							{
								StartIndex = 0;
							}
						}
					}
				}
				if(char_end >= x_end)/*显示右侧溢出退出*/
				{
					drawing = 0;//退出本行文本刷新
					context_x -= ROOL_SPEED;
					if(context_x + firstwidth <= x)
					{
						context_x = x;
						if(++StartIndex >= BitmapTableLength)
						{
							StartIndex = 0;
						}
					}
				}
				break;
		}
		
		//绘制
		//if(drawing)
		{
			if(bitmapindex < 0)
			{//绘制一个空格
				DrawBackground(width);	
			}
			else 	if(type == RollType_Order_Right || type == RollType_Inverted_Right || type == RollType_Order_Center_Right || type == RollType_Inverted_Center_Right)
			{//绘制文本
				DecodeRollTextAntiAliasing_Right(bitmapindex);
			}
			else
			{
				DecodeRollTextAntiAliasing(bitmapindex);
			}
		}
	}
	return true;
}
/******************************************************************************/
void DecodeMultiLineText::SetRollText(unsigned short x, unsigned short y, unsigned short width, const char* text, const char* fontPath, short wordSpace,
									 RollType_en type, unsigned short background, unsigned short foreground)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->x_end = width + x - 1;
	if(x_end >= SCREEN_PIXEL_WIDTH)
	{
		x_end = SCREEN_PIXEL_WIDTH - 1;
	}
	this->wordSpace = wordSpace;
	this->type = type;
	this->background = background;
	this->foreground = foreground;
	int R = (foreground & 0xF800)>>11;
	int G = (foreground & 0x7E0)>>5;
	int B = foreground & 0x1F;
	int Rbg = (background & 0xF800)>>11;
	int Gbg = (background & 0x7E0)>>5;
	int Bbg =  background & 0x1F;

	if(foreground != background)
	{
		R += Rbg;
		G += Gbg;
		B += Bbg;
		R >>= 1;
		G >>= 1;
		B >>= 1;
		half = (R << 11) | (G << 5) | B;
		int Rd = (R - Rbg) >> 2;
		int Gd = (G - Gbg) >> 2;
		int Bd = (B - Bbg) >> 2;
		R -= Rd;
		G -= Gd;
		B -= Bd;
		quartern = (R << 11) | (G << 5) | B;
	}
	else
	{
		R >>= 1;
		G >>= 1;
		B >>= 1;
		half = (R << 11) | (G << 5) | B;
		R >>= 1;
		G >>= 1;
		B >>= 1;
		quartern = (R << 11) | (G << 5) | B;
	}
	
	ChangeText(text, fontPath);
}

void DecodeMultiLineText::SetRollText(const TextInfo& info)
{
	SetRollText(info.x, info.y, info.width, info.text, info.fontPath, info.wordSpace, info.type, info.color, info.color);
}

void DecodeMultiLineText::ChangeType(RollType_en type)
{
	this->type = type;
	for(int i=0; i<MaxLineNumber; i++)
	{
		switch(type)
		{
			case RollType_Order_None:
			case RollType_Order_Left:
				StartIndex = 0;
				LineStart[i] = 0;				
				break;
			
			case RollType_Order_Right:
				StartIndex = 0;
				LineStart[i] = x_end;			
				break;	
			
			case RollType_Inverted_Left:
				StartIndex = BitmapTableLength - 1;
				LineStart[i] = 0;
				break;
			
			case RollType_Inverted_None:
			case RollType_Inverted_Right:
				StartIndex = BitmapTableLength - 1;
				LineStart[i] = x_end;		
				break;
				
			case RollType_Inverted_Center:
				StartIndex = BitmapTableLength - 1;
				if(LineMargin[i] > 0)
				{
					LineStart[i] = LineMargin[LineCount - i - 1] >> 1;// + (LineMargin[LineCount - i - 1]/maxCharWidth) * wordSpace;
				}
				else
				{
					LineStart[i] = 0;
				}
				break;		
			
			case RollType_Order_Center:
			default:
				StartIndex = 0;
				if(LineMargin[i] > 0)
				{
					LineStart[i] = LineMargin[i] >> 1;// + (LineMargin[i]/maxCharWidth) * wordSpace;
				}
				else
				{
					LineStart[i] = 0;
				}
				break;
		}
	}
}

void DecodeMultiLineText::ChangeText(const char* text, const char* fontPath)
{
	unsigned int address = GetFileAddress(fontPath);
	short lineWidth = 0;
	short spaceCount = 0;
	LineCount = 0;
	if(address == 0)
	{//没找到字库
		BitmapTableLength = 0;//标记字符串长度为0，停止句柄对此文本框的输出
		return;
	}
	for(int i=0; i<MaxLineNumber; i++)
	{
		LineStart[i] = 0;
		LineMargin[i] = -1;
	}
	int textIndex = 0;
	int tableIndex = 0;
	unsigned short fontlength = ReadHalfWordImmediately(address);
	address+=2;
	maxCharWidth = 0;
	while(text[textIndex] != '\0')
	{
		int index = text[textIndex];
		if(text[textIndex]&0x80)
		{//多字节编码
			for(textIndex++; (text[textIndex]&0xC0)==0x80; textIndex++)
			{
				index <<= 8;
				index |= text[textIndex];
			}
		}
		else
			textIndex++;
		
		if(index == '\n')
		{//换行符
			BitmapTable[tableIndex] = -2;
			
			LineMargin[LineCount] = width;
			LineMargin[LineCount] -= lineWidth;
			LineMargin[LineCount] -= spaceCount * maxCharWidth;
			
			spaceCount = 0;
			lineWidth = 0;
			
			if(++LineCount >= MaxLineNumber)
			{
				break;
			}	
		}
		else
		{//字符
			//查找字库
			int bitmap = -1;
			CreatFlashReader(address);//开始传输
			
			for(int j=0; j<fontlength; j++)
			{
				int utf8 = GetWord();
				if(utf8 == index)
				{
					bitmap = address+(fontlength<<2)+(j<<1);//utf8开始地址+所有utf8列表长度+当前
					break;
				}
			}
			CloseFlashReader();//传输终止
			if(bitmap < 0)//能找到的大于等于0，找不到的为-1，绘制时所有-1绘制成空格	
			{
				BitmapTable[tableIndex] = -1;
				spaceCount++;
			}
			else
			{
				BitmapTable[tableIndex] = address + ReadHalfWordImmediately(bitmap);
				unsigned short width = ReadHalfWordImmediately(BitmapTable[tableIndex]);		
				lineWidth += width;
				if(maxCharWidth < width)
				{
					maxCharWidth = width;
				}
			}
		}
		
		tableIndex++;
	}
	
	if(spaceCount || lineWidth)
	{//未以换行符结尾
		LineMargin[LineCount] = width;
		LineMargin[LineCount] -= lineWidth;
		LineMargin[LineCount] -= spaceCount * maxCharWidth;
		LineCount++;
	}
	
	for(int i=0; i<tableIndex; i++)
	{
		if(BitmapTable[i] >= 0)
		{
			CharHeight = ReadHalfWordImmediately(BitmapTable[i]+2);
			break;
		}
	}
	BitmapTableLength = tableIndex;
	
	ChangeType(type);
}

void DecodeMultiLineText::ChangeTextPos(unsigned short x, unsigned short y)
{
	unsigned short width = x_end - this->x;
	this->x = x;
	this->y = y;
	x_end = width + x;
	if(x >= SCREEN_PIXEL_WIDTH)
	{
		x_end = SCREEN_PIXEL_WIDTH - x - 1;
	}
}

void DecodeMultiLineText::ChangeTextPos(unsigned short x, unsigned short y, unsigned short width)
{
	this->x = x;
	this->y = y;
	this->x_end = width + x - 1;
	if(x_end >= SCREEN_PIXEL_WIDTH)
	{
		x_end = SCREEN_PIXEL_WIDTH - 1;
	}
	ChangeType(type);
}

void DecodeMultiLineText::ChangeTextPos(unsigned short x, unsigned short y, unsigned short width, short wordSpace)
{
	this->x = x;
	this->y = y;
	x_end = width + x - 1;
	if(x_end >= SCREEN_PIXEL_WIDTH)
	{
		x_end = SCREEN_PIXEL_WIDTH - 1;
	}
	this->wordSpace = wordSpace;	
	ChangeType(type);
}

void DecodeMultiLineText::ChangeColor(unsigned short background, unsigned short foreground)
{
	this->background = background;
	this->foreground = foreground;
	int R = (foreground & 0xF800)>>12;
	int G = (foreground & 0x7E0)>>6;
	int B = foreground & 0x1F>>1;
	if(foreground != background)
	{
		R += (background & 0xF800)>>12;
		G += (background & 0x7E0)>>6;
		B += background & 0x1F>>1;		
	}
	half = (R << 11) | (G << 5) | B;
	R >>= 1;
	G >>= 1;
	B >>= 1;
	quartern = (R << 11) | (G << 5) | B;
}

void DecodeMultiLineText::ChangeStartLine(char start)
{
	if(start >= LineCount)
	{
		start = 0;
	}
	LineIndex = start;
}

bool DecodeMultiLineText::DrawText(void)
{
	if(!BitmapTableLength || sleep)
	{//没有存储需要显示文本 或休眠 的直接跳过
		return false;
	}	
	short lineIndex = LineIndex;
	char_x = LineStart[lineIndex] + x;
	char_y = y + lineIndex * CharHeight;
	short index = StartIndex;
	int drawing = 1, skip = 0;
	while(drawing)
	{
		int	bitmapindex = BitmapTable[index];//获取字典索引

		short firstwidth, width;
		if(bitmapindex >= 0)
		{//普通字符
			width = ReadHalfWordImmediately(bitmapindex);//普通字符直接获取宽度
		}
		else if(bitmapindex >= -1)
		{//空格
			width = maxCharWidth;//空格使用字符串全部文本最大宽度					
		}
		else
		{//换行
			if(++lineIndex >= LineCount)
			{//行循环
				lineIndex = 0;
			}
			char_x = LineStart[lineIndex] + x;
			char_y += CharHeight;
			if(char_y >= SCREEN_PIXEL_HEIGHT)
			{
				drawing = 0;
				break;
			}
			skip = 1;
		}
		width += wordSpace;//在字符宽度基础上增加字间距处理，获取增加字间距的字符宽度
		if(index == StartIndex)
		{//本次显示的第一个字符，需要额外处理
			firstwidth = width;//记录本次显示的第一个字符宽度
		}
		//控制绘制节奏
		switch(type)
		{
			case RollType_Order_None:
				if(++index >= BitmapTableLength //文本结束退出
					|| char_x >= x_end)//显示溢出退出
				{
					drawing = 0;//文本结束退出
					//sleep = true;
				}		
				break;
				
			case RollType_Order_Left:
				if(++index >= BitmapTableLength)
				{
					index = 0;//循环文本
				}
				if(index == StartIndex /*文本第二次出现退出*/
					|| char_x >= x_end/*显示右侧溢出退出*/
					/*显示左侧溢出退出*/)
				{
					drawing = 0;//退出文本刷新
				}	
				break;
				
			case RollType_Order_Right:	
				if(++index >= BitmapTableLength)
				{
						index = 0;
				}
				if(index == StartIndex /*文本第二次出现退出*/
					|| char_x + firstwidth <= 0/*显示溢出退出*/)
				{
					drawing = 0;//退出文本刷新
				}
				break;

			case RollType_Inverted_None:
				if(--index < 0 //文本结束退出
					|| char_x >= x_end)//显示溢出退出
				{
					drawing = 0;//文本结束退出
					//sleep = true;
				}			
				break;
			
			case RollType_Inverted_Left:
				if(--index < 0)
				{
					index = BitmapTableLength - 1;
				}
				if(index == StartIndex /*文本第二次出现退出*/
					|| char_x >= x_end/*显示溢出退出*/)
				{
					drawing = 0;//退出文本刷新
				}
				break;
			
			case RollType_Inverted_Right:	
				if(--index < 0)
				{
					index = BitmapTableLength - 1;
				}
				if(index == StartIndex /*文本第二次出现退出*/
					|| char_x + firstwidth <= 0/*显示溢出退出*/)
				{
					drawing = 0;//退出文本刷新
				}
				break;
			
			case RollType_Inverted_Center:
				if(--index < 0)//文本结束退出
				{
					drawing = 0;//退出文本刷新
				}	
				if(char_x >= x_end)//显示溢出强制换行
				{
					while(BitmapTable[index] >= -1)//直到出现换行
					{
						if(++index >= BitmapTableLength)//文本结束退出
						{
							drawing = 0;//退出文本刷新
						}
					}
				}	
				break;
				
			case RollType_Order_Center:
			default:
				if(++index >= BitmapTableLength)//文本结束退出
				{
					drawing = 0;//退出文本刷新
				}	
				if(char_x >= x_end)//显示溢出强制换行
				{
					while(BitmapTable[index] >= -1)//直到出现换行
					{
						if(++index >= BitmapTableLength)//文本结束退出
						{
							drawing = 0;//退出文本刷新
						}
					}
				}	
				break;
		}
		
		//绘制
		if(skip)
		{
			skip = 0;
		}
		else
		{
			if(bitmapindex < 0)
			{//绘制一个空格
				DrawBackground(width);	
			}
			else 	if(type == RollType_Order_Right || type == RollType_Inverted_Right)
			{//绘制文本
				DecodeRollTextAntiAliasing_Right(bitmapindex);
			}
			else
			{
				DecodeRollTextAntiAliasing(bitmapindex);
			}
		}
	
	}
	return true;
}

/******************************************************************************/

IDecodeText& DecodeFont::GetText(int index)
{
	IDecodeText* target = text;
	for(int i=0; i<index; i++)
	{
		if(target->next)
		{
			target = target->next;
		}
	}
	return *target;
}

void DecodeFont::CreatText(void)
{
	IDecodeText* node = new DecodeSingleText();
	if(!text)
	{
		text = node;
	}
	else
	{
		IDecodeText* target = text;
		while(target->next)
		{
			target = target->next;
		}
		target->next = node;
	}
}

void DecodeFont::CreatText(char line)
{
	DecodeMultiLineText* node = new DecodeMultiLineText(line);
	if(!text)
	{
		text = node;
	}
	else
	{
		IDecodeText* target = text;
		while(target->next)
		{
			target = target->next;
		}
		target->next = node;
	}
}

void DecodeFont::SleepAll(void)
{
	IDecodeText* target = text;
	if(target)
	{
		target->sleep = true;
	}
	while(target->next)
	{
		target = target->next;
		target->sleep = true;
	}	
}

bool DecodeFont::Handle(unsigned short* videoMemory, int line)
{
	bool result = false;
	IDecodeText* target = text;
	while(target)
	{
		if(line == 0)
		{//首次扫描 创建临时绘制位置表和上次绘制记录表
			
		}
		
		
		//判断并绘制位于当前区域的文本内容
		result = target->DrawText(videoMemory, line) || result;
		
		if(line >= (SCREEN_REFRESH_LOOP-1))
		{//屏幕的最后一块 需要在这里更新文本滚动信息
			
		}	
		
		target = target->next;
	}
	return result;
}








