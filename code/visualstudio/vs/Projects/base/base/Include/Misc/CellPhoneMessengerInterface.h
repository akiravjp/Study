//-------------------------------------------------------------------
//������Ե�����2	�ֻ���Ѷ�������
//��Ȩ���У�        2008 ��ɽ���(Kingsoft)
//�������ڼ����ߣ�  2008-3-24	Խ��(Wooy)
/*-------------------------------------------------------------------
 �ܹ�ͨ������HTTP GET��ʽ���ֻ���ѶISP�������Ͷ�Ѷ�����󣬲���û�����
 ��ģ�鲻֧�ֶ��̣߳���δ����Linux֧�֡�
 ����URL��ʽ��
 http://1.0.0.1/default.aspx?Acc=Jx2&Phone=13900000000&Message=HELLO
-------------------------------------------------------------------*/
#ifndef __CELL_PHONE_MESSENGER_INTERFACE_H__
#define __CELL_PHONE_MESSENGER_INTERFACE_H__

//�������ø�ģ��Ĺ��������������Ϣ
struct CPM_WORK_ENVIRONMENT_INFO
{
	char	szRequestURLPrefix[512];	//����URLǰ׺�����ָ������õ�"?"����
	char	szAccountToken[16];			//�ʺŲ���"="ǰ�Ĺؼ���
	char	szPhoneNumberToken[16];		//�ֻ�����"="ǰ�Ĺؼ���
	char	szShortMessageToken[16];	//��Ѷ����"="ǰ�Ĺؼ���
	char	szAccountName[32];			//ʵ��ʹ��"�ķ����ʺ�
	char	szEncodeKey[32];			//����˽Կ����XmlRpc��ʽʱ�ã�
	char	szHandlerMethod[64];		//��������뷽�����ƣ���XmlRpc��ʽʱ�ã�
};

//��������һ����Ѷ�Ľṹ��
struct CPM_SHORT_MESSAGE_INFO
{
	//pPhoneNumber��pMessageContentָ�������ַ������������������ַ���������û���ַ�����β��\0��
	const char*		pPhoneNumber;		//���ն�Ѷ�ĵ绰���룻���ж�����룬��";"����
	unsigned int	uPhoneNumberLen;	//pPhoneNumber��ָ���ݵĳ��ȣ���������а����ַ�����β��\0����ó��Ȳ�����β����
	const char*		pMessageContent;	//��Ѷ�ı�����
	unsigned int	uMessageContentLen;	//pMessageContent��ָ���ݵĳ��ȣ���������а����ַ�����β��\0����ó��Ȳ�����β����
};

//��Ѷ���Ͳ����Ľ��
enum	CPM_RESULT
{
	CPM_RESULT_OK = 0,						//�������ͣ��޴���
	CPM_RESULT_UNACCEPTABLE_PHONE_NUMBER = 1,//��Ч���ֻ�����
	CPM_RESULT_SERVER_EXCEPTION = 7,		//����������δ֪�쳣
	CPM_RESULT_CONTENT_ACCEPT_DENY = 9,		//�ܾ����ոö�Ѷ����(��Ϣ���зǷ��ؼ���)
	CPM_RESULT_IO_EXCEPTION = 10000,		//�����й�����Ĵ���
	CPM_RESULT_FAIL = -1,					//δָ��ԭ�����������
	//��ο����ļ���ĩβ�ĸ�¼����֪��ѶISP�Է�����Ϣ�Ķ���
};

enum CPM_MESSENGER_TYPE
{
	CPM_MESSENGER_TYPE_HTTPGET = 1,
	CPM_MESSENGER_TYPE_XMLRPC = 2,
};

//<<<<<<===---+++   �ӿں���   +++---===>>>>>>
#ifndef CELL_PHONE_MESSENGER_INTERNAL_SIGNATURE
	extern "C" bool			CPMessengerSetWorkEnvironment(const CPM_WORK_ENVIRONMENT_INFO& env, CPM_MESSENGER_TYPE eType);
	extern "C" CPM_RESULT	CPMessengerSendShortMessage(const CPM_SHORT_MESSAGE_INFO& msg);
	extern "C" void			CPMessengerCleanup();
	typedef bool		(*FUNC_CPM_SET_WORK_ENVIRONMENT)(const CPM_WORK_ENVIRONMENT_INFO& env, CPM_MESSENGER_TYPE eType);
	typedef CPM_RESULT	(*FUNC_CPM_SEND_SHORT_MESSAGE)(const CPM_SHORT_MESSAGE_INFO& msg);
	typedef void		(*FUNC_CPM_CLEANUP)();
	#define FUNC_NAME_CP_MESSENGER_SET_WORK_ENVIRONMENT	"CPMessengerSetWorkEnvironment"
	#define FUNC_NAME_CP_MESSENGER_SEND_SHORT_MESSAGE	"CPMessengerSendShortMessage"
	#define FUNC_NAME_CP_MESSENGER_CLEANUP				"CPMessengerCleanup"
#endif

#endif	//#ifndef __CELL_PHONE_MESSENGER_INTERFACE_H__

//==============================================================
//	��¼����ѶISP�Է�����Ϣ�Ķ���
//������Ϣͳһʹ�á��������-����������塱�ĸ�ʽ�����嶨�����£�
// �������	�����������				˵��	
//		0	OK							�������ͣ��޴���	
//		1	Must be China-Mobile user	��phone���������ݵ����ݱ������й��ƶ����ֻ����룬�й��ƶ����ֻ����붨��μ�3.2	
//		2	undefined Command			��Command���������ݵ�����Ϊδ����ָ��	
//		3	Need Command Paramater		Get������û���ṩ��Command������	
//		4	Need user Paramater			Get������û���ṩ��phone������	
//		5	Need Content Paramater		Get������û���ṩ��content������	
//		7	Server Exception			����������δ֪�쳣	
//		9	Failed to filter message	��Ϣ���зǷ��ؼ���	
//
//  ������Ϣ�����������г�����ʽ��
//		0-OK
//		1-Must be China-Mobile user
//		9-Failed to filter message
//==============================================================
