#include "lcd_driver.h"
#include "flash_access.h"
#include "bsp_rtc.h"
#include "bsp_pwm.h"
#include "dsp_led.h"
#include <stdio.h>

#include "Draw.h"


Draw::Draw():Decode()
{
	Buffer = (unsigned short*)OutputDoubleBuffer;
	
	font = new DecodeFont(Buffer);
	DecodeFont& Font = *font;
	Font.CreatText();
	Font.CreatText();
	Font.CreatText();
	Font.CreatText();
	DrawTickCount = 0;//初始化显示模块心跳计数
	FlagContainers.All = 0;//初始化标志位

	CurrentShift = V2205ShiftInfo_None;
	NewShift = V2205ShiftInfo_None;
	LoopShift = V2205ShiftInfo_Low;
	
	LockState = V2205Bool_FALSE;
	
	SelectedModeFlag.all = 0;
	DustLevelFlag.all = 0;
	MainMenuFlag.all = 0;
	HistoryFlag.all	= 0;
	ResetFilterFlag.all = 0;
	LanguageMenuFlag.all = 0;
	ConfirmationFlag.all = 0;
	RechargeFlag.all = 0;
	HighAltitudeFlag.all = 0;
	ShowErrorFlag.all = 0;
	LowBatteryFlag.all = 0;
	FilterServiceLifeFlag.all = 0;
	LockFlag.all = 0;
	
	PrevState = DrawShowState_SelectedMode;
	NextState = DrawShowState_None;
	MotorState = MotorState_Stop;
	
	lastBatteryLevel = 0xFF;
	
	//读flash 获取存储的数据
	LOAD_NEED_SAVE();
	if(INIT_TIMESTAMP() || NeedSave.CheckFlag != VALID_FLASH_DATA_FLAG)
	{//检查到flash无内容或备份区掉电均初始化存储内容
		NeedSave.CheckFlag = VALID_FLASH_DATA_FLAG;//重置校验标志
		FlagContainers.bit.NeedStore = 1;//标记需要存储Flash数据
		//CurveDrawInit();//初始化曲线绘制模块
		for(int i=0; i<7; i++)
			NeedSave.History[i] = 0;//初始化历史数据
		NeedSave.HistoryTimestamp = GET_TIMESTAMP();
		NeedSave.Language = LanguageOptions_SimplifiedChinese;//默认语言
	}
}
unsigned int CountTick;
//输入模块心跳
//需要按固定周期调用
//nms：每n毫秒调用一次
void Draw::Tick(unsigned int nms)
{
	DrawTickCount += nms;
	CtrlTickCount += nms;
	CountTick = DrawTickCount;
}

//更新报文
//每有新报文调用一次
//message：报文数组指针
void Draw::Refresh(unsigned char* message)
{
	if(!FlagContainers.bit.StartExecute)
	{//未在处理报文时允许接收新报文
		u8* reserveOpint = (u8*)&Message;
		for(int i=0; i<sizeof(UartMessage_V1_17); i++)
			reserveOpint[i] = message[i];
	}
	//如果存在需要调整位置的数据 在这里调整
	
	//报文数据完全复制完毕后再进行标记，防止提前启动解析引发故障
	FlagContainers.bit.RefreshFlag = 1;
}

/***********************************************************************************/

void Draw::SetNextPage(DrawMainShowState next)
{
	if(next == NextState)
	{//防止重复触发
		return;
	}
	font->SleepAll();
	switch(next)
	{
		case DrawShowState_PowerOn://开机画面	
			ContinuousPictureIndex = 1;
			ContinuousPictureStep = 2;
			lastBatteryLevel = 0xFF;	
			break;
		
		case DrawShowState_SelectedMode://模式选择界面
			lastBatteryLevel = 0xFF;	
			
			if(PrevState != DrawShowState_DustLevel)
			{//从非灰尘等级页面切换到模式选择页面 图标从全暗开始显示
				ContinuousPictureIndex = -2;
				SelectedModeFlag.all = 0xFF;
				if(NewShift >= V2205ShiftInfo_Auto || NewShift <= V2205ShiftInfo_None)
				{	
					LoopShift = V2205ShiftInfo_Low;
				}
				else
				{
					LoopShift = NewShift;
				}
			}	
			if(ContinuousPictureStep > 0)
				ContinuousPictureStep = 8;
			else
				ContinuousPictureStep = -8;
			break;
		
		case DrawShowState_DustLevel://灰尘等级界面	
			lastBatteryLevel = 0xFF;	
			if(PrevState != DrawShowState_SelectedMode)
			{//从模式选职责页面切换到灰尘等级页面 图标从全暗开始显示
				ContinuousPictureIndex = 2;	
				DustLevelFlag.all = 0xFF;
				if(NewShift >= V2205ShiftInfo_Auto || NewShift <= V2205ShiftInfo_None)
				{
					LoopShift = V2205ShiftInfo_Low;
				}
				else
				{
					LoopShift = NewShift;
				}
			}	
			if(ContinuousPictureStep > 0)
				ContinuousPictureStep = 2;
			else
				ContinuousPictureStep = -2;
			break;
		
		case DrawShowState_MainMenu://主菜单界面	
			lastBatteryLevel = 0xFF;	
			MainMenuFlag.all = 0xFF;
			break;
		
		case DrawShowState_History://历史数据界面
			lastBatteryLevel = 0xFF;	
			HistoryFlag.all = 0xFF;
			break;
		
		case DrawShowState_ResetFilter://重置滤芯界面
			lastBatteryLevel = 0xFF;	
			ResetFilterFlag.all = 0xFF;
			break;
		
		case DrawShowState_LanguageMenu://语言选择界面
			lastBatteryLevel = 0xFF;	
			LanguageMenuFlag.all = 0xFF;
			NewLanguage = NeedSave.Language;//语言选择界面从现在的语言开始
			break;
		
		case DrawShowState_Confirmation://确认语言选择界面
			lastBatteryLevel = 0xFF;	
			ConfirmationFlag.all = 0xFF;
			break;
	
		case DrawShowState_Recharge://充电界面
			ContinuousPictureIndex = 1;
			ContinuousPictureStep = 2;
			RechargeFlag.all = 0xFF;
			break;
		
		case DrawShowState_Lock://锁动画界面
			lastBatteryLevel = 0xFF;	
			if(NextState == DrawShowState_ShowError)
			{
				NextState = PrevState;
			}
			LockFlag.all = 0xFF;
			break;
		
		case DrawShowState_ShowError://故障界面
			lastBatteryLevel = 0xFF;	
			ShowErrorFlag.all = 0xFF;
			if(PrevState == DrawShowState_Recharge /*前一个状态是充电状态*/
				&& ErrorData == 0)/*显示电量低故障*/
			{
				PrevState = DrawShowState_SelectedMode;
			}
			break;
		
		case DrawShowState_HighAltitude://高海拔界面
			lastBatteryLevel = 0xFF;	
			HighAltitudeFlag.all = 0xFF;
			break;
		
		case DrawShowState_FilterServiceLife://滤芯寿命提示界面
			lastBatteryLevel = 0xFF;	
			FilterServiceLifeFlag.all = 0xFF;
			break;
		
		case DrawShowState_TestMode:
			lastBatteryLevel = 0xFF;
			TestModeFlag.all = 0xFF;
			break;
		
		default:
			break;
	}
	
	if(NextState != DrawShowState_None)
	{
		PrevState = NextState;
	}
	else
	{
		PrevState = DrawShowState_SelectedMode;
	}
	NextState = next;
}

void Draw::ReturnPrevPage(void)
{
	if((PrevState == DrawShowState_SelectedMode || PrevState == DrawShowState_DustLevel)/*前一个页面是模式选择*/
		&& WorkStatePrve == WorkState_Work)/*前一个工作模式是放电*/
	{//重新开始放电计数	
		PrevState = SetStateDischarge();
	}
	else if(PrevState == DrawShowState_Recharge || PrevState == DrawShowState_PowerOn)//前一个页面是充电或开机页面
	{
		PrevState = DrawShowState_SelectedMode;
	}
	SetNextPage(PrevState);
	PrevState = NextState;//避免重复后退
	FlagContainers.bit.Locking = 0;
	FlagContainers.bit.Playing = 0;
}

void Draw::ReturnFromMenu(void)
{
	if(WorkState == WorkState_Charging)
	{
		SetNextPage(DrawShowState_Recharge);
	}
	else
	{
		SetNextPage(DrawShowState_SelectedMode);
	}
}

void Draw::RecordRunningTime(unsigned char workState)
{
	MotorState_en state;
	if(workState == WorkState_Work)
		state = MotorState_Running;
	else
		state = MotorState_Stop;
	if(MotorState != state)
	{
		if(state == MotorState_Running)
		{//电机开始工作
			CurrentTimestamp = GET_TIMESTAMP();
		}
		else
		{//电机停止
			FlagContainers.bit.NeedStore = 1;//数据更新 标记为需要存储
			//定位历史记录 和早期历史记录时间戳进行比较 滚动历史记录
			unsigned int timestamp = GET_TIMESTAMP();
			unsigned start = 0;
			int history = timestamp - NeedSave.HistoryTimestamp;//计算历史时间到现在的秒数
			history = history / (60*60*24);//计算历史时间到现在的天数
			if(history > 0)
			{//需要清除历史记录开始的零清理记录
				while(NeedSave.History[start] <= 0.01f)//1秒=0.0167分
				{//禁止以0记录开头
					if(++start >= history || start >= 7)
					{//防止溢出
						break;
					}
				}
			}
			if(start > 0)
			{//有需要提前滚动
				if(start < 7)	
					for(int i=start; i<7; i++)
					{//向前移动start
						NeedSave.History[i-start] = NeedSave.History[i];
						NeedSave.History[i] = 0;
					}
				else
					for(int i=0; i<7; i++)
					{//清除历史记录
						NeedSave.History[i] = 0;
					}
			}
			history -= start;//start小于等于history，history计算后最小可能等于0
			if(history >= 7)
			{//当前日期与历史时间戳差距大于7天
				int roll = history - 6;//计算需要向前滚动的天数	
				if(roll < 7)
				{//向前滚动范围小于7
					while(NeedSave.History[roll] <= 0.01f)//1秒=0.0167分
					{//滚动后禁止以0记录开头
						if(++roll >= 7)
						{//防止溢出
							break;
						}
					}
					for(int i=roll; i<7; i++)
					{//向前移动roll
						NeedSave.History[i-roll] = NeedSave.History[i];
						NeedSave.History[i] = 0;
					}
					NeedSave.HistoryTimestamp += (60*60*24)*roll;//时间戳向后移动
				}
				else
				{//向前滚动范围大于等于7，清除历史记录重新开始记录	
					roll = history;
					for(int i=0; i<7; i++)
					{//清除历史记录
						NeedSave.History[i] = 0;
					}
					NeedSave.HistoryTimestamp = timestamp;			
				}
				history -= roll;
			}
			int total = timestamp - CurrentTimestamp;//计算本次连续工作时间	
			NeedSave.History[history] += total/60.0f;//更新历史工作时间
		}
		MotorState = state;
	}
}

