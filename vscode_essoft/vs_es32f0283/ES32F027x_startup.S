        .syntax unified
        .cpu cortex-m0
        .arch armv6-m
        .fpu softvfp
        .thumb
 
/*  Stack Configuration
    Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
*/
       
        .equ Stack_Size,  0x00000400
 
        .section  .stack, "wa"
        .align 3
        .global Stack_Mem
        .global Stack_Size
Stack_Mem:     
        .if Stack_Size
        .space   Stack_Size
        .endif
        .size    Stack_Mem,.-Stack_Mem
        .set     Stack_Size,.-Stack_Mem
__initial_sp:
 
 
/*
 <h> Heap Configuration
   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
</h>
*/
 
        .equ     Heap_Size,       0x00000010
 
        .section  .heap, "wa"
        .align 3
 
        .global Heap_Mem_Start
        .global Heap_Mem_End
Heap_Mem_Start:     
        .if Heap_Size
        .space   Heap_Size
        .endif        
Heap_Mem_End:     
 
 
/* Vector Table Mapped to Address 0 at Reset*/
                                        
        .section  .vectors, "wax"
        .global  __vector
        .type  __vector, %object
        
__vector: 
                .long     __initial_sp  /* Top of Stack*/
                .long     Reset_Handler  /*Reset_Handler*/    
                .long     NMI_Handler  /* NMI Handler*/
                .long     HARDFAULT_Handler         /* HardFault Handler*/
                .long     0                            /* Reserved*/
                .long     0                            /* Reserved*/
                .long     0                            /* Reserved*/
                .long     0                            /* Reserved*/
                .long     0                            /* Reserved*/
                .long     0                            /* Reserved*/
                .long     0                            /* Reserved*/
                .long     SVC_Handler               /* SVCall Handler*/
                .long     0                            /* Reserved*/
                .long     0                            /* Reserved*/
                .long     PENDSV_Handler            /* PendSV Handler*/
                .long     SYSTICK_Handler           /* SysTick Handler*/
 
                /* External Interrupts*/
                .long     PENDSV_Handler             /* 14, PENDSV Handler*/
                .long     SYSTICK_Handler            /* 15, SYSTICK Handler*/
                .long     WWDT_IRQHandler            /* 16, WWDT IRQHandler*/
                .long     PVD_IRQHandler             /* 17, PVD IRQHandler*/
                .long     RTC_IRQHandler             /* 18, RTC IRQHandler*/
                .long     LowPowerWakeup_IRQHandler  /* 19, LowPowerWakeup IRQHandler*/
                .long     0                          /* 20, Reserved*/
                .long     EXTI0_1_IRQHandler         /* 21, EXTI01_1 IRQHandler*/
                .long     EXTI2_3_IRQHandler         /* 22, EXTI2_3 IRQHandler*/
                .long     EXTI4_15_IRQHandler        /* 23, EXTI4_15 IRQHandler*/
                .long     0                          /* 24, Reserved*/
                .long     DMA1_CH1_IRQHandler        /* 25, DMA1_CH1 IRQHandler*/
                .long     DMA1_CH2_3_IRQHandler      /* 26, DMA1_CH2_3 IRQHandler*/
                .long     DMA1_CH4_7_IRQHandler      /* 27, DMA1_CH4_7 IRQHandler*/
                .long     ADC_CMP_IRQHandler         /* 28, ADC_CMP IRQHandler*/
                .long     AD16C4T1_IRQHandler        /* 29, AD16C4T1 IRQHandler*/
                .long     BS16T1_IRQHandler          /* 30, BS16T1 IRQHandler*/
                .long     GP32C4T1_IRQHandler        /* 31, GP32C4T1 IRQHandler*/
                .long     GP16C4T1_IRQHandler        /* 32, GP16C4T1 IRQHandler*/
                .long     GP16C4T2_IRQHandler        /* 33, GP16C4T2 IRQHandler*/
                .long     GP16C4T3_IRQHandler        /* 34, GP16C4T3 IRQHandler*/
                .long     GP16C2T1_IRQHandler        /* 35, GP16C2T1 IRQHandler*/
                .long     GP16C2T2_IRQHandler        /* 36, GP16C2T2 IRQHandler*/
                .long     GP16C2T3_IRQHandler        /* 37, GP16C2T3 IRQHandler*/
                .long     GP16C2T4_IRQHandler        /* 38, GP16C2T4 IRQHandler*/
                .long     I2C1_IRQHandler            /* 39, I2C1 IRQHandler*/
                .long     I2C2_IRQHandler            /* 40, I2C2 IRQHandler*/
                .long     SPI1_IRQHandler            /* 41, SPI1 IRQHandler*/
                .long     SPI2_IRQHandler            /* 42, SPI2 IRQHandler*/
                .long     UART1_IRQHandler           /* 43, UART1 IRQHandler*/
                .long     UART2_IRQHandler           /* 44, UART2 IRQHandler*/
                .long     UART3_AES_IRQHandler       /* 45, UART3_AES IRQHandler*/
                .long     SUART1_SUART2_IRQHandler   /* 46, SUART1_SUART2 IRQHandler*/
                .long     USB_IRQHandler             /* 47, USB IRQHandler*/
 
               .size  __vector, .-__vector
                
