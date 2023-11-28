#ifndef _V2205_DRAW_H_
#define _V2205_DRAW_H_

#include "Decode.h"

#define SOFTWARE_VERSION_NUMBER		"5"/*软件版本号*/
#define TEST_MODE_FUNCTION_ENABLE	0

#define VALID_FLASH_DATA_FLAG		0x55AA55AA/*flash内存储有有效信息标志*/
#define FLASH_DATA_ADDRESS			0x0803D000/*预留4kB*/
#define FLASH_ERROR_ADDRESS			0x0803E000/*预留4kB*/

#define DELAY_CHANGE_TO_RUN_MS		3000
#define DELAY_PLAY_LOW_BATTERY		3680
#define DELAY_PLAY_ERROR			3680
#define DELAY_PLAY_FILTER_REPLACE	9160
#define DELAY_PLAY_FILTER_EXPIRE	3680

/* 清屏函数接口宏 */
#define CLEAR_SCREEN()		//ClearScreen(0)//LcdClearScreen(0)//lcd_clear(0);//
#define CLEAR_PART_SCREEN(x_start,y_start,x_end,y_end)	//ClearPartScreen(x_start,y_start,x_end,y_end,0)//LcdClearPartScreen(x_start,y_start,x_end,y_end,0)//
#define ALLOW_DISPLAY()			SET_PWM_DUTY_RATIO(0.75) /*timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 75);*/
#define DARK_SCREEN()			SET_PWM_DUTY_RATIO(0.25) /*timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 25);*/

#define LOAD_NEED_SAVE()		FlashAccessRead((uint8_t*)&(NeedSave), FLASH_DATA_ADDRESS, sizeof(NeedSave))
#define SAVE_NEED_SAVE()		FlashAccessWrite((uint8_t*)&(NeedSave), FLASH_DATA_ADDRESS, sizeof(NeedSave))

#define INIT_TIMESTAMP()		BspRtcInit()/*RTC_Init()*//*备份区掉电过返回1否则返回0*/
#define GET_TIMESTAMP()			BspRtcGetTimestamp()//0/*RTC_GetTimestamp()*/


#define V2205Draw_LED_RED_ON		LED_RED_ON
#define V2205Draw_LED_GREEN_ON		LED_GREEN_ON
#define V2205Draw_LED_RED_OFF		LED_RED_OFF
#define V2205Draw_LED_GREEN_OFF		LED_GREEN_OFF

typedef struct{
	unsigned char	header1;				//0xAC
	unsigned char	header2;				//0x03
	unsigned char	header3;				//0x0A
	unsigned char	shift					:4;	//档位信息 @V2205ShiftInfo
	unsigned char	dustLevel				:4;	//灰尘等级 @V2205DustLevel
	unsigned char	batteryLevel;			//电池电量
	unsigned char	lockAction				:1;	//切换连续工作模式 @LockAction
	unsigned char	operatingAction			:1;	//开机动作标志 @OperatingAction
	unsigned char	screenLuminance			:1; //显示屏亮度位 @ScreenLuminance
	unsigned char	languageConfirmation 	:1;	//语言确认动画 @LanguageConfirmation
	unsigned char	lock					:1;	//电子自锁状态 @Lock
	unsigned char	languageSetting			:1; //多国语言选择设置 @LanguageSetting
	unsigned char	select					:1;	//选择下一种语言 需要languageSetting置位后有效 与上一帧不同切换
	unsigned char	confirm					:1;	//语言确认动作 @Confirm
	unsigned char	errorData;				//故障码 @ErrorData
	unsigned char	workState;				//工作状态 @WorkState
	unsigned char	filterServiceLife		:4;	//滤芯寿命相关信息 @FilterServiceLife
	unsigned char	filterReset				:4;	//滤芯重置设置 @FilterReset
	unsigned char	cleaningRecord			:1;	//历史清洁记录界面 @CleaningRecord
	unsigned char	errorRecord				:1;	//故障记录 @ErrorRecord
	unsigned char	mainMenu				:1; //一级菜单 @MainMenu
	unsigned char	rollMenu				:3; //主菜单位置 @RollMenu
	unsigned char							:2;	//未使用
	unsigned char	remainingMinute;		//灰尘等级界面剩余时间-分
	unsigned char	remainingSecond;		/*灰尘等级界面剩余时间-秒
		0x00~0x3B：秒数
		0xEF：电池电量低（倒计时模糊处理）
		注：显示屏接收到第一帧倒计时数据时，自动处理1S倒计时，在档位不变的情况下，每隔15S去
		check下倒计时以作校准，档位改变时，立即更新时间后再自处理1S倒计时*/
	unsigned char	highAltitudeMode;		/*高海拔模式 @HighAltitudeMode
		（高海拔模式是长按模式按键3S进入语言选择界面后再长按自锁按键1S，进入和退出，需要BMS记忆该模式及电机档位。）*/
}UartMessage_V1_17;

