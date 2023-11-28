#ifndef __UARTX_H__
#define __UARTX_H__

#define UART_TIMBASE		50
#define UART_ERRORDELAY		3000



typedef struct {
	unsigned char TXp;//指针
	unsigned char TXuncomp;
//	unsigned char TxDATA[10];
	
	unsigned char Rxp;
	unsigned char Rxtmp;
	unsigned char RXsum;
	unsigned char uRxcompflag;
//	unsigned char RxDATA[10];
//	unsigned char errorCNT;
}UartxStruct;


extern void uartxvaluinit(void);
extern void uartTick(void);
extern void uartxinit(void);
extern void uartfunc(void);


#endif
