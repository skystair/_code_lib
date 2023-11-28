#ifndef _V2205_DRAW_H_
#define _V2205_DRAW_H_

#include "Decode.h"

#define SOFTWARE_VERSION_NUMBER		"5"/*����汾��*/
#define TEST_MODE_FUNCTION_ENABLE	0

#define VALID_FLASH_DATA_FLAG		0x55AA55AA/*flash�ڴ洢����Ч��Ϣ��־*/
#define FLASH_DATA_ADDRESS			0x0803D000/*Ԥ��4kB*/
#define FLASH_ERROR_ADDRESS			0x0803E000/*Ԥ��4kB*/

#define DELAY_CHANGE_TO_RUN_MS		3000
#define DELAY_PLAY_LOW_BATTERY		3680
#define DELAY_PLAY_ERROR			3680
#define DELAY_PLAY_FILTER_REPLACE	9160
#define DELAY_PLAY_FILTER_EXPIRE	3680

/* ���������ӿں� */
#define CLEAR_SCREEN()		//ClearScreen(0)//LcdClearScreen(0)//lcd_clear(0);//
#define CLEAR_PART_SCREEN(x_start,y_start,x_end,y_end)	//ClearPartScreen(x_start,y_start,x_end,y_end,0)//LcdClearPartScreen(x_start,y_start,x_end,y_end,0)//
#define ALLOW_DISPLAY()			SET_PWM_DUTY_RATIO(0.75) /*timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 75);*/
#define DARK_SCREEN()			SET_PWM_DUTY_RATIO(0.25) /*timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 25);*/

#define LOAD_NEED_SAVE()		FlashAccessRead((uint8_t*)&(NeedSave), FLASH_DATA_ADDRESS, sizeof(NeedSave))
#define SAVE_NEED_SAVE()		FlashAccessWrite((uint8_t*)&(NeedSave), FLASH_DATA_ADDRESS, sizeof(NeedSave))

#define INIT_TIMESTAMP()		BspRtcInit()/*RTC_Init()*//*���������������1���򷵻�0*/
#define GET_TIMESTAMP()			BspRtcGetTimestamp()//0/*RTC_GetTimestamp()*/


#define V2205Draw_LED_RED_ON		LED_RED_ON
#define V2205Draw_LED_GREEN_ON		LED_GREEN_ON
#define V2205Draw_LED_RED_OFF		LED_RED_OFF
#define V2205Draw_LED_GREEN_OFF		LED_GREEN_OFF

typedef struct{
	unsigned char	header1;				//0xAC
	unsigned char	header2;				//0x03
	unsigned char	header3;				//0x0A
	unsigned char	shift					:4;	//��λ��Ϣ @V2205ShiftInfo
	unsigned char	dustLevel				:4;	//�ҳ��ȼ� @V2205DustLevel
	unsigned char	batteryLevel;			//��ص���
	unsigned char	lockAction				:1;	//�л���������ģʽ @LockAction
	unsigned char	operatingAction			:1;	//����������־ @OperatingAction
	unsigned char	screenLuminance			:1; //��ʾ������λ @ScreenLuminance
	unsigned char	languageConfirmation 	:1;	//����ȷ�϶��� @LanguageConfirmation
	unsigned char	lock					:1;	//��������״̬ @Lock
	unsigned char	languageSetting			:1; //�������ѡ������ @LanguageSetting
	unsigned char	select					:1;	//ѡ����һ������ ��ҪlanguageSetting��λ����Ч ����һ֡��ͬ�л�
	unsigned char	confirm					:1;	//����ȷ�϶��� @Confirm
	unsigned char	errorData;				//������ @ErrorData
	unsigned char	workState;				//����״̬ @WorkState
	unsigned char	filterServiceLife		:4;	//��о���������Ϣ @FilterServiceLife
	unsigned char	filterReset				:4;	//��о�������� @FilterReset
	unsigned char	cleaningRecord			:1;	//��ʷ����¼���� @CleaningRecord
	unsigned char	errorRecord				:1;	//���ϼ�¼ @ErrorRecord
	unsigned char	mainMenu				:1; //һ���˵� @MainMenu
	unsigned char	rollMenu				:3; //���˵�λ�� @RollMenu
	unsigned char							:2;	//δʹ��
	unsigned char	remainingMinute;		//�ҳ��ȼ�����ʣ��ʱ��-��
	unsigned char	remainingSecond;		/*�ҳ��ȼ�����ʣ��ʱ��-��
		0x00~0x3B������
		0xEF����ص����ͣ�����ʱģ������
		ע����ʾ�����յ���һ֡����ʱ����ʱ���Զ�����1S����ʱ���ڵ�λ���������£�ÿ��15Sȥ
		check�µ���ʱ����У׼����λ�ı�ʱ����������ʱ������Դ���1S����ʱ*/
	unsigned char	highAltitudeMode;		/*�ߺ���ģʽ @HighAltitudeMode
		���ߺ���ģʽ�ǳ���ģʽ����3S��������ѡ�������ٳ�����������1S��������˳�����ҪBMS�����ģʽ�������λ����*/
}UartMessage_V1_17;

