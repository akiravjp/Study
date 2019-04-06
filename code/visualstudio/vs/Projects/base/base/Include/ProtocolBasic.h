#ifndef _GLOBALDEF_H_
#define _GLOBALDEF_H_

// ����幤���޹ص�ȫ���Եĺ�,�ṹ����:

// PROTOCOL_BIG_PACKAGE_BEGIN֮ǰЭ����������ڲ�ʹ��!
#define PROTOCOL_BIG_PACKAGE_BEGIN		10
// ��PROTOCOL_BIG_PACKAGE_BEGIN--PROTOCOL_NORMAL_PACKAGE_BEGIN֮��Ϊ���Э���!
#define PROTOCOL_NORMAL_PACKAGE_BEGIN	31



//�ַ������ȶ���
#define _NAME_LEN               32
//���֤�ַ�������
#define KG_STRING_SIZE_ID_CARD  19

#pragma	pack(1)
#pragma warning(disable: 4200)

#define PROTOCOL_MSG_TYPE unsigned char
#define PROTOCOL_MSG_SIZE (sizeof(PROTOCOL_MSG_TYPE))

#define INTRANER_IP					0
#define INTERNET_IP					1

typedef struct tagProtocolHeader
{
    union
    {
	    PROTOCOL_MSG_TYPE	cProtocol;
	    PROTOCOL_MSG_TYPE	ProtocolType;
	};
} ProtocolHeader, tagProtoHeader;

typedef struct tagProtocolHeader2 :  public tagProtocolHeader
{
	unsigned long ulIdentity;
} ProtocolHeader2;

struct tagLengthFirstProtoHeader
{
	unsigned short uLength;
	union
	{
		PROTOCOL_MSG_TYPE	cProtocol;
		PROTOCOL_MSG_TYPE	ProtocolType;
	};
};

struct tagSubProtoHeader
{
	PROTOCOL_MSG_TYPE	cSubProtocol;
};

struct PrtocolLengthHeader : tagProtoHeader
{
	unsigned short		Length;
};

struct tagBiProtoHeader : PrtocolLengthHeader
{
	PROTOCOL_MSG_TYPE	cSubProtocol;
};

struct tagBiProtoHeaderNoLen : tagProtoHeader
{
	PROTOCOL_MSG_TYPE	cSubProtocol;
};

struct TProcessData
{
	unsigned char	nProtoId;
	size_t			nDataLen;
	unsigned long	ulIdentity;
	bool			bLeave;
	char			pDataBuffer[1];//ʵ�ʵ�����
};

#define KSG_PASSWORD_MAX_SIZE 64

typedef struct tagKSG_PASSWORD
{
    char szPassword[KSG_PASSWORD_MAX_SIZE];    // ���ڲ���MD5���ַ�����������32���ַ�������ĩβ'\0'����Ҫ����33���ռ䣬���ʹ��64
} KSG_PASSWORD;

//��չ��
#define MAX_EXT_POINT_COUNT   8

struct tagExtPointInfo
{
	DWORD nExtPoint[MAX_EXT_POINT_COUNT];
};

enum Account_State_Type
{
    OFFLINE = 0x00000001,                   // ���߹һ�
    ACTIVED_DYNAMIC_PASSWORD = 0x00000002,  // �����˶�̬�������
};

struct tagGuidableInfo : public tagProtocolHeader2
{
	GUID            guid;
    tagExtPointInfo ExtPointInfo;       //���õĸ��͵�
	tagExtPointInfo ChangePointInfo;	//�仯�ĸ��͵�
	DWORD			nTotalLeftTime;		//�ܵĿ���Ϸʱ��,����Ϊ��λ(�������ºͼƵ�)
	DWORD			nLeftTimeOfPoint;	//������Ӧ��ʣ��ʱ��,����Ϊ��λ��nTotalLeftTime-nLeftTimeOfPoint���Եõ�����ʱ��	
    DWORD           dwLeftMoney;
    unsigned long   uLimitPlayTimeFlag;  // �����Ա�־λ
    unsigned long   uLimitOnlineSecond;  // �������ۼ�����ʱ��
    unsigned long   uLimitOfflineSecond; // �������ۼ�����ʱ��
    int             nChargeFlag;
    unsigned int    uAccountState;       // ��λʹ�ã�ÿλ��������ö��Account_State_Type�ж���
    char            szPhoneNumber[20];
	size_t	        datalength;
	char	        szData[0];
};

