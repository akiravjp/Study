/**********************************************************************
Դ��������: sdk_demo.cpp
�������Ȩ: �������ӹɷ����޹�˾
ϵͳ����  : 06���ڻ�ϵͳ
ģ������  : �����ڻ���Ϣ���Ľӿ�
����˵��  : HsFutuSDKʾ������
��    ��  : xdx
��������  : 20110315
��    ע  : HsFutuSDKʾ������
�޸���Ա  ��
�޸�����  ��
�޸�˵��  : 20110315 ����
**********************************************************************/
//#include <vld.h>
#include <iostream>
#include <string>
#include <iomanip>
#include "futu_data_types.h"
#include "futu_message_interface.h"
#include "futu_sdk_interface.h"
#include "stdafx.h"

using namespace  std;

#ifdef _WIN32
#   include <conio.h>
#   include <windows.h>
#   ifdef _DEBUG
#      pragma comment(lib,"HsFutuSDK.lib")
#   else
#      pragma comment(lib,"HsFutuSDK.lib")
#   endif

///�߾��ȼ�ʱ��,��λ����
class CTimeCounter
{
public:
	//���캯��
	CTimeCounter(){ QueryPerformanceFrequency(&hz); }
	//��ʼ��ʱ
	inline void Start(){ QueryPerformanceCounter(&rs); }
	//�ӿ�ʼ��ʱ��ȥ��ʱ��
	inline long double Elapse()
	{
		return ((now.QuadPart - rs.QuadPart) / (long double)hz.QuadPart) * 1000;
	}
	inline void Stop(){ QueryPerformanceCounter(&now); }
private:
	LARGE_INTEGER hz;
	LARGE_INTEGER rs;
	LARGE_INTEGER now;
};

//�Զ������߳����
HANDLE        g_hEvent = NULL;
volatile int  g_iType = 0;
volatile bool g_bStop = false;
//�����̺߳���

DWORD WINAPI auto_connect(void* lpParam)
{
	IHsFutuComm* lpComm = (IHsFutuComm*)lpParam;
	while (!g_bStop)
	{
		if (WAIT_OBJECT_0 == WaitForSingleObject(g_hEvent, INFINITE))
		{
			//�˳�
			if (g_bStop)
			{
				cout << "�Զ������߳��˳�!" << endl;
				return 0;
			}

			cout << "������Ӷ˿�,��ʼ�Զ�����......" << endl;
			//����
			for (int iRet = 0;;)
			{
				if (0 == (iRet = lpComm->Start(g_iType)))
				{
					ResetEvent(g_hEvent);
					break;
				}
				cout << "�߳��Զ�����ʧ��:" << lpComm->GetErrorMsg(iRet) << endl;
				//����ʧ��,��ͣһ�������
				Sleep(1000);
			}
		}
	}
	cout << "�Զ������߳��˳�!" << endl;
	return 0;
}
#define pause _getch
#else //end _WIN32
#include <sys/time.h>
class CTimeCounter
{
public:
	inline void Start(){ gettimeofday(&tv1, NULL); }
	inline void Stop(){ gettimeofday(&tv2, NULL); }
	inline long double Elapse()
	{
		return (tv2.tv_sec - tv1.tv_sec) * 1000 + (tv2.tv_usec - tv1.tv_usec) / 1000.0f;
	}
private:
	timeval tv1, tv2;
};
#define pause getchar
#endif//end #else


//ȫ�ֱ���
CTimeCounter g_Counter;

#define USER_NAME "100001"
#define USER_PWD  "111111"

//������ں���
void test_case(IFuMessage* lpReqMsg);

