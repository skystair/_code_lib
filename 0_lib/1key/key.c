//#include "config.h"
#include "key.h" 

#ifdef KEYLONG
	KeyStruct KeylongStruct;
#endif

KeyStruct Key[KeyshortNUM];

void KeydelayADD(void);
void KeyValueInit(void);
void KeyFunc(void);

void KeyValueInit(void)
{
	unsigned char i;
	for(i = 0;i< KeyshortNUM;i++){
		memset(&Key[i],0,KeyStructSize);
	}
}

void KeydelayADD(void){
	unsigned char i;
	for(i = 0;i< KeyshortNUM;i++){
		Key[i].u16Delay++;
	}
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
	if(KEYREAD(KeyshortNUM)){
		if(KeylongStruct.u16Delay >= KeylongStruct.u16Delaytim)
		{
			KeylongStruct.u16Delay = KeylongStruct.u16Delaytim;
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


	
