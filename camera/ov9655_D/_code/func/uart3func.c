#include "config.h"
//bat
const unsigned char u8UartTxstring1[] = "uartx Tx test!!!";
//0主机------------------------------------------------------------------------
UartxStruct Uart3;
unsigned char u8Uart3RxData[Uart3RxDNUM];


unsigned char *u8Uart3RxDATAp;
unsigned char *u8Uart3TxDATAp;

unsigned char u8Uart3RxSize;
unsigned char u8Uart3TxSize;
//unsigned char u8Uart3RxDATA[Uart3rxDNUM];

void Uart3Rxjieshou(void);
void Uart3Rxchuli(void);
void Uart3Txchuli(void);

void Uart3TXvalueinit(void);
void Uart3RXvalueinit(void);


//BAT==============================================================================
void Uart3TXvalueinit(void){
	Uart3.TXp = 0;
	Uart3.TXuncomp = 0;
	
	u8Uart3TxSize = 10;
	u8Uart3RxSize = 10;
	//memset(u8Uart3TxDATA,0,Uart3txDNUM);
	
	u8Uart3RxDATAp = u8Uart3RxData;
	u8Uart3TxDATAp = (unsigned char *)u8UartTxstring1;
	
}
void Uart3Txchuli(void){
	unsigned char i;
	if(Uart3.TXuncomp == 0){
		
		Uart3.TXuncomp = 1;
		
//		u8Uart3TxDATAp[Uart3txDNUM-1] = 0;
//		for(i = 0;i<(Uart3txDNUM-1);i++){
//			u8Uart3TxDATAp[Uart3txDNUM-1] += u8Uart3TxDATAp[i];
//		}
		Uart3.TXp = 0;
		
		uartxTXEIE(USART3, ENABLE);
	}
		
}
//BATR---------------------------------------------------
void Uart3RXvalueinit(void){
	Uart3.Rxp = 0;
	Uart3.Rxtmp = 0;
	Uart3.RXsum = 0;
	Uart3.uRxcompflag = 0;
	
//	memset(u8Uart3RxDATAp,0,Uart3rxDNUM);
}

void Uart3Rxgetdata(void){
	u8Uart3RxDATAp[Uart3.Rxp++] = Uart3.Rxtmp;
	Uart3.RXsum += Uart3.Rxtmp;
}

void Uart3Rxjieshou(void){
	switch(Uart3.Rxp){
		case 0://AC
//			if(Uart3.Rxtmp == 0xAC){
//				Uart3Rxgetdata();
//			}
//			break;
		case 1://电池02
//			if(Uart3.Rxtmp == 0x02){
//				Uart3Rxgetdata();
//			}else{
//				Uart3RXvalueinit();
//			}
//			break;
		case 2://本机00
//			if(Uart3.Rxtmp == 0x00){
//				Uart3Rxgetdata();
//			}else{
//				Uart3RXvalueinit();
//			}
//			break;
		case 3://电量
		case 4://电压AD
		case 5://充电状态
		case 6://故障
		case 7:
		case 8:
		case 9:	
		case 10://版本号
			Uart3Rxgetdata();
			break;
		case 11://校验
			u8Uart3RxDATAp[Uart3.Rxp] = Uart3.Rxtmp;
			if(Uart3.RXsum == Uart3.Rxtmp){
				Uart3.uRxcompflag = 1;
				Uart3.Rxp = 0;
				Uart3.RXsum = 0;
			}else{
				Uart3RXvalueinit();
			}
			break;
		default:
			Uart3RXvalueinit();
			break;
	}
}

void Uart3Rxchuli(void){

	if(Uart3.uRxcompflag == 1){
		Uart3.uRxcompflag = 0;
		
		
	}
}

void USART3_IRQHandler(void)
{
	//tx------------------------------------------------
	if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET) {
		USART_ClearITPendingBit(USART3,USART_IT_TXE);
		if(Uart3.TXuncomp == 1){
			if(u8Uart3TxDATAp[Uart3.TXp] == '\0'){//(Uart3.TXp >= Uart3txDNUM){
				while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
				Uart3.TXuncomp = 0;
				Uart3.TXp = 0;
				//Uart3TX_Len = 0;
				uartxTXEIE(USART3, DISABLE);
			}else{
				USART_SendData(USART3 ,u8Uart3TxDATAp[Uart3.TXp++]);
			}
		}
	}
	//rx------------------------------------------------
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET){
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
	
		Uart3.Rxtmp = (uint8_t)USART_ReceiveData(USART3);
		Uart3Rxjieshou();
	}
}
