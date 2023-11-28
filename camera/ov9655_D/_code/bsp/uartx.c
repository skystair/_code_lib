#include "config.h"

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

void uartxRXNEIE(USART_TypeDef* USARTx, FunctionalState NewState);
void uartxTXEIE(USART_TypeDef* USARTx, FunctionalState NewState);
void uartxvaluinit(void);
void uartxDelayADD(void);
void uartxinit(void);
void uartfunc(void);
 
void uartxRXNEIE(USART_TypeDef* USARTx, FunctionalState NewState){
	if (NewState != DISABLE){
		USARTx->CR1 |= USART_CR1_RXNEIE;
	}else{
		USARTx->CR1 &= (uint16_t)~((uint16_t)USART_CR1_RXNEIE);
	}
}
void uartxTXEIE(USART_TypeDef* USARTx, FunctionalState NewState){
	if (NewState != DISABLE){
		USARTx->CR1 |= USART_CR1_TXEIE;
	}else{
		USARTx->CR1 &= (uint16_t)~((uint16_t)USART_CR1_TXEIE);
	}
}
void uartxvaluinit(void){
	
}

void uartxDelayADD(void){
	
}
void uartxinit(void){
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);
	
//	uartxTXEIE(USART3, DISABLE);
//	uartxRXNEIE(USART3, ENABLE);
	
	USART_Cmd(USART3, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void uartfunc(void){
	
}


///* Use no semihosting */
//#if 1
//#pragma import(__use_no_semihosting)
//struct __FILE
//{  
//	int handle;
//};
//FILE __stdout;

//_sys_exit(int x)
//{
//	x = x;
//}
//#endif

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART3, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
  {}

  return ch;
}


