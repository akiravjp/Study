#ifndef _BISHOP_RELAY_PROTOCOL_H_
#define _BISHOP_RELAY_PROTOCOL_H_

#include "../ProtocolBasic.h"

enum B2R_PROTOCOL_ID // Bishop ==> Relay
{
    B2R_PROTOCOL_BEGIN = PROTOCOL_NORMAL_PACKAGE_BEGIN,
    B2R_GAME_SERVER_LOGIN_NOTIFY,    // Game server��½Bishopʱ֪ͨRelay, ref : tagGameSvrLoginRelay
    B2R_PLAYER_LOGIN_REQUEST,        // ���������Ϸ: ����Э��, ref : PLAYER_LOGIN_GAME_REQUEST
									 //	��ӰЭ��, ref : 
    B2R_DELETE_ROLE,                 // ��ѯ��ɫ�Ƿ����ɾ��, ref : tagNotifyToDelRole; ����: DELETE_ROLE_REQUEST
    B2R_EXT_POINTS_OPERATION_RESULT, // ���ӵ�������: ����Э��, ref : B2R_REPLY_OPERATE_EXTPOINT
    B2R_QUERY_IDENTITY_INFO,         // ��ѯ�����Ϣ������ԭ������relay��query map info ��Э�飬ref : tagQueryMapInfo
    B2R_PING,                        // ping , ref : PING_COMMAND
    B2R_QUERY_PLAYER_ONLINE_STATE,   // ��ѯ����Ƿ�����,����ͨ�����ñ�־λ��ʾ�Ƿ��ߺ�, ref: QUERY_PLAYER_ONLINE_STATE
    B2R_NOTIFY_KICK_ACCOUNT,         // ֪ͨRelay�������˺�����ȥ, ref: NOTIFY_KICK_ACCOUNT
    B2R_CREATE_ROLE_REQUEST,         // ���󴴽���ɫ
    B2R_QUERY_HOMETOWN_LIST,         // ��ѯ���ִ��б�
    B2R_ACCOUNT_USER_EXCHANGE_RESULT, // ��Ҷһ�ʱ���Ӧ��Э��, ref : KB2R_ACCOUNT_USER_EXCHANGE_RESULT
    B2R_ACCOUNT_TRANSFER_RESULT,      // �ʺ�֮��ת��Ӧ��Э��, ref : KB2R_ACCOUNT_TRANSFER_RESULT
    B2R_PLAYER_QUERY_TRANSFER_RESULT, // ���ת�ʲ�ѯӦ��Э��, ref : KB2R_PLAYER_QUERY_TRANSFER_RESULT
    B2R_PLAYER_FREEZE_FEE_RESULT,     // ��Ҷ���Ӧ��Э��, ref : KB2R_PLAYER_FREEZE_FEE_RESULT
    B2R_QUERY_ROLE_LIST,              // ��ѯ��ɫ�б�����Э��
    B2R_ACCOUNT_EXCHANGE_RESULT_EX,   // ��Ҽ���
    B2R_QUERY_ZONE_CHARGE_FLAG_RESULT,// ��ѯZoneChargeFlag
	B2R_NOTIFY_GROUP,				  // ֪ͨ��������
};

