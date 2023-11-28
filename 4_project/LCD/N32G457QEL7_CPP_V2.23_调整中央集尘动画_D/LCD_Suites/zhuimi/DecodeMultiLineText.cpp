#include "DecodeMultiLineText.h"

void DecodeMultiLineText::SetRollText(unsigned short x_new, unsigned short y_new, unsigned short width_new, const char* text, const char* fontPath, 
													short wordSpace_new, short SpaceGain_new, RollType_en type_new, unsigned short background_new, unsigned short foreground_new)
{
	x = x_new;
	y = y_new;
	width = width_new;
	x_end = width_new + x_new - 1;
	if(x_end >= SCREEN_PIXEL_WIDTH)
	{
		x_end = SCREEN_PIXEL_WIDTH - 1;
	}
	wordSpace = wordSpace_new;
	type = type_new;
	background = background_new;
	foreground = foreground_new;
	int R = (foreground_new & 0xF800)>>11;
	int G = (foreground_new & 0x7E0)>>5;
	int B = foreground_new & 0x1F;
	int Rbg = (background_new & 0xF800)>>11;
	int Gbg = (background_new & 0x7E0)>>5;
	int Bbg =  background_new & 0x1F;

	if(foreground_new != background_new)
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
	SetRollText(info.x, info.y, info.width, info.text, info.fontPath, info.wordSpace, info.SpaceGain, info.type, info.color, info.color);
}

