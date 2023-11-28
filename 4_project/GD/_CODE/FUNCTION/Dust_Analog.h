#ifndef _DUST_ANALOG_H
#define _DUST_ANALOG_H



// 发射与接收的对应关系
// 发mV	    收mV
// 800      400
// 950      1000

//////// 发射
#define DUST_DAC_MIN		(DAC_VALUE(500))
#define DUST_DAC_MIDDLE     (DAC_VALUE(1500))
#define DUST_DAC_MAX		(DAC_VALUE_MAX)
#define DUST_DAC_OutputLow_InputHigh    (DAC_VALUE(800))    // ADC: 119,  95mV
#define DUST_DAC_OutputHigh_InputLow    (DAC_VALUE(2000))   // ADC:1007, 810mV
#define DUST_DAC_STANDARD               (DAC_VALUE(1000))   // ADC:1007, 810mV


//////// 接收
//#define DUST_ADC_STANDARD   (VOLTAGE_2_ADC(600))
#define DUST_ADC_STANDARD   (VOLTAGE_2_ADC(1000))   // 正常工作的基准电压
#define DUST_ADC_RANGE      (VOLTAGE_2_ADC(400))    // 正常工作的允许误差


#define DUST_ADC_UV       (VOLTAGE_2_ADC(400))      // 高输出时，输入欠压
#define DUST_ADC_OV       (VOLTAGE_2_ADC(1500))     // 低输出时，输入超压

#define DUST_ADC_OutputLow_InputHigh        (VOLTAGE_2_ADC(1800))
#define DUST_ADC_OutputHigh_InputLow        (VOLTAGE_2_ADC(300))



//////// 发射DAC ///////
void Dust_DacSet(unsigned short int x);


/////// 接收ADC ////////
void Dust_AdcValue_Read(void);
unsigned char DustVoltage_IsDiff3(unsigned short int *pV);

unsigned char Dust_Analog_Regulate(void);
unsigned char DustVoltage_NotStandardCheck(void);



#endif
