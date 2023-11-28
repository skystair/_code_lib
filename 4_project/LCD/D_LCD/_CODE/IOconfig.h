#ifndef __IOCONFIG_H__
#define __IOCONFIG_H__


#define DMA_DELAY		0

//outpp-------------------------------------------------------------------
	//led ring, R(PB1) G(PA10)
#define LED_CHANGE_GPIO		1

#define LED_RED_PORT		GPIOB
#define LED_RED_PIN			GPIO_PIN_1

#if LED_CHANGE_GPIO
	#define LED_GREEN_PORT	GPIOA
	#define LED_GREEN_PIN	GPIO_PIN_10
		
#else
	#define LED_GREEN_PORT	GPIOB
	#define LED_GREEN_PIN	GPIO_PIN_2
#endif

#define LED_RED_ON			GPIO_SetBits(LED_RED_PORT, LED_RED_PIN)
#define LED_RED_OFF			GPIO_ResetBits(LED_RED_PORT, LED_RED_PIN)
#define LED_GREEN_ON		GPIO_SetBits(LED_GREEN_PORT, LED_GREEN_PIN)
#define LED_GREEN_OFF		GPIO_ResetBits(LED_GREEN_PORT, LED_GREEN_PIN)

//AF=======================================================================
	//SPI2---------------------------------------------------------------
#define FLASH_SPI_SELCETED 2

#if FLASH_SPI_SELCETED == 1
	#define FLASH_SPI						SPI1

	#define FLASH_PORT_CS					GPIOA
	#define FLASH_PIN_CS					GPIO_PIN_4
	#define FLASH_PORT_MOSI					GPIOA
	#define FLASH_PIN_MOSI					GPIO_PIN_7
	#define FLASH_PORT_MISO					GPIOA
	#define FLASH_PIN_MISO					GPIO_PIN_6
	#define FLASH_PORT_CLK					GPIOA
	#define FLASH_PIN_CLK					GPIO_PIN_5

	#define FLASH_DMA						DMA1
	#define FLASH_TX_DMA					DMA1_CH3
	#define FLASH_RX_DMA					DMA1_CH2
	#define FLASH_DMA_TX_TC					DMA1_FLAG_TC3
	#define FLASH_DMA_RX_TC 				DMA1_FLAG_TC2

#elif FLASH_SPI_SELCETED == 2
	#define FLASH_SPI						SPI2

	#define FLASH_PORT_CS					GPIOB
	#define FLASH_PIN_CS					GPIO_PIN_12
	#define FLASH_PORT_MOSI					GPIOB
	#define FLASH_PIN_MOSI					GPIO_PIN_15
	#define FLASH_PORT_MISO					GPIOB
	#define FLASH_PIN_MISO					GPIO_PIN_14
	#define FLASH_PORT_CLK					GPIOB
	#define FLASH_PIN_CLK					GPIO_PIN_13

	#define FLASH_DMA						DMA1
	#define FLASH_TX_DMA					DMA1_CH5
	#define FLASH_RX_DMA					DMA1_CH4
	#define FLASH_DMA_TX_TC					DMA1_FLAG_TC5
	#define FLASH_DMA_RX_TC 				DMA1_FLAG_TC4

#endif

#define sFLASH_CS_LOW() GPIO_ResetBits(FLASH_PORT_CS, FLASH_PIN_CS)
#define sFLASH_CS_HIGH() GPIO_SetBits(FLASH_PORT_CS, FLASH_PIN_CS)

	//spi1------------------------------------------------------------------------
