/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IIC_H
#define __IIC_H

#define DELAY_5US()	delay_1us(6)

#define IIC_SCL_PORT	PORT_HWEXIT	//b13
#define IIC_SCL_PIN		PIN_HWEXIT

#define IIC_SDA_PORT	PORT_MOTFG	//b9
#define IIC_SDA_PIN		PIN_MOTFG
//IIC=========================================================================
#define SCL_H()				gpio_bit_set(IIC_SCL_PORT, IIC_SCL_PIN)
#define SCL_L()				gpio_bit_reset(IIC_SCL_PORT, IIC_SCL_PIN)
#define SDA_H()				gpio_bit_set(IIC_SDA_PORT, IIC_SDA_PIN)
#define SDA_L()				gpio_bit_reset(IIC_SDA_PORT, IIC_SDA_PIN)


#define READ_SDA()			gpio_input_bit_get(IIC_SDA_PORT,IIC_SDA_PIN)
#define READ_SCL()			gpio_input_bit_get(IIC_SCL_PORT,IIC_SCL_PIN)

#define SDA_OUT()			GPIO_CTL(GPIOB) |= BIT(18)
#define SDA_IN()			GPIO_CTL(GPIOB) &= (~BIT(18))

#define SCL_OUT()			gpio_mode_set(PORT_HWEXIT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_HWEXIT);gpio_output_options_set(PORT_HWEXIT, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, PIN_HWEXIT)
#define SCL_IN()			gpio_mode_set(PORT_HWEXIT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, PIN_HWEXIT)

extern void IIC_Init(void);
extern void IIC_Start(void);
extern void IIC_Stop(void);
extern unsigned char IIC_Wait_Ack(void);
extern void IIC_Ack(void);
extern void IIC_NAck(void);
extern void IIC_Send_Byte(unsigned char  txd);
extern unsigned char IIC_Read_Byte(unsigned char ack);
#endif


