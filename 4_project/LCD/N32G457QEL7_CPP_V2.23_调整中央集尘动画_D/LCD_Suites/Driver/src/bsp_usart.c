#include "bsp_usart.h"


void Bsp_Usart_Config(void)
{
		USART_InitType USART_InitStructure;
    GPIO_InitType GPIO_InitStructure; 
    /* Enable GPIO clock */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);
    /* Enable USARTy and USARTz Clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USART3, ENABLE);
    
    /* Configure USARTy Rx as input floating */
    GPIO_InitStructure.Pin       = GPIO_PIN_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    /* Configure USARTy Tx as alternate function push-pull */
    GPIO_InitStructure.Pin        = GPIO_PIN_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);    
	
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



