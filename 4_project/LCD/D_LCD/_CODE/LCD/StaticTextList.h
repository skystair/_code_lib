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
	LanguageListIndex_SimplifiedChinese		= 0,//��������
	LanguageListIndex_English							= 1,//Ӣ��
	LanguageListIndex_ChineseTraditional	= 2,//��������	
	LanguageListIndex_Japanese						= 3,//����
	LanguageListIndex_Korean							= 4,//����
	LanguageListIndex_German							= 5,//����
	LanguageListIndex_French							= 6,//����
	LanguageListIndex_Italian							= 7,//�������
	LanguageListIndex_Spanish							= 8,//��������
	LanguageListIndex_Russian							= 9,//����
	LanguageListIndex_Arabic							= 10,//��������
	LanguageListIndex_Hebrew							= 11,//ϣ������
	LanguageListIndex_BigBattery					= 12,
	LanguageListIndex_SmallBattery				= 13,
	LanguageListIndex_Smybol							= 14,
	LanguageListIndex_error								= 15,
	LanguageListIndex_Unselected_SimplifiedChinese	=16,//��������
	LanguageListIndex_Unselected_English						= 17,//Ӣ��
	LanguageListIndex_Unselected_ChineseTraditional	= 18,//��������	
	LanguageListIndex_Unselected_Japanese						= 19,//����
	LanguageListIndex_Unselected_Korean							= 20,//����
	LanguageListIndex_Unselected_German							= 21,//����
	LanguageListIndex_Unselected_French							= 22,//����
	LanguageListIndex_Unselected_Italian						= 23,//�������
	LanguageListIndex_Unselected_Spanish						= 24,//��������
	LanguageListIndex_Unselected_Russian						= 25,//����
	LanguageListIndex_Unselected_Arabic							= 26,//��������
	LanguageListIndex_Unselected_Hebrew							= 27,//ϣ������
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
