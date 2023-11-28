#include "StaticTextList.h"

/******************************** 字库路径 ************************************/
const char* LanguageList[40] = {
	"\\root\\text\\selected\\0.chs",
	"\\root\\text\\selected\\1.chs",
	"\\root\\text\\selected\\2.chs",
	"\\root\\text\\selected\\3.chs",
	"\\root\\text\\selected\\4.chs",
	"\\root\\text\\selected\\5.chs",
	"\\root\\text\\selected\\6.chs",
	"\\root\\text\\selected\\7.chs",
	"\\root\\text\\selected\\8.chs",
	"\\root\\text\\selected\\9.chs",
	"\\root\\text\\selected\\10.chs",
	"\\root\\text\\selected\\11.chs",
	"\\root\\text\\battery\\big.chs",
	"\\root\\text\\battery\\small.chs",
	"\\root\\text\\battery\\symbol.chs",
	"\\root\\text\\error.chs",
	"\\root\\text\\unselect\\0.chs",
	"\\root\\text\\unselect\\1.chs",
	"\\root\\text\\unselect\\2.chs",
	"\\root\\text\\unselect\\3.chs",
	"\\root\\text\\unselect\\4.chs",
	"\\root\\text\\unselect\\5.chs",
	"\\root\\text\\unselect\\6.chs",
	"\\root\\text\\unselect\\7.chs",
	"\\root\\text\\unselect\\8.chs",
	"\\root\\text\\unselect\\9.chs",
	"\\root\\text\\unselect\\10.chs",
	"\\root\\text\\unselect\\11.chs",
	"\\root\\text\\bold\\0.chs",
	"\\root\\text\\bold\\1.chs",
	"\\root\\text\\bold\\2.chs",
	"\\root\\text\\bold\\3.chs",
	"\\root\\text\\bold\\4.chs",
	"\\root\\text\\bold\\5.chs",
	"\\root\\text\\bold\\6.chs",
	"\\root\\text\\bold\\7.chs",
	"\\root\\text\\bold\\8.chs",
	"\\root\\text\\bold\\9.chs",
	"\\root\\text\\bold\\10.chs",
	"\\root\\text\\bold\\11.chs",
};

