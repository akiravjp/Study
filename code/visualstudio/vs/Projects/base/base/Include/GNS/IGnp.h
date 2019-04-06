//--------------------------------------------------------------
// ��Ӱ��˵�����  GmcNetworkProtocol(GNP)
// ��Ȩ����:        2010 ��ɽ���(Kingsoft)
// ��������������: 2010-3-16 Golton Gao
//--------------------------------------------------------------
#ifndef __I_GMC_NETWORK_PROTOCOL_H__
#define __I_GMC_NETWORK_PROTOCOL_H__

#include "GnsDef.h"

// === �����֤��� ===//
#pragma pack(1)

// == �����֤ģʽ ==//
enum GNP_AUTHENTICATION_MODE	
{
	GAM_NONE = 0,	// �����������֤
	GAM_IP,			// IP�����֤ģʽ
};

// == �����֤��Ϣ ==//
#define GNP_AUTHENTICATION_MAX_LEN 512	// �����֤��Ϣ����󳤶�

#pragma pack()

// GNP�ļ����
struct IGnpMonitor
{
	virtual void Print(const char* pFormat, ...) = 0;
};

// GNP_CLIENT��������Ϣ
struct GNP_CLIENT_CONFIG
{
	char			LocalIP[16];			// GNP�ͻ��˵�IP�����ڿͻ����ж��IP���������ע��
	GNE_ADDR		LocalAddr;				// GNP�ͻ�����GNS�еĵ�ַ
	char			ServerIP[16];			// GNP����˵�IP
	unsigned int	ServerPort;				// GNP����˵ļ����˿�
	GNE_ADDR		ServerAddr;				// GNP�������GNS�еĵ�ַ
	int				ServerEncryptionType;	// ͨ�ż��ܷ�ʽ
};

// GnpClient�¼�������
struct IGnpClientEventHandler
{
	// ��Ϣ�����¼�
	// ���������	Head		--	GNM��Ϣ��ͷ��
	//				pLoadData	--	GNM��Ϣ�غ�����
	//				uLoadLen	--	GNM��Ϣ�غɳ���
	virtual void OnClientRecv(const GNM_HEAD& Head, const char* pLoadData, unsigned int uLoadLen) = 0;
};

// GnpClient
struct IGnpClient
{
	// ���ٽӿڶ���
	virtual void Release() = 0;

	// ���������֤�������Ϣ
	// ���������	uAuthenticationMode -- �����֤ģʽ���ο�GNP_AUTHENTICATION_MODE
	//				pAuthenticationInfo	-- �ض�ģʽ�������֤��Ϣ
	//				uInfoSize			-- �ض�ģʽ�������֤��Ϣ�ĳ��ȣ����<=GNP_AUTHENTICATION_MAX_LEN
	// ע�⣺��Initialize֮ǰ����
	// ���ӣ�IP�����֤��ʽ	--	SetAuthentication(GAM_IP, NULL, 0);
	virtual void SetAuthenticationInfo(unsigned int uAuthenticationMode, void* pAuhtenticationInfo, unsigned int uInfoSize) = 0;

	// ��ʼ��
	virtual bool Initialize(const GNP_CLIENT_CONFIG& Config) = 0;
	
	// ����ʼ��
	virtual void Terminate() = 0;
	
	// ����
	virtual void Tick() = 0;

	// ����GNM��Ϣ
	virtual bool Send(const GNM_HEAD& Head, const void* pLoadData, unsigned int uLoadLen) = 0;

	// ����״̬�Ƿ�����
	virtual bool IsOk() = 0;

	// ��ȡGNPЭ��汾
	virtual void GetVersion(unsigned int& uMajor, unsigned int& uMinor) = 0;

	// ���������ļ����
	// ���������pMonitor	-- NULL, �رռ����
	//						-- ��NULL��������ض���pMonitor
	virtual void SetMonitor(IGnpMonitor* pMonitor) = 0;

	// �����¼�������
	// ���������pEventHandler	-- �¼�������ָ�룬����ΪNULL
	// ע�⣺��Initialize֮�����
	virtual void SetEventHandler(IGnpClientEventHandler* pEventHandler) = 0;
};

// GNP_SERVER������Ϣ
struct GNP_SERVER_CONFIG
{
	char			ServerIP[16];			// GNP�����IP
	unsigned int	ServerPort;				// GNP����˼����˿�
	GNE_ADDR		ServerAddr;				// GNP�������GNS�еĵ�ַ
	unsigned int	ServerMaxConn;			// GNP�����֧�ֵ����������
	int				ServerEncryptionType;	// ͨ�ż��ܷ�ʽ
};

// GNP_SERVER�¼�������
struct IGnpServerEventHandler
{
	virtual void OnLogin(const GNE_ADDR& GneAddr) = 0;
	virtual void OnLogout(const GNE_ADDR& GneAddr) = 0;
	virtual void OnServerRecv(const GNM_HEAD& Head, const char* pLoadData, unsigned int uLoadLen) = 0;
};

