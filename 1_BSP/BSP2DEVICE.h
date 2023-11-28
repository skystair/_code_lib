//PIN-----------------------------------------------------

//OUT
	//1
#define PORT_PWRLCK		GPIOB
#define PIN_PWRLCK		GPIO_PIN_14
	//2
#define PORT_CHGON		GPIOB
#define PIN_CHGON		GPIO_PIN_12
	//3
#define PORT_HEATON		GPIOA
#define PIN_HEATON		GPIO_PIN_10
	//4
#define PORT_MOTEN		GPIOB
#define PIN_MOTEN		GPIO_PIN_15
	//5
#define PORT_LEDG		GPIOA
#define PIN_LEDG		GPIO_PIN_11
	//6
#define PORT_UV			GPIOF
#define PIN_UV			GPIO_PIN_6
	//7
#define PORT_L_IR		GPIOB
#define PIN_L_IR		GPIO_PIN_10
	//8
#define PORT_R_IR		GPIOB
#define PIN_R_IR		GPIO_PIN_11

//IN
#define PORT_HWEXIT		GPIOB
#define PIN_HWEXIT		GPIO_PIN_13

//AD
	//CH0
#define PORT_ADKEY		GPIOA
#define PIN_ADKEY		GPIO_PIN_0
	//ch1
#define PORT_I_HEAT		GPIOA
#define PIN_I_HEAT		GPIO_PIN_1
	//ch2
#define PORT_HEATNTC	GPIOA
#define PIN_HEATNTC		GPIO_PIN_2
	//ch3
#define PORT_HWDUST		GPIOA
#define PIN_HWDUST		GPIO_PIN_3
	//ch4

	//ch5
#define PORT_V_CHGR		GPIOA
#define PIN_V_CHGR		GPIO_PIN_5
	//ch6
#define PORT_V_BAT		GPIOA
#define PIN_V_BAT		GPIO_PIN_6
	//ch7
#define PORT_I_BRUSH	GPIOA
#define PIN_I_BRUSH		GPIO_PIN_7
	//ch8
#define PORT_L_PHOTO	GPIOB
#define PIN_L_PHOTO		GPIO_PIN_0
	//ch9
#define PORT_R_PHOTO	GPIOB
#define PIN_R_PHOTO		GPIO_PIN_1


//PWM
	//T0_CH0
#define PORT_BRUSHPWM	GPIOA
#define PIN_BRUSHPWM	GPIO_PIN_8
//#define AF_BRUSH		MD_GPIO_AF2
	//T15_CH0
#define PORT_HWPWM		GPIOB
#define PIN_HWPWM		GPIO_PIN_8
//#define AF_HWPWM		MD_GPIO_AF2
	//T2_CH0
#define PORT_MOTPWM		GPIOB
#define PIN_MOTPWM		GPIO_PIN_4
//#define AF_BRUSH		MD_GPIO_AF1
	//T16_CH0
#define PORT_MOTFG		GPIOB
#define PIN_MOTFG		GPIO_PIN_9
//#define AF_BRUSH		MD_GPIO_AF2

//UART
#define PORT_UART0TX	GPIOB
#define PIN_UART0TX		GPIO_PIN_6
#define AF_UART0TX		GPIO_AF_0

//INPUT----------------------------------------------------------
#define INPUT1		1
#define INPUT0		0

#define KEY_HWEXIT_READ		gpio_input_bit_get(GPIOB, GPIO_PIN_1)
#define KEY_test_READ		gpio_input_bit_get(GPIOA, GPIO_PIN_0)

