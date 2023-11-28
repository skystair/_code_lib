
/* Includes -------------------------------------------------------------------*/
#include <stdio.h>
#include "config.h"

unsigned char ADCfirst;
unsigned short int adc_sum[ADCNUM];
unsigned short int adc_result[ADCNUM];
unsigned short int adc_average[ADCNUM];

unsigned char u8HeatIshortflag;

void ADCxvalueinit(void);
void ADCxInit(void);
void DMAInit(void);
void ADCxfunc(void);


void ADCxValueInit(void){
	ADCfirst = 0;
	
	memset(&adc_sum,0,2 *ADCNUM);
	memset(&adc_result,0,2 *ADCNUM);
	memset(&adc_average,0,2 *ADCNUM);
	
	u8HeatIshortflag = 0;
}
void ADCxInit(void){
	DMAInit();
	
	/* ADC trigger config */
    adc_external_trigger_source_config(ADC_REGULAR_CHANNEL, ADC_EXTTRIG_REGULAR_T14_CH0 );//
	/* ADC data alignment config */
	adc_data_alignment_config(ADC_DATAALIGN_RIGHT);
/* ADC channel length config */
    adc_channel_length_config(ADC_REGULAR_CHANNEL, ADCNUM);
	
    /* ADC regular channel config */
	//0~5
	adc_regular_channel_config(0, ADC_CHANNEL_0, ADC_SAMPLETIME_13POINT5);
	adc_regular_channel_config(1, ADC_CHANNEL_1, ADC_SAMPLETIME_13POINT5);
    adc_regular_channel_config(2, ADC_CHANNEL_2, ADC_SAMPLETIME_13POINT5);
	adc_regular_channel_config(3, ADC_CHANNEL_3, ADC_SAMPLETIME_13POINT5);
	adc_regular_channel_config(4, ADC_CHANNEL_4, ADC_SAMPLETIME_13POINT5);
	adc_regular_channel_config(5, ADC_CHANNEL_5, ADC_SAMPLETIME_13POINT5);
	adc_regular_channel_config(6, ADC_CHANNEL_6, ADC_SAMPLETIME_13POINT5);
	adc_regular_channel_config(7, ADC_CHANNEL_7, ADC_SAMPLETIME_13POINT5);
	adc_regular_channel_config(8, ADC_CHANNEL_8, ADC_SAMPLETIME_13POINT5);
	adc_regular_channel_config(9, ADC_CHANNEL_9, ADC_SAMPLETIME_13POINT5);
	
    /* ADC external trigger enable */
    adc_external_trigger_config(ADC_REGULAR_CHANNEL, ENABLE);
//    /* ADC external trigger source config */
    adc_discontinuous_mode_config(ADC_REGULAR_CHANNEL, 5);//1~8
   
    /* enable ADC interface */
    adc_enable();
//	delay_1ms(1U);
    /* ADC calibration and reset calibration */
    adc_calibration_enable();
    /* ADC DMA function enable */
    adc_dma_mode_enable();
	
//	adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
	
	nvic_irq_enable(ADC_CMP_IRQn, 2U, 0U);
	adc_interrupt_enable(ADC_INT_EOC);

}

void DMAInit(void){
	dma_parameter_struct dma_init_struct;

    /* initialize DMA channel0 */
    dma_deinit(DMA_CH0);
	
	dma_init_struct.periph_addr  = (uint32_t)&(ADC_RDATA);
	dma_init_struct.periph_inc   = DMA_PERIPH_INCREASE_DISABLE;
	dma_init_struct.memory_addr  = (uint32_t)adc_result;
	dma_init_struct.memory_inc   = DMA_MEMORY_INCREASE_ENABLE;
	dma_init_struct.memory_width = DMA_MEMORY_WIDTH_16BIT;
	dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_16BIT;
	dma_init_struct.direction    = DMA_PERIPHERAL_TO_MEMORY;
	dma_init_struct.number       = ADCNUM;
	dma_init_struct.priority     = DMA_PRIORITY_ULTRA_HIGH;
    
    dma_init(DMA_CH0, &dma_init_struct);
    
//	nvic_irq_enable(DMA_Channel0_IRQn, 2U, 0U);
//	dma_interrupt_enable(DMA_CH0, DMA_INT_FTF);
//	dma_interrupt_enable(DMA_CH0, DMA_INT_HTF);
    /* configure DMA mode */
    dma_circulation_enable(DMA_CH0);	
//    dma_memory_to_memory_disable(DMA_CH0);
    /* enable DMA channel0 */
    dma_channel_enable(DMA_CH0);
}


void DMA_Channel0_IRQHandler(void)
{
//	u8ADCsampleflag = 1;
//	dma_interrupt_flag_clear(DMA_CH0, DMA_INT_FLAG_G);
}
unsigned char u8shortCount = 0;
unsigned char u8shortCount1 = 0;
unsigned short int testAD;

void ADC_CMP_IRQHandler(void)
{	
	
	if(testAD < AD_I_BRUSH_SHT)	testAD = AD_I_BRUSH_SHT;
	u32FGtick++;
//	if(gpio_input_bit_get(GPIOA, GPIO_PIN_8)){
//	}
	//if(ucWorkMode == 1)
	{
		if(AD_I_BRUSH_AVG > BRUSH_I_12A){
			
			u8shortCount++;
			if(u8shortCount >= 2){
				Brush_Duty_Set(0);
				u8BrushOverISDflag = 1;
				BrushStruct.ucState = 0;
			}	
		}else{
			u8shortCount = 0;
		}
		
		if(AD_I_HEAT > (BRUSH_I_10A/2)){
//			if(testAD < AD_I_BRUSH)	testAD = AD_I_BRUSH;
			u8shortCount1++;
			if(u8shortCount1 >= 2){
				HEAT_OFF;
				u8HeatIshortflag = 1;
				u8heatState = 0;
			}	
		}else{
			u8shortCount1 = 0;
		}
	}
		
	if(ADCfirst == 0){
		ADCfirst = 1;
		for(unsigned char i= 0;i<ADCNUM;i++){
			adc_sum[i] = adc_result[i]*7;
		}
	}else{
		for(unsigned char i= 0;i<ADCNUM;i++){
			adc_sum[i] += adc_result[i];
			adc_average[i] = adc_sum[i]/8;
			adc_sum[i] -= adc_average[i];
		}
	}
	
	adc_flag_clear(ADC_FLAG_EOC);
}



