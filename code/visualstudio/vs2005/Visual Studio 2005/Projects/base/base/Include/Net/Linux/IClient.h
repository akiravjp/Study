#ifndef ICLIENT_H
#define ICLIENT_H

//Ӧ��ʹ���̵߳ķ���,Startup�����̵߳ȴ��ź�,��ͬ��IOģ��ʹ�ò�ͬ���ź�֪ͨ��Щ�߳�,�����ʱ��
//���ݴ�������Ŀ�Ĳ�ͬ������ͬ��Ŀ���̺߳ͻ�����,�����쳣���
#include "ZPort.h"
#include "XBuffer.h"
#include "Cipher.h"
#include "Cache.h"

enum enumServerConnectInfo {
	enumServerConnectCreate = 0x100,
	enumServerConnectClose
};

typedef void (*CALLBACK_CLIENT_EVENT )(void *lpParam, const unsigned long &ulnEventType);

class IClient
{
public:
	STDPROC Startup() = 0;						//����һ���̷߳���
	STDPROC Cleanup() = 0;
	STDPROC Shutdown() = 0;
	virtual void Release() = 0;
	STDPROC ConnectTo(const char *pAddressToConnectServer, unsigned short usPortToConnectServer) = 0;
	STDPROC RegisterMsgFilter(void * lpParam, CALLBACK_CLIENT_EVENT pfnEventNotify) = 0;
	STDPROC SendPackToServer( const void * const pData, const unsigned long datalength) = 0;
	virtual void *GetPackFromServer(unsigned int &datalength) = 0;
	/*
	virtual void PushMessage(char *pMsg, size_t nMsgLen) = 0;
	virtual BOOL IsEmpty() = 0;
	*/
	virtual void PassPack() {}
};

#endif
