#ifndef _DECODE_H_
#define _DECODE_H_

#include "DecodeLocate.h"
#include "Decode_Memory.h"

#include "DecodeSingleText.h"
#include "DecodeMultiLineText.h"

/***********************图片解码类型******************************/
enum DecodeNodeType_en
{
	DecodeNodeType_Picture,
};

class DecodeNodeBase
{
public:
	struct DecodeNodeBase* next;//节点链表
	int line;//记录当前循环指向位于哪一行
	unsigned short *videoMemory;//记录当前显存地址
	DecodeNodeType_en type;//扩展节点类型
	bool draw;//开始绘制标志
	bool DmaBusy;//是否正在使用DMA传输当前节点
	char R_Base;
};

struct DecodePictureNode: public DecodeNodeBase
{
public:
	unsigned int address;
	unsigned short* DecodePoint;//解码指针

	unsigned short CopyLine;//复制行 指定从哪一行开始复制
	unsigned short TargetLine;//目标行 指定复制到显存的哪一行
	unsigned short DrawLine;//本次绘制行数
	unsigned short CopyCount;//已复制行计数

	short x;
	short y;
	unsigned short width;
	unsigned short height;
	unsigned short blockHeight;
	unsigned short blocksize;
	short lastExtra;//上次解码额外写入到缓存的数据量
	unsigned short LastData;//上次解码剩余的数据
	unsigned short LastOffset;//上次复制偏移叠加
	unsigned short R;//预留对齐

//解码缓存开始标志 不要在这后面增加变量
	unsigned short buffer;//解码显存开始位置
};

/***********************对外类型*********************************/
void DmaCallback(void);
class Decode : protected DecodeLocate
{
public:
	friend void DmaCallback(void);//DMA相关友元
	friend void SetNextCopyStep(DecodePictureNode& node);//DMA相关友元
	Decode()
	{
		VideoMemory[0] = new unsigned short[BLOCK_DECODED_SIZE];//申请显存0
		VideoMemory[1] = new unsigned short[BLOCK_DECODED_SIZE];//申请显存1
		Memory = new Decode_Memory;//构造动态内存分配
		Root = reinterpret_cast<DecodeNodeBase*>(0);//设置图片解码链表根节点
		Current = Root;//设置图片解码链表当前节点
		Text = reinterpret_cast<IDecodeText*>(0);
		SetMemDmaCallback(DmaCallback);//设置DMA回调函数
	}
	
	~Decode()
	{
		delete VideoMemory[0];//释放显存0
		delete VideoMemory[1];//释放显存1
		delete Memory;//释放动态内存分配
	}
	
	/*图片相关部分*/
	void RegisterPicture(short x, short y, const char* path);//注册图片到绘制链表
	void RefreshScreen(void);//按照绘制链表绘制并输出图片到屏幕
	
	/*字库相关部分*/
	void CreatText(void);
	void CreatText(char line);
	IDecodeText& GetText(int index);
	void SleepAll();
	
protected:
	unsigned short *VideoMemory[2];
	Decode_Memory* Memory;

private:
	static DecodeNodeBase* Root;
	static DecodeNodeBase* Current;
	static DecodeNodeBase* DmaCurrent;
	IDecodeText* Text;
	

	/*图片相关部分*/
	void CleanDrawList(void);//清除图片绘制链表
	void CleanTargetVideoMemory(unsigned short * target);//擦除显存
	void DrawPicture(DecodePictureNode& node);//绘制图片节点
	DecodeState Step(unsigned short in, unsigned short newdata, int &drawPixel, DecodePictureNode& node);//图片单步解码

	/*字库相关部分*/
	

};



#endif/*_DECODE_H_*/
