#include "config.h"


void Bsp_Usart_Config(void)
{
	USART_InitType USART_InitStructure;

		/* USART3 configuration ------------------------------------------------------*/
    USART_InitStructure.BaudRate            = 9600;
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX;

    /* Configure USARTy and USARTz */
    USART_Init(USART3, &USART_InitStructure);    /* Enable USARTy Receive and Transmit interrupts */
    USART_ConfigInt(USART3, USART_INT_RXDNE, ENABLE);    /* Enable the USARTy */
    USART_Enable(USART3, ENABLE);

}

void NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;

    /* Enable the USARTy Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = USART3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}

void Bsp_Usart_Init(void)
{
	Bsp_Usart_Config();
	NVIC_Configuration();
}



