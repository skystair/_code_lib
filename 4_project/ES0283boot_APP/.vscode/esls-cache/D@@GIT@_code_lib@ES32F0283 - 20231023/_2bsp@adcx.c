#include "config.h"


unsigned char ADCfirst;
unsigned short int adc_sum[ADCNUM];
unsigned short int adc_result[ADCNUM];
unsigned short int adc_average[ADCNUM];
unsigned int sample_seq_channel[ADCNUM] ={4,5,6,7};

md_dma_init_typedef dma_initStruct;

void ADCxvalueinit(void);
void ADCxinit(void);
void DMAInit(void);
void ADCxfunc(void);


void ADCxvalueinit(void){
	ADCfirst = 0;
	
//	memset(&adc_sum,0,2 *ADCNUM);
	memset(&adc_result,0,2 *ADCNUM);
//	memset(&adc_average,0,2 *ADCNUM);
}
void ADCxinit(void){
	//add by zhourx
	uint32_t normal_sample_seq_channel[] =
    {
        MD_ADC_NCHS1_NS1_CH4
    };
	uint32_t inject_sample_seq_channel[] =
    {
        MD_ADC_NCHS1_NS1_CH5, MD_ADC_NCHS1_NS2_CH6, MD_ADC_NCHS1_NS3_CH7
    };
	//add by zhourx
	
	md_adc_initial md_adc_initx;
	md_adc_initx.ALIGN = MD_ADC_CFG_ALIGN_RIGHT;
	md_adc_initx.RSEL = MD_ADC_CFG_RSEL_12BIT;
	md_adc_initx.Regular_Injected = MD_ADC_MODE_NCHS;
	md_adc_initx.Regular_CM = MD_ADC_CFG_CM_SINGLE;
	md_adc_initx.Cnt = MD_ADC_NCHS1_NSL_1CON;
	md_adc_initx.CKDIV = MD_ADC_SMPT1_CKDIV_DIV4;
	
	//1.±궨
	md_adc_calibration(ADC, &md_adc_initx);
	
	//2.ch time
	md_adc_set_sampletime_channel_4(ADC, 0x80);//0~0XFF
	md_adc_set_sampletime_channel_5(ADC, 0x80);
	md_adc_set_sampletime_channel_6(ADC, 0x80);
	md_adc_set_sampletime_channel_7(ADC, 0x80);
	
	md_adc_init(ADC, &md_adc_initx);//3.init
	while ((ADC->RIF & 0x1) == 0);
	
	md_adc_sequence_conversion(ADC, &md_adc_initx, normal_sample_seq_channel);
	
	//setting inject channel
    md_adc_initx.Regular_Injected = MD_ADC_MODE_ICHS;
    md_adc_initx.Cnt = MD_ADC_ICHS_ISL_3CON;
    md_adc_sequence_conversion(ADC, &md_adc_initx, inject_sample_seq_channel);
	
	md_adc_enable_inj_auto_convert(ADC);

	md_adc_set_normal_external_trigger_source(ADC, MD_ADC_CFG_NEXTSEL_GP16C4T1_TRGOUT);
	md_adc_set_normal_external_trigger_mode(ADC, MD_ADC_CFG_NETS_RISING);

	md_adc_set_start_normal(ADC, MD_ADC_CON_NSTART_START_REGULAR);
}

void GP16C4T1_IRQHandler(void)
{
	md_timer_clear_it_upd(GP16C4T1);
	adc_result[0] = md_adc_get_normal_data(ADC);
	adc_result[1] = md_adc_get_inj_data_1(ADC);
	adc_result[2] = md_adc_get_inj_data_2(ADC);
	adc_result[3] = md_adc_get_inj_data_3(ADC);
	
//	DustADC();
//	
//	if(Brush_I_protectShort()){
//		Brush_Duty_Set(0);
//		ucMode_Dshitf = 0;
//		u8ModeShutdownflag = MODE_ERRSD_BRUSH;
//		u8errorindex = LCD_PAGE_BRUSH_D_ERR;
//	}
	
//	testtick++;
	if(ADCfirst == 0){
		ADCfirst = 1;
		for(unsigned char i= 0;i<ADCNUM;i++){
			adc_sum[i] = adc_result[i]*2;
		}
	}else{
		for(unsigned char i= 0;i<ADCNUM;i++){
			adc_sum[i] += adc_result[i];
			adc_average[i] = adc_sum[i]/3;
			adc_sum[i] -= adc_average[i];
		}
	}
	
}

