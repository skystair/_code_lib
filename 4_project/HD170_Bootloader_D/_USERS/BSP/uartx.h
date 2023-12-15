#ifndef __UARTX_H__
#define __UARTX_H__


#define HEAD0	0x3A	//:
#define HEAD1	0x31	//1
#define HEAD2	0x30	//0

#define ADDRHEAD	0x38	//8






extern void Uart_init(void);
extern void Uart_Deinit(void);

#endif
