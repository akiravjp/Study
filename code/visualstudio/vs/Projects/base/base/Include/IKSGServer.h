#ifndef IKSGSERVER_H
#define IKSGSERVER_H

enum enumClientConnectInfo {
	enumClientConnectCreate = 0x100,
	enumClientConnectClose
};

typedef void (*CALLBACK_SERVER_EVENT)(void* lpParam, unsigned long ulnID, enumClientConnectInfo ulnEventType);

class IKSGServer {
public:
	//������ʼ��
	virtual bool Startup() = 0;

	//�˳�����
	virtual bool Cleanup() = 0;

	//��һ���˿������������
	virtual bool OpenServer(unsigned long ulnAddressToListenOn, unsigned short usnPortToListenOn) = 0;

	//�ر��������
	virtual bool CloseServer() = 0;

	//ע���¼��ص�����
	virtual bool RegisterMsgFilter(void * lpParam, CALLBACK_SERVER_EVENT pfnEventNotify) = 0;

	//�����ݼ���ĳ�ͻ��˵ķ��Ͷ���,���ݲ��ἴʱ���͵��ͻ���
	virtual bool PackDataToClient(unsigned long ulnClientID, const void *pData, unsigned long datalength) = 0;

	//�����Ͷ����е�����ǿ�Ƽ�ʱ���͵��ͻ���, ulnClientID == -1 ��ʾǿ�Ʒ������пͻ��˻���������
	virtual bool SendPackToClient(unsigned long ulnClientID) = 0;

	//�����ݼ�ʱ���͵��ͻ���
	virtual bool SendData(unsigned long ulnClientID, const void *pData, unsigned long datalength) = 0;

	//ȡ�ô�ĳ�ͻ��˷�������һ�����ݰ�
	virtual const void *GetPackFromClient(unsigned long ulnClientID, unsigned long &datalength) = 0;

	//ǿ�ƶϿ�һ���ͻ�������
	virtual bool ShutdownClient(unsigned long ulnClientID) = 0;

	//ȡ�õ�ǰ����Ч�ͻ�����������
	virtual unsigned long GetClientCount() = 0;

	//ȡ��һ���ͻ��˵���Ϣ(IP��ַ)
	virtual const char * GetClientInfo(unsigned long ulnClientID) = 0;
	
	//���Ҫ��֤ KSGServer ��������,�����ڳ������̲߳��ϵ��ô˺���
	virtual void Breathe() = 0;
};

/************************************************************
//������CreateKSGServer()
//���ܣ�����һ�� KSGServer ����
//������unsigned long	ulMaxClient		: Server֧�ֵ����������
		unsigned long	ulBufferParam1	: windows: ��KSGServer����Ŀ��л�����������, linux: �����ͻ������ӵķ��ͻ�������С
		unsigned long	ulBufferParam2	: windows: �����������Ĵ�С, linux: �����ͻ������ӵĽ��ܻ�������С
//���أ�IKSGServer*	: �����õ� KSGServer ����ָ��
************************************************************/
IKSGServer* CreateKSGServer(unsigned long ulMaxClient,
							unsigned long ulBufferParam1,
							unsigned long ulBufferParam2);

//ɾ���ͷ�һ�� KSGServer ����
bool DeleteKSGServer(IKSGServer*);

#endif
