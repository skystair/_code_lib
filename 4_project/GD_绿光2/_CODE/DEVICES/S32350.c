#include "config.h"

unsigned char u8S32350delay;
unsigned char u8S32350state;
unsigned short int u16data1;
unsigned short int u16data2;

unsigned char u8gain1;
unsigned char u8gain2;
unsigned char u8ITtime;
unsigned char u8S23250onoff;

void S32350func(void){
	unsigned char u8tempdata;
	switch(u8S32350state){
		case 0:
			IIC_Start();
		//addr
			IIC_Send_Byte(0x20);//W
			IIC_Wait_Ack();
		//CMD
			IIC_Send_Byte(0x00);
			IIC_Wait_Ack();
		//
			IIC_Send_Byte(0x10);//L4
			IIC_Wait_Ack();
			IIC_Send_Byte(0x29);//H4
			//IIC_Wait_Ack();
			IIC_Wait_Ack();
			IIC_Stop();
			
			u8S32350state++;
			u8S32350delay = 0;
			break;
		case 1:
			//idle
			if(u8S32350delay >= 150){
				u8S32350delay = 0;
				u8S32350state++;
			}
		break;
		case 2:
			IIC_Start();
		//addr
			IIC_Send_Byte(0x20);//W
			IIC_Wait_Ack();
		//CMD
			IIC_Send_Byte(0x04);
			IIC_Wait_Ack();
			IIC_Start();
			IIC_Send_Byte(0x21);//R
			IIC_Wait_Ack();
			
			u8tempdata = IIC_Read_Byte(1);//L4
			u16data1 = IIC_Read_Byte(0);//H4
			u16data1 = (u16data1<<8) + u8tempdata;
			IIC_Stop();
		
			u8S32350state++;
			u8S32350delay = 0;
			break;
		case 3:
			//idle
			if(u8S32350delay >= 15){
				u8S32350delay = 0;
				u8S32350state++;
			}
		break;
		case 4:
			IIC_Start();
		//addr
			IIC_Send_Byte(0x20);//W
			IIC_Wait_Ack();
		//CMD
			IIC_Send_Byte(0x05);
			IIC_Wait_Ack();
			IIC_Start();
			IIC_Send_Byte(0x21);//R
			IIC_Wait_Ack();
			
			u8tempdata = IIC_Read_Byte(1);//L4
			u16data2 = IIC_Read_Byte(0);//H4
			u16data2 = (u16data2<<8) + u8tempdata;
			IIC_Stop();
		
			u8S32350state++;
			u8S32350delay = 0;
			break;
		case 5:
			//idle
			if(u8S32350delay >= 15){
				u8S32350delay = 0;
				u8S32350state = 0;
			}
		break;
		default:break;
	
	
	}
	
	
	
}