//用于放电状态 从其他页面切换会模式选择页面 3秒后显示灰尘等级页面
DrawMainShowState Draw::SetStateDischarge(void)
{
	DrawMainShowState state = DrawShowState_SelectedMode;
	if((NextState != DrawShowState_SelectedMode && NextState != DrawShowState_DustLevel)
		|| (WorkStatePrve != WorkState_Work))
	{//不在模式选择和灰尘等级页面
		state = DrawShowState_SelectedMode;//尝试切换到灰尘等级页面
		ShowDustDelay = DelayFlag_Start;//开始计时标志
	}
	if(ShowDustDelay == DelayFlag_Finish)//3秒延时 //计时完成标志
	{
		state = DrawShowState_DustLevel;
	}
	return state;
}

void Draw::SetBatteryLevel(unsigned char level)
{
	if(level == batteryLevel)
	{//防止重复触发
		return;
	}
	batteryLevel = level;//记录电量值
	SelectedModeFlag.bit.battery = 1;//置位模式选择界面电量标志
	DustLevelFlag.bit.battery = 1;//置位灰尘等级界面电量标志
	RechargeFlag.bit.battery = 1;//置位充电界面电量标志
}

V2205Bool Draw::LowBatteryCheck(unsigned char level)
{
	if(level <= 0)
	{//电量已耗尽
		//if(LowBatteryWarning != LowBatteryWarning_Out)
		{
			LowBatteryWarning = LowBatteryWarning_Out;
			//ErrorShowDelay = DelayFlag_Start;
			//FlagContainers.bit.StartStrongPlaying = 1;	
			//PlayingDelay = DelayFlag_Start;
			return V2205Bool_TRUE;
		}
//		else if(ErrorShowDelay != DelayFlag_Finish)
//		{//保持时间未结束
//			return V2205Bool_TRUE;
//		}
	}
	else if(Message.remainingSecond == 0xEF || level <= 10)
	{//电量低
		if(!FlagContainers.bit.LowBattery)//未触发电量低
		{
			if(FlagContainers.bit.LowBatteryPage)//用于避免在一次开机中播放多次电量低动画
			{
				FlagContainers.bit.LowBattery = 1;
				return V2205Bool_FALSE;
			}
			else
			{
				LowBatteryWarning = LowBatteryWarning_Low;
				FlagContainers.bit.StartPlaying = 1;	
				PlayingDelay = DelayFlag_Start;
				return V2205Bool_TRUE;
			}	
		}	
//		else if(ErrorShowDelay != DelayFlag_Finish)
//		{//保持时间未结束
//			return V2205Bool_TRUE;
//		}
	}
	else
	{
		LowBatteryWarning = LowBatteryWarning_None;
		FlagContainers.bit.LowBattery = 0;
	}
	return V2205Bool_FALSE;
}

int Draw::SetShift(V2205ShiftInfo shift)
{
	if(shift == NewShift)
	{//防止重复触发
		return 0;//未变化
	}
	if(shift > V2205ShiftInfo_Auto || shift == 0)
	{//超出范围，不显示
		return 0;//未变化
	}
	NewShift = shift;
	DustLevelFlag.bit.shift = 1;	
	SelectedModeFlag.bit.Mode = 1;
	return 1;//有变化
}

void Draw::SetDustLevel(char shift)
{	
	DustLevel = shift;
//	if(shift)//屏幕灰尘等级无的状态
//	{
//		//CurveDrawSetLevel(shift);//模块内带重复屏蔽 不需要额外处理
//		DustLevel = shift;
//	}
//	else
//	{
//		DustLevel = 1;
//	}
}

void Draw::SetMainEnum(RollMenu_en menu)
{
	if(menu == MainMenu)
	{//防止重复触发
		return;
	}
	MainMenuPrve = MainMenu;
	MainMenu = menu;
	MainMenuFlag.bit.selected = 1;
	MainMenuFlag.bit.clear = 1;
}

void Draw::SetLanguageSelected(unsigned char select)
{
	if(select == lastLanguageSelect)
	{//防止重复触发
		return;
	}
	lastLanguageSelect = select;
	int nl = NewLanguage;
	if(++nl > LanguageOptions_Max)
	{
		nl = LanguageOptions_Min;
	}
	NewLanguage = (V2205DrawLanguageOptions)nl;
	LanguageMenuFlag.bit.selected = 1;
}	

V2205Bool Draw::SetLockState(V2205Bool state)
{
	if(state == LockState)
	{//防止重复触发
		return V2205Bool_FALSE;
	}
	LockState = state;
	LockFlag.bit.show = 1;
	SelectedModeFlag.bit.lock = 1;
	DustLevelFlag.bit.lock = 1;
	return V2205Bool_TRUE;
}

//判断是否播放重置滤芯
DrawMainShowState Draw::CheckFilterReset(DrawMainShowState state)
{
	if(Message.filterReset)
	{//开始播放重置滤芯动画	
		state = DrawShowState_ResetFilter;//重置滤芯
		if(Message.filterReset&FILTER_RESET_SETING)
		{//播放重置滤芯动画最后一帧
			FlagContainers.bit.ResetFilter = 1;
		}
		else
		{
			FlagContainers.bit.ResetFilter = 0;
		}
	}
	return state;
}

//判断是否进入语言选择
DrawMainShowState Draw::CheckLanguageSetting(DrawMainShowState state)
{
	int confirm = 0;
	if(Message.languageSetting)
	{//显示语言选项
		if(Message.confirm)
		{//最终确认语言选择
			FlagContainers.bit.comfirmLangeuage = 1;
			state = DrawShowState_Confirmation;//确认语言动画
			confirm = 1;
		}
		else
		{
			FlagContainers.bit.comfirmLangeuage = 0;
		}
		if(Message.languageConfirmation)
		{//确认语言选择
			state = DrawShowState_Confirmation;//确认语言动画
			confirm = 1;
		}
		if(!confirm)
		{//语言菜单翻页
			state = DrawShowState_LanguageMenu;//语言选择菜单
			SetLanguageSelected(Message.select);//仅显示语言菜单时接收语言菜单滚动信息
		}
	}
	return state;
}

//检查是否需要显示历史记录
DrawMainShowState Draw::CheckCleaningRecord(DrawMainShowState state)
{
	if(Message.cleaningRecord)
	{//显示历史记录
		state = DrawShowState_History;//历史数据
	}
	return state;
}

//检查是否需要显示主菜单
DrawMainShowState Draw::CheckMainMenu(DrawMainShowState state)
{
	if(Message.mainMenu)
	{//显示主菜单
		state = DrawShowState_MainMenu;//主菜单
		SetMainEnum((RollMenu_en)Message.rollMenu);//仅显示主菜单时接收主菜单滚动信息
	}
	return state;
}

//检查是否显示故障或电量警告
DrawMainShowState Draw::CheckErrorData(DrawMainShowState state)
{
	ErrorData_en current = (ErrorData_en)Message.errorData;
	switch(Message.errorData)
	{
		case ErrorData_TuyereBlocked://全堵风口（UI风道堵塞）
		case ErrorData_RollerStall://地刷堵转（UI请清理滚刷）
		case ErrorData_RollerShortOut://地刷短路（UI请清理滚刷）
		case ErrorData_DischargeOvertemperatureProtection://放电过温保护（UI电池过温）  (不包含放电低温)
		case ErrorData_FilterNotInstalled://滤芯未安装（UI）
			if(ErrorData != Message.errorData)
			{
				state = DrawShowState_ShowError;//故障页面
				PlayingDelay = DelayFlag_Start;
				FlagContainers.bit.StartStrongPlaying = 1;		
				ShowErrorFlag.all = 0xFF;
			}
			state = DrawShowState_ShowError;//故障页面
			break;
		
		case ErrorData_BldcUndervoltage://BLDC欠压（UI错误代码1）--录在故障记录里
		case ErrorData_BldcCvervoltage://BLDC过压（UI错误代码1）--录在故障记录里
		case ErrorData_BldcOverTemperature://BLDC过温（UI错误代码1）--录在故障记录里
		case ErrorData_BldcOvercurrent://BLDC过流（UI错误代码1）--录在故障记录里
		case ErrorData_BldcOverspeed://BLDC超速（UI错误代码1）--录在故障记录里
		case ErrorData_BldcOpenPhase://BLDC缺相（UI错误代码1）--录在故障记录里
		case ErrorData_DischargeNoLoadProtection://放电空载保护（UI错误代码2）
		case ErrorData_CommunicationTimeout://通讯超时（可能发不出去）（UI错误代码3）--录在故障记录里
		case ErrorData_ChargerVoltageAbnormal://充电器电压异常（UI错误代码4）
		case ErrorData_ChargerOvercurrent://充电过流（UI错误代码5）
		case ErrorData_ChargerTimeout://充电超时（UI错误代码6）
		case ErrorData_BatteriesFault://电芯故障（UI错误代码7）--录在故障记录里
		case ErrorData_NTCFault://温度传感器(NTC)故障（UI错误代码8）--录在故障记录里
		case ErrorData_BMSHardwareFault://前端通讯失败(BMS硬件异常)（UI错误代码9）--录在故障记录里	
			if(ErrorData != Message.errorData)
			{
				ShowErrorFlag.all = 0xFF;
			}
			state = DrawShowState_ShowError;//故障页面
			break;
		
		case ErrorData_Reserve://放电过流/短路/ /BLDC关断失败保护，屏幕无法显示
		case ErrorData_OverchargeProtection://过充保护
		case ErrorData_OverDischargeProtection://过放保护				
		default:
			if(FlagContainers.bit.StrongPlaying && NextState == DrawShowState_ShowError)
			{//未完成强制故障播放的继续播放
				state = DrawShowState_ShowError;
				current = ErrorData;//维持原有故障状态
			}
			else
			{
				current = ErrorData_None;
				//ErrorData = ErrorData_None;
			}
			break;
	}
	
	ErrorData = current;
	return state;
}

DrawMainShowState Draw::CheckFilterServiceLife(DrawMainShowState state)
{
	if(Message.filterServiceLife != FILTER_SERVICE_LIFE_NORMAL)
	{//滤芯寿命提示界面
		if(Message.filterServiceLife == FILTER_SERVICE_LIFE_RINSE //提醒清洗滤芯(UI请清理滤芯) 不使用
			|| Message.filterServiceLife > FILTER_SERVICE_LIFE_EXPIRE)//超出范围的值
		{
			return state;
		}
		else if(FilterServiceLife != Message.filterServiceLife)
		{
			FilterServiceLifeFlag.bit.show = 1;
			PlayingDelay = DelayFlag_Start;
//			if(Message.filterServiceLife == FILTER_SERVICE_LIFE_REPLACE)
//			{//滤芯到期-提示后播放动画
//				FlagContainers.bit.StartStrongPlaying = 1;
//			}
//			else
//			{//滤芯将到期
				FlagContainers.bit.StartPlaying = 1;	
//			}
		}
		state = DrawShowState_FilterServiceLife;//滤芯寿命提示
		FilterServiceLife = Message.filterServiceLife;//记录需要提示的滤芯提示信息
	}
	return state;
}

DrawMainShowState Draw::CheckHighAltitudeMode(DrawMainShowState state)
{
	if(Message.highAltitudeMode != HIGH_ALTITUDE_MODE_NONE)
	{
		HighAltitudeMode = Message.highAltitudeMode;
		state = DrawShowState_HighAltitude;
	}
	return state;
}

DrawMainShowState Draw::CheckLock(DrawMainShowState state)
{
	if((SetLockState((V2205Bool)Message.lock) && Message.lockAction)
		|| FlagContainers.bit.Locking)
	{//自锁状态发生变化
		state = DrawShowState_Lock;//可能切换到锁动画页面
		FlagContainers.bit.Locking = 1;
	}
	return state;
}

