#ifndef _BISHOP_CLIENT_PROTOCOL_H_
#define _BISHOP_CLIENT_PROTOCOL_H_

#include "../ProtocolBasic.h"

#define BISHOP_PROTOCOL_VERSION 3

enum B2C_PROTOCOL_ID    // Bishop ==> Client
{
    B2C_PROTOCOL_BEGIN = PROTOCOL_NORMAL_PACKAGE_BEGIN,
    B2C_ACCOUNT_VERIFY_RESULT,          // ��ҵ�½�������֤�Ľ��, ref : KLoginAccountInfo
    B2C_RETURN_ROLE_LIST,               // ���ؽ�ɫ�б���ͻ���, ref : TProcessData + role list data 
    B2C_CREATE_OR_DELETE_ROLE_RESULT,   // �½�����ɾ����ɫ�Ľ��, ref : tagNewDelRoleResponse
    B2C_NOTIFY_PLAYER_LOGIN_GAMESVR,    // ֪ͨ�ͻ��ε�½Game server, ref : tagNotifyPlayerLogin
	B2C_NOTIFY_GAME_VERSION_INFO,		// ���������Ӹս�����ʱ����,����Ϸ�汾��Ϣ�����ͻ���, ref : tagNotifyGameVersion
    B2C_SYNC_HOMETOWN_LIST,             // ͬ�����ִ��б�
    B2C_CREATE_ROLE_RESPOND,            // ������ɫӦ�𣬽���Э��
    B2C_DELETE_ROLE_RESPOND,            // ɾ����ɫӦ�𣬽���Э��
    B2C_RETURN_ROLE_LIST_IN_ZONE,       // ���ش����еĽ�ɫ�� ref : TProcessData + ROLE_IN_ZONE
	B2C_NOTIFY_PASSPOD_VERIFY,			// ֪ͨ�ͻ�����֤�ܱ�
	B2C_PASSPOD_VERIFY_RESULT,			// �ܱ���֤���
};

enum C2B_PROTOCOL_ID    // Client ==> Bishop
{
    C2B_PROTOCOL_BEGIN = PROTOCOL_NORMAL_PACKAGE_BEGIN,
    C2B_PLAYER_LOGIN_INFO,      // ��ҵ�½��Ϣ(�ʺ�,����), ref : KLoginAccountInfo
    C2B_CREATE_ROLE,            // ���󴴽���ɫ, ref : NEW_PLAYER_COMMAND, ����Ŀ�Զ�����ͳһ�ṹ
    C2B_DELETE_ROLE,            // ����ɾ����ɫ, ref : tagDBDelPlayer
    C2B_GAME_LOGIN_REQUEST,     // ���ѡ��һ����ɫ�������½��Ϸ, ref : tagDBSelPlayer
    C2B_QUERY_HOMETOWN_LIST,    // �������ִ��б�
	C2B_SEL_SUB_SERVER,			// ѡ��һ���ӷ�������ref : tagDBSelSubServer
    C2B_PLAYER_LOGIN_INFO_SD,   // ʢ����ҵ�½��Ϣ, ref : KLoginAccountInfoSD
    C2B_PLAYER_LOGIN_INFO_AND_LOGIN_KEY,// ʹ���Ŷӵ�½��Э��
	C2B_PASSPOD_VERIFY,			// �ܱ���Ϣ
	C2B_PLAYER_LOGIN_INFO_YY,   // yy��ҵ�½��Ϣ, ��ʵ��ͨ�õ���֤Э����
};

#pragma	pack(push, 1)

#define	LOGIN_ACCOUNT_MIN_LEN	6
#define LOGIN_ACCOUNT_MAX_LEN	16
#define LOGIN_PASSWORD_MIN_LEN	8
#define LOGIN_PASSWORD_MAX_LEN	16
#define LOGIN_ROLE_NAME_MIN_LEN	6
#define	LOGIN_ROLE_NAME_MAX_LEN	16

//login action return value
//the folloin' value is used in login connect operaion
#define	LOGIN_ACTION_FILTER					0xff0000	//��½�����еĲ������͹�����ֵ
#define LOGIN_A_CONNECT						0x010000	//����
#define	LOGIN_A_NEWACCOUNT					0x020000	//�½��˺ţ��˺ŷ�������
#define	LOGIN_A_SERVERLIST					0x030000	//��ȡ�������б��˺ŷ�������
#define	LOGIN_A_REPORT						0x040000	//֪ͨ����������(���������������)
#define	LOGIN_A_LOGIN						0x050000	//��½���������˺š���Ϸ��������
#define	LOGIN_A_LOGOUT						0x060000	//ע��
#define	LOGIN_A_CHARACTERLIST				0x070000	//��ȡ��ɫ�б���Ϸ��������


