#ifndef _BSP_DMA_H_
#define _BSP_DMA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g45x.h"


#define MEM_DMA							DMA2
#define MEM_DMA_CH						DMA2_CH1
#define MEM_DMA_TC						DMA2_FLAG_TC1
#define MEM_DMA_IRQ						DMA2_Channel1_IRQn

#define MEM_DMA_CLK						RCC_AHB_PERIPH_DMA2

typedef void (*MemIrqCallback)(void);
void bspMemDmaStart(uint32_t source, uint32_t target, uint32_t halfWordSize);
void BspSetMemDmaIrqCallBack(MemIrqCallback callback);

void dmaXinit (void);
#ifdef __cplusplus
}
#endif

#endif/*_BSP_DMA_H_*/
