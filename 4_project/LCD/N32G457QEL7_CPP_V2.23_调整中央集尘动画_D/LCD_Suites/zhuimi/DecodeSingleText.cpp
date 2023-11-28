#include "DecodeSingleText.h"

void DecodeSingleText::SetRollText(unsigned short x_new, unsigned short y_new, unsigned short width_new, const char* text, const char* fontPath, 
													short wordSpace_new, short SpaceGain_new, RollType_en type_new, unsigned short background_new, unsigned short foreground_new)
{
	x = x_new;
	y = y_new;
	x_end = width_new + x_new - 1;
	if(x_end >= SCREEN_PIXEL_WIDTH)
	{
		x_end = SCREEN_PIXEL_WIDTH - 1;
	}
	wordSpace = wordSpace_new;
	SpaceGain = SpaceGain_new;
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

void DecodeSingleText::SetRollText(const TextInfo& info)
{
	SetRollText(info.x, info.y, info.width, info.text, info.fontPath, info.wordSpace, info.SpaceGain, info.type, info.color, info.color);
}

void DecodeSingleText::ChangeType(RollType_en type_new)
{
	type = type_new;
	short spacelength = LineMargin - (BitmapTableLength - 1) * wordSpace;
	short charlenth = maxCharWidth - wordSpace;
	char spaceNum = 1;
	if(spacelength >= 0)
	{
		spaceNum += spacelength /charlenth;
		if(spacelength%charlenth)
		{
			spaceNum += 1;
		}
	}
	
	switch(type_new)
	{
		case RollType_Order_Right:
			StartIndex = 0;
			context_x = x_end;
			for(int i=0; i<spaceNum; i++)
			{
				BitmapTable[BitmapTableLength + i] = -1;
			}
			BitmapTableLength += spaceNum;
			break;
		
		case RollType_Order_Center_Right:
			StartIndex = 0;
			if(spacelength > 0)
			{
				LineStart = x_end - (spacelength >> 1);
			}
			else
			{
				LineStart = x_end;
			}
			context_x = LineStart;
			break;

		case RollType_Inverted_None:
			StartIndex = BitmapTableLength - 1;
			context_x = x;	
			break;

		case RollType_Inverted_Left:
			StartIndex = BitmapTableLength - 1;
			context_x = x;	
			for(int i=0; i<spaceNum; i++)
			{
				BitmapTable[BitmapTableLength + i] = -1;
			}
			BitmapTableLength += spaceNum;
			break;
		
		case RollType_Inverted_Right:
			StartIndex = BitmapTableLength - 1;
			context_x = x_end;
			for(int i=0; i<spaceNum; i++)
			{
				BitmapTable[BitmapTableLength + i] = -1;
			}
			BitmapTableLength += spaceNum;
			break;
		
		case RollType_Inverted_Center_Right:
			StartIndex = BitmapTableLength - 1;
			if(spacelength > 0)
			{
				LineStart = x_end - (spacelength  >> 1);
			}
			else
			{
				LineStart = x_end;
			}
			context_x = LineStart;
			break;
		
		case RollType_Order_None:
			StartIndex = 0;
			context_x = x;
			break;
		
		case RollType_Order_Left: 
			StartIndex = 0;
			context_x = x;		
			for(int i=0; i<spaceNum; i++)
			{
				BitmapTable[BitmapTableLength + i] = -1;
			}
			BitmapTableLength += spaceNum;
			break;
		
		case RollType_Inverted_Center_Left:
		case RollType_Inverted_Center:
			StartIndex = BitmapTableLength - 1;
			if(spacelength > 0)
			{
				LineStart += spacelength >> 1;
			}
			context_x = LineStart;
			break;

		case RollType_Order_Center_Left:
		case RollType_Order_Center:
		default:
			StartIndex = 0;
			if(spacelength > 0)
			{
				LineStart += spacelength >> 1;
			}
			context_x = LineStart;
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
	int spaceCount = 0;
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
			spaceCount++;
		}
		else
		{
			BitmapTable[tableIndex] = address + ReadHalfWordImmediately(bitmap);
			unsigned short width = ReadHalfWordImmediately(BitmapTable[tableIndex]);		
			LineMargin -= width;// + wordSpace;
//			if(LineMargin < 0)
//			{
//				LineMargin = 0;
//			}
			if(maxCharWidth < width)
			{
				maxCharWidth = width;
			}
		}
		
		if(++tableIndex >= ROLL_TEXT_STRING_MAX_LENGTH)
		{
			break;
		}
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
	LineMargin -= spaceCount * maxCharWidth;//(maxCharWidth + wordSpace);
//	if(LineMargin != 0)
//	{
//		LineMargin += wordSpace;
//	}
//	if(LineMargin < 0)
//	{
//		LineMargin = 0;
//	}
	ChangeType(type);
}

void DecodeSingleText::ChangeTextPos(unsigned short x_new, unsigned short y_new)
{
	unsigned short width = x_end - x;
	x = x_new;
	y = y_new;
	x_end = width + x_new;
	if(x_end >= SCREEN_PIXEL_WIDTH)
	{
		x_end = SCREEN_PIXEL_WIDTH -1;
	}
}

void DecodeSingleText::ChangeTextPos(unsigned short x_new, unsigned short y_new, unsigned short width_new)
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

void DecodeSingleText::ChangeTextPos(unsigned short x_new, unsigned short y_new, unsigned short width_new, short wordSpace_new)
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

void DecodeSingleText::ChangeColor(unsigned short background_new, unsigned short foreground_new)
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

bool DecodeSingleText::DrawText(unsigned short* videoMemory, int line)
{
	if(!BitmapTableLength || sleep)
	{//没有存储需要显示文本 或休眠 的直接跳过
		return false;
	}
	//判断是否需要绘制
	unsigned short buff_y_start = line*DECODE_BUFFER_HEIGHT;
	unsigned short buff_y_end = buff_y_start + DECODE_BUFFER_HEIGHT;
	unsigned short drawLine = 0, targetLine = 0;
	bool startDrawFlag = false;
	if(startDraw)
	{//已经开始绘制
		unsigned short y_end = y + CharHeight;
		if(y_end < buff_y_start)
		{//停止绘制
			startDraw = false;
			return false;
		}
		else
		{//继续绘制
				//计算本次绘制行数
			unsigned short toPicEnd = y_end - buff_y_start;
			drawLine = toPicEnd>DECODE_BUFFER_HEIGHT?DECODE_BUFFER_HEIGHT:toPicEnd;//显存位置到图片结尾高度与显存高度的最小值
		}
	}
	else
	{//未开始绘制
		if(y >= buff_y_start && y < buff_y_end)
		{//开始绘制
			startDraw = true;
			startDrawFlag = true;
			
			//计算本次图片绘制到显存的起始行
			targetLine = y - buff_y_start;
			
			//计算本次绘制行数
			unsigned short toBuffEnd = buff_y_end - y;
			drawLine = toBuffEnd>CharHeight?CharHeight:toBuffEnd;//图片到当前缓存结尾和图片高度的最小值
		}
		else
		{//不需要绘制
			return false;
		}
	}
	
	char_x = context_x;
	char_y = y;		
	char_end = char_x;
	short index = StartIndex;
	short currentIndex = index; 
	bool drawing = true;
	int spaceGainSum = 0;
	while(drawing)
	{	
		int	bitmapindex;
		if(index >= 0)
		{
			bitmapindex = BitmapTable[index];//获取字典索引
		}
		else
		{
			bitmapindex = -1;
		}
		
	//	short indexCurrent = index;
		short char_width;
		if(bitmapindex < 0)
		{
			char_width = maxCharWidth + SpaceGain;//空格使用字符串全部文本最大宽度 增加空格增益		
			if(char_width <= 0)
			{
				char_width = 0;
			}
			spaceGainSum += char_width - maxCharWidth;
		}
		else
		{
			char_width = ReadHalfWordImmediately(bitmapindex);//普通字符直接获取宽度
		}
		if(index == StartIndex)
		{//本次显示的第一个字符，需要额外处理
			firstwidth = char_width + wordSpace;//记录本次显示的第一个字符宽度
		}
	
		//控制绘制结束
		if(type >= RollType_Order_Right)
		{
			if(char_x <= 0 || char_x - firstwidth >= x_end)/*显示溢出退出*/
			{
				drawing = false;//退出本行文本刷新
			}
		}
		else
		{
			if(char_x + firstwidth <= 0 || char_x >= x_end)/*显示溢出退出*/
			{
				drawing = false;//退出本行文本刷新
			}
		}
		
		
		//绘制
		if(drawing)
		{
			if(startDrawFlag && index >= 0)
			{
				BitmapCurrent[currentIndex] = BitmapTable[index] + 6;//空格也会被赋值 =5 但不会被使用
				LastCode[currentIndex] = 0;
			}		
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
					DecodeRollTextAntiAliasing(videoMemory, currentIndex, drawLine, targetLine, char_width);	
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
					DecodeRollTextAntiAliasing(videoMemory, currentIndex, drawLine, targetLine, char_width);	
				}
				char_x = char_end + wordSpace;
			}
		}

		//控制选择下一个字符
		if(index >= 0)
		{
			if(type&1)
			{
				if(--index < 0)
				{
					index = BitmapTableLength - 1;
				}
			}
			else
			{
				if(++index >= BitmapTableLength)
				{
					index = 0;//循环文本
				}
			}
			//文本循环
			if(index == StartIndex) /*文本第二次出现退出*/
			{
				if((type == RollType_Order_Center_Left || type == RollType_Inverted_Center_Left 
					|| type == RollType_Order_Center_Right || type == RollType_Inverted_Center_Right
					|| type == RollType_Order_Center || type == RollType_Inverted_Center))
				{//带有居中属性的 允许字符重复出现	
					if(LineMargin - BitmapTableLength * wordSpace - spaceGainSum> 0)
					{
						firstwidth = 0;	
						drawing = false;//退出本行文本刷新
					}
				}
				else
				{
					index = -1;//标记为非法索引值
				}

			}
			else
			{
				//currentIndex = index;//不重复时与输入位置相同
			}
			if(type&1)
			{//临时存储区域以整个存储空间作为范围
				if(--currentIndex < 0)
				{
					currentIndex = ROLL_TEXT_STRING_MAX_LENGTH - 1;
				}
			}
			else
			{
				if(++currentIndex >= ROLL_TEXT_STRING_MAX_LENGTH)
				{
					currentIndex = 0;//循环文本
				}
			}
		}
		
	}
	return true;
}

