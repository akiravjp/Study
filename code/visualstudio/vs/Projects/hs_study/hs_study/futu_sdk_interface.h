/**********************************************************************
* Դ��������: futu_sdk_interface.h
* �������Ȩ: �������ӹɷ����޹�˾
* ϵͳ����  : 06�汾�ڻ�ϵͳ
* ģ������  : �����ڻ��ܱ߽ӿ�
* ����˵��  : �ܱ�ͨ�Žӿڶ���
* ��    ��  : xdx
* ��������  : 20110315
* ��    ע  : �ܱ�ͨ�Žӿڶ���  
* �޸���Ա  ��
* �޸�����  ��
* �޸�˵��  ��20110315 ����
**********************************************************************/
#ifndef _FUTU_SDK_INTERFACE_H_
#define _FUTU_SDK_INTERFACE_H_

#include "futu_data_types.h"
#include "futu_message_interface.h"

#ifdef _WIN32
#  ifdef HSAPI
#  undef HSAPI  
#  endif
#  define HSAPI __stdcall
#else
#    define HSAPI 
#endif

struct IFuCallBack;

////////////////////////////////�ڻ�ͨ�Ŷ���ӿ�//////////////////////////////////////////
struct IHsFutuComm:public IHSKnown
{
	/** 
	 * �������ò���
	 *@param szSection ����С��
	 *@param szName    ����������
	 *@param szVal     �������ֵ
	 *@return          ERR_OK��ʾ�ɹ�,������ʾʧ��
	 [���̰߳�ȫ]
	*/
	virtual int HSAPI SetConfig(const char* szSection,const char* szName,const char* szVal) = 0;

	/** 
	 * ��ʼ���ӿ�,ʼ����������,���ӵ�½��������ȡ����Ӧ����Ϣ
	 *@param lpCallback �첽�ص�����,���û��̳ж�Ӧ�Ľӿ�ʵ��֮,ΪNULL���ʾ�����Ļص���Ϣ
	 *@param iTimeOut   ��ʱʱ��,��ʾ��ʼ����ʱʱ��,��λ����,-1��ʾ�����ڵȴ�.
	 *@return           ERR_OK��ʾ�ɹ�,������ʾʧ��
	 [�̰߳�ȫ]
	*/
	virtual int HSAPI Init(IFuCallBack* lpCallback = NULL,int iTimeOut = 5000) = 0;
	
	/**
	 * ��������,��������Ӧ�õ�ͨ������.��ͨ�����ӶϿ�ʱ,Ҳ���Ե��ô˺���������������
	 *@param iType    Ҫ�����ķ�������.����ȡֵ1=SERVICE_TYPE_TRADE,
	                                           3=SERVICE_TYPE_TRADE+SERVICE_TYPE_QUOTE
	                  ������ʼ��������Ϊ3.
	 *@param iTimeout ��������ʱ
	 *@return         ERR_OK��ʾ�ɹ�,������ʾʧ�� 
	 [�̰߳�ȫ]
	*/
	virtual int HSAPI Start(int iType,int iTimeOut = 5000)  = 0;

	/** 20110729 luyj ����reportFlag����  �޸ĵ���20110729007
	 * �û���¼,���������ҵ��֮ǰ,��Ҫ�ȵ�½��ȡ����������֤��Ϣ
	 *@param szUserID   �û���,һ��ָ�ʽ��˺�
	 *@param szUserPass �û�����
	 *@param reportFlag �û��Ƿ���Ҫ���ƻر���1��Ҫ��0����Ҫ
	 *@param lpReserved ��������,���汾�ӿڱ�������ΪNULL
	 *@return           ERR_OK��ʾ����ɹ�(����ʱ������ʾ�Ѿ���½�ɹ�,����첽�ص���ȡӦ����Ϣ)
	 [�̰߳�ȫ]
	*/
	virtual int HSAPI DoLogin(const char *szUserID,const char* szUserPass,const int reportFlag,const void* lpReserved = NULL) = 0;