// GNP_SERVER�����֤��
struct IGnpServerAuthentication
{
	// �ж��Ƿ�ͨ�������֤
	// ���������	ClientAddr	--	��Ҫ��֤�Ŀͻ��˵�GNE��ַ��ϣ�����е���ݣ�
	//				uIp			--	�ͻ��˵�½��IP
	//				uMode		--	�����֤ģʽ���ο�GNP_AUTHENTICATION_MODE
	//				pInfo		--	�����֤��Ϣ�������������֤ģʽ�й�
	//				uInfoSize	--	�����֤��Ϣ�ĳ��ȣ���󲻳���GNP_AUTHENTICATION_MAX_LEN
	// ����ֵ��	true		--	ͨ�������֤
	//				false		--	δͨ�������֤
	virtual bool IsAuthenticated(const GNE_ADDR& ClientAddr, unsigned int uIp, unsigned int uMode, const void* pInfo, unsigned int uInfoSize) = 0;
};

struct GNE_INFO
{
	GNE_ADDR				Addr;		// GNE��ַ
	unsigned int			uIp;		// GNE���õ�IP
	unsigned int			uPort;		// GNE���õĶ˿�
};

struct IGnpServer
{
	// ���ٽӿڶ���
	virtual void Release() = 0;

	// ��ʼ��
	virtual bool Initialize(const GNP_SERVER_CONFIG& Config) = 0;

	// ����ʼ��
	virtual void Terminate() = 0;

	// ����
	virtual void Tick() = 0;

	// ����GNM��Ϣ
	// ���������	Head		--	GNM��Ϣͷ��
	//				pLoadData	--	GNM��Ϣ�غ�����
	//				uLoadLen	--	GNM��Ϣ�غɳ���
	// ����ֵ:		true		--	���ͳɹ�
	//				false		--	����ʧ��
	virtual bool Send(const GNM_HEAD& Head, const void* pLoadData, unsigned int uLoadLen) = 0;

	// ��������GNE
	// ���ӣ�
	/*
		IGnpServer*	pServer;
		for (unsigned int uPos = pServer->GetBeginPos(); uPos != pServer->GetEndPos(); pServer->GetNextPos(uPos))
		{
			GNE_INFO Info = pServer->GetGneInfo(uPos);
		}
	*/
	virtual unsigned int GetBeginPos() = 0;
	virtual unsigned int GetEndPos() = 0;
	virtual void GetNextPos(unsigned int& uPos) = 0;
	virtual GNE_INFO GetGneInfo(unsigned int uPos) = 0;

	// ��ȡ����GNE����
	virtual unsigned int GetGneCount() = 0;

	// ��ѯGNE�Ƿ��ѵ�¼
	virtual bool IsGneLogined(const GNE_ADDR& GneAddr) = 0;

	// �Ͽ�GNE����
	virtual void Disconnect(const GNE_ADDR& GneAddr) = 0;

	// ��ȡGNPЭ��İ汾(����д���ʼ����־�У����ڲ�֤����)
	virtual void GetVersion(unsigned int& uMajor, unsigned int& uMinor) = 0;

	// ���������ļ����
	// ���������pMonitor	-- NULL, �رռ����
	//						-- ��NULL��������ض���pMonitor
	virtual void SetMonitor(IGnpMonitor* pMonitor) = 0;

	// �����¼�������
	// ���������pEventHandler	-- �¼�������ָ�룬����ΪNULL
	// ע�⣺��Initialize֮�����
	virtual void SetEventHandler(IGnpServerEventHandler* pEventHandler) = 0;

	// ���������֤��
	// ���������pAuthentication	-- �����֤��ָ�룬����ΪNULL
	// ע�⣺��Initialize֮�����
	virtual void SetAuthentication(IGnpServerAuthentication* pAuthentication) = 0;
};

//=== �ⲿ���ø�ͷ�ļ�ʱ�������ӿ����� ===//
#ifndef  GNP_INTERNAL_SIGNATURE 

//== ��ʽ����DLL���õĽӿ� ==
extern "C" IGnpClient* GnpClientCreate();
extern "C" IGnpServer* GnpServerCreate();

//== ��ʾ����DLL���õĽӿ� ==

//= �����ӿں��������� =
#define FUNC_NAME_GNP_CLIENT_CREATE "GnpClientCreate"
#define FUNC_NAME_GNP_SERVER_CREATE "GnpServerCreate"

//= �����ӿں���ԭ�Ͷ���
typedef IGnpClient* (*FUNC_GNP_CLIENT_CREATE)();
typedef IGnpServer* (*FUNC_GNP_SERVER_CREATE)();

#endif // #ifndef  GNP_INTERNAL_SIGNATURE 

#endif // #ifndef __I_GMC_NETWORK_PROTOCOL_H__ 
