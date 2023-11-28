#ifndef _DECODE_LOCATE_H_
#define _DECODE_LOCATE_H_

#include "Decode_Port.h"

#define ROOT_SUBNODE_OFFSET		24
#define ROOT_FILE_OFFSET			28
#define TREE_COUNT			1

const unsigned int TreeRootAddressList[TREE_COUNT] = {0};

class DecodeLocate : protected DecodePort
{
public:
	DecodeLocate()
	{
		CurrentRootStartAddress = 0;	
	}
	
	~DecodeLocate()
	{
		
	}
	
	unsigned int GetFileAddress(const char* path);
	
protected:
													
private:
	int CompareRootName(unsigned int* source, unsigned int* target);
	int CompareFolderName(unsigned int* source, unsigned int address);
	int CompareFileName(unsigned int* source, unsigned int address);
	unsigned int FindTargetFolder(unsigned int* source, unsigned int address);
	unsigned int FindTargetFile(unsigned int* source, unsigned int address);

	int CurrentRootStartAddress;
};






#endif /* _DECODE_LOCATE_H_ */
