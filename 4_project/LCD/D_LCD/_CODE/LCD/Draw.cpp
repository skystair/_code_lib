#include "Draw.h"
#include "StaticTextList.h"
#include "config.h"

Draw::Draw():Decode()
{
	CreatText();//�½����й����ı���1
	CreatText();//�½����й����ı���2
	CreatText();//�½����й����ı���3
	CreatText();//�½����й����ı���4
	
	FlagContainers.bit.StartExecute = 0;
	FlagContainers.bit.RefreshFlag = 0;
	
	LOAD_NEED_SAVE();//��flash ��ȡ�洢������

	if(INIT_TIMESTAMP() || NeedSave.CheckFlag != VALID_FLASH_DATA_FLAG)
	{//��鵽flash�����ݻ򱸷����������ʼ���洢����
		NeedSave.CheckFlag = VALID_FLASH_DATA_FLAG;//����У���־
		FlagContainers.bit.NeedStore = 1;//�����Ҫ�洢Flash����
		for(int i=0; i<7; i++)
			NeedSave.History[i] = 0;//��ʼ����ʷ����
		NeedSave.HistoryTimestamp = GET_TIMESTAMP();
		NeedSave.Language = LanguageOptions_SimplifiedChinese;//Ĭ������
	}
}

void Draw::Init(void)
{
	DrawTickCount = 0;//��ʼ����ʾģ����������
	FlagContainers.All = 0;//��ʼ����־λ
	
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
	
//	lastBatteryLevel = 0xFF;
		

}

void Draw::ReloadPage(void)
{
	SetNextPage(NextState);
}

//����ģ������
//��Ҫ���̶����ڵ���
//nms��ÿn�������һ��
void Draw::Tick(unsigned int nms)
{
	DrawTickCount += nms;
	CtrlTickCount += nms;
	
	ReflashCount += nms;
}

//���±���
//ÿ���±��ĵ���һ��
//message����������ָ��
void Draw::Refresh(unsigned char* message)
{
	if(!FlagContainers.bit.StartExecute)
	{//δ�ڴ�����ʱ��������±���
		u8* reserveOpint = (u8*)&uMessage;
		for(int i=0; i<sizeof(UartMessage_V1_17); i++)
			reserveOpint[i] = message[i];
	}
	//���������Ҫ����λ�õ����� ���������
	
	//����������ȫ������Ϻ��ٽ��б�ǣ���ֹ��ǰ����������������
	FlagContainers.bit.RefreshFlag = 1;
}

/***********************************************************************************/

