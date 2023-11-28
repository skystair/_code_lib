//def of PORT PIN
#define gpiox_read_pin(x, y)	(READ_BIT(x->ID, y) == y)

#define D_PORT_A		GPIOA
#define D_PORT_B		GPIOB
#define D_PORT_C		GPIOC
#define D_PORT_D		GPIOD

#define D_PIN_0			MD_GPIO_PIN_0
#define D_PIN_1			MD_GPIO_PIN_1
#define D_PIN_2			MD_GPIO_PIN_2
#define D_PIN_3			MD_GPIO_PIN_3
#define D_PIN_4			MD_GPIO_PIN_4
#define D_PIN_5			MD_GPIO_PIN_5
#define D_PIN_6			MD_GPIO_PIN_6
#define D_PIN_7			MD_GPIO_PIN_7
#define D_PIN_8			MD_GPIO_PIN_8
#define D_PIN_9			MD_GPIO_PIN_9
#define D_PIN_10		MD_GPIO_PIN_10
#define D_PIN_11		MD_GPIO_PIN_11
#define D_PIN_12		MD_GPIO_PIN_12
#define D_PIN_13		MD_GPIO_PIN_13
#define D_PIN_14		MD_GPIO_PIN_14
#define D_PIN_15		MD_GPIO_PIN_15

#define D_AF_1			MD_GPIO_AF1
#define D_AF_2			MD_GPIO_AF2
#define D_AF_3			MD_GPIO_AF3
#define D_AF_4			MD_GPIO_AF4
#define D_AF_5			MD_GPIO_AF5
#define D_AF_6			MD_GPIO_AF6
#define D_AF_7			MD_GPIO_AF7
#define D_AF_8			MD_GPIO_AF8
#define D_AF_9			MD_GPIO_AF9

#define D_IO_READ		gpiox_read_pin

#define D_IO_H			md_gpio_set_pin_high
#define D_IO_L			md_gpio_set_pin_low

#define D_PWM_SET		md_timer_set_capture_compare1_value_ccrv1
//PIN-----------------------------------------------------
//AD
	//ch4
#define PORT_ADKEY		D_PORT_A
#define PIN_ADKEY		D_PIN_4
	//CH5
#define PORT_ADHW		D_PORT_A
#define PIN_ADHW		D_PIN_5
	//ch6
#define PORT_ADBRUSHI	D_PORT_A
#define PIN_ADBRUSHI	D_PIN_6
	//ch7
#define PORT_ADBRUSHX	D_PORT_A
#define PIN_ADBRUSHX	D_PIN_7


//PWM
	//GP16C4T2_CH1
#define PORT_BRUSHPWM	D_PORT_B
#define PIN_BRUSHPWM	D_PIN_4
#define AF_BRUSHPWM		D_AF_3
	//GP16C2T2_CH1
#define PORT_HWPWM		D_PORT_B
#define PIN_HWPWM		D_PIN_8
#define AF_HWPWM		D_AF_5

//UART
	//bat-------------------------//UART1
#define UART_BAT		UART1
#define USARTbat_IRQHandler		UART1_IRQHandler
#define USARTbat_IRQn	UART1_IRQn

#define PORT_TX_BAT		D_PORT_B
#define PIN_TX_BAT		D_PIN_6
#define AF_TX_BAT		D_AF_2

#define PORT_RX_BAT		D_PORT_B
#define PIN_RX_BAT		D_PIN_7
#define AF_RX_BAT		D_AF_2
	//MOT&LCD SCRENE	双从机-----//UART2
#define UART_MS			UART3	
#define USARTms_IRQHandler		UART3_AES_IRQHandler
#define USARTms_IRQn	UART3_AES_IRQn

#define PORT_TX_MS		D_PORT_B
#define PIN_TX_MS		D_PIN_10
#define AF_TX_MS		D_AF_2

#define PORT_RX_MS		D_PORT_B
#define PIN_RX_MS		D_PIN_11
#define AF_RX_MS		D_AF_2
	//BRUSH------------------------//UART 4 二合一
#define UART_BRUSH		UART4
#define USARTbrush_IRQHandler		UART4_KBCU_IRQHandler
#define USARTbrush_IRQn	UART4_KBCU_IRQn

#define PORT_TX_BRUSH	D_PORT_A
#define PIN_TX_BRUSH	D_PIN_0
#define AF_TX_BRUSH		D_AF_6

#define PORT_RX_BRUSH	D_PORT_A
#define PIN_RX_BRUSH	D_PIN_1
#define AF_RX_BRUSH		D_AF_6
	//

//INPUT----------------------------------------------------------
#define PORT_HWCNT		D_PORT_B
#define PIN_HWCNT		D_PIN_1

//#define KEY_test_READ	D_IO_READ(D_PORT_A, D_PIN_1)

//OUTPUT---------------------------------------------------------
//1
#define TEST_H			D_IO_H(D_PORT_C, D_PIN_1)
#define TEST_L			D_IO_L(D_PORT_C, D_PIN_1)
//2


	//PWM
#define	Brush_Duty_Set(x) 	D_PWM_SET(GP16C4T2, (x))
#define DAC_Duty_Set(x)		D_PWM_SET(GP16C2T2, (x))

//ADC
#define AD_ADKEY			adc_average[0]
#define AD_HWDUST			adc_result[1]
#define AD_brushI			adc_average[2]
#define AD_brushshortI		adc_result[2]
#define AD_brushI0			adc_result[3]

//----------------------------------
#define ADC_REF             (3300)
#define ADC_MAX             (0xFFF)
#define ADC_2_VOLTAGE(x)    ((unsigned int)(x) *ADC_REF/ADC_MAX)
#define VOLTAGE_2_ADC(x)    ((unsigned short int)((unsigned int)(x) *ADC_MAX/ADC_REF))