//V2205ShiftInfo
typedef enum{
	V2205ShiftInfo_None			= 0,//��ʼ״̬�����ڴ�����һ�ν����л�
	V2205ShiftInfo_Low			= 1,//�͵�
	V2205ShiftInfo_Middle		= 2,//�е�
	V2205ShiftInfo_High 		= 3,//�ߵ�
	V2205ShiftInfo_Auto			= 4,//�Զ�
}V2205ShiftInfo;

//V2205DustLevel
typedef enum{
	V2205DustLevel_None     	= 0,//��
	V2205DustLevel_Low			= 1,//��
	V2205DustLevel_Middle		= 2,//��
	V2205DustLevel_High 		= 3,//��
	V2205DustLevel_Max,
}V2205DustLevel;

//LockAction
#define LOCK_ACTION_NONE			0/*���л�*/
#define LOCK_ACTION_SWITCHING		1/*�л��У�������Ч��lock����������ģʽ�л�����bitͬ����1ά��1s��ָ�Ϊ0*/

//OperatingAction
#define OPERATING_ACTION_NONE		0/*Ĭ��״̬*/
#define OPERATING_ACTION_ON			1/*���������µ�Դ����ʹ����Ӿ�ֹ��Ϊ����ʱ��������2֡��*/

//ScreenLuminance
#define SCREEN_LUMINANCE_NORMAL		0/*��������*/
#define SCREEN_LUMINANCE_DARK		1/*�䰵*/

//LanguageConfirmation
#define LANGUAGE_CONFIRM_NONE		0/*δȷ��*/
#define LANGUAGE_CONFIRM_OK			1/*��������ѡ��ȷ�ϵ���ʱ���� ������ʱ��3s�����ֲ��Ŷ�����־��*/

//Lock
#define LOCK_OFF					0/*�ǵ�������*/
#define LOCK_ON						1/*��������״̬*/

//LanguageSetting
#define LANGUAGE_SETTING_ACTIVE		1/*��������ѡ�����*/

//Confirm
#define CONFIRM_SELLECTED_LANGUAGE	1/*ѡ�е�ǰ����*/

