#include "config.h"

uint8_t RXdatabyte;
uint8_t RXdata[20];  
void USART3_IRQHandler()
{
	static	uint8_t RX_data_cun=0, RX_stat=0;
	uint8_t i,j=15;
	uint16_t aRxBuffer_SUM=0;
	if(USART_GetFlagStatus(USART3, USART_FLAG_OREF) != RESET) //�ж�����ж�
	{
		
	}
	if(USART_GetFlagStatus(USART3, USART_FLAG_NEF) != RESET) //���������ж�
	{
		
	}
	if(USART_GetFlagStatus(USART3, USART_FLAG_FEF) != RESET) //֡�����ж�
	{
		
	}
	
	if(USART_GetFlagStatus(USART3, USART_FLAG_RXDNE) != RESET)
	{
		USART_ClrFlag(USART3, USART_FLAG_RXDNE);
		USART_ClrIntPendingBit(USART3, USART_INT_RXDNE);
		RXdatabyte = (uint8_t)USART_ReceiveData(USART3);
		if((RXdatabyte==0xAC)&&(RX_stat==0))  //�жϽ���ͷ  0xAC
		{  
			RX_data_cun=0;
			RX_stat=1;
			RXdata[RX_data_cun]=0xAC;
			RX_data_cun++;
		}
		else if(RX_stat)
		{
			RXdata[RX_data_cun]=RXdatabyte; 
			if((RXdata[0]!=0xAC)||(RXdata[1]!=0x03)) //���ǰ�������ݽ������ݴ���  0xAC ��0X03
			{
				RX_data_cun=0;   //���մ���
				RX_stat=0;
				for(i=0;i<j;i++)
				{
					RXdata[i]=0;
				}
			}
			else
				RX_data_cun++; //��������
			
			if(RX_data_cun>=j)  //�������12������
			{
				RX_data_cun=0;
				RX_stat=0;
				for(i=1;i<=12;i++) //����У���
				{
					aRxBuffer_SUM+=RXdata[i];  //ȡ��ַΪ����ļ����
				}
				if((((uint8_t)(aRxBuffer_SUM>>8)&0xff)==RXdata[13])&&((uint8_t)(aRxBuffer_SUM&0xFF)==RXdata[14])) //�ж�У���
				{
					//draw->Refresh(RXdata);
				}
				else
				{
					for(i=0;i<j;i++)
					{
						RXdata[i]=0; //������յ�����
					}
				}
			}
		 }		
	}	
}