enum R2B_PROTOCOL_ID // Relay ==> Bishop
{
    R2B_PROTOCOL_BEGIN = PROTOCOL_NORMAL_PACKAGE_BEGIN,
    R2B_PLAYER_LOGIN_RESPOND,       // ��ҵ�½��������Ϣ:  ����Э��, ref : PLAYER_LOGIN_GAME_RESPOND
									// ��ӰЭ��: PLAYER_LOGIN_GAME_RESPOND_YY
    R2B_DELETE_ROLE_RESULT,         // ����ɾ����ɫ�Ľ��, ref : tagNewDelRoleResponse; ����: DELETE_ROLE_RESPOND
    R2B_EXT_POINTS_OPERATION,       // ���󸽼ӵ����: ����Э��, ref : R2B_OPERATE_EXTPOINT
    R2B_ADD_BLACK_LIST,             // ��ָ���ʺż��������: ����Э��, ref : δ��
    R2B_PLAYER_ENTER_GAME,          // ��ҽ�����Ϸ, ����Э��, ref : R2B_PLAYER_LOGIN
    R2B_PLAYER_LEAVE_GAME,          // ����뿪��Ϸ, ����Э��, ref : R2B_PLAYER_LOGOUT
    R2B_UPDATE_IDENTITY_INFO,       // ��Ӧ�������B2R_QUERY_IDENTITY_INFO��Ӧ��,ref : tagUpdateMapID
    R2B_PING,                       // ping back, ref : PING_COMMAND
    R2B_NOTIFY_GAME_WORLD_PROTOCOL_VERSION, // ֪ͨBishop��Ϸ����İ汾��,  ����Э��, ref: NOTIFY_GAME_WORLD_PROTOCOL_VERSION
    R2B_RETURN_PLAYER_ONLINE_STATE, // �����������״̬, �����ѯʱ�������ߺű�־���������,���ʱ�Ѿ����ߺ���, ����Э��, ref: QUERY_PLAYER_ONLINE_STATE
    R2B_CREATE_ROLE_RESPOND,        // ������ɫ������Ϣ
    R2B_SYNC_HOMETOWN_LIST,         // �������ִ��б�
    R2B_ACCOUNT_USER_EXCHANGE_REQUEST, // ��Ҷһ�ʱ�������Э��, ref : KR2B_ACCOUNT_USER_EXCHANGE_REQUEST
    R2B_ACCOUNT_TRANSFER_REQUEST,   // �ʺ�֮��ת������Э��, ref : KR2B_ACCOUNT_TRANSFER_REQUEST
    R2B_PLAYER_QUERY_TRANSFER_REQUEST, // ���ת�ʲ�ѯ����Э��, ref : KR2B_PLAYER_QUERY_TRANSFER_REQUEST
    R2B_PLAYER_FREEZE_FEE_REQUEST,  // ��Ҷ�������Э��, ref : KR2B_PLAYER_FREEZE_FEE_REQUEST
    R2B_QUERY_ROLE_LIST_RESPOND,    // ��ѯ��ɫ�б�����Э��
    R2B_ACCOUNT_EXCHANGE_REQUEST_EX,// ��Ҽ���
    R2B_QUERY_ZONE_CHARGE_FLAG_REQUEST,  // ��ѯZoneChargeFlag
	R2B_SET_AT_LEAST_GS_COUNT,		// ֪ͨ��ʼʱ���ٶ��ٸ�GS��������ҽ���, ref : KR2B_AT_LEAST_GS_COUNT
};

#pragma	pack(push, 1)

struct tagNotifyGroup : public tagProtocolHeader
{
	int nAreaIdx;
	int nGroupIdx;
};

struct	tagGameSvrLoginRelay : public tagProtocolHeader2 
{
	unsigned int	uGameSvrIp;
	int				nMapCount;
	int				nMapIdList[0];
};

struct tagNotifyToDelRole : public tagProtocolHeader2
{
	char	szRoleName[_NAME_LEN];
};

struct  NOTIFY_GAME_WORLD_PROTOCOL_VERSION : public tagProtocolHeader2 // Relay ==> Bishop, ֪ͨBishop��Ϸ����<==>�ͻ��˵�Э��汾��
{
    int nGameWorldProtocolLowerVersion;
    int nGameWorldProtocolUpperVersion;
};

struct  QUERY_PLAYER_ONLINE_STATE : public tagProtocolHeader2   // Bishop ==> Relay,��ѯ����Ƿ��Ѿ�����
{
    char szAccountName[_NAME_LEN];
};

struct NOTIFY_KICK_ACCOUNT : public tagProtocolHeader2
{
    char szAccountName[_NAME_LEN];
};

struct RETURN_PLAYER_ONLINE_STATE : public tagProtocolHeader2 // Relay ==> Bishop, ������ҵ�����״̬
{
    int  nOnlineState; // ����Ƿ�����? (true/false)
};


struct PLAYER_LOGIN_GAME_REQUEST : tagProtocolHeader2   // Bishop ==> Relay, ���ѡ���ɫ�����½
{
    char            szAccountName[_NAME_LEN];
    DWORD           dwRoleID;
	tagExtPointInfo	ExtPointInfo;			// ���õĸ��͵�
	tagExtPointInfo	ChangePointInfo;		// �仯�ĸ��͵�
	unsigned long 	ulLeftTime;				// ʣ��ʱ��,����Ϊ��λ,���������Ͱ�ʱ(���죬����)
    unsigned long   ulLimitPlayTimeFlag;     // �����Ա�־λ
    unsigned long   ulLimitOnlineSecond;     // �������ۼ�����ʱ��
    unsigned long   ulLimitOfflineSecond;    // �������ۼ�����ʱ��
};

typedef enum // ��ö������: ������������Ϸ��ʱ��, Relay������������Bishop
{
    LOGIN_GAME_SUCCESS,         // ��½���󱻽���
    LOGIN_GAME_MAINTENANCE,     // ϵͳά����ͨ������Ϊ�Ҳ���MapID��Ӧ��Game server,����Ҳ�޷���̬���������ͼ
    LOGIN_GAME_OVERLOADED,      // �ҵ���MapID��Ӧ��Game server,���Ƿ����������������޷���½
    LOGIN_GAME_UNKNOWN_ERROR    // ����δ֪ԭ����ɵ��޷���½,����: �Ѿ���½ʱ,û�о����ߺžͳ��Ե�½
} LOGIN_GAME_RESPOND_CODE;