DrawMainShowState Draw::CheckWorkMode(DrawMainShowState state)
{
	WorkState = Message.workState;
	switch(WorkState)
	{
		case WorkState_Charging://充电状态
			state = DrawShowState_Recharge;
			FlagContainers.bit.PowerOn = 1;//充电状态跳过开机动画
			LowBatteryWarning = LowBatteryWarning_None;//切换到充电清除电量低标志
			FlagContainers.bit.LowBattery = 0;//切换到充电清除电量低标志
			break;
		
		case WorkState_Work://放电状态						
			//3秒后显示灰尘等级曲线			
			if(!FlagContainers.bit.PowerOn)
			{
				state = DrawShowState_PowerOn;
				break;
			}		
			if(LowBatteryCheck(Message.batteryLevel))//电量低检测---仅放电状态检测
			{
				state = DrawShowState_ShowError;//电量低整合到故障页面
			}
			else
			{
				state = SetStateDischarge();
			}
			break;
		
		case WorkState_Standby://待机状态（屏幕亮、电机不转定义为待机）
		default:
			if(!FlagContainers.bit.PowerOn)
			{
				state = DrawShowState_PowerOn;
				break;
			}
			if(LowBatteryCheck(Message.batteryLevel))//电量低检测---仅放电状态检测
			{
				state = DrawShowState_ShowError;//电量低整合到故障页面
			}
			else
			{
				state = DrawShowState_SelectedMode;//显示模式选择页面 不会自动切换
			}	
			break;
	}
	WorkStatePrve = WorkState;
	return state;
}

//执行报文
void Draw::ExecuteMessage(void)
{
	DrawMainShowState state = NextState;//默认为不切换页面
	if(!FlagContainers.bit.RefreshFlag)
	{//没有收到新的报文，退出解析函数
		return;
	}
	FlagContainers.bit.StartExecute = 1;//开始解析 设置标志防止解析中报文内容发生更改
	FlagContainers.bit.RefreshFlag = 0;//清除报文更新标志
	
	SetBatteryLevel(Message.batteryLevel);//更新电量
	SetDustLevel(Message.dustLevel);//更新灰尘等级
	int shiftChange = SetShift((V2205ShiftInfo)Message.shift);//更新档位信息

	//可能出现打断情况
	if(shiftChange////档位发生变化
		|| WorkState != Message.workState)//模式发生变化
	{
		FlagContainers.bit.Locking = 0;
		FlagContainers.bit.Playing = 0;
	}

	//检查是否需要进入测试状态（显示版本号）
	if(Message.workState == WorkState_Test)
	{
		state = DrawShowState_TestMode;
		FlagContainers.bit.Playing = 0;
		FlagContainers.bit.StrongPlaying = 0;
		
		TestMode = (TestMode_en)Message.remainingMinute;
		
		goto EndExecuteMessage;
	}
	
	state = CheckWorkMode(state);//检查工作模式
	if(!FlagContainers.bit.PowerOn)
		goto EndExecuteMessage;
	if(LowBatteryWarning == LowBatteryWarning_Out)
	{//仅故障优先级比电量耗尽更高
		state = CheckErrorData(state);//检查故障状态
		FlagContainers.bit.Playing = 0;
		FlagContainers.bit.StrongPlaying = 0;
		goto EndExecuteMessage;//电量耗尽后只显示电量耗尽
	}
	
	state = CheckLock(state);//检查锁状态
	state = CheckFilterServiceLife(state);//检查滤芯寿命
	state = CheckMainMenu(state);	//检查主菜单状态
	state = CheckLanguageSetting(state);//检查语言菜单状态
	state = CheckCleaningRecord(state);//检查历史记录显示状态
	state = CheckFilterReset(state);//检查滤芯重置显示状态
	state = CheckHighAltitudeMode(state);//检查高海拔显示状态
	state = CheckErrorData(state);//检查故障状态
	
	RecordRunningTime(Message.workState);//记录运行时间
	
//	goto EndExecuteMessage;
//	/* 解析报文结束后的固定步骤 */
EndExecuteMessage:

	if(FlagContainers.bit.ChangeLangeuage)
	{
		FlagContainers.bit.ChangeLangeuage = 0;
		FlagContainers.bit.NeedStore = 1;
		NeedSave.Language = NewLanguage;//更新最新语言选择为当前语言
//		SAVE_NEED_SAVE(); //修改语言后立即进行一次存储
	}
	
	if((FlagContainers.bit.Playing | FlagContainers.bit.StrongPlaying) == 0)//播放中不允许切换页面
	{
		FlagContainers.bit.Playing = FlagContainers.bit.StartPlaying;
		FlagContainers.bit.StrongPlaying = FlagContainers.bit.StartStrongPlaying;
		FlagContainers.bit.StartPlaying = 0;
		FlagContainers.bit.StartStrongPlaying = 0;
		SetNextPage(state);//已开机状态允许切换其他页面
	}
	
	if(state != DrawShowState_DustLevel)
	{
		V2205Draw_LED_RED_OFF;
		V2205Draw_LED_GREEN_OFF;
	}
	
	//屏幕亮度 最高优先级 立即变化
	if(Message.screenLuminance == SCREEN_LUMINANCE_NORMAL)
	{//正常亮度
		ALLOW_DISPLAY();
	}
	else
	{//变暗
		DARK_SCREEN();
		if(FlagContainers.bit.NeedStore)
		{//屏幕变暗时如果有需要存储的文件 立即进行一次存储
			FlagContainers.bit.NeedStore = 0;
			SAVE_NEED_SAVE();
		}
	}
	
	FlagContainers.bit.StartExecute = 0;//报文解析结束 清除正在解析标志
}

/********************************************************************************************/

void Draw::DelayCtrl(void)
{
	if(ShowDustDelay != DelayFlag_Stop && ShowDustDelay != DelayFlag_Finish)
	{
		if(ShowDustDelay == DelayFlag_Start)
		{
			CtrlTickCount	 = 0;
			ShowDustDelay = DelayFlag_Count;
		}
		//if(CtrlTickCount > 3000)//3000
		{
			ShowDustDelay = DelayFlag_Finish;
			if(WorkState == WorkState_Work && NextState == DrawShowState_SelectedMode)// && FlagContainers.bit.PowerOn
				SetNextPage(DrawShowState_DustLevel);//计时到达后仍需判断当前是否在运行状态，如果已切换到其他状态，则不切换到灰尘等级页面
		}
	}
	//ErrorShowDelay
//	if(ErrorShowDelay != DelayFlag_Stop && ErrorShowDelay != DelayFlag_Finish)
//	{
//		if(ErrorShowDelay == DelayFlag_Start)
//		{
//			CtrlTickCount	 = 0;
//			ErrorShowDelay = DelayFlag_Count;
//		}
//		if(CtrlTickCount > 3000)
//		{
//			ErrorShowDelay = DelayFlag_Finish;
//		}
//	}
	//PlayingDelay
	if(PlayingDelay != DelayFlag_Stop && PlayingDelay != DelayFlag_Finish)
	{
		if(PlayingDelay == DelayFlag_Start)
		{
			CtrlTickCount	 = 0;
			PlayingDelay = DelayFlag_Count;
		}
		if(CtrlTickCount > 3650)
		{
			PlayingDelay = DelayFlag_Finish;
			FlagContainers.bit.Playing = 0;
			FlagContainers.bit.StrongPlaying = 0;
		}
	}
}

/********************************************************************************************/

int Draw::DrawPowerOn(void)
{
	char file_path[64];
	int result = 0;
	if(DrawTickCount >= 85)
	{//模式图标动画控制
		DrawTickCount = 0;
		result++;
		sprintf(file_path,"\\root\\icon\\poweron\\%d.ed", ContinuousPictureIndex);
		DecodeFilePlaneMode(0, 0, file_path);//绘制图片
		ContinuousPictureIndex += ContinuousPictureStep;
//		删帧测试
//		if((ContinuousPictureIndex >= 33 && ContinuousPictureIndex<=34)
//			|| (ContinuousPictureIndex >= 27 && ContinuousPictureIndex<=28))
//		{
//			ContinuousPictureIndex += ContinuousPictureStep;
//		}
		if(ContinuousPictureIndex > 30)
		{//播放到最后一帧

			FlagContainers.bit.PowerOn = 1;//标记为已开机
			if(LowBatteryCheck(batteryLevel))//电量低检测---仅放电状态检测
			{
				FlagContainers.bit.Playing = FlagContainers.bit.StartPlaying;
				FlagContainers.bit.StrongPlaying = FlagContainers.bit.StartStrongPlaying;
				FlagContainers.bit.StartPlaying = 0;
				FlagContainers.bit.StartStrongPlaying = 0;
				SetNextPage(DrawShowState_ShowError);
			}
			else
			{
				if(WorkState == WorkState_Work)
				{//放电状态
					SetNextPage(SetStateDischarge());
				}
				else
				{//待机状态
					SetNextPage(DrawShowState_SelectedMode);
				}	
			}		
		}
//		if(ContinuousPictureStep > 0)
//		{
//			if(ContinuousPictureIndex > 37)
//			{//播放到最后一帧
//				ContinuousPictureStep = -1;
//			}
//		}
//		else
//		{
//			if(ContinuousPictureIndex <= 32)
//			{//倒向播放到扇叶最开始一帧
//				if(ContinuousPictureIndex > 1)
//				{//选择全黑的一帧
//					ContinuousPictureIndex = 1;
//				}
//				else
//				{//刷新过全黑的一帧后退出
//					FlagContainers.bit.PowerOn = 1;//标记为已开机
//					if(WorkState == WorkState_Work)
//					{//放电状态	
//						SetNextPage(SetStateDischarge());
//					}
//					else
//					{//待机状态
//						SetNextPage(DrawShowState_SelectedMode);
//					}	
//				}
//			}
//		}
	}
	return result;
}