//ErrorData
typedef enum{
	ErrorData_None					= 0x00,//�޴������
	ErrorData_BldcUndervoltage		= 0x01,//BLDCǷѹ��UI�������1��--¼�ڹ��ϼ�¼��
	ErrorData_BldcCvervoltage		= 0x02,//BLDC��ѹ��UI�������1��--¼�ڹ��ϼ�¼��
	ErrorData_BldcOverTemperature	= 0x03,//BLDC���£�UI�������1��--¼�ڹ��ϼ�¼��
	ErrorData_BldcOvercurrent		= 0x04,//BLDC������UI�������1��--¼�ڹ��ϼ�¼��
	ErrorData_BldcOverspeed			= 0x05,//BLDC���٣�UI�������1��--¼�ڹ��ϼ�¼��
	ErrorData_BldcOpenPhase			= 0x06,//BLDCȱ�ࣨUI�������1��--¼�ڹ��ϼ�¼��
	ErrorData_TuyereBlocked			= 0x07,//ȫ�·�ڣ�UI���������
	ErrorData_RollerStall			= 0x08,//��ˢ��ת��UI�������ˢ��
	ErrorData_RollerShortOut		= 0x09,//��ˢ��·��UI�������ˢ��
	ErrorData_OverDischargeProtection		= 0x0A,//���ű���
	ErrorData_DischargeOvertemperatureProtection 	= 0x0B,//�ŵ���±�����UI��ع��£�  (�������ŵ����)
	ErrorData_DischargeNoLoadProtection		= 0x0C,//�ŵ���ر�����UI�������2��
	ErrorData_CommunicationTimeout	= 0x0D,//ͨѶ��ʱ�����ܷ�����ȥ����UI�������3��--¼�ڹ��ϼ�¼��
	ErrorData_FilterNotInstalled	= 0x0E,//��оδ��װ��UI��
	ErrorData_Reserve				= 0x0F,//�ŵ����/��·/ /BLDC�ض�ʧ�ܱ�������Ļ�޷���ʾ
	ErrorData_OverchargeProtection	= 0x10,//���䱣��
	ErrorData_ChargerVoltageAbnormal	= 0x11,//�������ѹ�쳣��UI�������4��
	ErrorData_ChargerOvercurrent	= 0x12,//��������UI�������5��
	ErrorData_ChargerTimeout		= 0x13,//��糬ʱ��UI�������6��
	ErrorData_BatteriesFault		= 0x20,//��о���ϣ�UI�������7��--¼�ڹ��ϼ�¼��
	ErrorData_NTCFault				= 0x21,//�¶ȴ�����(NTC)���ϣ�UI�������8��--¼�ڹ��ϼ�¼��
	ErrorData_BMSHardwareFault		= 0x22,//ǰ��ͨѶʧ��(BMSӲ���쳣)��UI�������9��--¼�ڹ��ϼ�¼��
}ErrorData_en;

//WorkState
typedef enum{
	WorkState_Standby 	= 0x00,//����״̬����Ļ���������ת����Ϊ������
	WorkState_Charging 	= 0x01,//���״̬
	WorkState_Work		= 0x02,//�ŵ�״̬
	WorkState_CDC		= 0x03,//���뼯��(central dust collection)
	
	WorkState_Test		= 0xFF,//����ģʽ
}WorkState_en;

//FilterServiceLife
#define FILTER_SERVICE_LIFE_NORMAL		0/*δ����������ʱ��*/
#define FILTER_SERVICE_LIFE_RINSE		1/*������ϴ��о(UI��������о) ��ʹ��*/
#define FILTER_SERVICE_LIFE_REPLACE		2/*���Ѹ�����о(UI�������о)*/
#define FILTER_SERVICE_LIFE_EXPIRE		3/*��о��Ҫ�����뾡����� (UI��о��Ҫ��������)*/

//FilterReset
#define FILTER_RESET_NORMAL				0/*����Ҫ���Ŷ���*/
#define FILTER_RESET_SETING				1/*��о��ʾ�ָ����������У�ȷ����ɣ�*/
#define FILTER_RESET_RESET				2/*�������ܼ�����,�������ö�������ʼ������*/

//CleaningRecord
#define CLEANING_RECORD_SHOW		1/*������ʷ����¼����*/

//ErrorRecord
#define ERROE_RECORD_SHOW			1/*�������ϼ�¼*/

//MainMenu
#define MAIN_MENU_SHOW				1/*����һ���˵�*/

