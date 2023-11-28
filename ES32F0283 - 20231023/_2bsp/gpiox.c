#include "config.h"

//private-----------------------------

//public------------------------------
void GPioUbrushTxEnable(void);
void GPioUbrushTxDisable(void);

void GPioUbrushTxEnable(void){
	md_gpio_inittypedef md_gpio_initX;
	md_gpio_initX.OutDrive = MD_GPIO_DRIVING_8MA;
	md_gpio_initX.OutputType = MD_GPIO_OUTPUT_PUSHPULL;
	md_gpio_initX.Pull = MD_GPIO_PULL_UP;
	md_gpio_initX.Mode = MD_GPIO_MODE_FUNCTION;
	
	md_gpio_initX.Function = AF_TX_BRUSH;
	md_gpio_initX.Pin = PIN_TX_BRUSH;
    md_gpio_init(PORT_TX_BRUSH, &md_gpio_initX);
	
	md_gpio_initX.Function = MD_GPIO_AF0;
	md_gpio_initX.Pull = MD_GPIO_PULL_FLOATING;
	md_gpio_initX.Mode = MD_GPIO_MODE_INPUT;
	
	md_gpio_initX.Function = AF_RX_BRUSH;
	md_gpio_initX.Pin = PIN_RX_BRUSH;
    md_gpio_init(PORT_RX_BRUSH, &md_gpio_initX);
}
void GPioUbrushTxDisable(void){
	md_gpio_inittypedef md_gpio_initX;
	md_gpio_initX.OutDrive = MD_GPIO_DRIVING_8MA;
	md_gpio_initX.OutputType = MD_GPIO_OUTPUT_PUSHPULL;
	md_gpio_initX.Pull = MD_GPIO_PULL_UP;
	md_gpio_initX.Mode = MD_GPIO_MODE_FUNCTION;
	
	md_gpio_initX.Function = AF_RX_BRUSH;
	md_gpio_initX.Pin = PIN_RX_BRUSH;
    md_gpio_init(PORT_RX_BRUSH, &md_gpio_initX);
	
	md_gpio_initX.Function = MD_GPIO_AF0;
	md_gpio_initX.Pull = MD_GPIO_PULL_FLOATING;
	md_gpio_initX.Mode = MD_GPIO_MODE_INPUT;
	
	md_gpio_initX.Function = AF_TX_BRUSH;
	md_gpio_initX.Pin = PIN_TX_BRUSH;
    md_gpio_init(PORT_TX_BRUSH, &md_gpio_initX);
	
}

void GpioxInit(void);

void GpioxInit(void){
	md_gpio_inittypedef md_gpio_initX;
	
	md_gpio_initX.OutDrive = MD_GPIO_DRIVING_8MA;		//MD_GPIO_DRIVING_16MA
	md_gpio_initX.OutputType = MD_GPIO_OUTPUT_PUSHPULL;//MD_GPIO_OUTPUT_PUSHPULL;
	md_gpio_initX.Pull = MD_GPIO_PULL_UP;//MD_GPIO_PULL_UP;//MD_GPIO_PULL_FLOATING;
	
	md_gpio_initX.Mode = MD_GPIO_MODE_FUNCTION;
//MODfunc AFx-----------------------------------------------
	//U0
	//U1
	md_gpio_initX.Function = AF_TX_BAT;
	md_gpio_initX.Pin = PIN_TX_BAT;
    md_gpio_init(PORT_TX_BAT, &md_gpio_initX);
	md_gpio_initX.Pin = PIN_RX_BAT;
    md_gpio_init(PORT_RX_BAT, &md_gpio_initX);
	//U2
	md_gpio_initX.Function = AF_TX_MS;
	md_gpio_initX.Pin = PIN_TX_MS;
    md_gpio_init(PORT_TX_MS, &md_gpio_initX);
	md_gpio_initX.Pin = PIN_RX_MS;
    md_gpio_init(PORT_RX_MS, &md_gpio_initX);
	//U3
	//U4
	md_gpio_initX.Function = AF_RX_BRUSH;
	md_gpio_initX.Pin = PIN_RX_BRUSH;
    md_gpio_init(PORT_RX_BRUSH, &md_gpio_initX);

	md_gpio_initX.Pull = MD_GPIO_PULL_FLOATING;//MD_GPIO_PULL_FLOATING;
	md_gpio_initX.OutputType = MD_GPIO_OUTPUT_PUSHPULL;
	//PWM brush
	md_gpio_initX.Function = AF_BRUSHPWM;
	md_gpio_initX.Pin = PIN_BRUSHPWM;
    md_gpio_init(PORT_BRUSHPWM, &md_gpio_initX);
	//PWM HW
	md_gpio_initX.Function = AF_HWPWM;
	md_gpio_initX.Pin = PIN_HWPWM;
    md_gpio_init(PORT_HWPWM, &md_gpio_initX);
//MODad AF0-----------------------------------------------
	//ad	ch4 5 6 7
	md_gpio_initX.Mode = MD_GPIO_MODE_ANALOG;
	md_gpio_initX.Function = MD_GPIO_AF0;

	md_gpio_initX.Pin = PIN_ADKEY;
    md_gpio_init(PORT_ADKEY, &md_gpio_initX);
	
	md_gpio_initX.Pin = PIN_ADHW;
    md_gpio_init(PORT_ADHW, &md_gpio_initX);
	
	md_gpio_initX.Pin = PIN_ADBRUSHI;
    md_gpio_init(PORT_ADBRUSHI, &md_gpio_initX);
	
	md_gpio_initX.Pin = PIN_ADBRUSHX;
    md_gpio_init(PORT_ADBRUSHX, &md_gpio_initX);
//MOD IO af0-----------------------------------------------
	md_gpio_initX.Mode = MD_GPIO_MODE_INPUT;
	//in--------------------------------------------------------------------------------
	md_gpio_initX.Pull = MD_GPIO_PULL_FLOATING;
	md_gpio_initX.Pin = PIN_HWCNT;
	md_gpio_init(PORT_HWCNT, &md_gpio_initX);
	
//	md_gpio_initX.Mode = MD_GPIO_MODE_OUTPUT;
//	md_gpio_initX.Pin = D_PIN_1;
//	md_gpio_init(D_PORT_C, &md_gpio_initX);
	
//exti-------------------------------------------------------
}