/******************************** 档位 ************************************/
const TextInfo TextListShiftTable[12][4] = 
{	/*文本内容  字库路径 			x  y  文本宽度 字间距    颜色  				滚动方式*/
	{/*简体中文*/
		{"持久", LanguageList[28], 0, 11,    240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"强劲", LanguageList[28], 0, 11,    240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"超强", LanguageList[28], 0, 11,    240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"自动", LanguageList[28], 0, 11,    240,    -14,  0, 0xFFFF, RollType_Order_Center_Left},
	},
	{/*英语*/
		{"Eco", 	LanguageList[29], 0, 11,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"Med", 	LanguageList[29], 0, 11,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"Turbo", LanguageList[29], 0, 11,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"Auto", 	LanguageList[29], 0, 11,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left},
	},
	{/*繁体中文*/
		{"持久", LanguageList[30], 0, 11,    240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"強勁", LanguageList[30], 0, 11,    240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"超強", LanguageList[30], 0, 11,    240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"自動", LanguageList[30], 0, 11,    240,    -14,  0, 0xFFFF, RollType_Order_Center_Left},
	},
	{/*日语*/
		{"エコ", 				LanguageList[31], 0, 12,    240,    -18,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"スタンダード", LanguageList[31], 0, 16,    240,    -21,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"ターボ", 			LanguageList[31], 0, 12,    240,    -18,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"自動", 				LanguageList[31], 0, 12,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left},
	},
	{/*韩语*/
		{"에코", LanguageList[32], 0, 18,    240,    -17,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"중간", LanguageList[32], 0, 18,    240,    -17,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"터보", LanguageList[32], 0, 18,    240,    -17,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"자동", LanguageList[32], 0, 18,    240,    -17,  0, 0xFFFF, RollType_Order_Center_Left},
	},
	{/*德语*/
		{"Eco", 			LanguageList[33], 0, 8,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"Standard", 	LanguageList[33], 0, 10,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"Power", 		LanguageList[33], 0, 10,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"Auto",		 	LanguageList[33], 0, 8,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left},
	},
	{/*法语*/
		{"Eco", 		LanguageList[34], 0, 15,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"Médium", 	LanguageList[34], 0, 15,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"Turbo", 	LanguageList[34], 0, 15,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"Auto", 		LanguageList[34], 0, 15,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left},
	},
	{/*意大利语*/
		{"Eco", 	LanguageList[35], 0, 13,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"Med", 	LanguageList[35], 0, 13,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"Turbo", LanguageList[35], 0, 13,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"Auto", 	LanguageList[35], 0, 13,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left},
	},
	{/*西班牙语*/
		{"Eco", 	LanguageList[36], 0, 13,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"Med", 	LanguageList[36], 0, 13,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"Turbo", LanguageList[36], 0, 13,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"Auto", 	LanguageList[36], 0, 13,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left},
	},
	{/*俄语*/
		{"Эко", 					LanguageList[37], 0, 12,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"Стандарт", LanguageList[37], 0, 12,    240,    -18,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"Турбо", 			LanguageList[37], 0, 12,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"Авто", 				LanguageList[37], 0, 12,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left},
	},
	{/*阿拉伯语*/
		{"موفر", 	LanguageList[38], 0, 11,    240,    -17,  -0, 0xFFFF, RollType_Order_Center_Right}, 
		{"متوسط", LanguageList[38], 0, 11,    240,    -17,  0, 0xFFFF, RollType_Order_Center_Right}, 
		{"قوي", 	LanguageList[38], 0, 11,    240,    -17,  0, 0xFFFF, RollType_Order_Center_Right}, 
		{"تلقائي", 	LanguageList[38], 0, 11,    240,    -17,  0, 0xFFFF, RollType_Order_Center_Right},
	},
	{/*希伯来语*/
		{"אקו", 		LanguageList[39], 0, 12,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Right}, 
		{"בינוני", 	LanguageList[39], 0, 12,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Right}, 
		{"טורבו", 	LanguageList[39], 0, 12,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Right}, 
		{"אוטומטי", 	LanguageList[39], 0, 12,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Right},
	},
};
/******************************** 主菜单 ************************************/
const TextInfo TextListMainMenuSelectedTable[12][4] = 
{	/*		文本内容  						字库路径 		 x   y    文本宽度 字间距    颜色  				滚动方式*/
	{/*简体中文*/
		{"清洁记录",			LanguageList[0], 0, 10-3,      240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"重置滤芯",			LanguageList[0], 0, 20-3,     240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"语言选择",			LanguageList[0], 0, 90-3,    240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"退出",				LanguageList[0], 0, 160-3,    240,    -14,  0, 0xFFFF, RollType_Order_Center_Left},
	},
	{/*英语*/
		{"Cleaning Record  ", 	LanguageList[1], 0, 10-4,      240,    -15,  -10, 0xFFFF, RollType_Order_Center_Left}, 
		{"Filter Reset",		LanguageList[1], 20,	20-3,     240,    -15,  -10, 0xFFFF, RollType_Order_Center_Left}, 
		{"Select Language  ", 	LanguageList[1], 0, 90-2,    240,    -15,  -10, 0xFFFF, RollType_Order_Center_Left}, 
		{"Exit",				LanguageList[1], 0, 160-2,    240,    -15,  -10, 0xFFFF, RollType_Order_Center_Left},
	},
	{/*繁体中文*/
		{"清潔記錄", 					LanguageList[2], 0, 10-3,      240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"重置濾芯", 					LanguageList[2], 0, 65-3,     240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"語言選擇", 					LanguageList[2], 0, 120-3,    240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"退出",			 				LanguageList[2], 0, 175-3,    240,    -14,  0, 0xFFFF, RollType_Order_Center_Left},
	},
	{/*日语*/
		{"クリーニング記録 ", 	LanguageList[3], 0, 10-3,      240,    -17,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"フィルターリセット ", LanguageList[3], 0, 65-3,     240,    -20,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"言語を選択する ", 		LanguageList[3], 0, 120-3,    240,    -16,  0, 0xFFFF, RollType_Order_Center_Left}, 
		{"終了",			 				LanguageList[3], 0, 175-3,    240,    -16,  0, 0xFFFF, RollType_Order_Center_Left},
	},
	{/*韩语*/
		{"청소 기록", 					LanguageList[4], 2, 10+9,     240,    -17,  -20, 0xFFFF, RollType_Order_Center_Left}, 
		{"필터 초기화", 				LanguageList[4], 0, 65+6,     240,    -17,  -20, 0xFFFF, RollType_Order_Center_Left}, 
		{"언어 선택", 					LanguageList[4], 0, 120+9,    240,    -17,  -20, 0xFFFF, RollType_Order_Center_Left}, 
		{"나가기",			 			LanguageList[4], 0, 175+7,    240,    -17,  0, 0xFFFF, RollType_Order_Center_Left},
	},
	{/*德语*/
		{"Reinigungsprotokoll   ", 	LanguageList[5], 0, 10,     240,    -13,  -15, 0xFFFF, RollType_Order_Center_Left}, 
		{"Filter Reset", 					LanguageList[5], 0, 65-6,     240,    -13,  -15, 0xFFFF, RollType_Order_Center_Left}, 
		{"Sprache Wählen  ", 				LanguageList[5], 0, 120-7,    240,    -13,  -23, 0xFFFF, RollType_Order_Center_Left}, 
		{"Beenden",			 					LanguageList[5], 0, 175-8,    240,    -13,  -15, 0xFFFF, RollType_Order_Center_Left},
	},
	{/*法语*/
		{"Nettoyage du dossier     ", 		LanguageList[6], 0, 10,      240,    -15,  -26, 0xFFFF, RollType_Order_Center_Left}, 
		{"Réinitialiser le filtre    ",	LanguageList[6], 0, 65+1,     240,    -15,  -21, 0xFFFF, RollType_Order_Center_Left}, 
		{"Sélectionner la langue     ",	LanguageList[6], 0, 120-2,    240,    -15,  -20, 0xFFFF, RollType_Order_Center_Left}, 
		{"Sortie",			 						LanguageList[6], 0, 175,    240,    -15,  0, 0xFFFF, RollType_Order_Center_Left},
	},
	{/*意大利语*/
		{"Record di Pulizia   ", 		LanguageList[7], 0, 10,      240,    -13,  -15, 0xFFFF, RollType_Order_Center_Left}, 
		{"Ripristino del Filtro   ",	LanguageList[7], 0, 65-1,     240,    -15,  -13, 0xFFFF, RollType_Order_Center_Left}, 
		{"Seleziona Lingua   ", 			LanguageList[7], 0, 120-1,    240,    -15,  -13, 0xFFFF, RollType_Order_Center_Left}, 
		{"Esci",			 						LanguageList[7], 0, 175,    240,    -13,  -13, 0xFFFF, RollType_Order_Center_Left},
	},
	{/*西班牙语*/
		{"Historial de Limpieza   ", 	LanguageList[8], 0, 10+2,      240,    -15,  -20, 0xFFFF, RollType_Order_Center_Left}, 
		{"Restablecer del Filtro   ",	LanguageList[8], 0, 65+2,     240,    -15,  -13, 0xFFFF, RollType_Order_Center_Left}, 
		{"Seleccionar Idioma  ",			LanguageList[8], 0, 120+3,    240,    -15,  -18, 0xFFFF, RollType_Order_Center_Left}, 
		{"Salir",			 							LanguageList[8], 0, 175+2,    240,    -15,  -20, 0xFFFF, RollType_Order_Center_Left},
	},
	{/*俄语*/
		{"Запись уборки   ", 	LanguageList[9], 0, 10,      240,    -15,  -15, 0xFFFF, RollType_Order_Center_Left}, 
		{"Сброс фильтра  ",		LanguageList[9], 0, 65-1,     240,    -15,  -15, 0xFFFF, RollType_Order_Center_Left}, 
		{"Выбрать язык  ", 		LanguageList[9], 0, 120,    240,    -15,  -15, 0xFFFF, RollType_Order_Center_Left}, 
		{"Выход",			 						LanguageList[9], 0, 175,    240,    -15,  -15, 0xFFFF, RollType_Order_Center_Left},
	},
	{/*阿拉伯语*/
		{"   سجل التظيف", 	LanguageList[10], 0, 10,     240,    -18,  -20, 0xFFFF, RollType_Order_Center_Right}, 
		{"   تعيين الفلتر", 		LanguageList[10], 0, 65,    240,    -18,  -20, 0xFFFF, RollType_Order_Center_Right}, 
		{"   اختر اللغة", 		LanguageList[10], 0, 120,   240,    -18,  -20, 0xFFFF, RollType_Order_Center_Right}, 
		{"خروج",			LanguageList[10], 0, 175,   240,    -18,  -20, 0xFFFF, RollType_Order_Center_Right},
	},
	{/*希伯来语*/
		{"   הקלטה תוך כדי עבודת ניקיון",	LanguageList[11], 0, 10,     240,    -15,  -15, 0xFFFF, RollType_Order_Center_Right}, 
		{"איפוס מסנן", 					LanguageList[11], 0, 65,    240,    -15,  -15, 0xFFFF, RollType_Order_Center_Right}, 
		{"בחר שפה", 					LanguageList[11], 0, 120,   240,    -15,  -15, 0xFFFF, RollType_Order_Center_Right}, 
		{"יציאה",			 				LanguageList[11], 0, 175,   240,    -15,  -15, 0xFFFF, RollType_Order_Center_Right},
	},
};

