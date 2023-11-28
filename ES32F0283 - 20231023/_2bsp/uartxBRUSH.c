#include "config.h"
//brush
unsigned char u8yuyinflag;


unsigned char u8Xidiflag;
//1主机------------------------------------------------------------------------
UartxStruct UBrush;
unsigned char u8UbrushTxDATA[UbrushtxDNUM];
unsigned char u8UbrushRxDATA[UbrushrxDNUM];

void UbrushTxEnable(void);
void UbrushTxDisable(void);
void UbrushRxjieshou(void);
void UbrushRxchuli(void);
void UbrushTxchuli(void);

void UbrushTXvalueinit(void);
void UbrushRXvalueinit(void);

void UbrushTxEnable(void){
	GPioUbrushTxEnable();
	md_uart_enable_tx(UART_BRUSH);
}
void UbrushTxDisable(void){
	GPioUbrushTxDisable();
	md_uart_disable_tx(UART_BRUSH);
	
	
}
//U3==============================================================================
void UbrushTXvalueinit(void){

	UBrush.TXp = 0;
	UBrush.TXuncomp = 0;
	memset(u8UbrushTxDATA,0,UbrushtxDNUM);
	u8UbrushTxDATA[0] = 0xac;
	u8UbrushTxDATA[1] = 0;
	u8UbrushTxDATA[2] = 4;
	
	u8UbrushTxDATA[3] = 1;
	u8UbrushTxDATA[4] = 2;
	
	u8Xidiflag = 0;
	
	u8yuyinflag = 1;
	
}
void UbrushTxchuli(void){
	unsigned char i;
	if(u8Xidiflag == 1){
		if(UBrush.TXuncomp == 0){
			UBrush.TXuncomp = 1;
			
//			u8UbrushTxDATA[3] = ((u8yuyinflag <<4)| ucMode_Wshitf);
			u8UbrushTxDATA[4] = 2;

			u8UbrushTxDATA[UbrushtxDNUM -1] = 0;
			for(i = 0;i<(UbrushtxDNUM -1);i++){
				u8UbrushTxDATA[UbrushtxDNUM -1]+=u8UbrushTxDATA[i];
			}
			
			UBrush.TXp = 0;
			
			md_uart_disable_rx(UART_BRUSH);
			UbrushTxEnable();
			md_uart_enable_it_tfempty(UART_BRUSH);
		}
	}
}
//U3R---------------------------------------------------
void UbrushRXvalueinit(void){
	UBrush.Rxp = 0;
	UBrush.Rxtmp = 0;
	UBrush.RXsum = 0;
	UBrush.uRxcompflag = 0;
	
	memset(u8UbrushRxDATA,0,UbrushrxDNUM);
}

void UbrushRxgetdata(void){
	u8UbrushRxDATA[UBrush.Rxp++] = UBrush.Rxtmp;
	UBrush.RXsum += UBrush.Rxtmp;
}

void UbrushRxjieshou(void){
	switch(UBrush.Rxp){
		case 0://AC
			if(UBrush.Rxtmp == 0xAC){
				UbrushRxgetdata();
			}
			break;
		case 1://
			if(UBrush.Rxtmp == 0x04){
				UbrushRxgetdata();
			}else{
				UbrushRXvalueinit();
			}
			break;
		case 2://本机00
			if(UBrush.Rxtmp == 0x00){
				UbrushRxgetdata();
			}else{
				UbrushRXvalueinit();
			}
			break;
		case 3://脏污2红色百分比
		case 4://故障
		case 5://版本号
			UbrushRxgetdata();
			break;
		case 6://校验
			u8UbrushRxDATA[UBrush.Rxp] = UBrush.Rxtmp;
			if(UBrush.RXsum == UBrush.Rxtmp){
				UBrush.uRxcompflag = 1;
				u8Xidiflag = 1;
				UBrush.Rxp = 0;
				UBrush.RXsum = 0;
			}else{
				UbrushRXvalueinit();
			}
			break;
		default:
			UbrushRXvalueinit();
			break;
	}
}

void UbrushRxchuli(void){
	if(u8Xidiflag == 1){
		if(UartBrusherrdelay >= UART_ERRORDELAY){
			UartBrusherrdelay = UART_ERRORDELAY;
//			if(ucMode_index != 0){
//				UartBrusherrflag = 1;
//			}
			//u8Xidiflag = 0;
		}
	}else{
		UartBrusherrdelay = 0;
		UartBrusherrflag = 0;
	}
		
	if(UBrush.uRxcompflag == 1){
		UBrush.uRxcompflag = 0;
		
		UartBrusherrdelay = 0;
//		if(ucMode_index == 0){
//			UartBrusherrflag = 0;
//		}
		
	}
}

void USARTbrush_IRQHandler(void)     /*  IRQ 29  */
{
	//tx------------------------------------------------
	if (md_uart_is_active_it_tfempty(UART_BRUSH)) {
		md_uart_clear_it_tfempty(UART_BRUSH);
		if(UBrush.TXuncomp == 1){
			if(UBrush.TXp >= UbrushtxDNUM){
				while (!READ_BIT(UART3->STAT,UART_STAT_TFEMPTY));
				UBrush.TXuncomp = 0;
				UBrush.TXp = 0;
				//UbrushTX_Len = 0;
				UbrushTxDisable();
				md_uart_disable_it_tfempty(UART_BRUSH);
				md_uart_enable_rx(UART_BRUSH);
			}else{
				UART_BRUSH->TXDATA = u8UbrushTxDATA[UBrush.TXp++];
			}
		}
	}
	//rx------------------------------------------------
	if (md_uart_is_active_it_rfnempty(UART_BRUSH)) {
		md_uart_clear_it_rfnempty(UART_BRUSH);
	
		UBrush.Rxtmp = (uint8_t)(READ_REG(UART_BRUSH->RXDATA));
		UbrushRxjieshou();
	}
	
}
