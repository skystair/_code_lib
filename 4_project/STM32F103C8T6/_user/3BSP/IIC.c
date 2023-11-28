#include "config.h"

void delay(unsigned int n);
void GPIO_OUT_PP(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void GPIO_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
unsigned char IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NAck(void);
void IIC_Send_Byte(unsigned char  txd);
unsigned char IIC_Read_Byte(unsigned char ack);


void delay(unsigned int n){	//0.94us/n
	n = n * 6;
	for(; n > 0 ; n--)
	{
		__NOP();
	}
}
void GPIO_OUT_PP(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	
	GPIO_InitStruct.Pin = GPIO_Pin;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void GPIO_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	
	GPIO_InitStruct.Pin = GPIO_Pin;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}


void IIC_Init(void)
{
	SDA_H();
	SCL_H();
	SDA_OUT();
	SCL_OUT();
	SDA_H();
	SCL_H();
}

void IIC_Start(void)
{
	SDA_OUT();//sda线输出
	
	IIC_SDA_ON();
	IIC_SCL_ON();
	DELAY_5US();
	
	IIC_SDA_OFF();
	DELAY_5US();
	
	IIC_SCL_OFF();
	DELAY_5US();
}

void IIC_Stop(void)
{
	SDA_OUT();
	IIC_SCL_OFF();
	IIC_SDA_OFF();
 	DELAY_5US();
	IIC_SCL_ON();
	DELAY_5US();
	IIC_SDA_ON();
	DELAY_5US();
}

//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
unsigned char IIC_Wait_Ack(void)
{
	uint32_t ucErrTime=0;

    SDA_IN();      //SDA设置为输入  
    IIC_SDA_ON();DELAY_5US();   
    IIC_SCL_ON();DELAY_5US();
    while(READ_SDA())
    {
        ucErrTime++;
    //		HAL_Delay_us(10);
        if(ucErrTime>2500)
        {
            IIC_Stop();
//            eehError=0; 
            return 1;
        }
    }
	IIC_SCL_OFF();//时钟输出0 	
//	eehError=1;
	return 0;  
}

//产生ACK应答
void IIC_Ack(void)
{
    IIC_SCL_OFF();
    SDA_OUT();
    IIC_SDA_OFF();
    DELAY_5US();
    IIC_SCL_ON();
    DELAY_5US();
    IIC_SCL_OFF();
}

//不产生ACK应答		    
void IIC_NAck(void)
{

    IIC_SCL_OFF();
    SDA_OUT();
    IIC_SDA_ON();
    DELAY_5US();
    IIC_SCL_ON();
    DELAY_5US();
    IIC_SCL_OFF();

}			

//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(unsigned char  txd)
{                        
	static uint8_t t;
	static uint8_t data;

	data = txd;
	SDA_OUT();
	IIC_SCL_OFF();//拉低时钟开始数据传输
	for(t=0;t<8;t++)
	{
		if(data&0x80)
		{
			IIC_SDA_ON();
		}
		else
		{
			IIC_SDA_OFF();
		}
		data<<=1;
		DELAY_5US(); 
		IIC_SCL_ON();
		DELAY_5US();
		IIC_SCL_OFF();	
		DELAY_5US();
	}

} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
unsigned char IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
		SDA_IN();//SDA设置为输入
		for(i=0;i<8;i++ )
		{
			IIC_SCL_OFF(); 
			DELAY_5US();
			IIC_SCL_ON();
			receive<<=1;
			if(READ_SDA())receive++;   
			DELAY_5US(); 
		}					 
		if (!ack)
				IIC_NAck();//发送nACK
		else
				IIC_Ack(); //发送ACK 

    return receive;
}

