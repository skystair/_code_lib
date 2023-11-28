/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IIC_H
#define __IIC_H

#define DELAY_5US()	delay(5)


//IIC=========================================================================
#define SCL_H()				HAL_GPIO_WritePin(IIC_SCL_PORT, IIC_SCL_PIN, GPIO_PIN_SET)
#define SCL_L()				HAL_GPIO_WritePin(IIC_SCL_PORT, IIC_SCL_PIN, GPIO_PIN_RESET)
#define SDA_H()				HAL_GPIO_WritePin(IIC_SDA_PORT, IIC_SDA_PIN, GPIO_PIN_SET)
#define SDA_L()				HAL_GPIO_WritePin(IIC_SDA_PORT, IIC_SDA_PIN, GPIO_PIN_RESET)

#define IIC_SCL_ON()		SCL_H()
#define IIC_SCL_OFF()		SCL_L()
#define IIC_SDA_ON()		SDA_H()
#define IIC_SDA_OFF()		SDA_L()

#define READ_SDA()			HAL_GPIO_ReadPin(IIC_SDA_PORT,IIC_SDA_PIN)
#define READ_SCL()			HAL_GPIO_ReadPin(IIC_SCL_PORT,IIC_SCL_PIN)

#define SDA_OUT()			GPIO_OUT_PP(IIC_SDA_PORT,IIC_SDA_PIN)
#define SDA_IN()			GPIO_Input(IIC_SDA_PORT,IIC_SDA_PIN)

#define SCL_OUT()			GPIO_OUT_PP(IIC_SCL_PORT,IIC_SCL_PIN)
#define SCL_IN()			GPIO_Input(IIC_SCL_PORT,IIC_SCL_PIN)


extern void delay(unsigned int n);
extern void IIC_Init(void);
extern void IIC_Start(void);
extern void IIC_Stop(void);
extern unsigned char IIC_Wait_Ack(void);
extern void IIC_Ack(void);
extern void IIC_NAck(void);
extern void IIC_Send_Byte(unsigned char  txd);
extern unsigned char IIC_Read_Byte(unsigned char ack);
#endif


