#ifndef __BOARDIO_H
#define __BOARDIO_H


#define TEST_LED_Pin		GPIO_PIN_2
#define TEST_LED_GPIO_Port	GPIOB
#define TEST_KEY_Pin		GPIO_PIN_0
#define TEST_KEY_GPIO_Port	GPIOA


#define PWM_FAN_Pin			GPIO_PIN_1
#define PWM_FAN_GPIO_Port	GPIOA
#define FB_FAN_Pin			GPIO_PIN_2
#define FB_FAN_GPIO_Port	GPIOA

//SPI1
#define SPI1_SCK_Pin 				GPIO_PIN_5	//CLK
#define SPI1_SCK_GPIO_Port 			GPIOA
#define SPI1_MISO_Pin 				GPIO_PIN_6
#define SPI1_MISO_GPIO_Port 		GPIOA
#define SPI1_MOSI_Pin 				GPIO_PIN_7	//DIN
#define SPI1_MOSI_GPIO_Port 		GPIOA

#define OLED_DC_Pin 				GPIO_PIN_6	//DC   ←A8
#define OLED_DC_GPIO_Port 			GPIOA
#define OLED_RST_Pin 				GPIO_PIN_3	//RST  ←A9
#define OLED_RST_GPIO_Port 			GPIOA
#define OLED_CS_Pin 				GPIO_PIN_4	//CS   ←B6
#define OLED_CS_GPIO_Port 			GPIOA

#define OLED_SW_Pin					GPIO_PIN_15
#define OLED_SW_GPIO_Port			GPIOA
//SPI2
#define SPI2_SCK_Pin 				GPIO_PIN_13	//CLK
#define SPI2_SCK_GPIO_Port 			GPIOB
#define SPI2_MISO_Pin 				GPIO_PIN_14 //DOUT
#define SPI2_MISO_GPIO_Port 		GPIOB
#define SPI2_MOSI_Pin 				GPIO_PIN_15	//DIN
#define SPI2_MOSI_GPIO_Port 		GPIOB

#define SPI2_NSS_Pin 				GPIO_PIN_12	//CS
#define SPI2_NSS_GPIO_Port 			GPIOB



#define IIC_SCL_SOFT_Pin 			GPIO_PIN_6
#define IIC_SCL_SOFT_GPIO_Port		GPIOC
#define IIC_SDA_SOFT_Pin			GPIO_PIN_8
#define IIC_SDA_SOFT_GPIO_Port		GPIOC


#define GR_Pin				GPIO_PIN_3
#define GR_GPIO_Port		GPIOB
#define GG_Pin				GPIO_PIN_4
#define GG_GPIO_Port		GPIOB
#define GB_Pin				GPIO_PIN_5
#define GB_GPIO_Port		GPIOB

#define IIC_SCL_PIN			GPIO_PIN_6
#define IIC_SCL_PORT		GPIOB
#define IIC_SDA_PIN			GPIO_PIN_7
#define IIC_SDA_PORT		GPIOB

#define OPT_FB_Pin			GPIO_PIN_8
#define OPT_FB_GPIO_Port	GPIOB
#define OPT_CTL_Pin			GPIO_PIN_9
#define OPT_CTL_GPIO_Port	GPIOB



  /*PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */












#endif
