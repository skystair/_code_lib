#include "config.h"

void gpioinit(void);

void gpioinit(void){
	GPIO_InitType GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//outpp================================================
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	
		//1
	GPIO_InitStructure.Pin        = LED_RED_PIN;
	GPIO_InitPeripheral(LED_RED_PORT, &GPIO_InitStructure);
		//2
	GPIO_InitStructure.Pin        = LED_GREEN_PIN;
	GPIO_InitPeripheral(LED_GREEN_PORT, &GPIO_InitStructure);
		//3
	GPIO_InitStructure.Pin       = FLASH_PIN_CS;
    GPIO_InitPeripheral(FLASH_PORT_CS, &GPIO_InitStructure);
	sFLASH_CS_HIGH();
		//4
    GPIO_InitStructure.Pin       = LCD_PIN_CS;
    GPIO_InitPeripheral(LCD_PORT_CS, &GPIO_InitStructure);
	LCD_CS_SET();
		//5
    GPIO_InitStructure.Pin       = LCD_PIN_DC;
    GPIO_InitPeripheral(LCD_PORT_DC, &GPIO_InitStructure);
		//6
    GPIO_InitStructure.Pin       = LCD_PIN_RST;
    GPIO_InitPeripheral(LCD_PORT_RST, &GPIO_InitStructure);
	//in float=============================================
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		//1
	GPIO_InitStructure.Pin       = FLASH_PIN_MISO;
    GPIO_InitPeripheral(FLASH_PORT_MISO, &GPIO_InitStructure);
		//2
	/* Configure USARTy Rx as alternate function push-pull */
	GPIO_InitStructure.Pin       = USART3_RX_PIN;
    GPIO_InitPeripheral(USART3_RX_PORT, &GPIO_InitStructure);
	
	//AF===================================================
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	//spi2-----------------------------------------------
		//1
	GPIO_InitStructure.Pin        = FLASH_PIN_CLK;
    GPIO_InitPeripheral(FLASH_PORT_CLK, &GPIO_InitStructure);
		//2
    GPIO_InitStructure.Pin 			= FLASH_PIN_MOSI;
    GPIO_InitPeripheral(FLASH_PORT_MOSI, &GPIO_InitStructure);

	//spi1----------------------------------------------------
		//4
	GPIO_InitStructure.Pin        = LCD_PIN_CLK;
    GPIO_InitPeripheral(LCD_PORT_CLK, &GPIO_InitStructure);
		//5
    GPIO_InitStructure.Pin       = LCD_PIN_MOSI;
    GPIO_InitPeripheral(LCD_PORT_MOSI, &GPIO_InitStructure);
	
	//USART3--------------------------------------------------
		//8
    GPIO_InitStructure.Pin        = USART3_TX_PIN;
    GPIO_InitPeripheral(USART3_TX_PORT, &GPIO_InitStructure);  
		//9
	/* GPIOA Configuration: Channel 1 as alternate function push-pull */
    GPIO_InitStructure.Pin        = PWM_BL_PIN;
    GPIO_InitPeripheral(PWM_BL_PORT, &GPIO_InitStructure);
	
}