//OUTPUT---------------------------------------------------------
//1
#define PWR_ON			gpio_bit_set(PORT_PWRLCK, PIN_PWRLCK)
#define PWR_OFF			gpio_bit_reset(PORT_PWRLCK, PIN_PWRLCK)
//2
#define CHG_ON			gpio_bit_set(PORT_CHGON, PIN_CHGON)
#define CHG_OFF			gpio_bit_reset(PORT_CHGON, PIN_CHGON)
//3
#define HEAT_ON			gpio_bit_set(PORT_HEATON, PIN_HEATON)
#define HEAT_OFF		gpio_bit_reset(PORT_HEATON, PIN_HEATON)
//4
#define EN_MOT_ON		gpio_bit_set(PORT_MOTEN, PIN_MOTEN)
#define EN_MOT_OFF		gpio_bit_reset(PORT_MOTEN, PIN_MOTEN)
//5
#define LEDG_ON			gpio_bit_set(PORT_LEDG, PIN_LEDG)
#define LEDG_OFF		gpio_bit_reset(PORT_LEDG, PIN_LEDG)
//6
#define UV_ON			gpio_bit_set(PORT_UV, PIN_UV)
#define UV_OFF			gpio_bit_reset(PORT_UV, PIN_UV)
//7
#define L_PHOTO_OFF		gpio_bit_set(PORT_L_IR, PIN_L_IR)
#define L_PHOTO_ON		gpio_bit_reset(PORT_L_IR, PIN_L_IR)
//8
#define R_PHOTO_OFF		gpio_bit_set(PORT_R_IR, PIN_R_IR)
#define R_PHOTO_ON		gpio_bit_reset(PORT_R_IR, PIN_R_IR)

	//PWM
#define	Brush_ON			timer_enable(TIMER0);
#define	Brush_OFF			timer_disable(TIMER0);
#define	Brush_Duty_Set(x) 	timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_0,(x));
#define Mot_Duty_Set(x);	timer_channel_output_pulse_value_config(TIMER2,TIMER_CH_0,(x));

#define Brush_PERIOD	1000	//1ms


#define LED_ON(x)		ucLED_State[(x)] = 1
#define LED_OFF(x)		ucLED_State[(x)] = 0
//ADC
#define AD_ADKEY			adc_result[0]
#define AD_I_BRUSH_SHT		adc_result[1]
#define AD_I_BRUSH_AVG		adc_average[1]
#define AD_HEATNTC			adc_average[2]
#define AD_HWDUST			adc_average[3]

#define AD_I_CHGR			adc_average[4]

#define AD_V_CHGR			adc_average[5]
#define AD_V_BAT			adc_average[6]
#define AD_I_HEAT			adc_result[7]
#define AD_L_PHOTO			adc_average[8]
#define AD_R_PHOTO			adc_average[9]


//uart
#define DSPDATA1			u8U3txDATA[3]
#define DSPDATA2			u8U3txDATA[4]
#define DSPDATA3			u8U3txDATA[5]
#define DSPDATA4			u8U3txDATA[6]
#define DSPDATA5			u8U3txDATA[7]


//----------------------------------
typedef double       float64_t;

#define DAC_VOLTAGE_REF (3300)      // DAC????
//#define DAC_VALUE_MAX   (0xFFF)     // 3.3V
#define DAC_VALUE_MAX   (100)     // 3.3V
#define DAC_VALUE(x)    (unsigned short int)((float64_t)(x) *DAC_VALUE_MAX/DAC_VOLTAGE_REF)   // x????(mV)	0~3300


//////// ??? ////////
#define ADC_REF             (3300)		// ADC????mV
#define ADC_MAX             (0xFFF)		// ADC???
#define ADC_2_VOLTAGE(x)    ((unsigned int)(x) *ADC_REF/ADC_MAX)                // ADC? ? ??mV
#define VOLTAGE_2_ADC(x)    ((unsigned short int)((unsigned int)(x) *ADC_MAX/ADC_REF))    // ??mV ? ADC?

#define Dust_Int_Enable()	nvic_irq_enable(EXTI4_15_IRQn, 2U, 0U)
#define Dust_Int_Disable()	nvic_irq_disable(EXTI4_15_IRQn)

#define DAC_ValueSet(x)		timer_channel_output_pulse_value_config(TIMER15,TIMER_CH_0,(x));



