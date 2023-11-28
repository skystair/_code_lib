#ifndef __SQLIST_H
#define __SQLIST_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


//元素类型
#define	SQ_ELEMTYPE	unsigned int
typedef SQ_ELEMTYPE	ElemtypeSQ;
//单元素size
#define	SQ_ELEM_SINGLE_SIZE	(sizeof(SQ_ELEMTYPE))

typedef struct{
	ElemtypeSQ *data;
	unsigned int MaxSize;
	unsigned int length;
}SQlist;



void SQListfunc(void);





#endif
