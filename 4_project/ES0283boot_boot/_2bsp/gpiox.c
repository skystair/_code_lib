#include "config.h"


void Gpio_normalIO(void);
void Gpio_UartX(void);

void GpioxInit(void);



//1==================================================================
void Gpio_normalIO(void){
	md_gpio_inittypedef md_gpio_initX;
	
	md_gpio_initX.OutDrive = MD_GPIO_DRIVING_8MA;
	md_gpio_initX.OutputType = MD_GPIO_OUTPUT_PUSHPULL;
	md_gpio_initX.Pull = MD_GPIO_PULL_FLOATING;
	md_gpio_initX.Function = MD_GPIO_AF0;
	md_gpio_initX.Mode = MD_GPIO_MODE_INPUT;
	//in--------------------------------------------------------------------------------
	//out--------------------------------------------------------------------------------
	md_gpio_initX.Mode = MD_GPIO_MODE_OUTPUT;
	md_gpio_initX.Pin = D_PIN_1;
	md_gpio_init(D_PORT_C, &md_gpio_initX);
}
void Gpio_UartX(void){
	md_gpio_inittypedef md_gpio_initX;
	
	md_gpio_initX.OutDrive = MD_GPIO_DRIVING_8MA;
	md_gpio_initX.OutputType = MD_GPIO_OUTPUT_PUSHPULL;
	md_gpio_initX.Pull = MD_GPIO_PULL_UP;
	
	md_gpio_initX.Mode = MD_GPIO_MODE_FUNCTION;
	
	//U0
	//U1
	md_gpio_initX.Function = AF_TX_BAT;
	md_gpio_initX.Pin = PIN_TX_BAT;
    md_gpio_init(PORT_TX_BAT, &md_gpio_initX);
	md_gpio_initX.Pin = PIN_RX_BAT;
    md_gpio_init(PORT_RX_BAT, &md_gpio_initX);
}

void GpioxInit(void){
	Gpio_normalIO();
	Gpio_UartX();
}
