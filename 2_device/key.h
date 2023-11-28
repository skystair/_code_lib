#ifndef __KEY_H__
#define __KEY_H__

#define KeyNUM	5

#define KEY_DOWN	0
#define KEY_RELEASE	1

#define DC_IN		1

#define PRESS_SHORT	1
#define PRESS_1S0	2

#define KeyPWR		Key[0]
#define KeyMOD		Key[1]
#define KeyHEAT		Key[2]
#define KeyMicro	Key[3]
#define KeyDCin		Key[4]



#define KeyStructSize	4

typedef struct {
	unsigned char flag;
	unsigned char keep;
	unsigned short int u16Delay;
}KeyStruct;

extern KeyStruct Key[KeyNUM];

extern void KeyValueInit(void);
extern void KeyFunc(void);


#endif
