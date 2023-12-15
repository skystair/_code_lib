#include "config.h"

unsigned char StartFlag= 0;
	
unsigned char RXposition = 0;

unsigned char RXdataHead[3];
unsigned char RXlineSize;

unsigned char RXheadReadyFlag = 0;
unsigned char RXADDRheadReadyFlag = 0;

unsigned char RXdatatemp0 = 0;
unsigned char RXdataPosition = 0;
unsigned char RXdata[16];

unsigned char LastlineSize;
unsigned char LastlineFlag;

unsigned char GetlineFlag;

unsigned char HexEndFlag = 0;

void GetHead(unsigned char RXtemp);
void GetAddrHead(unsigned char RXtemp);
unsigned char ASCII2D(unsigned char ucASCII);
void GetData(unsigned char RXtemp);








void GetHead(unsigned char RXtemp){
	if(RXposition == 0){		//head0 = ":"?
		if(RXtemp == HEAD0){
			RXdataHead[0] = HEAD0;
			RXposition = 1;
		}
	}else if(RXposition == 1){	//head0 = "1"/"0"?
		if(RXtemp == 0x31){
			RXdataHead[1] = 1;	//1
			RXposition = 2;
			
		}else if(RXtemp == 0x30){	//0
			RXdataHead[1] = 0;
			RXposition = 2;
			if(RXheadReadyFlag == 1){
				//LastlineFlag = 1;
			}
			
		}else{
			RXposition = 0;
			RXdataHead[0] = 0;
		}
	}else if(RXposition == 2){	//head1 = "0"?
		RXdataHead[2] = ASCII2D(RXtemp);
		RXposition = 3;
		RXheadReadyFlag = 1;
		
		LastlineSize = (RXdataHead[1] << 4) + RXdataHead[2];
	}
}


void GetAddrHead(unsigned char RXtemp){
	if(RXposition == 3){
		if(RXtemp == ADDRHEAD){				//8
			RXposition = 4;
		}else{
			RXposition = 0;
			RXheadReadyFlag = 0;
		}
	}else if(RXposition == 4){				//0
		if(RXtemp == 0x30){
			RXposition = 5;
		}else{
			RXposition = 0;
			RXheadReadyFlag = 0;
		}
	}else if(RXposition == 5){				//0
		if(RXtemp == 0x30){
			RXposition = 6;
		}else{
			RXposition = 0;
			RXheadReadyFlag = 0;
		}
	}else if(RXposition == 6){				//0
		if(RXtemp == 0x30){
			RXposition = 7;
			RXADDRheadReadyFlag = 1;
		}else{
			RXposition = 0;
			RXheadReadyFlag = 0;
		}
	}
	
}

unsigned char ASCII2D(unsigned char ucASCII){
	unsigned char n;
	if( (ucASCII <= 57)&&(ucASCII >= 48) ){	//0~9
		n = ucASCII - 48;
	}
	
	if( (ucASCII <= 70)&&(ucASCII >= 65) ){	//a~f
		n = ucASCII - 55;
	}
	return n;
}

void GetData(unsigned char RXtemp){
	
	if(LastlineFlag != 1){
		
		if( (RXposition %2) == 1){
		RXdatatemp0 = ASCII2D(RXtemp) << 4;
		}else{
			RXdata[RXdataPosition] = RXdatatemp0 + ASCII2D(RXtemp);
			//RXdatatemp1 = ASCII2D(RXtemp);
			RXdataPosition++;
			
			if(RXdataPosition >= LastlineSize){
					//RXdataPosition = 0;
				GetlineFlag = 1;
				if(LastlineSize < 16){
					LastlineFlag = 1;
				}
			}
		}
	}
}


