#include "StaticTextList.h"

/******************************** 字库路径 ************************************/
const char* LanguageList[15] = {
	"\\root\\text\\0.chs",
	"\\root\\text\\1.chs",
	"\\root\\text\\2.chs",
	"\\root\\text\\3.chs",
	"\\root\\text\\4.chs",
	"\\root\\text\\5.chs",
	"\\root\\text\\6.chs",
	"\\root\\text\\7.chs",
	"\\root\\text\\8.chs",
	"\\root\\text\\9.chs",
	"\\root\\text\\10.chs",
	"\\root\\text\\11.chs",
	"\\root\\text\\battery\\big.chs",
	"\\root\\text\\battery\\small.chs",
	"\\root\\text\\error.chs",
};

/******************************** 档位 ************************************/
const TextInfo TextListShiftTable[12][4] = 
{	/*文本内容  字库路径 			x  y  文本宽度 字间距    颜色  				滚动方式*/
	{/*简体中文*/
		{"持久", LanguageList[0], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"强劲", LanguageList[0], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"超强", LanguageList[0], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"自动", LanguageList[0], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left},
	},
	{/*英语*/
		{"节能", LanguageList[1], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"标准", LanguageList[1], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"强力", LanguageList[1], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"自动", LanguageList[1], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left},
	},
	{/*繁体中文*/
		{"节能", LanguageList[2], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"标准", LanguageList[2], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"强力", LanguageList[2], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"自动", LanguageList[2], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left},
	},
	{/*日语*/
		{"节能", LanguageList[3], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"标准", LanguageList[3], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"强力", LanguageList[3], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"自动", LanguageList[3], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left},
	},
	{/*韩语*/
		{"节能", LanguageList[4], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"标准", LanguageList[4], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"强力", LanguageList[4], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"自动", LanguageList[4], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left},
	},
	{/*德语*/
		{"节能", LanguageList[5], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"标准", LanguageList[5], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"强力", LanguageList[5], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"自动", LanguageList[5], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left},
	},
	{/*法语*/
		{"节能", LanguageList[6], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"标准", LanguageList[6], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"强力", LanguageList[6], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"自动", LanguageList[6], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left},
	},
	{/*意大利语*/
		{"节能", LanguageList[7], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"标准", LanguageList[7], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"强力", LanguageList[7], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"自动", LanguageList[7], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left},
	},
	{/*西班牙语*/
		{"节能", LanguageList[8], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"标准", LanguageList[8], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"强力", LanguageList[8], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"自动", LanguageList[8], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left},
	},
	{/*俄语*/
		{"节能", LanguageList[9], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"标准", LanguageList[9], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"强力", LanguageList[9], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"自动", LanguageList[9], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left},
	},
	{/*阿拉伯语*/
		{"节能", LanguageList[10], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"标准", LanguageList[10], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"强力", LanguageList[10], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"自动", LanguageList[01], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left},
	},
	{/*希伯来语*/
		{"节能", LanguageList[11], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"标准", LanguageList[11], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"强力", LanguageList[11], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
		{"自动", LanguageList[11], 0, 0,    240,    -10,  0xFFFF, RollType_Order_Center_Left},
	},
};
/******************************** 主菜单 ************************************/
const TextInfo TextListMainMenuTable[12][4] = 
{	/*		文本内容  						字库路径 		 x   y    文本宽度 字间距    颜色  				滚动方式*/
	{/*简体中文*/
		{"清洁记录", 					LanguageList[0], 0, 0,      240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"重置滤芯", 					LanguageList[0], 0, 60,     240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"语言选择", 					LanguageList[0], 0, 120,    240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"退出", 							LanguageList[0], 0, 180,    240,    -10,  0x8410, RollType_Order_Center_Left},
	},
	{/*英语*/
		{"清洁记录", 					LanguageList[1], 0, 0,      240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"重置滤芯", 					LanguageList[1], 0, 60,     240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"语言选择", 					LanguageList[1], 0, 120,    240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"退出",			 				LanguageList[1], 0, 180,    240,    -10,  0x8410, RollType_Order_Center_Left},
	},
	{/*繁体中文*/
		{"清洁记录", 					LanguageList[2], 0, 0,      240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"重置滤芯", 					LanguageList[2], 0, 60,     240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"语言选择", 					LanguageList[2], 0, 120,    240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"退出",			 				LanguageList[2], 0, 180,    240,    -10,  0x8410, RollType_Order_Center_Left},
	},
	{/*日语*/
		{"清洁记录", 					LanguageList[3], 0, 0,      240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"重置滤芯", 					LanguageList[3], 0, 60,     240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"语言选择", 					LanguageList[3], 0, 120,    240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"退出",			 				LanguageList[3], 0, 180,    240,    -10,  0x8410, RollType_Order_Center_Left},
	},
	{/*韩语*/
		{"清洁记录", 					LanguageList[4], 0, 0,      240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"重置滤芯", 					LanguageList[4], 0, 60,     240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"语言选择", 					LanguageList[4], 0, 120,    240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"退出",			 				LanguageList[4], 0, 180,    240,    -10,  0x8410, RollType_Order_Center_Left},
	},
	{/*德语*/
		{"清洁记录", 					LanguageList[5], 0, 0,      240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"重置滤芯", 					LanguageList[5], 0, 60,     240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"语言选择", 					LanguageList[5], 0, 120,    240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"退出",			 				LanguageList[5], 0, 180,    240,    -10,  0x8410, RollType_Order_Center_Left},
	},
	{/*法语*/
		{"清洁记录", 					LanguageList[6], 0, 0,      240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"重置滤芯", 					LanguageList[6], 0, 60,     240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"语言选择", 					LanguageList[6], 0, 120,    240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"退出",			 				LanguageList[6], 0, 180,    240,    -10,  0x8410, RollType_Order_Center_Left},
	},
	{/*意大利语*/
		{"历史记录", 					LanguageList[7], 0, 0,      240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"重置滤芯", 					LanguageList[7], 0, 60,     240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"语言选择", 					LanguageList[7], 0, 120,    240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"退出",			 				LanguageList[7], 0, 180,    240,    -10,  0x8410, RollType_Order_Center_Left},
	},
	{/*西班牙语*/
		{"历史记录", 					LanguageList[8], 0, 0,      240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"重置滤芯", 					LanguageList[8], 0, 60,     240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"语言选择", 					LanguageList[8], 0, 120,    240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"退出",			 				LanguageList[8], 0, 180,    240,    -10,  0x8410, RollType_Order_Center_Left},
	},
	{/*俄语*/
		{"历史记录", 					LanguageList[9], 0, 0,      240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"重置滤芯", 					LanguageList[9], 0, 60,     240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"语言选择", 					LanguageList[9], 0, 120,    240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"退出",			 				LanguageList[9], 0, 180,    240,    -10,  0x8410, RollType_Order_Center_Left},
	},
	{/*阿拉伯语*/
		{"历史记录", 					LanguageList[10], 0, 0,     240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"重置滤芯", 					LanguageList[10], 0, 60,    240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"语言选择", 					LanguageList[10], 0, 120,   240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"退出",			 				LanguageList[10], 0, 180,   240,    -10,  0x8410, RollType_Order_Center_Left},
	},
	{/*希伯来语*/
		{"历史记录", 					LanguageList[11], 0, 0,     240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"重置滤芯", 					LanguageList[11], 0, 60,    240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"语言选择", 					LanguageList[11], 0, 120,   240,    -10,  0x8410, RollType_Order_Center_Left}, 
		{"退出",			 				LanguageList[11], 0, 180,   240,    -10,  0x8410, RollType_Order_Center_Left},
	},
};

/******************************** 历史数据 ************************************/
const TextInfo TextListHistoryTable[12] = 
{
	/*		文本内容  						字库路径 		 x   y    文本宽度 字间距    颜色  				滚动方式*/
	{"最近7天", 						LanguageList[0], 0, 180,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*简体中文*/
	{"最近7天", 						LanguageList[1], 0, 180,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*英语*/
	{"最近7天", 						LanguageList[2], 0, 180,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*繁体中文*/
	{"最近7天", 						LanguageList[3], 0, 180,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*日语*/
	{"最近7天", 						LanguageList[4], 0, 180,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*韩语*/
	{"最近7天", 						LanguageList[5], 0, 180,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*德语*/
	{"最近7天", 						LanguageList[6], 0, 180,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*法语*/
	{"最近7天", 						LanguageList[7], 0, 180,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*意大利语*/
	{"最近7天", 						LanguageList[8], 0, 180,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*西班牙语*/
	{"最近7天", 						LanguageList[9], 0, 180,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*俄语*/
	{"最近7天", 						LanguageList[10], 0, 180,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*阿拉伯语*/
	{"最近7天", 						LanguageList[11], 0, 180,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*希伯来语*/
};

/******************************** 语言列表 ************************************/
const TextInfo TextListLanguageTable[12] = 
{
	/*		文本内容  						字库路径 		 x   y    文本宽度 字间距    颜色  				滚动方式*/
	{"简体中文", 						LanguageList[0], 0, 0,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*简体中文*/
	{"English", 						LanguageList[1], 0, 60,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*英语*/
	{"繁體中文", 						LanguageList[2], 0, 120,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*繁体中文*/
	{"日本語", 							LanguageList[3], 0, 180,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*日语*/
	{"한국어", 								LanguageList[4], 0, 0,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*韩语*/
	{"Deutsch", 						LanguageList[5], 0, 60,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*德语*/
	{"Français", 						LanguageList[6], 0, 120,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*法语*/
	{"Italiano", 						LanguageList[7], 0, 180,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*意大利语*/
	{"Español", 						LanguageList[8], 0, 0,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*西班牙语*/
	{"Pусский", 						LanguageList[9], 0, 60,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*俄语*/
	{"العربية", 						LanguageList[10], 0, 120,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*阿拉伯语*/
	{"עברית", 							LanguageList[11], 0, 180,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*希伯来语*/
};

/******************************** 故障列表 ************************************/
//故障代码
const TextInfo TextListErrorCodeTable[12] = 
{
	/*文本内容  			 		字库路径 		  x   y    文本宽度 字间距  颜色  				滚动方式*/
	{"①", 						LanguageList[14], 0, 130,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
	{"②", 						LanguageList[14], 0, 130,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
	{"③", 						LanguageList[14], 0, 130,    240,    -10,  0xFFFF, RollType_Order_Center_Left},
	{"④", 						LanguageList[14], 0, 130,    240,    -10,  0xFFFF, RollType_Order_Center_Left},
	{"⑤", 						LanguageList[14], 0, 130,    240,    -10,  0xFFFF, RollType_Order_Center_Left}, 
	{"⑥", 						LanguageList[14], 0, 130,    240,    -10,  0xFFFF, RollType_Order_Center_Left},
	{"⑦", 						LanguageList[14], 0, 130,    240,    -10,  0xFFFF, RollType_Order_Center_Left},
	{"⑧", 						LanguageList[14], 0, 130,    240,    -10,  0xFFFF, RollType_Order_Center_Left},
	{"⑨", 						LanguageList[14], 0, 130,    240,    -10,  0xFFFF, RollType_Order_Center_Left},
	{"⑩", 						LanguageList[14], 0, 130,    240,    -10,  0xFFFF, RollType_Order_Center_Left},
};
//全堵风口
const TextInfo TextListTuyereBlockedTable[12] = 
{
	/*		文本内容  						字库路径 		 x   y    文本宽度 字间距    颜色  				滚动方式*/
	{"风道堵塞", 						LanguageList[0], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*简体中文*/
	{"English", 						LanguageList[1], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*英语*/
	{"繁體中文", 						LanguageList[2], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*繁体中文*/
	{"日本語", 							LanguageList[3], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*日语*/
	{"한국어", 								LanguageList[4], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*韩语*/
	{"Deutsch", 						LanguageList[5], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*德语*/
	{"Français", 						LanguageList[6], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*法语*/
	{"Italiano", 						LanguageList[7], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*意大利语*/
	{"Español", 						LanguageList[8], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*西班牙语*/
	{"Pусский", 						LanguageList[9], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*俄语*/
	{"العربية", 						LanguageList[10], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*阿拉伯语*/
	{"עברית", 							LanguageList[11], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*希伯来语*/
};
//地刷堵转
const TextInfo TextListRollerStallTable[12] = 
{
	/*		文本内容  						字库路径 		 x   y    文本宽度 字间距    颜色  				滚动方式*/
	{"清理滚刷", 						LanguageList[0], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*简体中文*/
	{"English", 						LanguageList[1], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*英语*/
	{"繁體中文", 						LanguageList[2], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*繁体中文*/
	{"日本語", 							LanguageList[3], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*日语*/
	{"한국어", 								LanguageList[4], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*韩语*/
	{"Deutsch", 						LanguageList[5], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*德语*/
	{"Français", 						LanguageList[6], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*法语*/
	{"Italiano", 						LanguageList[7], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*意大利语*/
	{"Español", 						LanguageList[8], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*西班牙语*/
	{"Pусский", 						LanguageList[9], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*俄语*/
	{"العربية", 						LanguageList[10], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*阿拉伯语*/
	{"עברית", 							LanguageList[11], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*希伯来语*/
};
//电池过温
const TextInfo TextListOvertemperatureTable[12] = 
{
	/*		文本内容  						字库路径 		 x   y    文本宽度 字间距    颜色  				滚动方式*/
	{"电池过热", 						LanguageList[0], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*简体中文*/
	{"English", 						LanguageList[1], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*英语*/
	{"繁體中文", 						LanguageList[2], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*繁体中文*/
	{"日本語", 							LanguageList[3], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*日语*/
	{"한국어", 								LanguageList[4], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*韩语*/
	{"Deutsch", 						LanguageList[5], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*德语*/
	{"Français", 						LanguageList[6], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*法语*/
	{"Italiano", 						LanguageList[7], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*意大利语*/
	{"Español", 						LanguageList[8], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*西班牙语*/
	{"Pусский", 						LanguageList[9], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*俄语*/
	{"العربية", 						LanguageList[10], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*阿拉伯语*/
	{"עברית", 							LanguageList[11], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*希伯来语*/
};
//滤芯未安装
const TextInfo TextListFilterNotInstalledTable[12] = 
{
	/*		文本内容  						字库路径 		 x   y    文本宽度 字间距    颜色  				滚动方式*/
	{"滤芯未安装", 					LanguageList[0], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*简体中文*/
	{"English", 						LanguageList[1], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*英语*/
	{"繁體中文", 						LanguageList[2], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*繁体中文*/
	{"日本語", 							LanguageList[3], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*日语*/
	{"한국어", 								LanguageList[4], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*韩语*/
	{"Deutsch", 						LanguageList[5], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*德语*/
	{"Français", 						LanguageList[6], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*法语*/
	{"Italiano", 						LanguageList[7], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*意大利语*/
	{"Español", 						LanguageList[8], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*西班牙语*/
	{"Pусский", 						LanguageList[9], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*俄语*/
	{"العربية", 						LanguageList[10], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*阿拉伯语*/
	{"עברית", 							LanguageList[11], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*希伯来语*/
};
//电量低
const TextInfo TextListBatteryLowTable[12] = 
{
	/*		文本内容  						字库路径 		 x   y    文本宽度 字间距    颜色  				滚动方式*/
	{"电量低", 							LanguageList[0], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*简体中文*/
	{"English", 						LanguageList[1], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*英语*/
	{"繁體中文", 						LanguageList[2], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*繁体中文*/
	{"日本語", 							LanguageList[3], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*日语*/
	{"한국어", 								LanguageList[4], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*韩语*/
	{"Deutsch", 						LanguageList[5], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*德语*/
	{"Français", 						LanguageList[6], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*法语*/
	{"Italiano", 						LanguageList[7], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*意大利语*/
	{"Español", 						LanguageList[8], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*西班牙语*/
	{"Pусский", 						LanguageList[9], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*俄语*/
	{"العربية", 						LanguageList[10], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*阿拉伯语*/
	{"עברית", 							LanguageList[11], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*希伯来语*/
};
//电量耗尽
const TextInfo TextListBatteryOutTable[12] = 
{
	/*		文本内容  						字库路径 		 x   y    文本宽度 字间距    颜色  				滚动方式*/
	{"电量耗尽", 						LanguageList[0], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*简体中文*/
	{"English", 						LanguageList[1], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*英语*/
	{"繁體中文", 						LanguageList[2], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*繁体中文*/
	{"日本語", 							LanguageList[3], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*日语*/
	{"한국어", 								LanguageList[4], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*韩语*/
	{"Deutsch", 						LanguageList[5], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*德语*/
	{"Français", 						LanguageList[6], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*法语*/
	{"Italiano", 						LanguageList[7], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*意大利语*/
	{"Español", 						LanguageList[8], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*西班牙语*/
	{"Pусский", 						LanguageList[9], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*俄语*/
	{"العربية", 						LanguageList[10], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*阿拉伯语*/
	{"עברית", 							LanguageList[11], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*希伯来语*/
};
//请更换滤芯
const TextInfo TextListReplaceFilterTable[12] = 
{
	/*		文本内容  						字库路径 		 x   y    文本宽度 字间距    颜色  				滚动方式*/
	{"更换滤芯", 						LanguageList[0], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*简体中文*/
	{"English", 						LanguageList[1], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*英语*/
	{"繁體中文", 						LanguageList[2], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*繁体中文*/
	{"日本語", 							LanguageList[3], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*日语*/
	{"한국어", 								LanguageList[4], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*韩语*/
	{"Deutsch", 						LanguageList[5], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*德语*/
	{"Français", 						LanguageList[6], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*法语*/
	{"Italiano", 						LanguageList[7], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*意大利语*/
	{"Español", 						LanguageList[8], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*西班牙语*/
	{"Pусский", 						LanguageList[9], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*俄语*/
	{"العربية", 						LanguageList[10], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*阿拉伯语*/
	{"עברית", 							LanguageList[11], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*希伯来语*/
};
//滤芯将到期
const TextInfo TextListFilterExpireTable[12] = 
{
	/*		文本内容  						字库路径 		 x   y    文本宽度 字间距    颜色  				滚动方式*/
	{"滤芯将到期", 					LanguageList[0], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*简体中文*/
	{"English", 						LanguageList[1], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*英语*/
	{"繁體中文", 						LanguageList[2], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*繁体中文*/
	{"日本語", 							LanguageList[3], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*日语*/
	{"한국어", 								LanguageList[4], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*韩语*/
	{"Deutsch", 						LanguageList[5], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*德语*/
	{"Français", 						LanguageList[6], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*法语*/
	{"Italiano", 						LanguageList[7], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*意大利语*/
	{"Español", 						LanguageList[8], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*西班牙语*/
	{"Pусский", 						LanguageList[9], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*俄语*/
	{"العربية", 						LanguageList[10], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*阿拉伯语*/
	{"עברית", 							LanguageList[11], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*希伯来语*/
};

/******************************** 锁动画 ************************************/
//上锁
const TextInfo TextListLockTable[12] = 
{
	/*		文本内容  						字库路径 		 x   y    文本宽度 字间距    颜色  				滚动方式*/
	{"连续工作模式打开 ", 	LanguageList[0], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*简体中文*/
	{"English", 						LanguageList[1], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*英语*/
	{"繁體中文", 						LanguageList[2], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*繁体中文*/
	{"日本語", 							LanguageList[3], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*日语*/
	{"한국어", 								LanguageList[4], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*韩语*/
	{"Deutsch", 						LanguageList[5], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*德语*/
	{"Français", 						LanguageList[6], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*法语*/
	{"Italiano", 						LanguageList[7], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*意大利语*/
	{"Español", 						LanguageList[8], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*西班牙语*/
	{"Pусский", 						LanguageList[9], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*俄语*/
	{"العربية", 						LanguageList[10], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*阿拉伯语*/
	{"עברית", 							LanguageList[11], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*希伯来语*/
};


//解锁
const TextInfo TextListUnlockTable[12] = 
{
	/*		文本内容  						字库路径 		 x   y    文本宽度 字间距    颜色  				滚动方式*/
	{"连续工作模式关闭 ", 	LanguageList[0], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*简体中文*/
	{"English", 						LanguageList[1], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*英语*/
	{"繁體中文", 						LanguageList[2], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*繁体中文*/
	{"日本語", 							LanguageList[3], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*日语*/
	{"한국어", 								LanguageList[4], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*韩语*/
	{"Deutsch", 						LanguageList[5], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*德语*/
	{"Français", 						LanguageList[6], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*法语*/
	{"Italiano", 						LanguageList[7], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*意大利语*/
	{"Español", 						LanguageList[8], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*西班牙语*/
	{"Pусский", 						LanguageList[9], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*俄语*/
	{"العربية", 						LanguageList[10], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*阿拉伯语*/
	{"עברית", 							LanguageList[11], 0, 130,      240,    -10,  0xFFFF, RollType_Order_Center_Left}, /*希伯来语*/
};