const TextInfo TextListMainMenuTable[12][4] = 
{	/*		文本内容  						字库路径 		 x   y    文本宽度 字间距    颜色  				滚动方式*/
	{/*简体中文*/
//		{"清洁记录",			LanguageList[16], 0, 10,      240,    -14,  0, 0x8410, RollType_Order_Center_Left}, 
//		{"重置滤芯",			LanguageList[16], 0, 65,     240,    -14,  0, 0x8410, RollType_Order_Center_Left}, 
//		{"语言选择",			LanguageList[16], 0, 120,    240,    -14,  0, 0x8410, RollType_Order_Center_Left}, 
//		{"退出",				LanguageList[16], 0, 175,    240,    -14,  0, 0x8410, RollType_Order_Center_Left},
		{"清洁记录",			LanguageList[16], 0, 10,	240,    -14,  0, 0x8410, RollType_Order_Center_Left}, 
		{"重置滤芯",			LanguageList[16], 0, 20,	240,    -14,  0, 0x8410, RollType_Order_Center_Left}, 
		{"语言选择",			LanguageList[16], 0, 90,    240,    -14,  0, 0x8410, RollType_Order_Center_Left}, 
		{"退出",				LanguageList[16], 0, 160,	240,    -14,  0, 0x8410, RollType_Order_Center_Left},
	},
	{/*英语*/
		{"Cleaning Record   ", 	LanguageList[17], 25, 10+2,      240,    -15,  -10, 0x8410, RollType_Order_Center_Left}, 
		{"Filter Reset",		LanguageList[17], 25, 20+1,     240,    -15,  -10, 0x8410, RollType_Order_Center_Left}, 
		{"Select Language   ", 	LanguageList[17], 0, 90-1,    240,    -15,  -10, 0x8410, RollType_Order_Center_Left}, 
		{"Exit",				LanguageList[17], 0, 160+5,    240,    -15,  -10, 0x8410, RollType_Order_Center_Left},
	},
	{/*繁体中文*/
		{"清潔記錄", 					LanguageList[18], 0, 10,      240,    -14,  0, 0x8410, RollType_Order_Center_Left}, 
		{"重置濾芯", 					LanguageList[18], 0, 65,     240,    -14,  0, 0x8410, RollType_Order_Center_Left}, 
		{"語言選擇", 					LanguageList[18], 0, 120,    240,    -14,  0, 0x8410, RollType_Order_Center_Left}, 
		{"退出",			 				LanguageList[18], 0, 175,    240,    -14,  0, 0x8410, RollType_Order_Center_Left},
	},
	{/*日语*/
		{"クリーニング記録   ", 	LanguageList[19], 20, 10,      220,    -16,  0, 0x8410, RollType_Order_Center_Left}, 
		{"フィルターリセット   ", LanguageList[19], 10, 65,     230,    -17,  0, 0x8410, RollType_Order_Center_Left}, 
		{"言語を選択する", 		LanguageList[19], 10, 120,    230,    -16,  0, 0x8410, RollType_Order_Center_Left}, 
		{"終了",			 				LanguageList[19], 10, 175,    230,    -15,  0, 0x8410, RollType_Order_Center_Left},
	},
	{/*韩语*/
		{"청소 기록", 					LanguageList[20], 0, 10+9,     240,    -17,  -20, 0x8410, RollType_Order_Center_Left}, 
		{"필터 초기화", 				LanguageList[20], 0, 65+11,     240,    -17,  -20, 0x8410, RollType_Order_Center_Left}, 
		{"언어 선택", 					LanguageList[20], 0, 120+9,    240,    -17,  -20, 0x8410, RollType_Order_Center_Left}, 
		{"나가기",			 			LanguageList[20], 0, 175+7,    240,    -17,  -20, 0x8410, RollType_Order_Center_Left},
	},
	{/*德语*/
		{"Reinigungsprotokoll", 	LanguageList[21], 30, 10,      240,    -13,  -10, 0x8410, RollType_Order_Center_Left}, 
		{"Filter Reset", 					LanguageList[21], 0, 60+6,     240,    -13,  -10, 0x8410, RollType_Order_Center_Left}, 
		{"Sprache Wählen", 				LanguageList[21], 0, 120-4,    240,    -13,  -20, 0x8410, RollType_Order_Center_Left}, 
		{"Beenden",			 					LanguageList[21], 5, 175-8,    240,    -13,  -10, 0x8410, RollType_Order_Center_Left},
	},
	{/*法语*/
		{"Nettoyage du dossier", 		LanguageList[22], 30, 10,      240,    -15,  0, 0x8410, RollType_Order_Center_Left}, 
		{"Réinitialiser le filtre",	LanguageList[22], 0, 65+0,     240,    -15,  0, 0x8410, RollType_Order_Center_Left}, 
		{"Sélectionner la langue",	LanguageList[22], 0, 120+1,    240,    -15,  0, 0x8410, RollType_Order_Center_Left}, 
		{"Sortie",			 						LanguageList[22], 0, 175-3,    240,    -15,  0, 0x8410, RollType_Order_Center_Left},
	},
	{/*意大利语*/
		{"Record di Pulizia", 		LanguageList[23], 27, 10+4,      240,    -13,  -13, 0x8410, RollType_Order_Center_Left}, 
		{"Ripristino del Filtro",	LanguageList[23], 0, 65+2,     240,    -13,  -13, 0x8410, RollType_Order_Center_Left}, 
		{"Seleziona Lingua", 			LanguageList[23], 0, 120+1,    240,    -13,  -13, 0x8410, RollType_Order_Center_Left}, 
		{"Esci",			 						LanguageList[23], 0, 175+2,    240,    -13,  -13, 0x8410, RollType_Order_Center_Left},
	},
	{/*西班牙语*/
		{"Historial de Limpieza", 	LanguageList[24], 30, 10+5,      240,    -15,  -15, 0x8410, RollType_Order_Center_Left}, 
		{"Restablecer del Filtro",	LanguageList[24], 0, 65+5,     240,    -15,  -15, 0x8410, RollType_Order_Center_Left}, 
		{"Seleccionar Idioma",			LanguageList[24], 0, 120+5,    240,    -15,  -15, 0x8410, RollType_Order_Center_Left}, 
		{"Salir",			 							LanguageList[24], 0, 175+5,    240,    -15,  -15, 0x8410, RollType_Order_Center_Left},
	},
	{/*俄语*/
		{"Запись уборки", 	LanguageList[25], 30, 10,      240,    -15,  -15, 0x8410, RollType_Order_Center_Left}, 
		{"Сброс фильтра",		LanguageList[25], 0, 65,     240,    -15,  -15, 0x8410, RollType_Order_Center_Left}, 
		{"Выбрать язык", 		LanguageList[25], 0, 120,    240,    -15,  -15, 0x8410, RollType_Order_Center_Left}, 
		{"Выход",			 						LanguageList[25], 0, 175,    240,    -15,  -15, 0x8410, RollType_Order_Center_Left},
	},
	{/*阿拉伯语*/
		{"سجل التظيف", 	LanguageList[26], 0, 10,     220,    -18,  -20, 0x8410, RollType_Order_Center_Right}, 
		{"تعيين الفلتر", 		LanguageList[26], 0, 65,    240,    -18,  -20, 0x8410, RollType_Order_Center_Right}, 
		{"اختر اللغة", 		LanguageList[26], 0, 120,   240,    -18,  -20, 0x8410, RollType_Order_Center_Right}, 
		{"خروج",			LanguageList[26], 0, 175,   240,    -18,  -20, 0x8410, RollType_Order_Center_Right},
	},
	{/*希伯来语*/
		{"הקלטה תוך כדי עבודת ניקיון",	LanguageList[27], 0, 10,     215,    -15,  -15, 0x8410, RollType_Order_Center_Right}, 
		{"איפוס מסנן", 					LanguageList[27], 0, 65,    240,    -15,  -15, 0x8410, RollType_Order_Center_Right}, 
		{"בחר שפה", 					LanguageList[27], 0, 120,   240,    -15,  -15, 0x8410, RollType_Order_Center_Right}, 
		{"יציאה",			 				LanguageList[27], 0, 175,   240,    -15,  -15, 0x8410, RollType_Order_Center_Right},
	},
};

