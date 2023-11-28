#include "config.h"


void MX_GPIO_Init(void);


void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

//下拉输入===================================================
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	
	GPIO_InitStruct.Pin = TEST_KEY_Pin;
	HAL_GPIO_Init(TEST_KEY_GPIO_Port, &GPIO_InitStruct);
	
//推挽输出===================================================
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	
	//test LED
	GPIO_InitStruct.Pin = TEST_LED_Pin;
	HAL_GPIO_Init(TEST_LED_GPIO_Port, &GPIO_InitStruct);
	//iic
	GPIO_InitStruct.Pin = IIC_SCL_PIN;
	HAL_GPIO_Init(IIC_SCL_PORT, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = IIC_SDA_PIN;
	HAL_GPIO_Init(IIC_SDA_PORT, &GPIO_InitStruct);
	//SPI1_CS+RST+DC
	HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, GPIO_PIN_RESET);
	
	GPIO_InitStruct.Pin = OLED_DC_Pin;
	HAL_GPIO_Init(OLED_DC_GPIO_Port, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = OLED_RST_Pin;
	HAL_GPIO_Init(OLED_RST_GPIO_Port, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = OLED_CS_Pin;
	HAL_GPIO_Init(OLED_CS_GPIO_Port, &GPIO_InitStruct);
	//spi2 CS
	HAL_GPIO_WritePin(SPI2_NSS_GPIO_Port, SPI2_NSS_Pin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = SPI2_NSS_Pin;
	HAL_GPIO_Init(SPI2_NSS_GPIO_Port, &GPIO_InitStruct);

/**TIM2 GPIO Configuration=======================================
    PA1     ------> TIM2_CH2 
    */
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pin = PWM_FAN_Pin;
    HAL_GPIO_Init(PWM_FAN_GPIO_Port, &GPIO_InitStruct);
	
	
//USART1 GPIO Configuration====================================
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  /*PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
//SPI1 GPIO Configuration=======================================
/*  PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI 
    */
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_7;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

//	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//    GPIO_InitStruct.Pin = GPIO_PIN_6;
//    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/**SPI2 GPIO Configuration=======================================
// 
    PB13     ------> SPI2_SCK
    PB14     ------> SPI2_MISO
    PB15     ------> SPI2_MOSI 
    */
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_15;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pin = GPIO_PIN_14;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	
}







