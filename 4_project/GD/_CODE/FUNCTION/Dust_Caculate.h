#ifndef _DUST_CACULATE_H
#define _DUST_CACULATE_H



#define DUST_VALUE_MIN  (0)
#define DUST_VALUE_MAX  (100)  // 用作灰尘环的最大值




void Dust_EXTI_Irq(void);
unsigned short int Dust_Get_Multiply(void);
void Dust_Caculate(void);



#endif
