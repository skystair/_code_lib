#include "config.h"

//private----------------------------
unsigned char u8UxTxstep;
unsigned short int u16UxTxDelay;
//pulbic------------------------------------------------------------------
unsigned char u8UxErrorflag[3];
unsigned short int u16UxErrordelay[3];

void uartxvaluinit(void);
void uartxDelayADD(void);
void uartxinit(void);
void uartfunc(void);

/* retarget the C library printf function to the USART */
//int fputc(int ch, FILE *f)
//{
//	WRITE_REG(UART3->TXDATA, (uint8_t)ch);
//    while (!READ_BIT(UART3->STAT,UART_STAT_TFEMPTY));
//    return ch;
//}
void uartTick(void);
void uartxvaluinit(void){
	u16UxTxDelay = 0;
	u8UxTxstep = 0;
	
	memset(&u8UxErrorflag, 0,3);
	memset(&u16UxErrordelay, 0,3);
	
	UartMSTXvalueinit();
	UartMSRXvalueinit();
	
	UartBATTXvalueinit();
	UartBATRXvalueinit();
	
	UbrushTXvalueinit();
	UbrushRXvalueinit();

}

void uartTick(void){
	u16UxErrordelay[0]++;
	u16UxErrordelay[1]++;
	u16UxErrordelay[2]++;
	
	u16UxTxDelay++;
}
void uartxinit(void){
	md_uart_init_typedef uart_initStruct;
	//0----------------------------------------------------
	//1----------------------------------------------------
	uart_initStruct.BaudRate = MD_UART_BAUDRATE_115200;
	uart_initStruct.BitOrder = MD_UART_LCON_LSB_FIRST;
	uart_initStruct.DataWidth = MD_UART_LCON_DLS_8;
	uart_initStruct.Parity = MD_UART_LCON_PS_NONE;
	uart_initStruct.StopBits = MD_UART_LCON_STOP_1;
	md_uart_init(UART_BAT, &uart_initStruct);
	md_uart_enable_it_rfnempty(UART_BAT);
	NVIC_EnableIRQ(UART1_IRQn);
//	//2----------------------------------------------------
	md_uart_init(UART_MS, &uart_initStruct);
	md_uart_enable_it_rfnempty(UART_MS);
	NVIC_EnableIRQ(USARTms_IRQn);
//	//3----------------------------------------------------
//	//4----------------------------------------------------
	md_uart_init(UART_BRUSH, &uart_initStruct);
	md_uart_disable_tx(UART_BRUSH);
	md_uart_enable_it_rfnempty(UART_BRUSH);
	NVIC_EnableIRQ(USARTbrush_IRQn);
}

void uartfunc(void){
	//T--------------------------------------------
	if(u16UxTxDelay <= UART_TIMBASE){//U0 Bat
		if(u8UxTxstep != 1){
			u8UxTxstep = 1;
			UartBATTxchuli();//单发
		}
	}else if(u16UxTxDelay <= (UART_TIMBASE *2)){//U1	MOT
		if(u8UxTxstep != 2){
			u8UxTxstep = 2;
			u8MOTxLCDflag = 0;
			UartMSTxchuli();//单发
		}
	}else if(u16UxTxDelay <= (UART_TIMBASE *3)){//U1	LCD
		if(u8UxTxstep != 3){
			u8UxTxstep = 3;
			u8MOTxLCDflag = 1;
			UartMSTxchuli();//单发
		}
	}else if(u16UxTxDelay <= (UART_TIMBASE *4)){//U3	brush
		if(u8UxTxstep != 4){
			u8UxTxstep = 4;
			
			UbrushTxchuli();//单发
		}
	}else{
		u8UxTxstep = 0;
		u16UxTxDelay = 0;
	}

	UartMSRxchuli();//单收
	UartBATRxchuli();//单收
	UbrushRxchuli();//单收
}





