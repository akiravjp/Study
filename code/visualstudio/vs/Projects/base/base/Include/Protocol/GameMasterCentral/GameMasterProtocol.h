//---------------------------------------------------------------------------
// ������Ե�����2 GameMasterCentral ������ͨ
// ��Ȩ����:       2006-2007 ��ɽ���(Kingsoft)
// ��������������: 2006 Խ��(wooy)
//---------------------------------------------------------------------------
// GameMasterCentral����Ϸ����ĸ���Master����֮���Э��ӿ�
//---------------------------------------------------------------------------
#ifndef __GAME_MASTER_CENTRAL_GAMEMASTER_PROTOCOL_H__
#define __GAME_MASTER_CENTRAL_GAMEMASTER_PROTOCOL_H__
#include "ProtocolBasic.h"
#include "GameMasterServiceDef.h"

#pragma	pack(push, 1)

enum GAME_MASTER_PROTOCOL_LIST
{
	GM_P_NORMAL	= PROTOCOL_NORMAL_PACKAGE_BEGIN,
	GM_P_OPERATION_REQUEST,					//�����������ݰ���ʽ��GAME_MASTER_PROTOCOL_HEADER
	GM_P_OPERATION_REQUEST_ON_ACCOUNT,		//���������ʺ�������Ϣ�Ĳ����������ݰ���ʽ��GAME_MASTER_PROTOCOL_WITH_OBJNAME
	GM_P_OPERATION_REQUEST_ON_ROLE,			//����������ɫ������Ϣ�Ĳ����������ݰ���ʽ��GAME_MASTER_PROTOCOL_WITH_OBJNAME
	GM_P_OPERATION_REQUEST_ON_OBJECT,		//������������������Ϣ�Ĳ����������ݰ���ʽ��GAME_MASTER_PROTOCOL_WITH_OBJNAME
	GM_P_OPERATION_RESPONSE,				//��������
};

//����GM_P_NORMALЭ�����Э��
enum GAME_MASTER_NORMAL_SUB_PROTOCOL
{
	GMN_P_SERVICE_LOGIN = 1,		//��Ϸ����ķ����������GMC��,���ȷ��˵�½��Ϣ
	GMN_P_SERVICE_PING,
	GMN_P_SERVICE_INFO,				//GMC���յ�GMN_P_SERVICE_LOGIN��Ϣ�󣬻ظ����������Ϣ���Է����öԷ�֪���Լ����
};

struct GAME_MASTER_SERVICE_PING : tagBiProtoHeaderNoLen
{
	unsigned int uTime;
};

//ÿ����Ϸ����ķ����������GMC��,���ȷ��˵�½��Ϣ����
struct GAME_MASTER_SERVICE_LOGIN : tagBiProtoHeaderNoLen
{
	int					nIdentifier;	//id ���� ʶ��� �����Ժ����֧�ֵ�̨GMS������ͬʱ���������ͬ��Ҫ����GMC�ĳ���
	unsigned int		uServiceType;	//����GameMasterCentral��MasterService����������ṩ�ķ��������,��MASTER_SERVICE_TYPE
	char				szOperatorAccount[32];
	char				szOperatorPasswd[64];
	char				Reserved[32];
};

//GMC���յ�GMN_P_SERVICE_LOGIN��Ϣ�󣬻ظ����������Ϣ���Է����öԷ�֪���Լ����
struct GAME_MASTER_SERVICE_INFO : tagBiProtoHeaderNoLen
{
	int					nAreaIndex;			//���������1�����
	int					nGroupIndex;		//���������2�����
	unsigned int		uServerId;		//���������Ψһ������ID
	char				szServerName[32];	//���������Ψһ�ַ�����ID
	char				szZoneName[32];		//���ڵ���������
	char				Reserved[12];
};

//����ˮ�ŵ�Э���ͷ
struct GAME_MASTER_PROTOCOL_HEADER : PrtocolLengthHeader
{
	GAME_MASTER_PROTOCOL_INFO	ProtInfo;
};

//�����ʺŵ�Э���ͷ
struct GAME_MASTER_PROTOCOL_WITH_OBJNAME : GAME_MASTER_PROTOCOL_HEADER
{
	NAMED_OBJECT_IDENTIFIER	Obj;
};

//����ˮ�ź����ݿ��Э���
struct GAME_MASTER_PROTOCOL_WITH_DATA : GAME_MASTER_PROTOCOL_HEADER
{
	DATA_CONTENT	Data;
};
#define GAME_MASTER_PROTOCOL_WITH_DATA_SIZE(n)		\
	((n > 0) ? (sizeof(GAME_MASTER_PROTOCOL_WITH_DATA) + n - 1) : sizeof(GAME_MASTER_PROTOCOL_HEADER))

//�����ʺź����ݿ��Э���
struct GAME_MASTER_PROTOCOL_WITH_OBJNAME_AND_DATA : GAME_MASTER_PROTOCOL_WITH_OBJNAME
{
	DATA_CONTENT	Data;
};
#define GAME_MASTER_PROTOCOL_WITH_OBJNAME_AND_DATA_SIZE(n)	\
	((n > 0) ? (sizeof(GAME_MASTER_PROTOCOL_WITH_OBJNAME_AND_DATA) + n - 1) : sizeof(GAME_MASTER_PROTOCOL_WITH_OBJNAME))

//����ˮ�ź�������Ϣ��Э����İ�ͷ
struct OPERATION_PROTOCOL_WITH_SVR_IDX_HEADER : GAME_MASTER_PROTOCOL_HEADER
{
	GAME_MASTER_SERVICE_SVR		ServiceSvr;
};

#pragma	pack(pop)

#endif// #ifndef __GAME_MASTER_CENTRAL_GAMEMASTER_PROTOCOL_H__