	/** 20110729 luyj ����report_flag����  �޸ĵ���20110729007 
	    20110701 luyj ����������� �޸ĵ���20110623004
	* �û���¼,���������ҵ��֮ǰ,��Ҫ�ȵ�½��ȡ����������֤��Ϣ
	*@param szUserID   �û���,һ��ָ�ʽ��˺�
	*@param szUserPass �û�����
	*@param lpReceivedMsg �û��ķ�����Ϣ
	*@param report_flag �û��Ƿ���Ҫ���ƻر���1��Ҫ��0����Ҫ
	*@param lpReserved ��������,���汾�ӿڱ�������ΪNULL
	*@return           ERR_OK��ʾ����ɹ�(����ʱ������ʾ�Ѿ���½�ɹ�,Ҫ��lpReceivedMsgȡ��Ӧ����Ϣ)
	[�̰߳�ȫ]
	*/
	virtual int HSAPI DoLoginEx(const char *szUserID,const char* szUserPass,IFuMessage* lpReceivedMsg,const int reportFlag,const void* lpReserved = NULL) = 0;

	/** 
	 * ����һ��ҵ��������Ϣ(Ӧ�������첽�ص��н���)
	 *@param lpMessage һ��ҵ��������Ϣ,���û����������������
	 *@param iKeyID    һ���Զ����ʶ,�첽Ӧ����л���˱�ʶ.-1��ʾ�����Ĵ˱�־(��Ĭ���첽Ӧ�����ʽ��˺���Ϊkeyid����)
     *@return          ERR_OK��ʾ��������ɹ�,��Ҫ���첽�ص���ȡ��Ӧ��Ӧ����Ϣ���
	 [���̰߳�ȫ]
	*/
	virtual int HSAPI AsyncSend(const IFuMessage* lpReqMsg,int iKeyID = -1) = 0;

	/** ͬ������һ��ҵ��������Ϣ
	 *@param lpReqMsg �����ҵ����Ϣ  [in]
	 *@param lpAnsMsg ͬ��Ӧ��ҵ����Ϣ[in,out]
	 *@param iTimeout ��ʱʱ��,��λ����
	 *@return         ERR_OK��ʾ�ɹ�,������ʾʧ��
	 [���̰߳�ȫ]
	*/
	virtual int HSAPI SyncSendRecv(const IFuMessage* lpReqMsg,IFuMessage* lpAnsMsg,int iTimeout = 3000) = 0;

	/**
	 * ���Ͷ�������,ҵ����ս��
	 *@param rType   ��������(�μ�REGType�Ķ���)
	 *@param rAction ����/�˶��ȶ���(�μ�REGAction�Ķ���)
	 *@param szParam ���ݲ�ͬ��rType����:
	                 ��������:szParam��ʾ���ĵĺ�Լ�б�,�Զ��ŷָ��ַ���,����WS905,a0905,cu0905,IF0905  
	                          ������ȫ�г�������,���Ĵ���ΪALLWWW
	                          ��Լ��ֻ��ָ��һ������(���Ȼ������)
				     ���ǻر�/������Ϣ:szParam���ʾ�����ĵ��û��˺�,ע��������˺Ŷ��ǵ�½�����˺�
	 *@return        ERR_OK��ʾ����ɹ�(���첽Ӧ����ȡ���Ľ��),������ʾ����ʧ��
	 [���̰߳�ȫ]
	*/
	virtual int HSAPI SubscribeRequest(REGType rType,REGAction rAction,const char* szParam) = 0;

	/** 
	 * �û��ǳ�
	 *@param szUserID    ���ǳ����û��˺�
	 *@param lpReserved  ��������,���汾��������ΪNULL
     *@return            ERR_OK��ʾ����ɹ�,������Դӵ�½Ӧ����ȡ����Ϣ
	 [�̰߳�ȫ]
	*/
	virtual int HSAPI DoLogout(const char* szUserID,const void* lpReserved = NULL) = 0;

