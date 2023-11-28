#include "config.h"

/* Configure MCO (PA8) Set PA8 Output SYSCLK/2.*/

//private-----------------------------
void Gpio_MCOout_init(void);
void Gpio_Uart_out_init(void);
void Gpio_IIC_SCCB_init(void);
void Gpio_SPI_LCD_init(void);
void Gpio_DCMI_init(void);
//public------------------------------

void GpioxInit(void);
//==============================================================
void Gpio_MCOout_init(void){//AF PP NP
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	RCC_MCO1Config(RCC_MCO1Source_HSE, RCC_MCO1Div_1);
}
//==============================================================
void Gpio_Uart_out_init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_PinAFConfig(Open207_USART_TX_GPIO_PORT, Open207_USART_TX_SOURCE, Open207_USART_TX_AF);
	GPIO_PinAFConfig(Open207_USART_RX_GPIO_PORT, Open207_USART_RX_SOURCE, Open207_USART_RX_AF);
	/*
	*  Open207_USART_TX -> PC10 , Open207_USART_RX -PC11
	*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = Open207_USART_TX_PIN;
	GPIO_Init(Open207_USART_TX_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = Open207_USART_RX_PIN;
	GPIO_Init(Open207_USART_TX_GPIO_PORT, &GPIO_InitStructure);
}
//==============================================================
void Gpio_IIC_SCCB_init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_PinAFConfig(Open207_SCCB_SDA_GPIO_PORT, Open207_SCCB_SDA_SOURCE, Open207_SCCB_SDA_AF);
	GPIO_PinAFConfig(Open207_SCCB_SCL_GPIO_PORT, Open207_SCCB_SCL_SOURCE, Open207_SCCB_SCL_AF);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	//AF PP PU //U3 tx
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_InitStructure.GPIO_Pin =  Open207_SCCB_SCL_PIN;
	GPIO_Init(Open207_SCCB_SCL_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  Open207_SCCB_SDA_PIN;
	GPIO_Init(Open207_SCCB_SDA_GPIO_PORT, &GPIO_InitStructure);
}
//==============================================================
void Gpio_SPI_LCD_init(void){//AF PP PU
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);
 	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 |GPIO_Pin_4 |GPIO_Pin_5;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//CS DC BKL RST---------------------------------------------
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 |GPIO_Pin_9 |GPIO_Pin_10 |GPIO_Pin_11;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	LCD_BKL_L();
	LCD_RST_H();
	LCD_DC_H();
	LCD_CS_H();
	
	//TOUCH=============================================================
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}
//==========================================================================
void Gpio_DCMI_init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	/* Connect DCMI pins to AF13 ************************************************/
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_DCMI);//HSYNC 
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_DCMI);//PCLK
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_DCMI);//VSYNC
	//RED	
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_DCMI);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_DCMI);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_DCMI);
	//Blue
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_DCMI);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource4, GPIO_AF_DCMI);	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_DCMI);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_DCMI);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_DCMI);
	/*
	D0 -- PC6
	D1 -- PA10
	D2 -- PC8
	D3 -- PC9
	D4 -- PE4
	D5 -- PB6
	D6 -- PE5
	D7 -- PE6

	PCK - PA6
	HS -- PA4
	VS -- PB7
	*/
	/* DCMI GPIO configuration **************************************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_10 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;  
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_4;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* PCLK(PA6) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
//==========================================================================
void GpioxInit(void){
//af
	//uart3-------------------------
	Gpio_Uart_out_init();
	//spi1---------------------------
	Gpio_SPI_LCD_init();
	Gpio_MCOout_init();
	//I2S
	Gpio_IIC_SCCB_init();
	//DCMI
	Gpio_DCMI_init();
}
