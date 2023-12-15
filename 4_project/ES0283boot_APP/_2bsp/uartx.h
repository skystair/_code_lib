#ifndef __UARTX_H__
#define __UARTX_H__

#define UART_TIMBASE		50
#define UART_ERRORDELAY		3000

#define UartBATerrflag		u8UxErrorflag[0]
#define UartMSerrflag		u8UxErrorflag[1]
#define UartBrusherrflag	u8UxErrorflag[2]

#define UartBATerrdelay		u16UxErrordelay[0]
#define UartMSerrdelay		u16UxErrordelay[1]
#define UartBrusherrdelay	u16UxErrordelay[2]


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

extern unsigned char u8UxErrorflag[3];
extern unsigned short int u16UxErrordelay[3];

extern unsigned char u8Shibiedelay;
//extern unsigned char u8U0txDATA[UartMStxDNUM];
//extern unsigned char u8U1txDATA[UartBATtxDNUM];

extern void uartxvaluinit(void);
extern void uartTick(void);
extern void uartxinit(void);
extern void uartfunc(void);


#endif