	/**
	 * �ر�����ͨ�Ŷ���,ֹͣ���ͨ������
	 *@return ERR_OK�ɹ�,������ʾʧ��
	 [�̰߳�ȫ]
	*/
	virtual int HSAPI Stop() = 0;

	/**
	 * ��ȡ����״̬
	 *@param iIndex���ӱ��.SERVICE_TYPE_TRADE - ��ʾ�������� SERVICE_TYPE_QUOTE -����(���ܰ����ر�)����
	 *@return ��ȡ����״̬(�ο�CONState�Ķ���)
	 [�̰߳�ȫ]
	*/
	virtual int HSAPI GetStatus(int iIndex) = 0;

	/**
	 * ��ȡ������Ϣ
	 *@param iErrNo �����
	 *@return       ��ȡ������Ϣ��˵��(����������ʧ��)
	 [�̰߳�ȫ]
	*/
	virtual const char* HSAPI GetErrorMsg(int iErrNo) = 0;

	/**
	 * ����ӿڶ���ʵ����ص�����(��Ҫ�ڶ�ʵ��Ӧ����)
	 *@param lpKey   Ҫ�󶨵����ݻ�����
     *@param iKeyLen Ҫ�󶨵����ݳ���
	 *@return        ERR_OK�󶨳ɹ�,������ʾ��ʧ��(�������ڴ�������)
	 [�̰߳�ȫ]
	*/
	virtual int  HSAPI SetKeyData(const void* lpKeyData,int iLen) = 0;

	/**
	 * ��ȡ��ӿڶ���󶨵�����
	 *@param iLen �󶨵����ݳ���[in,out]
	 *@return ����Ҫ�󶨵�����ָ��
	 [�̰߳�ȫ]
	*/
	virtual const void* HSAPI GetKeyData(int* iLen) = 0;
};

////////////////////////ͨ���첽�ص��ӿ�(ע��ص��е�IFuMessage��Ϣ��SDK��������������)//////////////////////////////////////////////////
struct IFuCallBack:public IHSKnown
{
	/** 
	 * ����״̬�ĸı�
	 *@param lpComm       ͨ�Žӿڶ���,�����ֶ����ӵ�Ӧ��
	 *@param iType        ��������.0 - ���� 1 - ����(���ܰ����ر�)
	 *@param iRet         ����״̬��ʶ
	 *@param szNotifyTime ������ʱ��
	 *@param szMessage    ˵����Ϣ
	*/
	virtual void HSAPI OnNotifyConnState(IHsFutuComm* lpComm,int iType,int iStatus,const char* szNotifyTime,const char* szMessage) = 0;

	/**
	 * ��½Ӧ����Ӧ
	 *@param lpComm ͨ�Žӿڶ���,�����ֶ����ӵ�Ӧ��
	 *@param lpMsg  ��½Ӧ����Ӧ��Ϣ
	*/
	virtual void HSAPI OnRspLogin(IHsFutuComm* lpComm,IFuMessage* lpMsg) = 0;

	/** 
	 * �ǳ�����
	 *@param lpComm ͨ�Žӿڶ���,�����ֶ����ӵ�Ӧ��
	 *@param lpMsg  �ǳ�Ӧ����Ӧ��Ϣ
	*/
	virtual void HSAPI OnRspLogout(IHsFutuComm* lpComm,IFuMessage* lpMsg) = 0;

	/**
	 *����\�˶�������߻ر��Ľ��
	 *@param lpComm    ͨ�Žӿڶ���,�����ֶ����ӵ�Ӧ��
	 *@param sType     ��������(��������,�������,�ر�,������Ϣ)
	 *@param aAction   ����ʽ(����,ȡ��,ȡ��ȫ��,����)
	 *@param iResult   ���Ľ��,-1δ֪ʧ��,0���ĳɹ�,1�ظ�����,2ȡ���ɹ�,3û�ж��Ŀ���ȡ��
	 *@param lpParam   ���ӵĲ���,���ǻر�Ӧ��,�����˺�;��������,���Ǻ�Լ����;ALLWWW��ʾ����;NULLδ֪
	 *@param szMessage ����˵��  
	*/
	virtual void  HSAPI OnRspSubResult(IHsFutuComm* lpComm,REGType sType,REGAction aAction,int iResult,const char* lpParam,const char* szMessage) = 0;

