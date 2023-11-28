#include "DecodeFont.h"

//void IDecodeText::SetRollText(unsigned short x_new, unsigned short y_new, unsigned short width_new, const char* text, const char* fontPath, short wordSpace_new, RollType_en type_new, unsigned short background_new, unsigned short foreground_new)
//{(void)x_new;(void)y_new;(void)width_new;(void)text;(void)fontPath;(void)wordSpace_new;(void)type_new;(void)background_new;(void)foreground_new;}

//void IDecodeText::SetRollText(const TextInfo& info)
//{(void)info;}

//void IDecodeText::ChangeType(RollType_en type_new)
//{(void)type_new;}

//void IDecodeText::ChangeText(const char* text, const char* fontPath)
//{(void)text;(void)fontPath;}

//void IDecodeText::ChangeTextPos(unsigned short x_new, unsigned short y_new)
//{(void)x_new;(void)y_new;}

//void IDecodeText::ChangeTextPos(unsigned short x_new, unsigned short y_new, unsigned short width_new)
//{(void)x_new;(void)y_new;(void)width_new;}

//void IDecodeText::ChangeTextPos(unsigned short x_new, unsigned short y_new, unsigned short width_new, short wordSpace_new)
//{(void)x_new;(void)y_new;(void)width_new;(void)wordSpace_new;}

//void IDecodeText::ChangeColor(unsigned short background_new, unsigned short foreground_new)
//{(void)background_new;(void)foreground_new;}

//bool IDecodeText::DrawText(unsigned short* videoMemory, int line)
//{(void)videoMemory;(void)line; return false;}

//void IDecodeText::RollText(void)
//{(void)firstwidth;}


/******************************************字库解码公共模块**************************************************/

bool IDecodeText::IsMultiLine(void)
{
	return MultiLine;
}

void IDecodeText::ReadyToDraw(void)
{
	startDraw = false;
}

void IDecodeText::DrawRollCode(unsigned short* buffer, unsigned char type, unsigned char num)
{
	if(num)
	{
		unsigned short color;
		switch(type)
		{
			case 0xC0:
				color = foreground;
				break;
			
			case 0x80:
				color = half;
				break;
			
			case 0x40:
				color = quartern;
				break;
			
			case 0x00:
			default:
				color = background;
				if(background == foreground)
				{
					num = 0;
				}
				break;
		}
		for(int i=0; i<num; i++)
		{
			buffer[i] = color;
		}
	}	
}



void IDecodeText::DecodeRollTextAntiAliasing(unsigned short* videoMemory, short index, unsigned short drawLine, unsigned short targetLine, unsigned short charWidth)
{
	if(charWidth <= 0)
	{
		return;
	}
	unsigned short* target = videoMemory + targetLine * SCREEN_PIXEL_WIDTH;//锁定行
	unsigned short* targetEnd = target + x_end;//锁定行尾
	unsigned short remove_start;//默认行首删除值
	if(char_x >= x)
	{
		target += char_x;//锁定列
		remove_start = 0;//修正行尾删除值
	}
	else
	{
		target += x;
		remove_start = x - char_x;
	}
	unsigned short* targetStart = target;//记录行开始位置
	CreatFlashReader((unsigned int)BitmapCurrent[index]);	
	for(int i=0; i<drawLine; i++)//控制绘制行数
	{	
		unsigned short remove_start_temp = remove_start;//每行需要减少的开始数据长度
		short needDraw = charWidth;
		while(needDraw)//控制单行绘制数量
		{
			//获取编码数据
			unsigned char code;
			if(LastCode[index])
			{
				code = LastCode[index];
				LastCode[index] = 0;
			}
			else
			{
				code = GetByte();
				BitmapCurrent[index] += 1;
			}
			
			//消耗编码数据
			unsigned char type = code & 0xC0;
			unsigned char num = code & 0x3F;
		
			//计算剩余量
			unsigned char residue = 0;//剩余值
			unsigned char expected = num;//预期值
			
			if(needDraw < num)
			{//有剩余
				residue = num - needDraw;//计算剩余
				LastCode[index] = type | residue;//存储剩余值
				expected = needDraw;//更新绘制量预期值
			}

			//计算绘制量实际值
			unsigned char actual = expected;//实际值
			if(remove_start_temp)//行首部分删减
			{
				unsigned char min = actual>remove_start_temp?remove_start_temp:actual;
				actual -= min;
				remove_start_temp -= min;
			}
			
			if(reinterpret_cast<int>(target) + (actual<<1) >= reinterpret_cast<int>(targetEnd))//行尾部分删减
			{
				unsigned char toend = reinterpret_cast<int>(targetEnd) - reinterpret_cast<int>(target);
				actual = toend >> 1;
			}
			
			DrawRollCode(target, type, actual);//按照实际值绘制
			target += actual;
			
			//调整还需要绘制数据量
			needDraw -= expected;
		}
		targetStart += SCREEN_PIXEL_WIDTH;
		target = targetStart;
		targetEnd += SCREEN_PIXEL_WIDTH;
	}	
	CloseFlashReader();
}

//空格直接写入显存
void IDecodeText::DrawBackground(unsigned short* videoMemory, short width, unsigned short drawLine, unsigned short targetLine)
{
	if(background != foreground)
	{
		unsigned short* target = videoMemory + targetLine * SCREEN_PIXEL_WIDTH;//锁定行
		unsigned short remove_start;//默认行首删除值
		unsigned short toTextEnd;
		if(char_x >= x)
		{
			target += char_x;//字符开始在文本框内
			remove_start = 0;//修正行尾删除值
			toTextEnd = x_end - char_x;//字符开始到文本框结尾长度
		}
		else
		{
			target += x;//字符开始在文本框左侧
			remove_start = x - char_x;//删除文本框前部分
			toTextEnd = x_end - x;//文本框长度
		}
		
		short num = width>toTextEnd?toTextEnd:width;
		num -= remove_start;
		if(num < 0)
		{
			num = 0;
		}
		for(int i=0; i<drawLine; i++)
		{
			for(int i=0; i<num; i++)
			{
				target[i] = background;
			}
			target += SCREEN_PIXEL_WIDTH;//移动到下一行
		}
	}
}


