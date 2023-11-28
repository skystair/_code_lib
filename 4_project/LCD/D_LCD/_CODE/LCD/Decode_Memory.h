#ifndef _DECODE_MEMORY_H_
#define _DECODE_MEMORY_H_

#include "Decode_Config.h"

#define DECODE_MEMORY_FREE_BLOCK_TRIM				15

struct BlockEnrty_t
{
	unsigned int length	:31;
	unsigned int used		:1;
	unsigned char data;
};

class Decode_Memory
{
public:
	Decode_Memory()
	{
		buffer = new char[DECODE_MODULE_BUFFER_SIZE];
		Root = reinterpret_cast<BlockEnrty_t*>(buffer);
		EndOfBuffer = reinterpret_cast<BlockEnrty_t*>(buffer + DECODE_MODULE_BUFFER_SIZE);
		NextFree = Root;
		Residue = DECODE_MODULE_BUFFER_SIZE - sizeof(unsigned int);
		Root->length = Residue;
		Root->used = 0;
		FreeCount = 0;	
	}

	~Decode_Memory()
	{
		delete buffer;
	}
	
	void* Malloc(unsigned int size);
	void* MallocFast(unsigned int size);
	void Free(void* address);
	void FreeAll(void);
	
private:
	char *buffer;
	BlockEnrty_t* Root;
	BlockEnrty_t* EndOfBuffer;
	BlockEnrty_t* NextFree;
	unsigned int Residue;//剩余存储容量
	unsigned char FreeCount;//单独释放次数计数

	BlockEnrty_t* GetNetFreeBlockEnrty(BlockEnrty_t* entry);
	void* TryMalloc(BlockEnrty_t* target, unsigned int size);
	
};




















#endif/*_DECODE_MEMORY_H_*/
