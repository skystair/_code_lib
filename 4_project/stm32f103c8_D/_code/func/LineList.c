#include "LineList.h"


//元素
ElemtypeL	LElemData0;
Lnode	*Lnode0;
////表
Llist		Llist0;
////返回表元素
//ElemtypeL EreturnValue;
////位置号
//unsigned int ElemPosition;

void LListInit(Llist *LlistX, unsigned int initSize);			//1.初始化表
void DestroyList(Llist *LlistX);								//2.删除表

void IncreaseList(Llist *LlistX, unsigned int IncreaseSize);	//3.扩容表

bool LListInsert(Llist *LlistX ,unsigned int i ,ElemtypeL e);		//4.插入元素
bool LListDelete(Llist *LlistX ,unsigned int i ,ElemtypeL *e);	//5.删除元素

unsigned int LocateElem(Llist *LlistX ,ElemtypeL e);				//6.按值查找位置
Lnode* LElemGet(Llist *LlistX ,unsigned int i);				//7.按位置查找值

unsigned int LengthofList(Llist *LlistX);						//8.表长度
void LListPrint(Llist *LlistX);									//9.
bool IsListEmpty(Llist *LlistX);								//10.

void LListPrint(Llist *LlistX){
	unsigned char i = 1;
	Lnode *headtmp = LlistX->head;
	while(LlistX->head != NULL){
		i++;
		printf("ListElement[%d] = %d \n",i , LlistX->head->data);
		LlistX->head = (Lnode *)LlistX->head->next;
	}
	LlistX->head = headtmp;
}
void LineListfunc(void);

//1=========================================================
void LListInit(Llist *LlistX, unsigned int initSize){
	if(initSize == 0){
		LlistX->head = NULL;
		return;
	}
	LlistX->head = (Lnode *)malloc(sizeof(Lnode));
	LlistX->tmppos = LlistX->head;
	
	LlistX->tmppos->data = 2;
	if(initSize == 1){
		LlistX->tmppos->next = NULL;
		return;
	}
	
	for(unsigned int i = 1; i < initSize ; i++){
		LlistX->tmppos->next = (struct Lnode *)malloc(sizeof(Lnode));
		LlistX->tmppos = (Lnode *)LlistX->tmppos->next;
		LlistX->tmppos->data = i+2;
	}
	
	LlistX->tmppos->next = NULL;
}
//x=========================================================
Lnode* LElemGet(Llist *LlistX ,unsigned int i){
	LlistX->tmppos = LlistX->head;
	while(i > 1){
		if(LlistX->tmppos == NULL){
			return false;
		}
		i--;
		LlistX->tmppos = (Lnode *)LlistX->tmppos->next;
	}
	return LlistX->tmppos;
}
//x=========================================================
bool LListInsert(Llist *LlistX ,unsigned int i ,ElemtypeL e){
	LlistX->tmppos = LlistX->head;
	if(i == 0){//位置超范围
		return false;
	}
	Lnode *tmpNode = (Lnode *)malloc(sizeof(Lnode));
	tmpNode->data = e;
	tmpNode->next = NULL;
	
	if(LlistX->head == NULL){	//空
		LlistX->head = tmpNode;
		return true;
	}
	
	if(i == 1){
		tmpNode->next = (struct Lnode *)LlistX->tmppos;
		LlistX->head = tmpNode;
		return true;
	}
	
	while(i > 2){
		if(LlistX->tmppos == NULL){
			return false;
		}
		i--;
		LlistX->tmppos = (Lnode *)LlistX->tmppos->next;
	}
	tmpNode->next = LlistX->tmppos->next;
	LlistX->tmppos->next = (struct Lnode *)tmpNode;
	return true;
}
//x=========================================================
bool LListDelete(Llist *LlistX ,unsigned int i ,ElemtypeL *e){
	if(LlistX->head == NULL){	//空
		return false;
	}
	if(i == 0){//位置超范围
		return false;
	}
	LlistX->tmppos = LlistX->head;
	
	if(LlistX->head->next == NULL){	//
		*e = LlistX->tmppos->data;
		free(LlistX->tmppos);
		LlistX->head = NULL;
		return true;
	}
	if(i == 1){
		*e = LlistX->tmppos->data;
		LlistX->head = (Lnode *)LlistX->head->next;
		LlistX->tmppos->next = NULL;
		free(LlistX->tmppos);
		return true;
	}
	while(i > 2){
		if(LlistX->tmppos == NULL){
			return false;
		}
		i--;
		LlistX->tmppos = (Lnode *)LlistX->tmppos->next;
	}
	Lnode *tmpNode;
	tmpNode = (Lnode *)LlistX->tmppos->next;
	*e = tmpNode->data;
	LlistX->tmppos->next = tmpNode->next;
	tmpNode->next = NULL;
	free(tmpNode);
	return true;
}

bool Bresult;

void LineListfunc(void){
	//初始化
	LListInit(&Llist0, 5);
	//查询
	Lnode0 = LElemGet(&Llist0, 3);
	//插入
	Bresult = LListInsert(&Llist0 ,3 ,88);
	LListPrint(&Llist0);
	printf("==========================\n");
	//删除
	Bresult = LListDelete(&Llist0 ,1 ,&LElemData0);
	Bresult = LListDelete(&Llist0 ,3 ,&LElemData0);
	//打印
	LListPrint(&Llist0);
}


void ElemListfunc(void){
	
}