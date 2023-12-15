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
//	WRITE_REG(UART1->TXDATA, (uint8_t)ch);
//    while (!READ_BIT(UART1->STAT,UART_STAT_TFEMPTY));
//    return ch;
//}
void uartTick(void);
void uartxvaluinit(void){
	u16UxTxDelay = 0;
	u8UxTxstep = 0;
	
	memset(&u8UxErrorflag, 0,3);
	memset(&u16UxErrordelay, 0,3);

	
	UartBATTXvalueinit();
	UartBATRXvalueinit();


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
}

void uartfunc(void){
	
}