//��ʾ������Ϣ
void ShowFuMessage(IFuMessage* lpMessage)
{
	cout << "======================<<IFuMessage BEGIN>>=====================" << endl;
	cout << "nRecords:" << lpMessage->GetCount()
		<< " MsgType:" << lpMessage->GetMsgType()
		<< ((lpMessage->GetCount() <= 0) ? " (Ӧ������Ϊ��)" : "") << endl;
	for (int i = 0; i<lpMessage->GetCount(); ++i)
	{
		IFuRecord* lpRecord = lpMessage->GetRecord(i);
		cout << "Record [" << i + 1 << "]:" << endl;
		for (lpRecord->MoveFirst(); !lpRecord->IsEOF(); lpRecord->MoveNext())
		{
			const char* strField = lpRecord->GetFieldName();
			cout.width(20);
			cout << strField << " : " << lpRecord->GetString(strField) << endl;
		}
		cout << endl;
	}
	cout << "=======================<<IFuMessage END>>======================" << endl;
}


//�첽�ص��ӿڵ�ʵ��
class CMyCallBack :public IFuCallBack
{
public:
	//�ӿڲ�ѯ
	unsigned long  HSAPI QueryInterface(const char *, IHSKnown **){ return 0; }
	//���ýӿڣ����ü�����һ
	unsigned long  HSAPI AddRef(){ return 0; }
	//�ͷŽӿڣ����ü�����һ������Ϊ0ʱ�ͷŽӿڵ�ʵ�ֶ���
	unsigned long  HSAPI Release(){ return 0; }
	//����״̬�ĸı�
	void HSAPI OnNotifyConnState(IHsFutuComm* lpComm, int iType, int iStatus, const char* szNotifyTime, const char* szMessage)
	{
		cout << "ͨ��״̬�ı�:" << iType << " : " << setw(2) << iStatus << " : " << szNotifyTime << " : " << szMessage << endl;
#ifdef _WIN32
		if ((iStatus == 0) && !g_bStop)//���ӶϿ���
		{
			g_iType = iType;
			SetEvent(g_hEvent);
		}
#else

#endif
	}

	//��½����
	void HSAPI OnRspLogin(IHsFutuComm* lpComm, IFuMessage* lpMsg)
	{
		cout << "��½����:" << lpMsg->GetRecord()->GetCount() << endl;
		lpMsg->AddRef();
		ShowFuMessage(lpMsg);
	}

	//�ǳ�����
	void HSAPI OnRspLogout(IHsFutuComm* lpComm, IFuMessage* lpMsg)
	{
		cout << "�ǳ�����:" << endl;
		ShowFuMessage(lpMsg);
	}

	//���巴��
	void  HSAPI OnRspSubResult(IHsFutuComm* lpComm, REGType sType, REGAction aType, int iResult, const char* lpParam, const char* szMessage)
	{
		cout << "���Ľ������:type=" << sType << " action=" << aType << " result=" << iResult << " param=" << (lpParam ? lpParam : "(null)") << " message=" << szMessage << endl;
	}

	//���յ�ҵ��Ӧ����Ϣ
	void HSAPI OnReceivedBiz(IHsFutuComm* lpComm, IFuMessage* lpAnsData, int iRet, int iKeyID)
	{
		g_Counter.Stop();
		cout << "�յ�ҵ����Ϣ���첽�����ʱ:" << g_Counter.Elapse() << " iRet=" << iRet << "KeyID=" << iKeyID << endl;
		ShowFuMessage(lpAnsData);
	}

	//���յ������г�����
	void HSAPI OnRecvMarketData(IHsFutuComm* lpComm, CMarketInfo* lpInfo, REGAction rAction)
	{
		cout << "��������:(" << lpInfo->futu_exch_type << ":" << lpInfo->contract_code << ")" << endl;
	}

	//���յ�����г�����
	void HSAPI OnRecvArgMarketData(IHsFutuComm* lpComm, CArgMarketInfo* lpInfo, REGAction rAction)
	{
		cout << "�������:(" << lpInfo->futu_exch_type << ":" << lpInfo->arbicontract_id << ")" << endl;
	}

	//���յ�ί�з�����Ϣ
	void HSAPI OnRecvOrderInfo(IHsFutuComm* lpComm, const COrderRspInfo* lpInfo)
	{
		cout << "ί�з���:(fund_account=" << lpInfo->fund_account << " : entrust_no=" << lpInfo->entrust_no << ")" << endl;
	}

