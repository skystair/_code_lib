#ifndef _DECODE_FONT_H_
#define _DECODE_FONT_H_

#include "DecodeLocate.h"
#include "Decode_Memory.h"

/*********************�����������*******************************/
//ע�⣺�������Ϊż�����������Ϊ����
typedef enum
{
	//�����ı�
	RollType_Order_Center    			= 0,//�����һ�ȡ�ַ��� �����ı�����---�����ı�Ĭ��״̬ ѡ��Ƕ����ı�״̬ ����ת�����״̬
	RollType_Inverted_Center 			= 1,//���ҵ����ȡ�ַ��� �����ı�����
	
	//�����ı�
	RollType_Order_None						= 2,//�����һ�ȡ�ַ��� ������ʾ���ı���
	RollType_Inverted_None				= 3,//���ҵ����ȡ�ַ��� ������ʾ���ı���
	RollType_Order_Left						=	4,//�����һ�ȡ�ַ��� �ı������ƶ�	
	RollType_Inverted_Left				= 5,//���ҵ����ȡ�ַ��� �ı������ƶ�		
	RollType_Order_Center_Left		= 6,//�����һ�ȡ�ַ��� �����ı� �������	
	RollType_Inverted_Center_Left	= 7,//���ҵ����ȡ�ַ��� �����ı� �������
	
	RollType_Order_Right					= 8,//�����һ�ȡ�ַ��� �ı������ƶ�
	RollType_Inverted_Right				= 9,//���ҵ����ȡ�ַ��� �ı������ƶ�
	RollType_Order_Center_Right		= 10,//�����һ�ȡ�ַ��� �����ı� �������
	RollType_Inverted_Center_Right=	11,//���ҵ����ȡ�ַ��� �����ı� �������	
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
	short wordSpace;//�ʼ��		
	unsigned short x;//�ı���X����
	unsigned short y;//�ı���Y����
	unsigned short x_end;//�ı����������
	unsigned short background;//����ɫ
	unsigned short foreground;//ǰ��ɫ
	short BitmapTableLength;//�ַ���
	
	int BitmapTable[ROLL_TEXT_STRING_MAX_LENGTH];//�洢�ַ�����Ӧ���ֵ�����
	int BitmapCurrent[ROLL_TEXT_STRING_MAX_LENGTH];//�洢���뵽һ�����һ������������Դ��ַ
	unsigned char LastCode[ROLL_TEXT_STRING_MAX_LENGTH];//�洢��һ�ν���δ��ɲ��ֵı�������
		
	short StartIndex;//��ʼ��ʾ�ַ�λ��
	short SpaceGain;//�ո����� ���ƿո��С

	short char_x;
	short char_y;
	short char_end;
	unsigned short maxCharWidth;//�����ַ�������� ��������ո�
	unsigned short CharHeight;
	unsigned short half;
	unsigned short quartern;
	short firstwidth;
	
	unsigned short CopyLine;//������ ָ������һ�п�ʼ����
	unsigned short TargetLine;//Ŀ���� ָ�����Ƶ��Դ����һ��
	unsigned short DrawLine;//���λ�������
	unsigned short CopyCount;//�Ѹ����м���
	
	RollType_en type;
	
	void DrawRollCode(unsigned short* buffer, unsigned char type, unsigned char num);
	void DecodeRollTextAntiAliasing(unsigned short* videoMemory, short index, unsigned short drawLine, unsigned short targetLine, unsigned short charWidth);
	void DrawBackground(unsigned short* videoMemory, short width, unsigned short drawLine, unsigned short targetLine);
	
private:
};














#endif/*_DECODE_FONT_H_*/
