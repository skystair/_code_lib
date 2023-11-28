#include "bsp_rtc.h"

int BspRtcInit(void)
{
	int result = 0;
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_BKP, ENABLE);
	
	PWR_BackupAccessEnable(ENABLE);
	
	uint16_t checkNum = BKP_ReadBkpData(BKP_DAT1);

	if(checkNum != 0x55AA)
	{//备份区掉电过，需要重新配置
		
		result = 1;
		RCC_EnableLsi(ENABLE);
		while(RCC_GetFlagStatus(RCC_FLAG_LSIRD) != SET);
		RCC_ConfigRtcClk(RCC_RTCCLK_SRC_LSI);
		RCC_EnableRtcClk(ENABLE);
		RTC_EnableWriteProtection(DISABLE);
		
		if(RTC_EnterInitMode() == SUCCESS)
		{
			RTC_InitType RTC_InitStruct;
			RTC_InitStruct.RTC_AsynchPrediv = 125;
			RTC_InitStruct.RTC_SynchPrediv = 320;
			RTC_InitStruct.RTC_HourFormat = RTC_24HOUR_FORMAT;
			RTC_Init(&RTC_InitStruct);
			RTC_TimeType RTC_TimeStruct;
			*(uint32_t*)(&RTC_TimeStruct) = 0;
			RTC_ConfigTime(RTC_FORMAT_BIN, &RTC_TimeStruct);
			RTC_DateType RTC_DateStruct;
			*(uint32_t*)(&RTC_DateStruct) = 0x00010101;
			RTC_SetDate(RTC_FORMAT_BIN, &RTC_DateStruct);
			RTC_ExitInitMode();
			
			BKP_WriteBkpData(BKP_DAT1, 0x55AA);
		}
	}

	RTC_WaitForSynchro();
	return result;
}

//void BspRtcInit(void)
//{
//	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
//	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_BKP, ENABLE);
//	
//	PWR_BackupAccessEnable(ENABLE);
//	
//	RCC_EnableLsi(ENABLE);
//	while(RCC_GetFlagStatus(RCC_FLAG_LSIRD) != SET);
//	RCC_ConfigRtcClk(RCC_RTCCLK_SRC_LSI);
//	RCC_EnableRtcClk(ENABLE);
//	
//	RTC_WaitForSynchro();
//}
//不需要设置返回0，需要设置返回1
//int BspRtcInit_All(void)
//{
//	int flag = 0;
//	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
//	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_BKP, ENABLE);
//	
//	PWR_BackupAccessEnable(ENABLE);
//	uint16_t bkpData = BKP_ReadBkpData(BKP_DAT1);
//	if(bkpData != 0x50A0)
//	{//需要初始化
//		flag = 1;
//		RTC_EnableWriteProtection(DISABLE);	//取消写保护
//		BKP_WriteBkpData(BKP_DAT1, 0x50A0);	//写入标志
//		
//		//启用LSI并设置为RTC时钟
//		RCC_EnableLsi(ENABLE);
//		while(RCC_GetFlagStatus(RCC_FLAG_LSIRD) != SET);
//		RCC_ConfigRtcClk(RCC_RTCCLK_SRC_LSI);
//		RCC_EnableRtcClk(ENABLE);
//		
//		if(RTC_EnterInitMode() == SUCCESS)
//		{
//			RTC_InitType RTC_InitStruct;
//			RTC_InitStruct.RTC_AsynchPrediv = 125;
//			RTC_InitStruct.RTC_SynchPrediv = 320;
//			RTC_InitStruct.RTC_HourFormat = RTC_24HOUR_FORMAT;
//			RTC_Init(&RTC_InitStruct);
//			RTC_TimeType RTC_TimeStruct;
//			*(uint32_t*)(&RTC_TimeStruct) = 0;
//			RTC_ConfigTime(RTC_FORMAT_BIN, &RTC_TimeStruct);
//			RTC_DateType RTC_DateStruct;
//			*(uint32_t*)(&RTC_DateStruct) = 0x00010101;
//			RTC_SetDate(RTC_FORMAT_BIN, &RTC_DateStruct);
//			RTC_ExitInitMode();
//		}
//	}
//	
//	RTC_WaitForSynchro();
//	
//	return flag;
//}


const unsigned short TheNumberOfDaysBeforeThisMonth[] = 
{
	0, 31, 31+28, 31+28+31, 31+28+31+30, 31+28+31+30+31,
	31+28+31+30+31+30, 31+28+31+30+31+30+31, 31+28+31+30+31+30+31+31,
	31+28+31+30+31+30+31+31+30, 31+28+31+30+31+30+31+31+30+31,
	31+28+31+30+31+30+31+31+30+31+30, 31+28+31+30+31+30+31+31+30+31+30+31
};

uint32_t BspRtcGetTimestamp(void)
{
	uint32_t timestamp;
	RTC_TimeType RTC_TimeStruct;
	RTC_DateType RTC_DateStruct;
	RTC_GetTime(RTC_FORMAT_BIN, &RTC_TimeStruct);
	RTC_GetDate(RTC_FORMAT_BIN, &RTC_DateStruct);
	timestamp = RTC_TimeStruct.Hours*60*60;
	timestamp += RTC_TimeStruct.Minutes*60;
	timestamp += RTC_TimeStruct.Seconds;
	timestamp += (RTC_DateStruct.Year/4 + RTC_DateStruct.Year*365 + TheNumberOfDaysBeforeThisMonth[RTC_DateStruct.Month-1] + RTC_DateStruct.Date-1)*24*60*60;
	if(RTC_DateStruct.Year > 0||RTC_DateStruct.Month > 2)
	{
		timestamp += 24*60*60;
	}
	return timestamp;
}

void BspRtcSetTimestamp(unsigned char year,unsigned char month, unsigned char day, unsigned char hour, unsigned char minute, unsigned char second)
{
	RCC_EnableLsi(ENABLE);
		while(RCC_GetFlagStatus(RCC_FLAG_LSIRD) != SET);
		RCC_ConfigRtcClk(RCC_RTCCLK_SRC_LSI);
		RCC_EnableRtcClk(ENABLE);
		RTC_EnableWriteProtection(DISABLE);
		
		if(RTC_EnterInitMode() == SUCCESS)
		{
			RTC_InitType RTC_InitStruct;
			RTC_InitStruct.RTC_AsynchPrediv = 125;
			RTC_InitStruct.RTC_SynchPrediv = 320;
			RTC_InitStruct.RTC_HourFormat = RTC_24HOUR_FORMAT;
			RTC_Init(&RTC_InitStruct);
			RTC_TimeType RTC_TimeStruct;
			RTC_TimeStruct.Hours = hour;
			RTC_TimeStruct.Minutes = minute;
			RTC_TimeStruct.Seconds = second;
			RTC_ConfigTime(RTC_FORMAT_BIN, &RTC_TimeStruct);
			RTC_DateType RTC_DateStruct;
			RTC_DateStruct.Year = year;
			RTC_DateStruct.Month = month;
			RTC_DateStruct.Date = day;
			RTC_SetDate(RTC_FORMAT_BIN, &RTC_DateStruct);
			RTC_ExitInitMode();
		}
}