struct PLAYER_LOGIN_GAME_RESPOND : tagProtocolHeader2   // Relay ==> Bishop, ��ҵ�½�������Ӧ
{
	int			    nRespondCode; // LOGIN_GAME_RESPOND_CODE
    DWORD           dwRoleID;
	GUID		    Guid;
	DWORD			dwLoginIP;
	WORD	        wLoginPort;
};

struct PLAYER_LOGIN_GAME_RESPOND_YY : tagProtocolHeader2 // same with upper
{
	int			    nPermit;
	int				nServerIndex;
	char			szRoleName[32];
	GUID		    Guid;
	DWORD			dwLoginIP;
	WORD	        wLoginPort;
};

struct KR2B_AT_LEAST_GS_COUNT : tagProtocolHeader
{
	int nCount;
};

struct PLAYER_ENTER_GAME : tagProtocolHeader2   // Relay ==> Bishop, ֪ͨ��Ϣ: ��ҵ�½��Ϸ
{
	char szAccountName[_NAME_LEN];
};

struct PLAYER_LEAVE_GAME : tagProtocolHeader2   // Relay ==> Bishop, ����˳���Ϸ
{
	char szAccountName[_NAME_LEN];
};

struct REQUEST_RELAY_DELETE_ROLE : tagProtocolHeader2 // Bishop ==> Relay, ����ɾ����ɫ(ѯ���Ƿ����ɾ��,�����ǲ���ɾ����)
{
    char    szAccountName[_NAME_LEN];
	DWORD   dwRoleID;
};

struct RELAY_DELETE_ROLE_RESPOND : tagProtocolHeader2 // Relay ==> Bishop, ����ɾ����ɫ�Ľ��(true/false)
{
	int			nResult; // ɾ����ɫ�Ľ��(true/false)
};

struct EXT_POINT_OPERATION_REQUEST : tagProtocolHeader2 // Relay ==> Bishop,���������ӵ����
{
	char szAccountName[_NAME_LEN];
	union
	{
		unsigned uExtPointIndex;    // ��Ҫ�ı�ĸ��ӵ������
		unsigned uSilverType;       // ��Ʊ�����ͣ���16λ��0����ʾ����Ʊ��1����ʾС��Ʊ��
		//             ��16λ��0��תΪ��������תΪ�����ܣ��£�
	};

	int      nChangeValue;      // ���ӵ㱻�޸ĵ�ֵ�������ɸ���������Ʊ����Ŀ

	unsigned uFlag;             // �����0��ʾ���ӵ�ı仯�������CHANGE_EXT_POINT_SILVER : ��ʾ��Ʊ�Ĵ���
	int      nPlayerDataIndex;  // ������ݵ������ţ�����������Э��	
};

struct EXT_POINT_OPERATION_RESPOND : tagProtocolHeader2 // Bishop ==> Relay, ���ӵ�����Ľ��
{
	int         nResult;
	char        szAccountName[_NAME_LEN];
	int         nFlag;
	int         nPlayerDataIndex;  // ������ݵ������ţ�����������Э��	
};

struct KB2R_CREATE_ROLE_REQUEST : tagProtocolHeader2 // Bishop --> Relay, ���󴴽���ɫ
{
    char   szAccountName[_NAME_LEN];
};

struct KR2B_CREATE_ROLE_RESPOND : tagProtocolHeader2 // Bishop --> Relay, ������ɫ����Ӧ
{
    bool   bSucceed;
    size_t uDataLen;
    BYTE   byData[0];
};

// ��ѯ�ִ���,����Э��
struct KB2R_QUERY_HOMETOWN_LIST : public tagProtocolHeader2
{
    int nReserved;
};

// ͬ�����ִ���,����Э��
struct KR2B_SYNC_HOMETOWN_LIST : public tagProtocolHeader2
{
    size_t uDataLen;
    BYTE   byData[0];
};

// KR2B_SYNC_HOMETOWN_LISTЭ���������������ִ����ݵ����size
#define MAX_HOMETOWN_MAP_DESC_DATA_SIZE   1024

struct KR2B_ACCOUNT_USER_EXCHANGE_REQUEST : public tagProtocolHeader2
{
    char   szAccount[_NAME_LEN];
    DWORD  dwExchangeType;
    DWORD  dwDestAmount;                                    // �һ��ɵ���Ŀ
    DWORD  dwSrcAmount;                                     // ���һ�����Ŀ
};

struct KB2R_ACCOUNT_USER_EXCHANGE_RESULT : public tagProtocolHeader2
{
    char   szAccount[_NAME_LEN];
    DWORD  dwExchangeType;
    DWORD  dwDestAmount;                                    // �һ��ɵ���Ŀ
    DWORD  dwSrcAmount;                                     // ���һ�����Ŀ
    
    int    nResult;
};

