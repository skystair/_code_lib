#include "bsp_Dma.h"

volatile uint8_t MEM_StartDraw = 0;
MemIrqCallback MemDmaCallback = ((MemIrqCallback)0);

void BspMemDmaInit(void)
{
	DMA_InitType DMA_InitStructure;
	
	/*ENABLE DMA CLK*/
	RCC_EnableAHBPeriphClk(MEM_DMA_CLK, ENABLE);
	
	DMA_DeInit(MEM_DMA_CH);
	
	DMA_InitStructure.PeriphAddr     = ((uint32_t)0);//Ä¿±ê
	DMA_InitStructure.MemAddr        = ((uint32_t)0);//Ô´
	DMA_InitStructure.Direction      = DMA_DIR_PERIPH_DST;
	DMA_InitStructure.BufSize        = ((uint32_t)0);
	DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_ENABLE;
	DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
	DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_HALFWORD;
	DMA_InitStructure.MemDataSize    = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.CircularMode   = DMA_MODE_NORMAL;
	DMA_InitStructure.Priority       = DMA_PRIORITY_VERY_HIGH;
	DMA_InitStructure.Mem2Mem        = DMA_M2M_ENABLE;
	DMA_Init(MEM_DMA_CH, &DMA_InitStructure);
	
	DMA_ConfigInt(MEM_DMA_CH, MEM_DMA_TC, ENABLE);

	NVIC_InitType NVIC_InitStructure;
	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel                   = MEM_DMA_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	MEM_StartDraw = 0;
}

void bspMemDmaStart(uint32_t source, uint32_t target, uint32_t halfWordSize)
{
	uint32_t time_out_count = 0;
	while(MEM_StartDraw||time_out_count > 60000)
		time_out_count++;
	MEM_StartDraw = 1;
	
	MEM_DMA_CH->MADDR = source; 
	MEM_DMA_CH->PADDR = target;
	MEM_DMA_CH->TXNUM = halfWordSize;
	DMA_EnableChannel(MEM_DMA_CH, ENABLE);
}

void BspSetMemDmaIrqCallBack(MemIrqCallback callback)
{
	MemDmaCallback = callback;
}

void DMA2_Channel1_IRQHandler()
{
	DMA_EnableChannel(MEM_DMA_CH, DISABLE);
	
	DMA_ClearFlag(MEM_DMA_TC, MEM_DMA);
	DMA_ClrIntPendingBit(MEM_DMA_TC, MEM_DMA);
	
	MEM_StartDraw = 0;
	if(MemDmaCallback)
	{
		MemDmaCallback();
	}
}