//V2205ShiftInfo
typedef enum{
	V2205ShiftInfo_None			= 0,//初始状态，用于触发第一次界面切换
	V2205ShiftInfo_Low			= 1,//低档
	V2205ShiftInfo_Middle		= 2,//中档
	V2205ShiftInfo_High 		= 3,//高档
	V2205ShiftInfo_Auto			= 4,//自动
}V2205ShiftInfo;

//V2205DustLevel
typedef enum{
	V2205DustLevel_None     	= 0,//无
	V2205DustLevel_Low			= 1,//低
	V2205DustLevel_Middle		= 2,//中
	V2205DustLevel_High 		= 3,//高
	V2205DustLevel_Max,
}V2205DustLevel;

//LockAction
#define LOCK_ACTION_NONE			0/*无切换*/
#define LOCK_ACTION_SWITCHING		1/*切换中，产生有效的lock动画（连续模式切换）该bit同步置1维持1s后恢复为0*/

//OperatingAction
#define OPERATING_ACTION_NONE		0/*默认状态*/
#define OPERATING_ACTION_ON			1/*开机（按下电源开关使电机从静止变为运行时连续发送2帧）*/

//ScreenLuminance
#define SCREEN_LUMINANCE_NORMAL		0/*正常亮度*/
#define SCREEN_LUMINANCE_DARK		1/*变暗*/

//LanguageConfirmation
#define LANGUAGE_CONFIRM_NONE		0/*未确认*/
#define LANGUAGE_CONFIRM_OK			1/*出现语言选择确认倒计时动画 （动画时长3s，保持播放动画标志）*/

//Lock
#define LOCK_OFF					0/*非电子自锁*/
#define LOCK_ON						1/*电子自锁状态*/

//LanguageSetting
#define LANGUAGE_SETTING_ACTIVE		1/*进入语言选择界面*/

//Confirm
#define CONFIRM_SELLECTED_LANGUAGE	1/*选中当前语言*/

//ErrorData
typedef enum{
	ErrorData_None					= 0x00,//无错误故障
	ErrorData_BldcUndervoltage		= 0x01,//BLDC欠压（UI错误代码1）--录在故障记录里
	ErrorData_BldcCvervoltage		= 0x02,//BLDC过压（UI错误代码1）--录在故障记录里
	ErrorData_BldcOverTemperature	= 0x03,//BLDC过温（UI错误代码1）--录在故障记录里
	ErrorData_BldcOvercurrent		= 0x04,//BLDC过流（UI错误代码1）--录在故障记录里
	ErrorData_BldcOverspeed			= 0x05,//BLDC超速（UI错误代码1）--录在故障记录里
	ErrorData_BldcOpenPhase			= 0x06,//BLDC缺相（UI错误代码1）--录在故障记录里
	ErrorData_TuyereBlocked			= 0x07,//全堵风口（UI风道堵塞）
	ErrorData_RollerStall			= 0x08,//地刷堵转（UI请清理滚刷）
	ErrorData_RollerShortOut		= 0x09,//地刷短路（UI请清理滚刷）
	ErrorData_OverDischargeProtection		= 0x0A,//过放保护
	ErrorData_DischargeOvertemperatureProtection 	= 0x0B,//放电过温保护（UI电池过温）  (不包含放电低温)
	ErrorData_DischargeNoLoadProtection		= 0x0C,//放电空载保护（UI错误代码2）
	ErrorData_CommunicationTimeout	= 0x0D,//通讯超时（可能发不出去）（UI错误代码3）--录在故障记录里
	ErrorData_FilterNotInstalled	= 0x0E,//滤芯未安装（UI）
	ErrorData_Reserve				= 0x0F,//放电过流/短路/ /BLDC关断失败保护，屏幕无法显示
	ErrorData_OverchargeProtection	= 0x10,//过充保护
	ErrorData_ChargerVoltageAbnormal	= 0x11,//充电器电压异常（UI错误代码4）
	ErrorData_ChargerOvercurrent	= 0x12,//充电过流（UI错误代码5）
	ErrorData_ChargerTimeout		= 0x13,//充电超时（UI错误代码6）
	ErrorData_BatteriesFault		= 0x20,//电芯故障（UI错误代码7）--录在故障记录里
	ErrorData_NTCFault				= 0x21,//温度传感器(NTC)故障（UI错误代码8）--录在故障记录里
	ErrorData_BMSHardwareFault		= 0x22,//前端通讯失败(BMS硬件异常)（UI错误代码9）--录在故障记录里
}ErrorData_en;

