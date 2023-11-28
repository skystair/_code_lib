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
			{//��������Χ
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
	{//ʣ��ռ����	
		result = reinterpret_cast<void*>(&target->data);
		unsigned int length = target->length;
		target->length = size;
		target->used = 1;		
		BlockEnrty_t* next = Decode_Memory_Get_Next(target);
		if(reinterpret_cast<unsigned int>(next) < reinterpret_cast<unsigned int>(EndOfBuffer))
		{//����ռ�δ��ȫ����
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
	if(size&3)//���ֽڶ���
	{
		size += (4-size&3);
	}
	BlockEnrty_t* target = GetNetFreeBlockEnrty(Root);
	
	while(target)
	{
		result = TryMalloc(target, size);	
		if(result)
		{//�ɹ����䵽�洢�ռ�
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
	if(size&3)//���ֽڶ���
	{
		size += (4-size&3);
	}
	if(NextFree->length > size)
	{//ʣ��ռ����	
		Residue -= size + sizeof(unsigned int);
		result = reinterpret_cast<void*>(&NextFree->data);
		unsigned int length = NextFree->length;
		NextFree->length = size;
		NextFree->used = 1;		
		BlockEnrty_t* next = Decode_Memory_Get_Next(NextFree);
		NextFree = next;
		next->used = 0;
		if(reinterpret_cast<unsigned int>(next) < reinterpret_cast<unsigned int>(EndOfBuffer))
		{//����ռ�δ��ȫ����
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
	{//��Ҫ�ͷŵ��ڴ��ڹ���ռ���
		BlockEnrty_t* target = reinterpret_cast<BlockEnrty_t*>(reinterpret_cast<unsigned int>(address)-sizeof(unsigned int));
		Residue += target->length + sizeof(unsigned int);
		target->used = 0;		
		unsigned int length = target->length;
		BlockEnrty_t* next = Decode_Memory_Get_Next(target);	
		while(next->used == 0)
		{//�������Ŀ��п�	
			length += next->length + sizeof(unsigned int);
			if(reinterpret_cast<unsigned int>(next) + next->length + 4 >= reinterpret_cast<unsigned int>(EndOfBuffer))
			{
				break;
			}
			next = Decode_Memory_Get_Next(next);
		}
		target->length = length;
		if(++FreeCount > DECODE_MEMORY_FREE_BLOCK_TRIM)
		{//���ͷŴ����ﵽ����ֵ�����һ��ȫ�ֿհ׿ռ�ϲ�
			target = GetNetFreeBlockEnrty(Root);//��Root��ʼѰ�ҿ��п�
			while(target)
			{
				length = target->length;
				next = Decode_Memory_Get_Next(target);//������Ŀ�
				while(next->used == 0)//���������ʼ�Ŀհ׿��ں�
				{//�հ׿���ǿհ׿�	
					length += next->length + sizeof(unsigned int);		
					if(reinterpret_cast<unsigned int>(next) + next->length + 4 >= reinterpret_cast<unsigned int>(EndOfBuffer))
					{//�Ѿ�������������β
						target->length = length;//�ϲ��ѷ��ֵĿհ׿�
						break;
					}
					next = Decode_Memory_Get_Next(next);//������Ŀ�
					if(next->used)
					{//��һ��������ʹ�ÿ�
						target->length = length;//�ϲ��ѷ��ֵĿհ׿�
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
