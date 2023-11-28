#ifndef VOICE_H
#define VOICE_H






extern unsigned short int u16voiceStartDelay;
extern unsigned char u8voice01Delay;


void VoiceValueinit(void);
void VoiceCMD(unsigned char u8CMD);
void Voiceplay(unsigned char u8addr);
void VoiceFunc(void);

#endif
