#ifndef __UARTX_H__
#define __UARTX_H__


#define UART1txDNUM	(1+5)
#define UART3txDNUM	(5+5)









//extern unsigned char u8uart1delay;
//extern unsigned char u8U1txDATA[UART1txDNUM];

extern unsigned char u8uart3delay;
extern unsigned char u8U3txDATA[UART3txDNUM];

extern void uartxvaluinit(void);
extern void uartxinit(void);
extern void uartfunc(void);


#endif

//	if(UART2->IER &0x01){
//		if (UART_GetITStatus(UART2, UART_ISR_TX) != RESET) {//ISR
//			UART_ClearITPendingBit(UART2, UART_ICR_TX);//ICR UART_ICR_TXC
//			UART_ClearITPendingBit(UART2, UART_ICR_TXC);//ICR UART_ICR_TXC
//			if(Uart2TXp >= 12){
//				UART_ITConfig(UART2, UART_IER_TX, DISABLE);//IER
//				while (!UART_GetFlagStatus(UART2, UART_CSR_TXC));//CSR
//				Uart2TXuncomp = 0;
//				Uart2TXp = 0;
//	//			Uart2RX_Len = Uart2TX_Len;
//				
//				u8U2Tx2sum = 0;
//	//			Uart2TX_Len = 0;
//			}else{
//				if(Uart2TXp < 10){
//					u8U2Tx2sum+= u8Uart2_TX[Uart2TXp];
//				}else if(Uart2TXp == 10){
//					u8Uart2_TX[Uart2TXp+1] = u8U2Tx2sum + u8Uart2_TX[Uart2TXp];
//				}
//				
//				if(u8Uart2_TX[9] == 2){
//					if(Uart2TXp == 10){
//						u8Uart2_TX[9] = 0;
//						u8U2Tx2sum += u8Uart2_TXnew;
//						UART2->TDR = u8Uart2_TXnew;
//					}else{
//						UART2->TDR = u8Uart2_TX[Uart2TXp];
//						Uart2TXp++;
//					}
//					
//				}else{
//					UART2->TDR = u8Uart2_TX[Uart2TXp];
//					Uart2TXp++;
//				}
//			}
//		}
//	}
