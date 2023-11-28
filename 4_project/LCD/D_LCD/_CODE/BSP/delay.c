#include "delay.h"


void systick_delay_us(u32 nus)
{		
	u32 temp;	    
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);	//select system clock	
	SysTick->LOAD=nus*(SystemCoreClock/1000000); //time relode	  		 
	SysTick->VAL=0x00;        //clear timer value
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;  //Start countdown	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//wait for the time reach 
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //close the count
	SysTick->VAL =0x00;       //clear timer value	 
}

void systick_delay_ms(u16 nms)
{	 		  	  
//	u32 temp;
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);	//select system clock	
	SysTick->LOAD=(SystemCoreClock/1000000)*1000;//time relode(SysTick->LOAD is 24bit)
	SysTick->VAL =0x00;           //clear timer value
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;          //Start countdown	 
	for(int i=0; i<nms; i++)
	{
		SysTick->CTRL &= ~SysTick_CTRL_COUNTFLAG_Msk;
//		do
//		{
//			temp=SysTick->CTRL;
//		}
		while(!(SysTick->CTRL&SysTick_CTRL_COUNTFLAG_Msk));//wait for the time reach  
	}	
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //close the count
	SysTick->VAL =0x00;       //clear timer value		  	    
} 
