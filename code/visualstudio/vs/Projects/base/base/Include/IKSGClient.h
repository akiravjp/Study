#ifndef IKSGCLIENT_H
#define IKSGCLIENT_H


enum enumServerConnectInfo {
	enumServerConnectCreate = 0x100,
	enumServerConnectClose
};

typedef void (*CALLBACK_CLIENT_EVENT)(void *lpParam, enumServerConnectInfo eEventType);

class IKSGClient {
public:
	//�趨�¼��ص�����
	virtual bool RegisterMsgFilter(void * lpParam, CALLBACK_CLIENT_EVENT pfnEventNotify) = 0;

	//������ʼ��
	virtual bool Startup() = 0;

	//�˳�����
	virtual bool CleanUp() = 0;

	//����ָ��IP��ַ
	virtual bool ConnectTo(const char * const &pAddressToConnectServer, unsigned short usPortToConnectServer) = 0;

	//�Ͽ�����
	virtual bool Shutdown() = 0;

	//��Server��������
	virtual bool SendPackToServer(const void * const pData, const unsigned long datalength) = 0;

	//��ȡ��Server���͹���������
	virtual void *GetPackFromServer(unsigned int &datalength) = 0;
};

//����KSGClient����
//windows:	ulBufferParam1��Ч, ����ͬԭRainBowLib
//linux:	ulBufferParam1Ϊ���ͻ�������С, ulBufferParam2Ϊ���ܻ�������С
IKSGClient* CreateKSGClient(unsigned long ulBufferParam1, unsigned long ulBufferParam2);

//ɾ���ͷ�KSGClient����
bool DeleteKSGClient(IKSGClient*);

#endif
