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


/******************************************�ֿ���빫��ģ��**************************************************/

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
	unsigned short* target = videoMemory + targetLine * SCREEN_PIXEL_WIDTH;//������
	unsigned short* targetEnd = target + x_end;//������β
	unsigned short remove_start;//Ĭ������ɾ��ֵ
	if(char_x >= x)
	{
		target += char_x;//������
		remove_start = 0;//������βɾ��ֵ
	}
	else
	{
		target += x;
		remove_start = x - char_x;
	}
	unsigned short* targetStart = target;//��¼�п�ʼλ��
	CreatFlashReader((unsigned int)BitmapCurrent[index]);	
	for(int i=0; i<drawLine; i++)//���ƻ�������
	{	
		unsigned short remove_start_temp = remove_start;//ÿ����Ҫ���ٵĿ�ʼ���ݳ���
		short needDraw = charWidth;
		while(needDraw)//���Ƶ��л�������
		{
			//��ȡ��������
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
			
			//���ı�������
			unsigned char type = code & 0xC0;
			unsigned char num = code & 0x3F;
		
			//����ʣ����
			unsigned char residue = 0;//ʣ��ֵ
			unsigned char expected = num;//Ԥ��ֵ
			
			if(needDraw < num)
			{//��ʣ��
				residue = num - needDraw;//����ʣ��
				LastCode[index] = type | residue;//�洢ʣ��ֵ
				expected = needDraw;//���»�����Ԥ��ֵ
			}

			//���������ʵ��ֵ
			unsigned char actual = expected;//ʵ��ֵ
			if(remove_start_temp)//���ײ���ɾ��
			{
				unsigned char min = actual>remove_start_temp?remove_start_temp:actual;
				actual -= min;
				remove_start_temp -= min;
			}
			
			if(reinterpret_cast<int>(target) + (actual<<1) >= reinterpret_cast<int>(targetEnd))//��β����ɾ��
			{
				unsigned char toend = reinterpret_cast<int>(targetEnd) - reinterpret_cast<int>(target);
				actual = toend >> 1;
			}
			
			DrawRollCode(target, type, actual);//����ʵ��ֵ����
			target += actual;
			
			//��������Ҫ����������
			needDraw -= expected;
		}
		targetStart += SCREEN_PIXEL_WIDTH;
		target = targetStart;
		targetEnd += SCREEN_PIXEL_WIDTH;
	}	
	CloseFlashReader();
}

//�ո�ֱ��д���Դ�
void IDecodeText::DrawBackground(unsigned short* videoMemory, short width, unsigned short drawLine, unsigned short targetLine)
{
	if(background != foreground)
	{
		unsigned short* target = videoMemory + targetLine * SCREEN_PIXEL_WIDTH;//������
		unsigned short remove_start;//Ĭ������ɾ��ֵ
		unsigned short toTextEnd;
		if(char_x >= x)
		{
			target += char_x;//�ַ���ʼ���ı�����
			remove_start = 0;//������βɾ��ֵ
			toTextEnd = x_end - char_x;//�ַ���ʼ���ı����β����
		}
		else
		{
			target += x;//�ַ���ʼ���ı������
			remove_start = x - char_x;//ɾ���ı���ǰ����
			toTextEnd = x_end - x;//�ı��򳤶�
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
			target += SCREEN_PIXEL_WIDTH;//�ƶ�����һ��
		}
	}
}


