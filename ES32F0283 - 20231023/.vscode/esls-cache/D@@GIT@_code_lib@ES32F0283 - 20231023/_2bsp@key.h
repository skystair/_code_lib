//0~5个短按按键 + 1个可长按按键
#ifndef __KEY_H__
#define __KEY_H__

#include "string.h" 

#define KEYLONG		5

#define KeyshortNUM	1

#define KEY_PWR		0
#define Key_MOD		1

//1.#include file-------------------------------------------------
#include "config.h" 

//2.deine keydown
#define KEY1_READ	((AD_ADKEY>400)&&(AD_ADKEY<900))
#define KEY2_READ	0
#define KEY3_READ	0//
#define KEY4_READ	0//
#define KEY5_READ	0//

#define KEYL_READ	(AD_ADKEY >= 1200)

//3.keydown time
#define KEYshortTIM	20
//const unsigned short int KEYshort_DELAY = KEYshortdelay;
extern const unsigned short int KEYshort_DELAY;

//4.KEYREAD定义
//unsigned char KEYREAD(unsigned char u8KeyCH);
extern unsigned char KEYREAD(unsigned char u8KeyCH);

//5.
//KeydelayADD()调用-------
//KeyFunc()调用-----------


#define KEYlongTIM	1500
//const unsigned short int KEYlong_DELAY = KEYlongTIM;
extern const unsigned short int KEYlong_DELAY;

#define KeyPWR			Key[0]
#define KeyMOD			Key[1]
#define Keyshort3		Key[2]
#define Keyshort4		Key[3]
#define Keyshort5		Key[4]


#define PRESS_SHORT	1
#define PRESS_LONG	2

#define KeyStructSize	5
typedef struct {
	unsigned char flag;			//1
	unsigned char keep;			//1
	unsigned short int u16Delay;//2
}KeyStruct;

//extern KeyStruct Key[KeyshortNUM];

#ifdef KEYLONG
extern KeyStruct KeylongStruct;
#endif

extern void KeyValueInit(void);
extern void KeyFunc(void);
extern void KeydelayADD(void);
extern void KeyflagClear(unsigned char u8keych);
extern unsigned char Keyflagread(unsigned char u8keych);
extern unsigned char Keyholdread(unsigned char u8keych);

//----------------------------------------------
//unsigned char KEYREAD(unsigned char u8KeyCH){
//	switch(u8KeyCH){
//		case 0:
//			if(KEY1_READ) return 1; else return 0;
//			break;
//		case 1:
//			if(KEY2_READ) return 1; else return 0;
//			break;
//		case 2:
//			if(KEY3_READ) return 1; else return 0;
//			break;
//		case 3:
//			if(KEY4_READ) return 1; else return 0;
//			break;
//		case 4:
//			if(KEY5_READ) return 1; else return 0;
//			break;
//		default:break;
//	}
//	return 0;
//}
#endif