	/** 
	 * ҵ����յ�ҵ��Ӧ����Ϣ
	 *@param lpComm     ͨ�Žӿڶ���,�����ֶ����ӵ�Ӧ��
	 *@param lpAnsData  ҵ��Ӧ����Ϣ
	 *@param iRet       ������ERR_OK��ʾ�ɹ�,�����������ֵȡ����Ĵ�����Ϣ
	 *@param iKeyID     �첽��������������keyid,������ָ��,��Ĭ�����ʽ��˺ŷ���
    */
	virtual void HSAPI OnReceivedBiz(IHsFutuComm* lpComm,IFuMessage* lpAnsData,int iRet,int iKeyID) = 0;

	/** 
	 * ���յ������г�����
	 *@param lpComm     ͨ�Žӿڶ���,�����ֶ����ӵ�Ӧ��
	 *@param lpInfo     ������������
	 *@param rAction    ��ʾ�ǿ��ջ��Ƕ�������
	*/
	virtual void HSAPI OnRecvMarketData(IHsFutuComm* lpComm,CMarketInfo* lpInfo,REGAction rAction) = 0;

	/** 
	 * ���յ�����г�����
	 *@param lpComm     ͨ�Žӿڶ���,�����ֶ����ӵ�Ӧ��
	 *@param lpInfo     ������������
	 *@param rAction    ��ʾ�ǿ��ջ��Ƕ�������
	*/
	virtual void HSAPI OnRecvArgMarketData(IHsFutuComm* lpComm,CArgMarketInfo* lpInfo,REGAction rAction) = 0;

	/** 
	 * ���յ�ί�з�����Ϣ
	 *@param lpComm     ͨ�Žӿڶ���,�����ֶ����ӵ�Ӧ��
	 *@param lpInfo     ί�з�����Ϣ(�μ�COrderRspInfo�ṹ�Ķ���)
	*/
	virtual void HSAPI OnRecvOrderInfo(IHsFutuComm* lpComm,const COrderRspInfo* lpInfo) = 0;

	/** 
	 * ���յ������ɽ�����
	 *@param lpComm     ͨ�Žӿڶ���,�����ֶ����ӵ�Ӧ��
	 *@param lpInfo     �����ɽ�����(�μ�CRealRspInfo�ṹ�Ķ���)
	*/
	virtual void HSAPI OnRecvOrderRealInfo(IHsFutuComm* lpComm,const CRealRspInfo* lpInfo) = 0;

	/**
	 * ���߸�����Ϣ
	 *@param  lpComm    ͨ�Žӿڶ���,�����ֶ����ӵ�Ӧ��
	 *@param  szUsrID   ��Ϣ��ص��˺�
	 *@param  szMessage ��صĸ�����Ϣ
	*/
	virtual void HSAPI OnRspOnlineMsg(IHsFutuComm* lpComm,const char* szUsrID,const char* szMessage) = 0;
};


//////////////////////////////////�����ӿ�////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif
    
	/** 
	 * �����µ�ͨ�Žӿڶ���(���Դ�����ͬ�Ľӿڶ��������Ӷ��������)
	 *@param lpReserved ��������,Ŀǰ������ΪNULL
	 *@return           ��NULL��ʾ��Ч�Ľӿڶ���(���Ե�����Ӧ�Ľӿں���)�������ʾ�����ڴ�ʧ��
	 [�̰߳�ȫ]
	*/

    IHsFutuComm* HSAPI NewFuCommObj(void* lpReserved = NULL);

	/** 
	 * ��ȡSDK�汾��
	 *@return �汾��,ʮ����������,����0x10000000,��ʾ�汾Ϊ1.0.0.0
	 [�̰߳�ȫ]
    */
	int HSAPI GetSDKVersion();

#ifdef __cplusplus
}
#endif

#endif /*futu_sdk_interface.h*/

