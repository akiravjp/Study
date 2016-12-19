#ifndef _GODDESS_PROTOCOL_H_
#define _GODDESS_PROTOCOL_H_

#include "../ProtocolBasic.h"

enum GODDESS_C2S_PROTOCOL_ID    // Goddess client ==> server
{
    GODDESS_C2S_PROTOCOL_BEGIN = PROTOCOL_BIG_PACKAGE_BEGIN,
    GDC2S_SAVE_ROLE_DATA,         // �洢��ɫ����, ref : TProcessData
    GDC2S_SET_STATISTIC_INFO,     // ����ͳ����Ϣ, ref : TProcessData

    GDC2S_PING = PROTOCOL_NORMAL_PACKAGE_BEGIN + 1, // ping, ref : PING_COMMAND
    GDC2S_QUERY_ROLE_LIST,        // ��ȡ��ɫ�б�, ref : TProcessData
    GDC2S_QUERY_ROLE_DATA,        // ��ȡ��ɫ����, ref : TProcessData
    GDC2S_CREATE_ROLE,            // ������ɫ, ref : TProcessData
    GDC2S_DELETE_ROLE,            // ɾ����ɫ, ref : TProcessData

    GDC2S_LOCK_OR_UNLOCK_ROLE,    // ��ɫ���ݼ�/��������, ref : LOCK_OR_UNLOCK_ROLE
    GDC2S_PLAYER_ENTER_GAME,      // ��ɫ������Ϸ, ref : TProcessData
    GDC2S_PLAYER_LEAVE_GAME,      // ��ɫ�뿪��Ϸ�����ǽ�����Ϸʧ��, ref : TProcessData
    GDC2S_SHUTDOWN_GODDESS,       // �����عر�Goddess, ref : TProcessData
    GDC2S_QUERY_STATISTIC_INFO,   // ��ȡͳ����Ϣ, ref : TProcessData
    GDC2S_TRANSFER_ROLE,          // ��ɫ����ת��, ref : ???
    GDC2S_QUERY_ROLE_LIST_ITEM,   // ��ȡ������ɫ�б���Ϣ, ref : TProcessData

    GDC2S_LOCK_OR_UNLOCK_ROLE_EXT,// ��ɫ���ݼ�/��������, �ò����з��ذ� ref : LOCK_OR_UNLOCK_ROLE_EXT
    GDC2S_CREATE_TONGNAME,        // �����������ref : CREATE_TONG_NAME
    GDC2S_QUERY_ROLE_LIST_IN_ZONE,// ��ȡһ��������һ���˺ŵ����н�ɫ���������ڷ�������ref : TProcessData
	GDC2S_CANCLE_TONGNAME,		  // ȡ��һ���������ע�� ref: TProcessData

	GDC2S_SYNC_ZONE_INFO,			// ֪ͨ������Ϣ���� ref: TRocessData, pDataBuffer=szGroup
	GDC2S_ROLE_BASE_OPER,			// �Խ�ɫ���ݵ�һЩ��������Э�� ref:TProcessData
	GDC2S_USE_CHICKEN_HORSE,		// ʹ�ü����� ref:CHICKEN_HORSE
	GDC2S_LOTTERY_REQUEST,			// ��ȯ�������
	GDC2S_LIMITE_OUTPUT_REQUEST,	// ȫ�����Ʋ�������
};

enum GODDESS_S2C_PROTOCOL_ID     // Goddess server ==> client
{
    GODDESS_S2C_PROTOCOL_BEGIN = PROTOCOL_BIG_PACKAGE_BEGIN,
    GDS2C_RETURN_ROLE_DATA,       // ���ؽ�ɫ����, ref : TProcessData + role data
    GDS2C_CREATE_ROLE_RESULT,     // ������ɫ���ݵĲ������, ref : TProcessData,pDataBuf[0]ȡֵ�μ�enum CREATE_ROLE_RESULT
    GDS2C_RETURN_ROLE_LIST_ITEM,  // ���ص�����ɫ�б���Ϣ, ref : TProcessData

    GDS2C_PING = PROTOCOL_NORMAL_PACKAGE_BEGIN + 1, // ping back, ref : PING_COMMAND    

    GDS2C_RETURN_ROLE_LIST,       // ���ؽ�ɫ�б�, ref : TProcessData + role list data(�������role_list_numΪ0������QueryFamilyListInZone()�Ľ��)
    GDS2C_SAVE_ROLE_DATA_RESULT,  // �洢��ɫ���ݷ��ؽ��, ref : TProcessData
    GDS2C_DELETE_ROLE_RESULT,     // ɾ����ɫ���ݷ��ؽ��, ref : TProcessData
    GDS2C_SHUTDOWN_CMD_RESPOND,   // �����¼�Э��: �ر��������Ӧ���, ref : TProcessData
    GDS2C_RETURN_STATISTIC_INFO,  // ����ͳ����Ϣ, ref : TProcessData

    GDS2C_RETURN_LOCK_OR_UNLOCK_ROLE_EXT, // ���ؽ�ɫ���ݼ�/�����Ĳ������, ref : TProcessData,  
                                          // TProcessData.pDataBuffer[0]:0 failed, TProcessData.pDataBuffer[0]:1 success

