#include "config.h"

//使用条件
//1端口定义
#define VOICE_DATA_H	gpio_bit_set(GPIOF, GPIO_PIN_7)
#define VOICE_DATA_L	gpio_bit_reset(GPIOF, GPIO_PIN_7)
//2定时器变量
/*
1ms
u16voiceStartDelay++;

100us
u8voice01Delay++;
*/

//private----------------------------------
unsigned char u8VoiceCMD;
unsigned char u8VoiceADDR;
unsigned char u8Voicestate;
unsigned char u8VoidceDATApos;

void VoicerunHL(unsigned char u8T);
void VoiceSendByte(unsigned char u8Byte);
void VoiceNextstate(void);

//public-----------------------------------
unsigned short int u16voiceStartDelay;
unsigned char u8voice01Delay;
void VoiceValueinit(void);
void VoiceCMD(unsigned char u8CMD);
void Voiceplay(unsigned char u8addr);
void VoiceFunc(void);

void VoiceValueinit(void){
	u8Voicestate = 0;
	u8VoiceADDR = 0;
}

void VoiceCMD(unsigned char u8CMD){
	u8Voicestate = 1;
	u8VoiceCMD = u8CMD;
}
void Voiceplay(unsigned char u8addr){
	u8Voicestate = 1;
	u8VoiceCMD = 0xF3;
	u8VoiceADDR = u8addr;
}

void VoicerunHL(unsigned char u8T){
	if(u8voice01Delay <= u8T){
		VOICE_DATA_H;
	}else if(u8voice01Delay <= 8){
		VOICE_DATA_L;
	}else{
		u8VoidceDATApos++;
		u8voice01Delay = 0;
	}
}
void VoiceSendByte(unsigned char u8Byte){
	if((u8Byte & BIT(u8VoidceDATApos)) == BIT(u8VoidceDATApos)){
		VoicerunHL(6);
	}else{
		VoicerunHL(2);
	}
}
void VoiceNextstate(void){
	if(u16voiceStartDelay >= 500){
		u16voiceStartDelay = 0;
		u8Voicestate++;
		u8VoidceDATApos = 0;
		u8voice01Delay = 0;
	}
}
void VoiceFunc(void){
	switch(u8Voicestate){
		case 0://H
			//idle
			VOICE_DATA_H;
			u16voiceStartDelay = 0;
			break;
		case 1://5ms L
			VOICE_DATA_L;
			VoiceNextstate();
			break;
		case 2://send func
			if(u8VoidceDATApos <8){
				VoiceSendByte(u8VoiceCMD);
				u16voiceStartDelay = 0;
			}else{
				if(u8VoiceCMD == 0xF3){
					VoiceNextstate();
				}else{
					u8Voicestate = 0;
				}
			}
			break;
		case 3://send DATA
			if(u8VoidceDATApos <8){
				VoiceSendByte(u8VoiceADDR);
			}else{
				u8Voicestate = 0;
			}
			break;
		default:break;
	}
	
}