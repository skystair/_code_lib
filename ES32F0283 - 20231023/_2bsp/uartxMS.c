#include "config.h"
///mot&lcd screne



//PUBLIC
unsigned char u8MOTxLCDflag;

unsigned char u8MSTxlen;
//1主机------------------------------------------------------------------------
UartxStruct UartMS;
unsigned char *u8UmsTxDATAp;
unsigned char *u8UmsRxDATAp;

void UartMSRxjieshou(void);
void UartMSRxchuli(void);
void UartMSTxchuli(void);

void UartMSTXvalueinit(void);
void UartMSRXvalueinit(void);


//U0==============================================================================
void UartMSTXvalueinit(void){
	u8MOTxLCDflag = 0;
//	u8MSTxlen = UartMOTtxlen-1;
	
	UartMS.TXp = 0;
	UartMS.TXuncomp = 0;
//	
//	u8UmsRxDATAp = u8MOTRxDATA;
}
void UartMSTxchuli(void){
	unsigned char i;
	if(u8MOTxLCDflag == 0){	//MOT--------------------------
//		u8UmsTxDATAp = u8MOTTxDATA;
//		u8MSTxlen = UartMOTtxlen -1;
		
	}else{					//LCD--------------------------
//		u8UmsTxDATAp = u8LCDTxDATA;
//		u8MSTxlen = UartLCDtxlen -1;
//		u8LCDTxRuntick++;
	}
	
	if(UartMS.TXuncomp == 0){
		UartMS.TXuncomp = 1;

		u8UmsTxDATAp[u8MSTxlen] = 0;
		for(i = 0;i<(u8MSTxlen);i++){
			u8UmsTxDATAp[u8MSTxlen]+=u8UmsTxDATAp[i];
		}
		
		UartMS.TXp = 0;
		md_uart_enable_it_tfempty(UART_MS);
	}
		
}
//U0R---------------------------------------------------
void UartMSRXvalueinit(void){
	UartMS.Rxp = 0;
	UartMS.Rxtmp = 0;
	UartMS.RXsum = 0;
	UartMS.uRxcompflag = 0;
	
//	memset(u8UmsRxDATA,0,UartMSrxDNUM);
}

void UartMSRxgetdata(void){
	u8UmsRxDATAp[UartMS.Rxp++] = UartMS.Rxtmp;
	UartMS.RXsum += UartMS.Rxtmp;
}

void UartMSRxjieshou(void){
	switch(UartMS.Rxp){
		case 0://AC
			if(UartMS.Rxtmp == 0xAC){
				UartMSRxgetdata();
			}
			break;
		case 1://电机01/LCD03
			if(UartMS.Rxtmp == 0x01){
				UartMSRxgetdata();
			}else{
				UartMSRXvalueinit();
			}
			break;
		case 2://本机00
			if(UartMS.Rxtmp == 0x00){
				UartMSRxgetdata();
			}else{
				UartMSRXvalueinit();
			}
			break;
		case 3://功率bit0~7
		case 4://功率bit8~15
		case 5://转速bit0~7
		case 6://转速bit8~15
		case 7://转速bit16~23
		case 8://温度+50
		case 9://故障
		case 10://版本号
			UartMSRxgetdata();
			break;
		case 11://校验
			u8UmsRxDATAp[UartMS.Rxp] = UartMS.Rxtmp;
			if(UartMS.RXsum == UartMS.Rxtmp){
				UartMS.uRxcompflag = 1;
				UartMS.Rxp = 0;
				UartMS.RXsum = 0;
			}else{
				UartMSRXvalueinit();
			}
			break;
		default:
			UartMSRXvalueinit();
			break;
	}
}

void UartMSRxchuli(void){
	if(UartMSerrdelay >= UART_ERRORDELAY){
		UartMSerrdelay = UART_ERRORDELAY;
//		if(ucMode_index != 0){
//			UartMSerrflag = 1;
//		}
	}
	if(UartMS.uRxcompflag == 1){
		UartMS.uRxcompflag = 0;
		
		UartMSerrdelay = 0;
//		if(ucMode_index == 0){
//			UartMSerrflag = 0;
//		}
		
//		MotRxfunc();
	}
}

void USARTms_IRQHandler(void)
{
	//tx------------------------------------------------
	if (md_uart_is_active_it_tfempty(UART_MS)) {
		md_uart_clear_it_tfempty(UART_MS);
		if(UartMS.TXuncomp == 1){
			if(UartMS.TXp > u8MSTxlen){
				while (!READ_BIT(UART3->STAT,UART_STAT_TFEMPTY));
				UartMS.TXuncomp = 0;
				UartMS.TXp = 0;
				//UartMSTX_Len = 0;
				md_uart_disable_it_tfempty(UART_MS);
			}else{
				UART_MS->TXDATA = u8UmsTxDATAp[UartMS.TXp++];
			}
		}
	}
	//rx------------------------------------------------
	if (md_uart_is_active_it_rfnempty(UART_MS)) {
		UartMS.Rxtmp = (uint8_t)(READ_REG(UART_MS->RXDATA));
		UartMSRxjieshou();
		md_uart_clear_it_rfnempty(UART_MS);
	}
}