#define	LOGIN_R_REQUEST						0	//when the login request is send form client to server
#define	LOGIN_R_SUCCESS						1
#define	LOGIN_R_FAILED						2
#define	LOGIN_R_ACCOUNT_OR_PASSWORD_ERROR	3
#define	LOGIN_R_ACCOUNT_EXIST				4
#define	LOGIN_R_TIMEOUT						5
#define	LOGIN_R_IN_PROGRESS					6
#define	LOGIN_R_NO_IN_PROGRESS				7
#define	LOGIN_R_VALID						8    //�Ϸ�
#define	LOGIN_R_INVALID						9    //�Ƿ�
// Add by Freeway Chen in 2003.7.1
#define LOGIN_R_INVALID_PROTOCOLVERSION     10  // Э��汾�����ݣ���� KProtocolDef.h's KPROTOCOL_VERSION
#define LOGIN_R_FREEZE						11	// ������
#define LOGIN_R_SMS_LOCK					12	// �˺ű����Ŷ���
#define LOGIN_R_NOT_ACTIVE					13	// �˺�δ����
#define LOGIN_R_KICKOUT_OLDACC				14	// �˺��߳���
#define LOGIN_R_ACC_IN_GATEWAY				15	// �˺Ŷ���������
#define LOGIN_R_INVALID_PROTO				16	// ��Ϊʹ���˷ǹٷ��ͻ��ˣ��˺ű���ʱ���ᣬ���Ժ��ٵ�¼
// ����Paysys���뼤����Ĺ���:
#define LOGIN_R_CDKEY                       17  // ���뼤������� 
#define LOGIN_R_ACTIVE                      18  // �˺�δ������,��Ҫ������
#define LOGIN_R_BLACK_LIST                  19  // ������������Σ��ʺű�Paysys��������������
// 2005-10-04 : ����"ϵͳά��"�ķ��ش���
#define LOGIN_R_SYSTEM_MAINTENANCE          20  // ϵͳά����
// 2005-10-13: ��֤�ù�,�����˺�������Ϸ��(�������Զ��ߺ�)
#define LOGIN_R_SUCCESS_AND_IN_GAME         21   
// ���˺������ֿ��˺�(������<�������>���͵�����),����û�м���,�뵽"xxx"��ҳȥ���� ...
#define LOGIN_R_ACCOUNT_CARD_UNACTIVE       22
// ���ʺŵ�¼ʱ�����޸�����
#define LOGIN_R_CHANGE_PASSWORD             23
// ����ļ����벻����
#define LOGIN_R_ACTIVE_CODE_NOT_EXIST       24
// ����ļ������Ѿ�ʹ�ù���
#define LOGIN_R_ACTIVE_CODE_ALREADY_USED    25
// ���ʺ�Ϊ�����Զ��󣬲������¼
#define LOGIN_R_LIMIT_ACCOUNT               26

#define LOGIN_R_PASSPOD_SYSTEM              27 // PASSPODϵͳ����
#define LOGIN_R_PASSPOD_TOKEN_USED          28 // ������ʹ��
#define LOGIN_R_PASSPOD_TOKEN_FAILED        29 // ��֤ʧ��
#define LOGIN_R_PASSPOD_TOKEN_EXPIRED       30 // ���ƹ���
#define LOGIN_R_PASSPOD_TOKEN_NOTFOUND      31 // ���ư�δ�ҵ�
#define LOGIN_R_PASSPOD_TOKEN_DISABLE       32 // �����Ѿ����ã���ʧ��

#define LOGIN_R_LOGIN_KEY_INVALID           33  // �Ŷ��õ���KEY�Ѿ�ʧЧ
#define LOGIN_R_MUTI_ACCOUNT_ONLINE			34  // ͬһ���֤�Ķ���˺�ͬʱ��½
#define LOGIN_R_USER_INFO_MISSED			35  // ʵ������Ϣ��ȫ�����֤����ϵ��ʽȱһ���ɣ�

#define LOGIN_R_PASSPOD_MATRIX_FAILED		36 // ������֤ʧ��
#define LOGIN_R_PASSPOD_MATRIX_CARDINVALID	37 // ������Ч
#define LOGIN_R_PASSPOD_MATRIX_NOTFOUND		38 // ����δ�ҵ�


// �ַ�������
//#define _KG_STRING_SIZE_ID_CARD             22  // ���֤����
#define _KG_STRING_SIZE_SD_TOKEN            384 // ʢ��Token����
#define _KG_STRING_SIZE_YY_TOKEN            600 // yy Token����
#define _KG_STRING_SIZE_DEFAULE_RESERVED    16  // Ĭ�ϱ�������

#define KG_PASSPOD_NONE						0
#define KG_PASSPOD_EKEY						1	//����
#define KG_PASSPOD_ECARD					2	//�ܱ���
#define KG_PASSPOD_ECARD_SEED_NUM			3

enum KLOGIN_EX_FLAG
{
	enumEX_JUST_LOGIN		= 0x1,
};

struct KLoginStructHead
{
	unsigned short	Size;		//size of the struct, if the struct is been inherit, the size is ref the the derive struct
	int				Param;		//be one of the LOGIN_R_* define value combin with a LOGIN_A_* value.
};

// ��ҵ�½(�ϴ��ʺ�,����)�Լ���֤�������������ṹ,ע: �����������!
struct KLoginAccountInfo : KLoginStructHead 
{
	char	        Account[_NAME_LEN];	//account
	KSG_PASSWORD    Password;
	unsigned long   nLeftTime;     //ʣ��ʱ��    
    int             nGameServerProtocolVersion;	
    int             nBishopProtocolVersion;
	union
	{
		unsigned long   nLeftTimeOfPoint;   // ʣ��ʱ���У�������Ӧ��ʱ��
		BOOL			bKickOutOldAcc;
	};
    char          szActivateCode[_NAME_LEN]; // �����룬���õ�ʱ����0
    unsigned char byMachineID[16];               // ����ID

    unsigned long ulLastLoginTime;           // �ϴε�½ʱ��,ע��,ֻ������ҵ�½��֤ͨ���������,��ֵ����Ч,������0.
    unsigned long ulLastLoginIP;             // �ϴε�½IP,ע��,ֻ������ҵ�½��֤ͨ���������,��ֵ����Ч,������0.
    unsigned long uLimitPlayTimeFlag;        // �����Ա�־λ
    unsigned long uLimitOnlineSecond;        // �������ۼ�����ʱ��
    unsigned long uLimitOfflineSecond;       // �������ۼ�����ʱ��
    unsigned      uGatewayID;

    BYTE          byPasspodVersion;          // �ܱ��汾
    BYTE          byPasspodMode;             // �ܱ���֤��ʽ
    char          szTokenPassword[10];       // ��������

	DWORD		  dwExFlag;					 // ��չ���λ
};

// ����Ŷӵ�½
struct KLoginAccountInfoAndLoginKey : public KLoginAccountInfo
{
    unsigned uLoginQueuePlayerID;
    GUID LoginKey;
};

// ʢ����ҵ�½(�ϴ��ʺ�,����)�Լ���֤�������������ṹ
struct  KLoginAccountInfoSD : public KLoginAccountInfo 
{
    char         szIDCard[KG_STRING_SIZE_ID_CARD];
    int          nIsIDCardValid;
    char         szToken[_KG_STRING_SIZE_SD_TOKEN];
    char         szReserved[_KG_STRING_SIZE_DEFAULE_RESERVED];
};

// YY��¼Э�飬ʹ�������ʺ�+��Կ���ܵ�����
struct  KLoginAccountInfoYy : public KLoginAccountInfoAndLoginKey 
{
	char         szToken[_KG_STRING_SIZE_YY_TOKEN];
};

struct tagKB2C_PASSPOD_VERIFY : tagProtocolHeader
{
	BYTE byPasspodVersion;    // �ܱ��汾
	BYTE byPasspodMode;       // �ܱ���֤��ʽ
	char szMatrixPosition[9]; // ��Ҫ�û�����ľ��������λ��

	int nReturn;
};

typedef tagKB2C_PASSPOD_VERIFY KB2C_PASSPOD_VERIFY_RESULT, KB2C_PASSPOD_VERIFY_NOTIFY;

struct KC2B_PASSPOD_VERIFY : tagProtocolHeader
{
	union
	{
		char szTokenPassword[10]; // ��������
		char szMatrixPassword[9]; // ��Ӧ����λ�õ�����
	};
};

// Client ==> Bishop, ����Э��, ��������½����(Bishop), Э��: C2B_PLAYER_LOGIN_INFO
struct  KC2B_PLAYER_LOGIN_GATEWAY_REQUEST : public tagProtocolHeader 
{
    char         szAccountName[_NAME_LEN];
    KSG_PASSWORD Password;
    char         szActivateCode[_NAME_LEN]; // ������,û��ʱ����
    int          nGameWorldProtocolVersion;	
    int          nGatewayProtocolVersion;
};

