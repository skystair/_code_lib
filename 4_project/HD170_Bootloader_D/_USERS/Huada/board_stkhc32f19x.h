#ifndef __BOARD_STKHC32F19X_H__
#define __BOARD_STKHC32F19X_H__

///< STK GPIO DEFINE
///< USER KEY
#define STK_USER_PORT       GpioPortA
#define STK_USER_PIN        GpioPin7

///< LED
#define STK_LED_PORT        GpioPortD
#define STK_LED_PIN         GpioPin14

///< XTH
#define SYSTEM_XTH          (32*1000*1000u)     ///< 32MHz

#define STK_XTHI_PORT       GpioPortF
#define STK_XTHI_PIN        GpioPin0
#define STK_XTHO_PORT       GpioPortF
#define STK_XTHO_PIN        GpioPin1

///< XTL
#define SYSTEM_XTL          (32768u)            ///< 32768Hz
#define STK_XTLI_PORT       GpioPortC
#define STK_XTLI_PIN        GpioPin14
#define STK_XTLO_PORT       GpioPortC
#define STK_XTLO_PIN        GpioPin15



//OUTPUT========================================
	//MOS


	//LED

//INPUT=========================================
	//KEY

//ADC===========================================

//COMMUNICATE===================================

	//UART0
#define UART0_TX_PIN 		GpioPin6
#define UART0_TX_PORT 		GpioPortA
#define UART0_RX_PIN 		GpioPin7
#define UART0_RX_PORT 		GpioPortA

#endif
