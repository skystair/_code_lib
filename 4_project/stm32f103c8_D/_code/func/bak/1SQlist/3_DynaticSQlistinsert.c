#include "DataStruct.h"


unsigned int EleminitSize;
//元素
Elemtype ElemData0;
////表
SQlist	SQlist0;
////返回表元素
//Elemtype EreturnValue;
////位置号
//unsigned int ElemPosition;



void InitList(SQlist *SQlistX);									//初始化表
void DestroyList(SQlist *SQlistX);								//删除表

void IncreaseList(SQlist *SQlistX, unsigned int IncreaseSize);

bool ListInsert(SQlist *SQlistX ,unsigned int i ,Elemtype e);	//插入元素
void ListDelete(SQlist *SQlistX ,unsigned int i ,Elemtype *e);	//删除元素

unsigned int LocateElem(SQlist *SQlistX ,Elemtype e);			//按值查找位置
Elemtype GetElem(SQlist *SQlistX ,unsigned int i);				//按位置查找值

unsigned int LengthofList(SQlist *SQlistX);						//表长度
void PrintList(SQlist *SQlistX);
bool IsListEmpty(SQlist *SQlistX);

void ElemListfunc(void);

//=========================================================================
void InitList(SQlist *SQlistX){
	//静态表
//	memset(SQlistX , 1 ,ELEM_SINGLE_SIZE * ELEM_MAX_SIZE);
//	SQlistX -> length  = 0;
	//动态表
	EleminitSize = 10;

	SQlistX->data = (Elemtype *)malloc(ELEM_SINGLE_SIZE *EleminitSize);
	memset(SQlistX->data , 0 ,ELEM_SINGLE_SIZE * EleminitSize);	//新空间清0
	
	SQlistX->length = 0;
	SQlistX->MaxSize = EleminitSize;
}
void DestroyList(SQlist *SQlistX){
	free(SQlistX->data);
}

void IncreaseList(SQlist *SQlistX, unsigned int IncreaseSize){
	unsigned int tmpSize = SQlistX->MaxSize + IncreaseSize;
	Elemtype *P = SQlistX->data;
	
	SQlistX->data = (Elemtype *)malloc(ELEM_SINGLE_SIZE *tmpSize);
	memset(SQlistX->data , 0 ,ELEM_SINGLE_SIZE * tmpSize);	//新空间清0
	
	for(unsigned int i = 0;i < SQlistX->MaxSize ;i++){
		SQlistX->data[i] = P[i];
	}
	SQlistX->MaxSize = tmpSize;
	free(P);
}

bool ListInsert(SQlist *SQlistX ,unsigned int i ,Elemtype e){
	Elemtype tmp1,tmp2;
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

void ElemListfunc(void){
	bool Result;
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
	printf("\nListintsert = %d;\n",(unsigned char)Result);	
	//输出
	for(unsigned int i = 0; i < SQlist0.length; i++){
		printf("ListElement[%d] = %d \n",i , SQlist0.data[i]);
	}
	printf("\nListPrint complete;\n");	
	
	DestroyList(&SQlist0);
	
}