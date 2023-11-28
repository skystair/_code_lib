#include "Decode_Memory.h"

#define Decode_Memory_Get_Next(target) reinterpret_cast<BlockEnrty_t*>(&(&target->data)[target->length])

BlockEnrty_t* Decode_Memory::GetNetFreeBlockEnrty(BlockEnrty_t* entry)
{
	if(reinterpret_cast<unsigned int>(entry) >= reinterpret_cast<unsigned int>(EndOfBuffer))
	{
		entry =  reinterpret_cast<BlockEnrty_t*>(0);
	}
	else
	{
		while(entry->used)
		{
			entry = Decode_Memory_Get_Next(entry);
			if(reinterpret_cast<unsigned int>(entry) >= reinterpret_cast<unsigned int>(EndOfBuffer))
			{//超过管理范围
				entry =  reinterpret_cast<BlockEnrty_t*>(0);
				break;
			}
		}
	}

	return entry;
}

void* Decode_Memory::TryMalloc(BlockEnrty_t* target, unsigned int size)
{
	void* result = reinterpret_cast<void*>(0);
	if(target->length > size)
	{//剩余空间充足	
		result = reinterpret_cast<void*>(&target->data);
		unsigned int length = target->length;
		target->length = size;
		target->used = 1;		
		BlockEnrty_t* next = Decode_Memory_Get_Next(target);
		if(reinterpret_cast<unsigned int>(next) < reinterpret_cast<unsigned int>(EndOfBuffer))
		{//缓存空间未完全用完
			next->used = 0;
			next->length = length - size - sizeof(unsigned int);
			NextFree = next;
		}
	}
	return result;
}

void* Decode_Memory::Malloc(unsigned int size)
{
	void* result = reinterpret_cast<void*>(0);
	if(size&3)//四字节对齐
	{
		size += (4-size&3);
	}
	BlockEnrty_t* target = GetNetFreeBlockEnrty(Root);
	
	while(target)
	{
		result = TryMalloc(target, size);	
		if(result)
		{//成功分配到存储空间
			Residue -= size + sizeof(unsigned int);
			break;
		}
		target = GetNetFreeBlockEnrty(target);
	}
	
	return result;
}

void* Decode_Memory::MallocFast(unsigned int size)
{
	void* result = reinterpret_cast<void*>(0);
	if(size&3)//四字节对齐
	{
		size += (4-size&3);
	}
	if(NextFree->length > size)
	{//剩余空间充足	
		Residue -= size + sizeof(unsigned int);
		result = reinterpret_cast<void*>(&NextFree->data);
		unsigned int length = NextFree->length;
		NextFree->length = size;
		NextFree->used = 1;		
		BlockEnrty_t* next = Decode_Memory_Get_Next(NextFree);
		NextFree = next;
		next->used = 0;
		if(reinterpret_cast<unsigned int>(next) < reinterpret_cast<unsigned int>(EndOfBuffer))
		{//缓存空间未完全用完
			next->length = length - size - sizeof(unsigned int);
		}
		else
		{
			next->length = 0;
		}
	}
	return result;
}

void Decode_Memory::Free(void* address)
{
	if(reinterpret_cast<unsigned int>(address) >= reinterpret_cast<unsigned int>(Root) 
		&& reinterpret_cast<unsigned int>(address) < reinterpret_cast<unsigned int>(EndOfBuffer))
	{//需要释放的内存在管理空间内
		BlockEnrty_t* target = reinterpret_cast<BlockEnrty_t*>(reinterpret_cast<unsigned int>(address)-sizeof(unsigned int));
		Residue += target->length + sizeof(unsigned int);
		target->used = 0;		
		unsigned int length = target->length;
		BlockEnrty_t* next = Decode_Memory_Get_Next(target);	
		while(next->used == 0)
		{//连接其后的空闲块	
			length += next->length + sizeof(unsigned int);
			if(reinterpret_cast<unsigned int>(next) + next->length + 4 >= reinterpret_cast<unsigned int>(EndOfBuffer))
			{
				break;
			}
			next = Decode_Memory_Get_Next(next);
		}
		target->length = length;
		if(++FreeCount > DECODE_MEMORY_FREE_BLOCK_TRIM)
		{//当释放次数达到设置值后进行一次全局空白空间合并
			target = GetNetFreeBlockEnrty(Root);//从Root开始寻找空闲块
			while(target)
			{
				length = target->length;
				next = Decode_Memory_Get_Next(target);//获得其后的块
				while(next->used == 0)//用来启用最开始的空白块融合
				{//空白块后还是空白块	
					length += next->length + sizeof(unsigned int);		
					if(reinterpret_cast<unsigned int>(next) + next->length + 4 >= reinterpret_cast<unsigned int>(EndOfBuffer))
					{//已经到达管理区域结尾
						target->length = length;//合并已发现的空白块
						break;
					}
					next = Decode_Memory_Get_Next(next);//获得其后的块
					if(next->used)
					{//下一块是正在使用块
						target->length = length;//合并已发现的空白块
						break;
					}
				}
				target = GetNetFreeBlockEnrty(Decode_Memory_Get_Next(target));
			}

			
		}
	}
}

void Decode_Memory::FreeAll(void)
{
	Residue = DECODE_MODULE_BUFFER_SIZE - sizeof(unsigned int);
	Root->length = Residue;
	Root->used = 0;
	NextFree = Root;
	FreeCount = 0;
}
