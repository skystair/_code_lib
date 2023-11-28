#include "config.h"

void RCCxEnable(void);
void valueinit(void);
void BSPinit(void);
void I2Cxinit(void);
void SPIxinit(void);
void DCMI_Config(void);


void RCCxEnable(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE); 
	
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
}

void valueinit(void){
	Uart3TXvalueinit();
}
void BSPinit(void){
	RCCxEnable();
	
	GpioxInit();
	SPIxinit();
	I2Cxinit();
	DCMI_Config();
//	uartxinit();
}

void I2Cxinit(void){
	I2C_InitTypeDef  SCCB_InitStructure;
	I2C_DeInit(Open207_SCCB);
	SCCB_InitStructure.I2C_Mode = I2C_Mode_I2C;
	SCCB_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	SCCB_InitStructure.I2C_OwnAddress1 = SCCB_SLAVE_ADDRESS7;
	SCCB_InitStructure.I2C_Ack = I2C_Ack_Enable;
	SCCB_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	SCCB_InitStructure.I2C_ClockSpeed = SCCB_SPEED;
	
	I2C_Cmd(Open207_SCCB, ENABLE);
	I2C_Init(Open207_SCCB, &SCCB_InitStructure);
	
	I2C_AcknowledgeConfig(Open207_SCCB, ENABLE);	
}
void SPIxinit(void){
	SPI_InitTypeDef SPI_InitStructure;
	
//	SPI_I2S_DeInit(SPI1);
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(SPI1, &SPI_InitStructure); 
	SPI_Cmd(SPI1, ENABLE);
	
}
void DCMI_Config(void)
{
	DCMI_InitTypeDef DCMI_InitStructure;
	DMA_InitTypeDef  DMA_InitStructure;
	
	NVIC_InitTypeDef NVIC_InitStructure;
	/* DCMI configuration *******************************************************/ 
	DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;
	DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
	DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Falling;
	DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_High;
	DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_High;
	DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
	DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;
	DCMI_Init(&DCMI_InitStructure);

	/* DCMI Interrupts config ***************************************************/
	DCMI_ITConfig(DCMI_IT_VSYNC, ENABLE);
	//DCMI_ITConfig(DCMI_IT_LINE, ENABLE);
	//DCMI_ITConfig(DCMI_IT_FRAME, ENABLE);
	//DCMI_ITConfig(DCMI_IT_ERR, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = DCMI_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	NVIC_Init(&NVIC_InitStructure);
	/* Configures the DMA2 to transfer Data from DCMI to the LCD ****************/	
  /* DMA2 Stream1 Configuration */  
	DMA_DeInit(DMA2_Stream1);
	DMA_InitStructure.DMA_Channel = DMA_Channel_1;  
	DMA_InitStructure.DMA_PeripheralBaseAddr = DCMI_DR_ADDRESS;	
	DMA_InitStructure.DMA_Memory0BaseAddr = (unsigned int)(&LCDdata);//FSMC_LCD_ADDRESS;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = 240;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//DMA_MemoryInc_Enable;//DMA_MemoryInc_Disable
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA_Mode_Normal;//
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;//DMA_FIFOMode_Disable;//
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream1, &DMA_InitStructure); 
	
	DMA_DeInit(DMA1_Stream2);
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;  
	DMA_InitStructure.DMA_PeripheralBaseAddr = SPI1_DR_ADDRESS;	
	DMA_InitStructure.DMA_Memory0BaseAddr = (unsigned int)&LCDdata;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize = 240;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//DMA_MemoryInc_Enable;//DMA_MemoryInc_Disable
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_MemoryDataSize_HalfWord;//DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA_Mode_Normal;//
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;//DMA_FIFOMode_Disable;//
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA1_Stream2, &DMA_InitStructure); 
}