void DecodeSingleText::RollText(void)
{
	if(!firstwidth || pause)
	{//没有存储需要显示文本 或休眠 或不需要滚动文本 的直接跳过
		return;
	}
	//控制绘制节奏
	switch(type)
	{		
		case RollType_Order_Center_Right:
		case RollType_Order_Right:	
			context_x += ROOL_SPEED;
			if(context_x - firstwidth >= x_end)
			{
				context_x = x_end -1;
				if(++StartIndex >= BitmapTableLength)
				{
					StartIndex = 0;
				}
			}
			break;
			
		case RollType_Inverted_Center_Left:
		case RollType_Inverted_Center:
		case RollType_Inverted_Left:
			context_x -= ROOL_SPEED;
			if(context_x + firstwidth <= x)
			{
				context_x = x;
				if(--StartIndex < 0)
				{
					StartIndex = BitmapTableLength - 1;
				}
			}
			break;
		
		case RollType_Inverted_Center_Right:
		case RollType_Inverted_Right:	
			context_x += ROOL_SPEED;
			if(context_x - firstwidth >= x_end)
			{
				context_x -= firstwidth;
				if(--StartIndex < 0)
				{
					StartIndex = BitmapTableLength - 1;
				}
			}
			break;
			
		case RollType_Order_Center_Left:
		case RollType_Order_Center:
		case RollType_Order_Left:
			context_x -= ROOL_SPEED;
			if(context_x + firstwidth <= x)
			{
				context_x = x;
				if(++StartIndex >= BitmapTableLength)
				{
					StartIndex = 0;
				}
			}
			break;
			
		case RollType_Order_None:
		case RollType_Inverted_None:
		default:
			break;
	}
}
