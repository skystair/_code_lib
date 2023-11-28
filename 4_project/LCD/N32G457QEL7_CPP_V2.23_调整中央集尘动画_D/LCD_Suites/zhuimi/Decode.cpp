#include "Decode.h"

/**********************初始化部分******************************************/
DecodeNodeBase* Decode::Root = reinterpret_cast<DecodeNodeBase*>(0);
DecodeNodeBase* Decode::Current = reinterpret_cast<DecodeNodeBase*>(0);
DecodeNodeBase* Decode::DmaCurrent = reinterpret_cast<DecodeNodeBase*>(0);

/************************************字库在接口类中的实现部分******************************************/

void Decode::CreatText(void)
{
	IDecodeText* node = new DecodeSingleText;
	if(!Text)
	{
		Text = node;
	}
	else
	{
		IDecodeText* target = Text;
		while(target->next)
		{
			target = target->next;
		}
		target->next = node;
	}
}

void Decode::CreatText(char line)
{
	IDecodeText* node = new DecodeMultiLineText(line);
	if(!Text)
	{
		Text = node;
	}
	else
	{
		IDecodeText* target = Text;
		while(target->next)
		{
			target = target->next;
		}
		target->next = node;
	}
}

IDecodeText& Decode::GetText(int index)
{
	IDecodeText* target = Text;
	for(int i=0; i<index; i++)
	{
		if(target->next)
		{
			target = target->next;
		}
	}
	return *target;
}

void Decode::SleepAll()
{
	IDecodeText* target = Text;
	while(target)
	{
		target->sleep = true;
		target->pause = false;
		target = target->next;
	}
}

/**************************************图片在接口类中的实现部分********************************************/
void Decode::CleanDrawList(void)
{
	Memory->FreeAll();
	Root = reinterpret_cast<DecodeNodeBase*>(0);
	Current = Root;
}

void Decode::RegisterPicture(short x, short y, const char* path)
{
	unsigned short width,height,blockHeight;
	int BlockSize;
	unsigned int address = GetFileAddress(path);
	if(address == 0)
	{
		return;
	}
	
	CreatFlashReader(address);//开始传输
	GetHalfWord();//丢弃文件标志
	width = GetHalfWord();//读取图片宽度
	height = GetHalfWord();//读取图片高度
	blockHeight = GetHalfWord();//读取行数
	BlockSize = GetWord();//读取BlockSize
	CloseFlashReader();	
	DecodeNodeBase* node = reinterpret_cast<DecodeNodeBase*>(Memory->MallocFast(BlockSize + sizeof(DecodePictureNode)));
	if(node)
	{//内存分配成功
		node->next = reinterpret_cast<DecodeNodeBase*>(0);
		node->type = DecodeNodeType_Picture;
		node->draw = false;//设置为未开始绘制
		node->DmaBusy = false;//设置为未开始传输
		if(Root)
		{
			Current->next = node;//将新建节点注册到链表结尾
			Current = node;//将当前节点指向新建节点
		}
		else
		{
			Root = node;	
			Current = node;
		}
		DecodePictureNode* p_node = reinterpret_cast<DecodePictureNode*>(node);
		p_node->address = address + 12;
		p_node->x = x;
		p_node->y = y;
		p_node->width = width;
		p_node->height = height;
		p_node->blockHeight =blockHeight;
		p_node->blocksize = static_cast<unsigned short>(BlockSize);
		p_node->DecodePoint = &p_node->buffer;//解码指针指向解码缓存开始位置
		p_node->LastData = 0;
	}
}

void Decode::CleanTargetVideoMemory(unsigned short * target)
{
#if((BLOCK_DECODED_SIZE&1) == 0)
	unsigned int* w_target = reinterpret_cast<unsigned int*>(target);
	for(int i=0; i<(BLOCK_DECODED_SIZE>>1); i++)
	{
		w_target[i] = 0;
	}
#else
	
	for(int i=0; i<BLOCK_DECODED_SIZE; i++)
	{
		target[i] = 0;
	}
#endif
}

