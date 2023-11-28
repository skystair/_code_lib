#include "config.h"
//unsigned char u8uart1delay;
//unsigned char Uart1TXp;
//unsigned char Uart1TXuncomp;
//unsigned char Uart1TX_Len;
//unsigned char u8U1txDATA[UART1txDNUM] = {0xAC,0x01,0x01,0x39,0x00,0x3B};

unsigned char u8uart3delay;
unsigned char Uart3TXp;
unsigned char Uart3TXuncomp;
unsigned char Uart3TX_Len;
unsigned char u8U3txDATA[UART3txDNUM] = {0xAC,0x03,0x05,100,0,0x3f,0x86,0x21,0x01,0x8b};

void uartxvaluinit(void);
void uartxinit(void);
void uartfunc(void);

void uartDisable1(void);
void uartEnable1(void);
//PB6: UART1_TX.
//PB7: UART1_RX (Internal weak pull-up).

//PB10: UART3_TX.




void uartxvaluinit(void){
	
//	Uart1TXp = 0;
//	Uart1TXuncomp = 0;
//	Uart1TX_Len = 0;
//	u8uart1delay = 0;
	
	u8uart3delay = TIME10MS_50MS;
//	Uart3TXp = 0;
//	Uart3TXuncomp = 0;
//	Uart3TX_Len = 0;
	
	//memset(&u8U1txDATA,0,UART1txDNUM);
	//memset(&u8U3txDATA,0,UART3txDNUM);
}

void uartxinit(void){
	/* USART configure */
    usart_deinit(USART0);
    usart_baudrate_set(USART0, 9600);
    usart_receive_config(USART0, USART_RECEIVE_DISABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
	
	
    usart_enable(USART0);
	nvic_irq_enable(USART0_IRQn, 2U, 0U);
//	usart_interrupt_enable(USART0,USART_INT_TBE);
}

void uartfunc(void){
	unsigned short int tempsum;
//	//1======================================
//	if(u8uart1delay >= TIME10MS_100MS){
//		u8uart1delay = 0;
//		if(Uart1TXuncomp == 0){
//			Uart1TXuncomp = 1;
//			u8U1txDATA[3] = u16Mmotor_PWM_duty;
//			u8U1txDATA[5] = u8U1txDATA[3] + 2;
//			Uart1TX_Len = 6;
//			Uart1TXp = 0;---------------------------
//			md_uart_enable_it_tfempty(UART1);
//		}
//	}
		
	//3======================================
	if(u8uart3delay >= TIME1MS_100MS){
		u8uart3delay = 0;
		if(Uart3TXuncomp == 0)
		{
			Uart3TXuncomp = 1;
			
			tempsum = 0;
			for(unsigned char i = 1;i<=7;i++){
				tempsum+= u8U3txDATA[i];
			}
			u8U3txDATA[8] = tempsum/256;
			u8U3txDATA[9] = tempsum%256;
			Uart3TX_Len = 10;
			Uart3TXp = 0;
			
			usart_interrupt_enable(USART0,USART_INT_TBE);
		}
	}
		
	
}

//void UART1_IRQHandler(void)         /*  IRQ 27 */
//{
//	md_uart_clear_it_tbc(UART1);
//	if (md_uart_is_active_it_tfempty(UART1)) {
//		md_uart_clear_it_tfempty(UART1);
//		
//		if(Uart1TXp >= Uart1TX_Len){
//			md_uart_disable_it_tfempty(UART1);
//			while (!READ_BIT(UART1->STAT,UART_STAT_TFEMPTY));
//			Uart1TXuncomp = 0;
//			Uart1TXp = 0;
//			Uart1TX_Len = 0;
//		}else{
//			UART1->TXDATA = u8U1txDATA[Uart1TXp++];
//		}
//	}
//}
/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(USART0, (uint8_t)ch);
    while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
    return ch;
}

void USART0_IRQHandler(void)     /*  IRQ 29  */
{
	
	if (usart_flag_get(USART0 ,USART_FLAG_TBE)) {
		usart_flag_clear(USART0 ,USART_FLAG_TBE);
		
		if(Uart3TXp >= Uart3TX_Len){
			while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
			Uart3TXuncomp = 0;
			Uart3TXp = 0;
			Uart3TX_Len = 0;
			usart_interrupt_disable(USART0,USART_INT_TBE);
		}else{
			usart_data_transmit(USART0, u8U3txDATA[Uart3TXp++]);
		}
	}
}