	//���յ��ɽ�����
	void HSAPI OnRecvOrderRealInfo(IHsFutuComm* lpComm, const CRealRspInfo* lpInfo)
	{
		cout << "�ɽ�����:(";
		cout << "fund_account=" << lpInfo->fund_account << ";";
		cout << " entrust_no=" << lpInfo->entrust_no << ";";
		cout << "entrust_bs=" << lpInfo->entrust_bs << ";";
		cout << "entrust_direction=" << lpInfo->entrust_direction << ";";
		cout << "hedge_type=" << lpInfo->hedge_type << ";";
		cout << "futu_exch_type=" << lpInfo->futu_exch_type;
		cout << ")" << endl;

	}

	//����������Ϣ
	void HSAPI OnRspOnlineMsg(IHsFutuComm* lpComm, const char* szUsrID, const char* szMessage)
	{
		cout << "������Ϣ:(user=" << (szUsrID ? szUsrID : "(null)") << " message=" << szMessage << ")" << endl;
	}
};


//���������
int main(void)
{
	cout << "************************************************************" << endl;
	cout << "***                                                      ***" << endl;
	cout << "***    HsFutuSDK DEMO by HUNDSUN (" << __DATE__ << "-" << __TIME__ << ")  ***" << endl;
	cout << "***              SDK Version:0x" << hex << GetSDKVersion() << dec << "                  ***" << endl;
	cout << "***                                                      ***" << endl;
	cout << "************************************************************" << endl;
	//cout<<"ProcessID:"<<GetCurrentProcessId()<<" ThreadID:"<<GetCurrentThreadId()<<endl;

	//���dll�İ汾�ǽӿ������İ汾����Ϸ�
	if (HSFUSDK_VERSION != GetSDKVersion())
	{
		cout << "ע�⣺�ӿڵ�ͷ�ļ��汾[0x" << hex << HSFUSDK_VERSION << "]���汾[0x" << GetSDKVersion() << "]������,���ܵ��¼����Դ���!" << endl;
		return -1;
	}
	//�½�ͨ�Ŷ���
	IHsFutuComm* lpComm = NewFuCommObj(NULL);//FUTU_SYSTEM_V06,FUTU_SYSTEM_UFT

#ifdef _WIN32
	g_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	//�����Զ������߳�
	HANDLE hThread = CreateThread(NULL, 0, auto_connect, lpComm, 0, NULL);
#else

#endif
	//���ò���
	lpComm->SetConfig("futu", "server", "127.0.0.1:2800");
	lpComm->SetConfig("futu", "biz_license_str", "31332263F984F25D4A1ADEFEC3");
	lpComm->SetConfig("futu", "comm_license_file", "C:\\yfq_license.dat");
	lpComm->SetConfig("futu", "entrust_type", "L");//ί�з�ʽ

	//��ʼ���ӿڶ���
	CMyCallBack callback;
	int iRet = 0;
	if (0 != (iRet = lpComm->Init(&callback)))
	{
		cout << "��ʼ��ʧ��.iRet=" << iRet << " msg:" << lpComm->GetErrorMsg(iRet) << endl;
		lpComm->Release();
		return -1;
	}
	//����(��Ϣ����)
	if (0 != (iRet = lpComm->Start(SERVICE_TYPE_QUOTE)))
	{
		cout << "����ʧ��.iRet=" << iRet << " msg:" << lpComm->GetErrorMsg(iRet) << endl;
		lpComm->Release();
		return -1;
	}

	pause();


	//����(����) 
	if (0 != (iRet = lpComm->Start(SERVICE_TYPE_TRADE)))
	{
		cout << "����ʧ��.iRet=" << iRet << " msg:" << lpComm->GetErrorMsg(iRet) << endl;
		lpComm->Release();
		return -1;
	}


	pause();

	//��½
	if (0 != (iRet = lpComm->DoLogin(USER_NAME, USER_PWD, 1)))
	{
		cout << "��½ʧ��.iRet:" << iRet << " msg:" << lpComm->GetErrorMsg(iRet) << endl;
		lpComm->Release();
		return -1;
	}


	//��DoLoginEx��¼
	/*
	IFuMessage* lpLoginMsg=NewFuMessage(MSG_TYPE_USER_LOGIN,MSG_MODE_ANSWER);
	if(0 != (iRet = lpComm->DoLoginEx(USER_NAME,USER_PWD,lpLoginMsg,0)))
	{
	cout<<"��½ʧ��.iRet:"<<iRet<<" msg:"<<lpComm->GetErrorMsg(iRet)<<endl;
	lpComm->Release();
	return -1;
	}
	cout<<"��½����:"<<lpLoginMsg->GetRecord()->GetCount()<<endl;
	lpLoginMsg->AddRef();
	ShowFuMessage(lpLoginMsg);
	lpLoginMsg->Release();
	*/
	pause();
	//lpComm->DoLogin("20033",USER_PWD);
	pause();
	//lpComm->DoLogin("20035",USER_PWD);
	pause();

	//����һ��������߻ر�
	lpComm->SubscribeRequest(SingleCode, Subscription, "ALLWWW");
	//lpComm->SubscribeRequest(SingleCode,Subscription,"CF205");
	lpComm->SubscribeRequest(RspReport, Subscription, USER_NAME);
	//lpComm->SubscribeRequest(CombinCode,Subscription,"ALLWWW");
	//lpComm->SubscribeRequest(OnlineMsg,Subscription,USER_NAME);

	pause();
	/*
	//ҵ�����ί���µ�
	IFuMessage* lpReqMsg = NewFuMessage(MSG_TYPE_NEW_SINGLE_ORDER,MSG_MODE_REQUEST); //ί���µ�
	IFuMessage* lpAnsMsg = NewFuMessage();     //������Ϣ(�޹���Ϣ���ͺ�ģʽ,SDK�����������)

	//����������(�ֶ�˳���޹�,�ظ������ֶ��򸲸���ֵ)
	IFuRecord* lpRecord = lpReqMsg->AddRecord();
	lpRecord->SetString("fund_account",USER_NAME);
	lpRecord->SetString("password",USER_PWD);
	lpRecord->SetString("futu_exch_type","F1");
	lpRecord->SetString("futures_account","");
	lpRecord->SetString("contract_code","TA110");
	lpRecord->SetString("entrust_bs","2");
	lpRecord->SetString("futures_direction","1");
	lpRecord->SetString("hedge_type","0");
	lpRecord->SetString("futu_entrust_prop","0");
	lpRecord->SetString("futu_entrust_price","9160.0");
	lpRecord->SetString("entrust_amount","1");
	lpRecord->SetString("entrust_kind","0");
	//lpRecord->SetString("volume_condition","0");
	CTimeCounter t1;
	t1.Start();
	//ͬ��������Ϣ
	iRet = lpComm->SyncSendRecv(lpReqMsg,lpAnsMsg);
	t1.Stop();
	cout<<"ͬ��ί�к�ʱ:"<<":"<<t1.Elapse()<<endl;
	if(iRet != 0)
	{
	cout<<"ͬ��ί��ʧ��:iRet="<<iRet<<" msg:"<<lpComm->GetErrorMsg(iRet)<<endl;
	}
	else
	{
	cout<<"ͬ��ί�гɹ�!"<<endl;
	}
	ShowFuMessage(lpAnsMsg);

	//���ί�д�����
	IFuMessage* lpCheckCombinReqMsg = NewFuMessage(MSG_TYPE_CHECK_COMBIN_CODE,MSG_MODE_REQUEST); //ί���µ�
	IFuMessage* lpCheckCombinAnsMsg = NewFuMessage();     //������Ϣ(�޹���Ϣ���ͺ�ģʽ,SDK�����������)

	//����������(�ֶ�˳���޹�,�ظ������ֶ��򸲸���ֵ)
	IFuRecord* lpCheckCombinRecord = lpCheckCombinReqMsg->AddRecord();
	lpCheckCombinRecord->SetString("fund_account",USER_NAME);
	lpCheckCombinRecord->SetString("futu_exch_type","F1");
	lpCheckCombinRecord->SetString("futures_account","");
	lpCheckCombinRecord->SetString("contract_code","CF109");
	lpCheckCombinRecord->SetString("entrust_bs","1");
	lpCheckCombinRecord->SetString("futures_direction","1");
	lpCheckCombinRecord->SetString("second_code","CF111");
	lpCheckCombinRecord->SetString("arbitrage_code","CF109&CF111");
	CTimeCounter t2;
	t2.Start();
	//ͬ��������Ϣ
	iRet = lpComm->SyncSendRecv(lpCheckCombinReqMsg,lpCheckCombinAnsMsg);
	t2.Stop();
	cout<<"ͬ��ί�к�ʱ:"<<":"<<t2.Elapse()<<endl;
	if(iRet != 0)
	{
	cout<<"ͬ��ί��ʧ��:iRet="<<iRet<<" msg:"<<lpComm->GetErrorMsg(iRet)<<endl;
	}
	else
	{
	cout<<"ͬ��ί�гɹ�!"<<endl;
	}
	ShowFuMessage(lpCheckCombinAnsMsg);
	lpCheckCombinReqMsg->Release();
	lpCheckCombinAnsMsg->Release();

	pause();
	*/

	//�ֲֲ�ѯ
	IFuMessage* lpReqMsgHOLD = NewFuMessage(MSG_TYPE_GET_HOLDSINFO, MSG_MODE_REQUEST); //ί���µ�
	IFuMessage* lpAnsMsgHOLD = NewFuMessage();  //������Ϣ(�޹���Ϣ���ͺ�ģʽ,SDK�����������)
	IFuRecord*  lpRecordHOLD = lpReqMsgHOLD->AddRecord();
	lpRecordHOLD->SetString("fund_account", USER_NAME);
	lpRecordHOLD->SetString("begin_date", "20120202");
	lpRecordHOLD->SetString("end_date", "20120206");
	lpRecordHOLD->SetString("money_type", "0");
	lpRecordHOLD->SetString("total_type", "1");

	CTimeCounter tHOLD;
	tHOLD.Start();
	lpComm->SyncSendRecv(lpReqMsgHOLD, lpAnsMsgHOLD);
	tHOLD.Stop();
	cout << "ͬ��ί�к�ʱ:" << ":" << tHOLD.Elapse() << endl;
	ShowFuMessage(lpAnsMsgHOLD);

	lpReqMsgHOLD->Release();
	lpAnsMsgHOLD->Release();

	pause();

	/*
	//���ί���µ�
	IFuMessage* lpReqMsg = NewFuMessage(MSG_TYPE_NEW_COMBIN_ORDER,MSG_MODE_REQUEST); //ί���µ�
	IFuMessage* lpAnsMsg = NewFuMessage();     //������Ϣ(�޹���Ϣ���ͺ�ģʽ,SDK�����������)

	//����������(�ֶ�˳���޹�,�ظ������ֶ��򸲸���ֵ)
	IFuRecord* lpRecord = lpReqMsg->AddRecord();
	lpRecord->SetString("fund_account",USER_NAME);
	lpRecord->SetString("futu_exch_type","F1");
	lpRecord->SetString("futures_account","");
	lpRecord->SetString("contract_code","CF109");
	lpRecord->SetString("entrust_bs","1");
	lpRecord->SetString("futures_direction","1");
	lpRecord->SetString("hedge_type","0");
	lpRecord->SetString("futu_entrust_prop","7");
	lpRecord->SetString("futu_entrust_price","0");
	lpRecord->SetString("entrust_amount","1");
	lpRecord->SetString("spring_price","0");
	lpRecord->SetString("time_condition","3");
	lpRecord->SetString("valid_date","0");
	lpRecord->SetString("second_code","CF111");
	lpRecord->SetString("volume_condition","0");
	lpRecord->SetString("weave_type","7");
	lpRecord->SetString("arbitrage_code","CF109&CF111");
	CTimeCounter t1;
	t1.Start();
	//ͬ��������Ϣ
	iRet = lpComm->SyncSendRecv(lpReqMsg,lpAnsMsg);
	t1.Stop();
	cout<<"ͬ��ί�к�ʱ:"<<":"<<t1.Elapse()<<endl;
	if(iRet != 0)
	{
	cout<<"ͬ��ί��ʧ��:iRet="<<iRet<<" msg:"<<lpComm->GetErrorMsg(iRet)<<endl;
	}
	else
	{
	cout<<"ͬ��ί�гɹ�!"<<endl;
	}
	ShowFuMessage(lpAnsMsg);

	//�ͷ���Ϣ
	lpReqMsg->Release();
	lpAnsMsg->Release();

	pause();
	*/
	/*
	//��ѯ��ϴ���
	IFuMessage* lpGetCombinCodeReqMsg = NewFuMessage(MSG_TYPE_GET_COMBIN_CODE,MSG_MODE_REQUEST); //ί���µ�
	IFuMessage* lpGetCombinCodeAnsMsg = NewFuMessage();     //������Ϣ(�޹���Ϣ���ͺ�ģʽ,SDK�����������)

	//����������(�ֶ�˳���޹�,�ظ������ֶ��򸲸���ֵ)
	IFuRecord* lpGetCombinCodeRecord = lpGetCombinCodeReqMsg->AddRecord();
	lpGetCombinCodeRecord->SetString("fund_account",USER_NAME);
	lpGetCombinCodeRecord->SetString("futu_exch_type","F1");
	lpGetCombinCodeRecord->SetString("request_num","");
	CTimeCounter t3;
	t3.Start();
	//ͬ��������Ϣ
	iRet = lpComm->SyncSendRecv(lpGetCombinCodeReqMsg,lpGetCombinCodeAnsMsg);
	t3.Stop();
	cout<<"ͬ��ί�к�ʱ:"<<":"<<t3.Elapse()<<endl;
	if(iRet != 0)
	{
	cout<<"ͬ��ί��ʧ��:iRet="<<iRet<<" msg:"<<lpComm->GetErrorMsg(iRet)<<endl;
	}
	else
	{
	cout<<"ͬ��ί�гɹ�!"<<endl;
	}
	ShowFuMessage(lpGetCombinCodeAnsMsg);

	//�ͷ���Ϣ
	lpGetCombinCodeReqMsg->Release();
	lpGetCombinCodeAnsMsg->Release();

	pause();
	*/

	/*
	//��ѯ�������
	IFuMessage* lpGetCombinQuoteReqMsg = NewFuMessage(MSG_TYPE_GET_COMBIN_QUOTE,MSG_MODE_REQUEST); //ί���µ�
	IFuMessage* lpGetCombinQuoteAnsMsg = NewFuMessage();     //������Ϣ(�޹���Ϣ���ͺ�ģʽ,SDK�����������)

	//����������(�ֶ�˳���޹�,�ظ������ֶ��򸲸���ֵ)
	IFuRecord* lpGetCombinQuoteRecord = lpGetCombinQuoteReqMsg->AddRecord();
	lpGetCombinQuoteRecord->SetString("fund_account",USER_NAME);
	lpGetCombinQuoteRecord->SetString("futu_exch_type","");
	lpGetCombinQuoteRecord->SetString("arbicontract_id","");
	CTimeCounter t4;
	t4.Start();
	//ͬ��������Ϣ
	iRet = lpComm->SyncSendRecv(lpGetCombinQuoteReqMsg,lpGetCombinQuoteAnsMsg);
	t4.Stop();
	cout<<"ͬ��ί�к�ʱ:"<<":"<<t4.Elapse()<<endl;
	if(iRet != 0)
	{
	cout<<"ͬ��ί��ʧ��:iRet="<<iRet<<" msg:"<<lpComm->GetErrorMsg(iRet)<<endl;
	}
	else
	{
	cout<<"ͬ��ί�гɹ�!"<<endl;
	}
	ShowFuMessage(lpGetCombinQuoteAnsMsg);

	//�ͷ���Ϣ
	lpGetCombinQuoteReqMsg->Release();
	lpGetCombinQuoteAnsMsg->Release();

	pause();
	*/
	/*
	//У������
	IFuMessage* lpGetCheckPwdReqMsg = NewFuMessage(MSG_TYPE_CHECK_PWD,MSG_MODE_REQUEST); //ί���µ�
	IFuMessage* lpGetCheckPwdAnsMsg = NewFuMessage();     //������Ϣ(�޹���Ϣ���ͺ�ģʽ,SDK�����������)

	//����������(�ֶ�˳���޹�,�ظ������ֶ��򸲸���ֵ)
	IFuRecord* lpGetCheckPwdRecord = lpGetCheckPwdReqMsg->AddRecord();
	lpGetCheckPwdRecord->SetString("fund_account",USER_NAME);
	lpGetCheckPwdRecord->SetString("password",USER_PWD);
	CTimeCounter t5;
	t5.Start();
	//ͬ��������Ϣ
	iRet = lpComm->SyncSendRecv(lpGetCheckPwdReqMsg,lpGetCheckPwdAnsMsg);
	t5.Stop();
	cout<<"ͬ��ί�к�ʱ:"<<":"<<t5.Elapse()<<endl;
	if(iRet != 0)
	{
	cout<<"ͬ��ί��ʧ��:iRet="<<iRet<<" msg:"<<lpComm->GetErrorMsg(iRet)<<endl;
	}
	else
	{
	cout<<"ͬ��ί�гɹ�!"<<endl;
	}
	ShowFuMessage(lpGetCheckPwdAnsMsg);

	//�ͷ���Ϣ
	lpGetCheckPwdReqMsg->Release();
	lpGetCheckPwdAnsMsg->Release();
	*/
	/*if(0 == iRet)
	{
	//��������
	cout<<"Press any key to cancel an order....."<<endl;
	pause();
	lpRecord->Clear();
	lpReqMsg->SetMsgType(MSG_TYPE_CANCEL_ORDER,MSG_MODE_REQUEST);

	lpRecord->SetString("entrust_no",lpAnsMsg->GetRecord()->GetString("entrust_no"));   //ί�к�
	lpRecord->SetString("fund_account",USER_NAME);
	lpRecord->SetString("password",USER_PWD);

	//�첽������Ϣ
	lpAnsMsg->Clear();
	iRet = lpComm->SyncSendRecv(lpReqMsg,lpAnsMsg);
	if(0 != iRet)
	{
	cout<<"����ʧ��:iRet="<<iRet<<" msg:"<<lpComm->GetErrorMsg(iRet)<<endl;
	}
	else
	{
	cout<<"���ɹ�,Show"<<endl;
	}
	ShowFuMessage(lpAnsMsg);
	}
	*/



	pause();

	//�ǳ�
	pause();
	lpComm->SubscribeRequest(NAType, CxlAll, ALLWWW);
	pause();
	lpComm->DoLogout(USER_NAME);
	//pause();
	//lpComm->DoLogout("");
	pause();
	//lpComm->DoLogout("20035");
	//��ͣ�ȴ��ǳ����
	pause();

#ifdef _WIN32
	//�ر��Զ������߳�
	g_bStop = true;
	SetEvent(g_hEvent);
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
#else

#endif

	//�ر�ͨ������
	lpComm->Stop();

	//�ͷ�ͨ�Ŷ���
	lpComm->Release();
}


