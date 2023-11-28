#ifndef __EXITX_H__
#define __EXITX_H__











//md_gpio_set_pin_low(GPIOC, MD_GPIO_PIN_0);
//md_gpio_set_pin_low(GPIOC, MD_GPIO_PIN_2);
//md_gpio_set_pin_high(GPIOC, MD_GPIO_PIN_1);
//md_gpio_set_pin_high(GPIOC, MD_GPIO_PIN_3);


extern unsigned char u8FGdelay;
extern unsigned int u32FGtick;
extern unsigned int u32FGtime;
extern unsigned char u8FGerrorflag;
extern unsigned int EXTIx_Cnt;

extern void ExitxValueInit(void);
extern void ExitxInit(void);

#endif
