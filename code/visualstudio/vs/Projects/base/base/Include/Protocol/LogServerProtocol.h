//---------------------------------------------------------------------------
// ������Ե�����2 GameMasterCentral ������ͨ
// ��Ȩ����:       2006-2007 ��ɽ���(Kingsoft)
// ��������������: 2006 Խ��(wooy)
//---------------------------------------------------------------------------
// GameMasterCentral����Ϸ����ĸ���Master����֮���Э��ӿ�
//---------------------------------------------------------------------------
#ifndef __LOG_SERVER_PROTOCOL_H__
#define __LOG_SERVER_PROTOCOL_H__

#pragma	pack(push, 1)

enum LOG_SERVER_PROTOCOL_LIST
{
	LOG_SERVER_P_LOGIN	= 32,			//�ͻ��˵�¼��Ϣ��
	LOG_SERVER_P_LOGIN_RESP,			//��¼��Ϣ�Ļ�����
	LOG_SERVER_P_PING,					// �ɿͻ���������ping���������LogSvrԭ�ⲻ����ping��
	LOG_SERVER_P_QUERY_LOG,
	LOG_SERVER_P_ADD_LOG_COMMON,		// ��(ͨ��)������־�����Ӽ�¼
	LOG_SERVER_P_ADD_LOG_COMMON_RESULT,	// LogServer�ظ��ͻ��˵���Ӽ�¼���
	LOG_SERVER_P_ADD_LOG_ITEM,			// ����Ʒ��־�����Ӽ�¼
};

#define LOG_SERVER_PING_INTERVAL	30	//�ͻ��˷���ping����Ƶ�ʣ���λ����
#define LOG_SERVER_DISCONNCT_TIME	100	//�����LogSvr����˳�ʱ��δ�յ�������󽫶Ͽ����ӣ���λ����

struct LOG_SERVER_S_LOGIN
{
	unsigned char	cProtocol;				// = LOG_SERVER_P_LOGIN
	bool			bFailIfDbNotExist;		//������ݿⲻ�����Ƿ�ֱ�ӵ�¼ʧ�ܣ�����ѯ���Ƿ񴴽�
	char			szGameSpaceName[32];	//Ŀ����Ϸ��������ƣ������������group��
	char			szDatabaseName[32];		//���ݿ�Ŀ���
	char			szDbAccount[32];		//�������ݿ���ʺ�
	char			szDbPassword[64];		//�������ݿ������
	char			Reserved[8];
};

enum LOG_SERVER_E_LOGIN_RESULT
{
	LOG_SERVER_E_LR_OK = 1,			//��¼�ɹ�
	LOG_SERVER_E_LR_DB_ACC_ERR,		//��¼ʧ�ܣ���ʹ�õ����ݿ��ʺ���������
	LOG_SERVER_E_LR_DB_NOT_EXIST,	//ָ�������ݿⲻ����
	LOG_SERVER_E_LR_FAIL,			//��¼ʧ�ܣ�����ԭ��
};

struct LOG_SERVER_S_LOGIN_RESP
{
	unsigned char	cProtocol;			// = LOG_SERVER_P_LOGIN_RESP
	unsigned char	cResult;
};

//LogServer�յ�Ping��Ϣ�����ԭ������
struct LOG_SERVER_S_PING
{
	unsigned char	cProtocol;	// = LOG_SERVER_P_PING
	unsigned int	uTime;		// = ʱ���
};

struct LOG_SERVER_S_QUERY_LOG
{
	unsigned char	cProtocol;		// = LOG_SERVER_P_QUERY_LOG
	unsigned int	uSerialNo[2];	// ��Ϣ������ˮ��
	char			szLogSort[32];	// ��־����
	char			szLogObject[64];// ��־��ص�Ŀ�������
	unsigned int	uParamLen;		// �����szParam�ĳ���(������β��'\0')
	char			szParam[1];
	
};

//����Ĳ���������β����'\0'�ĳ���
#define LOG_SERVER_S_QUERY_LOG_SIZE(n)			(sizeof(LOG_SERVER_S_QUERY_LOG) + (n) - 1)
#define LOG_SERVER_S_QUERY_LOG_CHECK_SIZE(p,s)	((s) == LOG_SERVER_S_QUERY_LOG_SIZE((p)->uParamLen))

//LOG_SERVER_P_ADD_LOG_COMMON
struct LOG_SERER_S_ADD_LOG_COMMON
{
	unsigned char	cProtocol;		// = LOG_SERVER_P_ADD_LOG_COMMON
	unsigned char	bReturnId;		// �����²�����־��idֵ
	unsigned int	uLogType;		// ��־����
	unsigned int	uLogFlag;		// ��־���
	unsigned int	uSerialNo[2];	// ��Ϣ������ˮ��
	unsigned short	usObjNameLen;	// �������Ƴ���(������β��'\0')
	unsigned short	usInfoLen;		// ��־��Ϣ����(�����ı���Ϣ������'\0'��β)
	char			ObjNameAndInfo[1];//������������־��Ϣ���ݣ����ܳ���ΪusObjNameLen+usInfoLen(����'\0'��β)
};
#define LOG_SERER_S_ADD_LOG_COMMON_SIZE(onl, il)	(sizeof(LOG_SERER_S_ADD_LOG_COMMON) + (onl) + (il) - 1)
#define LOG_SERER_S_ADD_LOG_COMMON_CHECK_SIZE(p,s)	((s) == LOG_SERER_S_ADD_LOG_COMMON_SIZE((p)->usObjNameLen, (p)->usInfoLen))

struct LOG_SERER_S_ADD_LOG_COMMON_RESULT
{
	unsigned char	cProtocol;		// = LOG_SERVER_P_ADD_LOG_COMMON
	unsigned int	uSerialNo[2];	// ������Ϣ������ˮ��
	unsigned int	uLogId;			// ����������²�����־��idֵ�����Ϊ0ֵ��ʾʧ��
};

#pragma	pack(pop)

#endif// #ifndef __LOG_SERVER_PROTOCOL_H__
