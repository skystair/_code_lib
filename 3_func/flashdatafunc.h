#ifndef __FLASHDATAFUNC_H
#define __FLASHDATAFUNC_H

#define DATA_SAVE_ADDR0  ((unsigned int)0x08004000)	//充电完成
#define DATA_SAVE_ADDR1  ((unsigned int)0x08004002)	//电量



extern unsigned short int u16Batfullflag;
extern unsigned char u8flashW_CapDelay;
extern unsigned char u8flashC_Capflag;

extern unsigned char u8flashfuncdelay;
extern unsigned char u8updataflag;


extern void flashvalueinit(void);
extern void flashdatafunc(void);
#endif