void Decode::DrawPicture(DecodePictureNode& node)
{
	unsigned short buff_y_start = node.line*DECODE_BUFFER_HEIGHT;
	unsigned short buff_y_end = buff_y_start + DECODE_BUFFER_HEIGHT;
	if(node.draw)
	{//已开始绘制 判断是否在本次绘制完成
		unsigned short pic_y_end = node.y + node.height;
		if(pic_y_end <= buff_y_start || buff_y_end < node.y)
		{//绘制已结束 或 绘制未开始
			node.draw = false;
			node.DrawLine = 0;
		}
		else
		{//继续绘制 
			//计算本次图片绘制到显存的起始行
			node.TargetLine = 0;
			
			//计算本次绘制行数
			unsigned short toPicEnd = pic_y_end - buff_y_start;
			node.DrawLine = toPicEnd>DECODE_BUFFER_HEIGHT?DECODE_BUFFER_HEIGHT:toPicEnd;//显存位置到图片结尾高度与显存高度的最小值
		}
	}
	else
	{//未开始绘制 判断是否从本次开始绘制
		if(node.y >=  buff_y_start && node.y < buff_y_end)//
		{
			node.draw = true;//标记为开始绘制
			node.lastExtra = 0;
			
			//计算从解码缓存开始复制的行号
			node.CopyLine = 0;//首次复制从第一行开始 每次DMA传输结束后自增（DMA每次传输一行）
			
			//计算本次图片绘制到显存的起始行
			node.TargetLine = node.y - buff_y_start;
			
			//计算本次绘制行数
			unsigned short toBuffEnd = buff_y_end - node.y;	
			node.DrawLine = toBuffEnd>node.height?node.height:toBuffEnd;//图片到当前缓存结尾和图片高度的最小值	
		}
		else if(buff_y_start == 0 && node.y < 0)//仅绘制第一块时需要判断
		{//异常开始情况 图片开始位置在屏幕外
			unsigned short pic_y_end = node.y + node.height;
			if(pic_y_end > 0)
			{//图片你必须有部分在屏幕内 否则不绘制
				node.draw = true;//标记为开始绘制
				node.lastExtra = 0;
				
				//计算从解码缓存开始复制的行号
				node.CopyLine = -node.y;//首次复制从第一行开始 每次DMA传输结束后自增（DMA每次传输一行）
				
				//计算本次图片绘制到显存的起始行
				node.TargetLine = 0;
				
				//计算本次绘制行数
				unsigned short toPicEnd = node.height + node.y;	
				node.DrawLine = toPicEnd>DECODE_BUFFER_HEIGHT?DECODE_BUFFER_HEIGHT:toPicEnd;//图片到当前缓存结尾和图片高度的最小值	
			}
		}
		else
		{
			node.DrawLine = 0;
		}
	}
	//向解码缓存中解码
	if(node.draw)
	{
		CreatFlashReader(node.address);//开始传输
		int drawPixel = node.DrawLine * node.width;// + node.lastExtra;
		
		DecodeState state = DecodeState_OK;
		while(state == DecodeState_OK)//本次解码像素限制未结束或正常解码继续 drawPixel > 0 && 
		{
			unsigned short in;
			unsigned short newdata;
			if(node.LastData)
			{
				in = node.LastData;
				node.LastData = 0;
				newdata = 0;
			}
			else
			{
				in = GetHalfWord();
				newdata = 1;
			}
			
			state = Step(in, newdata, drawPixel, node);
		}
		CloseFlashReader();
		
		node.lastExtra = drawPixel;
		
		//将解码数据叠加到显存	
		unsigned int targetColumn;
		unsigned int sourceIndex;	
		unsigned int halfWordSize = node.width;
		if(node.x < 0)
		{
			targetColumn = 0;
			sourceIndex = node.CopyLine * node.width - node.x;
			halfWordSize += node.x;
			if(halfWordSize > SCREEN_PIXEL_WIDTH)
			{
				halfWordSize = SCREEN_PIXEL_WIDTH;
			}
		}
		else
		{
			targetColumn = node.x << 1;
			sourceIndex = node.CopyLine * node.width;
			if(halfWordSize > SCREEN_PIXEL_WIDTH - node.x)
			{
				halfWordSize = SCREEN_PIXEL_WIDTH - node.x;
			}
		}
		while(DmaCurrent->DmaBusy);
		unsigned int targetAddress = reinterpret_cast<unsigned int>(node.videoMemory) + (node.TargetLine * SCREEN_BYTE_WIDTH) + targetColumn;
		unsigned int sourceAddress = reinterpret_cast<unsigned int>(&node.buffer) + (sourceIndex << 1);
		node.CopyCount = 0;
		DmaCurrent = Current;
		node.DmaBusy = true;
		StartMemDma(sourceAddress, targetAddress, halfWordSize);		
	}
}

void Decode::RefreshScreen(void)
{
	IDecodeText* targetText = Text;
	while(targetText)
	{
		targetText->ReadyToDraw();	
		targetText = targetText->next;
	}
	
	for(int line=0; line<SCREEN_REFRESH_LOOP; line++)
	{//按显存高度刷新屏幕 line&1 选择显存
		unsigned short *TargetVideoMemory = VideoMemory[line&1];//指定当前显存
		CleanTargetVideoMemory(TargetVideoMemory);//清空当前显存
		
		Current = Root;
		DecodeNodeBase* Last;
		//绘制所有图片位于当前显存位置的部分
		if(Current)
		{
			while(Current)
			{				
				switch(Current->type)
				{
					case DecodeNodeType_Picture:
						Current->line = line;
						Current->videoMemory = TargetVideoMemory;
						DrawPicture(*reinterpret_cast<DecodePictureNode*>(Current));
						break;
					
					default:
						break;
				}
				Last = Current;
				Current = Current->next;
			}
			
			while(Last->DmaBusy);
		}
			
		//字库解码直接写入显存 使用缓存解码消耗内存过大 远超过图片解码
		IDecodeText* targetText = Text;
		while(targetText)
		{
			//每个文本框仅有两个缓存 缓存大小=最大字符宽度*字符高度*2 字符串开始输出时申请，输出结束后释放
			//targetText->maxCharWidth * targetText->CharHeight * 2
			
			targetText->DrawText(TargetVideoMemory, line);
			if(line >= (SCREEN_REFRESH_LOOP-1))
			{
				targetText->RollText();
			}
			targetText = targetText->next;
		}
		
		//将当前显存通过不阻塞的DMA输出到屏幕
		unsigned short y = line*DECODE_BUFFER_HEIGHT;
		Decode_DrawPicture(0, y, SCREEN_PIXEL_WIDTH, y+DECODE_BUFFER_HEIGHT, TargetVideoMemory);
	}
	//清除绘制树 每个绘制树仅维持到绘制完成
	CleanDrawList();
}