/******************************** 历史数据 ************************************/
const TextInfo TextListHistoryTable[12] = 
{
	/*		文本内容  						字库路径 		 x   y    文本宽度 字间距    颜色  				滚动方式*/
	{"最近7天", 											LanguageList[0], 0, 180,      240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, /*简体中文*/
	{"Last 7 days", 								LanguageList[1], 0, 180,      240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, /*英语*/
	{"最近7天", 											LanguageList[2], 0, 180,      240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, /*繁体中文*/
	{"直近七日間", 									LanguageList[3], 0, 180,      240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, /*日语*/
	{"최근 7일", 											LanguageList[4], 30, 180,     240,    -15,  -30, 0xFFFF, RollType_Order_Center_Left}, /*韩语*/
	{"Die letzten 7 Tage        ", 	LanguageList[5], 0, 180,      240,    -13,  -20, 0xFFFF, RollType_Order_Center_Left}, /*德语*/
	{"Les 7 derniers jours     ", 	LanguageList[6], 0, 180,      240,    -15,  -20, 0xFFFF, RollType_Order_Center_Left}, /*法语*/
	{"Ultimi 7 giorni    ", 				LanguageList[7], 0, 180,      240,    -13,  -23, 0xFFFF, RollType_Order_Center_Left}, /*意大利语*/
	{"Los últimos 7 días    ", 			LanguageList[8], 0, 180,      240,    -15,  -20, 0xFFFF, RollType_Order_Center_Left}, /*西班牙语*/
	{"Последние 7 дней   ",	LanguageList[9], 0, 180,      240,    -15,  -20, 0xFFFF, RollType_Order_Center_Left}, /*俄语*/
	{"آخر7 أيام", 												LanguageList[10], 40, 180,      240,    -18,  -20, 0xFFFF, RollType_Order_Center_Right}, /*阿拉伯语*/
	{"   שבעת הימים האחרונים", 						LanguageList[11], 0, 180,      240,    -15,  -22, 0xFFFF, RollType_Order_Center_Right}, /*希伯来语*/
};

/******************************** 语言列表 ************************************/
const TextInfo TextListLanguageTable[12] = 
{
	/*		文本内容  	字库路径 		 	x   y    文本宽度 字间距    颜色  				滚动方式*/
	{"简体中文",		LanguageList[0],	0,	65-6,	240,    -14,  0, 0x8410, RollType_Order_Center_Left}, /*简体中文*/
	{"English",			LanguageList[1],	0,	120,	240,    -15,  0, 0x8410, RollType_Order_Center_Left}, /*英语*/
};

const TextInfo TextListLanguageSelectedTable[12] = 
{
	/*		文本内容		字库路径 		 x   y    文本宽度 字间距    颜色  				滚动方式*/
	{"简体中文",		LanguageList[0],	0, 	65-4,	240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, /*简体中文*/
	{"English",			LanguageList[1],	0, 	120-3,	240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, /*英语*/
};
/******************************** 故障列表 ************************************/
//故障代码
const TextInfo TextListErrorCodeTable[12] = 
{
	/*文本内容  			 		字库路径 		  x   y    文本宽度 字间距  颜色  				滚动方式*/
	{"①", 						LanguageList[15], 0, 130,    240,    -10,  0, 0xFFFF, RollType_Order_Center_Left}, 
	{"②", 						LanguageList[15], 0, 130,    240,    -10,  0, 0xFFFF, RollType_Order_Center_Left}, 
	{"③", 						LanguageList[15], 0, 130,    240,    -10,  0, 0xFFFF, RollType_Order_Center_Left},
	{"④", 						LanguageList[15], 0, 130,    240,    -10,  0, 0xFFFF, RollType_Order_Center_Left},
	{"⑤", 						LanguageList[15], 0, 130,    240,    -10,  0, 0xFFFF, RollType_Order_Center_Left}, 
	{"⑥", 						LanguageList[15], 0, 130,    240,    -10,  0, 0xFFFF, RollType_Order_Center_Left},
	{"⑦", 						LanguageList[15], 0, 130,    240,    -10,  0, 0xFFFF, RollType_Order_Center_Left},
	{"⑧", 						LanguageList[15], 0, 130,    240,    -10,  0, 0xFFFF, RollType_Order_Center_Left},
	{"⑨", 						LanguageList[15], 0, 130,    240,    -10,  0, 0xFFFF, RollType_Order_Center_Left},
	{"⑩", 						LanguageList[15], 0, 130,    240,    -10,  0, 0xFFFF, RollType_Order_Center_Left},
};
//全堵风口
const TextInfo TextListTuyereBlockedTable[12] = 
{
	/*		文本内容				字库路径 		 x   y    	文本宽度 字间距    颜色  				滚动方式*/
	{"风道堵塞",					LanguageList[0], 0, 130,      240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, /*简体中文*/
	{"Air duct blocked   ",			LanguageList[1], 0, 130,      240,    -15,  -15, 0xFFFF, RollType_Order_Center_Left}, /*英语*/
	{"風道堵塞",					LanguageList[2], 0, 130,      240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, /*繁体中文*/
	{"エアダクトが詰まっています ",	LanguageList[3], 0, 130,      240,    -17,  0, 0xFFFF, RollType_Order_Center_Left}, /*日语*/
	{"에어 덕트 막힘    ",				LanguageList[4], 0, 130,      240,    -15,  -30, 0xFFFF, RollType_Order_Center_Left}, /*韩语*/
	{"Luftkanal blockiert  ", 										LanguageList[5], 0, 130,      240,    -13,  -13, 0xFFFF, RollType_Order_Center_Left}, /*德语*/
	{"Conduit d’air bloqué    ", 									LanguageList[6], 0, 130,      240,    -15,  -20, 0xFFFF, RollType_Order_Center_Left}, /*法语*/
	{"Condotto dell'aria bloccato   ", 						LanguageList[7], 0, 130,      240,    -13,  -17, 0xFFFF, RollType_Order_Center_Left}, /*意大利语*/
	{"Conducto de aire bloqueado   ", 							LanguageList[8], 0, 130,      240,    -15,  -13, 0xFFFF, RollType_Order_Center_Left}, /*西班牙语*/
	{"Воздуховод заблокирован   ", 	LanguageList[9], 0, 130,      240,    -15,  -15, 0xFFFF, RollType_Order_Center_Left}, /*俄语*/
	{"   انسداد مجرى الهواء", 																		LanguageList[10], 0, 130,      240,    -18,  -20, 0xFFFF, RollType_Order_Center_Right}, /*阿拉伯语*/
	{"    תעלת האוויר חסומה", 																LanguageList[11], 0, 130,      240,    -15,  -20, 0xFFFF, RollType_Order_Center_Right}, /*希伯来语*/
};
//地刷堵转
const TextInfo TextListRollerStallTable[12] = 
{
	/*		文本内容  										字库路径 		 x   y    	文本宽度 字间距    颜色  				滚动方式*/
	{"清理滚刷", 											LanguageList[0], 0, 130,      240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, /*简体中文*/
	{"Clean the brush   ", 						LanguageList[1], 0, 130,      240,    -15,  -15, 0xFFFF, RollType_Order_Center_Left}, /*英语*/
	{"清理滾刷", 											LanguageList[2], 0, 130,      240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, /*繁体中文*/
	{"ブラシを清掃する ", 							LanguageList[3], 0, 130,      240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, /*日语*/
	{"브러시 세척", 											LanguageList[4], 9, 130,      240,    -15,  -30, 0xFFFF, RollType_Order_Center_Left}, /*韩语*/
	{"Reinigen Sie die Bürste   ", 		LanguageList[5], 0, 130,      240,    -13,  -15, 0xFFFF, RollType_Order_Center_Left}, /*德语*/
	{"Nettoyer la brosse     ", 			LanguageList[6], 0, 130,      240,    -15,  -26, 0xFFFF, RollType_Order_Center_Left}, /*法语*/
	{"Pulisci la spazzola     ", 			LanguageList[7], 0, 130,      240,    -13,  -17, 0xFFFF, RollType_Order_Center_Left}, /*意大利语*/
	{"Limpiar el cepillo   ", 				LanguageList[8], 0, 130,      240,    -15,  -20, 0xFFFF, RollType_Order_Center_Left}, /*西班牙语*/
	{"Очистить щетку   ",	LanguageList[9], 0, 130,      240,    -15,  -25, 0xFFFF, RollType_Order_Center_Left}, /*俄语*/
	{"   تنظيف الفرشاة", 												LanguageList[10], 0, 130,      240,    -18,  -20, 0xFFFF, RollType_Order_Center_Right}, /*阿拉伯语*/
	{"    נקה את המברשת", 										LanguageList[11], 0, 130,      240,    -15,  -20, 0xFFFF, RollType_Order_Center_Right}, /*希伯来语*/
};
//电池过温
const TextInfo TextListOvertemperatureTable[12] = 
{
	/*		文本内容  													字库路径 		 x   y    	文本宽度 字间距    颜色  				滚动方式*/
	{"电池过热", 														LanguageList[0], 0, 130,      240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, /*简体中文*/
	{"Battery overheating   ", 							LanguageList[1], 0, 130,      240,    -15,  -15, 0xFFFF, RollType_Order_Center_Left}, /*英语*/
	{"電池過熱", 														LanguageList[2], 0, 130,      240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, /*繁体中文*/
	{"バッテリー過熱 ", 											LanguageList[3], 0, 130,      240,    -16,  0, 0xFFFF, RollType_Order_Center_Left}, /*日语*/
	{"배터리 과열", 														LanguageList[4], 9, 130,      240,    -15,  -30, 0xFFFF, RollType_Order_Center_Left}, /*韩语*/
	{"Batterieüberhitzung   ", 							LanguageList[5], 0, 130,      240,    -13,  -15, 0xFFFF, RollType_Order_Center_Left}, /*德语*/
	{"Surchauffe de la batterie     ", 			LanguageList[6], 0, 130,      240,    -15,  -20, 0xFFFF, RollType_Order_Center_Left}, /*法语*/
	{"Surriscaldamento della batteria   ",	LanguageList[7], 0, 130,      240,    -13,  -20, 0xFFFF, RollType_Order_Center_Left}, /*意大利语*/
	{"Batería sobrecalentada   ", 					LanguageList[8], 0, 130,      240,    -15,  -13, 0xFFFF, RollType_Order_Center_Left}, /*西班牙语*/
	{"Перегрев батареи   ", 		LanguageList[9], 0, 130,      240,    -15,  -20, 0xFFFF, RollType_Order_Center_Left}, /*俄语*/
	{"   ارتفاع حرارة البطارية", 												LanguageList[10], 0, 130,      240,    -18,  -20, 0xFFFF, RollType_Order_Center_Right}, /*阿拉伯语*/
	{"    התחממות יתר של הסוללה", 									LanguageList[11], 0, 130,      240,    -15,  -20, 0xFFFF, RollType_Order_Center_Right}, /*希伯来语*/
};
//滤芯未安装
const TextInfo TextListFilterNotInstalledTable[12] = 
{
	/*		文本内容  						字库路径 		 x   y    文本宽度 字间距    颜色  				滚动方式*/
	{"滤芯未安装", 													LanguageList[0], 0, 130,      240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, /*简体中文*/
	{"Filter not installed    ", 						LanguageList[1], 0, 130,      240,    -15,  -15, 0xFFFF, RollType_Order_Center_Left}, /*英语*/
	{"濾網未安裝", 													LanguageList[2], 0, 130,      240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, /*繁体中文*/
	{"フィルター未取付 ", 									LanguageList[3], 0, 130,      240,    -16,  0, 0xFFFF, RollType_Order_Center_Left}, /*日语*/
	{"필터 미설치", 														LanguageList[4], 14, 130,      240,    -15,  -30, 0xFFFF, RollType_Order_Center_Left}, /*韩语*/
	{"Filter ist nicht installiert     ", 	LanguageList[5], 0, 130,      240,    -13,  -15, 0xFFFF, RollType_Order_Center_Left}, /*德语*/
	{"Filtre désinstallé     ", 						LanguageList[6], 0, 130,      240,    -15,  -20, 0xFFFF, RollType_Order_Center_Left}, /*法语*/
	{"Filtro non installato     ", 					LanguageList[7], 0, 130,      240,    -13,  -15, 0xFFFF, RollType_Order_Center_Left}, /*意大利语*/
	{"Filtro no instalado   ", 							LanguageList[8], 0, 130,      240,    -15,  -13, 0xFFFF, RollType_Order_Center_Left}, /*西班牙语*/
	{"Фильтр не установлен   ",	LanguageList[9], 0, 130,      240,    -15,  -20, 0xFFFF, RollType_Order_Center_Left}, /*俄语*/
	{"   لم يثبت الفلتر", 															LanguageList[10], 0, 130,      240,    -18,  -20, 0xFFFF, RollType_Order_Center_Right}, /*阿拉伯语*/
	{"    המסנן הוסר", 															LanguageList[11], 0, 130,      240,    -15,  -20, 0xFFFF, RollType_Order_Center_Right}, /*希伯来语*/
};
//电量低
const TextInfo TextListBatteryLowTable[12] = 
{
	/*		文本内容  						字库路径 		 x   y    文本宽度 字间距    颜色  				滚动方式*/
	{"电量低", 																LanguageList[0], 0, 130,      240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, /*简体中文*/
	{"Low battery", 													LanguageList[1], 0, 130,      240,    -15,  -15, 0xFFFF, RollType_Order_Center_Left}, /*英语*/
	{"電量低", 																LanguageList[2], 0, 130,      240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, /*繁体中文*/
	{"バッテリー低下 ", 												LanguageList[3], 0, 130,      240,    -16,  0, 0xFFFF, RollType_Order_Center_Left}, /*日语*/
	{"배터리 부족", 															LanguageList[4], 9, 130,      240,    -15,  -30, 0xFFFF, RollType_Order_Center_Left}, /*韩语*/
	{"Batteriestand niedrig   ", 							LanguageList[5], 0, 130,      240,    -13,  -15, 0xFFFF, RollType_Order_Center_Left}, /*德语*/
	{"Pile faible", 													LanguageList[6], 0, 130,      240,    -15,  -20, 0xFFFF, RollType_Order_Center_Left}, /*法语*/
	{"Batteria scarica    ", 									LanguageList[7], 0, 130,      240,    -13,  -17, 0xFFFF, RollType_Order_Center_Left}, /*意大利语*/
	{"Batería baja", 													LanguageList[8], 0, 130,      240,    -15,  -13, 0xFFFF, RollType_Order_Center_Left}, /*西班牙语*/
	{"Низкий заряд батареи   ",		LanguageList[9], 0, 130,      240,    -15,  -20, 0xFFFF, RollType_Order_Center_Left}, /*俄语*/
	{"  لبطارية منخفضة", 															LanguageList[10], 0, 130,      240,    -18,  -20, 0xFFFF, RollType_Order_Center_Right}, /*阿拉伯语*/
	{"   סוללה חלשה", 															LanguageList[11], 0, 130,      240,    -15,  -20, 0xFFFF, RollType_Order_Center_Right}, /*希伯来语*/
};
//电量耗尽
const TextInfo TextListBatteryOutTable[12] = 
{
	/*		文本内容  						字库路径 		 x   y    文本宽度 字间距    颜色  				滚动方式*/
	{"电量耗尽", 																LanguageList[0], 0, 130,      240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, /*简体中文*/
	{"Battery runs out   ", 										LanguageList[1], 0, 130,      240,    -15,  -15, 0xFFFF, RollType_Order_Center_Left}, /*英语*/
	{"電量耗盡", 																LanguageList[2], 0, 130,      240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, /*繁体中文*/
	{"電池が切れました ", 												LanguageList[3], 0, 130,      240,    -16,  0, 0xFFFF, RollType_Order_Center_Left}, /*日语*/
	{"배터리 없음", 																LanguageList[4], 9, 130,      240,    -15,  -30, 0xFFFF, RollType_Order_Center_Left}, /*韩语*/
	{"Der Akku ist leer    ", 									LanguageList[5], 0, 130,      240,    -13,  -20, 0xFFFF, RollType_Order_Center_Left}, /*德语*/
	{"La batterie est déchargée     ", 					LanguageList[6], 0, 130,      240,    -15,  -20, 0xFFFF, RollType_Order_Center_Left}, /*法语*/
	{"La batteria si esaurisce     ", 					LanguageList[7], 0, 130,      240,    -13,  -17, 0xFFFF, RollType_Order_Center_Left}, /*意大利语*/
	{"La batería se ha agotado    ", 						LanguageList[8], 0, 130,      240,    -15,  -15, 0xFFFF, RollType_Order_Center_Left}, /*西班牙语*/
	{"Батарея израсходована   ",	LanguageList[9], 0, 130,      240,    -15,  -15, 0xFFFF, RollType_Order_Center_Left}, /*俄语*/
	{"   نفاد طاقة البطارية", 																LanguageList[10], 0, 130,      240,    -18,  -20, 0xFFFF, RollType_Order_Center_Right}, /*阿拉伯语*/
	{"  הסוללה נגמרת", 																LanguageList[11], 0, 130,      240,    -15,  -15, 0xFFFF, RollType_Order_Center_Right}, /*希伯来语*/
};
//请更换滤芯
const TextInfo TextListReplaceFilterTable[12] = 
{
	/*		文本内容  						字库路径 		 x   y    文本宽度 字间距    颜色  				滚动方式*/
	{"更换并重置滤芯 ", 																	LanguageList[0], 0, 130,      240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, /*简体中文*/
	{"Replace and reset filter   ", 										LanguageList[1], 0, 130,      240,    -15,  -15, 0xFFFF, RollType_Order_Center_Left}, /*英语*/
	{"更換並重置濾芯 ", 																	LanguageList[2], 0, 130,      240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, /*繁体中文*/
	{"フィルターを交換してリセットします ", 								LanguageList[3], 0, 130,      240,    -20,  0, 0xFFFF, RollType_Order_Center_Left}, /*日语*/
	{"필터 교체 및 재설정   ", 																LanguageList[4], 0, 130,      240,    -15,  -27, 0xFFFF, RollType_Order_Center_Left}, /*韩语*/
	{"Filter wechseln und ersetzen     ", 							LanguageList[5], 0, 130,      240,    -14,  -20, 0xFFFF, RollType_Order_Center_Left}, /*德语*/
	{"Remplacer et initialiser le filtre     ", 				LanguageList[6], 0, 130,      240,    -16,  -28, 0xFFFF, RollType_Order_Center_Left}, /*法语*/
	{"Sostituisci e Ripristina il filtro     ", 				LanguageList[7], 0, 130,      240,    -13,  -17, 0xFFFF, RollType_Order_Center_Left}, /*意大利语*/
	{"Reemplazar y restablecer el filtro   ", 					LanguageList[8], 0, 130,      240,    -15,  -22, 0xFFFF, RollType_Order_Center_Left}, /*西班牙语*/
	{"Заменить и сбросить фильтр   ",	LanguageList[9], 0, 130,      240,    -16,  -22, 0xFFFF, RollType_Order_Center_Left}, /*俄语*/
	{"   تبديل وتعيين الفلتر", 																				LanguageList[10], 0, 130,      240,    -18,  -20, 0xFFFF, RollType_Order_Center_Right}, /*阿拉伯语*/
	{"    החלפה ואיפוס של המסנן", 																	LanguageList[11], 0, 130,      240,    -15,  -20, 0xFFFF, RollType_Order_Center_Right}, /*希伯来语*/
};
//滤芯将到期
const TextInfo TextListFilterExpireTable[12] = 
{
	/*		文本内容  						字库路径 		 x   y    文本宽度 字间距    颜色  				滚动方式*/
	{"滤芯将到期", 															LanguageList[0], 0, 130,      240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, /*简体中文*/
	{"Filter is expiring   ", 									LanguageList[1], 0, 130,      240,    -15,  -13, 0xFFFF, RollType_Order_Center_Left}, /*英语*/
	{"濾芯將到期", 															LanguageList[2], 0, 130,      240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, /*繁体中文*/
	{"フィルターの有効期限が切れます ", 					LanguageList[3], 0, 130,      240,    -17,  0, 0xFFFF, RollType_Order_Center_Left}, /*日语*/
	{"필터 교체 필요    ", 													LanguageList[4], 0, 130,      240,    -15,  -30, 0xFFFF, RollType_Order_Center_Left}, /*韩语*/
	{"Der Filter läuft bald ab   ", 						LanguageList[5], 0, 130,      240,    -13,  -20, 0xFFFF, RollType_Order_Center_Left}, /*德语*/
	{"Le filtre sera bientôt périmé   ", 				LanguageList[6], 0, 130,      240,    -15,  -25, 0xFFFF, RollType_Order_Center_Left}, /*法语*/
	{"Il filtro è in scadenza    ", 						LanguageList[7], 0, 130,      240,    -13,  -17, 0xFFFF, RollType_Order_Center_Left}, /*意大利语*/
	{"Filtro a punto de expirar   ", 						LanguageList[8], 0, 130,      240,    -15,  -15, 0xFFFF, RollType_Order_Center_Left}, /*西班牙语*/
	{"Фильтр требует замены   ",		LanguageList[9], 0, 130,      240,    -15,  -23, 0xFFFF, RollType_Order_Center_Left}, /*俄语*/
	{"   الفلتر قريب من الانتهاء", 															LanguageList[10], 0, 130,      240,    -18,  -20, 0xFFFF, RollType_Order_Center_Right}, /*阿拉伯语*/
	{"   מסנן עומד לפוג", 																LanguageList[11], 0, 130,      240,    -15,  -15, 0xFFFF, RollType_Order_Center_Right}, /*希伯来语*/
};

/******************************** 锁动画 ************************************/
//上锁
const TextInfo TextListLockTable[12] = 
{
	/*		文本内容  						字库路径 		 x   y    文本宽度 字间距    颜色  				滚动方式*/
	{"连续工作模式打开 ", 		LanguageList[0], 0, 130,      240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, /*简体中文*/
	{"Lock on", 						LanguageList[1], 10, 130,      240,    -15,  -15, 0xFFFF, RollType_Order_Center_Left}, /*英语*/
	{"連續工作模式打開 ", 		LanguageList[2], 0, 130,      240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, /*繁体中文*/
	{"ロックオン", 					LanguageList[3], 0, 130,      240,    -17,  0, 0xFFFF, RollType_Order_Center_Left}, /*日语*/
	{"고정 켜짐", 							LanguageList[4], 24, 130,      240,    -15,  -30, 0xFFFF, RollType_Order_Center_Left}, /*韩语*/
	{"Geschlossen", 				LanguageList[5], 0, 130,      240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, /*德语*/
	{"Bloqué", 							LanguageList[6], 0, 130,      240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, /*法语*/
	{"Blocco on", 					LanguageList[7], 19, 130,      240,    -14,  -18, 0xFFFF, RollType_Order_Center_Left}, /*意大利语*/
	{"Bloqueo encendido   ",LanguageList[8], 0, 130,      240,    -15,  -15, 0xFFFF, RollType_Order_Center_Left}, /*西班牙语*/
	{"Блок вкл.", 		LanguageList[9], 20, 130,      240,    -15,  -20, 0xFFFF, RollType_Order_Center_Left}, /*俄语*/
	{"فتح القفل", 								LanguageList[10], 0, 130,      240,    -18,  -20, 0xFFFF, RollType_Order_Center_Right}, /*阿拉伯语*/
	{"  נעילה הפעלה", 						LanguageList[11], 0, 130,      240,    -15,  -15, 0xFFFF, RollType_Order_Center_Right}, /*希伯来语*/
};


//解锁
const TextInfo TextListUnlockTable[12] = 
{
	/*		文本内容  						字库路径 		 x   y    文本宽度 字间距    颜色  				滚动方式*/
	{"连续工作模式关闭 ", 		LanguageList[0], 0, 130,      240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, /*简体中文*/
	{"Lock off", 						LanguageList[1], 10, 130,      240,    -15,  -15, 0xFFFF, RollType_Order_Center_Left}, /*英语*/
	{"連續工作模式關閉 ", 		LanguageList[2], 0, 130,      240,    -14,  0, 0xFFFF, RollType_Order_Center_Left}, /*繁体中文*/
	{"ロックオフ", 					LanguageList[3], 0, 130,      240,    -17,  0, 0xFFFF, RollType_Order_Center_Left}, /*日语*/
	{"고정 꺼짐", 							LanguageList[4], 24, 130,      240,    -15,  -30, 0xFFFF, RollType_Order_Center_Left}, /*韩语*/
	{"Geöffnet", 						LanguageList[5], 5, 130,      240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, /*德语*/
	{"Débloqué", 						LanguageList[6], 0, 130,      240,    -15,  0, 0xFFFF, RollType_Order_Center_Left}, /*法语*/
	{"Blocco off", 					LanguageList[7], 19, 130,      240,    -14,  -18, 0xFFFF, RollType_Order_Center_Left}, /*意大利语*/
	{"Bloqueo apagado   ", 	LanguageList[8], 0, 130,      240,    -15,  -15, 0xFFFF, RollType_Order_Center_Left}, /*西班牙语*/
	{"Блок выкл.",		LanguageList[9], 0, 130,      240,    -16,  -20, 0xFFFF, RollType_Order_Center_Left}, /*俄语*/
	{"إغلاق القفل", 							LanguageList[10], 0, 130,      240,    -18,  -20, 0xFFFF, RollType_Order_Center_Right}, /*阿拉伯语*/
	{"  נעילה כיבוי", 							LanguageList[11], 0, 130,      240,    -15,  -15, 0xFFFF, RollType_Order_Center_Right}, /*希伯来语*/
};

