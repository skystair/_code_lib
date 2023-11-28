#ifndef __DUSTFUNC_H
#define __DUSTFUNC_H



#define DUST_VALUE_MIN  (0)
#define DUST_VALUE_MAX  (100)  // ?????????






extern unsigned char u8dustERRdelay;
extern unsigned char u8dustCaldelay;
extern unsigned char u8dustpos;
extern unsigned char u8dustnum[10];
extern unsigned char u8dustdelay;
extern unsigned short int u16dustsum;

extern void DUSTfunc(void);

#endif