//WorkState
typedef enum{
	WorkState_Standby 	= 0x00,//待机状态（屏幕亮、电机不转定义为待机）
	WorkState_Charging 	= 0x01,//充电状态
	WorkState_Work		= 0x02,//放电状态
	WorkState_CDC		= 0x03,//中央集尘(central dust collection)
	
	WorkState_Test		= 0xFF,//测试模式
}WorkState_en;

//FilterServiceLife
#define FILTER_SERVICE_LIFE_NORMAL		0/*未到更换提醒时间*/
#define FILTER_SERVICE_LIFE_RINSE		1/*提醒清洗滤芯(UI请清理滤芯) 不使用*/
#define FILTER_SERVICE_LIFE_REPLACE		2/*提醒更换滤芯(UI请更换滤芯)*/
#define FILTER_SERVICE_LIFE_EXPIRE		3/*滤芯将要过期请尽快更换 (UI滤芯将要到期提醒)*/

//FilterReset
#define FILTER_RESET_NORMAL				0/*不需要播放动画*/
#define FILTER_RESET_SETING				1/*滤芯显示恢复出厂设置中（确认完成）*/
#define FILTER_RESET_RESET				2/*长按功能键发送,出现重置动画（开始动画）*/

//CleaningRecord
#define CLEANING_RECORD_SHOW		1/*调出历史清洁记录界面*/

//ErrorRecord
#define ERROE_RECORD_SHOW			1/*调出故障记录*/

//MainMenu
#define MAIN_MENU_SHOW				1/*进入一级菜单*/

//RollMenu
typedef enum{//（000——001——010——011——000依次循环）
	RollMenu_CleaningRecord			= 0,//进入时默认为000(历史清洁记录)；按一次按键由000转为001
	RollMenu_ResetFilter			= 1,//滤网重置，按一次按键由000转为001
	RollMenu_SelectLanguage			= 2,//语言选择，按一次按键由001转为010
	RollMenu_Exit					= 3,//退出，按一次按键由010转为011
	RollMenu_None,
}RollMenu_en;

//HighAltitudeMode
#define HIGH_ALTITUDE_MODE_NONE			0/*无变化*/
#define HIGH_ALTITUDE_MODE_ENTERING  	1/*进入高海拔模式（UI显示进入动画界面中，倒计时开始）*/
#define HIGH_ALTITUDE_MODE_ENTERED		2/*进入高海拔模式确认完成（UI显示进入动画界面确认完成）*/
#define HIGH_ALTITUDE_MODE_EXITING	 	3/*退出高海拔模式（UI显示退出动画界面中，倒计时开始）*/
#define HIGH_ALTITUDE_MODE_EXITED		4/*退出高海拔模式确认完成（UI显示退出动画界面确认完成）*/

typedef enum{
	LanguageOptions_Min = 0,
	LanguageOptions_SimplifiedChinese	= 0,//简体中文
	LanguageOptions_English				= 1,//英语
	LanguageOptions_ChineseTraditional	= 2,//繁体中文	
	LanguageOptions_Japanese			= 3,//日语
	LanguageOptions_Korean				= 4,//韩语
	LanguageOptions_German				= 5,//德语
	LanguageOptions_French				= 6,//法语
	LanguageOptions_Italian				= 7,//意大利语
	LanguageOptions_Spanish				= 8,//西班牙语
	LanguageOptions_Russian				= 9,//俄语
	LanguageOptions_Arabic				= 10,//阿拉伯语
	LanguageOptions_Hebrew				= 11,//希伯来语
	LanguageOptions_Max = LanguageOptions_English,
}V2205DrawLanguageOptions;

