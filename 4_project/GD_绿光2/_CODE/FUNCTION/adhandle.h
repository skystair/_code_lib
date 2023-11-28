#ifndef __ADHANDLE_H__
#define __ADHANDLE_H__

//#define SEL5V0

#ifdef SEL5V0
//5v==============================================================
//heat
#define AD_NTC_60C			800		//2.427
#define AD_NTC_57C			872		//2.707
#define AD_NTC_55C			940		//2.98
#define AD_NTC_50C			1066	//3.518
#define AD_NTC_45C			1226	//4.272
#define AD_NTC_40C			1404	//5.22

#define AD_NTC_OPEN		4000	//  4000/4095*3.3=3.22V 421K
#define AD_NTC_SHORT	100		//  100/4095*3.3=0.8V		0.25K

//2.Brush_I 100mR
#define BRUSH_I_3A		245			//0.10*3/5*4095
#define BRUSH_I_6A		491			//0.10*6/3.3*4095


//3.BatV
//2770/112.8 = 24.5
//X* 6 * 5.1 /56.1 *4095 /5 = X*6 *74.45
#define BAT_V_18V6		1384	//3.1*6*112.8 = 18.6 *74.45
#define BAT_V_17V1		1273	//2.85*6*112.8 = 17.1 *74.45
#define BAT_V_19V5		1452	//19.5*74.45 = 2200


#define BAT_V_24V9		1853
#define BAT_V_24V7		1840
#define BAT_V_25V0		1861
#define BAT_V_25V2		CHG_OVER_NOR

#define BAT_PER_001		1266
#define BAT_PER_010		1451
#define BAT_PER_020		1489
#define BAT_PER_030		1526
#define BAT_PER_040		1553
#define BAT_PER_050		1581

//4.DC in
//---------------------------------------------
#define CHG_V_28		2084	//28*5.1/56.1*4095/5
#define CHG_OVER_NOR	1875	//(25.2+0)*5.1/56.1*4095/5
#define CHG_CUT_V		447		//6*5.1/56.1*4095/5


//5.keyAD
#define AD_KEY_DELT		50
#define AD_KEY_PWR		(491+AD_KEY_DELT)		//0.6/5*4095
#define AD_KEY_MODL		(1318-AD_KEY_DELT)		//1.61/5*4095
#define AD_KEY_MODH		(1441+AD_KEY_DELT)		//1.76/5*4095
#define AD_KEY_HEATL	(2137-AD_KEY_DELT)		//2.61/5*4095
#define AD_KEY_HEATH	(2500+AD_KEY_DELT)		//2.91/5*4095

#else
//3.3v==============================================================
//heat
#define AD_NTC_60C			800		//2.427
#define AD_NTC_57C			872		//2.707
#define AD_NTC_55C			940		//2.98
#define AD_NTC_50C			1066	//3.518
#define AD_NTC_45C			1226	//4.272
#define AD_NTC_40C			1404	//5.22

#define AD_NTC_OPEN		4000	//  4000/4095*3.3=3.22V 421K
#define AD_NTC_SHORT	100		//  100/4095*3.3=0.8V		0.25K


//2.Brush_I 100mR
#define BRUSH_I_01A		124	//0.10*1/3.3*4095
#define BRUSH_I_02A5	310	//0.10*2.5/3.3*4095
#define BRUSH_I_06A		744	//0.10*6/3.3*4095
#define BRUSH_I_07A		867	//0.10*7/3.3*4095
#define BRUSH_I_09A		1116	//0.10*9/3.3*4095
#define BRUSH_I_10A		1240	//0.10*10/3.3*4095
#define BRUSH_I_11A		1364	//0.10*1/3.3*4095
#define BRUSH_I_12A		1489	//0.10*12/3.3*4095
//#define BRUSH_I_3A		20	//0.10*3/3.3*4095
//#define BRUSH_I_6A		60	//0.10*6/3.3*4095
//3.BatV
//2770/112.8 = 24.5
//X* 6 * 5.1 /56.1 *4095 /3.3 = X*6 *112.8
#define BAT_V_18V0		2030
#define BAT_V_18V5		2087
#define BAT_V_LOW1		2094	//18.56
#define BAT_V_18V6		2098	//3.1*6*112.8 = 18.6 *112.8
#define BAT_V_17V1		1929	//2.85*6*112.8 = 17.1 *112.8
#define BAT_V_19V5		2200	//19.5*112.8 = 2200

#define BAT_V_24V5		2764	//24.5*112.8 
#define BAT_V_24V9		2808
#define BAT_V_24V7		2788
#define BAT_V_25V0		2820
#define BAT_V_25V2		CHG_OVER_NOR

#define BAT_PER_001		1918
#define BAT_PER_010		2199
#define BAT_PER_020		2256
#define BAT_PER_030		2312
#define BAT_PER_040		2353
#define BAT_PER_050		2395

//4.DC in
//---------------------------------------------
#define CHG_V_28		3158	//28*5.1/56.1*4095/3.3
#define CHG_OVER_NOR	2842	//(25.2+0)*5.1/56.1*4095/3.3
#define CHG_CUT_V		677		//6*5.1/56.1*4095/3.3


//5.keyAD
#define AD_KEY_DELT		200

////3.3V 理论
//#define AD_KEY_PWR		(699+AD_KEY_DELT)		//0.6/5*4095		
//#define AD_KEY_MODL		(1625-AD_KEY_DELT)		//1.36/3.3*4095
//#define AD_KEY_MODH		(1837+AD_KEY_DELT)		//1.51/3.3*4095
//#define AD_KEY_HEATL	(2531-AD_KEY_DELT)		//2.13/3.3*4095
//#define AD_KEY_HEATH	(2953+AD_KEY_DELT)		//2.41/3.3*4095

//3.3V 实测
#define AD_KEY_PWR		(660+AD_KEY_DELT)
#define AD_KEY_MODL		(1460-AD_KEY_DELT)
#define AD_KEY_MODH		(1555+AD_KEY_DELT)
#define AD_KEY_HEATL	(2250-AD_KEY_DELT)
#define AD_KEY_HEATH	(2440+AD_KEY_DELT)
#define AD_KEY_MICROL	(2960-AD_KEY_DELT)
#define AD_KEY_MICROH	(3238+AD_KEY_DELT)


#endif

extern unsigned char u8DSG_batdelay1;
extern unsigned char u8DSG_batdelay2;

extern unsigned char u8BrushOverIDelay1;
extern unsigned char u8BrushOverIDelay2;

extern unsigned char u8DSG_Lbatflag;
extern unsigned char u8BrushOverIflag;

extern unsigned char u8NTCstate;
extern unsigned char u8NTCdelay1;
extern unsigned char u8NTCdelay2;
extern unsigned char u8NTCdelay3;

extern void ad_valueInit(void);
extern void adhandle(void);

#endif
