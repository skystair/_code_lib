#include "config.h"



#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)

PUTCHAR_PROTOTYPE
{
	Uart_SendDataPoll(M0P_UART0, (unsigned char)ch);
  return ch;
}


void Uart_init(void);
void Uart_Deinit(void);

void Uart0_IRQHandler(void);


void Uart_init(void)
{
	stc_uart_cfg_t    stcCfg = {0};

    ///<UART Init
    stcCfg.enRunMode        = UartMskMode1;          //模式1
    stcCfg.enStopBit        = UartMsk1bit;           //1bit停止位
    //stcCfg.enMmdorCk        = UartMskEven;           //偶检验
    stcCfg.stcBaud.u32Baud  = 115200;                  //波特率9600
    stcCfg.stcBaud.enClkDiv = UartMsk8Or16Div;       //通道采样分频配置
    stcCfg.stcBaud.u32Pclk  = Sysctrl_GetPClkFreq(); //获得外设时钟（PCLK）频率值
        
    Uart_Init(M0P_UART0, &stcCfg);                   ///<UART0串口初始化
	
    Uart_HdModeEnable(M0P_UART0);                    //使能UART0单线半双工模式
    
//    ///<UART0中断使能
//    Uart_ClrStatus(M0P_UART0,UartRC);                ///<清接收请求
//    Uart_ClrStatus(M0P_UART0,UartTC);                ///<清接收请求
//    Uart_EnableIrq(M0P_UART0,UartRxIrq);            ///<使能串口接收中断
//    //Uart_EnableIrq(M0P_UART0,UartTxIrq);             ///<禁用串口发送中断    
//    EnableNvic(UART0_2_IRQn, IrqLevel3, TRUE);       ///<系统中断使能
	
	RXposition = 0;
}

void Uart_Deinit(void){
	stc_uart_cfg_t    stcCfg = {0};
	
	
	Uart_HdModeDisable(M0P_UART0);
	Uart_Init(M0P_UART0, &stcCfg);
}

//UART0中断服务函数
void Uart0_IRQHandler(void)
{
	unsigned char RXtemp;
	
	Flag_Time1ms = 0;
	
	if(Uart_GetStatus(M0P_UART0, UartRC))
	{
		RXtemp = Uart_ReceiveData(M0P_UART0);   //UART0接收数据
		
		if(RXADDRheadReadyFlag == 0){	//接收0x8000
			HexEndFlag = 0;
			if(RXheadReadyFlag == 0){	//接收head
				GetHead(RXtemp);
			}else if(RXheadReadyFlag == 1){
				
				if(RXADDRheadReadyFlag == 0){
					GetAddrHead(RXtemp);
				}
			}
		
		}else if(RXADDRheadReadyFlag ==1){
			HexEndFlag = 0;
			Startdownloadflag = 1;
			if(RXposition <= 2){
					GetHead(RXtemp);
			}else if(RXposition <= 6){
				RXposition++;
				
			}else if(RXposition == 7){
				if(RXtemp != 0x30){	//0
					HexEndFlag = 1;
					
					RXheadReadyFlag = 0;
					RXADDRheadReadyFlag = 0;
					Uart_ClrStatus(M0P_UART0, UartRC);
					return;
				}
				RXposition = 8;
			}else if(RXposition == 8){
				if(RXtemp != 0x30){ //0
					HexEndFlag = 1;
					
					RXheadReadyFlag = 0;
					RXADDRheadReadyFlag = 0;
					Uart_ClrStatus(M0P_UART0, UartRC);
					return;
				}
				RXposition = 9;
			}else if(RXposition <= 40){//DATA
				GetData(RXtemp);
				
				RXposition++;
			}else if(RXposition < 44){
				RXposition++;			//CHK+END
			}else{
				RXposition = 0;
			}
		}





	Uart_ClrStatus(M0P_UART0, UartRC);                             //清除中断状态标志位
	}
	if(Uart_GetStatus(M0P_UART0, UartTC))
	{
	Uart_ClrStatus(M0P_UART0, UartTC);                             //清除中断状态标志位
	}
}