typedef enum { V2205Bool_FALSE = 0, V2205Bool_TRUE = !V2205Bool_FALSE, } V2205Bool;

typedef enum{
	DrawShowState_Min					=0 ,	//有效范围下边界
	
	DrawShowState_None = DrawShowState_Min,		//初始界面，用于触发第一次界面切换
	DrawShowState_PowerOn				= 1,	//开机画面
	DrawShowState_SelectedMode			= 2,	//模式选择界面
	DrawShowState_DustLevel				= 3,	//灰尘等级界面	
	DrawShowState_MainMenu				= 4,	//主菜单界面	
	DrawShowState_History				= 5,	//历史数据界面
	DrawShowState_ResetFilter			= 6,	//重置滤芯界面
	DrawShowState_LanguageMenu			= 7,	//语言选择界面
	DrawShowState_Confirmation			= 8,	//确认语言选择界面
	
	DrawShowState_Recharge				= 9,	//充电界面
	DrawShowState_Lock					= 10,	//锁动画界面
	DrawShowState_ShowError				= 11,	//故障界面
	
	DrawShowState_HighAltitude			= 12,	//高海拔界面
	DrawShowState_FilterServiceLife		= 13,	//滤芯寿命提示界面
	DrawShowState_CentralDustCollection = 14,	//中央集尘页面
	
	DrawShowState_TestMode,						//测试页面
	DrawShowState_Max,							//有效范围上边界
}DrawMainShowState;

typedef enum{
	LowBatteryWarning_None,
	LowBatteryWarning_Low,
	LowBatteryWarning_Out,
}LowBatteryWarning_t;

typedef enum{
	DelayFlag_Stop,
	DelayFlag_Start,
	DelayFlag_Count,
	DelayFlag_Finish,
}DelayFlag_en;

typedef enum{
	MotorState_Stop,
	MotorState_Running,
}MotorState_en;

typedef enum{
	TestMode_Versions,
}TestMode_en;

//------------------------------------------------------------------------------------
class Draw : protected Decode{
public:
	Draw();
	void Init(void);
	void ReloadPage(void);
	void Tick(unsigned int nms);
	void Refresh(unsigned char* message);
	void Handle(void);

protected:
	UartMessage_V1_17 Message;//报文解析结构体

	/*标志和内部计数*/
	union{
		struct{
			unsigned int RefreshFlag		:1;//有新报文
			unsigned int StartExecute   	:1;//开始解析报文标志
			unsigned int DirtyDta			:1;//脏数据标志
			unsigned int PowerOn			:1;//已开机标志
			unsigned int ChangeLangeuage	:1;//发生语言切换 修改为最新的语言
			unsigned int InitLowBattery		:1;//电量低状态开机标志
			
			unsigned int ShowDuty			:1;//正在显示灰尘等级
			unsigned int comfirmLangeuage	:1;//最终确认语言选择
			unsigned int ResetFilter		:1;//更换滤芯确认标志
			unsigned int NeedStore			:1;//flash数据需要存储
			unsigned int Locking			:1;//正在播放锁动画
			unsigned int StartPlaying		:1;//开始闪烁-可打断
			unsigned int Playing			:1;//正在闪烁-可打断
			unsigned int StartStrongPlaying	:1;//开始闪烁-不可打断
			unsigned int StrongPlaying		:1;//正在闪烁-不可打断
			
			unsigned int LowBattery			:1;//电量低已显示标志
			unsigned int LowBatteryPage		:1;//电量低动画已播放标志
		}bit;
		unsigned int All;
	}FlagContainers;
	
	/* 计时控制 */
	unsigned int DrawTickCount;//绘制心跳计数
	unsigned int CtrlTickCount;//控制心跳计数
	
	unsigned int CurrentTimestamp;//本次连续工作开始时间戳
	
