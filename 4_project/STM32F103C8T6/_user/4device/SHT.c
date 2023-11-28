#include "config.h"
//温湿度传感器*2（板载1+外接1）

unsigned char u8HTfailFlag;

//unsigned char ;

unsigned char Centi_H;
unsigned char Centi_L;
unsigned char RH_H;
unsigned char RH_L; 
	
float Centi;
float Humidity;

void SHT31_valueInit(void);
void Deal_HT(void);

void SHT31_valueInit(void){
	
	u8HTfailFlag = 1;
//	 = 0;
	Centi_H = 0;
	Centi_L = 0;
	RH_H = 0;
	RH_L = 0; 
		
	Centi = 0;
	Humidity = 0;
}

void Deal_HT(void){  
	
//开启测量(0x88 0x2c 0x06)--放SCL高1ms等测量--
	//start--0x89--ACK--SCL被模块拉低--温度H8-SACK-温度L8-SACK-CHKSUM-SACK-
									//湿度H8-SACK-湿度L8-SACK-CHKSUM-SNACK-stop
		
	IIC_HT_Start();
	IIC_HT_WriteByte(0x88);//WRITE
	IIC_HT_ReadAck();
	IIC_HT_WriteByte(0x2C);
	IIC_HT_ReadAck();
	IIC_HT_WriteByte(0x06);
	IIC_HT_ReadAck();
	
	IIC_HT_Stop();
	delay_ms(10);		//放SCL
	
	IIC_HT_Start();
	IIC_HT_WriteByte(0x89);//READ
	
	IIC_HT_Stop();
	delay_ms(10);		//放SCL
	
	IIC_HT_Start();
	IIC_HT_WriteByte(0x89);//READ
	IIC_HT_ReadAck();
	
	//温度
	Centi_H = IIC_HT_ReadByte(0);
	IIC_HT_sendAck();
	Centi_L = IIC_HT_ReadByte(0);
	IIC_HT_sendAck();
	//CHKSUM
	IIC_HT_ReadByte(0);//chksum
	IIC_HT_sendAck();
	
	//湿度
	RH_H = IIC_HT_ReadByte(0);
	IIC_HT_sendAck();
	RH_L = IIC_HT_ReadByte(0);
	IIC_HT_sendAck();
	//CHKSUM
	IIC_HT_ReadByte(0);//chksum
	IIC_HT_sendAck();
	
	IIC_HT_Stop();

	
	Centi = ((float)(Centi_H << 8) + Centi_L)*175/65535 -46.85;
	Humidity = ((float)(RH_H << 8) + RH_L)/65535*100;

//判断数值合理
	if( (HT_TEMP_MIN <= Centi) && (Centi <= HT_TEMP_MAX) &&		//温度
		(HT_HUMIT_MIN <= Humidity) && (Humidity <= HT_HUMIT_MAX) )//湿度
		u8HTfailFlag = 0;
	else
		u8HTfailFlag = 1;
					
}


