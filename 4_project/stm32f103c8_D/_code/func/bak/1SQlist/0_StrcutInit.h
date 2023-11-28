#ifndef __DATASTRUCT_H
#define __DATASTRUCT_H

#include <stdbool.h>


//#define TRUE		1
//#define FALSE		0

//typedef enum {FALSE = 0,TRUE = 1} bool;

#define	ELEMTYPE	unsigned char

typedef ELEMTYPE	Elemtype;

#define	ELMAXSIZE	10

typedef struct{
	Elemtype data[ELMAXSIZE];
	unsigned int length;
}DStruct;


























void InitList(DStruct *DStructX);






#endif
