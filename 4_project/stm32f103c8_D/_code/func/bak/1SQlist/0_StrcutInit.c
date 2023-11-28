#include "DataStruct.h"

////表
//SQlist	SQlist0;
////返回表元素
//Elemtype EreturnValue;
////位置号
//unsigned int ElemPosition;



void InitList(SQlist *SQlistX);									//初始化表
void DestroyList(SQlist *SQlistX);								//删除表

void ListInsert(SQlist *SQlistX ,unsigned int i ,Elemtype e);		//插入元素
void ListDelete(SQlist *SQlistX ,unsigned int i ,Elemtype *e);	//删除元素

unsigned int LocateElem(SQlist *SQlistX ,Elemtype e);				//按值查找位置
Elemtype GetElem(SQlist *SQlistX ,unsigned int i);				//按位置查找值

unsigned int LengthofList(SQlist *SQlistX);						//
void PrintList(SQlist *SQlistX);
bool IsListEmpty(SQlist *SQlistX);



void InitList(SQlist *SQlistX){
	
}

void DestroyList(SQlist *SQlistX){
	
}

