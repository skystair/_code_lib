#ifndef __LINELIST_H
#define __LINELIST_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


//元素类型
#define	L_ELEMTYPE	unsigned int
typedef L_ELEMTYPE	ElemtypeL;
//单元素size
#define	L_ELEM_SINGLE_SIZE	(sizeof(L_ELEMTYPE))

//链表
typedef struct{
	ElemtypeL data;
	struct Lnode *next;
}Lnode;

typedef struct{
	Lnode *tmppos;
	Lnode *head;
}Llist;



void LineListfunc(void);





#endif