void Draw::SetNextPage(DrawMainShowState next)
{
	if(next == NextState)
	{//��ֹ�ظ�����
		return;
	}
	RecordRunningTime(next);
	SleepAll();
	switch(next)
	{
		case DrawShowState_PowerOn://��������	
			ContinuousPictureIndex = 1;
			ContinuousPictureStep = 2;
//			lastBatteryLevel = 0xFF;	
			break;
		
		case DrawShowState_SelectedMode://ģʽѡ�����
//			lastBatteryLevel = 0xFF;	
			FlagContainers.bit.Playing  = 0;
			FlagContainers.bit.StrongPlaying = 0;
			if(NextState != DrawShowState_DustLevel)
			{//�ӷǻҳ��ȼ�ҳ���л���ģʽѡ��ҳ�� ͼ���ȫ����ʼ��ʾ	
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
		
		case DrawShowState_DustLevel://�ҳ��ȼ�����	
			FlagContainers.bit.Playing  = 0;
			FlagContainers.bit.StrongPlaying = 0;
//			lastBatteryLevel = 0xFF;	
			if(NextState != DrawShowState_SelectedMode)
			{//��ģʽѡְ��ҳ���л����ҳ��ȼ�ҳ�� ͼ���ȫ����ʼ��ʾ
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
		
		case DrawShowState_MainMenu://���˵�����	
//			lastBatteryLevel = 0xFF;	
			MainMenuFlag.all = 0xFF;
			break;
		
		case DrawShowState_History://��ʷ���ݽ���
//			lastBatteryLevel = 0xFF;	
			HistoryFlag.all = 0xFF;
			break;
		
		case DrawShowState_ResetFilter://������о����
//			lastBatteryLevel = 0xFF;	
			ResetFilterFlag.all = 0xFF;
			break;
		
		case DrawShowState_LanguageMenu://����ѡ�����
//			lastBatteryLevel = 0xFF;	
			LanguageMenuFlag.all = 0xFF;
			NewLanguage = NeedSave.Language;//����ѡ���������ڵ����Կ�ʼ
			break;
		
		case DrawShowState_Confirmation://ȷ������ѡ�����
//			lastBatteryLevel = 0xFF;	
			ConfirmationFlag.all = 0xFF;
			break;
	
		case DrawShowState_Recharge://������
			FlagContainers.bit.Playing  = 0;
			FlagContainers.bit.StrongPlaying = 0;
			ContinuousPictureIndex = 1;
			ContinuousPictureStep = 2;
			RechargeFlag.all = 0xFF;
			break;
		
		case DrawShowState_Lock://����������
//			lastBatteryLevel = 0xFF;	
			if(NextState == DrawShowState_ShowError)
			{
				NextState = PrevState;
			}
			LockFlag.all = 0xFF;
			break;
		
		case DrawShowState_ShowError://���Ͻ���
//			lastBatteryLevel = 0xFF;	
			ShowErrorFlag.all = 0xFF;
			if(ErrorData)
			{
				SetPlayingDelay(DELAY_PLAY_ERROR);
			}
			else
			{/*��ʾ�����͹���*/
				SetPlayingDelay(DELAY_PLAY_LOW_BATTERY);
				if(PrevState == DrawShowState_Recharge)
				{/*ǰһ��״̬�ǳ��״̬*/
					PrevState = DrawShowState_SelectedMode;
				}
			}
			break;
		
		case DrawShowState_HighAltitude://�ߺ��ν���
//			lastBatteryLevel = 0xFF;	
			HighAltitudeFlag.all = 0xFF;
			break;
		
		case DrawShowState_FilterServiceLife://��о������ʾ����
//			lastBatteryLevel = 0xFF;	
			FilterServiceLifeFlag.all = 0xFF;
			if(FilterServiceLife == FILTER_SERVICE_LIFE_REPLACE)
			{//��о����-��ʾ�󲥷Ŷ���
				SetPlayingDelay(DELAY_PLAY_FILTER_REPLACE);
			}
			else
			{//��о������
				SetPlayingDelay(DELAY_PLAY_FILTER_EXPIRE);
			}
			break;
		
		case DrawShowState_CentralDustCollection:
//			lastBatteryLevel = 0xFF;	
			CDCFlag.all =0xFF; 
			ContinuousPictureIndex = 1;
			ContinuousPictureStep = 2;
			break;
		
		case DrawShowState_TestMode:
//			lastBatteryLevel = 0xFF;
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
	if((PrevState == DrawShowState_SelectedMode || PrevState == DrawShowState_DustLevel || PrevState == DrawShowState_PowerOn)/*ǰһ��ҳ����ģʽѡ��*/
		&& WorkStatePrve == WorkState_Work)/*ǰһ������ģʽ�Ƿŵ�*/
	{//���¿�ʼ�ŵ����	
		PrevState = SetStateDischarge();
	}
	else// if(PrevState == DrawShowState_Recharge || PrevState == DrawShowState_PowerOn || PrevState == DrawShowState_ShowError)//ǰһ��ҳ���ǳ��򿪻�ҳ��
	{
		PrevState = DrawShowState_SelectedMode;
	}
	SetNextPage(PrevState);
	PrevState = NextState;//�����ظ�����
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

void Draw::RecordRunningTime(DrawMainShowState workState)
{
	MotorState_en state;
	if(workState == DrawShowState_DustLevel)
		state = MotorState_Running;
	else
		state = MotorState_Stop;
	if(MotorState != state)
	{
		if(state == MotorState_Running)
		{//�����ʼ����
			CurrentTimestamp = GET_TIMESTAMP();
		}
		else
		{//���ֹͣ
			FlagContainers.bit.NeedStore = 1;//���ݸ��� ���Ϊ��Ҫ�洢
			//��λ��ʷ��¼ ��������ʷ��¼ʱ������бȽ� ������ʷ��¼
			unsigned int timestamp = GET_TIMESTAMP();
			unsigned start = 0;
			int history = timestamp - NeedSave.HistoryTimestamp;//������ʷʱ�䵽���ڵ�����
			history = history / (60*60*24);//������ʷʱ�䵽���ڵ�����
			if(history > 0)
			{//��Ҫ�����ʷ��¼��ʼ���������¼
				while(NeedSave.History[start] <= 0.01f)//1��=0.0167��
				{//��ֹ��0��¼��ͷ
					if(++start >= history || start >= 7)
					{//��ֹ���
						break;
					}
				}
			}
			if(start > 0)
			{//����Ҫ��ǰ����
				if(start < 7)	
					for(int i=start; i<7; i++)
					{//��ǰ�ƶ�start
						NeedSave.History[i-start] = NeedSave.History[i];
						NeedSave.History[i] = 0;
					}
				else
					for(int i=0; i<7; i++)
					{//�����ʷ��¼
						NeedSave.History[i] = 0;
					}
			}
			history -= start;//startС�ڵ���history��history�������С���ܵ���0
			if(history >= 7)
			{//��ǰ��������ʷʱ���������7��
				int roll = history - 6;//������Ҫ��ǰ����������	
				if(roll < 7)
				{//��ǰ������ΧС��7
					while(NeedSave.History[roll] <= 0.01f)//1��=0.0167��
					{//�������ֹ��0��¼��ͷ
						if(++roll >= 7)
						{//��ֹ���
							break;
						}
					}
					for(int i=roll; i<7; i++)
					{//��ǰ�ƶ�roll
						NeedSave.History[i-roll] = NeedSave.History[i];
						NeedSave.History[i] = 0;
					}
					NeedSave.HistoryTimestamp += (60*60*24)*roll;//ʱ�������ƶ�
				}
				else
				{//��ǰ������Χ���ڵ���7�������ʷ��¼���¿�ʼ��¼	
					roll = history;
					for(int i=0; i<7; i++)
					{//�����ʷ��¼
						NeedSave.History[i] = 0;
					}
					NeedSave.HistoryTimestamp = timestamp;			
				}
				history -= roll;
			}
			int total = timestamp - CurrentTimestamp;//���㱾����������ʱ��	
			NeedSave.History[history] += total/60.0f;//������ʷ����ʱ��
		}
		MotorState = state;
	}
}

//���ڷŵ�״̬ ������ҳ���л���ģʽѡ��ҳ�� 3�����ʾ�ҳ��ȼ�ҳ��
DrawMainShowState Draw::SetStateDischarge(void)
{
	DrawMainShowState state = DrawShowState_SelectedMode;
	if((NextState != DrawShowState_SelectedMode && NextState != DrawShowState_DustLevel)
		|| (WorkStatePrve != WorkState_Work))
	{//����ģʽѡ��ͻҳ��ȼ�ҳ��
		state = DrawShowState_SelectedMode;//�����л����ҳ��ȼ�ҳ��
		SetShowDustDelay(DELAY_CHANGE_TO_RUN_MS);
		//ShowDustDelay = DelayFlag_Start;//��ʼ��ʱ��־		
	}
	if(ShowDustDelay == DelayFlag_Finish)//3����ʱ //��ʱ��ɱ�־
	{
		state = DrawShowState_DustLevel;
	}
	return state;
}

void Draw::SetBatteryLevel(unsigned char level)
{

	if(level == batteryLevel)
	{//��ֹ�ظ�����
		return;
	}
	if(level > 100)
	{
		FlagContainers.bit.DirtyDta = 1;//������Χ�ĵ������� ���Ϊ������
		level = 100;
	}
	batteryLevel = level;//��¼����ֵ
	SelectedModeFlag.bit.battery = 1;//��λģʽѡ����������־
	DustLevelFlag.bit.battery = 1;//��λ�ҳ��ȼ����������־
	RechargeFlag.bit.battery = 1;//��λ�����������־
}

V2205Bool Draw::LowBatteryCheck(unsigned char level)
{
	if(level <= 0&&(!uMessage.errorData))
	{//�����Ѻľ�
		//if(LowBatteryWarning != LowBatteryWarning_Out)
		{
			ShowErrorFlag.all = 0xFF;
			LowBatteryWarning = LowBatteryWarning_Out;
			//ErrorShowDelay = DelayFlag_Start;
			//FlagContainers.bit.StartStrongPlaying = 1;	
			//PlayingDelay = DelayFlag_Start;
			return V2205Bool_TRUE;
		}
//		else if(ErrorShowDelay != DelayFlag_Finish)
//		{//����ʱ��δ����
//			return V2205Bool_TRUE;
//		}
	}
	else if((uMessage.remainingSecond == 0xEF || level <= 10 )&&(!uMessage.errorData))//�й��ϴ����򲻴���������
	{//������
		if(!FlagContainers.bit.LowBattery)//δ����������
		{
			if(FlagContainers.bit.LowBatteryPage)//���ڱ�����һ�ο����в��Ŷ�ε����Ͷ���
			{
				FlagContainers.bit.LowBattery = 1;
				return V2205Bool_FALSE;
			}
			else
			{
				LowBatteryWarning = LowBatteryWarning_Low;
				ShowErrorFlag.all = 0xFF;
		//		FlagContainers.bit.StartStrongPlaying = 1;
				FlagContainers.bit.StartPlaying = 1;
				ShowErrorFlag.bit.show = 1;
		//		PlayingDelay = DelayFlag_Start;
				return V2205Bool_TRUE;
			}	
		}	
//		else if(ErrorShowDelay != DelayFlag_Finish)
//		{//����ʱ��δ����
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
	{//��ֹ�ظ�����
		return 0;//δ�仯
	}
	if(shift > V2205ShiftInfo_Auto || shift == 0)
	{//������Χ�����Ϊ������
		FlagContainers.bit.DirtyDta = 1;
		shift = V2205ShiftInfo_Low;
		//return 0;//δ�仯
	}
	NewShift = shift;
	DustLevelFlag.bit.shift = 1;	
	SelectedModeFlag.bit.Mode = 1;
	return 1;//�б仯
}

void Draw::SetDustLevel(char shift)
{	
	if(uMessage.workState == WorkState_Work)
	{//������״̬��Ҫ�ҳ��ȼ� ���жϻҳ��ȼ�
		if(shift <= V2205DustLevel_None || shift >= V2205DustLevel_Max)
		{
			FlagContainers.bit.DirtyDta = 1;
			DustLevel = V2205DustLevel_Low;//�ṩĬ��ֵ
			return;
		}
		DustLevel = shift;
	}
//	if(shift)//��Ļ�ҳ��ȼ��޵�״̬
//	{
//		//CurveDrawSetLevel(shift);//ģ���ڴ��ظ����� ����Ҫ���⴦��
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
	{//��ֹ�ظ�����
		return;
	}
	if(menu >= RollMenu_None)
	{
		FlagContainers.bit.DirtyDta = 1;
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
	{//��ֹ�ظ�����
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
	{//��ֹ�ظ�����
		return V2205Bool_FALSE;
	}
	LockState = state;
	LockFlag.bit.show = 1;
	SelectedModeFlag.bit.lock = 1;
	DustLevelFlag.bit.lock = 1;
	return V2205Bool_TRUE;
}

//�ж��Ƿ񲥷�������о
DrawMainShowState Draw::CheckFilterReset(DrawMainShowState state)
{
	if(uMessage.filterReset > FILTER_RESET_RESET)
	{
		FlagContainers.bit.DirtyDta = 1;
		return state;
	}
	if(uMessage.filterReset)
	{//��ʼ����������о����	
		state = DrawShowState_ResetFilter;//������о
		if(uMessage.filterReset&FILTER_RESET_SETING)
		{//����������о�������һ֡
			FlagContainers.bit.ResetFilter = 1;
		}
		else
		{
			FlagContainers.bit.ResetFilter = 0;
		}
	}
	return state;
}

//�ж��Ƿ��������ѡ��
DrawMainShowState Draw::CheckLanguageSetting(DrawMainShowState state)
{
	int confirm = 0;
	if(uMessage.languageSetting)
	{//��ʾ����ѡ��
		if(uMessage.confirm)
		{//����ȷ������ѡ��
			FlagContainers.bit.comfirmLangeuage = 1;
			state = DrawShowState_Confirmation;//ȷ�����Զ���
			confirm = 1;
		}
		else
		{
			FlagContainers.bit.comfirmLangeuage = 0;
		}
		if(uMessage.languageConfirmation)
		{//ȷ������ѡ��
			state = DrawShowState_Confirmation;//ȷ�����Զ���
			confirm = 1;
		}
		if(!confirm)
		{//���Բ˵���ҳ
			state = DrawShowState_LanguageMenu;//����ѡ��˵�
			SetLanguageSelected(uMessage.select);//����ʾ���Բ˵�ʱ�������Բ˵�������Ϣ
		}
	}
	return state;
}

//����Ƿ���Ҫ��ʾ��ʷ��¼
DrawMainShowState Draw::CheckCleaningRecord(DrawMainShowState state)
{
	if(uMessage.cleaningRecord)
	{//��ʾ��ʷ��¼
		state = DrawShowState_History;//��ʷ����
	}
	return state;
}

//����Ƿ���Ҫ��ʾ���˵�
DrawMainShowState Draw::CheckMainMenu(DrawMainShowState state)
{
	if(uMessage.mainMenu)
	{//��ʾ���˵�
		if(NextState == DrawShowState_ShowError 
			&& LowBatteryWarning == LowBatteryWarning_Low
			&& ErrorData == ErrorData_None)
		{
			FlagContainers.bit.Playing = 0;
			FlagContainers.bit.StrongPlaying = 0;
			FlagContainers.bit.StartPlaying = 0;
			FlagContainers.bit.StartStrongPlaying = 0;
		}
		state = DrawShowState_MainMenu;//���˵�
		SetMainEnum((RollMenu_en)uMessage.rollMenu);//����ʾ���˵�ʱ�������˵�������Ϣ
	}
	return state;
}

//����Ƿ���ʾ���ϻ��������
DrawMainShowState Draw::CheckErrorData(DrawMainShowState state)
{
	ErrorData_en current = (ErrorData_en)uMessage.errorData;
	switch(uMessage.errorData)
	{
		//ǿ����˸����
		case ErrorData_DischargeOvertemperatureProtection://�ŵ���±�����UI��ع��£�  (�������ŵ����)
//			if(ErrorData != uMessage.errorData)
//			{
//				state = DrawShowState_ShowError;//����ҳ��
//				PlayingDelay = DelayFlag_Start;
//				FlagContainers.bit.StartStrongPlaying = 1;		
//				ShowErrorFlag.all = 0xFF;
//			}
//			state = DrawShowState_ShowError;//����ҳ��
//			break;
			
		//��˸����ǿ�ƴ���
		case ErrorData_TuyereBlocked://ȫ�·�ڣ�UI���������
		case ErrorData_RollerStall://��ˢ��ת��UI�������ˢ��
		case ErrorData_RollerShortOut://��ˢ��·��UI�������ˢ��
//		case ErrorData_FilterNotInstalled://��оδ��װ��UI��
			if(ErrorData != uMessage.errorData)
			{
				state = DrawShowState_ShowError;//����ҳ��
		//		PlayingDelay = DelayFlag_Start;
				FlagContainers.bit.StartPlaying = 1;		
				ShowErrorFlag.all = 0xFF;
			}
			state = DrawShowState_ShowError;//����ҳ��
			break;
			
		//��̬��ʾ����
		case ErrorData_BldcUndervoltage://BLDCǷѹ��UI�������1��--¼�ڹ��ϼ�¼��
		case ErrorData_BldcCvervoltage://BLDC��ѹ��UI�������1��--¼�ڹ��ϼ�¼��
		case ErrorData_BldcOverTemperature://BLDC���£�UI�������1��--¼�ڹ��ϼ�¼��
		case ErrorData_BldcOvercurrent://BLDC������UI�������1��--¼�ڹ��ϼ�¼��
		case ErrorData_BldcOverspeed://BLDC���٣�UI�������1��--¼�ڹ��ϼ�¼��
		case ErrorData_BldcOpenPhase://BLDCȱ�ࣨUI�������1��--¼�ڹ��ϼ�¼��
		case ErrorData_DischargeNoLoadProtection://�ŵ���ر�����UI�������2��
		case ErrorData_CommunicationTimeout://ͨѶ��ʱ�����ܷ�����ȥ����UI�������3��--¼�ڹ��ϼ�¼��
		case ErrorData_ChargerVoltageAbnormal://�������ѹ�쳣��UI�������4�� 
		case ErrorData_ChargerOvercurrent://��������UI�������5��
		case ErrorData_ChargerTimeout://��糬ʱ��UI�������6��
		case ErrorData_BatteriesFault://��о���ϣ�UI�������7��--¼�ڹ��ϼ�¼��
		case ErrorData_NTCFault://�¶ȴ�����(NTC)���ϣ�UI�������8��--¼�ڹ��ϼ�¼��
		case ErrorData_BMSHardwareFault://ǰ��ͨѶʧ��(BMSӲ���쳣)��UI�������9��--¼�ڹ��ϼ�¼��	
			if(ErrorData != uMessage.errorData)
			{
				ShowErrorFlag.all = 0xFF;
			}
			state = DrawShowState_ShowError;//����ҳ��
			break;
		
		//����ʾ����
		case ErrorData_Reserve://�ŵ����/��·/ /BLDC�ض�ʧ�ܱ�������Ļ�޷���ʾ
		case ErrorData_OverchargeProtection://���䱣��
		case ErrorData_OverDischargeProtection://���ű���	
		case ErrorData_None://�޹���
			if(FlagContainers.bit.StrongPlaying && NextState == DrawShowState_ShowError)
			{//δ���ǿ�ƹ��ϲ��ŵļ�������
				state = DrawShowState_ShowError;
				current = ErrorData;//ά��ԭ�й���״̬
			}
			else
			{
				current = ErrorData_None;
				if(FlagContainers.bit.Playing && NextState == DrawShowState_ShowError && LowBatteryWarning != LowBatteryWarning_Low)
				{
					FlagContainers.bit.Playing = 0;
				}
				//V2205Draw.ErrorData = ErrorData_None;
			}
			break;
		
		default:
			FlagContainers.bit.DirtyDta = 1;
			break;
	}
	
	ErrorData = current;
	return state;
}

DrawMainShowState Draw::CheckFilterServiceLife(DrawMainShowState state)
{
	if(uMessage.filterServiceLife != FILTER_SERVICE_LIFE_NORMAL)
	{//��о������ʾ����
		if(uMessage.filterServiceLife == FILTER_SERVICE_LIFE_RINSE)//������ϴ��о(UI��������о) ��ʹ��	
		{
			return state;
		}
		else if(uMessage.filterServiceLife > FILTER_SERVICE_LIFE_EXPIRE)//������Χ��ֵ
		{
			FlagContainers.bit.DirtyDta = 1;
			return state;
		}
		else if(FilterServiceLife != uMessage.filterServiceLife)
		{
			FilterServiceLifeFlag.bit.show = 1;
			FlagContainers.bit.StartPlaying = 1;	
		}
		state = DrawShowState_FilterServiceLife;//��о������ʾ
		FilterServiceLife = uMessage.filterServiceLife;//��¼��Ҫ��ʾ����о��ʾ��Ϣ
	}
	if(!FlagContainers.bit.Playing)
	{
		FilterServiceLife = uMessage.filterServiceLife;//��¼��Ҫ��ʾ����о��ʾ��Ϣ
	}
	return state;
}

DrawMainShowState Draw::CheckHighAltitudeMode(DrawMainShowState state)
{
	if(uMessage.highAltitudeMode != HIGH_ALTITUDE_MODE_NONE)
	{
		if(uMessage.highAltitudeMode == HIGH_ALTITUDE_MODE_ENTERING || uMessage.highAltitudeMode == HIGH_ALTITUDE_MODE_ENTERED)
		{
			if(HighAltitudeMode == HIGH_ALTITUDE_MODE_EXITING || HighAltitudeMode == HIGH_ALTITUDE_MODE_EXITED)
			{//ֱ�Ӵ��˳��л������룬����ҳ��
				HighAltitudeFlag.bit.show = 1;
			}
		}
		else if(uMessage.highAltitudeMode == HIGH_ALTITUDE_MODE_EXITING || uMessage.highAltitudeMode == HIGH_ALTITUDE_MODE_EXITED)
		{
			if(HighAltitudeMode == HIGH_ALTITUDE_MODE_ENTERING || HighAltitudeMode == HIGH_ALTITUDE_MODE_ENTERED)
			{	//ֱ�Ӵӽ����л����˳�������ҳ��
				HighAltitudeFlag.bit.show = 1;
			}
		}
		else
		{
			FlagContainers.bit.DirtyDta = 1;
			return state;
		}
		HighAltitudeMode = uMessage.highAltitudeMode;
		state = DrawShowState_HighAltitude;
	}
	return state;
}

DrawMainShowState Draw::CheckLock(DrawMainShowState state)
{
	if((SetLockState((V2205Bool)uMessage.lock) && uMessage.lockAction)
		|| FlagContainers.bit.Locking)
	{//����״̬�����仯
		state = DrawShowState_Lock;//�����л���������ҳ��
		FlagContainers.bit.Playing = 0;//�����ϵ����ȼ�����
		FlagContainers.bit.Locking = 1;
	}
	return state;
}

DrawMainShowState Draw::CheckWorkMode(DrawMainShowState state)
{
	WorkState = uMessage.workState;
	switch(WorkState)
	{
		case WorkState_Charging://���״̬
			state = DrawShowState_Recharge;
			FlagContainers.bit.PowerOn = 1;//���״̬������������
			LowBatteryWarning = LowBatteryWarning_None;//�л��������������ͱ�־
			FlagContainers.bit.LowBattery = 0;//�л��������������ͱ�־
			FlagContainers.bit.LowBatteryPage = 0;//�ӳ��ҳ�淵�غ�����������ʾһ�ε���������
			FlagContainers.bit.Playing = 0;//���ҳ��ǿ���л� ����������ҳ��
			FlagContainers.bit.StrongPlaying = 0;//���ҳ��ǿ���л� ����������ҳ��
			ShowDustDelay = DelayFlag_Finish;//����ֹͣ�л�������ģʽ��ʱ
			PlayingDelay = DelayFlag_Finish;//����ֹͣ�������ż�ʱ
			break;
		
		case WorkState_Work://�ŵ�״̬						
			//3�����ʾ�ҳ��ȼ�����			
			if(!FlagContainers.bit.PowerOn)
			{
				state = DrawShowState_PowerOn;
				break;
			}		
			if(LowBatteryCheck(uMessage.batteryLevel))//�����ͼ��---���ŵ�״̬���
			{
				state = DrawShowState_ShowError;//���������ϵ�����ҳ��
			}
			else
			{
				state = SetStateDischarge();
			}
			break;
		
		case WorkState_CDC:
//			if(!FlagContainers.bit.PowerOn)
//			{
//				state = DrawShowState_PowerOn;
//				break;
//			}	
//			if(LowBatteryCheck(uMessage.batteryLevel))//�����ͼ��---���ŵ�״̬���
//			{
//				state = DrawShowState_ShowError;//���������ϵ�����ҳ��
//			}
//			else
//			{
//				state = DrawShowState_CentralDustCollection;//��ʾ���뼯��ҳ��
//			}
			
			
			state = DrawShowState_CentralDustCollection;
			FlagContainers.bit.PowerOn = 1;//���״̬������������
			LowBatteryWarning = LowBatteryWarning_None;//�л��������������ͱ�־
			FlagContainers.bit.LowBattery = 0;//�л��������������ͱ�־
			FlagContainers.bit.LowBatteryPage = 0;//�ӳ��ҳ�淵�غ�����������ʾһ�ε���������
			FlagContainers.bit.Playing = 0;//���ҳ��ǿ���л� ����������ҳ��
			FlagContainers.bit.StrongPlaying = 0;//���ҳ��ǿ���л� ����������ҳ��
			ShowDustDelay = DelayFlag_Finish;//����ֹͣ�л�������ģʽ��ʱ
			PlayingDelay = DelayFlag_Finish;//����ֹͣ�������ż�ʱ
			break;
			
		case WorkState_Standby://����״̬����Ļ���������ת����Ϊ������
			if(!FlagContainers.bit.PowerOn)
			{
				state = DrawShowState_PowerOn;
				break;
			}
			if(LowBatteryCheck(uMessage.batteryLevel))//�����ͼ��---���ŵ�״̬���
			{
				state = DrawShowState_ShowError;//���������ϵ�����ҳ��
			}
			else
			{
				state = DrawShowState_SelectedMode;//��ʾģʽѡ��ҳ�� �����Զ��л�
			}	
			break;
			
			default:		
				if(!FlagContainers.bit.PowerOn)
				{//����ʹ��ģʽ�����ݿ���
					state = DrawShowState_PowerOn;
					break;
				}
				FlagContainers.bit.DirtyDta = 1;//δ����ģʽ ���Ϊ������
				break;
	}
	WorkStatePrve = WorkState;
	return state;
}

//ִ�б���
void Draw::ExecuteMessage(void)
{
	DrawMainShowState state = NextState;//Ĭ��Ϊ���л�ҳ��
	if(!FlagContainers.bit.RefreshFlag)
	{//û���յ��µı��ģ��˳���������
		return;
	}
	FlagContainers.bit.StartExecute = 1;//��ʼ���� ���ñ�־��ֹ�����б������ݷ�������
	FlagContainers.bit.RefreshFlag = 0;//������ĸ��±�־
	
	SetBatteryLevel(uMessage.batteryLevel);	//���µ���
	SetDustLevel(uMessage.dustLevel);		//���»ҳ��ȼ�
	int shiftChange = SetShift((V2205ShiftInfo)uMessage.shift);//���µ�λ��Ϣ

	//���ܳ��ִ�����
	if(shiftChange////��λ�����仯
		|| WorkState != uMessage.workState)//ģʽ�����仯
	{
		FlagContainers.bit.Locking = 0;
		FlagContainers.bit.Playing = 0;
	}

	//����Ƿ���Ҫ�������״̬����ʾ�汾�ţ�
	if(uMessage.workState == WorkState_Test)
	{
		state = DrawShowState_TestMode;
		FlagContainers.bit.Playing = 0;
		FlagContainers.bit.StrongPlaying = 0;
		FlagContainers.bit.DirtyDta = 0;//����ģʽ����¼������
		
		TestMode = (TestMode_en)uMessage.remainingMinute;
		
		goto EndExecuteMessage;
	}
	
	state = CheckWorkMode(state);//��鹤��ģʽ
	if(!FlagContainers.bit.PowerOn)
	{
		if(FlagContainers.bit.DirtyDta)
		{
			FlagContainers.bit.DirtyDta = 0;//����ʹ�������ݿ���
			DustLevel = V2205DustLevel_Low;
			NewShift = V2205ShiftInfo_Low;
		}
		goto EndExecuteMessage;
	}
	if(FlagContainers.bit.InitLowBattery)
	{
		FlagContainers.bit.InitLowBattery = 0;
		goto EndExecuteMessage;
	}
	if(LowBatteryWarning == LowBatteryWarning_Out)
	{//���������ȼ��ȵ����ľ�����
		state = CheckErrorData(state);//������״̬
		FlagContainers.bit.Playing = 0;
		FlagContainers.bit.StrongPlaying = 0;
		goto EndExecuteMessage;//�����ľ���ֻ��ʾ�����ľ�
	}
	
	state = CheckLock(state);//�����״̬
	state = CheckFilterServiceLife(state);//�����о����
	state = CheckMainMenu(state);	//������˵�״̬
	state = CheckLanguageSetting(state);//������Բ˵�״̬
	state = CheckCleaningRecord(state);//�����ʷ��¼��ʾ״̬
	state = CheckFilterReset(state);//�����о������ʾ״̬
	state = CheckHighAltitudeMode(state);//���ߺ�����ʾ״̬
	state = CheckErrorData(state);//������״̬
	
//	RecordRunningTime(uMessage.workState);//��¼����ʱ��
	
//	goto EndExecuteMessage;
//	/* �������Ľ�����Ĺ̶����� */
EndExecuteMessage:

	if(FlagContainers.bit.ChangeLangeuage)
	{
		FlagContainers.bit.ChangeLangeuage = 0;
		FlagContainers.bit.NeedStore = 1;
		NeedSave.Language = NewLanguage;//������������ѡ��Ϊ��ǰ����
//		SAVE_NEED_SAVE(); //�޸����Ժ���������һ�δ洢
	}
	if(FlagContainers.bit.DirtyDta)
	{//��ֹ�������л�ҳ��
		FlagContainers.bit.DirtyDta = 0;		
	}
	
	if(NextState == DrawShowState_SelectedMode
		|| NextState == DrawShowState_DustLevel
		|| NextState == DrawShowState_MainMenu
		|| NextState == DrawShowState_Recharge)
	{
		FlagContainers.bit.Playing = 0;
		FlagContainers.bit.StrongPlaying = 0;
	}
	
	if((FlagContainers.bit.Playing | FlagContainers.bit.StrongPlaying) == 0)//�����в������л�ҳ��
	{
		FlagContainers.bit.Playing = FlagContainers.bit.StartPlaying;
		FlagContainers.bit.StrongPlaying = FlagContainers.bit.StartStrongPlaying;
		FlagContainers.bit.StartPlaying = 0;
		FlagContainers.bit.StartStrongPlaying = 0;
		SetNextPage(state);//�ѿ���״̬�����л�����ҳ��
	}
	
	if(state != DrawShowState_DustLevel)
	{
		V2205Draw_LED_RED_OFF;
		V2205Draw_LED_GREEN_OFF;
	}
	
	//��Ļ���� ������ȼ� �����仯
	if(uMessage.screenLuminance != SCREEN_LUMINANCE_NORMAL)
	{//�䰵
		DARK_SCREEN();
		if(FlagContainers.bit.NeedStore)
		{//��Ļ�䰵ʱ�������Ҫ�洢���ļ� ��������һ�δ洢
			FlagContainers.bit.NeedStore = 0;
			SAVE_NEED_SAVE();
		}
	}
	
	FlagContainers.bit.StartExecute = 0;//���Ľ������� ������ڽ�����־
}

/********************************************************************************************/
void Draw::SetShowDustDelay(unsigned int limit)
{
	ShowDustDelay = DelayFlag_Count;
	ShowDustDelay_Timestamp = CtrlTickCount;
	ShowDustDelay_Limit = limit;
}

void Draw::SetPlayingDelay(unsigned int limit)
{
	PlayingDelay = DelayFlag_Count;
	PlayingDelay_Timestamp = CtrlTickCount;	
	PlayingDelay_Limit = limit;
}

void Draw::DelayCtrl(void)
{
	if(ShowDustDelay != DelayFlag_Stop && ShowDustDelay != DelayFlag_Finish)
	{
//		if(ShowDustDelay == DelayFlag_Start)
//		{
//			CtrlTickCount	 = 0;
//			ShowDustDelay = DelayFlag_Count;
//		}
		//if(CtrlTickCount > 3000)//3000
		//if(CtrlTickCount - ShowDustDelay_Timestamp >= ShowDustDelay_Limit)
		{
			ShowDustDelay = DelayFlag_Finish;
			if(WorkState == WorkState_Work && NextState == DrawShowState_SelectedMode)// && FlagContainers.bit.PowerOn
				SetNextPage(DrawShowState_DustLevel);//��ʱ����������жϵ�ǰ�Ƿ�������״̬��������л�������״̬�����л����ҳ��ȼ�ҳ��
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
//		if(PlayingDelay == DelayFlag_Start)
//		{
//			CtrlTickCount	 = 0;
//			PlayingDelay = DelayFlag_Count;
//		}
		if(CtrlTickCount - PlayingDelay_Timestamp >= PlayingDelay_Limit)
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
	{//ģʽͼ�궯������
		DrawTickCount = 0;
		result++;
		sprintf(file_path,"\\root\\icon\\poweron\\%d.ed", ContinuousPictureIndex);
		RegisterPicture(0, 0, file_path);//����ͼƬ	
		ContinuousPictureIndex += ContinuousPictureStep;
//		ɾ֡����
//		if((ContinuousPictureIndex >= 33 && ContinuousPictureIndex<=34)
//			|| (ContinuousPictureIndex >= 27 && ContinuousPictureIndex<=28))
//		{
//			ContinuousPictureIndex += ContinuousPictureStep;
//		}
		if(ContinuousPictureIndex > 30)
		{//���ŵ����һ֡

			FlagContainers.bit.PowerOn = 1;//���Ϊ�ѿ���
			if(LowBatteryCheck(batteryLevel))//�����ͼ��---���ŵ�״̬���
			{
				FlagContainers.bit.Playing = 1;
				FlagContainers.bit.StrongPlaying = 0;
				FlagContainers.bit.StartPlaying = 0;
				FlagContainers.bit.StartStrongPlaying = 0;
				SetNextPage(CheckErrorData(DrawShowState_ShowError));
				FlagContainers.bit.RefreshFlag = 1;
				FlagContainers.bit.InitLowBattery = 1;
			}
			else
			{
				if(WorkState == WorkState_Work)
				{//�ŵ�״̬
					SetNextPage(CheckErrorData(SetStateDischarge()));
//					RecordRunningTime(uMessage.workState);//��¼����ʱ��		
				}
				else
				{//����״̬
					SetNextPage(CheckErrorData(DrawShowState_SelectedMode));
				}	
			}		
		}
//		if(ContinuousPictureStep > 0)
//		{
//			if(ContinuousPictureIndex > 37)
//			{//���ŵ����һ֡
//				ContinuousPictureStep = -1;
//			}
//		}
//		else
//		{
//			if(ContinuousPictureIndex <= 32)
//			{//���򲥷ŵ���Ҷ�ʼһ֡
//				if(ContinuousPictureIndex > 1)
//				{//ѡ��ȫ�ڵ�һ֡
//					ContinuousPictureIndex = 1;
//				}
//				else
//				{//ˢ�¹�ȫ�ڵ�һ֡���˳�
//					FlagContainers.bit.PowerOn = 1;//���Ϊ�ѿ���
//					if(WorkState == WorkState_Work)
//					{//�ŵ�״̬	
//						SetNextPage(SetStateDischarge());
//					}
//					else
//					{//����״̬
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
		{//������Ϩ��״̬���������λ
			SelectedModeFlag.bit.Mode = 0;//���ģʽ������־	
			if(ContinuousPictureStep < 0)
				ContinuousPictureStep *= -1;
			if(CurrentShift != NewShift)
			{//��Ҫ�л���λ
				ContinuousPictureIndex +=	ContinuousPictureStep;
				CurrentShift = NewShift;
				if(CurrentShift == V2205ShiftInfo_Auto)
				{//�Զ���ѭ����ʾ
					ContinuousPictureStep = 8;
					LoopShift = V2205ShiftInfo_Low;
				}
				else
				{//���൵λֱ����ʾ
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
	{//ģʽͼ�궯������
		DrawTickCount = 0;
		result++;
		
		if(ContinuousPictureIndex > 25)
		{//��һ��ѭ��
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
			{//�Զ���ѭ����ʾ
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
		RegisterPicture(0, 0, file_path);//����ͼƬ		
		
		ContinuousPictureIndex +=	ContinuousPictureStep;
//		{
//			sprintf(file_path,"\\root\\icon\\shift\\%d\\%d.ed", LoopShift, ContinuousPictureIndex);
//			DecodeFilePlaneMode(0, 0, file_path);//����ͼƬ		
//		}

		if(FlagContainers.bit.LowBattery || batteryLevel <= 10)
		{//����ʾ������
			IDecodeText& text0 = GetText(0);
			IDecodeText& text2 = GetText(2);
			text0.sleep = true;
			text2.sleep = true;
			if(ContinuousPictureIndex >= 12)
			{
				RegisterPicture(76, 70, "\\root\\icon\\ldld.ed");//���������ͼ��
			}	
		}
		else
		{//δ��ʾ������
			IDecodeText& text0 = GetText(0);
			IDecodeText& text2 = GetText(2);
			text0.sleep = false;
			text2.sleep = false;			
			if(batteryLevel < 10)
			{
				sprintf(file_path,"%d",batteryLevel);
				text0.SetRollText(0, 68, 230, file_path, LanguageList[LanguageListIndex_SmallBattery], -14, 0, RollType_Order_Center, DISCHARGE_BATTERY_LEVEL_TEXT_COLOR, DISCHARGE_BATTERY_LEVEL_TEXT_COLOR);
				text2.SetRollText(122, 83, 40, "%", LanguageList[LanguageListIndex_Smybol], 0, 0, RollType_Order_Center, DISCHARGE_BATTERY_LEVEL_TEXT_COLOR, DISCHARGE_BATTERY_LEVEL_TEXT_COLOR);
			}
			else if(batteryLevel < 100)
			{
				sprintf(file_path,"%d",batteryLevel);
				text0.SetRollText(0, 68, 230, file_path, LanguageList[LanguageListIndex_SmallBattery], -14, 0, RollType_Order_Center, DISCHARGE_BATTERY_LEVEL_TEXT_COLOR, DISCHARGE_BATTERY_LEVEL_TEXT_COLOR);
				text2.SetRollText(132, 83, 40, "%", LanguageList[LanguageListIndex_Smybol], 0, 0, RollType_Order_Center, DISCHARGE_BATTERY_LEVEL_TEXT_COLOR, DISCHARGE_BATTERY_LEVEL_TEXT_COLOR);
			}
			else 
			{
				text0.SetRollText(0, 68, 235, "100", LanguageList[LanguageListIndex_SmallBattery], -14, 0, RollType_Order_Center, DISCHARGE_BATTERY_LEVEL_TEXT_COLOR, DISCHARGE_BATTERY_LEVEL_TEXT_COLOR);
				text2.SetRollText(140, 83, 40, "%", LanguageList[LanguageListIndex_Smybol], 0, 0, RollType_Order_Center, DISCHARGE_BATTERY_LEVEL_TEXT_COLOR, DISCHARGE_BATTERY_LEVEL_TEXT_COLOR);
			}
		}

		if(LockState)
		{//����״̬������״̬
			RegisterPicture(116, 1,"\\root\\icon\\dot.ed");
		}
		if(NeedSave.Language == LanguageOptions_Arabic)
		{//ʹ��ͼƬ
			IDecodeText& text1 = GetText(1);
			text1.sleep = true;
			sprintf(file_path,"\\root\\text\\bold\\10\\%d.ed", NewShift);//ѡ�������ﵲλ�ı�
			RegisterPicture(0, 20, file_path);//�������ﵲλ�ı�
		}
		else
		{
			IDecodeText& text1 = GetText(1);
			text1.sleep = false;
			text1.SetRollText(TextListShiftTable[NeedSave.Language][NewShift-1]);
		}
		
	}
	return result;
}

int Draw::DrawDustLevel(void)
{
	char file_path[64];
	int result;
//	if(DustLevelFlag.bit.clear)
//	{
//		DustLevelFlag.bit.clear = 0;
//		CLEAR_SCREEN();
//		result++;
//	}
	if(DrawTickCount >= 80)
	{//ģʽͼ�궯������
		DrawTickCount = 0;	
		result++;	
		
		if(CurrentShift != NewShift)
		{
			ContinuousPictureStep = -8;
		}
		
		ContinuousPictureIndex +=	ContinuousPictureStep;
		
		if(ContinuousPictureIndex > 25 || ContinuousPictureIndex < 2)
		{//��һ��ѭ��
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
			{//Ϩ��״̬
				if(CurrentShift != NewShift)
				{//��Ҫ�л���λ
					CurrentShift = NewShift;
					if(CurrentShift == V2205ShiftInfo_Auto)
					{//�Զ���ѭ����ʾ
						LoopShift = V2205ShiftInfo_Low;
					}
					else
					{//���൵λֱ����ʾ
						LoopShift = CurrentShift;
					}
				}
				if(CurrentShift == V2205ShiftInfo_Auto)
				{//�Զ���ѭ����ʾ
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
			RegisterPicture(0, 0, file_path);//����ͼƬ		
		}
		else
		{
			if(DustLevel)
				sprintf(file_path,"\\root\\icon\\running\\%d\\%d\\%d.ed", LoopShift, DustLevel, ContinuousPictureIndex);
			else
				sprintf(file_path,"\\root\\icon\\running\\%d\\1\\%d.ed", LoopShift, ContinuousPictureIndex);
			RegisterPicture(0, 0, file_path);//����ͼƬ		
		}
		if(FlagContainers.bit.LowBattery || batteryLevel <= 10)
		{//����ʾ������
			IDecodeText& text0 = GetText(0);
			IDecodeText& text2 = GetText(2);
			text0.sleep = true;
			text2.sleep = true;
			if(ContinuousPictureIndex >= 12)
			{
				RegisterPicture(76, 70, "\\root\\icon\\ldld.ed");//���������ͼ��
			}		
		}
		else
		{//δ��ʾ������
			IDecodeText& text0 = GetText(0);
			IDecodeText& text2 = GetText(2);
			text0.sleep = false;
			text2.sleep = false;
			if(batteryLevel < 10)
			{
				sprintf(file_path,"%d",batteryLevel);
				text0.SetRollText(0, 68, 230, file_path, LanguageList[LanguageListIndex_SmallBattery], -14, 0, RollType_Order_Center, DISCHARGE_BATTERY_LEVEL_TEXT_COLOR, DISCHARGE_BATTERY_LEVEL_TEXT_COLOR);
				text2.SetRollText(122, 83, 40, "%", LanguageList[LanguageListIndex_Smybol], 0, 0, RollType_Order_Center, DISCHARGE_BATTERY_LEVEL_TEXT_COLOR, DISCHARGE_BATTERY_LEVEL_TEXT_COLOR);
			}
			else if(batteryLevel < 100)
			{
				sprintf(file_path,"%d",batteryLevel);
				text0.SetRollText(0, 68, 230, file_path, LanguageList[LanguageListIndex_SmallBattery], -14, 0, RollType_Order_Center, DISCHARGE_BATTERY_LEVEL_TEXT_COLOR, DISCHARGE_BATTERY_LEVEL_TEXT_COLOR);
				text2.SetRollText(132, 83, 40, "%", LanguageList[LanguageListIndex_Smybol], 0, 0, RollType_Order_Center, DISCHARGE_BATTERY_LEVEL_TEXT_COLOR, DISCHARGE_BATTERY_LEVEL_TEXT_COLOR);
			}
			else 
			{
				text0.SetRollText(0, 68, 235, "100", LanguageList[LanguageListIndex_SmallBattery], -14, 0, RollType_Order_Center, DISCHARGE_BATTERY_LEVEL_TEXT_COLOR, DISCHARGE_BATTERY_LEVEL_TEXT_COLOR);
				text2.SetRollText(140, 83, 40, "%", LanguageList[LanguageListIndex_Smybol], 0, 0, RollType_Order_Center, DISCHARGE_BATTERY_LEVEL_TEXT_COLOR, DISCHARGE_BATTERY_LEVEL_TEXT_COLOR);
			}
		}
		
		if(LockState)
		{//����״̬������״̬
			RegisterPicture(116, 1,"\\root\\icon\\dot.ed");
		}
		
		IDecodeText& text1 = GetText(1);
		if(NeedSave.Language == LanguageOptions_Arabic)
		{//ʹ��ͼƬ
			text1.sleep = true;
			sprintf(file_path,"\\root\\text\\bold\\10\\%d.ed", NewShift);//ѡ�������ﵲλ�ı�
			RegisterPicture(0, 20, file_path);//�������ﵲλ�ı�
		}
		else
		{
			text1.sleep = false;
			text1.SetRollText(TextListShiftTable[NeedSave.Language][NewShift-1]);
		}

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
//	if(MainMenuFlag.bit.clear)
//	{
//		MainMenuFlag.bit.clear = 0;
//		CLEAR_SCREEN();
//		result++;
//		
//	}
//	IDecodeText& text0 = GetText(0);
	IDecodeText& text1 = GetText(1);
	IDecodeText& text2 = GetText(2);
	IDecodeText& text3 = GetText(3);
	if(NeedSave.Language == LanguageOptions_Arabic)
	{//ʹ��ͼƬ
//		text0.sleep = true;
		text1.sleep = true;
		text2.sleep = true;
		text3.sleep = true;
	}
	else
	{//ʹ�ù����ı�
//		text0.sleep = false;
		text1.sleep = false;
		text2.sleep = false;
		text3.sleep = false;
	}

	if(MainMenuFlag.bit.showAll)
	{
		MainMenuFlag.bit.showAll = 0;
		result++;
		if(NeedSave.Language == LanguageOptions_Arabic)
		{//ʹ��ͼƬ
			
		}
		else
		{//ʹ�ù����ı�
//			text0.SetRollText(TextListMainMenuTable[NeedSave.Language][0]);
			text1.SetRollText(TextListMainMenuTable[NeedSave.Language][1]);
			text2.SetRollText(TextListMainMenuTable[NeedSave.Language][2]);
			text3.SetRollText(TextListMainMenuTable[NeedSave.Language][3]);	
//			text0.pause = true;
			text1.pause = true;
			text2.pause = true;
			text3.pause = true;
		}
		MainMenuPrve = RollMenu_None;
	}
	if(MainMenuFlag.bit.selected)
	{
		MainMenuFlag.bit.selected = 0;	
		if(MainMenuPrve != MainMenu)
		{
			result++;		
			switch(MainMenuPrve){//����ǰһ������������
//				case RollMenu_CleaningRecord://����ʱĬ��Ϊ000(��ʷ����¼)����һ�ΰ�����000תΪ001
//					if(NeedSave.Language != LanguageOptions_Arabic)
//					{	
//						text0.SetRollText(TextListMainMenuTable[NeedSave.Language][0]);
//						text0.pause = true;
//					}
//					break;
			
				case RollMenu_ResetFilter://�������ã���һ�ΰ�����000תΪ001
					if(NeedSave.Language != LanguageOptions_Arabic)
					{
						text1.SetRollText(TextListMainMenuTable[NeedSave.Language][1]);
						text1.pause = true;
					}
					break;
				
				case RollMenu_SelectLanguage://����ѡ�񣬰�һ�ΰ�����001תΪ011
					if(NeedSave.Language != LanguageOptions_Arabic)
					{
						text2.SetRollText(TextListMainMenuTable[NeedSave.Language][2]);
						text2.pause = true;
					}
					break;
				
				case RollMenu_Exit://�˳�����һ�ΰ�����011תΪ100
					if(NeedSave.Language != LanguageOptions_Arabic)
					{
						text3.SetRollText(TextListMainMenuTable[NeedSave.Language][3]);	
						text3.pause = true;
					}			
					break;
				
				default:
					break;
			}
			switch(MainMenu){//������ǰѡ�е��ı�
				case RollMenu_CleaningRecord://����ʱĬ��Ϊ000(��ʷ����¼)����һ�ΰ�����000תΪ001
//					if(NeedSave.Language == LanguageOptions_Arabic)
//					{			
//						RegisterPicture(0, 10, "\\root\\text\\selected\\10\\qjjl.ed");
//						RegisterPicture(0, 65, "\\root\\text\\selected\\10\\lxcz_.ed");
//						RegisterPicture(0, 120, "\\root\\text\\selected\\10\\yyxz_.ed");
//						RegisterPicture(0, 175, "\\root\\text\\selected\\10\\tc_.ed");
//					}
//					else
//					{
//						text0.SetRollText(TextListMainMenuSelectedTable[NeedSave.Language][0]);
//						text0.pause = false;
//					}		
//					break;
			
				case RollMenu_ResetFilter://�������ã���һ�ΰ�����000תΪ001
					if(NeedSave.Language == LanguageOptions_Arabic)
					{
//						RegisterPicture(0, 10, "\\root\\text\\selected\\10\\qjjl_.ed");
						RegisterPicture(0, 50, "\\root\\text\\selected\\10\\lxcz.ed");					
						RegisterPicture(0, 120, "\\root\\text\\selected\\10\\yyxz_.ed");
						RegisterPicture(0, 175, "\\root\\text\\selected\\10\\tc_.ed");
					}
					else
					{
						text1.SetRollText(TextListMainMenuSelectedTable[NeedSave.Language][1]);
						text1.pause = false;
					}	
					break;
				
				case RollMenu_SelectLanguage://����ѡ�񣬰�һ�ΰ�����001תΪ011
					if(NeedSave.Language == LanguageOptions_Arabic)
					{
//						RegisterPicture(0, 10, "\\root\\text\\selected\\10\\qjjl_.ed");
						RegisterPicture(0, 65, "\\root\\text\\selected\\10\\lxcz_.ed");
						RegisterPicture(0, 120, "\\root\\text\\selected\\10\\yyxz.ed");
						RegisterPicture(0, 175, "\\root\\text\\selected\\10\\tc_.ed");				
					}
					else
					{
						text2.SetRollText(TextListMainMenuSelectedTable[NeedSave.Language][2]);
						text2.pause = false;
					}
					break;
				
				case RollMenu_Exit://�˳�����һ�ΰ�����011תΪ100
					if(NeedSave.Language == LanguageOptions_Arabic)
					{
//						RegisterPicture(0, 10, "\\root\\text\\selected\\10\\qjjl_.ed");
						RegisterPicture(0, 65, "\\root\\text\\selected\\10\\lxcz_.ed");
						RegisterPicture(0, 120, "\\root\\text\\selected\\10\\yyxz_.ed");		
						RegisterPicture(0, 175, "\\root\\text\\selected\\10\\tc.ed");
					}
					else
					{
						text3.SetRollText(TextListMainMenuSelectedTable[NeedSave.Language][3]);
						text3.pause = false;
					}	
					break;
				
				default:
					break;
			}
			MainMenuPrve = MainMenu;
		}	
	}	
	if(DrawTickCount >= 40 || result)
	{//ģʽͼ�궯������
		DrawTickCount = 0;	
		if(NeedSave.Language != LanguageOptions_Arabic)
		{//ʹ�ù����ı��Ķ�ʱˢ��
			result++;	
		}
	}
	return result;
}

int Draw::DrawHistory(void)
{
	char file_path[64];
	int result = 0;
//	if(HistoryFlag.bit.clear)
//	{
//		HistoryFlag.bit.clear = 0;
//		CLEAR_SCREEN();
//		result++;
//	}

	if(HistoryFlag.bit.show)
	{
		HistoryFlag.bit.show = 0;
		DrawTickCount = 40;
		IDecodeText& text0 = GetText(0);
		if(NeedSave.Language == LanguageOptions_Arabic)
		{
			text0.sleep = true;		
		}
		else
		{
			
			text0.sleep = false;
			text0.SetRollText(TextListHistoryTable[NeedSave.Language]);
		}
	}
	if(DrawTickCount >= 40)
	{
		DrawTickCount = 0;
		result++;	
		
		if(NeedSave.Language == LanguageOptions_Arabic)
		{
			RegisterPicture(5, 180, "\\root\\text\\selected\\10\\record.ed");//������������ı�ͼƬ
		}
		
		RegisterPicture(0, 0, "\\root\\icon\\history\\bg.ed");//��ʷ���汳��	 
		
//		sprintf(file_path,"\\root\\text\\%d\\record.ed", NeedSave.Language);
//		RegisterPicture(0, 180, file_path);	//��ʷ����ײ�����
		for(int i=0; i<7; i++)
		{//������ʷ��¼��״ͼ
			int history = (int)(NeedSave.History[i]/5);

			if(NeedSave.History[i] > 0.01f)//���϶���
				history +=1;
			
			if(history > 19)//�������
				history = 19;
			
			sprintf(file_path,"\\root\\icon\\history\\%d.ed", history);
			if(history != 0)
			{
				RegisterPicture(47+27*i, 39, file_path);
			}
//			else
//			{
//				RegisterPicture(34+28*i, 132, file_path);
//			}
		}	
	}
	return result;
}

int Draw::DrawResetFilter(void)
{
	char file_path[64];
	int result = 0; 	
	if(ResetFilterFlag.bit.show)
	{
		ResetFilterFlag.bit.show = 0;
		DrawTickCount = 0;
		result++;
		ContinuousPictureIndex = 1;
		ContinuousPictureStep = 2;
		sprintf(file_path,"\\root\\icon\\loop\\%d.ed", ContinuousPictureIndex);//ָ����
		RegisterPicture(0, 0, file_path);
		
		RegisterPicture(72, 45, "\\root\\icon\\lxcz0.ed");//����ͼ��
		IDecodeText& text0 = GetText(0);
		text0.sleep = false;
		text0.SetRollText(0, 134, 240, "3", LanguageList[LanguageListIndex_BigBattery], -10, 0, RollType_Order_Center, 0xFFFF, 0xFFFF);

		//DecodeFilePlaneMode(76, 146, "\\root\\text\\battery\\3.ed");//��������
	}

	if(DrawTickCount >= 80)
	{
		if(ContinuousPictureIndex < 64)
		{//�Ƿ�����ȷ�϶����Բ��ŵ�֡
			ContinuousPictureIndex += ContinuousPictureStep;
			DrawTickCount = 0;
			result++;
			int loopIndex = ContinuousPictureIndex*100/75;
			if(loopIndex >= 100)
			{
				loopIndex = 99;
			}
			sprintf(file_path,"\\root\\icon\\loop\\%d.ed", loopIndex);//ָ����
			RegisterPicture(0, 0, file_path);
			
			RegisterPicture(72, 45, "\\root\\icon\\lxcz0.ed");//����ͼ��
			
			IDecodeText& text0 = GetText(0);
			sprintf(file_path,"%d",3 - ContinuousPictureIndex/22);
			text0.SetRollText(0, 134, 240, file_path, LanguageList[LanguageListIndex_BigBattery], -10, 0, RollType_Order_Center, 0xFFFF, 0xFFFF);

			//sprintf(file_path,"\\root\\text\\battery\\big\\%d.ed", 3 - ContinuousPictureIndex/22);//ָ������
			//DecodeFilePlaneMode(76, 146, file_path);//��������
			
		}	
		else if(ContinuousPictureIndex < 75)
		{//ʣ�������֡
			if(FlagContainers.bit.ResetFilter)
			{//��Ҫ����ȷ�ϲ��ܲ���
				ContinuousPictureIndex += ContinuousPictureStep;
				if(ContinuousPictureIndex > 75)
				{
					ContinuousPictureIndex = 75;
				}
				DrawTickCount = 0;
				result++;
				
				int loopIndex = ContinuousPictureIndex*100/75;
				if(loopIndex >= 100)
				{
					loopIndex = 100;
				}
				sprintf(file_path,"\\root\\icon\\loop\\%d.ed", loopIndex);//ָ����
				RegisterPicture(0, 0, file_path);
				
				RegisterPicture(72, 45, "\\root\\icon\\lxcz1.ed");//����ͼ��
				
				sprintf(file_path,"\\root\\icon\\verify\\%d.ed", ContinuousPictureIndex - 63);//ָ���Ժ�
				RegisterPicture(102, 156, file_path);//���ƶԺ�
				
				IDecodeText& text0 = GetText(0);
				text0.sleep = true;
			}
		}
		else
		{
			if(!FlagContainers.bit.ResetFilter)
			{//ȷ�� ���˳���˵�
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
//	if(LanguageMenuFlag.bit.clear)
//	{
//		LanguageMenuFlag.bit.clear = 0;
//		CLEAR_SCREEN();
//		result++;
//	}
	if(LanguageMenuFlag.bit.selected)
	{
		CLEAR_SCREEN();
		
		LanguageMenuFlag.bit.selected = 0;
		result++;

		int page = NewLanguage>>2;
		int current = NewLanguage&3;
		
		IDecodeText& text0 = GetText(0);
		IDecodeText& text1 = GetText(1);
//		IDecodeText& text2 = GetText(2);
//		IDecodeText& text3 = GetText(3);
		text0.sleep = false;
		text1.sleep = false;
//		text2.sleep = false;
//		text3.sleep = false;
		switch(current)
		{
			case 0:
				text0.SetRollText(TextListLanguageSelectedTable[page<<2]);
				text1.SetRollText(TextListLanguageTable[(page<<2) + 1]);
				break;
			
			case 1:
				text0.SetRollText(TextListLanguageTable[page<<2]);
				text1.SetRollText(TextListLanguageSelectedTable[(page<<2) + 1]);
				break;
			
			case 2:				
				text0.SetRollText(TextListLanguageTable[page<<2]);
				text1.SetRollText(TextListLanguageTable[(page<<2) + 1]);
				break;
			
			case 3:
				text0.SetRollText(TextListLanguageTable[page<<2]);
				text1.SetRollText(TextListLanguageTable[(page<<2) + 1]);
				break;
			
			default:
				break;
		}		
	}
	return result;
}

int Draw::DrawConfirmation(void)
{
	char file_path[64];
	int result = 0;
//	if(ConfirmationFlag.bit.clear)
//	{
//		ConfirmationFlag.bit.clear = 0;
//		CLEAR_SCREEN();
//		result++;
//	}
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
		{//�Ƿ�����ȷ�϶����Բ��ŵ�֡
			ContinuousPictureIndex += ContinuousPictureStep;
			DrawTickCount = 0;
			result++;
			
			int loopIndex = ContinuousPictureIndex*100/75;
			if(loopIndex >= 100)
			{
				loopIndex = 99;
			}	
			sprintf(file_path,"\\root\\icon\\loop\\%d.ed", loopIndex);//ָ����
			RegisterPicture(0, 0, file_path);
			
			IDecodeText& text0 = GetText(0);
			if(NewLanguage == LanguageOptions_Arabic)
			{
				text0.sleep = true;
				RegisterPicture(40, 72, "\\root\\text\\selected\\10\\_.ed");
			}
			else
			{
				text0.sleep = false;
				text0.SetRollText(TextListLanguageTable[NewLanguage]);
				text0.ChangeColor(0x8410, 0x8410);
				text0.ChangeTextPos(0, 72);
			}
			
			
			//sprintf(file_path,"\\root\\text\\%d\\_l.ed", NewLanguage);//ָ������
			//DecodeFilePlaneMode(40, 72, file_path);//ָ������
			
			IDecodeText& text1 = GetText(1);
			text1.sleep = false;
			sprintf(file_path,"%d",3 - ContinuousPictureIndex/22);
			text1.SetRollText(0, 134, 240, file_path, LanguageList[LanguageListIndex_BigBattery], -10, 0, RollType_Order_Center, 0xFFFF, 0xFFFF);
			
			//sprintf(file_path,"\\root\\text\\battery\\big\\%d.ed", 3 - ContinuousPictureIndex/22);//ָ������
			//DecodeFilePlaneMode(76, 146, file_path);//��������
		}	
		else if(ContinuousPictureIndex < 75)
		{//ʣ�������֡
			if(FlagContainers.bit.comfirmLangeuage)
			{//��Ҫ����ȷ�ϲ��ܲ���
				ContinuousPictureIndex += ContinuousPictureStep;
				if(ContinuousPictureIndex > 75)
				{
					ContinuousPictureIndex = 75;
				}
				DrawTickCount = 0;
				result++;
				
				int loopIndex = ContinuousPictureIndex*100/75;
				if(loopIndex >= 100)
				{
					loopIndex = 99;
				}	
				sprintf(file_path,"\\root\\icon\\loop\\%d.ed", loopIndex);//ָ����
				RegisterPicture(0, 0, file_path);
				
				IDecodeText& text0 = GetText(0);
				if(NewLanguage == LanguageOptions_Arabic)
				{
					text0.sleep = true;
					RegisterPicture(40, 72, "\\root\\text\\selected\\10\\_l.ed");
				}
				else
				{
					text0.ChangeColor(0xFFFF, 0xFFFF);
				}
				
			
				IDecodeText& text1 = GetText(1);
				text1.sleep = true;
				//sprintf(file_path,"\\root\\text\\%d\\_l.ed", NewLanguage);//ָ������
				//RegisterPicture(40, 72, file_path);//ָ������
				
				
				
				sprintf(file_path,"\\root\\icon\\verify\\%d.ed", ContinuousPictureIndex - 63);//ָ���Ժ�
				RegisterPicture(102, 156, file_path);//���ƶԺ�
				
				
			}
		}
		else
		{
			//������� ����洢
			FlagContainers.bit.ChangeLangeuage = 1;
			if(!FlagContainers.bit.comfirmLangeuage)
			{//ȷ�� ���˳���˵�
				FlagContainers.bit.comfirmLangeuage = 0;
				NeedSave.Language = NewLanguage;//������������ѡ��Ϊ��ǰ����
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
		
//		if(lastBatteryLevel != batteryLevel)
		{
//		lastBatteryLevel = batteryLevel;

			//���³�����
			IDecodeText& text0 = GetText(0);
			text0.sleep = false;
			if(batteryLevel < 100)
			{
				//���³�����
				sprintf(file_path,"\\root\\icon\\loop\\%d.ed", batteryLevel);//ָ����			
				RegisterPicture(0, 0, file_path);
				
				sprintf(file_path,"%d",batteryLevel);
				text0.SetRollText(0, 42, 240, file_path, LanguageList[LanguageListIndex_BigBattery], -23, 0, RollType_Order_Center, 0xFFFF, 0xFFFF);
			}
			else
			{
				RegisterPicture(0, 0, "\\root\\icon\\loop\\100.ed");
				text0.SetRollText(0, 42, 240, "100", LanguageList[LanguageListIndex_BigBattery], -23, 0, RollType_Order_Center, 0xFFFF, 0xFFFF);
			}
			

			//sprintf(file_path,"\\root\\text\\battery\\big\\%d.ed", batteryLevel);//ָ����������
			//DecodeFilePlaneMode(76, 60, file_path);
		}
		
		sprintf(file_path,"\\root\\icon\\bolt\\%d.ed", ContinuousPictureIndex);//ָ������	
		RegisterPicture(104, 136, file_path);//��������
		
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
			if(ContinuousPictureIndex > 25)
			{
				ContinuousPictureIndex = 25;
				ContinuousPictureStep *= -1;	
			}
			else if(ContinuousPictureIndex < 1)
			{
				ContinuousPictureIndex = 1;
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
//	if(LockFlag.bit.clear)
//	{
//		LockFlag.bit.clear = 0;
//		CLEAR_SCREEN();
//		result++;
//	}
	if(LockFlag.bit.show)
	{
		LockFlag.bit.show = 0;
		DrawTickCount = 40;
		result++;
		IDecodeText& text0 = GetText(0);
		text0.sleep = false;	
		if(LockState)
		{//����
			ContinuousPictureIndex = 0;
			ContinuousPictureStep = 1;	
			if(NeedSave.Language == LanguageOptions_Arabic)
			{
				text0.sleep = true;
				RegisterPicture(0, 130, "\\root\\text\\selected\\10\\lock.ed");
			}
			else
			{
				text0.SetRollText(TextListLockTable[NeedSave.Language]);
			}
			
//			sprintf(file_path,"\\root\\text\\%d\\lock.ed", NeedSave.Language);
//			if(NeedSave.Language >= LanguageOptions_English && NeedSave.Language <= LanguageOptions_Russian)
//			{
//				RegisterPicture(0, 104, file_path);
//			}
//			else
//			{
//				RegisterPicture(0, 130, file_path);
//			}
		}
		else
		{//����	
			ContinuousPictureIndex = 20;
			ContinuousPictureStep = -1;
			if(NeedSave.Language == LanguageOptions_Arabic)
			{
				text0.sleep = true;
				RegisterPicture(0, 130, "\\root\\text\\selected\\10\\unlock.ed");
			}
			else
			{
				text0.SetRollText(TextListUnlockTable[NeedSave.Language]);
			}
//			sprintf(file_path,"\\root\\text\\%d\\unlock.ed", NeedSave.Language);
//			if(NeedSave.Language >= LanguageOptions_English && NeedSave.Language <= LanguageOptions_Russian)
//			{
//				RegisterPicture(0, 104, file_path);
//			}
//			else
//			{
//				RegisterPicture(0, 130, file_path);
//			}	
		}
	}
	if(DrawTickCount >= 40)
	{
		if(ContinuousPictureIndex >= 0 && ContinuousPictureIndex <= 20)
		{
			DrawTickCount = 0;
			result++;
			
			if(NeedSave.Language == LanguageOptions_Arabic)
			{
				if(LockState)
				{
					RegisterPicture(0, 130, "\\root\\text\\selected\\10\\lock.ed");
				}
				else
				{
					RegisterPicture(0, 130, "\\root\\text\\selected\\10\\unlock.ed");
				}
			}
			sprintf(file_path,"\\root\\icon\\lock\\%d.ed", ContinuousPictureIndex);
//			if(NeedSave.Language >= LanguageOptions_English && NeedSave.Language <= LanguageOptions_Russian)
//			{
//				RegisterPicture(72, 18, file_path);
//			}
//			else
//			{
				RegisterPicture(72, 35, file_path);
//			}
			ContinuousPictureIndex += ContinuousPictureStep;	
			result++;
		}	
		else
		{
			if(DrawTickCount >= 1040)
			{
				ReturnPrevPage();
			}		
			if(DrawTickCount%40 == 0)
			{
				if(LockState)
				{
					RegisterPicture(72, 35, "\\root\\icon\\lock\\20.ed");
					if(NeedSave.Language == LanguageOptions_Arabic)
					{
						RegisterPicture(0, 130, "\\root\\text\\selected\\10\\lock.ed");
					}
				}
				else
				{
					RegisterPicture(72, 35, "\\root\\icon\\lock\\0.ed");
					if(NeedSave.Language == LanguageOptions_Arabic)
					{
						RegisterPicture(0, 130, "\\root\\text\\selected\\10\\unlock.ed");
					}
				}
				result++;
			}			
		}	
	}
	return result;
}

int Draw::DrawShowError(void)
{
//	char file_path[64];
	int result = 0;
//	if(ShowErrorFlag.bit.clear)
//	{
//		ShowErrorFlag.bit.clear = 0;
//		CLEAR_SCREEN();
//		result++;
//	}
	if(ShowErrorFlag.bit.show)
	{
		ShowErrorFlag.bit.show = 0;		
		IDecodeText& text0 = GetText(0);
		text0.sleep = false;
		if(NeedSave.Language == LanguageOptions_Arabic)
		{
			text0.sleep = true;
		}
		else
		switch(ErrorData)
		{
			case ErrorData_BldcUndervoltage://BLDCǷѹ��UI�������1��--¼�ڹ��ϼ�¼��		
			case ErrorData_BldcCvervoltage://BLDC��ѹ��UI�������1��--¼�ڹ��ϼ�¼��
			case ErrorData_BldcOverTemperature://BLDC���£�UI�������1��--¼�ڹ��ϼ�¼��	
			case ErrorData_BldcOvercurrent://BLDC������UI�������1��--¼�ڹ��ϼ�¼��
			case ErrorData_BldcOverspeed://BLDC���٣�UI�������1��--¼�ڹ��ϼ�¼��
			case ErrorData_BldcOpenPhase://BLDCȱ�ࣨUI�������1��--¼�ڹ��ϼ�¼��
				//text0.SetRollText(TextListErrorCodeTable[0]);	
				text0.sleep = true;
				break;
			
			case ErrorData_TuyereBlocked://ȫ�·�ڣ�UI���������
				text0.SetRollText(TextListTuyereBlockedTable[NeedSave.Language]);
				break;
			
			case ErrorData_RollerStall://��ˢ��ת��UI�������ˢ��
			case ErrorData_RollerShortOut://��ˢ��·��UI�������ˢ��
				text0.SetRollText(TextListRollerStallTable[NeedSave.Language]);
				break;
			
			case ErrorData_OverDischargeProtection://���ű���
				text0.sleep = true;
				return result;
			
			case ErrorData_DischargeOvertemperatureProtection://�ŵ���±�����UI��ع��£�  (�������ŵ����)
				text0.SetRollText(TextListOvertemperatureTable[NeedSave.Language]);
				break;
			
			case ErrorData_DischargeNoLoadProtection://�ŵ���ر�����UI�������2��
				//text0.SetRollText(TextListErrorCodeTable[1]);
				text0.sleep = true;
				break;
			
			case ErrorData_CommunicationTimeout://ͨѶ��ʱ�����ܷ�����ȥ����UI�������3��--¼�ڹ��ϼ�¼��		
				//text0.SetRollText(TextListErrorCodeTable[2]);	
				text0.sleep = true;
				break;
			
//			case ErrorData_FilterNotInstalled://��оδ��װ��UI��
//				text0.SetRollText(TextListFilterNotInstalledTable[NeedSave.Language]);
//				break;
			
			case ErrorData_Reserve://�ŵ����/��·/ /BLDC�ض�ʧ�ܱ�������Ļ�޷���ʾ
				text0.sleep = true;
				return result;
			
			case ErrorData_OverchargeProtection://���䱣��
				text0.sleep = true;
				return result;
			
			case ErrorData_ChargerVoltageAbnormal://�������ѹ�쳣��UI�������4��
				//text0.SetRollText(TextListErrorCodeTable[3]);
				text0.sleep = true;
				break;
			
			case ErrorData_ChargerOvercurrent://��������UI�������5��
				//text0.SetRollText(TextListErrorCodeTable[4]);
				text0.sleep = true;
				break;
			
			case ErrorData_ChargerTimeout://��糬ʱ��UI�������6��
				//text0.SetRollText(TextListErrorCodeTable[5]);
				text0.sleep = true;
				break;
			
			case ErrorData_BatteriesFault://��о���ϣ�UI�������7��--¼�ڹ��ϼ�¼��
				//text0.SetRollText(TextListErrorCodeTable[6]);
				text0.sleep = true;
				break;
			
			case ErrorData_NTCFault://�¶ȴ�����(NTC)���ϣ�UI�������8��--¼�ڹ��ϼ�¼��
				//text0.SetRollText(TextListErrorCodeTable[7]);
				text0.sleep = true;
				break;
			
			case ErrorData_BMSHardwareFault://ǰ��ͨѶʧ��(BMSӲ���쳣)��UI�������9��--¼�ڹ��ϼ�¼��
				//text0.SetRollText(TextListErrorCodeTable[8]);
				text0.sleep = true;
				break;
			
			default://���Ǽ�¼�Ĺ��ϻ����޹��� �������е����;����ж�
				if(LowBatteryWarning == LowBatteryWarning_Low)
				{
					text0.SetRollText(TextListBatteryLowTable[NeedSave.Language]);
				}
				else if(LowBatteryWarning == LowBatteryWarning_Out)
				{
					text0.SetRollText(TextListBatteryOutTable[NeedSave.Language]);
				}
				else
				{//����λ�ù���
					text0.sleep = true;
				}
				break;
		}
		DrawTickCount = 0;
	}
	if(DrawTickCount <= 3600)
	{//0~600 ��600ms
		if(DrawTickCount%40 == 0)
		{
			if(DrawTickCount%1200 < 600)
			{
				switch(ErrorData)
				{
					case ErrorData_BldcUndervoltage://BLDCǷѹ��UI�������1��--¼�ڹ��ϼ�¼��		
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");		
						RegisterPicture(0, 130, "\\root\\text\\error\\1.ed");		
						goto EndErrorDisplay;
					
					case  ErrorData_BldcCvervoltage://BLDC��ѹ��UI�������1��--¼�ڹ��ϼ�¼��
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");	
						RegisterPicture(0, 130, "\\root\\text\\error\\1.ed");		
						goto EndErrorDisplay;
					
					case ErrorData_BldcOverTemperature://BLDC���£�UI�������1��--¼�ڹ��ϼ�¼��	
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");
						RegisterPicture(0, 130, "\\root\\text\\error\\1.ed");		
						goto EndErrorDisplay;	
					
					case ErrorData_BldcOvercurrent://BLDC������UI�������1��--¼�ڹ��ϼ�¼��
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");
						RegisterPicture(0, 130, "\\root\\text\\error\\1.ed");		
						goto EndErrorDisplay;
					
					case ErrorData_BldcOverspeed://BLDC���٣�UI�������1��--¼�ڹ��ϼ�¼��
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");
						RegisterPicture(0, 130, "\\root\\text\\error\\1.ed");		
						goto EndErrorDisplay;
					
					case ErrorData_BldcOpenPhase://BLDCȱ�ࣨUI�������1��--¼�ڹ��ϼ�¼��
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");
						RegisterPicture(0, 130, "\\root\\text\\error\\1.ed");		
						goto EndErrorDisplay;
					
					case ErrorData_TuyereBlocked://ȫ�·�ڣ�UI���������
						result++;//����UI����Ľ������� ����ֱ���˳�	
						RegisterPicture(72, 38, "\\root\\icon\\fdds.ed");
						if(NeedSave.Language == LanguageOptions_Arabic)
						{
							RegisterPicture(0, 130, "\\root\\text\\selected\\10\\fdds.ed");
						}
						goto EndErrorDisplay;
					
					case ErrorData_RollerStall://��ˢ��ת��UI�������ˢ��
					case ErrorData_RollerShortOut://��ˢ��·��UI�������ˢ��
						result++;//����UI����Ľ������� ����ֱ���˳�
						RegisterPicture(72, 38, "\\root\\icon\\qlgs.ed");
						if(NeedSave.Language == LanguageOptions_Arabic)
						{
							RegisterPicture(0, 130, "\\root\\text\\selected\\10\\qlgs.ed");
						}
						goto EndErrorDisplay;
					
					case ErrorData_OverDischargeProtection://���ű���
						return result;
					
					case ErrorData_DischargeOvertemperatureProtection://�ŵ���±�����UI��ع��£�  (�������ŵ����)
						result++;//����UI����Ľ������� ����ֱ���˳�			
						RegisterPicture(72, 38, "\\root\\icon\\dcgr.ed");
						if(NeedSave.Language == LanguageOptions_Arabic)
						{
							RegisterPicture(0, 130, "\\root\\text\\selected\\10\\dcgr.ed");
						}
						goto EndErrorDisplay;
					
					case ErrorData_DischargeNoLoadProtection://�ŵ���ر�����UI�������2��
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");	
						RegisterPicture(0, 130, "\\root\\text\\error\\2.ed");		
						goto EndErrorDisplay;
					
					case ErrorData_CommunicationTimeout://ͨѶ��ʱ�����ܷ�����ȥ����UI�������3��--¼�ڹ��ϼ�¼��		
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");				
						RegisterPicture(0, 130, "\\root\\text\\error\\3.ed");		
						goto EndErrorDisplay;
					
//					case ErrorData_FilterNotInstalled://��оδ��װ��UI��
//						result++;//����UI����Ľ������� ����ֱ���˳�
//						RegisterPicture(72, 38, "\\root\\icon\\lxwaz.ed");
//						if(NeedSave.Language == LanguageOptions_Arabic)
//						{
//							RegisterPicture(0, 130, "\\root\\text\\selected\\10\\lxwaz.ed");
//						}
//						goto EndErrorDisplay;
					
					case ErrorData_Reserve://�ŵ����/��·/ /BLDC�ض�ʧ�ܱ�������Ļ�޷���ʾ
						return result;
					
					case ErrorData_OverchargeProtection://���䱣��
						return result;
					
					case ErrorData_ChargerVoltageAbnormal://�������ѹ�쳣��UI�������4��
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");	
						RegisterPicture(0, 130, "\\root\\text\\error\\4.ed");		
						goto EndErrorDisplay;
					
					case ErrorData_ChargerOvercurrent://��������UI�������5��
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");
						RegisterPicture(0, 130, "\\root\\text\\error\\5.ed");		
						goto EndErrorDisplay;
					
					case ErrorData_ChargerTimeout://��糬ʱ��UI�������6��
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");	
						RegisterPicture(0, 130, "\\root\\text\\error\\6.ed");		
						goto EndErrorDisplay;
					
					case ErrorData_BatteriesFault://��о���ϣ�UI�������7��--¼�ڹ��ϼ�¼��
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");
						RegisterPicture(0, 130, "\\root\\text\\error\\7.ed");		
						goto EndErrorDisplay;
					
					case ErrorData_NTCFault://�¶ȴ�����(NTC)���ϣ�UI�������8��--¼�ڹ��ϼ�¼��
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");
						RegisterPicture(0, 130, "\\root\\text\\error\\8.ed");		
						goto EndErrorDisplay;
					
					case ErrorData_BMSHardwareFault://ǰ��ͨѶʧ��(BMSӲ���쳣)��UI�������9��--¼�ڹ��ϼ�¼��
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");	
						RegisterPicture(0, 130, "\\root\\text\\error\\9.ed");		
						goto EndErrorDisplay;
					
					default://���Ǽ�¼�Ĺ��ϻ����޹��� �������е����;����ж�
						if(LowBatteryWarning == LowBatteryWarning_Low)
						{	
							result++;
							FlagContainers.bit.LowBattery = 1;
							FlagContainers.bit.LowBatteryPage = 1;
							RegisterPicture(72, 38,"\\root\\icon\\dld.ed");
							if(NeedSave.Language == LanguageOptions_Arabic)
							{
								RegisterPicture(0, 130, "\\root\\text\\selected\\10\\dld.ed");
							}
							goto EndErrorDisplay;
						}
						else if(LowBatteryWarning == LowBatteryWarning_Out)
						{
							result++;
							RegisterPicture(72, 38,"\\root\\icon\\dlhj.ed");
							if(NeedSave.Language == LanguageOptions_Arabic)
							{
								RegisterPicture(0, 130, "\\root\\text\\selected\\10\\dlhj.ed");
							}
							goto EndErrorDisplay;
						}
						else
						{
							
						}
						break;
				}	
			}
			else
			{
				switch(ErrorData)
				{
					case ErrorData_BldcUndervoltage://BLDCǷѹ��UI�������1��--¼�ڹ��ϼ�¼��	
						result++;					
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");		
						RegisterPicture(0, 130, "\\root\\text\\error\\1.ed");		
						goto EndErrorDisplay;
					
					case  ErrorData_BldcCvervoltage://BLDC��ѹ��UI�������1��--¼�ڹ��ϼ�¼��
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");	
						RegisterPicture(0, 130, "\\root\\text\\error\\1.ed");		
						goto EndErrorDisplay;
					
					case ErrorData_BldcOverTemperature://BLDC���£�UI�������1��--¼�ڹ��ϼ�¼��	
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");	
						RegisterPicture(0, 130, "\\root\\text\\error\\1.ed");		
						goto EndErrorDisplay;	
					
					case ErrorData_BldcOvercurrent://BLDC������UI�������1��--¼�ڹ��ϼ�¼��
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");
						RegisterPicture(0, 130, "\\root\\text\\error\\1.ed");		
						goto EndErrorDisplay;
					
					case ErrorData_BldcOverspeed://BLDC���٣�UI�������1��--¼�ڹ��ϼ�¼��
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");
						RegisterPicture(0, 130, "\\root\\text\\error\\1.ed");		
						goto EndErrorDisplay;
					
					case ErrorData_BldcOpenPhase://BLDCȱ�ࣨUI�������1��--¼�ڹ��ϼ�¼��
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");
						RegisterPicture(0, 130, "\\root\\text\\error\\1.ed");		
						goto EndErrorDisplay;
					
					case ErrorData_TuyereBlocked://ȫ�·�ڣ�UI���������
						result++;//����UI����Ľ������� ����ֱ���˳�
						if(NeedSave.Language == LanguageOptions_Arabic)
						{
							RegisterPicture(0, 130, "\\root\\text\\selected\\10\\fdds.ed");
						}
						goto EndErrorDisplay;
					
					case ErrorData_RollerStall://��ˢ��ת��UI�������ˢ��
					case ErrorData_RollerShortOut://��ˢ��·��UI�������ˢ��
						result++;//����UI����Ľ������� ����ֱ���˳�
						if(NeedSave.Language == LanguageOptions_Arabic)
						{
							RegisterPicture(0, 130, "\\root\\text\\selected\\10\\qlgs.ed");
						}
						goto EndErrorDisplay;
					
					case ErrorData_OverDischargeProtection://���ű���
						return result;
					
					case ErrorData_DischargeOvertemperatureProtection://�ŵ���±�����UI��ع��£�  (�������ŵ����)
						result++;//����UI����Ľ������� ����ֱ���˳�		
						if(NeedSave.Language == LanguageOptions_Arabic)
						{
							RegisterPicture(0, 130, "\\root\\text\\selected\\10\\dcgr.ed");
						}					
						goto EndErrorDisplay;
					
					case ErrorData_DischargeNoLoadProtection://�ŵ���ر�����UI�������2��
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");
						RegisterPicture(0, 130, "\\root\\text\\error\\2.ed");		
						goto EndErrorDisplay;
					
					case ErrorData_CommunicationTimeout://ͨѶ��ʱ�����ܷ�����ȥ����UI�������3��--¼�ڹ��ϼ�¼��		
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");	
						RegisterPicture(0, 130, "\\root\\text\\error\\3.ed");		
						goto EndErrorDisplay;
					
//					case ErrorData_FilterNotInstalled://��оδ��װ��UI��
//						result++;//����UI����Ľ������� ����ֱ���˳�
//						if(NeedSave.Language == LanguageOptions_Arabic)
//						{
//							RegisterPicture(0, 130, "\\root\\text\\selected\\10\\lxwaz.ed");
//						}
//						goto EndErrorDisplay;
					
					case ErrorData_Reserve://�ŵ����/��·/ /BLDC�ض�ʧ�ܱ�������Ļ�޷���ʾ
						return result;
					
					case ErrorData_OverchargeProtection://���䱣��
						return result;
					
					case ErrorData_ChargerVoltageAbnormal://�������ѹ�쳣��UI�������4��
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");
						RegisterPicture(0, 130, "\\root\\text\\error\\4.ed");		
						goto EndErrorDisplay;
					
					case ErrorData_ChargerOvercurrent://��������UI�������5��
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");	
						RegisterPicture(0, 130, "\\root\\text\\error\\5.ed");		
						goto EndErrorDisplay;
					
					case ErrorData_ChargerTimeout://��糬ʱ��UI�������6��
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");
						RegisterPicture(0, 130, "\\root\\text\\error\\6.ed");		
						goto EndErrorDisplay;
					
					case ErrorData_BatteriesFault://��о���ϣ�UI�������7��--¼�ڹ��ϼ�¼��
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");
						RegisterPicture(0, 130, "\\root\\text\\error\\7.ed");		
						goto EndErrorDisplay;
					
					case ErrorData_NTCFault://�¶ȴ�����(NTC)���ϣ�UI�������8��--¼�ڹ��ϼ�¼��
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");
						RegisterPicture(0, 130, "\\root\\text\\error\\8.ed");		
						goto EndErrorDisplay;
					
					case ErrorData_BMSHardwareFault://ǰ��ͨѶʧ��(BMSӲ���쳣)��UI�������9��--¼�ڹ��ϼ�¼��
						result++;
						RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");	
						RegisterPicture(0, 130, "\\root\\text\\error\\9.ed");		
						goto EndErrorDisplay;
					
					default://���Ǽ�¼�Ĺ��ϻ����޹��� �������е����;����ж�
						if(LowBatteryWarning == LowBatteryWarning_Low)
						{
							result++;
							if(NeedSave.Language == LanguageOptions_Arabic)
							{
								RegisterPicture(0, 130, "\\root\\text\\selected\\10\\dld.ed");
							}
							goto EndErrorDisplay;
						}
						else if(LowBatteryWarning == LowBatteryWarning_Out)
						{
							result++;
							RegisterPicture(72, 38,"\\root\\icon\\dlhj.ed");
							if(NeedSave.Language == LanguageOptions_Arabic)
							{
								RegisterPicture(0, 130, "\\root\\text\\selected\\10\\dlhj.ed");
							}
							goto EndErrorDisplay;
						}
						else
						{
							return result;
						}
				}		
			}
		}	
	}
	else if(DrawTickCount >= 3641)
	{
		DrawTickCount = 3601;	
		switch(ErrorData)
		{
			case ErrorData_BldcUndervoltage://BLDCǷѹ��UI�������1��--¼�ڹ��ϼ�¼��		
				result++;				
				RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");		
				RegisterPicture(0, 130, "\\root\\text\\error\\1.ed");		
				break;
			
			case  ErrorData_BldcCvervoltage://BLDC��ѹ��UI�������1��--¼�ڹ��ϼ�¼��
				result++;
				RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");	
				RegisterPicture(0, 130, "\\root\\text\\error\\1.ed");		
				break;
			
			case ErrorData_BldcOverTemperature://BLDC���£�UI�������1��--¼�ڹ��ϼ�¼��	
				result++;
				RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");
				RegisterPicture(0, 130, "\\root\\text\\error\\1.ed");		
				break;
			
			case ErrorData_BldcOvercurrent://BLDC������UI�������1��--¼�ڹ��ϼ�¼��
				result++;
				RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");
				RegisterPicture(0, 130, "\\root\\text\\error\\1.ed");		
				break;
			
			case ErrorData_BldcOverspeed://BLDC���٣�UI�������1��--¼�ڹ��ϼ�¼��
				result++;
				RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");
				RegisterPicture(0, 130, "\\root\\text\\error\\1.ed");		
				break;
			
			case ErrorData_BldcOpenPhase://BLDCȱ�ࣨUI�������1��--¼�ڹ��ϼ�¼��
				result++;
				RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");
				RegisterPicture(0, 130, "\\root\\text\\error\\1.ed");		
				break;
			
			case ErrorData_TuyereBlocked://ȫ�·�ڣ�UI���������
				result++;//����UI����Ľ������� ����ֱ���˳�			
				RegisterPicture(72, 38, "\\root\\icon\\fdds.ed");	
				if(NeedSave.Language == LanguageOptions_Arabic)
				{
					RegisterPicture(0, 130, "\\root\\text\\selected\\10\\fdds.ed");
				}			
				break;
			
			case ErrorData_RollerStall://��ˢ��ת��UI�������ˢ��
			case ErrorData_RollerShortOut://��ˢ��·��UI�������ˢ��
				result++;//����UI����Ľ������� ����ֱ���˳�
				RegisterPicture(72, 38, "\\root\\icon\\qlgs.ed");
				if(NeedSave.Language == LanguageOptions_Arabic)
				{
					RegisterPicture(0, 130, "\\root\\text\\selected\\10\\qlgs.ed");
				}
				break;
			
			case ErrorData_OverDischargeProtection://���ű���
				break;
			
			case ErrorData_DischargeOvertemperatureProtection://�ŵ���±�����UI��ع��£�  (�������ŵ����)
				result++;//����UI����Ľ������� ����ֱ���˳�			
				RegisterPicture(72, 38, "\\root\\icon\\dcgr.ed");
				if(NeedSave.Language == LanguageOptions_Arabic)
				{
					RegisterPicture(0, 130, "\\root\\text\\selected\\10\\dcgr.ed");
				}
				break;
			
			case ErrorData_DischargeNoLoadProtection://�ŵ���ر�����UI�������2��
				result++;
				RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");	
				RegisterPicture(0, 130, "\\root\\text\\error\\2.ed");		
				break;
			
			case ErrorData_CommunicationTimeout://ͨѶ��ʱ�����ܷ�����ȥ����UI�������3��--¼�ڹ��ϼ�¼��		
				result++;
				RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");	
				RegisterPicture(0, 130, "\\root\\text\\error\\3.ed");		
				break;
			
//			case ErrorData_FilterNotInstalled://��оδ��װ��UI��
//				result++;//����UI����Ľ������� ����ֱ���˳�
//				RegisterPicture(72, 38, "\\root\\icon\\lxwaz.ed");
//				if(NeedSave.Language == LanguageOptions_Arabic)
//				{
//					RegisterPicture(0, 130, "\\root\\text\\selected\\10\\lxwaz.ed");
//				}
//				break;
			
			case ErrorData_Reserve://�ŵ����/��·/ /BLDC�ض�ʧ�ܱ�������Ļ�޷���ʾ
				return result;
			
			case ErrorData_OverchargeProtection://���䱣��
				return result;
			
			case ErrorData_ChargerVoltageAbnormal://�������ѹ�쳣��UI�������4��
				result++;
				RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");
				RegisterPicture(0, 130, "\\root\\text\\error\\4.ed");		
				break;
			
			case ErrorData_ChargerOvercurrent://��������UI�������5��
				result++;
				RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");
				RegisterPicture(0, 130, "\\root\\text\\error\\5.ed");		
				break;
			
			case ErrorData_ChargerTimeout://��糬ʱ��UI�������6��
				result++;
				RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");	
				RegisterPicture(0, 130, "\\root\\text\\error\\6.ed");		
				break;
			
			case ErrorData_BatteriesFault://��о���ϣ�UI�������7��--¼�ڹ��ϼ�¼��
				result++;
				RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");
				RegisterPicture(0, 130, "\\root\\text\\error\\7.ed");		
				break;
			
			case ErrorData_NTCFault://�¶ȴ�����(NTC)���ϣ�UI�������8��--¼�ڹ��ϼ�¼��
				result++;
				RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");	
				RegisterPicture(0, 130, "\\root\\text\\error\\8.ed");		
				break;
			
			case ErrorData_BMSHardwareFault://ǰ��ͨѶʧ��(BMSӲ���쳣)��UI�������9��--¼�ڹ��ϼ�¼��
				result++;
				RegisterPicture(72, 38, "\\root\\icon\\gzdm.ed");
				RegisterPicture(0, 130, "\\root\\text\\error\\9.ed");		
				break;
			
			default://���Ǽ�¼�Ĺ��ϻ����޹��� �������е����;����ж�
				if(LowBatteryWarning == LowBatteryWarning_Low)
				{
					ReturnPrevPage();
					return result;
				}
				else if(LowBatteryWarning == LowBatteryWarning_Out)
				{
					result++;
					RegisterPicture(72, 38,"\\root\\icon\\dlhj.ed");
					if(NeedSave.Language == LanguageOptions_Arabic)
					{
						RegisterPicture(0, 130, "\\root\\text\\selected\\10\\dlhj.ed");
					}
					break;
				}
				else
				{
					return result;
				}
		}		
	}
	return result;
	
EndErrorDisplay:
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
		{//�Ƿ�����ȷ�϶����Բ��ŵ�֡
			ContinuousPictureIndex += ContinuousPictureStep;
			DrawTickCount = 0;
			result++;
			int loopIndex = ContinuousPictureIndex*100/75;
			if(loopIndex >= 100)
			{
				loopIndex = 99;
			}
			sprintf(file_path,"\\root\\icon\\loop\\%d.ed", loopIndex);//ָ����
			RegisterPicture(0, 0, file_path);
			
			if(HighAltitudeMode == HIGH_ALTITUDE_MODE_ENTERING
				|| HighAltitudeMode == HIGH_ALTITUDE_MODE_ENTERED)
			{
				RegisterPicture(72, 45, "\\root\\icon\\highon0.ed");//����ͼ��
			}
			else
			{
				RegisterPicture(72, 45, "\\root\\icon\\highoff0.ed");//����ͼ��
			}
			
			IDecodeText& text0 = GetText(0);
			text0.sleep = false;
			sprintf(file_path,"%d",3 - ContinuousPictureIndex/22);
			text0.SetRollText(0, 134, 240, file_path, LanguageList[LanguageListIndex_BigBattery], -10, 0, RollType_Order_Center, 0xFFFF, 0xFFFF);
			
			//sprintf(file_path,"\\root\\text\\battery\\big\\%d.ed", 3 - ContinuousPictureIndex/22);//ָ������
			//RegisterPicture(76, 146, file_path);//��������
		}	
		else if(ContinuousPictureIndex < 75)
		{//ʣ�������֡
			if(HighAltitudeMode == HIGH_ALTITUDE_MODE_ENTERED
				|| HighAltitudeMode ==  HIGH_ALTITUDE_MODE_EXITED)
			{//��Ҫ����ȷ�ϲ��ܲ���
				ContinuousPictureIndex += ContinuousPictureStep;
				if(ContinuousPictureIndex > 75)
				{
					ContinuousPictureIndex = 75;
				}
				DrawTickCount = 0;
				result++;
				
				int loopIndex = ContinuousPictureIndex*100/75;
				if(loopIndex >= 100)
				{
					loopIndex = 99;
				}
				sprintf(file_path,"\\root\\icon\\loop\\%d.ed", loopIndex);//ָ����
				RegisterPicture(0, 0, file_path);
				
				if(HighAltitudeMode == HIGH_ALTITUDE_MODE_ENTERING
					|| HighAltitudeMode == HIGH_ALTITUDE_MODE_ENTERED)
				{
					
					RegisterPicture(72, 45, "\\root\\icon\\highon1.ed");//����ͼ��
				}
				else
				{
					RegisterPicture(72, 45, "\\root\\icon\\highoff1.ed");//����ͼ��
				}
				sprintf(file_path,"\\root\\icon\\verify\\%d.ed", ContinuousPictureIndex - 63);//ָ���Ժ�
				RegisterPicture(102, 156, file_path);//���ƶԺ�
				
				IDecodeText& text0 = GetText(0);
				text0.sleep = true;
			}
		}
//		else
//		{
//			if(HighAltitudeMode == HIGH_ALTITUDE_MODE_ENTERED
//				|| HighAltitudeMode ==  HIGH_ALTITUDE_MODE_EXITED)
//			{//ȷ�� ���˳���˵�
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
//	if(FilterServiceLifeFlag.bit.clear)
//	{
//		FilterServiceLifeFlag.bit.clear = 0;
//		CLEAR_SCREEN();
//		result++;
//	}
	if(FilterServiceLifeFlag.bit.show)
	{
		FilterServiceLifeFlag.bit.show = 0;	
		DrawTickCount = 0;			
		IDecodeText& text0 = GetText(0);
		text0.sleep = false;
		
		if(FilterServiceLife == FILTER_SERVICE_LIFE_REPLACE)
		{/*���Ѹ�����о(UI�������о)*/
			ContinuousPictureIndex = 1;
			ContinuousPictureStep = 2;
				
			if(NeedSave.Language == LanguageOptions_Arabic)
			{
				text0.sleep = true;
				
			}
			else
			{
				text0.SetRollText(TextListReplaceFilterTable[NeedSave.Language]);		
			}		
		}
		else if(FilterServiceLife == FILTER_SERVICE_LIFE_EXPIRE)
		{/*��о��Ҫ�����뾡����� (UI��о��Ҫ��������)*/
			if(NeedSave.Language == LanguageOptions_Arabic)
			{
				text0.sleep = true;
			}
			else
			{
				text0.SetRollText(TextListFilterExpireTable[NeedSave.Language]);
			}
		}		
	}
	if(FilterServiceLife == FILTER_SERVICE_LIFE_REPLACE)
	{/*���Ѹ�����о(UI�������о)*/
		if(DrawTickCount%40 == 0)
		{
			if(DrawTickCount < 3200)
			{//����ͼ��׶�
				result++;
				RegisterPicture(72, 38,"\\root\\icon\\ghlx.ed");		
				if(NeedSave.Language == LanguageOptions_Arabic)
				{
					RegisterPicture(0, 130, "\\root\\text\\selected\\10\\ghlx.ed");
				}	
			}	
			else if(ContinuousPictureIndex <= 181)
			{//���Ŷ����׶�
					IDecodeText& text0 = GetText(0);
					text0.sleep = true;
				
					DrawTickCount = 3200/40*40;
					result++;	
					if(ContinuousPictureIndex == 1)
					{
						CLEAR_SCREEN();
					}
					sprintf(file_path,"\\root\\icon\\ghlx\\%d.ed", ContinuousPictureIndex);
					RegisterPicture(20, 20, file_path);
					
					ContinuousPictureIndex += ContinuousPictureStep;	
			}
			else if(DrawTickCount >= 4200)
			{
				ReturnPrevPage();
			}
		}
	}	
	else if(FilterServiceLife == FILTER_SERVICE_LIFE_EXPIRE)
	{/*��о��Ҫ�����뾡����� (UI��о��Ҫ��������)*/
		if(DrawTickCount%40 == 0)
		{
			if(DrawTickCount <= 3600)
			{
				result++;	
				if(DrawTickCount%1200 < 600)
				{//����
					RegisterPicture(72, 38,"\\root\\icon\\lxjdq.ed");			
				}
			}
			else
			{
				if(DrawTickCount%40 == 0)
				{
					result++;
					RegisterPicture(72, 38,"\\root\\icon\\lxjdq.ed");			
				}
			}
			if(NeedSave.Language == LanguageOptions_Arabic)
			{
				RegisterPicture(0, 130, "\\root\\text\\selected\\10\\lxjdq.ed");
			}			
		}
	}
	
	return result;
}

#define CDC_START_UI_LENGTH					73/*��ʼ���ִ�1��ʼ�Ľ�β������*/
#define CDC_RUNNING_UI_LENGTH				89/*ѭ�����ִ�1��ʼ�Ľ�β������*/
#define CDC_END_UI_LENGTH						113/*�������ִ�1��ʼ�Ľ�β������*/
#define CDC_END_DELAY_LENGTH				1/*��β�Ժ�ͣ��ʱ��(��λ40ms)*/
#define CDC_END_DELAY_INDEX					115/*ͣ����֡����*/
#define CDC_SUM_LENGTH							337-45/*�ܲ���ʱ�䣨����ʱ��/40ms��*/
#define CDC_RUNNING_MAX_INDEX				(CDC_SUM_LENGTH - CDC_END_UI_LENGTH - CDC_END_DELAY_LENGTH)/*�����м�ֵ*/

#define CDC_RUNNING_UI_RUNNING_TOTAL				(CDC_SUM_LENGTH-CDC_START_UI_LENGTH-CDC_END_UI_LENGTH)
#define CDC_RUNNING_UI_RUNNING_LAST_NEED		(CDC_RUNNING_UI_RUNNING_TOTAL%CDC_RUNNING_UI_LENGTH)/*���һ������ѭ��֡��*/
#define CDC_RUNNING_UI_RUNNING_LOOP					(CDC_RUNNING_UI_RUNNING_TOTAL/CDC_RUNNING_UI_LENGTH)/*��������ѭ������*/
#define CDC_RUNNING_UI_RUNNING_LOOP_END			((CDC_RUNNING_UI_RUNNING_LOOP*CDC_RUNNING_UI_LENGTH)+CDC_START_UI_LENGTH)
#define CDC_RUNNING_UI_RUNNING_LAST_SKIP		(CDC_RUNNING_UI_LENGTH/CDC_RUNNING_UI_RUNNING_LAST_NEED)
#define CDC_RUNNING_UI_RUNNING_LAST_OFFSET	(CDC_RUNNING_UI_LENGTH%CDC_RUNNING_UI_RUNNING_LAST_NEED)

int Draw::V2205DrawCdc(void)
{
	int result = 0;
	char file_path[64];
	if(CDCFlag.bit.show)
	{
		CDCFlag.bit.show = 0;
		CdcLoopCount = 0;
		DrawTickCount = 80;
	}
	if(DrawTickCount >= 80)
	{
		DrawTickCount = 0;
		result++;	
		
		ContinuousPictureIndex +=	ContinuousPictureStep;
		if(ContinuousPictureIndex <= CDC_START_UI_LENGTH)
		{
			sprintf(file_path,"\\root\\icon\\cdc\\start\\%d.ed", ContinuousPictureIndex); 
		}
		else if(ContinuousPictureIndex <= CDC_RUNNING_MAX_INDEX)
		{
			int currentIndex;
			#if 0
			if(CdcLoopCount&1)
			{//�ݼ�����
				currentIndex = CDC_RUNNING_UI_LENGTH - (ContinuousPictureIndex - CDC_START_UI_LENGTH) % CDC_RUNNING_UI_LENGTH;
				if(CdcLoopCount == CDC_RUNNING_UI_RUNNING_LOOP)
				{
					if(currentIndex == (CDC_RUNNING_UI_LENGTH - CDC_RUNNING_UI_RUNNING_LOOP_END/2))
					{
						CdcLoopCount++;
					}
				}
				else
				{
					if(currentIndex <= 0)
					{
						CdcLoopCount++;
						currentIndex = 0;
					}
				}			
			}
			else
			{//��������
				currentIndex = (ContinuousPictureIndex - CDC_START_UI_LENGTH) % CDC_RUNNING_UI_LENGTH;
				if(CdcLoopCount == CDC_RUNNING_UI_RUNNING_LOOP)
				{//���һ��ѭ��
					if(currentIndex == (CDC_RUNNING_UI_RUNNING_LOOP_END/2))
					{
						CdcLoopCount++;
					}
				}
				else
				{
					if(currentIndex >= CDC_RUNNING_UI_LENGTH)
					{
						CdcLoopCount++;
						currentIndex = CDC_RUNNING_UI_LENGTH;
					}
				}			
			}
			#else
			currentIndex = (ContinuousPictureIndex - CDC_START_UI_LENGTH) % CDC_RUNNING_UI_LENGTH;
			if(CdcLoopCount == CDC_RUNNING_UI_RUNNING_LOOP)
			{
				if(currentIndex < CDC_RUNNING_UI_RUNNING_LAST_OFFSET)
				{//���һ��ѭ������ƫ��ǰ��ÿ����skip+1֡
					currentIndex = currentIndex * (CDC_RUNNING_UI_RUNNING_LAST_SKIP + 1);
				}
				else
				{//���һ��ѭ������ƫ�ƺ�ÿ����skip֡
					currentIndex = currentIndex * CDC_RUNNING_UI_RUNNING_LAST_SKIP + CDC_RUNNING_UI_RUNNING_LAST_OFFSET;
				}	
			}
			else
			{
				if(currentIndex >= CDC_RUNNING_UI_LENGTH)
				{
					CdcLoopCount++;
					currentIndex = CDC_RUNNING_UI_LENGTH;
				}
			}
			#endif
			if(!(currentIndex&1))
			{
				currentIndex++;
			}
			sprintf(file_path,"\\root\\icon\\cdc\\running\\%d.ed", currentIndex); 	
		}
		else if(ContinuousPictureIndex <= CDC_SUM_LENGTH)
		{
			int currentIndex = ContinuousPictureIndex - CDC_RUNNING_MAX_INDEX;
			if(currentIndex >= CDC_END_DELAY_INDEX + CDC_END_DELAY_LENGTH)
			{
				currentIndex -= CDC_END_DELAY_LENGTH;
			}
			else if(currentIndex > CDC_END_DELAY_INDEX)
			{
				currentIndex = CDC_END_DELAY_INDEX;
			}
			if(!(currentIndex&1))
			{
				currentIndex++;
			}
			sprintf(file_path,"\\root\\icon\\cdc\\end\\%d.ed", currentIndex); 
		}
		else
		{
			ContinuousPictureIndex = CDC_SUM_LENGTH;
			sprintf(file_path,"\\root\\icon\\cdc\\end\\%d.ed", CDC_END_UI_LENGTH); 
		}
		RegisterPicture(0, 0, file_path);
		
//		if(ContinuousPictureIndex >= 250)
//		{
//			ContinuousPictureIndex = 250;
//		}
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
		IDecodeText& text0 = GetText(0);
		text0.sleep = false;
		switch(TestMode)
		{
			case TestMode_Versions:
			default:
				CLEAR_SCREEN();
				text0.SetRollText(0, 74, 240, SOFTWARE_VERSION_NUMBER, LanguageList[LanguageListIndex_BigBattery], -10, 0, RollType_Order_Center, 0xFFFF, 0xFFFF);
				break;
		}
		
	}

	return result;
}

void Draw::ExecuteDraw(void)
{
	int result = 0;
	switch(NextState)
	{
		case DrawShowState_PowerOn://��������
			result = DrawPowerOn();
			break;
		
		case DrawShowState_SelectedMode://ģʽѡ�����
			result = DrawSelectedMode();
			break;
		
		case DrawShowState_DustLevel://�ҳ��ȼ�����
			result = DrawDustLevel();
			break;
		
		case DrawShowState_MainMenu://���˵�����
			result = DrawMainMenu();
			break;
		
		case DrawShowState_History://��ʷ���ݽ���
			result = DrawHistory();
			break;
		
		case DrawShowState_ResetFilter://������о����
			result = DrawResetFilter();
			break;
		
		case DrawShowState_LanguageMenu://����ѡ�����
			result = DrawLanguageMenu();
			break;
		
		case DrawShowState_Confirmation://ȷ������ѡ�����
			result = DrawConfirmation();
			break;
	
		case DrawShowState_Recharge://������
			result = DrawRecharge();
			break;
		
		case DrawShowState_HighAltitude://�ߺ��ν���
			result = DrawHighAltitude();
			break;
		
		case DrawShowState_ShowError://���Ͻ���
			result = DrawShowError();
			break;
		
		case DrawShowState_FilterServiceLife://��о������ʾ����
			result = DrawFilterServiceLife();
			break;
		
		case DrawShowState_Lock://����������
			result = DrawLock();
			break;
		
		case DrawShowState_CentralDustCollection:
			result = V2205DrawCdc();
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
		if(uMessage.screenLuminance == SCREEN_LUMINANCE_NORMAL)
		{//��������
			ALLOW_DISPLAY();
		}
	}
}

//ģ����
//ѭ�����ã��Ƽ�ʹ�õ����ȼ���������
//����������Ⱦ���
void Draw::Handle(void)
{
	ExecuteMessage();
	
	DelayCtrl();
	ExecuteDraw();
}