int Draw::DrawSelectedMode(void)
{
	char file_path[64];
	int result = 0;
	if(SelectedModeFlag.bit.Mode)
	{
		if(ContinuousPictureIndex <= 2)
		{//仅在已熄灭状态允许更换档位
			SelectedModeFlag.bit.Mode = 0;//清除模式更换标志	
			if(ContinuousPictureStep < 0)
				ContinuousPictureStep *= -1;
			if(CurrentShift != NewShift)
			{//需要切换档位
				ContinuousPictureIndex +=	ContinuousPictureStep;
				CurrentShift = NewShift;
				if(CurrentShift == V2205ShiftInfo_Auto)
				{//自动挡循环显示
					ContinuousPictureStep = 8;
					LoopShift = V2205ShiftInfo_Low;
				}
				else
				{//其余档位直接显示
					ContinuousPictureStep = 8;
					LoopShift = CurrentShift;
				}
			}
		}
		else if(ContinuousPictureIndex >= 25)
		{
			if(ContinuousPictureStep > 0)
				ContinuousPictureStep *= -1;
			ContinuousPictureIndex +=	ContinuousPictureStep;
		}
		else
		{
			ContinuousPictureStep = -8;
		}
	}
	if(DrawTickCount >= 80)
	{//模式图标动画控制
		DecodeFont& Font = *font; 
		DrawTickCount = 0;
		result++;
		//擦除文本区域，避免因文本位置变动引起的重影
		ClearPartScreen(0, 0, 240, 120 , 0);
		
		if(ContinuousPictureIndex > 25)
		{//新一次循环
			if(CurrentShift == V2205ShiftInfo_Auto)
			{
				if(ContinuousPictureStep > 2)
				{
					ContinuousPictureStep = 2;
				}
				ContinuousPictureStep *= -1;
			}
			ContinuousPictureIndex = 25;
		}
		if(ContinuousPictureIndex <= 1)
		{
			ContinuousPictureStep *= -1;
			if(CurrentShift == V2205ShiftInfo_Auto)
			{//自动挡循环显示
				int ls = LoopShift;
				if(++ls >= V2205ShiftInfo_Auto)
				{
					ls = V2205ShiftInfo_Low;
				}
				LoopShift = (V2205ShiftInfo)ls;
			}		
			ContinuousPictureIndex = 2;
		}
		sprintf(file_path,"\\root\\icon\\shift\\%d\\%d.ed", LoopShift, ContinuousPictureIndex);
		DecodeFilePlaneMode(0, 0, file_path);//绘制图片		
		
		ContinuousPictureIndex +=	ContinuousPictureStep;
//		{
//			sprintf(file_path,"\\root\\icon\\shift\\%d\\%d.ed", LoopShift, ContinuousPictureIndex);
//			DecodeFilePlaneMode(0, 0, file_path);//绘制图片		
//		}

		if(FlagContainers.bit.LowBattery)
		{//已显示电量低
			IDecodeText& text0 = Font.GetText(0);
			text0.sleep = true;
			if(ContinuousPictureIndex >= 12)
			{
				DecodeFilePlaneMode(76, 70, "\\root\\icon\\ldld.ed");//输出电量低图标
			}	
		}
		else
		{//未显示电量低
			IDecodeText& text0 = Font.GetText(0);
			text0.sleep = false;
			if(batteryLevel < 100)
			{
				sprintf(file_path,"%d%%",batteryLevel);
				text0.SetRollText(0, 74, 240, file_path, LanguageList[LanguageListIndex_SmallBattery], -10, RollType_Order_Center, 0xFFFF, 0xFFFF);
			}
			else
			{
				text0.SetRollText(0, 74, 240, "100%", LanguageList[LanguageListIndex_SmallBattery], -10, RollType_Order_Center, 0xFFFF, 0xFFFF);
			}
		}

		if(LockState)
		{//新锁状态是锁定状态
			DecodeFilePlaneMode(116, 1,"\\root\\icon\\dot.ed");
		}
		else
		{//新锁状态是解除状态
			ClearPartScreen(116, 1, 126, 10, 0);
		}
		IDecodeText& text1 = Font.GetText(1);
		text1.sleep = false;
		text1.SetRollText(TextListShiftTable[NeedSave.Language][NewShift-1]);
		font->Handle();
	}
	return result;
}

int Draw::DrawDustLevel(void)
{
	char file_path[64];
	int result;
	if(DustLevelFlag.bit.clear)
	{
		DustLevelFlag.bit.clear = 0;
		CLEAR_SCREEN();
		result++;
	}
	if(DrawTickCount >= 80)
	{//模式图标动画控制
		DecodeFont& Font = *font; 
		DrawTickCount = 0;	
		result++;	
		//擦除文本区域，避免因文本位置变动引起的重影
		ClearPartScreen(0, 0, 240, 120, 0);	
		
		if(CurrentShift != NewShift)
		{
			ContinuousPictureStep = -8;
		}
		
		ContinuousPictureIndex +=	ContinuousPictureStep;
		
		if(ContinuousPictureIndex > 25 || ContinuousPictureIndex < 2)
		{//新一次循环
			if(ContinuousPictureStep > 0)
			{
				ContinuousPictureStep = -2;
			}
			else
			{
				ContinuousPictureStep = 2;
			}
			//ContinuousPictureStep *= -1;
			if(ContinuousPictureIndex > 25)
			{
				ContinuousPictureIndex = 25;
			}
			else
			{
				ContinuousPictureIndex = 2;
			}
			//ContinuousPictureIndex +=	ContinuousPictureStep;
			if(ContinuousPictureStep > 0)
			{//熄灭状态
				if(CurrentShift != NewShift)
				{//需要切换档位
					CurrentShift = NewShift;
					if(CurrentShift == V2205ShiftInfo_Auto)
					{//自动挡循环显示
						LoopShift = V2205ShiftInfo_Low;
					}
					else
					{//其余档位直接显示
						LoopShift = CurrentShift;
					}
				}
				if(CurrentShift == V2205ShiftInfo_Auto)
				{//自动挡循环显示
					int ls = LoopShift;
					if(++ls >= V2205ShiftInfo_Auto)
					{
						ls = V2205ShiftInfo_Low;
					}
					LoopShift = (V2205ShiftInfo)ls;
				}
			}	
			if(DustLevel)
				sprintf(file_path,"\\root\\icon\\running\\%d\\%d\\%d.ed", LoopShift, DustLevel, ContinuousPictureIndex);
			else
				sprintf(file_path,"\\root\\icon\\running\\%d\\1\\%d.ed", LoopShift, ContinuousPictureIndex);
			DecodeFilePlaneMode(0, 0, file_path);//绘制图片		
		}
		else
		{
			if(DustLevel)
				sprintf(file_path,"\\root\\icon\\running\\%d\\%d\\%d.ed", LoopShift, DustLevel, ContinuousPictureIndex);
			else
				sprintf(file_path,"\\root\\icon\\running\\%d\\1\\%d.ed", LoopShift, ContinuousPictureIndex);
			DecodeFilePlaneMode(0, 0, file_path);//绘制图片		
		}
		if(FlagContainers.bit.LowBattery)
		{//已显示电量低
			IDecodeText& text0 = Font.GetText(0);
			text0.sleep = true;
			if(ContinuousPictureIndex >= 12)
			{
				DecodeFilePlaneMode(76, 70, "\\root\\icon\\ldld.ed");//输出电量低图标
			}		
		}
		else
		{//未显示电量低
			IDecodeText& text0 = Font.GetText(0);
			text0.sleep = false;
			if(batteryLevel < 100)
			{
				sprintf(file_path,"%d%%",batteryLevel);
				text0.SetRollText(0, 74, 240, file_path, LanguageList[LanguageListIndex_SmallBattery], -10, RollType_Order_Center, 0xFFFF, 0xFFFF);
			}
			else
			{
				text0.SetRollText(0, 74, 240, "100%", LanguageList[LanguageListIndex_SmallBattery], -10, RollType_Order_Center, 0xFFFF, 0xFFFF);
			}
		}
		
		if(LockState)
		{//新锁状态是锁定状态
			DecodeFilePlaneMode(116, 1,"\\root\\icon\\dot.ed");
		}
		else
		{//新锁状态是解除状态
			ClearPartScreen(116,1, 126, 10, 0);
		}
		IDecodeText& text1 = Font.GetText(1);
		text1.sleep = false;
		text1.SetRollText(TextListShiftTable[NeedSave.Language][NewShift-1]);
		font->Handle();
		
		if(DustLevel == V2205DustLevel_High)
		{
			V2205Draw_LED_RED_ON;
			V2205Draw_LED_GREEN_OFF;
		}
		else if(DustLevel == V2205DustLevel_Middle)
		{
			V2205Draw_LED_RED_ON;
			V2205Draw_LED_GREEN_ON;
		}
		else if(DustLevel == V2205DustLevel_Low)
		{
			V2205Draw_LED_RED_OFF;
			V2205Draw_LED_GREEN_ON;
		}
		else
		{
			V2205Draw_LED_RED_OFF;
			V2205Draw_LED_GREEN_OFF;
		}
	}
	return result;
}

int Draw::DrawMainMenu(void)
{
	//char file_path[64];
	int result;
	if(MainMenuFlag.bit.clear)
	{
		MainMenuFlag.bit.clear = 0;
		CLEAR_SCREEN();
		result++;
		
	}
	DecodeFont& Font = *font; 
	IDecodeText& text0 = Font.GetText(0);
	IDecodeText& text1 = Font.GetText(1);
	IDecodeText& text2 = Font.GetText(2);
	IDecodeText& text3 = Font.GetText(3);
	text0.sleep = false;
	text1.sleep = false;
	text2.sleep = false;
	text3.sleep = false;
	if(MainMenuFlag.bit.showAll)
	{
		MainMenuFlag.bit.showAll = 0;
		result++;
		
		text0.SetRollText(TextListMainMenuTable[NeedSave.Language][0]);
		text1.SetRollText(TextListMainMenuTable[NeedSave.Language][1]);
		text2.SetRollText(TextListMainMenuTable[NeedSave.Language][2]);
		text3.SetRollText(TextListMainMenuTable[NeedSave.Language][3]);	
		MainMenuPrve = RollMenu_None;
	}
	if(MainMenuFlag.bit.selected)
	{
		MainMenuFlag.bit.selected = 0;	
		if(MainMenuPrve != MainMenu)
		{
			result++;		
			switch(MainMenuPrve)
			{//调暗前一个高亮的文字
				case RollMenu_CleaningRecord://进入时默认为000(历史清洁记录)；按一次按键由000转为001
					text0.ChangeColor(0x8410, 0x8410);
					break;
			
				case RollMenu_ResetFilter://滤网重置，按一次按键由000转为001
					text1.ChangeColor(0x8410, 0x8410);
					break;
				
				case RollMenu_SelectLanguage://语言选择，按一次按键由001转为011
					text2.ChangeColor(0x8410, 0x8410);
					break;
				
				case RollMenu_Exit://退出，按一次按键由011转为100
					text3.ChangeColor(0x8410, 0x8410);
					break;
				
				default:
					break;
			}
			switch(MainMenu)
			{//高亮当前选中的文本
				case RollMenu_CleaningRecord://进入时默认为000(历史清洁记录)；按一次按键由000转为001
					text0.ChangeColor(0xFFFF, 0xFFFF);
					break;
			
				case RollMenu_ResetFilter://滤网重置，按一次按键由000转为001
					text1.ChangeColor(0xFFFF, 0xFFFF);
					break;
				
				case RollMenu_SelectLanguage://语言选择，按一次按键由001转为011
					text2.ChangeColor(0xFFFF, 0xFFFF);
					break;
				
				case RollMenu_Exit://退出，按一次按键由011转为100
					text3.ChangeColor(0xFFFF, 0xFFFF);
					break;
				
				default:
					break;
			}
			MainMenuPrve = MainMenu;
		}	
	}	
	if(DrawTickCount >= 80 || result)
	{//模式图标动画控制
		DrawTickCount = 0;	
		result++;	
		CLEAR_SCREEN();
		font->Handle();
	}
	return result;
}


int Draw::DrawHistory(void)
{
	char file_path[64];
	int result = 0;
	DecodeFont& Font = *font;
	if(HistoryFlag.bit.clear)
	{
		HistoryFlag.bit.clear = 0;
		CLEAR_SCREEN();
		result++;
	}
	if(HistoryFlag.bit.show)
	{
		HistoryFlag.bit.show = 0;
		result++;		
		DecodeFilePlaneMode(0, 0, "\\root\\icon\\history\\bg.ed");//历史界面背景	 
		IDecodeText& text0 = Font.GetText(0);
		text0.sleep = false;
		text0.SetRollText(TextListHistoryTable[NeedSave.Language]);
//		sprintf(file_path,"\\root\\text\\%d\\record.ed", NeedSave.Language);
//		DecodeFilePlaneMode(0, 180, file_path);	//历史界面底部文字
		for(int i=0; i<7; i++)
		{//绘制历史记录柱状图
			int history = (int)(NeedSave.History[i]/5);

			if(NeedSave.History[i] > 0.01f)//向上对齐
				history +=1;
			
			if(history > 19)//避免溢出
				history = 19;
			
			sprintf(file_path,"\\root\\icon\\history\\%d.ed", history);
			if(history != 0)
			{
				DecodeFilePlaneMode(47+27*i, 39, file_path);
			}
//			else
//			{
//				DecodeFilePlaneMode(34+28*i, 132, file_path);
//			}
		}	
		DrawTickCount = 80;
	}
	if(DrawTickCount >= 80)
	{
		DrawTickCount = 0;
		result++;	
		ClearPartScreen(0, 180, 240, 240, 0);
		Font.Handle();
	}
	return result;
}