.thumb
                .text
                .thumb_func
                .global  Reset_Handler
                .type Reset_Handler,%function
Reset_Handler:
           
                .extern main
                .extern InitRam

                LDR     R0, =InitRam
                BLX     R0
                LDR     R0, =main
                BLX     R0
             
               .size  Reset_Handler, .-Reset_Handler
 
                .text
/* Dummy Exception IRQHandlers (infinite loops which can be modified)*/                
               
                 .weak NMI_Handler
                 .type NMI_Handler,%function
NMI_Handler:     
                 B       .
                 .size  NMI_Handler, .-NMI_Handler
                
                 .weak  HARDFAULT_Handler
                 .type  HARDFAULT_Handler,%function
HARDFAULT_Handler:
                B .
                .size  HARDFAULT_Handler, .-HARDFAULT_Handler
                
                .weak SVC_Handler
                .type SVC_Handler,%function
SVC_Handler: 
                B       .
                .size  SVC_Handler, .-SVC_Handler
              
                
                .weak  PENDSV_Handler
                .type  PENDSV_Handler,%function
PENDSV_Handler:
                B .
          .size  PENDSV_Handler, .-PENDSV_Handler
                 
                .weak  SYSTICK_Handler
                .type  SYSTICK_Handler,%function
SYSTICK_Handler: 
                B .
                .size  SYSTICK_Handler, .-SYSTICK_Handler
 
                .global Default_IRQHandler
                .type  Default_IRQHandler,%function
Default_IRQHandler: 
                B       .
                .size  Default_IRQHandler, .-Default_IRQHandler
                .macro IRQ handler
                .weak \handler
                .set \handler,Default_IRQHandler 
                .endm
				
				IRQ WWDT_IRQHandler
				IRQ PVD_IRQHandler
				IRQ RTC_IRQHandler
				IRQ LowPowerWakeup_IRQHandler
				IRQ EXTI0_1_IRQHandler
				IRQ EXTI2_3_IRQHandler
				IRQ EXTI4_15_IRQHandler
				IRQ DMA1_CH1_IRQHandler
				IRQ DMA1_CH2_3_IRQHandler
				IRQ DMA1_CH4_7_IRQHandler
				IRQ ADC_CMP_IRQHandler
				IRQ AD16C4T1_IRQHandler
				IRQ BS16T1_IRQHandler
				IRQ GP32C4T1_IRQHandler
				IRQ GP16C4T1_IRQHandler
				IRQ GP16C4T2_IRQHandler
				IRQ GP16C4T3_IRQHandler
				IRQ GP16C2T1_IRQHandler
				IRQ GP16C2T2_IRQHandler
				IRQ GP16C2T3_IRQHandler
				IRQ GP16C2T4_IRQHandler
				IRQ I2C1_IRQHandler
				IRQ I2C2_IRQHandler
				IRQ SPI1_IRQHandler
				IRQ SPI2_IRQHandler
				IRQ UART1_IRQHandler
				IRQ UART2_IRQHandler
				IRQ UART3_AES_IRQHandler
				IRQ SUART1_SUART2_IRQHandler
				IRQ USB_IRQHandler
								
				
				
				.end
