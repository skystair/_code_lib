#include "config.h"


void GPIO_init(void);
void GPIO_Deinit(void);

void SysClkInit(void);

void CLK_EN(void);
void CLK_DisableAll(void);

void Interrupt_EN(void);
void Interrupt_DisEN(void);


void GPIO_init(void){
	stc_gpio_cfg_t stcGpioCfg = {0};

//GPIO_OUT=============================================
	stcGpioCfg.bOutputVal = 0;
	stcGpioCfg.enDir = GpioDirOut;//端口方向
	//stcGpioCfg.enDrv
	stcGpioCfg.enPu = GpioPuDisable;//上拉X
	stcGpioCfg.enPd = GpioPdDisable;//下拉Y
	
	//LED
	Gpio_Init(STK_LED_PORT, STK_LED_PIN, &stcGpioCfg);

//uart================================================
	stcGpioCfg.enDir = GpioDirIn;
//	Gpio_Init(GpioPortA, GpioPin10, &stcGpioCfg);
//	Gpio_SetAfMode(GpioPortA, GpioPin10, GpioAf1);	//配置端口为URART0_RX
	
	stcGpioCfg.enDir = GpioDirOut;	//GPIO 输出
	stcGpioCfg.enPu  = GpioPuEnable;	//必须设置成上拉，否则不能正常工作
	stcGpioCfg.enOD  = GpioOdEnable;	//GPIO开漏输出使能
	///<UART0 TX
//	Gpio_Init(GpioPortA, GpioPin9, &stcGpioCfg);
//	Gpio_SetAfMode(GpioPortA, GpioPin9, GpioAf1);	//配置端口为URART0_TX
	Gpio_Init(GpioPortB, GpioPin6, &stcGpioCfg);
	Gpio_SetAfMode(GpioPortB, GpioPin6, GpioAf2);	//配置端口为URART0_TX
}

void GPIO_Deinit(void){
	stc_gpio_cfg_t stcGpioCfg = {0};
	Gpio_Init(STK_LED_PORT, STK_LED_PIN, &stcGpioCfg);
	
	Gpio_SetAfMode(GpioPortB, GpioPin6, GpioAf0);
	Gpio_Init(GpioPortB, GpioPin6, &stcGpioCfg);
//	
//	Gpio_SetAfMode(GpioPortA, GpioPin9, GpioAf0);
//	Gpio_Init(GpioPortA, GpioPin9, &stcGpioCfg);
}

void SysClkInit(void){
    stc_sysctrl_pll_cfg_t stcPLLCfg;    
    
    ///< 加载目标频率的RCH的TRIM值
    Sysctrl_SetRCHTrim(SysctrlRchFreq4MHz);
    ///< 使能RCH
    Sysctrl_ClkSourceEnable(SysctrlClkRCH, TRUE);
    
    stcPLLCfg.enInFreq    = SysctrlPllInFreq4_6MHz;     //RCH 4MHz
    stcPLLCfg.enOutFreq   = SysctrlPllOutFreq24_36MHz;  //PLL 输出
    stcPLLCfg.enPllClkSrc = SysctrlPllRch;              //输入时钟源选择RCH
    stcPLLCfg.enPllMul    = SysctrlPllMul8;                        //4MHz x 8 = 32MHz
    Sysctrl_SetPLLFreq(&stcPLLCfg); 
    
    ///< 当使用的时钟源HCLK大于24M：设置FLASH 读等待周期为1 cycle(默认值也为1 cycle)
    Flash_WaitCycle(FlashWaitCycle1);    
//     Sysctrl_SetPLLStableTime(SysctrlPllStableCycle16384);
    ///< 使能PLL
    Sysctrl_ClkSourceEnable(SysctrlClkPLL, TRUE);
    ///< 时钟切换到PLL
    Sysctrl_SysClkSwitch(SysctrlClkPLL);

}


void CLK_EN(void)
{
	Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE); //打开GPIO外设时钟门控
	Sysctrl_SetPeripheralGate(SysctrlPeripheralTim3, TRUE); //Base Timer3外设时钟使能
	Sysctrl_SetPeripheralGate(SysctrlPeripheralUart0,TRUE);//使能uart0模块时钟
}
void CLK_DisableAll(void){
	Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, FALSE); //打开GPIO外设时钟门控
	Sysctrl_SetPeripheralGate(SysctrlPeripheralTim3, FALSE); //Base Timer3外设时钟使能
	Sysctrl_SetPeripheralGate(SysctrlPeripheralUart0,FALSE);//使能uart0模块时钟
}

void Interrupt_EN(void){	
	//timer3
	Tim3_ClearIntFlag(Tim3UevIrq);                          //清中断标志
    Tim3_Mode0_EnableIrq();	//使能TIM3中断(模式0时只有一个中断)
    EnableNvic(TIM3_IRQn, IrqLevel3, TRUE);                 //TIM3 开中断
	//UART0
	 ///<UART0中断使能
    Uart_ClrStatus(M0P_UART0,UartRC);
    Uart_ClrStatus(M0P_UART0,UartTC);
    Uart_EnableIrq(M0P_UART0,UartRxIrq);
    //Uart_EnableIrq(M0P_UART0,UartTxIrq);   
    EnableNvic(UART0_2_IRQn, IrqLevel3, TRUE);
}

void Interrupt_DisEN(void){
	Tim3_ClearAllIntFlag();
    Tim3_Mode0_DisableIrq();
    EnableNvic(TIM3_IRQn, IrqLevel3, FALSE);
	
	Uart_ClrStatus(M0P_UART0,UartRC);
    Uart_ClrStatus(M0P_UART0,UartTC);
    Uart_DisableIrq(M0P_UART0,UartRxIrq);
    //Uart_EnableIrq(M0P_UART0,UartTxIrq);
    EnableNvic(UART0_2_IRQn, IrqLevel3, FALSE);
}