int Draw::DrawResetFilter(void)
{
	char file_path[64];
	int result = 0;
	DecodeFont& Font = *font; 	
	if(ResetFilterFlag.bit.show)
	{
		ResetFilterFlag.bit.show = 0;
		DrawTickCount = 0;
		result++;
		ContinuousPictureIndex = 1;
		ContinuousPictureStep = 2;
		sprintf(file_path,"\\root\\icon\\loop\\%d.ed", ContinuousPictureIndex);//指定环
		DecodeFilePlaneMode(0, 0, file_path);
		
		DecodeFilePlaneMode(72, 45, "\\root\\icon\\lxcz0.ed");//绘制图标
		IDecodeText& text0 = Font.GetText(0);
		text0.sleep = false;
		text0.SetRollText(0, 146, 240, "3", LanguageList[LanguageListIndex_BigBattery], -10, RollType_Order_Center, 0xFFFF, 0xFFFF);
		Font.Handle();
		//DecodeFilePlaneMode(76, 146, "\\root\\text\\battery\\3.ed");//绘制数字
	}

	if(DrawTickCount >= 80)
	{
		if(ContinuousPictureIndex < 64)
		{//是否最终确认都可以播放的帧
			ContinuousPictureIndex += ContinuousPictureStep;
			DrawTickCount = 0;
			result++;
			sprintf(file_path,"\\root\\icon\\loop\\%d.ed", ContinuousPictureIndex*100/64);//指定环
			DecodeFilePlaneMode(0, 0, file_path);
			
			DecodeFilePlaneMode(72, 45, "\\root\\icon\\lxcz0.ed");//绘制图标
			
			IDecodeText& text0 = Font.GetText(0);
			sprintf(file_path,"%d",3 - ContinuousPictureIndex/22);
			text0.SetRollText(0, 146, 240, file_path, LanguageList[LanguageListIndex_BigBattery], -10, RollType_Order_Center, 0xFFFF, 0xFFFF);
			Font.Handle();
			//sprintf(file_path,"\\root\\text\\battery\\big\\%d.ed", 3 - ContinuousPictureIndex/22);//指定数字
			//DecodeFilePlaneMode(76, 146, file_path);//绘制数字
			
		}	
		else if(ContinuousPictureIndex < 75)
		{//剩余的其他帧
			if(FlagContainers.bit.ResetFilter)
			{//需要最终确认才能播放
				ContinuousPictureIndex += ContinuousPictureStep;
				if(ContinuousPictureIndex > 75)
				{
					ContinuousPictureIndex = 75;
				}
				DrawTickCount = 0;
				result++;
//				sprintf(file_path,"\\root\\icon\\loop\\%d.ed", ContinuousPictureIndex*4/3);//指定环
//				DecodeFilePlaneMode(0, 0, file_path);
				DecodeFilePlaneMode(0, 0, "\\root\\icon\\loop\\100.ed");
				
				DecodeFilePlaneMode(72, 45, "\\root\\icon\\lxcz1.ed");//绘制图标
				
				sprintf(file_path,"\\root\\icon\\verify\\%d.ed", ContinuousPictureIndex - 63);//指定对号
				DecodeFilePlaneMode(102, 156, file_path);//绘制对号
			}
		}
		else
		{
			if(!FlagContainers.bit.ResetFilter)
			{//确认 并退出语菜单
				FlagContainers.bit.ResetFilter = 0;
				ReturnPrevPage();
			}	
		}	
	}
	return result;
}

int Draw::DrawLanguageMenu(void)
{
	//char file_path[64];
	int result = 0;
	if(LanguageMenuFlag.bit.clear)
	{
		LanguageMenuFlag.bit.clear = 0;
		CLEAR_SCREEN();
		result++;
	}
	if(LanguageMenuFlag.bit.selected)
	{
		CLEAR_SCREEN();
		
		LanguageMenuFlag.bit.selected = 0;
		result++;
		int page = NewLanguage>>2;
		int current = NewLanguage&3;
		
		DecodeFont& Font = *font;
		IDecodeText& text0 = Font.GetText(0);
		IDecodeText& text1 = Font.GetText(1);
		IDecodeText& text2 = Font.GetText(2);
		IDecodeText& text3 = Font.GetText(3);
		text0.sleep = false;
		text1.sleep = false;
		text2.sleep = false;
		text3.sleep = false;	
		text0.SetRollText(TextListLanguageTable[page<<2]);
		text1.SetRollText(TextListLanguageTable[(page<<2) + 1]);
		text2.SetRollText(TextListLanguageTable[(page<<2) + 2]);
		text3.SetRollText(TextListLanguageTable[(page<<2) + 3]);
		switch(current)
		{
			case 0:
				text0.ChangeColor(0xFFFF, 0xFFFF);
				text1.ChangeColor(0x8410, 0x8410);
				text2.ChangeColor(0x8410, 0x8410);
				text3.ChangeColor(0x8410, 0x8410);
				break;
			
			case 1:
				text0.ChangeColor(0x8410, 0x8410);
				text1.ChangeColor(0xFFFF, 0xFFFF);
				text2.ChangeColor(0x8410, 0x8410);
				text3.ChangeColor(0x8410, 0x8410);
				break;
			
			case 2:
				text0.ChangeColor(0x8410, 0x8410);
				text1.ChangeColor(0x8410, 0x8410);
				text2.ChangeColor(0xFFFF, 0xFFFF);
				text3.ChangeColor(0x8410, 0x8410);
				break;
			
			case 3:
				text0.ChangeColor(0x8410, 0x8410);
				text1.ChangeColor(0x8410, 0x8410);
				text2.ChangeColor(0x8410, 0x8410);
				text3.ChangeColor(0xFFFF, 0xFFFF);
				break;
			
			default:
				break;
		}
		Font.Handle();
//		for(int i=page<<2; i<(page+1)<<2; i++)
//		{
//			int index = i&3;
//			if(index == current)
//			{//当前选中的语言选项 高亮显示
//				sprintf(file_path,"\\root\\text\\%d\\_l.ed", i);
//				DecodeFilePlaneMode(40, index*60, file_path);
//			}
//			else
//			{//未选中的语言选项 低亮度显示
//				sprintf(file_path,"\\root\\text\\%d\\_.ed", i);
//				DecodeFilePlaneMode(40, index*60, file_path);
//			}
//		}
		//绘制进度条
		if(page == 0)
		{
			DecodeFilePlaneMode(234, 26, "\\root\\icon\\pos1.ed");//绘制进度条
			DecodeFilePlaneMode(234, 90, "\\root\\icon\\pos0.ed");//绘制进度条
			DecodeFilePlaneMode(234, 154, "\\root\\icon\\pos0.ed");//绘制进度条
		}
		else if(page == 1)
		{
			DecodeFilePlaneMode(234, 26, "\\root\\icon\\pos0.ed");//绘制进度条
			DecodeFilePlaneMode(234, 90, "\\root\\icon\\pos1.ed");//绘制进度条
			DecodeFilePlaneMode(234, 154, "\\root\\icon\\pos0.ed");//绘制进度条
		}
		else 
		{
			DecodeFilePlaneMode(234, 26, "\\root\\icon\\pos0.ed");//绘制进度条
			DecodeFilePlaneMode(234, 90, "\\root\\icon\\pos0.ed");//绘制进度条
			DecodeFilePlaneMode(234, 154, "\\root\\icon\\pos1.ed");//绘制进度条
		}			
	}
	return result;
}

int Draw::DrawConfirmation(void)
{
	char file_path[64];
	int result = 0;
	DecodeFont& Font = *font;
	if(ConfirmationFlag.bit.clear)
	{
		ConfirmationFlag.bit.clear = 0;
		CLEAR_SCREEN();
		result++;
	}
	if(ConfirmationFlag.bit.show)
	{
		ConfirmationFlag.bit.show = 0;
		DrawTickCount = 0;
		ContinuousPictureIndex = 1;
		 ContinuousPictureStep = 2;
		result++;	
	}
	if(DrawTickCount >= 80)
	{
		if(ContinuousPictureIndex < 64)
		{//是否最终确认都可以播放的帧
			ContinuousPictureIndex += ContinuousPictureStep;
			DrawTickCount = 0;
			result++;
			sprintf(file_path,"\\root\\icon\\loop\\%d.ed", ContinuousPictureIndex*100/64);//指定环
			DecodeFilePlaneMode(0, 0, file_path);
			IDecodeText& text0 = Font.GetText(0);
			text0.sleep = false;
			text0.SetRollText(TextListLanguageTable[NewLanguage]);
			text0.ChangeColor(0x8410, 0x8410);
			text0.ChangeTextPos(0, 72);
			
			//sprintf(file_path,"\\root\\text\\%d\\_l.ed", NewLanguage);//指定文字
			//DecodeFilePlaneMode(40, 72, file_path);//指定文字
			
			IDecodeText& text1 = Font.GetText(1);
			text1.sleep = false;
			sprintf(file_path,"%d",3 - ContinuousPictureIndex/22);
			text1.SetRollText(0, 146, 240, file_path, LanguageList[LanguageListIndex_BigBattery], -10, RollType_Order_Center, 0xFFFF, 0xFFFF);
			Font.Handle();
			
			//sprintf(file_path,"\\root\\text\\battery\\big\\%d.ed", 3 - ContinuousPictureIndex/22);//指定数字
			//DecodeFilePlaneMode(76, 146, file_path);//绘制数字
		}	
		else if(ContinuousPictureIndex < 75)
		{//剩余的其他帧
			if(FlagContainers.bit.comfirmLangeuage)
			{//需要最终确认才能播放
				ContinuousPictureIndex += ContinuousPictureStep;
				if(ContinuousPictureIndex > 75)
				{
					ContinuousPictureIndex = 75;
				}
				DrawTickCount = 0;
				result++;
//				sprintf(file_path,"\\root\\icon\\loop\\%d.ed", ContinuousPictureIndex*4/3);//指定环
//				DecodeFilePlaneMode(0, 0, file_path);
				DecodeFilePlaneMode(0, 0, "\\root\\icon\\loop\\100.ed");
				
				DecodeFilePlaneMode(0, 0, file_path);
				IDecodeText& text0 = Font.GetText(0);
				text0.ChangeColor(0xFFFF, 0xFFFF);
				IDecodeText& text1 = Font.GetText(1);
				text1.sleep = true;
				Font.Handle();
				//sprintf(file_path,"\\root\\text\\%d\\_l.ed", NewLanguage);//指定文字
				//DecodeFilePlaneMode(40, 72, file_path);//指定文字
				
				sprintf(file_path,"\\root\\icon\\verify\\%d.ed", ContinuousPictureIndex - 63);//指定对号
				DecodeFilePlaneMode(102, 156, file_path);//绘制对号
			}
		}
		else
		{
			//播放完成 允许存储
			FlagContainers.bit.ChangeLangeuage = 1;
			if(!FlagContainers.bit.comfirmLangeuage)
			{//确认 并退出语菜单
				FlagContainers.bit.comfirmLangeuage = 0;
				NeedSave.Language = NewLanguage;//更新最新语言选择为当前语言
				ReturnFromMenu();		
			}	
		}	
	}
	return result;
}

