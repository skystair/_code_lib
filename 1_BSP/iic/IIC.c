#include "config.h"

void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
unsigned char IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NAck(void);
void IIC_Send_Byte(unsigned char  txd);
unsigned char IIC_Read_Byte(unsigned char ack);



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
	SDA_H();
	SDA_OUT();//sda线输出

	SCL_H();
	delay_1us(6);
	
	SDA_L();
	delay_1us(6);
	SCL_L();
//	delay_1us(3);
}

void IIC_Stop(void)
{
	SDA_L();
	SDA_OUT();
	SCL_L();
 	delay_1us(6);
	SCL_H();
	delay_1us(6);
	SDA_H();
	delay_1us(6);
}

//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
unsigned char IIC_Wait_Ack(void)
{
	uint32_t ucErrTime=0;
//	SDA_IN();      //SDA设置为输入
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
	SDA_L();
	SDA_OUT();
	
	SCL_L();
	delay_1us(1);
	SCL_H();
	delay_1us(5);
	SCL_L();
    
	delay_1us(2);
//	SCL_L();//时钟输出0 	
//	eehError=1;
	SDA_IN();
	return 0;  
}

//产生ACK应答
void IIC_Ack(void)
{
    SCL_L();
	delay_1us(6);
	SDA_L();
    SDA_OUT();
    delay_1us(6);
    SCL_H();
    delay_1us(6);
    SCL_L();
	delay_1us(6);
	SDA_IN();
}

//不产生ACK应答		    
void IIC_NAck(void)
{

    SCL_L();
	delay_1us(6);
    SDA_IN();
    delay_1us(6);
    SCL_H();
    delay_1us(6);
    SCL_L();
	delay_1us(6);

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
	SDA_H();
	SDA_OUT();
	
	SCL_L();//拉低时钟开始数据传输
	for(t=0;t<8;t++)
	{
		if(data&0x80)
		{
			SDA_H();
		}
		else
		{
			SDA_L();
		}
		delay_1us(2);
		SCL_H();
		delay_1us(6);
		SCL_L();
		delay_1us(2);
		data<<=1;
	}
	SDA_IN();
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
unsigned char IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
		//SDA_IN();//SDA设置为输入
		for(i=0;i<8;i++ )
		{
			SCL_L(); 
			delay_1us(6);
			SCL_H();
			receive<<=1;
			delay_1us(3); 
			if(READ_SDA())receive++;   
			delay_1us(3);
		}
		SCL_L();
		if (!ack)
				IIC_NAck();//发送nACK
		else
				IIC_Ack(); //发送ACK 

    return receive;
}

