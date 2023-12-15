#ifndef __MAINUART_H
#define __MAINUART_H
#include "config.h"









extern unsigned char RXdata[16];
extern unsigned char RXdataPosition;

extern unsigned char RXposition;
extern unsigned char RXheadReadyFlag;

extern unsigned char RXADDRheadReadyFlag;

extern unsigned char GetlineFlag;

extern unsigned char LastlineSize;
extern unsigned char LastlineFlag;

extern unsigned char HexEndFlag;

extern void GetHead(unsigned char RXtemp);
extern void GetAddrHead(unsigned char RXtemp);
extern void GetData(unsigned char RXtemp);



#endif