struct KR2B_ACCOUNT_TRANSFER_REQUEST : public tagProtocolHeader2
{
    long long   llTransferGUID;                             // ���ײ�����Ψһ���,����Ϸ���紫��Paysys.�������ѯ������
    char        szAccountDest[_NAME_LEN];                   // Ŀ���˻�
    char        szAccountSrc[_NAME_LEN];                    // Դ�˻�
    DWORD       dwTransferFlag;
    DWORD       dwTransferType;                             // 1: �Ƶ�ת��; 2: ���ת��; 3: ��չ��ת��
    DWORD       dwExtPoint;                                 // ��չ��ת��ʱ����չ������
    DWORD       dwTransferAmount;                           // ת�ʵ���Ŀ
};

struct KB2R_ACCOUNT_TRANSFER_RESULT : public tagProtocolHeader2
{
    long long   llTransferGUID;                             // ���ײ�����Ψһ���,����Ϸ���紫��Paysys.�������ѯ������
    char        szAccountDest[_NAME_LEN];                   // Ŀ���˻�
    char        szAccountSrc[_NAME_LEN];                    // Դ�˻�
    DWORD       dwTransferFlag;
    DWORD       dwTransferType;                             // 1: �Ƶ�ת��, 2: ���ת��, 3: ��չ��ת��
    DWORD       dwExtPoint;                                 // ��չ��ת��ʱ����չ������
    DWORD       dwTransferAmount;                           // ת�ʵ���Ŀ
    int         nResult;                                    // 1 �ɹ�, 2: ʧ��, 3: �Ҳ����ʺ�, 1100: �������
};

struct KR2B_PLAYER_QUERY_TRANSFER_REQUEST : public tagProtocolHeader2
{
    long long llTransferGUID;                               // ���ײ�����Ψһ���, ����Ϸ���紫��Paysys
};

struct KB2R_PLAYER_QUERY_TRANSFER_RESULT : public tagProtocolHeader2
{
    long long llTransferGUID;                               // ���ײ�����Ψһ���, ����Ϸ���紫��Paysys
    DWORD     dwTransferTime;
    char      szAccountDest[_NAME_LEN]; 
    char      szAccountSrc[_NAME_LEN]; 
    DWORD     dwTransferFlag;
    DWORD     dwTransferType;
    DWORD     dwExtPoint;                                   // ������չ�㶳��, ���ֶ�Ϊ��չ������0��7��
    DWORD     dwTransferAmount;
    DWORD     dwTransferResult;

    int       nResult;
};

struct KR2B_PLAYER_FREEZE_FEE_REQUEST : tagProtocolHeader2
{
    long long   llFreezeGUID;
    char        szAccount[_NAME_LEN];
    DWORD       dwFreezeFlag;
    DWORD       dwFreezeType;
    DWORD       dwExtPoint;                                 // ������չ�㶳�ᣬ���ֶ�Ϊ��չ������0��7��
    DWORD       dwFreezeAmount;
};

struct KR2B_QUERY_ROLE_LIST_RESPOND : tagProtocolHeader2
{
    unsigned        uDataLen;
    unsigned char   byRoleList[0];
};

struct KB2R_PLAYER_FREEZE_FEE_RESULT : tagProtocolHeader2
{
    long long   llFreezeGUID;
    char        szAccount[_NAME_LEN];
    DWORD       dwFreezeFlag;
    DWORD       dwFreezeType;
    DWORD       dwExtPoint;                                 // ������չ�㶳�ᣬ���ֶ�Ϊ��չ������0��7��
    DWORD       dwFreezeAmount;

    int         nResult;
};

struct KR2B_ACCOUNT_EXCHANGE_REQUEST_EX : tagProtocolHeader2 
{
    char        szSrcAccount[_NAME_LEN];
    char        szDestAccount[_NAME_LEN];
    DWORD       dwExchangeType;
    DWORD       dwDestAmount;
    DWORD       dwSrcAmount;
};

struct KB2R_ACCOUNT_EXCHANGE_RESULT_EX : tagProtocolHeader2
{
    char        szSrcAccount[_NAME_LEN];
    char        szDestAccount[_NAME_LEN];
    DWORD       dwExchangeType;
    DWORD       dwDestAmount;
    DWORD       dwSrcAmount;

    int         nResult;
};

struct KB2R_QUERY_ROLE_LIST : tagProtocolHeader2
{
    char        szAccount[_NAME_LEN];
};

struct KR2B_QUERY_ZONE_CHARGE_FLAG_REQUEST : tagProtocolHeader2
{
    int nReserved;
};

struct KB2R_QUERY_ZONE_CHARGE_FLAG_RESULT : tagProtocolHeader2
{
    int  nZoneChargeFlag;
    int  nZoneID;
    char szZoneName[32];
};


#pragma pack(pop)

#endif