    GDS2C_CREATE_TONGNAME_RESULT, // ���ش���������Ľ��, ref : TProcessData
                                  // TProcessData.pDataBuffer[0]:0 failed, TProcessData.pDataBuffer[0]:1 success

    GDS2C_SET_STATISTIC_INFO_RESULT,   // ����ͳ����Ϣ���ؽ��, ref : TProcessData,
                                       // TProcessData.pDataBuffer[0]:0 failed, TProcessData.pDataBuffer[0]:1 success
    GDS2C_RETURN_ROLE_LIST_IN_ZONE,     // ����һ��������һ���˺ŵ����н�ɫ���������ڷ�������ref : TProcessData,ROLE_IN_ZONE
                                       // TProcessData.pDataBuffer[0]  : 0 failed, 1 success
                                       // &TProcessData.pDataBuffer[1] : (unsigned)uRoleCount + ROLE_IN_ZONE[uRoleCount]
	GDS2C_SYNC_ZONE_INFO_RET,		// ��������ͬ����� ref:TProcessData pDataBuffer=true false
	GDS2C_ROLE_BASE_OPER_RET,		// ���ؽ�ɫ���������Ľ�� ref:TProcessData
	GDS2C_USE_CHICKEN_HORSE_RET,	// ����ʹ�ü���������Ľ�� ref:CHICKEN_HORSE
	GDS2C_LOTTERY_RESPONSE,			// ��ȯ���
	GDS2C_LIMITE_OUTPUT_RESPONSE,	// ȫ�����Ʋ���Ӧ��
};

#pragma    pack(push, 1)
enum GODDESS_CREATE_RESULT
{
	GODDESS_CREATE_SUCCESS									= 1,
	GODDESS_CREATE_UNKNOW_FAILED							= -1,
	GODDESS_CREATE_FAMILY_NAME_FILTER						= -2,	//���������Ϸ�
	GODDESS_CREATE_FAMILY_NAME_EXIST						= -3,	//�������Ѵ���
	GODDESS_CREATE_OVER_MAX_ROLE_PER_ACCOUNT				= -4,	//�ʺ�����������ȫ������
	GODDESS_CREATE_OVER_MAX_ROLE_PER_ACCOUNT_PER_ZONE		= -5,	//�ʺ�������������������
	GODDESS_CREATE_ROLE_NAME_FILTER							= -6,	//��ɫ�����Ϸ�
	GODDESS_CREATE_ROLE_NAME_EXIST							= -7,	//��ɫ���Ѵ���
};

struct LOCK_OR_UNLOCK_ROLE : tagProtocolHeader
{
    bool bLock;
    char szRoleName[_NAME_LEN];
};

struct LOCK_OR_UNLOCK_ROLE_EXT : tagProtocolHeader2
{
    bool bLock;
    char szRoleName[_NAME_LEN];
};

struct CREATE_TONG_NAME : tagProtocolHeader2
{
    char szTongName[_NAME_LEN];
};

struct ROLE_IN_ZONE
{
	char szFamilyName[_NAME_LEN];
	char szGatewayName[_NAME_LEN];
	char szZoneName[_NAME_LEN];
};

struct DISCARD_ROLE_INFO
{
	DWORD	dwHigh;
	DWORD	dwLow;
	char	szName[_NAME_LEN];
	char	cRoleType;
	bool	bNameExpire;
};

struct SYNC_GROUP_INFO: tagProtocolHeader
{
	int		nAreaIdx;
	int		nGroupIdx;
};

struct CHICKEN_HORSE
{
	unsigned int uVersion;
	char cszKey[11];	//10 + 1 terminating null byte
};

//��ȯ
struct LOTTERY_REQUEST : tagProtocolHeader
{
	unsigned int uParam;
};

enum LOTTERY_PROTOCOL{
	enumLOTTERY_APLLY_ONE,			//����һ�Ž�ȯ
	enumLOTTERY_QUERY_HAS,			//��������ID��ѯӵ�н�ȯ��Ϣ
	enumLOTTERY_QUERY_PRIZED,		//��ѯ�н���ȯ

	enumLOTTER_PROTOCOL_COUNT,
};

#define LOTTERY_TYPE unsigned int

//request
struct LOTTERY_PLAYER_REQUEST : tagProtocolHeader
{
	char szFamilyName[_NAME_LEN];
	unsigned int uParam;
};

//response
struct LOTTERY{
	LOTTERY_TYPE uNumber;
	WORD uSequency;
	union{
		char szFamilyName[_NAME_LEN];
		unsigned int uPrizeType;
	};
};

struct LOTTERY_APPLY_ONE : LOTTERY
{
	char szAreaGroup[_NAME_LEN];
};

struct LOTTERY_HAS
{
	WORD uCount;
	char szFamilyName[_NAME_LEN];
	LOTTERY iaLotterys[1];
};

struct LOTTERY_PRIZE
{
	LOTTERY_TYPE uNumber;
	WORD uSequency;
	WORD uPrizeType;
	char szFamilyName[_NAME_LEN];
	char szAreaGroup[_NAME_LEN];
};

struct LOTTERY_PRIZES
{
	WORD uCount;
	LOTTERY_PRIZE iaLotterys[1];
};

//limite output
struct LIMITE_OUTPUT
{
	WORD uLimiteID;
	WORD uLimiteNum;
	WORD uOutputNum;
};

#pragma pack(pop)

#endif