int Draw::DrawRecharge(void)
{
	char file_path[64];
	int result = 0;
//	if(RechargeFlag.bit.clear)
//	{
//		RechargeFlag.bit.clear = 0;
//		CLEAR_SCREEN();
//		result++;
//	}
//	if(RechargeFlag.bit.battery)
//	{
//		RechargeFlag.bit.battery = 0;
//		DrawTickCount = 0;
//		result++;
//		sprintf(file_path,"\\root\\recharge\\%d.ed", batteryLevel);
//		DecodeFilePlaneMode(0, 0, file_path);
//	}
	if(DrawTickCount >= 80)
	{
		DrawTickCount = 0;
		result++;
		
		if(lastBatteryLevel != batteryLevel)
		{
			lastBatteryLevel = batteryLevel;

			//更新充电电量
			DecodeFont& Font = *font;
			IDecodeText& text0 = Font.GetText(0);
			text0.sleep = false;
			if(batteryLevel < 100)
			{
				//更新充电进度
				sprintf(file_path,"\\root\\icon\\loop\\%d.ed", batteryLevel);//指定环			
				DecodeFilePlaneMode(0, 0, file_path);
				
				sprintf(file_path,"%d",batteryLevel);
				text0.SetRollText(0, 60, 240, file_path, LanguageList[LanguageListIndex_BigBattery], -10, RollType_Order_Center, 0xFFFF, 0xFFFF);
			}
			else
			{
				DecodeFilePlaneMode(0, 0, "\\root\\icon\\loop\\100.ed");
				text0.SetRollText(0, 60, 240, "100", LanguageList[LanguageListIndex_BigBattery], -10, RollType_Order_Center, 0xFFFF, 0xFFFF);
			}
			
			Font.Handle();

			//sprintf(file_path,"\\root\\text\\battery\\big\\%d.ed", batteryLevel);//指定电量数字
			//DecodeFilePlaneMode(76, 60, file_path);
		}
		
		sprintf(file_path,"\\root\\icon\\bolt\\%d.ed", ContinuousPictureIndex);//指定闪电	
		DecodeFilePlaneMode(104, 136, file_path);//绘制闪电
		
		if(batteryLevel >= 100)
		{
			if(ContinuousPictureStep < 0)
			{
				ContinuousPictureStep *= -1;
			}

			ContinuousPictureIndex -= ContinuousPictureStep;
			if(ContinuousPictureIndex <= 1)
			{
				ContinuousPictureIndex = 1;
			}
		}
		else
		{		
			ContinuousPictureIndex += ContinuousPictureStep;
			if(ContinuousPictureIndex > 25 || ContinuousPictureIndex < 1)
			{
				ContinuousPictureStep *= -1;
			}

		}
		
		
	}
	return result;
}

int Draw::DrawLock(void)
{
	char file_path[64];
	int result = 0;
	DecodeFont& Font = *font;
	if(LockFlag.bit.clear)
	{
		LockFlag.bit.clear = 0;
		CLEAR_SCREEN();
		result++;
	}
	if(LockFlag.bit.show)
	{
		LockFlag.bit.show = 0;
		DrawTickCount = 80;
		result++;
		IDecodeText& text0 = Font.GetText(0);
		text0.sleep = false;	
		if(LockState)
		{//上锁
			ContinuousPictureIndex = 0;
			ContinuousPictureStep = 2;	
			text0.SetRollText(TextListLockTable[NeedSave.Language]);
//			sprintf(file_path,"\\root\\text\\%d\\lock.ed", NeedSave.Language);
//			if(NeedSave.Language >= LanguageOptions_English && NeedSave.Language <= LanguageOptions_Russian)
//			{
//				DecodeFilePlaneMode(0, 104, file_path);
//			}
//			else
//			{
//				DecodeFilePlaneMode(0, 130, file_path);
//			}
		}
		else
		{//解锁	
			ContinuousPictureIndex = 20;
			ContinuousPictureStep = -2;
			text0.SetRollText(TextListUnlockTable[NeedSave.Language]);
//			sprintf(file_path,"\\root\\text\\%d\\unlock.ed", NeedSave.Language);
//			if(NeedSave.Language >= LanguageOptions_English && NeedSave.Language <= LanguageOptions_Russian)
//			{
//				DecodeFilePlaneMode(0, 104, file_path);
//			}
//			else
//			{
//				DecodeFilePlaneMode(0, 130, file_path);
//			}	
		}
	}
	if(DrawTickCount >= 80)
	{
		if(ContinuousPictureIndex >= 0 && ContinuousPictureIndex <= 20)
		{
			DrawTickCount = 0;
			result++;
			sprintf(file_path,"\\root\\icon\\lock\\%d.ed", ContinuousPictureIndex);
//			if(NeedSave.Language >= LanguageOptions_English && NeedSave.Language <= LanguageOptions_Russian)
//			{
//				DecodeFilePlaneMode(72, 18, file_path);
//			}
//			else
//			{
				DecodeFilePlaneMode(72, 38, file_path);
//			}
			ContinuousPictureIndex += ContinuousPictureStep;	
			result++;
			ClearPartScreen(0, 130, 240, 240, 0);
			Font.Handle();
		}	
		else
		{
			if(DrawTickCount >= 1040)
			{
				ReturnPrevPage();
			}		
			if(DrawTickCount%80 == 0)
			{
				result++;
				ClearPartScreen(0, 130, 240, 240, 0);
				Font.Handle();
			}			
		}	
	}
	return result;
}