	unsigned int ShowDustDelay_Timestamp;
	unsigned int ShowDustDelay_Limit;
	unsigned int PlayingDelay_Timestamp;
	unsigned int PlayingDelay_Limit;
	
	DelayFlag_en ShowDustDelay;//到显示灰尘等级页面的延时状态
	//DelayFlag_en ErrorShowDelay;//故障显示延时状态
	DelayFlag_en PlayingDelay;//播放延时
	
	MotorState_en MotorState;
	/*显示状态*/	
	V2205ShiftInfo CurrentShift;//当前正在显示的档位
	V2205ShiftInfo NewShift;
	V2205Bool LockState;//锁状态
	
	unsigned char WorkState;//当前工作状态
	unsigned char WorkStatePrve;//前一个工作状态
	
	ErrorData_en ErrorData;
	short ContinuousPictureIndex;//连续图片索引
	short ContinuousPictureStep;//步控制
	/* 页面状态标志 每个图片对应一个标志*/
	//模式选择页面
	union{
		struct{
			unsigned char clear		:1;//擦除显存后再绘制---用于从其他更大页面切换过来
			unsigned char Mode		:1;//切换档位
			unsigned char lock		:1;//锁状态点
			unsigned char battery	:1;//电池图标
		}bit;
		unsigned char all;
	}SelectedModeFlag;
	V2205ShiftInfo LoopShift;
	//灰尘等级曲线
	union{
		struct{
			unsigned char clear		:1;//擦除显存后再绘制---用于从其他更大页面切换过来
			unsigned char lock		:1;//锁标志
			unsigned char shift		:1;//档位图标
			unsigned char battery	:1;//电池图标			
		}bit;
		unsigned char all;
	}DustLevelFlag;
	unsigned char DustLevel;//当前灰尘等级
	//主菜单
	union{
		struct{
			unsigned char clear		:1;//擦除显存后再绘制---用于从其他更大页面切换过来
			unsigned char showAll 	:1;//强制显示全部
			unsigned char selected 	:1;//已选项发生变化
		}bit;
		unsigned char all;
	}MainMenuFlag;
	RollMenu_en MainMenu;		//记录当前选中菜单项
	RollMenu_en MainMenuPrve;	//前一个菜单选中选项
	//历史记录
	union{
		struct{
			unsigned char clear		:1;//擦除显存后再绘制---用于从其他更大页面切换过来
			unsigned char show 		:1;//显示历史界面
		}bit;
		unsigned char all;
	}HistoryFlag;
	//重置滤芯
	union{
		struct{
			unsigned char clear		:1;//擦除显存后再绘制---用于从其他更大页面切换过来
			unsigned char show 		:1;//显示历史界面
		}bit;
		unsigned char all;
	}ResetFilterFlag;
	//语言选择界面
	union{
		struct{
			unsigned char clear			:1;//擦除显存后再绘制---用于从其他更大页面切换过来
			unsigned char selected 		:1;//更新语言选择界面
		}bit;
		unsigned char all;
	}LanguageMenuFlag;
	unsigned char lastLanguageSelect;
	
	V2205DrawLanguageOptions NewLanguage;//菜单中选中的语言
	//语言确认界面
	union{
		struct{
			unsigned char clear			:1;//擦除显存后再绘制---用于从其他更大页面切换过来
			unsigned char show 			:1;//开始语言确认界面
		}bit;
		unsigned char all;
	}ConfirmationFlag;
	//充电界面
	union{
		struct{
			unsigned char clear			:1;//擦除显存后再绘制---用于从其他更大页面切换过来
			unsigned char battery 		:1;//电量区间发生变化
		}bit;
		unsigned char all;
	}RechargeFlag;
	unsigned char batteryLevel;
//	unsigned char lastBatteryLevel;
	//高海拔界面
	union{
		struct{
			unsigned char clear			:1;//擦除显存后再绘制---用于从其他更大页面切换过来
			unsigned char show 			:1;//电量区间发生变化
		}bit;
		unsigned char all;
	}HighAltitudeFlag;
	unsigned char HighAltitudeMode;//记录当前的高海拔模式
	//故障界面
	union{
		struct{
			unsigned char clear			:1;//擦除显存后再绘制---用于从其他更大页面切换过来
			unsigned char show 			:1;//电量区间发生变化
		}bit;
		unsigned char all;
	}ShowErrorFlag;
	
