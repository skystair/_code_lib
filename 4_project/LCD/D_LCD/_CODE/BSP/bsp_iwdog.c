#include "config.h"


void BspIwdogInit(void)
{
#if(ENABLE_BSP_IWDOG)
//	RCC_EnableLsi(ENABLE);
//	while (RCC_GetFlagStatus(RCC_FLAG_LSIRD) == RESET)
//	{
//	}
	IWDG_WriteConfig(IWDG_WRITE_ENABLE);
	IWDG_SetPrescalerDiv(IWDG_PRESCALER_DIV8);
	 IWDG_CntReload(2500);//500ms
	IWDG_ReloadKey();
	IWDG_Enable();
#endif
}

void BspIwdogReload(void)
{
#if(ENABLE_BSP_IWDOG)
	 IWDG_ReloadKey();
#endif
}

int BspIsIwdogReset(void)
{
	int result = 0;
#if(ENABLE_BSP_IWDOG)
	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
	{
		result = 1;
	}
#endif
	return result;
}