void DecodeMultiLineText::ChangeType(RollType_en type_new)
{
	type = type_new;
	short spacelength;
	for(int i=0; i<MaxLineNumber; i++)
	{
		if(type_new&1)
		{
			StartIndex = BitmapTableLength - 1;
			spacelength = LineMargin[i] - BitmapTableLength * wordSpace;
			if(LineMargin[i] > 0)
			{
				LineStart[i] = LineMargin[StartIndex - i] >> 1;
			}
			else
			{
				LineStart[i] = 0;
			}
		}
		else
		{
			StartIndex = 0;
			spacelength = LineMargin[i] - BitmapTableLength * wordSpace;
			if(spacelength > 0)
			{	
				LineStart[i] = spacelength >> 1;
			}
			else
			{
				LineStart[i] = 0;
			}
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

void DecodeMultiLineText::ChangeTextPos(unsigned short x_new, unsigned short y_new)
{
	unsigned short width = x_end - x;
	x = x_new;
	y = y_new;
	x_end = width + x_new;
	if(x_new >= SCREEN_PIXEL_WIDTH)
	{
		x_end = SCREEN_PIXEL_WIDTH - x_new - 1;
	}
}

void DecodeMultiLineText::ChangeTextPos(unsigned short x_new, unsigned short y_new, unsigned short width_new)
{
	x = x_new;
	y = y_new;
	x_end = width_new + x_new - 1;
	if(x_end >= SCREEN_PIXEL_WIDTH)
	{
		x_end = SCREEN_PIXEL_WIDTH - 1;
	}
	ChangeType(type);
}

void DecodeMultiLineText::ChangeTextPos(unsigned short x_new, unsigned short y_new, unsigned short width_new, short wordSpace_new)
{
	x = x_new;
	y = y_new;
	x_end = width_new + x_new - 1;
	if(x_end >= SCREEN_PIXEL_WIDTH)
	{
		x_end = SCREEN_PIXEL_WIDTH - 1;
	}
	wordSpace = wordSpace_new;	
	ChangeType(type);
}

void DecodeMultiLineText::ChangeColor(unsigned short background_new, unsigned short foreground_new)
{
	background = background_new;
	foreground = foreground_new;
	int R = (foreground_new & 0xF800)>>11;
	int G = (foreground_new & 0x7E0)>>5;
	int B = foreground_new & 0x1F;
	int Rbg = (background_new & 0xF800)>>11;
	int Gbg = (background_new & 0x7E0)>>5;
	int Bbg =  background_new & 0x1F;

	if(foreground_new != background_new)
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
}

void DecodeMultiLineText::ChangeStartLine(char start)
{
	if(start >= LineCount)
	{
		start = 0;
	}
	LineIndex = start;
}

bool DecodeMultiLineText::NeedDraw(int decodeLine, int textLine, unsigned short& drawLine, unsigned short& targetLine, short& index)
{
	//判断是否需要绘制
	unsigned short buff_y_start = decodeLine*DECODE_BUFFER_HEIGHT;
	unsigned short buff_y_end = buff_y_start + DECODE_BUFFER_HEIGHT;
	drawLine = 0, targetLine = 0;
	bool startDrawFlag = false;

	while(true)
	{
		unsigned short y_start = y + CharHeight * textLine;
		unsigned short y_end = y_start + CharHeight;
		if(startDraw)
		{//已经开始绘制
			if(y_end < buff_y_start)
			{//本行不绘制
				startDraw = false;
			}
			else
			{//继续绘制
					//计算本次绘制行数
				unsigned short toPicEnd = y_end - buff_y_start;
				drawLine = toPicEnd>DECODE_BUFFER_HEIGHT?DECODE_BUFFER_HEIGHT:toPicEnd;//显存位置到图片结尾高度与显存高度的最小值
				break;
			}
		}
		else
		{//未开始绘制
			if(y_start >= buff_y_start && y_start < buff_y_end)
			{//开始绘制
				startDraw = true;
				startDrawFlag = true;
				
				//计算本次图片绘制到显存的起始行
				targetLine = y_start - buff_y_start;
				
				//计算本次绘制行数
				unsigned short toBuffEnd = buff_y_end - y_start;
				drawLine = toBuffEnd>CharHeight?CharHeight:toBuffEnd;//图片到当前缓存结尾和图片高度的最小值
				break;
			}
			else
			{//本行不绘制
				startDraw = false;
			}
		}
		
		while(BitmapTable[index] >= -1)//直到出现换行
		{
			if(++index >= BitmapTableLength)//文本结束退出
			{	
				startDraw = false;//退出文本刷新
				return startDrawFlag;
			}
		}
		index++;
		textLine++;
	}
	
	
	return startDrawFlag;
}

bool DecodeMultiLineText::DrawText(unsigned short* videoMemory, int line)
{
	if(!BitmapTableLength || sleep)
	{//没有存储需要显示文本 或休眠 的直接跳过
		return false;
	}	
	short lineIndex = LineIndex;
	char_x = LineStart[lineIndex] + x;
	char_y = y + lineIndex * CharHeight;
	short index = StartIndex;
	bool drawing = true, skip = false;
	unsigned short drawLine=0, targetLine=0;
	
	bool startDrawFlag = NeedDraw(line, lineIndex, drawLine, targetLine, index);
	
	drawing = startDraw;
	while(drawing)
	{
		int	bitmapindex = BitmapTable[index];//获取字典索引
		if(startDrawFlag)
		{
			BitmapCurrent[index] = bitmapindex + 6;
			LastCode[index] = 0;
		}
		short char_width;
		
		if(bitmapindex >= 0)
		{//普通字符
			char_width = ReadHalfWordImmediately(bitmapindex);//普通字符直接获取宽度
		}
		else if(bitmapindex >= -1)
		{//空格
			char_width = maxCharWidth;//空格使用字符串全部文本最大宽度					
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
				drawing = false;
				break;
			}
			skip = true;
		}
		
		if(index == StartIndex)
		{//本次显示的第一个字符，需要额外处理
			firstwidth = char_width + wordSpace;//记录本次显示的第一个字符宽度
		}

		if(skip)
		{
			skip = false;
		}
		else
		{
			if(drawing)
			{
				if(type >= RollType_Order_Right)
				{//绘制方向：从右向左
					char_end = char_x;
					char_x -= char_width;
					if(bitmapindex < 0)
					{//绘制空格
						DrawBackground(videoMemory, char_width, drawLine, targetLine);
					}
					else
					{//绘制文本
						DecodeRollTextAntiAliasing(videoMemory, index, drawLine, targetLine, char_width);	
					}		
					char_x -= wordSpace;
				}
				else
				{//绘制方向：从左向右
					char_end = char_x + char_width;
					if(bitmapindex < 0)
					{//绘制空格
						DrawBackground(videoMemory, char_width, drawLine, targetLine);
					}
					else
					{//绘制文本
						DecodeRollTextAntiAliasing(videoMemory, index, drawLine, targetLine, char_width);	
					}
					char_x = char_end + wordSpace;
				}
			}
		}
		
		//控制绘制节奏
		if(type&1)
		{
			if(--index < 0)//文本结束退出
			{
				drawing = false;//退出文本刷新
			}	
			if(char_x >= x_end)//显示溢出强制换行
			{
				while(BitmapTable[index] >= -1)//直到出现换行
				{
					if(++index >= BitmapTableLength)//文本结束退出
					{
						drawing = false;//退出文本刷新
						break;
					}
				}
			}	
		}
		else
		{
			if(++index >= BitmapTableLength)//文本结束退出
			{
				drawing = false;//退出文本刷新
			}	
			if(char_x >= x_end)//显示溢出强制换行
			{
				break;
//				while(BitmapTable[index] >= -1)//直到出现换行
//				{
//					if(++index >= BitmapTableLength)//文本结束退出
//					{
//						drawing = false;//退出文本刷新
//						break;
//					}
//				}
			}	
		}	
	}
	return true;
}

void DecodeMultiLineText::RollText(void)
{

	
}