#define	FAIL_REASON_NONE		                0
#define FAIL_REASON_VALID_PWD	                1
#define	FAIL_REASON_NOT_ALLOW	                2
#define	FAIL_REASON_UNKNOWN                     3
#define FAIL_REASON_NAME_FILTER                 4
#define FAIL_REASON_NAME_EXIST                  5
#define FAIL_REASON_OVER_MAX_ROLE_PER_GATEWAY   6
#define FAIL_REASON_OVER_MAX_ROLE_PER_ZONE      7
#define FAIL_REASON_ROLE_NAME_FILTER			8
#define FAIL_REASON_ROLE_NAME_EXIST				9


//ɾ�����½���ɫ�ķ�����Ϣ��������
struct tagNewDelRoleResponse : tagProtocolHeader2
{
	char	szRoleName[_NAME_LEN];
    bool	bSucceeded;	
	BYTE	cFailReason;
};

struct tagQueryMapInfo : public tagProtocolHeader
{
	unsigned int		uTime;
};

struct tagUpdateMapID : public tagProtocolHeader
{	
	//  For example : Are your clear older information when it update local information.	 
	bool bRelay;	//�����relay����1�������gameserver����0
	int nMapCount;	//�����relay����0
	int nServerIndex; //��̨�������ǵڼ�̨
	int nMaxPlayer;
	char szServerName[32];
	int snMapID[0];	// C4200 warning
};
struct tagServerInfo
{
	unsigned char ucServerNum;
};

struct tagServerInfoElem
{
	char nServerIndex;
	char nPercent;
	WORD nSvrFuncType;
	DWORD dwFuncList;
	char szServerName[32];
};

typedef struct tagPING_COMMAND : public tagProtocolHeader
{
	DWORD dwTime;
} PING_COMMAND;

struct tagSvrConnectedInitReady : public tagProtocolHeader
{
	bool	bReady;
};

// �һ�����
enum _Exchange_Type
{
    _COIN_EXCHANGE_SECOND  = 1,                             // ��Ҷһ��Ƶ�
    _COIN_EXCHANGE_DATE    = 2                              // ��Ҷһ���ʱ

};

// ת�ʱ�־
enum _Transfer_Flag
{
    _TRANSFER_FREEZE_FEE    = 1,                            // ת�ʶ���Ľ��
    _TRANSFER_UNFREEZE_FEE  = 2                             // ת��δ����Ľ��
};

// ת������
enum _Transfer_Type
{
    _TRANSFER_SECOND   = 1,                                 // �Ƶ�
    _TRANSFER_COIN     = 2,                                 // ���
    _TRANSFER_EXTPOINT = 3                                  // ��չ��
};

// ���ᣬ�ⶳ�Ʒѱ�־
enum _Freeze_Fee_Flag
{
    _FREEZE   = 1,                                          // ����
    _UNFREEZE = 2                                           // ����
};

// ���ᣬ�ⶳ�Ʒ�����
enum _Freeze_Fee_Type
{
    _FREEZE_SECOND   = 1,                                   // �Ƶ�
    _FREEZE_COIN     = 2,                                   // ���
    _FREEZE_EXTPOINT = 3                                    // ��չ��
};

enum PasspodVersion
{
    PASSPODVERSION_UNBIND = 0, 
    PASSPODVERSION_ZP3    = 1 //����Passpod3.0
};

enum PasspodMode
{
    PASSPODMODE_UNBIND   = 0,
    PASSPODMODE_ZPTOKEN  = 1 //��������
};

#pragma pack()

#endif 