int Draw::DrawShowError(void)
{
//	char file_path[64];
	int result = 0;
	DecodeFont& Font = *font;
	if(ShowErrorFlag.bit.clear)
	{
		ShowErrorFlag.bit.clear = 0;
		CLEAR_SCREEN();
		result++;
	}
	if(ShowErrorFlag.bit.show)
	{
		ShowErrorFlag.bit.show = 0;		
		IDecodeText& text0 = Font.GetText(0);
		text0.sleep = false;
		switch(ErrorData)
		{
			case ErrorData_BldcUndervoltage://BLDC欠压（UI错误代码1）--录在故障记录里		
			case ErrorData_BldcCvervoltage://BLDC过压（UI错误代码1）--录在故障记录里
			case ErrorData_BldcOverTemperature://BLDC过温（UI错误代码1）--录在故障记录里	
			case ErrorData_BldcOvercurrent://BLDC过流（UI错误代码1）--录在故障记录里
			case ErrorData_BldcOverspeed://BLDC超速（UI错误代码1）--录在故障记录里
			case ErrorData_BldcOpenPhase://BLDC缺相（UI错误代码1）--录在故障记录里
				text0.SetRollText(TextListErrorCodeTable[0]);	
				break;
			
			case ErrorData_TuyereBlocked://全堵风口（UI风道堵塞）
				text0.SetRollText(TextListTuyereBlockedTable[NeedSave.Language]);
				break;
			
			case ErrorData_RollerStall://地刷堵转（UI请清理滚刷）
			case ErrorData_RollerShortOut://地刷短路（UI请清理滚刷）
				text0.SetRollText(TextListRollerStallTable[NeedSave.Language]);
				break;
			
			case ErrorData_OverDischargeProtection://过放保护
				text0.sleep = true;
				return result;
			
			case ErrorData_DischargeOvertemperatureProtection://放电过温保护（UI电池过温）  (不包含放电低温)
				text0.SetRollText(TextListOvertemperatureTable[NeedSave.Language]);
				break;
			
			case ErrorData_DischargeNoLoadProtection://放电空载保护（UI错误代码2）
				text0.SetRollText(TextListErrorCodeTable[1]);
				break;
			
			case ErrorData_CommunicationTimeout://通讯超时（可能发不出去）（UI错误代码3）--录在故障记录里		
				text0.SetRollText(TextListErrorCodeTable[2]);	
				break;
			
			case ErrorData_FilterNotInstalled://滤芯未安装（UI）
				text0.SetRollText(TextListFilterNotInstalledTable[NeedSave.Language]);
				break;
			
			case ErrorData_Reserve://放电过流/短路/ /BLDC关断失败保护，屏幕无法显示
				text0.sleep = true;
				return result;
			
			case ErrorData_OverchargeProtection://过充保护
				text0.sleep = true;
				return result;
			
			case ErrorData_ChargerVoltageAbnormal://充电器电压异常（UI错误代码4）
				text0.SetRollText(TextListErrorCodeTable[3]);
				break;
			
			case ErrorData_ChargerOvercurrent://充电过流（UI错误代码5）
				text0.SetRollText(TextListErrorCodeTable[4]);
				break;
			
			case ErrorData_ChargerTimeout://充电超时（UI错误代码6）
				text0.SetRollText(TextListErrorCodeTable[5]);
				break;
			
			case ErrorData_BatteriesFault://电芯故障（UI错误代码7）--录在故障记录里
				text0.SetRollText(TextListErrorCodeTable[6]);
				break;
			
			case ErrorData_NTCFault://温度传感器(NTC)故障（UI错误代码8）--录在故障记录里
				text0.SetRollText(TextListErrorCodeTable[7]);
				break;
			
			case ErrorData_BMSHardwareFault://前端通讯失败(BMS硬件异常)（UI错误代码9）--录在故障记录里
				text0.SetRollText(TextListErrorCodeTable[8]);
				break;
			
			default://不是记录的故障或暂无故障 继续进行电量低警告判断
				if(LowBatteryWarning == LowBatteryWarning_Low)
				{
					text0.SetRollText(TextListBatteryLowTable[NeedSave.Language]);
				}
				else if(LowBatteryWarning == LowBatteryWarning_Out)
				{
					text0.SetRollText(TextListBatteryOutTable[NeedSave.Language]);
				}
				else
				{//其他位置故障
					text0.sleep = true;
				}
				break;
		}
		DrawTickCount = 0;
	}
	if(DrawTickCount <= 3600)
	{//0~600 亮600ms
		if(DrawTickCount%1200 == 0)
		{
			switch(ErrorData)
			{
				case ErrorData_BldcUndervoltage://BLDC欠压（UI错误代码1）--录在故障记录里		
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");			
					goto EndErrorDisplay;
				
				case  ErrorData_BldcCvervoltage://BLDC过压（UI错误代码1）--录在故障记录里
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");	
					goto EndErrorDisplay;
				
				case ErrorData_BldcOverTemperature://BLDC过温（UI错误代码1）--录在故障记录里	
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");
					goto EndErrorDisplay;	
				
				case ErrorData_BldcOvercurrent://BLDC过流（UI错误代码1）--录在故障记录里
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");
					goto EndErrorDisplay;
				
				case ErrorData_BldcOverspeed://BLDC超速（UI错误代码1）--录在故障记录里
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");
					goto EndErrorDisplay;
				
				case ErrorData_BldcOpenPhase://BLDC缺相（UI错误代码1）--录在故障记录里
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");
					goto EndErrorDisplay;
				
				case ErrorData_TuyereBlocked://全堵风口（UI风道堵塞）
					result++;//仅有UI界面的进行自增 否则直接退出	
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\fdds.ed");
					goto EndErrorDisplay;
				
				case ErrorData_RollerStall://地刷堵转（UI请清理滚刷）
				case ErrorData_RollerShortOut://地刷短路（UI请清理滚刷）
					result++;//仅有UI界面的进行自增 否则直接退出
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\qlgs.ed");
					goto EndErrorDisplay;
				
				case ErrorData_OverDischargeProtection://过放保护
					return result;
				
				case ErrorData_DischargeOvertemperatureProtection://放电过温保护（UI电池过温）  (不包含放电低温)
					result++;//仅有UI界面的进行自增 否则直接退出			
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\dcgr.ed");
					goto EndErrorDisplay;
				
				case ErrorData_DischargeNoLoadProtection://放电空载保护（UI错误代码2）
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");	
					goto EndErrorDisplay;
				
				case ErrorData_CommunicationTimeout://通讯超时（可能发不出去）（UI错误代码3）--录在故障记录里		
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");	
					goto EndErrorDisplay;
				
				case ErrorData_FilterNotInstalled://滤芯未安装（UI）
					result++;//仅有UI界面的进行自增 否则直接退出
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\lxwaz.ed");
					goto EndErrorDisplay;
				
				case ErrorData_Reserve://放电过流/短路/ /BLDC关断失败保护，屏幕无法显示
					return result;
				
				case ErrorData_OverchargeProtection://过充保护
					return result;
				
				case ErrorData_ChargerVoltageAbnormal://充电器电压异常（UI错误代码4）
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");	
					goto EndErrorDisplay;
				
				case ErrorData_ChargerOvercurrent://充电过流（UI错误代码5）
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");
					goto EndErrorDisplay;
				
				case ErrorData_ChargerTimeout://充电超时（UI错误代码6）
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");	
					goto EndErrorDisplay;
				
				case ErrorData_BatteriesFault://电芯故障（UI错误代码7）--录在故障记录里
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");
					goto EndErrorDisplay;
				
				case ErrorData_NTCFault://温度传感器(NTC)故障（UI错误代码8）--录在故障记录里
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");
					goto EndErrorDisplay;
				
				case ErrorData_BMSHardwareFault://前端通讯失败(BMS硬件异常)（UI错误代码9）--录在故障记录里
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");	
					goto EndErrorDisplay;
				
				default://不是记录的故障或暂无故障 继续进行电量低警告判断
					if(LowBatteryWarning == LowBatteryWarning_Low)
					{	
						result++;
						FlagContainers.bit.LowBattery = 1;
						FlagContainers.bit.LowBatteryPage = 1;
						DecodeFilePlaneMode(72, 38,"\\root\\icon\\dld.ed");
						goto EndErrorDisplay;
					}
					else if(LowBatteryWarning == LowBatteryWarning_Out)
					{
						result++;
						DecodeFilePlaneMode(72, 38,"\\root\\icon\\dlhj.ed");
						goto EndErrorDisplay;
					}
					else
					{
						
					}
					break;
			}	
		}
		else if(DrawTickCount%1200 == 600)
		{//600~1200 部分需要灭600ms			
			switch(ErrorData)
			{
				case ErrorData_BldcUndervoltage://BLDC欠压（UI错误代码1）--录在故障记录里	
					result++;					
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");			
					goto EndErrorDisplay;
				
				case  ErrorData_BldcCvervoltage://BLDC过压（UI错误代码1）--录在故障记录里
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");	
					goto EndErrorDisplay;
				
				case ErrorData_BldcOverTemperature://BLDC过温（UI错误代码1）--录在故障记录里	
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");	
					goto EndErrorDisplay;	
				
				case ErrorData_BldcOvercurrent://BLDC过流（UI错误代码1）--录在故障记录里
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");
					goto EndErrorDisplay;
				
				case ErrorData_BldcOverspeed://BLDC超速（UI错误代码1）--录在故障记录里
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");
					goto EndErrorDisplay;
				
				case ErrorData_BldcOpenPhase://BLDC缺相（UI错误代码1）--录在故障记录里
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");
					goto EndErrorDisplay;
				
				case ErrorData_TuyereBlocked://全堵风口（UI风道堵塞）
					result++;//仅有UI界面的进行自增 否则直接退出
					ClearPartScreen(72, 38, 168, 128, 0);
					goto EndErrorDisplay;
				
				case ErrorData_RollerStall://地刷堵转（UI请清理滚刷）
				case ErrorData_RollerShortOut://地刷短路（UI请清理滚刷）
					result++;//仅有UI界面的进行自增 否则直接退出
					ClearPartScreen(72, 38, 168, 128, 0);
					goto EndErrorDisplay;
				
				case ErrorData_OverDischargeProtection://过放保护
					return result;
				
				case ErrorData_DischargeOvertemperatureProtection://放电过温保护（UI电池过温）  (不包含放电低温)
					result++;//仅有UI界面的进行自增 否则直接退出			
					ClearPartScreen(72, 38, 168, 128, 0);
					goto EndErrorDisplay;
				
				case ErrorData_DischargeNoLoadProtection://放电空载保护（UI错误代码2）
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");
					goto EndErrorDisplay;
				
				case ErrorData_CommunicationTimeout://通讯超时（可能发不出去）（UI错误代码3）--录在故障记录里		
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");	
					goto EndErrorDisplay;
				
				case ErrorData_FilterNotInstalled://滤芯未安装（UI）
					result++;//仅有UI界面的进行自增 否则直接退出
					ClearPartScreen(72, 38, 168, 128, 0);
					goto EndErrorDisplay;
				
				case ErrorData_Reserve://放电过流/短路/ /BLDC关断失败保护，屏幕无法显示
					return result;
				
				case ErrorData_OverchargeProtection://过充保护
					return result;
				
				case ErrorData_ChargerVoltageAbnormal://充电器电压异常（UI错误代码4）
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");
					goto EndErrorDisplay;
				
				case ErrorData_ChargerOvercurrent://充电过流（UI错误代码5）
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");	
					goto EndErrorDisplay;
				
				case ErrorData_ChargerTimeout://充电超时（UI错误代码6）
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");
					goto EndErrorDisplay;
				
				case ErrorData_BatteriesFault://电芯故障（UI错误代码7）--录在故障记录里
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");
					goto EndErrorDisplay;
				
				case ErrorData_NTCFault://温度传感器(NTC)故障（UI错误代码8）--录在故障记录里
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");
					goto EndErrorDisplay;
				
				case ErrorData_BMSHardwareFault://前端通讯失败(BMS硬件异常)（UI错误代码9）--录在故障记录里
					result++;
					DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");	
					goto EndErrorDisplay;
				
				default://不是记录的故障或暂无故障 继续进行电量低警告判断
					if(LowBatteryWarning == LowBatteryWarning_Low)
					{
						result++;
						ClearPartScreen(72, 38, 168, 128, 0);
						goto EndErrorDisplay;
					}
					else if(LowBatteryWarning == LowBatteryWarning_Out)
					{
						result++;
						DecodeFilePlaneMode(72, 38,"\\root\\icon\\dlhj.ed");
						goto EndErrorDisplay;
					}
					else
					{
						return result;
					}
			}		
		}		
	}
	else if(DrawTickCount < 3760)
	{
		DrawTickCount = 3760;	
		switch(ErrorData)
		{
			case ErrorData_BldcUndervoltage://BLDC欠压（UI错误代码1）--录在故障记录里				
				DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");		
				break;
			
			case  ErrorData_BldcCvervoltage://BLDC过压（UI错误代码1）--录在故障记录里
				DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");	
				break;
			
			case ErrorData_BldcOverTemperature://BLDC过温（UI错误代码1）--录在故障记录里	
				DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");
				break;
			
			case ErrorData_BldcOvercurrent://BLDC过流（UI错误代码1）--录在故障记录里
				DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");
				break;
			
			case ErrorData_BldcOverspeed://BLDC超速（UI错误代码1）--录在故障记录里
				DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");
				break;
			
			case ErrorData_BldcOpenPhase://BLDC缺相（UI错误代码1）--录在故障记录里
				DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");
				break;
			
			case ErrorData_TuyereBlocked://全堵风口（UI风道堵塞）
				result++;//仅有UI界面的进行自增 否则直接退出			
				DecodeFilePlaneMode(72, 38, "\\root\\icon\\fdds.ed");			
				break;
			
			case ErrorData_RollerStall://地刷堵转（UI请清理滚刷）
			case ErrorData_RollerShortOut://地刷短路（UI请清理滚刷）
				result++;//仅有UI界面的进行自增 否则直接退出
				DecodeFilePlaneMode(72, 38, "\\root\\icon\\qlgs.ed");
				break;
			
			case ErrorData_OverDischargeProtection://过放保护
				break;
			
			case ErrorData_DischargeOvertemperatureProtection://放电过温保护（UI电池过温）  (不包含放电低温)
				result++;//仅有UI界面的进行自增 否则直接退出			
				DecodeFilePlaneMode(72, 38, "\\root\\icon\\dcgr.ed");
				break;
			
			case ErrorData_DischargeNoLoadProtection://放电空载保护（UI错误代码2）
				DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");	
				break;
			
			case ErrorData_CommunicationTimeout://通讯超时（可能发不出去）（UI错误代码3）--录在故障记录里		
				DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");	
				break;
			
			case ErrorData_FilterNotInstalled://滤芯未安装（UI）
				result++;//仅有UI界面的进行自增 否则直接退出
				DecodeFilePlaneMode(72, 38, "\\root\\icon\\lxwaz.ed");
				break;
			
			case ErrorData_Reserve://放电过流/短路/ /BLDC关断失败保护，屏幕无法显示
				return result;
			
			case ErrorData_OverchargeProtection://过充保护
				return result;
			
			case ErrorData_ChargerVoltageAbnormal://充电器电压异常（UI错误代码4）
				DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");
				break;
			
			case ErrorData_ChargerOvercurrent://充电过流（UI错误代码5）
				DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");
				break;
			
			case ErrorData_ChargerTimeout://充电超时（UI错误代码6）
				DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");	
				break;
			
			case ErrorData_BatteriesFault://电芯故障（UI错误代码7）--录在故障记录里
				DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");
				break;
			
			case ErrorData_NTCFault://温度传感器(NTC)故障（UI错误代码8）--录在故障记录里
				DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");	
				break;
			
			case ErrorData_BMSHardwareFault://前端通讯失败(BMS硬件异常)（UI错误代码9）--录在故障记录里
				DecodeFilePlaneMode(72, 38, "\\root\\icon\\gzdm.ed");
				break;
			
			default://不是记录的故障或暂无故障 继续进行电量低警告判断
				if(LowBatteryWarning == LowBatteryWarning_Low)
				{
					ReturnPrevPage();
					return result;
				}
				else if(LowBatteryWarning == LowBatteryWarning_Out)
				{
					result++;
					DecodeFilePlaneMode(72, 38,"\\root\\icon\\dlhj.ed");
					break;
				}
				else
				{
					return result;
				}
		}		
	}
	else if(DrawTickCount >= 3840)
	{
		DrawTickCount = 3760;
	}
	if(DrawTickCount%80 == 0)
	{
		result++;
		ClearPartScreen(0, 130, 240, 240, 0);
		Font.Handle();
	}
	return result;
	
EndErrorDisplay:
	ClearPartScreen(0, 130, 240, 240, 0);
	Font.Handle();
	return result;
}

