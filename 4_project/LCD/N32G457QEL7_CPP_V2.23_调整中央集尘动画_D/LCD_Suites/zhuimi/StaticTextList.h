#ifndef _STATIC_TEXT_LIST_H_
#define _STATIC_TEXT_LIST_H_

#include "DecodeFont.h"

#define SimplifiedChineseText(target) 	Text_SimplifiedChinese_##target
#define EnglishText(target)							Text_English_##target
#define ChineseTraditionalText(target)	Text_ChineseTraditional_##target
#define JapaneseText(target)						Text_Japanese_##target
#define KoreanText(target)							Text_Korean_##target
#define GermanText(target)							Text_German_##target
#define FrenchText(target)							Text_French_##target
#define ItalianText(target)							Text_Italian_##target
#define SpanishText(target)							Text_Spanish_##target
#define RussianText(target)							Text_Russian_##target
#define ArabicText(target)							Text_Arabic_##target
#define HebrewText(target)							Text_Hebrew_##target

#define TextList(target)								Text_List_##target

enum LanguageListIndex{
	LanguageListIndex_SimplifiedChinese		= 0,//简体中文
	LanguageListIndex_English							= 1,//英语
	LanguageListIndex_ChineseTraditional	= 2,//繁体中文	
	LanguageListIndex_Japanese						= 3,//日语
	LanguageListIndex_Korean							= 4,//韩语
	LanguageListIndex_German							= 5,//德语
	LanguageListIndex_French							= 6,//法语
	LanguageListIndex_Italian							= 7,//意大利语
	LanguageListIndex_Spanish							= 8,//西班牙语
	LanguageListIndex_Russian							= 9,//俄语
	LanguageListIndex_Arabic							= 10,//阿拉伯语
	LanguageListIndex_Hebrew							= 11,//希伯来语
	LanguageListIndex_BigBattery					= 12,
	LanguageListIndex_SmallBattery				= 13,
	LanguageListIndex_Smybol							= 14,
	LanguageListIndex_error								= 15,
	LanguageListIndex_Unselected_SimplifiedChinese	=16,//简体中文
	LanguageListIndex_Unselected_English						= 17,//英语
	LanguageListIndex_Unselected_ChineseTraditional	= 18,//繁体中文	
	LanguageListIndex_Unselected_Japanese						= 19,//日语
	LanguageListIndex_Unselected_Korean							= 20,//韩语
	LanguageListIndex_Unselected_German							= 21,//德语
	LanguageListIndex_Unselected_French							= 22,//法语
	LanguageListIndex_Unselected_Italian						= 23,//意大利语
	LanguageListIndex_Unselected_Spanish						= 24,//西班牙语
	LanguageListIndex_Unselected_Russian						= 25,//俄语
	LanguageListIndex_Unselected_Arabic							= 26,//阿拉伯语
	LanguageListIndex_Unselected_Hebrew							= 27,//希伯来语
};



//typedef const char* TextInfo;
typedef const TextInfo* TextLists;



extern const char* LanguageList[40];
extern const TextInfo TextListShiftTable[12][4];
extern const TextInfo TextListMainMenuTable[12][4];
extern const TextInfo TextListMainMenuSelectedTable[12][4];
extern const TextInfo TextListHistoryTable[12];
extern const TextInfo TextListLanguageTable[12];
extern const TextInfo TextListLanguageSelectedTable[12];
extern const TextInfo TextListErrorCodeTable[12];
extern const TextInfo TextListTuyereBlockedTable[12];
extern const TextInfo TextListRollerStallTable[12];
extern const TextInfo TextListOvertemperatureTable[12];
extern const TextInfo TextListFilterNotInstalledTable[12];
extern const TextInfo TextListBatteryLowTable[12];
extern const TextInfo TextListBatteryOutTable[12];
extern const TextInfo TextListReplaceFilterTable[12];
extern const TextInfo TextListFilterExpireTable[12];
extern const TextInfo TextListLockTable[12];
extern const TextInfo TextListUnlockTable[12];

#endif /*_STATIC_TEXT_LIST_H_*/