// Bishop ==> Client, ����Э��, ��������½����(Bishop)�Ľ��, Э��: B2C_ACCOUNT_VERIFY_RESULT
struct  KB2C_PLAYER_LOGIN_GATEWAY_RESPOND : public tagProtocolHeader 
{
    int           nRespondCode;
    unsigned long ulEndOfDayTime;
    unsigned long ulLeftTimeOfPoint;  
    unsigned long ulLastLoginTime;      // �ϴε�½ʱ��,ע��,ֻ������ҵ�½��֤ͨ���������,��ֵ����Ч,������0.
    unsigned long ulLastLoginIP;        // �ϴε�½IP,ע��,ֻ������ҵ�½��֤ͨ���������,��ֵ����Ч,������0.
    unsigned long ulLimitPlayTimeFlag;   // �����Ա�־λ
    unsigned long ulLimitOnlineSecond;   // �������ۼ�����ʱ��
    unsigned long ulLimitOfflineSecond;  // �������ۼ�����ʱ��
    int           nGatewayProtocolVersion;
    int           nGameWorldLowerVersion;
    int           nGameWorldUpperVersion;
};

struct tagDBSelPlayer : public tagProtocolHeader2
{
	char	szRoleName[_NAME_LEN];
};

struct tagDBSelSubServer : public tagProtoHeader
{
	unsigned char ucServerIndex;
};

struct tagDBDelPlayer : public tagProtocolHeader
{
	char	        szAccountName[_NAME_LEN];
    KSG_PASSWORD    Password;
	char	        szRoleName[_NAME_LEN];
};


#define ROLE_LOGIN_RESULT_SUCCESS           1   // �����½,ref: tagNotifyPlayerLogin
#define ROLE_LOGIN_RESULT_MAINTENANCE       2   // ��ɫ���ڵķ���������ά����, ref: tagNotifyPlayerLogin
#define ROLE_LOGIN_RESULT_IS_FULL           3   // ��ɫ���ڷ���������,ref: tagNotifyPlayerLogin
#define ROLE_LOGIN_RESULT_UNKNOWN           4   // ������δ֪����ͨ�����ڽ�ɫ���ݷ���,�������ݴ��󣬱���ס�ˣ��ȵ�

struct tagNotifyPlayerLogin : public tagProtocolHeader
{
	char            szRoleName[_NAME_LEN];
    int             nResult; // ��ֵ��������"ROLE_LOGIN_RESULT_ ... ..."
	GUID            guid;
	UINT			nIPAddr;
	unsigned short	wPort;
};

struct KC2B_GAME_LOGIN_REQUEST : tagProtocolHeader
{
    DWORD dwRoleID;
};

// ��������¼��Ϸ����Ӧ,����Э��
struct KB2C_ROLE_LOGIN_RESPOND :  tagProtocolHeader
{
    int             nRespondCode;
    DWORD           dwRoleID;
	GUID            guid;
	DWORD			dwIPAddr;
	WORD	        wPort;
};

struct tagNotifyGameVersion : public tagProtocolHeader
{
	int				nMinVersion;
	int				nCurrentVersion;
};

// ������ɫ, ����Э��
struct KC2B_CREATE_ROLE_REQUEST : public tagProtocolHeader
{
    size_t uDataLen;
    BYTE   byData[0];
};

// ɾ����ɫ, ����Э��
struct KC2B_DELETE_ROLE_REQUEST : public tagProtocolHeader
{
    DWORD           dwRoleID;
    KSG_PASSWORD    Password;
};

// ��ѯ�ִ���,����Э��
struct KC2B_QUERY_HOMETOWN_LIST : public tagProtocolHeader
{
    int nReserved;
};

// ͬ���ִ���������,����Э��
struct KB2C_SYNC_HOMETOWN_LIST : public tagProtocolHeader
{
    size_t uDataLen;
    BYTE   byData[0];
};

// ��ѯ��ɫ�б�,����Э��
struct KB2C_RETURN_ROLE_LIST : public tagProtocolHeader
{
    size_t uDataLen;
    BYTE   byData[0];
};

// ���ش�����ɫӦ����Ϣ,����Э��
struct KB2C_CREATE_ROLE_RESPOND : public tagProtocolHeader
{
    bool    bSucceeded;
    size_t  uDataLen;
    BYTE    byData[0];
};

// ����ɾ����ɫӦ����Ϣ,����Э��
struct KB2C_DELETE_ROLE_RESPOND : public tagProtocolHeader
{
    DWORD   dwRoleID;
    bool    bSucceeded;
    BYTE	cFailReason;
};

struct KC2B_QUERY_ROLE_LIST_IN_ZONE : public tagProtocolHeader
{
    int nReserved;
};

#pragma pack(pop)

#endif
