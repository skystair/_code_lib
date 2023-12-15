//#include "config.h"
#include "key.h" 

#ifdef KEYLONG
	KeyStruct KeylongStruct;
#endif

KeyStruct Key[KeyshortNUM];

void KeydelayADD(void);
void KeyValueInit(void);
void KeyFunc(void);
unsigned char Keyflagread(unsigned char u8keych);
void KeyflagClear(unsigned char u8keych);
unsigned char Keyholdread(unsigned char u8keych);

void KeyValueInit(void)
{
	unsigned char i;
	for(i = 0;i< KeyshortNUM;i++){
		memset(&Key[i],0,KeyStructSize);
	}
	memset(&KeylongStruct,0,KeyStructSize);
}

void KeydelayADD(void){
	unsigned char i;
	for(i = 0;i< KeyshortNUM;i++){
		Key[i].u16Delay++;
	}
	KeylongStruct.u16Delay++;
}

unsigned char Keyflagread(unsigned char u8keych){
	if(u8keych < KeyshortNUM)
		return Key[u8keych].flag;
	else if(u8keych == KEYLONG){
		return KeylongStruct.flag;
	}
	return 0;
}
void KeyflagClear(unsigned char u8keych){
	if(u8keych < KeyshortNUM)
		Key[u8keych].flag = 0;
	else if(u8keych == KEYLONG){
		KeylongStruct.flag = 0;
	}
}
unsigned char Keyholdread(unsigned char u8keych){
	if(u8keych < KeyshortNUM)
		return Key[u8keych].keep;
	else if(u8keych == KEYLONG){
		return KeylongStruct.keep;
	}
	return 0;
}

void KeyFunc(void)	
{
	unsigned char i;
	
	for(i = 0;i< KeyshortNUM;i++){
		if(KEYREAD(i) == 1){
		if(Key[i].u16Delay >= KEYshort_DELAY)
		{
			Key[i].u16Delay = KEYshort_DELAY;
			if(Key[i].keep != 1)
			{
				Key[i].keep = 1;
				Key[i].flag = PRESS_SHORT;
			}
		}
	}else{
		Key[i].flag = 0;
		Key[i].keep = 0;
		Key[i].u16Delay = 0;
	}
	}
	
	#ifdef KEYLONG
	if(KEYREAD(KEYLONG)){
		if(KeylongStruct.u16Delay >= KEYlong_DELAY)
		{
			KeylongStruct.u16Delay = KEYlong_DELAY;
			if(KeylongStruct.keep != 1)
			{
				KeylongStruct.keep = 1;
				KeylongStruct.flag = 2;
			}
		}
	}else{
		if((KeylongStruct.u16Delay >= KEYshort_DELAY)&&(KeylongStruct.u16Delay < KEYlong_DELAY)){
			KeylongStruct.flag = 1;
		}else{
			KeylongStruct.flag = 0;
		}
		KeylongStruct.keep = 0;
		KeylongStruct.u16Delay = 0;
	}
	#endif
}


	