/**********************************************************************************************************/
DecodeNodeBase* DmaCurrentNode;
inline void SetNextCopyStep(DecodePictureNode& node)
{
	if(++node.CopyLine >= node.blockHeight)
	{
		node.CopyLine = 0;
	}
	if(++node.CopyCount < node.DrawLine)
	{
		node.TargetLine++;
		unsigned int targetColumn;
		unsigned int sourceIndex;	
		unsigned int halfWordSize = node.width;
		if(node.x < 0)
		{
			targetColumn = 0;
			sourceIndex = node.CopyLine * node.width - node.x;
			halfWordSize += node.x;
			if(halfWordSize > SCREEN_PIXEL_WIDTH)
			{
				halfWordSize = SCREEN_PIXEL_WIDTH;
			}
		}
		else
		{
			targetColumn = node.x << 1;
			sourceIndex = node.CopyLine * node.width;
			if(halfWordSize > SCREEN_PIXEL_WIDTH - node.x)
			{
				halfWordSize = SCREEN_PIXEL_WIDTH - node.x;
			}
		}
		
		unsigned int targetAddress = reinterpret_cast<unsigned int>(node.videoMemory) + (node.TargetLine * SCREEN_BYTE_WIDTH) + targetColumn;
		unsigned int sourceAddress = reinterpret_cast<unsigned int>(&node.buffer) + (sourceIndex << 1);
		
		Decode::StartMemDma(sourceAddress, targetAddress, halfWordSize);
		
		node.DmaBusy = true;
	}
	else
	{
		node.DmaBusy = false;
	}
}
void DmaCallback(void)
{
	switch(Decode::DmaCurrent->type)
	{
		case DecodeNodeType_Picture:
			SetNextCopyStep(*reinterpret_cast<DecodePictureNode*>(Decode::DmaCurrent));		
			break;
		
		default:
			break;
	}
}

DecodeState Decode::Step(unsigned short in, unsigned short newdata, int &drawPixel, DecodePictureNode& node)
{
	if(!newdata)
	{
		node.address -= 2;
	}
	if(in & 0x8000)
	{//直接复制源码
		short lenth = in & 0x7FFF;
		
		if(drawPixel - lenth < 0)
		{//即将超出本次解码限额		
			node.LastData = (lenth - drawPixel) | 0x8000;
			lenth = drawPixel;
		}
		GetLengData(reinterpret_cast<unsigned char*>(node.DecodePoint), lenth<<1);
		node.DecodePoint += lenth;
		drawPixel -= lenth;
		node.address += (lenth<<1) + 2;
	}
	else if(in)
	{//从已解码缓存中复制
		unsigned short offset = GetHalfWord();	
		if(!newdata)
		{
			offset += node.LastOffset;
		}
		else
		{
			node.LastOffset = 0;
		}
		if(drawPixel - in < 0)
		{//即将超出本次解码限额
			node.address -= 2;
			node.LastData = in - drawPixel;
			in = drawPixel;
			node.LastOffset += in;
		}		
		unsigned short* sourcePoint = &node.buffer;
		for(int i=0; i<in; i++)
		{
			node.DecodePoint[i] = sourcePoint[offset+i];
		}
		node.DecodePoint += in;
		drawPixel -= in;
		node.address += 4;
	}
	else
	{//块开始或结束
		node.DecodePoint = &node.buffer;//更新解码指针
		in = GetHalfWord();
		unsigned short newFlag = GetHalfWord();
		if(in==0&&newFlag==0)
		{//解码结束
			return DecodeState_End;
		}
		else
		{//新解码块起点
			if(drawPixel > 0)
			{
				*node.DecodePoint = in;
				node.DecodePoint += 1;
				drawPixel -= 1;
				node.address += 4;
				return Step(newFlag, 1, drawPixel, node);
			}
			else
			{
				return DecodeState_BlockEnd;
			}	
		}
	}
	if(drawPixel > 0)
	{
		return DecodeState_OK;
	}
	else
	{
		return DecodeState_BlockEnd;//不是解码的块 而是用于显示的块已经满了
	}
}