#define LCD_SPI_SELCETED 1
#if (LCD_SPI_SELCETED == 1)
	#define LCD_SPI								SPI1

	#define LCD_PORT_CS						GPIOA
	#define LCD_PIN_CS						GPIO_PIN_4
	#define LCD_PORT_MOSI					GPIOA
	#define LCD_PIN_MOSI					GPIO_PIN_7
	#define LCD_PORT_MISO					GPIOA
	#define LCD_PIN_MISO					GPIO_PIN_6
	#define LCD_PORT_CLK					GPIOA
	#define LCD_PIN_CLK						GPIO_PIN_5
	#define LCD_PORT_DC						GPIOA
	#define LCD_PIN_DC						GPIO_PIN_3
	#define LCD_PORT_RST					GPIOB
	#define LCD_PIN_RST						GPIO_PIN_0

	#define LCD_DMA								DMA1
	#define LCD_TX_DMA						DMA1_CH3
	#define LCD_RX_DMA						DMA1_CH2
	#define LCD_DMA_TX_TC					DMA1_FLAG_TC3
	#define LCD_DMA_RX_TC 				DMA1_FLAG_TC2
	#define LCD_DMA_TX_IRQ				DMA1_Channel3_IRQn
	#define LCD_DMA_RX_IRQ				DMA1_Channel2_IRQn

	#define LCD_DMA_CLK						RCC_AHB_PERIPH_DMA1
	#define LCD_GPIO_CLK					RCC_APB2_PERIPH_GPIOA|RCC_APB2_PERIPH_AFIO
	#define LCD_SPI_CLK_ENABLE()	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_SPI1, ENABLE)

#elif (LCD_SPI_SELCETED == 2)
	#define LCD_SPI								SPI2

	#define LCD_PORT_CS						GPIOB
	#define LCD_PIN_CS						GPIO_PIN_12
	#define LCD_PORT_MOSI					GPIOB
	#define LCD_PIN_MOSI					GPIO_PIN_15
	#define LCD_PORT_MISO					GPIOB
	#define LCD_PIN_MISO					GPIO_PIN_14
	#define LCD_PORT_CLK					GPIOB
	#define LCD_PIN_CLK						GPIO_PIN_13
	#define LCD_PORT_DC						GPIOA
	#define LCD_PIN_DC						GPIO_PIN_10
	#define LCD_PORT_RST					GPIOB
	#define LCD_PIN_RST						GPIO_PIN_0


	#define LCD_DMA								DMA1
	#define LCD_TX_DMA						DMA1_CH5
	#define LCD_RX_DMA						DMA1_CH4
	#define LCD_DMA_TX_TC					DMA1_FLAG_TC5//DMA1_INT_TXC5
	#define LCD_DMA_RX_TC 				DMA1_FLAG_TC4
	#define LCD_DMA_TX_TXC				DMA1_INT_TXC5
	#define LCD_DMA_RX_TXC 				DMA1_INT_TXC4
	#define LCD_DMA_TX_IRQ				DMA1_Channel5_IRQn
	#define LCD_DMA_RX_IRQ				DMA1_Channel4_IRQn

	#define LCD_DMA_CLK						RCC_AHB_PERIPH_DMA1
	#define LCD_GPIO_CLK					RCC_APB2_PERIPH_GPIOB|RCC_APB2_PERIPH_GPIOA|RCC_APB2_PERIPH_AFIO
	#define LCD_SPI_CLK_ENABLE()	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_SPI2, ENABLE)

#endif

#define LCD_CS_CLR() GPIO_ResetBits(LCD_PORT_CS, LCD_PIN_CS)
#define LCD_CS_SET() GPIO_SetBits(LCD_PORT_CS, LCD_PIN_CS)

#define LCD_DC_CLR() GPIO_ResetBits(LCD_PORT_DC, LCD_PIN_DC)
#define LCD_DC_SET() GPIO_SetBits(LCD_PORT_DC, LCD_PIN_DC)

#define LCD_RST_CLR() GPIO_ResetBits(LCD_PORT_RST, LCD_PIN_RST)
#define LCD_RST_SET() GPIO_SetBits(LCD_PORT_RST, LCD_PIN_RST)
	//----------------------------------------------
#define USART3_TX_PORT	GPIOB
#define USART3_TX_PIN	GPIO_PIN_10

#define USART3_RX_PORT	GPIOB
#define USART3_RX_PIN	GPIO_PIN_11
	//----------------------------------------------
#define PWM_BL_PORT		GPIOA
#define PWM_BL_PIN		GPIO_PIN_8


#endif

