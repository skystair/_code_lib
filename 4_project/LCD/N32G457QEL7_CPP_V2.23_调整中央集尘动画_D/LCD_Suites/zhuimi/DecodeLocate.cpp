#include "DecodeLocate.h"

int DecodeLocate::CompareRootName(unsigned int* source, unsigned int* target)
{
	for(int i=0; i<2; i++)
	{
		if(source[i] > target[i])
		{
			return 1;
		}
		else if(source[i] < target[i])
		{
			return -1;
		}
	}
	return 0;
}

int DecodeLocate::CompareFolderName(unsigned int* source, unsigned int address)
{
	unsigned int target;
	for(int i=0; i<2; i++)
	{
		target = ReadWordImmediately(address);
		if(source[i] > target)
		{
			return 1;
		}
		else if(source[i] < target)
		{
			return -1;
		}
		address += 4;
	}
	return 0;
}

int DecodeLocate::CompareFileName(unsigned int* source, unsigned int address)
{
	unsigned int target;
	for(int i=0; i<3; i++)
	{
		target = ReadWordImmediately(address);
		if(source[i] > target)
		{
			return 1;
		}
		else if(source[i] < target)
		{
			return -1;
		}
		address += 4;
	}
	return 0;
}

unsigned int DecodeLocate::FindTargetFolder(unsigned int* source, unsigned int address)
{
	int result = CompareFolderName(source, address);
	if(result > 0)
	{//向右
		address = ReadWordImmediately(address + 12);
		if(address == 0)
		{//没有右节点
			return 0;
		}
		address += CurrentRootStartAddress;
		address = FindTargetFolder(source, address);
	}
	else if(result < 0)
	{//向左
		address = ReadWordImmediately(address + 8);
		if(address == 0)
		{//没有左节点
			return 0;
		}
		address += CurrentRootStartAddress;
		address = FindTargetFolder(source, address);
	}
	return address;
}

unsigned int DecodeLocate::FindTargetFile(unsigned int* source, unsigned int address)
{
	int result = CompareFileName(source, address);
	if(result > 0)
	{//向右
		address = ReadWordImmediately(address + 16);
		if(address == 0)
		{//没有右节点
			return 0;
		}
		address += CurrentRootStartAddress;
		address = FindTargetFile(source, address);
	}
	else if(result < 0)
	{//向左
		address = ReadWordImmediately(address + 12);
		if(address == 0)
		{//没有左节点
			return 0;
		}
		address += CurrentRootStartAddress;
		address = FindTargetFile(source, address);
	}
	return address;
}

unsigned int DecodeLocate::GetFileAddress(const char* path)
{
	unsigned int source[3];
	unsigned char* p = (unsigned char*)source;
	unsigned int address;
	if(*path != '\\')
	{//不是标准的路径
		return 0;
	}
	/* 选择树 */
	source[0] = 0;
	source[1] = 0;
	source[2] = 0;
	for(int i=0; i<12; i++)
	{
		path++;
		if(*path == '\\')
		{//获取到文件夹名
			break;
		}
		if(*path == '\0')
		{//获取到文件名
			return 0;//第一节必须是树名，出现文件名，输入路径错误
		}
		p[i] = *path;		
	}
	
	CurrentRootStartAddress = 0xFFFFFFFF;
	for(int i=0; i<TREE_COUNT; i++)
	{
		CurrentRootStartAddress = TreeRootAddressList[i];
		if(CompareFolderName(source, CurrentRootStartAddress) == 0)
		{
			break;
		}
	}
	if(CurrentRootStartAddress == 0xFFFFFFFF)
	{//没有找到树
		return 0;
	}
	/* 根节点 文件夹或文件列表 */
	source[0] = 0;
	source[1] = 0;
	source[2] = 0;
	for(int i=0; i<12; i++)
	{
		path++;
		if(*path == '\\')
		{//获取到文件夹名
			address = CurrentRootStartAddress + ReadWordImmediately(ROOT_SUBNODE_OFFSET);
			break;
		}
		if(*path == '\0')
		{//获取到文件名
			address = CurrentRootStartAddress + ReadWordImmediately(ROOT_FILE_OFFSET);		
			address = FindTargetFile(source, address);
			return CurrentRootStartAddress + ReadWordImmediately(address + 20);
		}
		p[i] = *path;		
	}
	if(address == 0)
	{//没有根文件夹节点或根文件节点
		return 0;
	}
	address = FindTargetFolder(source, address);
	if(address == 0)
	{//没有找到 结束查找
		return 0;
	}
	
	/* 后续所有 */
	while(1)
	{	
		source[0] = 0;
		source[1] = 0;
		source[2] = 0;
		for(int i=0; i<12; i++)
		{
			path++;
			if(*path == '\\')
			{//获取到文件夹名
				address = CurrentRootStartAddress + ReadWordImmediately(address + 16);
				address = FindTargetFolder(source, address);
				break;
			}
			if(*path == '\0')
			{//获取到文件名
				address = CurrentRootStartAddress + ReadWordImmediately(address + 20);
				address = FindTargetFile(source, address);
				return CurrentRootStartAddress + ReadWordImmediately(address + 20);
			}
			p[i] = *path;		
		}
	}
}