int Draw::DrawHighAltitude(void)
{
	char file_path[64];
	int result = 0;
//	if(HighAltitudeFlag.bit.clear)
//	{
//		HighAltitudeFlag.bit.clear = 0;
//		CLEAR_SCREEN();
//		result++;
//	}
	if(HighAltitudeFlag.bit.show)
	{
		HighAltitudeFlag.bit.show = 0;
		ContinuousPictureIndex = 0;
		ContinuousPictureStep = 2;
	}
	if(DrawTickCount >= 80)
	{
		if(ContinuousPictureIndex < 64)
		{//是否最终确认都可以播放的帧
			ContinuousPictureIndex += ContinuousPictureStep;
			DrawTickCount = 0;
			result++;
			sprintf(file_path,"\\root\\icon\\loop\\%d.ed", ContinuousPictureIndex*100/64);//指定环
			DecodeFilePlaneMode(0, 0, file_path);
			
			if(HighAltitudeMode == HIGH_ALTITUDE_MODE_ENTERING
				|| HighAltitudeMode == HIGH_ALTITUDE_MODE_ENTERED)
			{
				DecodeFilePlaneMode(72, 45, "\\root\\icon\\highon0.ed");//绘制图标
			}
			else
			{
				DecodeFilePlaneMode(72, 45, "\\root\\icon\\highoff0.ed");//绘制图标
			}
			
			DecodeFont& Font = *font;
			IDecodeText& text0 = Font.GetText(0);
			text0.sleep = false;
			sprintf(file_path,"%d",3 - ContinuousPictureIndex/22);
			text0.SetRollText(0, 146, 240, file_path, LanguageList[LanguageListIndex_BigBattery], -10, RollType_Order_Center, 0xFFFF, 0xFFFF);
			Font.Handle();
			
			//sprintf(file_path,"\\root\\text\\battery\\big\\%d.ed", 3 - ContinuousPictureIndex/22);//指定数字
			//DecodeFilePlaneMode(76, 146, file_path);//绘制数字
		}	
		else if(ContinuousPictureIndex < 75)
		{//剩余的其他帧
			if(HighAltitudeMode == HIGH_ALTITUDE_MODE_ENTERED
				|| HighAltitudeMode ==  HIGH_ALTITUDE_MODE_EXITED)
			{//需要最终确认才能播放
				ContinuousPictureIndex += ContinuousPictureStep;
				if(ContinuousPictureIndex > 75)
				{
					ContinuousPictureIndex = 75;
				}
				DrawTickCount = 0;
				result++;
//				sprintf(file_path,"\\root\\icon\\loop\\%d.ed", ContinuousPictureIndex*4/3);//指定环
//				DecodeFilePlaneMode(0, 0, file_path);
				
				DecodeFilePlaneMode(0, 0, "\\root\\icon\\loop\\100.ed");
				if(HighAltitudeMode == HIGH_ALTITUDE_MODE_ENTERING
					|| HighAltitudeMode == HIGH_ALTITUDE_MODE_ENTERED)
				{
					
					DecodeFilePlaneMode(72, 45, "\\root\\icon\\highon1.ed");//绘制图标
				}
				else
				{
					DecodeFilePlaneMode(72, 45, "\\root\\icon\\highoff1.ed");//绘制图标
				}
				sprintf(file_path,"\\root\\icon\\verify\\%d.ed", ContinuousPictureIndex - 63);//指定对号
				DecodeFilePlaneMode(102, 156, file_path);//绘制对号
			}
		}
//		else
//		{
//			if(HighAltitudeMode == HIGH_ALTITUDE_MODE_ENTERED
//				|| HighAltitudeMode ==  HIGH_ALTITUDE_MODE_EXITED)
//			{//确认 并退出语菜单
//				FlagContainers.bit.ResetFilter = 0;
//				ReturnPrevPage();
//			}	
//		}	
	}
	return result;
}

int Draw::DrawFilterServiceLife(void)
{
	char file_path[64];
	int result = 0;
	DecodeFont& Font = *font;
	if(FilterServiceLifeFlag.bit.clear)
	{
		FilterServiceLifeFlag.bit.clear = 0;
		CLEAR_SCREEN();
		result++;
	}
	if(FilterServiceLifeFlag.bit.show)
	{
		FilterServiceLifeFlag.bit.show = 0;	
		DrawTickCount = 0;			
		IDecodeText& text0 = Font.GetText(0);
		text0.sleep = false;
		if(FilterServiceLife == FILTER_SERVICE_LIFE_REPLACE)
		{/*提醒更换滤芯(UI请更换滤芯)*/
			result++;
			ContinuousPictureIndex = 1;
			ContinuousPictureStep = 2;
			DecodeFilePlaneMode(72, 38,"\\root\\icon\\ghlx.ed");
			
			text0.SetRollText(TextListReplaceFilterTable[NeedSave.Language]);
			Font.Handle();			
//			sprintf(file_path,"\\root\\text\\%d\\ghlx.ed", NeedSave.Language);
//			DecodeFilePlaneMode(0, 130, file_path);
		}
		else if(FilterServiceLife == FILTER_SERVICE_LIFE_EXPIRE)
		{/*滤芯将要过期请尽快更换 (UI滤芯将要到期提醒)*/
			result++;	
			DecodeFilePlaneMode(72, 38,"\\root\\icon\\lxjdq.ed");
			text0.SetRollText(TextListFilterExpireTable[NeedSave.Language]);
			Font.Handle();
//			sprintf(file_path,"\\root\\text\\%d\\lxjdq.ed", NeedSave.Language);
//			if(NeedSave.Language == LanguageOptions_Russian)
//			{
//				DecodeFilePlaneMode(72, 18,"\\root\\icon\\lxjdq.ed");
//				DecodeFilePlaneMode(0, 104, file_path);
//			}
//			else
//			{
//				DecodeFilePlaneMode(72, 38,"\\root\\icon\\lxjdq.ed");
//				DecodeFilePlaneMode(0, 130, file_path);
//			}
		}		
	}
	if(FilterServiceLife == FILTER_SERVICE_LIFE_REPLACE)
	{/*提醒更换滤芯(UI请更换滤芯)*/
		if(DrawTickCount >= 80)
		{
			if(ContinuousPictureIndex <= 181)
			{
				if(DrawTickCount >= 1080)
				{
					DrawTickCount = 1000;
					result++;	
					if(ContinuousPictureIndex == 1)
					{
						CLEAR_SCREEN();
					}
					sprintf(file_path,"\\root\\icon\\ghlx\\%d.ed", ContinuousPictureIndex);
					DecodeFilePlaneMode(20, 20, file_path);
					
					ContinuousPictureIndex += ContinuousPictureStep;	
				}
				else
				{
					if(DrawTickCount%80 == 0)
					{
						result++;
						ClearPartScreen(0, 130, 240, 240, 0);
						Font.Handle();
					}		
				}
			}
			else
			{
				if(DrawTickCount >= 2080)
					ReturnPrevPage();
			}			
		}
	}	
	else if(FilterServiceLife == FILTER_SERVICE_LIFE_EXPIRE)
	{/*滤芯将要过期请尽快更换 (UI滤芯将要到期提醒)*/
		if(DrawTickCount <= 3600)
		{
			if(DrawTickCount%1200 == 0)
			{//点亮
				result++;	
				if(NeedSave.Language == LanguageOptions_Russian)
				{
					DecodeFilePlaneMode(72, 18,"\\root\\icon\\lxjdq.ed");
				}
				else
				{
					DecodeFilePlaneMode(72, 38,"\\root\\icon\\lxjdq.ed");
				}
			}
			else if(DrawTickCount%1200 == 600)
			{//熄灭
				result++;	
				if(NeedSave.Language == LanguageOptions_Russian)
				{
					ClearPartScreen(72, 18, 168, 108, 0);
				}
				else
				{
					ClearPartScreen(72, 38, 168, 128, 0);
				}
			}
			if(DrawTickCount%80 == 0)
			{
				result++;
				ClearPartScreen(0, 130, 240, 240, 0);
				Font.Handle();
			}
		}
		else
		{
			if(DrawTickCount%80 == 0)
			{
				result++;
				ClearPartScreen(0, 130, 240, 240, 0);
				Font.Handle();
			}
			//ReturnPrevPage();
		}
	}
	
	return result;
}

int Draw::V2205DrawTestMode(void)
{
	int result = 0;
//	char file_path[64];
	if(TestModeFlag.bit.show)
	{
		TestModeFlag.bit.show = 0;
		result++;
		DecodeFont& Font = *font; 
		IDecodeText& text0 = Font.GetText(0);
		text0.sleep = false;
		switch(TestMode)
		{
			case TestMode_Versions:
			default:
				CLEAR_SCREEN();
				text0.SetRollText(0, 74, 240, SOFTWARE_VERSION_NUMBER, LanguageList[LanguageListIndex_BigBattery], -10, RollType_Order_Center, 0xFFFF, 0xFFFF);
				Font.Handle();
				break;
		}
		
	}

	return result;
}

//typedef int (*DrawExecuteFunction)(void);
//DrawExecuteFunction DrawExecuteFunctions[] = 
//{
//	electedMode,
//	
//};
//void V2205LedDrawExecuteDraw(void)
//{
//	if(DrawExecuteFunctions[NextState]())
//	{
//		Decode_RefreshScreen();
//	}
//}

void Draw::ExecuteDraw(void)
{
	int result = 0;
	switch(NextState)
	{
		case DrawShowState_PowerOn://开机画面
			result = DrawPowerOn();
			break;
		
		case DrawShowState_SelectedMode://模式选择界面
			result = DrawSelectedMode();
			break;
		
		case DrawShowState_DustLevel://灰尘等级界面
			result = DrawDustLevel();
			break;
		
		case DrawShowState_MainMenu://主菜单界面
			result = DrawMainMenu();
			break;
		
		case DrawShowState_History://历史数据界面
			result = DrawHistory();
			break;
		
		case DrawShowState_ResetFilter://重置滤芯界面
			result = DrawResetFilter();
			break;
		
		case DrawShowState_LanguageMenu://语言选择界面
			result = DrawLanguageMenu();
			break;
		
		case DrawShowState_Confirmation://确认语言选择界面
			result = DrawConfirmation();
			break;
	
		case DrawShowState_Recharge://充电界面
			result = DrawRecharge();
			break;
		
		case DrawShowState_HighAltitude://高海拔界面
			result = DrawHighAltitude();
			break;
		
		case DrawShowState_ShowError://故障界面
			result = DrawShowError();
			break;
		
		case DrawShowState_FilterServiceLife://滤芯寿命提示界面
			result = DrawFilterServiceLife();
			break;
		
		case DrawShowState_Lock://锁动画界面
			result = DrawLock();
			break;
		
		case DrawShowState_TestMode:
			result = V2205DrawTestMode();
			break;
		
		default:
			break;
	}
	
	if(result)
	{
		RefreshScreen();
	}
}

//模块句柄
//循环调用，推荐使用低优先级长期运行
//包含所有渲染语句
void Draw::Handle(void)
{
	ExecuteMessage();
	
	DelayCtrl();
	ExecuteDraw();

}
#if TEST_MODE_FUNCTION_ENABLE
void Draw::CleanScreenBuffer(void)
{
	CLEAR_SCREEN();
}

void Draw::RefreshToScreen(void)
{
	RefreshScreen();
}

void Draw::ResetTimer(void)
{
	DrawTickCount = 0;
}

unsigned int Draw::GetTimer(void)
{
	return DrawTickCount;
}
#endif/*TEST_MODE_FUNCTION_ENABLE*/