//RollMenu
typedef enum{//��000����001����010����011����000����ѭ����
	RollMenu_CleaningRecord			= 0,//����ʱĬ��Ϊ000(��ʷ����¼)����һ�ΰ�����000תΪ001
	RollMenu_ResetFilter			= 1,//�������ã���һ�ΰ�����000תΪ001
	RollMenu_SelectLanguage			= 2,//����ѡ�񣬰�һ�ΰ�����001תΪ010
	RollMenu_Exit					= 3,//�˳�����һ�ΰ�����010תΪ011
	RollMenu_None,
}RollMenu_en;

//HighAltitudeMode
#define HIGH_ALTITUDE_MODE_NONE			0/*�ޱ仯*/
#define HIGH_ALTITUDE_MODE_ENTERING  	1/*����ߺ���ģʽ��UI��ʾ���붯�������У�����ʱ��ʼ��*/
#define HIGH_ALTITUDE_MODE_ENTERED		2/*����ߺ���ģʽȷ����ɣ�UI��ʾ���붯������ȷ����ɣ�*/
#define HIGH_ALTITUDE_MODE_EXITING	 	3/*�˳��ߺ���ģʽ��UI��ʾ�˳����������У�����ʱ��ʼ��*/
#define HIGH_ALTITUDE_MODE_EXITED		4/*�˳��ߺ���ģʽȷ����ɣ�UI��ʾ�˳���������ȷ����ɣ�*/

typedef enum{
	LanguageOptions_Min = 0,
	LanguageOptions_SimplifiedChinese	= 0,//��������
	LanguageOptions_English				= 1,//Ӣ��
	LanguageOptions_ChineseTraditional	= 2,//��������	
	LanguageOptions_Japanese			= 3,//����
	LanguageOptions_Korean				= 4,//����
	LanguageOptions_German				= 5,//����
	LanguageOptions_French				= 6,//����
	LanguageOptions_Italian				= 7,//�������
	LanguageOptions_Spanish				= 8,//��������
	LanguageOptions_Russian				= 9,//����
	LanguageOptions_Arabic				= 10,//��������
	LanguageOptions_Hebrew				= 11,//ϣ������
	LanguageOptions_Max = LanguageOptions_English,
}V2205DrawLanguageOptions;

typedef enum { V2205Bool_FALSE = 0, V2205Bool_TRUE = !V2205Bool_FALSE, } V2205Bool;

