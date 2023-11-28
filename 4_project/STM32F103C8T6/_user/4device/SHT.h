#ifndef __SHT_H
#define __SHT_H


#define HT_TEMP_MIN		-40.0F
#define HT_TEMP_MAX		150.0F
#define HT_HUMIT_MIN	0.0F
#define HT_HUMIT_MAX	100.0F

#define delay_ms			HAL_Delay
#define IIC_HT_Start		IIC_Start
#define IIC_HT_WriteByte	IIC_Send_Byte
#define IIC_HT_ReadAck		IIC_Wait_Ack
#define IIC_HT_Stop			IIC_Stop
#define IIC_HT_ReadByte		IIC_Read_Byte
#define IIC_HT_sendAck		IIC_Ack



extern unsigned char u8HTfailFlag;
//extern unsigned char HTnum;

extern float Centi;		//环境实时温度
extern float Humidity;	//环境实时湿度

extern void SHT31_valueInit(void);
extern void Deal_HT(void);

#endif