	//电量低界面
	union{
		struct{
			unsigned char clear			:1;//擦除显存后再绘制---用于从其他更大页面切换过来
			unsigned char show 			:1;//电量区间发生变化
		}bit;
		unsigned char all;
	}LowBatteryFlag;
	LowBatteryWarning_t LowBatteryWarning;
	
	//滤芯寿命提示界面
	union{
		struct{
			unsigned char clear			:1;//擦除显存后再绘制---用于从其他更大页面切换过来
			unsigned char show 			:1;//电量区间发生变化
		}bit;
		unsigned char all;
	}FilterServiceLifeFlag;
	unsigned char FilterServiceLife;
	
	//锁动画界面
	union{
		struct{
			unsigned char clear			:1;//擦除显存后再绘制---用于从其他更大页面切换过来
			unsigned char show 			:1;//电量区间发生变化
		}bit;
		unsigned char all;
	}LockFlag;
	
	union{
		struct{
			unsigned char clear			:1;//擦除显存后再绘制---用于从其他更大页面切换过来
			unsigned char show 			:1;//
		}bit;
		unsigned char all;
	}CDCFlag;
	unsigned char CdcLoopCount;
	
	union{
		struct{
			unsigned char show			:1;//需要刷新一次标志
		}bit;
		unsigned char all;
	}TestModeFlag;
	TestMode_en TestMode;
	
	DrawMainShowState PrevState;//前一个页面
	DrawMainShowState NextState;//下一个页面

	struct{
		//CurveDrawData_st CurveDrawData;		
		unsigned int CheckFlag;
		unsigned int HistoryTimestamp;//历史数据时间戳--七天中的最早一天	
		float History[7];//历史记录
		V2205DrawLanguageOptions Language;//当前语言			
	}NeedSave;
	
private:
	void SetNextPage(DrawMainShowState next);
	void ReturnPrevPage(void);
	void ReturnFromMenu(void);
	void RecordRunningTime(DrawMainShowState workState);
	DrawMainShowState SetStateDischarge(void);
	void SetBatteryLevel(unsigned char level);
	V2205Bool LowBatteryCheck(unsigned char level);
	int SetShift(V2205ShiftInfo shift);
	void SetDustLevel(char shift);
	void SetMainEnum(RollMenu_en menu);
	void SetLanguageSelected(unsigned char select);
	V2205Bool SetLockState(V2205Bool state);
	DrawMainShowState CheckFilterReset(DrawMainShowState state);
	DrawMainShowState CheckLanguageSetting(DrawMainShowState state);
	DrawMainShowState CheckCleaningRecord(DrawMainShowState state);
	DrawMainShowState CheckMainMenu(DrawMainShowState state);
	DrawMainShowState CheckErrorData(DrawMainShowState state);
	DrawMainShowState CheckFilterServiceLife(DrawMainShowState state);
	DrawMainShowState CheckHighAltitudeMode(DrawMainShowState state);
	DrawMainShowState CheckLock(DrawMainShowState state);
	DrawMainShowState CheckWorkMode(DrawMainShowState state);
	/*****************************/
	void ExecuteMessage(void);
	/*****************************/
	void SetShowDustDelay(unsigned int limit);
	void SetPlayingDelay(unsigned int limit);
	void DelayCtrl(void);
	/*****************************/
	int DrawPowerOn(void);
	int DrawSelectedMode(void);
	int DrawDustLevel(void);
	int DrawMainMenu(void);
	int DrawHistory(void);
	int DrawResetFilter(void);
	int DrawLanguageMenu(void);
	int DrawConfirmation(void);
	int DrawRecharge(void);
	int DrawLock(void);
	int DrawShowError(void);
	int DrawHighAltitude(void);
	int DrawFilterServiceLife(void);
	int V2205DrawCdc(void);
	int V2205DrawTestMode(void);
	void ExecuteDraw(void);	
};
//------------------------------------------------------------------------------------
#define DISCHARGE_BATTERY_LEVEL_TEXT_COLOR	0x9CD3		

#endif/*_V2205_DRAW_H_*/