typedef enum{
	DrawShowState_Min					=0 ,	//��Ч��Χ�±߽�
	
	DrawShowState_None = DrawShowState_Min,		//��ʼ���棬���ڴ�����һ�ν����л�
	DrawShowState_PowerOn				= 1,	//��������
	DrawShowState_SelectedMode			= 2,	//ģʽѡ�����
	DrawShowState_DustLevel				= 3,	//�ҳ��ȼ�����	
	DrawShowState_MainMenu				= 4,	//���˵�����	
	DrawShowState_History				= 5,	//��ʷ���ݽ���
	DrawShowState_ResetFilter			= 6,	//������о����
	DrawShowState_LanguageMenu			= 7,	//����ѡ�����
	DrawShowState_Confirmation			= 8,	//ȷ������ѡ�����
	
	DrawShowState_Recharge				= 9,	//������
	DrawShowState_Lock					= 10,	//����������
	DrawShowState_ShowError				= 11,	//���Ͻ���
	
	DrawShowState_HighAltitude			= 12,	//�ߺ��ν���
	DrawShowState_FilterServiceLife		= 13,	//��о������ʾ����
	DrawShowState_CentralDustCollection = 14,	//���뼯��ҳ��
	
	DrawShowState_TestMode,						//����ҳ��
	DrawShowState_Max,							//��Ч��Χ�ϱ߽�
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
	UartMessage_V1_17 Message;//���Ľ����ṹ��

	/*��־���ڲ�����*/
	union{
		struct{
			unsigned int RefreshFlag		:1;//���±���
			unsigned int StartExecute   	:1;//��ʼ�������ı�־
			unsigned int DirtyDta			:1;//�����ݱ�־
			unsigned int PowerOn			:1;//�ѿ�����־
			unsigned int ChangeLangeuage	:1;//���������л� �޸�Ϊ���µ�����
			unsigned int InitLowBattery		:1;//������״̬������־
			
			unsigned int ShowDuty			:1;//������ʾ�ҳ��ȼ�
			unsigned int comfirmLangeuage	:1;//����ȷ������ѡ��
			unsigned int ResetFilter		:1;//������оȷ�ϱ�־
			unsigned int NeedStore			:1;//flash������Ҫ�洢
			unsigned int Locking			:1;//���ڲ���������
			unsigned int StartPlaying		:1;//��ʼ��˸-�ɴ��
			unsigned int Playing			:1;//������˸-�ɴ��
			unsigned int StartStrongPlaying	:1;//��ʼ��˸-���ɴ��
			unsigned int StrongPlaying		:1;//������˸-���ɴ��
			
			unsigned int LowBattery			:1;//����������ʾ��־
			unsigned int LowBatteryPage		:1;//�����Ͷ����Ѳ��ű�־
		}bit;
		unsigned int All;
	}FlagContainers;
	
	/* ��ʱ���� */
	unsigned int DrawTickCount;//������������
	unsigned int CtrlTickCount;//������������
	
	unsigned int CurrentTimestamp;//��������������ʼʱ���
	
	unsigned int ShowDustDelay_Timestamp;
	unsigned int ShowDustDelay_Limit;
	unsigned int PlayingDelay_Timestamp;
	unsigned int PlayingDelay_Limit;
	
	DelayFlag_en ShowDustDelay;//����ʾ�ҳ��ȼ�ҳ�����ʱ״̬
	//DelayFlag_en ErrorShowDelay;//������ʾ��ʱ״̬
	DelayFlag_en PlayingDelay;//������ʱ
	
	MotorState_en MotorState;
	/*��ʾ״̬*/	
	V2205ShiftInfo CurrentShift;//��ǰ������ʾ�ĵ�λ
	V2205ShiftInfo NewShift;
	V2205Bool LockState;//��״̬
	
	unsigned char WorkState;//��ǰ����״̬
	unsigned char WorkStatePrve;//ǰһ������״̬
	
	ErrorData_en ErrorData;
	short ContinuousPictureIndex;//����ͼƬ����
	short ContinuousPictureStep;//������
	/* ҳ��״̬��־ ÿ��ͼƬ��Ӧһ����־*/
	//ģʽѡ��ҳ��
	union{
		struct{
			unsigned char clear		:1;//�����Դ���ٻ���---���ڴ���������ҳ���л�����
			unsigned char Mode		:1;//�л���λ
			unsigned char lock		:1;//��״̬��
			unsigned char battery	:1;//���ͼ��
		}bit;
		unsigned char all;
	}SelectedModeFlag;
	V2205ShiftInfo LoopShift;
	//�ҳ��ȼ�����
	union{
		struct{
			unsigned char clear		:1;//�����Դ���ٻ���---���ڴ���������ҳ���л�����
			unsigned char lock		:1;//����־
			unsigned char shift		:1;//��λͼ��
			unsigned char battery	:1;//���ͼ��			
		}bit;
		unsigned char all;
	}DustLevelFlag;
	unsigned char DustLevel;//��ǰ�ҳ��ȼ�
	//���˵�
	union{
		struct{
			unsigned char clear		:1;//�����Դ���ٻ���---���ڴ���������ҳ���л�����
			unsigned char showAll 	:1;//ǿ����ʾȫ��
			unsigned char selected 	:1;//��ѡ����仯
		}bit;
		unsigned char all;
	}MainMenuFlag;
	RollMenu_en MainMenu;		//��¼��ǰѡ�в˵���
	RollMenu_en MainMenuPrve;	//ǰһ���˵�ѡ��ѡ��
	//��ʷ��¼
	union{
		struct{
			unsigned char clear		:1;//�����Դ���ٻ���---���ڴ���������ҳ���л�����
			unsigned char show 		:1;//��ʾ��ʷ����
		}bit;
		unsigned char all;
	}HistoryFlag;
	//������о
	union{
		struct{
			unsigned char clear		:1;//�����Դ���ٻ���---���ڴ���������ҳ���л�����
			unsigned char show 		:1;//��ʾ��ʷ����
		}bit;
		unsigned char all;
	}ResetFilterFlag;
	//����ѡ�����
	union{
		struct{
			unsigned char clear			:1;//�����Դ���ٻ���---���ڴ���������ҳ���л�����
			unsigned char selected 		:1;//��������ѡ�����
		}bit;
		unsigned char all;
	}LanguageMenuFlag;
	unsigned char lastLanguageSelect;
	
	V2205DrawLanguageOptions NewLanguage;//�˵���ѡ�е�����
	//����ȷ�Ͻ���
	union{
		struct{
			unsigned char clear			:1;//�����Դ���ٻ���---���ڴ���������ҳ���л�����
			unsigned char show 			:1;//��ʼ����ȷ�Ͻ���
		}bit;
		unsigned char all;
	}ConfirmationFlag;
	//������
	union{
		struct{
			unsigned char clear			:1;//�����Դ���ٻ���---���ڴ���������ҳ���л�����
			unsigned char battery 		:1;//�������䷢���仯
		}bit;
		unsigned char all;
	}RechargeFlag;
	unsigned char batteryLevel;
//	unsigned char lastBatteryLevel;
	//�ߺ��ν���
	union{
		struct{
			unsigned char clear			:1;//�����Դ���ٻ���---���ڴ���������ҳ���л�����
			unsigned char show 			:1;//�������䷢���仯
		}bit;
		unsigned char all;
	}HighAltitudeFlag;
	unsigned char HighAltitudeMode;//��¼��ǰ�ĸߺ���ģʽ
	//���Ͻ���
	union{
		struct{
			unsigned char clear			:1;//�����Դ���ٻ���---���ڴ���������ҳ���л�����
			unsigned char show 			:1;//�������䷢���仯
		}bit;
		unsigned char all;
	}ShowErrorFlag;
	
	//�����ͽ���
	union{
		struct{
			unsigned char clear			:1;//�����Դ���ٻ���---���ڴ���������ҳ���л�����
			unsigned char show 			:1;//�������䷢���仯
		}bit;
		unsigned char all;
	}LowBatteryFlag;
	LowBatteryWarning_t LowBatteryWarning;
	
	//��о������ʾ����
	union{
		struct{
			unsigned char clear			:1;//�����Դ���ٻ���---���ڴ���������ҳ���л�����
			unsigned char show 			:1;//�������䷢���仯
		}bit;
		unsigned char all;
	}FilterServiceLifeFlag;
	unsigned char FilterServiceLife;
	
	//����������
	union{
		struct{
			unsigned char clear			:1;//�����Դ���ٻ���---���ڴ���������ҳ���л�����
			unsigned char show 			:1;//�������䷢���仯
		}bit;
		unsigned char all;
	}LockFlag;
	
	union{
		struct{
			unsigned char clear			:1;//�����Դ���ٻ���---���ڴ���������ҳ���л�����
			unsigned char show 			:1;//
		}bit;
		unsigned char all;
	}CDCFlag;
	unsigned char CdcLoopCount;
	
	union{
		struct{
			unsigned char show			:1;//��Ҫˢ��һ�α�־
		}bit;
		unsigned char all;
	}TestModeFlag;
	TestMode_en TestMode;
	
	DrawMainShowState PrevState;//ǰһ��ҳ��
	DrawMainShowState NextState;//��һ��ҳ��

	struct{
		//CurveDrawData_st CurveDrawData;		
		unsigned int CheckFlag;
		unsigned int HistoryTimestamp;//��ʷ����ʱ���--�����е�����һ��	
		float History[7];//��ʷ��¼
		V2205DrawLanguageOptions Language;//��ǰ����			
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

