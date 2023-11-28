#include "config.h"

UBYTE *BlackImage;


unsigned char u8OLEDflag;

void OLED_valueinit(void);
void OLED_init(void);
void OLED_func(void);



void OLED_valueinit(void){
	u8OLEDflag = 0;
}



void OLED_init(void){
	OLED_1in5_rgb_Init();
	HAL_Delay(500);
	OLED_1in5_rgb_Clear();
	
	
	uint32_t Imagesize = (OLED_1in5_RGB_WIDTH*2) * OLED_1in5_RGB_HEIGHT;
	
	if((BlackImage = (UBYTE *)malloc(Imagesize/4)) == NULL) {
		printf("Failed to apply for black memory...\r\n");
			//return -1;
		while(1);
	}
	
	Paint_NewImage(BlackImage, 64, 128, 0, BLACK);	
	Paint_SetScale(65);
	
	Paint_SelectImage(BlackImage);

	Paint_DrawString_EN(0, 0,	"V  :", 	&Font20, BLACK, BLUE);
	Paint_DrawString_EN(0, 22,	"C  :", 	&Font20, BLACK, BLUE);
	Paint_DrawString_EN(0, 44,	"T&H:", 	&Font20, BLACK, BLUE);

	Paint_DrawString_EN(0, 68,	"T-MOS :",	&Font12, BLACK, BLUE);
	Paint_DrawString_EN(0, 84,	"T-PCB :",	&Font12, BLACK, BLUE);
	Paint_DrawString_EN(0, 100,	"VIN   :",	&Font12, BLACK, BLUE);
	Paint_DrawString_EN(0, 116,	"REF   :",	&Font12, BLACK, BLUE);
	
	OLED_1in5_rgb_Display_Part(BlackImage, 0, 0, 64, 128);
	
	printf("Drawing:page 0\r\n");	
	Paint_Clear(BLACK);	
	Driver_Delay_ms(200);
}

void OLED_func(void){
	Paint_DrawNum(0,   2, Vad[0], 	&Font12, 3, RED, BLACK);//V an7
	Paint_DrawNum(0,  24, Vad[1], 	&Font12, 3, RED, BLACK);//C an3
	Paint_DrawNum(0,  46, Centi, 	&Font12, 3, RED, BLACK);//T&H
	Paint_DrawNum(0,  57, Humidity, &Font12, 3, RED, BLACK);//T&H
	Paint_DrawNum(0,  68, Vad[3], 	&Font12, 3, RED, BLACK);//T-MOS an4
	Paint_DrawNum(0,  84, Vad[4], 	&Font12, 3, RED, BLACK);//T-PCB an5
	Paint_DrawNum(0, 100, Vad[5], 	&Font12, 3, RED, BLACK);//VIN an0
	Paint_DrawNum(0, 116, Vad[6], 	&Font12, 3, RED, BLACK);//REF an6
	OLED_1in5_rgb_Display_Part(BlackImage, 64, 0, 128, 128);
//	Paint_Clear(BLACK);
}








