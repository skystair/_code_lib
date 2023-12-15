#include "config.h"
//bat

//0主机------------------------------------------------------------------------
UartxStruct UartBAT;

unsigned char *u8BATRxDATAp;
unsigned char *u8BATTxDATAp;
//unsigned char u8BATRxDATA[UartBATrxDNUM];

void UartBATRxjieshou(void);
void UartBATRxchuli(void);
void UartBATTxchuli(void);

void UartBATTXvalueinit(void);
void UartBATRXvalueinit(void);


//BAT==============================================================================
void UartBATTXvalueinit(void){
	UartBAT.TXp = 0;
	UartBAT.TXuncomp = 0;
	//memset(u8BATTxDATA,0,UartBATtxDNUM);
	u8BATRxDATAp = u8BATRxDATA;
	u8BATTxDATAp = u8BATTxDATA;
	
}
void UartBATTxchuli(void){
	unsigned char i;
	if(UartBAT.TXuncomp == 0){
		
		UartBAT.TXuncomp = 1;
		
		u8BATTxDATAp[UartBATtxDNUM-1] = 0;
		for(i = 0;i<(UartBATtxDNUM-1);i++){
			u8BATTxDATAp[UartBATtxDNUM-1] += u8BATTxDATAp[i];
		}
		UartBAT.TXp = 0;
		
		md_uart_disable_rx(UART_BAT);
		md_uart_enable_it_tfempty(UART_BAT);
	}
		
}
//BATR---------------------------------------------------
void UartBATRXvalueinit(void){
	UartBAT.Rxp = 0;
	UartBAT.Rxtmp = 0;
	UartBAT.RXsum = 0;
	UartBAT.uRxcompflag = 0;
	
//	memset(u8BATRxDATAp,0,UartBATrxDNUM);
}

void UartBATRxgetdata(void){
	u8BATRxDATAp[UartBAT.Rxp++] = UartBAT.Rxtmp;
	UartBAT.RXsum += UartBAT.Rxtmp;
}

void UartBATRxjieshou(void){
	switch(UartBAT.Rxp){
		case 0://AC
			if(UartBAT.Rxtmp == 0xAC){
				UartBATRxgetdata();
			}
			break;
		case 1://电池02
			if(UartBAT.Rxtmp == 0x02){
				UartBATRxgetdata();
			}else{
				UartBATRXvalueinit();
			}
			break;
		case 2://本机00
			if(UartBAT.Rxtmp == 0x00){
				UartBATRxgetdata();
			}else{
				UartBATRXvalueinit();
			}
			break;
		case 3://电量
		case 4://电压AD
		case 5://充电状态
		case 6://故障
		case 7:
		case 8:
		case 9:	
		case 10://版本号
			UartBATRxgetdata();
			break;
		case 11://校验
			u8BATRxDATAp[UartBAT.Rxp] = UartBAT.Rxtmp;
			if(UartBAT.RXsum == UartBAT.Rxtmp){
				UartBAT.uRxcompflag = 1;
				UartBAT.Rxp = 0;
				UartBAT.RXsum = 0;
			}else{
				UartBATRXvalueinit();
			}
			break;
		default:
			UartBATRXvalueinit();
			break;
	}
}

void UartBATRxchuli(void){
	if(UartBATerrdelay >= UART_ERRORDELAY){
		UartBATerrdelay = UART_ERRORDELAY;
//		if(ucMode_index != 0){
//			UartBATerrflag = 1;
//		}
	}

	if(UartBAT.uRxcompflag == 1){
		UartBAT.uRxcompflag = 0;
		
		UartBATerrdelay = 0;
//		if(ucMode_index == 0){
//			UartBATerrflag = 0;
//		}
		if(u8BATRxDATAp[7] == 0xdd){
			if(u8BATRxDATAp[8] == 0xdd){
				if(u8BATRxDATAp[9] == 0xdd){
					__NVIC_SystemReset();
				}
			}
		}
		//BatRxhandle();
	}
}

void USARTbat_IRQHandler(void)
{
	//tx------------------------------------------------
	if (md_uart_is_active_it_tfempty(UART_BAT)) {
		md_uart_clear_it_tfempty(UART_BAT);
		if(UartBAT.TXuncomp == 1){
			if(UartBAT.TXp >= UartBATtxDNUM){
				while (!READ_BIT(UART_BAT->STAT,UART_STAT_TFEMPTY));
				UartBAT.TXuncomp = 0;
				UartBAT.TXp = 0;
				//UartBATTX_Len = 0;
				md_uart_disable_it_tfempty(UART_BAT);
				md_uart_enable_rx(UART_BAT);
			}else{
				UART_BAT->TXDATA = u8BATTxDATAp[UartBAT.TXp++];
			}
		}
	}
	//rx------------------------------------------------
	if (md_uart_is_active_it_rfnempty(UART_BAT)) {
		md_uart_clear_it_rfnempty(UART_BAT);
	
		UartBAT.Rxtmp = (uint8_t)(READ_REG(UART_BAT->RXDATA));
		UartBATRxjieshou();
	}
}
