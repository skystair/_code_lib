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
	{//û�ҵ��ֿ�
		BitmapTableLength = 0;//����ַ�������Ϊ0��ֹͣ����Դ��ı�������
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
		{//���ֽڱ���
			for(i++; (text[i]&0xC0)==0x80; i++)
			{
				index <<= 8;
				index |= text[i];
			}
		}
		else
			i++;
		
		//�����ֿ�
		int bitmap = -1;
		
		CreatFlashReader(address);//��ʼ����
		for(int j=0; j<fontlength; j++)
		{
			int utf8 = GetWord();
			if(utf8 == index)
			{
				bitmap = address+(fontlength<<2)+(j<<1);//utf8��ʼ��ַ+����utf8�б���+��ǰ
				break;
			}
		}
		CloseFlashReader();//������ֹ
		
		if(bitmap < 0)//���ҵ��Ĵ��ڵ���0���Ҳ�����Ϊ-1������ʱ����-1���Ƴɿո�	
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
	{//û�д洢��Ҫ��ʾ�ı� ������ ��ֱ������
		return false;
	}
	//�ж��Ƿ���Ҫ����
	unsigned short buff_y_start = line*DECODE_BUFFER_HEIGHT;
	unsigned short buff_y_end = buff_y_start + DECODE_BUFFER_HEIGHT;
	unsigned short drawLine = 0, targetLine = 0;
	bool startDrawFlag = false;
	if(startDraw)
	{//�Ѿ���ʼ����
		unsigned short y_end = y + CharHeight;
		if(y_end < buff_y_start)
		{//ֹͣ����
			startDraw = false;
			return false;
		}
		else
		{//��������
				//���㱾�λ�������
			unsigned short toPicEnd = y_end - buff_y_start;
			drawLine = toPicEnd>DECODE_BUFFER_HEIGHT?DECODE_BUFFER_HEIGHT:toPicEnd;//�Դ�λ�õ�ͼƬ��β�߶����Դ�߶ȵ���Сֵ
		}
	}
	else
	{//δ��ʼ����
		if(y >= buff_y_start && y < buff_y_end)
		{//��ʼ����
			startDraw = true;
			startDrawFlag = true;
			
			//���㱾��ͼƬ���Ƶ��Դ����ʼ��
			targetLine = y - buff_y_start;
			
			//���㱾�λ�������
			unsigned short toBuffEnd = buff_y_end - y;
			drawLine = toBuffEnd>CharHeight?CharHeight:toBuffEnd;//ͼƬ����ǰ�����β��ͼƬ�߶ȵ���Сֵ
		}
		else
		{//����Ҫ����
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
			bitmapindex = BitmapTable[index];//��ȡ�ֵ�����
		}
		else
		{
			bitmapindex = -1;
		}
		
	//	short indexCurrent = index;
		short char_width;
		if(bitmapindex < 0)
		{
			char_width = maxCharWidth + SpaceGain;//�ո�ʹ���ַ���ȫ���ı������ ���ӿո�����		
			if(char_width <= 0)
			{
				char_width = 0;
			}
			spaceGainSum += char_width - maxCharWidth;
		}
		else
		{
			char_width = ReadHalfWordImmediately(bitmapindex);//��ͨ�ַ�ֱ�ӻ�ȡ���
		}
		if(index == StartIndex)
		{//������ʾ�ĵ�һ���ַ�����Ҫ���⴦��
			firstwidth = char_width + wordSpace;//��¼������ʾ�ĵ�һ���ַ����
		}
	
		//���ƻ��ƽ���
		if(type >= RollType_Order_Right)
		{
			if(char_x <= 0 || char_x - firstwidth >= x_end)/*��ʾ����˳�*/
			{
				drawing = false;//�˳������ı�ˢ��
			}
		}
		else
		{
			if(char_x + firstwidth <= 0 || char_x >= x_end)/*��ʾ����˳�*/
			{
				drawing = false;//�˳������ı�ˢ��
			}
		}
		
		
		//����
		if(drawing)
		{
			if(startDrawFlag && index >= 0)
			{
				BitmapCurrent[currentIndex] = BitmapTable[index] + 6;//�ո�Ҳ�ᱻ��ֵ =5 �����ᱻʹ��
				LastCode[currentIndex] = 0;
			}		
			if(type >= RollType_Order_Right)
			{//���Ʒ��򣺴�������
				char_end = char_x;
				char_x -= char_width;
				if(bitmapindex < 0)
				{//���ƿո�
					DrawBackground(videoMemory, char_width, drawLine, targetLine);
				}
				else
				{//�����ı�
					DecodeRollTextAntiAliasing(videoMemory, currentIndex, drawLine, targetLine, char_width);	
				}		
				char_x -= wordSpace;
			}
			else
			{//���Ʒ��򣺴�������
				char_end = char_x + char_width;
				if(bitmapindex < 0)
				{//���ƿո�
					DrawBackground(videoMemory, char_width, drawLine, targetLine);
				}
				else
				{//�����ı�
					DecodeRollTextAntiAliasing(videoMemory, currentIndex, drawLine, targetLine, char_width);	
				}
				char_x = char_end + wordSpace;
			}
		}

		//����ѡ����һ���ַ�
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
					index = 0;//ѭ���ı�
				}
			}
			//�ı�ѭ��
			if(index == StartIndex) /*�ı��ڶ��γ����˳�*/
			{
				if((type == RollType_Order_Center_Left || type == RollType_Inverted_Center_Left 
					|| type == RollType_Order_Center_Right || type == RollType_Inverted_Center_Right
					|| type == RollType_Order_Center || type == RollType_Inverted_Center))
				{//���о������Ե� �����ַ��ظ�����	
					if(LineMargin - BitmapTableLength * wordSpace - spaceGainSum> 0)
					{
						firstwidth = 0;	
						drawing = false;//�˳������ı�ˢ��
					}
				}
				else
				{
					index = -1;//���Ϊ�Ƿ�����ֵ
				}

			}
			else
			{
				//currentIndex = index;//���ظ�ʱ������λ����ͬ
			}
			if(type&1)
			{//��ʱ�洢�����������洢�ռ���Ϊ��Χ
				if(--currentIndex < 0)
				{
					currentIndex = ROLL_TEXT_STRING_MAX_LENGTH - 1;
				}
			}
			else
			{
				if(++currentIndex >= ROLL_TEXT_STRING_MAX_LENGTH)
				{
					currentIndex = 0;//ѭ���ı�
				}
			}
		}
		
	}
	return true;
}

void DecodeSingleText::RollText(void)
{
	if(!firstwidth || pause)
	{//û�д洢��Ҫ��ʾ�ı� ������ ����Ҫ�����ı� ��ֱ������
		return;
	}
	//���ƻ��ƽ���
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
