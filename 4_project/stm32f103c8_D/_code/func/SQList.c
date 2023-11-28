#include "SQList.h"


unsigned int EleminitSize;
//元素
ElemtypeSQ ElemData0;
////表
SQlist	SQlist0;
////返回表元素
//ElemtypeSQ EreturnValue;
////位置号
//unsigned int ElemPosition;



void InitList(SQlist *SQlistX);									//1.初始化表
void DestroyList(SQlist *SQlistX);								//2.删除表

void IncreaseList(SQlist *SQlistX, unsigned int IncreaseSize);	//3.扩容表

bool ListInsert(SQlist *SQlistX ,unsigned int i ,ElemtypeSQ e);	//4.插入元素
bool ListDelete(SQlist *SQlistX ,unsigned int i ,ElemtypeSQ *e);	//5.删除元素

unsigned int LocateElem(SQlist *SQlistX ,ElemtypeSQ e);			//6.按值查找位置
ElemtypeSQ GetElem(SQlist *SQlistX ,unsigned int i);				//7.按位置查找值

unsigned int LengthofList(SQlist *SQlistX);						//8.表长度
void PrintList(SQlist *SQlistX);								//9.
bool IsListEmpty(SQlist *SQlistX);								//10.

void ElemListfunc(void);

//1=========================================================================
void InitList(SQlist *SQlistX){
	//静态表
//	memset(SQlistX , 1 ,SQ_ELEM_SINGLE_SIZE * ELEM_MAX_SIZE);
//	SQlistX -> length  = 0;
	//动态表
	EleminitSize = 10;

	SQlistX->data = (ElemtypeSQ *)malloc(SQ_ELEM_SINGLE_SIZE *EleminitSize);
	memset(SQlistX->data , 0 ,SQ_ELEM_SINGLE_SIZE * EleminitSize);	//新空间清0
	
	SQlistX->length = 0;
	SQlistX->MaxSize = EleminitSize;
}
//2=========================================================================
void DestroyList(SQlist *SQlistX){
	free(SQlistX->data);
}
//3=========================================================================
void IncreaseList(SQlist *SQlistX, unsigned int IncreaseSize){
	unsigned int tmpSize = SQlistX->MaxSize + IncreaseSize;
	ElemtypeSQ *P = SQlistX->data;
	
	SQlistX->data = (ElemtypeSQ *)malloc(SQ_ELEM_SINGLE_SIZE *tmpSize);
	memset(SQlistX->data , 0 ,SQ_ELEM_SINGLE_SIZE * tmpSize);	//新空间清0
	
	for(unsigned int i = 0;i < SQlistX->MaxSize ;i++){
		SQlistX->data[i] = P[i];
	}
	SQlistX->MaxSize = tmpSize;
	free(P);
}
//4=========================================================================
bool ListInsert(SQlist *SQlistX ,unsigned int i ,ElemtypeSQ e){
	ElemtypeSQ tmp1,tmp2;
	if(i > SQlistX->length){
		return false;
	}
	if(SQlistX->length >= SQlistX->MaxSize){
		//IncreaseList(SQlistX, 1);
		return false;
	}
//	tmp1 = e;
//	for(unsigned int j = i;j<= SQlistX->length; j++){
//		tmp2 = SQlistX->data[j];
//		SQlistX->data[j] = tmp1;
//		tmp1 = tmp2;
//	}
	for(unsigned int j = SQlistX->length;j>i ; j--){
		SQlistX->data[j] = SQlistX->data[j-1];
	}
	SQlistX->data[i] = e;
	
	SQlistX->length++;
//	SQlistX->data[i] = e;
	return true;
}
//5=========================================================================
bool ListDelete(SQlist *SQlistX ,unsigned int i ,ElemtypeSQ *e){
	if(i >= SQlistX->length){
		return false;
	}
	*e = SQlistX->data[i];
	for(unsigned int j = i; j < SQlistX->length-1; j++){
		SQlistX->data[j] = SQlistX->data[j+1];
	}
	SQlistX->length--;
	return true;
}
//6=========================================================================
unsigned int LocateElem(SQlist *SQlistX ,ElemtypeSQ e){
	unsigned int i;
	for(i = 0; i< SQlistX->length;i++){
		if(SQlistX->data[i] == e){
			break;
		}
	}
	if(i >= SQlistX->length){
		return 777;
	}
	return i;
}
//7=========================================================================
ElemtypeSQ GetElem(SQlist *SQlistX ,unsigned int i){
	if(i < SQlistX->length){
		return SQlistX->data[i];
	}
	return 0;
}
//8=========================================================================
unsigned int LengthofList(SQlist *SQlistX){
	return SQlistX->length;
}
//9=========================================================================
void PrintList(SQlist *SQlistX){
	for(unsigned int i = 0; i < SQlist0.length; i++){
		printf("ListElement[%d] = %d \n",i , SQlist0.data[i]);
	}
}
bool Result;
ElemtypeSQ Returnvalue;
void SQListfunc(void){
	
	
	//初始化
	InitList(&SQlist0);
	printf("Listinit complete;\n\n");	
	//赋值
	for(unsigned int i = 0;i < SQlist0.MaxSize ;i++){
		SQlist0.data[i] = i;
		SQlist0.length++;
	}
	//扩容
	IncreaseList(&SQlist0,5);
	printf("Listincrease complete;\n\n");	
	//赋值
	for(unsigned int i = SQlist0.length;i < SQlist0.MaxSize ;i++){
		SQlist0.data[i] = i;
		SQlist0.length++;
	}
	SQlist0.length--;
	//插入
	Result = ListInsert(&SQlist0,9,77);
	printf("ListIntsert = %d;\n",(unsigned char)Result);	
	//删除
	Result = ListDelete(&SQlist0,8,&Returnvalue);
	printf("ListDelete = %d;\n",(unsigned char)Result);
	//查找
	Returnvalue = GetElem(&SQlist0,8);
	Returnvalue = LocateElem(&SQlist0,8);
	//输出
	PrintList(&SQlist0);
	printf("\nListPrint complete;\n");	
	
	DestroyList(&SQlist0);
	
}