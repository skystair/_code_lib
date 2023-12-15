#ifndef __JUMP_H__
#define __JUMP_H__

typedef void(*pFunction)(void);

#define APP_ADDRESS		0x10000
//#define JUMP_ADDRESS	(*(__IO uint32_t*)(APP_ADDRESS + 4))


extern void JumpFunc(void);

#endif
