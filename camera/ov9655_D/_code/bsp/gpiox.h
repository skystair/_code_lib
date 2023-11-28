#ifndef __GPIOX_H__
#define __GPIOX_H__


#define LCD_BKL_H()    GPIO_SetBits(GPIOD, GPIO_Pin_8)
#define LCD_BKL_L()    GPIO_ResetBits(GPIOD, GPIO_Pin_8)

#define LCD_RST_H()    GPIO_SetBits(GPIOD, GPIO_Pin_9)
#define LCD_RST_L()    GPIO_ResetBits(GPIOD, GPIO_Pin_9)

#define LCD_DC_H()		GPIO_SetBits(GPIOD,GPIO_Pin_10)
#define LCD_DC_L()		GPIO_ResetBits(GPIOD,GPIO_Pin_10)

#define LCD_CS_H()		GPIO_SetBits(GPIOD,GPIO_Pin_11)
#define LCD_CS_L()		GPIO_ResetBits(GPIOD,GPIO_Pin_11)


 /* Configure I2C1 pins: PB10->SIOC and PB11->SIOD */ 
#define Open207_SCCB                        	I2C2
#define Open207_SCCB_CLK                    	RCC_APB1Periph_I2C2

#define Open207_SCCB_SDA_PIN                 	GPIO_Pin_10
#define Open207_SCCB_SDA_GPIO_PORT           	GPIOB
#define Open207_SCCB_SDA_GPIO_CLK            	RCC_AHB1Periph_GPIOB
#define Open207_SCCB_SDA_SOURCE              	GPIO_PinSource10
#define Open207_SCCB_SDA_AF                  	GPIO_AF_I2C2

#define Open207_SCCB_SCL_PIN                 	GPIO_Pin_11
#define Open207_SCCB_SCL_GPIO_PORT           	GPIOB
#define Open207_SCCB_SCL_GPIO_CLK            	RCC_AHB1Periph_GPIOB
#define Open207_SCCB_SCL_SOURCE              	GPIO_PinSource11
#define Open207_SCCB_SCL_AF                  	GPIO_AF_I2C2
//------------------------------------------------------------------
#define Open207_USART                        USART3
#define Open207_USART_CLK                    RCC_APB1Periph_USART3

#define Open207_USART_TX_PIN                 GPIO_Pin_10
#define Open207_USART_TX_GPIO_PORT           GPIOC
#define Open207_USART_TX_GPIO_CLK            RCC_AHB1Periph_GPIOC
#define Open207_USART_TX_SOURCE              GPIO_PinSource10
#define Open207_USART_TX_AF                  GPIO_AF_USART3

#define Open207_USART_RX_PIN                 GPIO_Pin_11
#define Open207_USART_RX_GPIO_PORT           GPIOC
#define Open207_USART_RX_GPIO_CLK            RCC_AHB1Periph_GPIOC
#define Open207_USART_RX_SOURCE              GPIO_PinSource11
#define Open207_USART_RX_AF                  GPIO_AF_USART3

#define Open207_USART_IRQn                   USART3_IRQn











extern void GpioxInit(void);

#endif
