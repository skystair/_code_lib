//0~5个短按按键 + 1个可长按按键
#ifndef __KEY_H__
#define __KEY_H__

//#include "config.h" 
#include "string.h" 

//二次处理参数=====================================================
//定义按键按下
#define KEY1_READ	(AD_ADKEY >= 3000)
#define KEY2_READ	((AD_ADKEY>300)&&(AD_ADKEY<1000))
#define KEY3_READ	0//
#define KEY4_READ	0//
#define KEY5_READ	0//

#define KEYL_READ	0

//KeydelayADD()调用-------
//KeyFunc()调用-----------

//*** <<< Use Configuration Wizard in Context Menu >>> ***
//1.定义按键数量
//短按按键数量
//<o> 1.KeyshortNUM <0-5> <i>range0~5
#define KeyshortNUM	3
//2.定义按键按下时间
//<o> 2.KEYshort_DELAY <0-255> <i>range0~255ms
//#define KEYshort_DELAY	20
extern const unsigned short int KEYshort_DELAY;
//3.定义按下电平
//<o> 3.KEY_DOWN <0-1> <i>range0~1
#define KEY_DOWN	1

//是否定义长按按键
//<c> enable KEYLONG
//#define KEYLONG
//</c>
//<o> 1.KEYlong_DELAY <0-65535> <i>range0~65535ms
#define KEYlong_DELAY	1500
//*** <<< end of configuration section >>>    ***

#define DC_IN		1

#define PRESS_SHORT	1
#define PRESS_1S5	2

#define Keyshort1		Key[0]
#define Keyshort2		Key[1]
#define Keyshort3		Key[2]
#define Keyshort4		Key[3]
#define Keyshort5		Key[4]


#define KeyPWR		Keyshort1
#define KeyMOD		Keyshort2

#define KeyStructSize	6
typedef struct {
	unsigned char flag;			//1
	unsigned char keep;			//1
	unsigned short int u16Delay;//2
	unsigned short int u16Delaytim;
}KeyStruct;

extern KeyStruct Key[KeyshortNUM];

#ifdef KEYLONG
extern KeyStruct KeylongStruct;
#endif

extern void KeyValueInit(void);
extern void KeyFunc(void);
extern void KeydelayADD(void);

extern unsigned char KEYREAD(unsigned char u8KeyCH);
//----------------------------------------------
//unsigned char KEYREAD(unsigned char u8KeyCH){
//	Key[u8KeyCH].u16Delaytim = KEYshort_DELAY;
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
