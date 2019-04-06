// -------------------------------------------------------------------------
//    �ļ���        ��    AccountLoginDef.h
//    ������        ��    ����
//    ����ʱ��    ��    2003-5-2 22:04:24
//    ��������    ��
//
// -------------------------------------------------------------------------
#ifndef __ACCOUNTLOGINDEF_H__
#define __ACCOUNTLOGINDEF_H__

#ifdef WIN32
#include <WTypes.h>
#endif

#include "../ProtocolBasic.h"

#define KSG_LOGIN3

// ��Ҫ�������û��Ķ˿ڴ��ݸ�PaySys
#define KSG_USER_PORT
//#undef KSG_USER_PORT

#pragma    pack(push, 1)


#define LOGIN_USER_ACCOUNT_MIN_LEN        4
#define LOGIN_USER_ACCOUNT_MAX_LEN       32
#define LOGIN_USER_PASSWORD_MIN_LEN       6
#define LOGIN_USER_PASSWORD_MAX_LEN      64
#define LOGIN_USER_BIRTHDAY_MAX_LEN       9

//login action return value
#define ACTION_SUCCESS                  0x1
#define ACTION_FAILED                   0x2
#define E_ACCOUNT_OR_PASSWORD           0x3
#define E_ACCOUNT_EXIST                 0x4
#define E_ACCOUNT_NODEPOSIT             0x5 //�㿨���Ϊ�㡢���޵㿨
#define E_ACCOUNT_ACCESSDENIED          0x6
#define E_ADDRESS_OR_PORT               0x7
#define E_ACCOUNT_FREEZE                0x8
#define E_ACCOUNT_CHANGE_EXT_POINT      0x9
#define E_ACCOUNT_USE_SILVER            0xA
///0x0B �����ֵ�ڿͻ��˱�����Ϊ��������
#define E_ACCOUNT_SMS_LOCK              0xC //�˺ű��û���������
#define E_ACCOUNT_NOT_ACTIVE            0xD //�˺�δ����
#define E_ACCOUNT_KICKOUT_OLDACC        0xE
#define E_ACCOUNT_IN_GATEWAY            0xF
#define E_SYSTEM_BUSY                   0x10 //ϵͳæ
#define E_BLACK_LIST                    21  // �ʺű�Paysys������������������!

#define E_CONNECT_PAYSYS_ACCOUNT        50 // Gateway��Paysysʱ�û�����
#define E_CONNECT_PAYSYS_PASSWORD       51 // Gateway��Paysysʱ�����
#define E_CONNECT_PAYSYS_IP             52 // Gateway��PaysysʱIP��
#define E_CONNECT_PAYSYS_MAC            53 // Gateway��PaysysʱMAC��

#define E_ACTIVE_CODE_NOT_EXIST         68 // �����벻����
#define E_ACTIVE_CODE_ALREADY_USED      69 // �������Ѿ�ʹ�ù���
// �������������������ڼ�����Ĺ���ʵ��:
#define E_CDKEY                         70  // ���뼤�������
#define E_ACTIVE                        71  // �˺�δ������,��Ҫ������

// �����ĸ������������������ƹ�CDKey��ʹ�õ�!
// ע: ����������������,����1��ʾ�ɹ�,2��ʾ���ݿ����,3��ʾ�����cdkey������(����˵�����)
#define E_ISCDKEY                       74  // ����Ѿ�ʹ�ù�cdkey��,һ���ʺ�ֻ��ʹ��һ���ƹ�Աcdkey
#define E_NEWTIMEOUT                    75  // ���ʺ�ʹ���ѳ�10Сʱ,������ʹ���ƹ�Աcdkey
#define E_NEWACTIVED                    76  // ���ʺŲ���ʹ���ƹ�Աcdkey,�����Ǹ�����ʺ�����"�ƹ�Ա���ֿ��ʺ�"
#define E_NOAPPLY                       77  // �����cdkey�Ѿ�������,�����Ǹ�cdkey��û����Ч(δ���ƹ�Ա��ȡ)

// ��һ����ν�����ֿ��˺�,������<�������>���͵��������ֿ��˺�,��ʹ��ʱҪ�ȼ���
// �����֤ʱ���ֻ�û�м���,�ͷ������������,�����Ҫ��ָ������ҳ��ȥ����
#define E_ACCOUNT_CARD_UNACTIVE         80

// ���´������������շѺ���ҵ�һ�ν�����Ϸ��ʾ����վ�޸�����
#define E_CHANGE_PASSWORD               86

// ���´�����������Paysys 2.0�������¼ӵĳ���ֵ
#define E_FEE_TYPE_ID_NOT_EXIST                     1000
#define E_ACCOUNT_CHARGE_NOT_FOUND_OR_OVERDUE       1001
#define E_CHARGE_PARAM_ERROR                        1002
#define E_CHARGE_SILVER_DENOMINATOR_ERROR           1003
#define E_CHARGE_SILVER_SILVER_TYPE_ERROR           1004
#define E_GATEWAY_STATE_NOT_FOUND                   1005
#define E_GATEWAY_STATE_NOT_SET_WORK_CONNECTION_ID  1006
#define E_GATEWAY_STATE_NEW_CONNECTION_ID           1007
#define E_GATEWAY_STATE_PARAM_ERROR                 1008
#define E_PARAM_ERROR                               1009
#define E_ZONE_ID_NOT_EXIST                         1010
#define E_ZONE_NAME_NOT_EXIST                       1011
#define E_GATEWAY_NAME_NOT_EXIST                    1012
#define E_NOT_A_FREE_GATEWAY                        1013
#define E_ZONE_STATE_NOT_MATCH                      1014
#define E_ZONE_ACCOUNT_ID_NOT_EXIST                 1015 //�ڷ������в�����
#define E_ZONE_NOT_CHARGED                          1016 //�����������ķ���û���շ�

// Added by zhaofine, for IB only
#define E_IB_NO_ENOUGH_COIN                         1100 // �ڹ�����Ʒʱ��������㡣
#define E_IB_ITEM_NOT_EXIST                         1101 // ��Ʒ������
#define E_IB_ITEM_HAS_BEEN_USED                     1102 // ��Ʒ���ڣ������ѱ�����
#define E_IB_ITEM_EXPIRED                           1103 // ��Ʒ���ڣ�������ʧЧ
#define S_IB_ITEM_NOT_IN_SAME_GATEWAY               1200 // ��Ʒ���ڣ����������ĵ����ز�һ�¡�

#define E_LIMIT_ACCOUNT                             1400 // ���ʺ�Ϊ�����Զ��󣬲������¼
#define E_PASSPOD_VERIFY_TIME                       1701 // ��δ������ʱ�����֤

//���´����������ʢ�� by ����Ԫ
#define E_ID_CARD_NOT_EXIST                         1900

#define E_LIMIT_MUTI_ACCOUNT_ONLINE                 1401 // ������ͬһ���������֤�¶���˺�����
#define E_REAL_NAME_PARAM_ERROR                     4024 // ���ʵ����Ϣ����

//���´������Ǹ������õ�
#define E_OVER_MAX_BIND_TIMES                       3001 //����������
#define E_OVER_MAX_TRANSFER_TIMES                   3002 //�������������
#define E_HAS_APPLIED_TRIAL_ACCOUNT                 3003 //�Ѿ����ù���

//���´�����������ܱ�
#define S_PASSPOD_SUCCESS                           5000 //��֤�ɹ�
#define E_PASSPOD_SYSTEM                            5001 //PASSPODϵͳ����
#define E_PASSPOD_TOKEN_USED                        5002 //������ʹ��
#define E_PASSPOD_TOKEN_FAILED                      5003 //������֤ʧ��
#define E_PASSPOD_TOKEN_EXPIRED                     5004 //���ƹ���
#define E_PASSPOD_TOKEN_NOTFOUND                    5005 //���ư�δ�ҵ�
#define E_PASSPOD_TOKEN_DISABLE                     5006 //�����Ѿ����ã���ʧ��
#define E_PASSPOD_MATRIX_FAILED                     5007 //������֤ʧ��
#define E_PASSPOD_MATRIX_CARDINVALID                5008 //������Ч
#define E_PASSPOD_MATRIX_NOTFOUND                   5009 //����δ�ҵ�

#define ACCOUNT_CURRENT_VERSION                     10

typedef enum
{
    AccountUser = 1,                  // �û�������Ϸ���õ�Э�飬һ��ʹ��KAccountUser�ṹ��������    AccountUserReturn
    AccountUserLoginInfo,             // ��ͨ�û���½ʹ�õ�Э�飬һ��ʹ��KAccountUserLoginInfo�ṹ��������    AccountUserReturnEx
    ServerAccountUserLoginInfo,       // ������û��ĵ�½ʹ�õ�Э�飬һ�������أ�Relay���û���½ʹ��    KServerAccountUserLoginInfo�ṹ����Ҫ��֤IP��������MAC��ַ��ʹ��AccountUserReturnЭ�鷵�أ��ṹʹ��    KAccountUserReturnVerify
    AccountUserReturn,                // �û���½���أ�һ��ʹ��KAccountUserReturn�ṹ
    AccountUserTimeInfo,              // RelayServerʹ��
    ServerOptionInfo,                 // RelayServerʹ��
    ServerInfo,                       // RelayServerʹ��
    AccountUserVerify,                // �û��޸�����ʹ�ã�һ��ʹ��KAccountUserLoginInfo�ṹ
    AccountUserReturnEx,              // �����û��ĵ�½������������ӵ㣬һ��ʹ��KAccountUserReturnExt�ṹ
    AccountUserLogout,                // ����˳���ϷЭ�飬һ��ʹ��KAccountUserLogout�ṹ������ʹ��    AccountUserReturn
    AccountChangeExtPoint,            // ����޸ĸ��ӵ㣬����ʹ����Ʊ��תΪʱ�䣩��һ��ʹ��    KAccountUserChangeExtPoint�ṹ��ʹ��AccountUserReturn,���Ƿ��ؽṹʹ��KAccountUserReturnExt2
    AccountUserGetIp,                 // RelayServerʹ��
    AccountSpreaderCDKEY = 22,        // ���������ƹ�CDKEY��PaySys
    AccountSpreaderCDKEYRet = 23,     // ���������ƹ�CDKEYʹ�ý��


    AccountIB_ItemBuy = 30,           // ���ݹ��������PaySys
    AccountIB_ItemBuyRet,             // ���ش��ݹ�����
    AccountIB_ItemUse,                // ������Ʒʹ�������PaySys
    AccountIB_ItemUseRet,             // ������Ʒʹ�ý��
    AccountIB_UserLoginInfo = 34,     // ר����IBģʽ�ĵ�����Э�飬����Э�齫����һ���ֶ�����ʾ�����
    
    AccountUserSetChargeFlag = 35,    //�޸��û�Charge_Flag
	AccountUserSetChargeFlagRet,

    AccountUserTransfer    = 37,      //ת��
    AccountUserTransferRet = 38,        

    ChangeAccountState  = 40,         // �����ʺ�״̬��KChangeAccountState
    ChangeAccountStateRetrun,         // �����ʺ�״̬���أ�KChangeAccountStateRet

    AccountUserExchange     = 42,     // ��Ҷһ�
    AccountUserExchargeRet  = 43,  

    AccountUserQueryTransfer    = 44, // ת�ʲ�ѯ
    AccountUserQueryTransferRet = 45,

    AccountUserFreezeFee    = 46,     // ��Ҷ������
    AccountUserFreezeFeeRet = 47,

    AccountIB_MultiItemBuy = 50,      // ���ݹ��������PaySys
    AccountIB_MultiItemBuyRet = 51,   // ���ش��ݹ�����
    AccountIB_MultiItemUse = 52,      // ������Ʒʹ�������PaySys
    AccountIB_MultiItemUseRet = 53,   // ������Ʒʹ�ý��
    
    AccountUserInfo         = 54,     // ��ȡ�ʺ���Ϣ
    AccountUserInfoRet      = 55,     // ��ȡ�ʺ���Ϣ����
    
    AccountUserPasspodVerify    = 56, //�ܱ���֤
    AccountUserPasspodVerifyRet = 57, //�ܱ���֤����

    
    AccountIB_ItemBuy_SD = 60,        // ���ݹ��������PaySys
    AccountIB_ItemBuyRet_SD = 61,     // ������Ʒ�ķ��ؽ��
    AccountIB_MultiItemBuy_SD = 62,   // ���ݹ��������PaySys
    AccountIB_MultiItemBuyRet_SD = 63,// ������Ʒ�ķ��ؽ��

    GetZoneChargeFlag = 65,           // ��ȡ���Ʒѱ�־
    GetZoneChargeFlagRet = 66,        // ��ȡ���Ʒѱ�־����
    
    AccountUserExchangeEx = 67,       // ��Ҽ���
    AccountUserExchangeExRet = 68,     // ��Ҽ��۷��ؽ��

    AccountUserPasspodVerifyEx = 69,  // ����ܱ���֤Э����չ
    AccountUserPasspodVerifyRetEx = 70,

    AccountUserInfoEx    = 71,
    AccountUserInfoRetEx = 72,        // ��ȡ�˺���Ϣ���أ���չ
	
} ACCOUNTHEADTYPE;

// ͨ��Э��: ��Ϸ���絽Paysys������������
enum G2P_COMMON_REQUEST_SubType
{
	enumTypeAccountActivePresentCode = 48,			//��Ʒ��
};
// ͨ��Э��: ��Ϸ���絽Paysys��������Э��
enum G2P_COMMON_REQUEST_SubProtocol
{
	enumProtocolAccountActivePresentCode = 50,		//��Ʒ��
};

// ͨ��Э��: Paysys����Ϸ����Ļ�Ӧ������
enum P2G_COMMON_REPLY_SubType
{
	enumTypeAccountActivePresentCodeRet = 49,		//��Ʒ��
};
// ͨ��Э��: Paysys����Ϸ����Ļ�Ӧ��Э��
enum P2G_COMMON_REPLY_SubProtocol
{
	enumProtocolAccountActivePresentCodeRet = 50,	//��Ʒ��
};

struct KAccountHead
{
    WORD  Size;        // size of the struct
    WORD  Version;     // ACCOUNT_CURRENT_VERSION
    WORD  Type;
    DWORD Operate;     // gateway used
};

struct KAccountUser : public KAccountHead
{
    char Account[LOGIN_USER_ACCOUNT_MAX_LEN];    //account
};

struct KAccountUserReturn : public KAccountUser
{
    int nReturn;
};

struct KAccountUserPassword : public KAccountUser
{
    char Password[LOGIN_USER_PASSWORD_MAX_LEN];    //password
};

struct KAccountUserLogout : public KAccountUser
{
    WORD nExtPoint; //��Ҫ�۳��ĸ��͵�
};

typedef enum _PLAYER_SOURCE
{
    PLAYER_SOURCE_INVALID = 0,
    PLAYER_SOURCE_KS, // Kingsoft Player
    PLAYER_SOURCE_SD,  // SNDA Player
	PLAYER_SOURCE_YY,  // yy Player
} PLAYER_SOURCE;

struct KAccountUserLoginInfo : public KAccountUserPassword  // Bishop ==> Paysys, ��������֤!
{
    DWORD UserIP;
    DWORD UserPort;
    BYTE  byMachineID[16];      // ��ͬ��MachineID�����ӱ���Ϊ��ͬһ̨���Զ࿪
    BYTE  nLogout;              // 1��ʾloginʱҪ��logout��0��ʾ������¼
    char  szActivateCode[LOGIN_USER_ACCOUNT_MAX_LEN];
    
    BYTE  byPasspodVersion;     // �ܱ��汾
    BYTE  byPasspodMode;        // �ܱ���֤��ʽ
    char  szTokenPassword[10];  // ��������
    char  szMatrixPosition[9];  // ��Ҫ�û�����ľ��������λ��
    char  szMatrixPassword[9];  // ��Ӧ����λ�õ�����

    BYTE  byReserve[33];
};

struct  KAccountUserLoginInfoSD : public KAccountUserPassword
{
    DWORD UserIP;
    DWORD UserPort;
    BYTE  byMachineID[16];      // ��ͬ��MachineID�����ӱ���Ϊ��ͬһ̨���Զ࿪
    BYTE  nLogout;              // 1��ʾloginʱҪ��logout��0��ʾ������¼
    char  szActivateCode[LOGIN_USER_ACCOUNT_MAX_LEN];

    BYTE  byPasspodVersion;     // �ܱ��汾
    BYTE  byPasspodMode;        // �ܱ���֤��ʽ
    char  szTokenPassword[10];  // ��������
    char  szMatrixPosition[9];  // ��Ҫ�û�����ľ��������λ��
    char  szMatrixPassword[9];  // ��Ӧ����λ�õ�����

    char  szIDCard[KG_STRING_SIZE_ID_CARD]; // ���֤

    BYTE  byReserve[14];
};

struct  KAccountUserLoginInfoSDExt : public KAccountUserPassword
{
	DWORD UserIP;
	DWORD UserPort;
	BYTE  byMachineID[16];      // ��ͬ��MachineID�����ӱ���Ϊ��ͬһ̨���Զ࿪
	BYTE  nLogout;              // 1��ʾloginʱҪ��logout��0��ʾ������¼
	char  szActivateCode[LOGIN_USER_ACCOUNT_MAX_LEN];

	BYTE  byPasspodVersion;     // �ܱ��汾
	BYTE  byPasspodMode;        // �ܱ���֤��ʽ
	char  szTokenPassword[10];  // ��������
	char  szMatrixPosition[9];  // ��Ҫ�û�����ľ��������λ��
	char  szMatrixPassword[9];  // ��Ӧ����λ�õ�����

	char  szIDCard[KG_STRING_SIZE_ID_CARD]; // ���֤

	BYTE  byReserve[128];
};

struct KServerAccountUserLoginInfo : public KAccountUserPassword // Bishop ==> Paysys, Bishop�����֤�����ý���Paysys
{
    DWORD Address;
    BYTE  MacAddress[6];
    DWORD nLastTime;
    DWORD nPlayerCount;
};

struct KServerAccountUserLoginInfo2 : KAccountHead      // Bishop ==> Paysys, Bishop�����֤�����ñ���Paysys
{
    char          szAccountName[LOGIN_USER_ACCOUNT_MAX_LEN];
    char          szPassWord[LOGIN_USER_PASSWORD_MAX_LEN];
    int           nReserved;
    unsigned      dwUserIP;
    unsigned char byMacAddress[6];
    unsigned      dwLastLiveTime;
};

struct KAccountUserFullInfo : public KAccountUserPassword
{
    DWORD UserIP;
    char  Password2[LOGIN_USER_PASSWORD_MAX_LEN]; //secpassword
};

struct KAccountUserIp : public KAccountUser
{
    DWORD UserIP;
};

struct KAccountUserReturnVerify : public KAccountUserReturn
{
    long dwVerifyTime;
};

typedef struct _USER_RET_PLAY_LIMIT_PLAY_TIME
{
    int          nLimit_Player_Flag;
    int          nLimitOnlineSecond;
    int          nLimitOfflineSecond;
} USER_RET_PLAY_LIMIT_PLAY_TIME;

#define ACCOUNT_MAX_EXT_POINT_COUNT 8
struct KAccountUserReturnExt : public KAccountUserReturn    // Paysys ==> Bishop, ��������֤���!
{
    union
    {
        struct
        {
            WORD nExtPoint;         //���õĸ��͵�
            WORD nExtPoint1;        //���õĸ��͵�1
            WORD nExtPoint2;        //���õĸ��͵�2
            WORD nExtPoint3;        //���õĸ��͵�3
            WORD nExtPoint4;        //���õĸ��͵�4
            WORD nExtPoint5;        //���õĸ��͵�5
            WORD nExtPoint6;        //���õĸ��͵�6
            WORD nExtPoint7;        //���õĸ��͵�7
        };
        WORD nExtPointArray[ACCOUNT_MAX_EXT_POINT_COUNT];
    };

    // ���ʣ��ʱ���Ϊ��ʱ�͵��������ִ�����
    DWORD dwEndOfDayTime;    // ��Ұ�ʱ(����,���µ�)�Ľ�ֹʱ��, time_t, ��λ��
    DWORD nLeftTimeOfPoint;  // ʣ�����
    DWORD dwLastLoginTime;   // ����ϴε�½��ʱ��
    DWORD dwLastLoginIP;     // ����ϴε�½��IP

    union
    {
        struct
        {
            DWORD dwLimitPlayTimeFlag;   // Reserve[0]..Reserve[3]
            DWORD dwLimitOnlineSecond;   // Reserve[4]..Reserve[7]
            DWORD dwLimitOfflineSecond;  // Reserve[8]..Reserve[11]
            int   nChargeFlag;           // byReserve[12] .. Reserve[15]
            unsigned int  uAccountState; // byReserve[16] .. Reserve[19] 
            char  szMobileNumber[20];    // byReserve[20] .. byReserve[39]
            DWORD dwGatewayID;           // byReserve[40] .. byReserve[43]
            BYTE  byPasspodVersion;      // byReserve[44] .. byReserve[44]�ܱ��汾
            BYTE  byPasspodMode;         // byReserve[45] .. byReserve[45]�ܱ���֤��ʽ
            char  szMatrixPosition[9];   // byReserve[46] .. byReserve[54]��Ҫ�û�����ľ��������λ��
        };
        BYTE  byReserve[64];
    };
};

struct KAccountUserReturnExt2 : public KAccountUserReturn // Paysys ==> Bishop, ���ӵ�����Ľ��!
{
    unsigned uFlag;
    int      nPlayerDataIndex;  // ����������Э�鵽��GameServerʱ����ʾȡ����ҵ�����
};

#define CHANGE_EXT_POINT_SILVER         0x1
struct KAccountUserChangeExtPoint : public KAccountUser // Bishop ==> Paysys, ����������ӵ�!
{
    union
    {
        unsigned uExtPointIndex;    // ��Ҫ�ı�ĸ��ӵ������
        unsigned uSilverType;       // ��Ʊ�����ͣ���16λ��0����ʾ����Ʊ��1����ʾС��Ʊ��
                                    //             ��16λ��0��תΪ��������תΪ�����ܣ��£�
    };
    int          nChangeValue;      // ���ӵ㱻�޸ĵ�ֵ�������ɸ���������Ʊ����Ŀ
    int          nPlayerDataIndex;  // ����������Э�鵽��GameServerʱ����ʾȡ����ҵ�����
    unsigned     uFlag;             // �����0��ʾ���ӵ�ı仯�������CHANGE_EXT_POINT_SILVER : ��ʾ��Ʊ�Ĵ���
};

struct KAccountUserTimeInfo : public KAccountUserReturn
{
    DWORD nTime;
};

typedef enum
{
    server_OnlinePlayerCount = 0x0001,
    server_RegisterCount = 0x0002,
    server_Login = 0x0004,
    server_Logout = 0x0008,
    server_PlayerWhere = 0x0010,
    server_LoginAlready = 0x0020,
    server_PlayerWhereID = 0x0040,
    server_GWRelayID = 0x0080,
} SERVERTYPE;

struct KServerInfo : public KAccountUser
{
    short nServerType;
    DWORD nValue;
};

/**
 * @description δ��ֵ�������˺ŵ���20�������趨��ʱ����ʹ��ѵ�10Сʱδʹ���꣬
                Ҳ��������Ϸ�������߳���ͬʱ��paysys����Э�齫��ʹ��ʱ������Ϊ0
 * @protocol    c2s_tryout_timeout_req Bishop=>Paysys
 * @author        wangbin
 * @datetime    2004-12-28 14:46
 */
struct TRYOUT_TIMEOUT_ASK : KAccountHead
{
    UINT    nIdentity;                                // GameServer��ʶ
    BYTE    nReason;                                  // ԭ�򣨱�����
    int     nPlayerIndex;                             // �����������
    char    szAccount[LOGIN_USER_ACCOUNT_MAX_LEN];    // �˺���
};

/**
 * @description δ��ֵ�������˺ŵ���20�������趨��ʱ����ʹ��ѵ�10Сʱδʹ���꣬
                Ҳ��������Ϸ�������߳���ͬʱ��paysys����Э�齫��ʹ��ʱ������Ϊ0
 * @protocol    s2c_tryout_timeout_res Paysys=>Bishop
 * @author        wangbin
 * @datetime    2004-12-28 14:47
 */
struct TRYOUT_TIMEOUT_ANS : KAccountHead
{
    UINT    nIdentity;                                // GameServer��ʶ
    BYTE    nResult;                                  // ��������1Ϊ�ɹ���0Ϊʧ��
    int     nPlayerIndex;                             // �����������
    char    szAccount[LOGIN_USER_ACCOUNT_MAX_LEN];    // �˺���
};



#define KG_SPREAD_NEW_PLAYER_CDKEY_FLAG    2
#define KG_VIRTUAL_GOODS_REPORT_FLAG       15

// �ӱ����µ�Paysys���õ��Ľӿڣ��������������ƹ�CDKey
struct  TAccountCDKEY : public KAccountHead
{
    char  szAccountName[32];
    short nFlag;         // KG_SPREAD_NEW_PLAYER_CDKEY_FLAG�������ƹ�����к���֤

    int   nChangeValue;
    char  ChangeStr[64]; // ��flag=KG_SPREAD_NEW_PLAYER_CDKEY_FLAGʱ�����ַ�����ʾ�����ƹ�����к�
    int   nResevrval;
    char  ResevrStr[64];
};

// ��Paysys����������Ʒ��Ԫ������ҡ���Ʊ�ȣ��Ľṹ
#define KG_MAX_GOODS_TYPE_COUNT 8
struct tagVirtualGoodsStatistic : KAccountHead
{
	char               szAccountName[32];  // fill:NULL\0
	short              nFlag;              // fill:15

    // report how many kinds of goods, the max value is KG_MAX_GOODS_TYPE_COUNT
    // such as 4, then the avaible values in llMoneyCount is the head 4 int64
    int                nGoodsTypeCount;

#ifdef WIN32
    unsigned __int64   ullGoodsAmount[KG_MAX_GOODS_TYPE_COUNT];
#else
	unsigned long long ullGoodsAmount[KG_MAX_GOODS_TYPE_COUNT];
#endif

    int                nResevrval;
    char               ResevrStr[64];
};

struct  TAccountCDKEYRet : public KAccountHead
{
    char  szAccountName[32];
    short nFlag;     // KG_SPREAD_NEW_PLAYER_CDKEY_FLAG�������ƹ�����к���֤

    int   nResult;   // ���󷵻ؽ��
    char  ResevrStr[64];
    int   nResevrval;
};

//������ҼƷ�״̬
struct KAccountSetChargeFlag : public KAccountUser
{
    DWORD dwLastLoginIP;
    int   nChargeFlag;                           //0:���,1:�շ�
    BYTE byReserve[128];
};
struct KAccountSetChargeFlagRet : public KAccountUser
{
    int   nChargeFlag;                           //0:���,1:�շ�
    WORD  nExtPoint; 
    WORD  nExtPoint1;
    WORD  nExtPoint2;
    WORD  nExtPoint3;
    WORD  nExtPoint4;
    WORD  nExtPoint5;
    WORD  nExtPoint6;
    WORD  nExtPoint7;
    DWORD dwEndOfDayTime;    // ��Ұ�ʱ(����,���µ�)�Ľ�ֹʱ��, time_t, ��λ��
    DWORD nLeftTimeOfPoint;  // ʣ�����
    union
    {
        struct  
        {
            DWORD nLeftTimeOfDay;    // byReserve[0] .. byReserve[3] ��Ҽ����ʣ������
            DWORD dwEndTimeOfFee;    // byReserve[4] .. byReserve[7]
        };
        BYTE byReserve[128];
    };
    int   nResult;
};

//////////////////////////  IB Mode Start  /////////////////////////////////////
enum enumIB_ItemUseType
{
    IB_UseType_Unknown = -1,       // δ֪����
    IB_UseType_Unlimit = 0,        // ����ʹ�ã�û�б�ֵ�ڣ�
    IB_UseType_Any_Time,           // �ڹ���ǰ��������ʹ��
    IB_UseType_By_Time,            // �ڹ���ǰ����ʹ��һ��
};

// GUID��Ϊ0���Ҹ�16λΪ0�����GUID��PaySystem��Ʒ��ΪIB��Ʒ
#define IB_IS_IB_ITEM(nItemGUID) \
    (((nItemGUID > 0) && (nItemGUID >> 48) == 0) ? TRUE : FALSE)


#define MAX_ITEM_COUNT_IN_PACKAGE_TO_PAYSYS 16

struct KIBAccountBuyItem : public KAccountUser
{
    int   nPlayerDataIndex;                           // �������Ϸ����ı��
    int   nGoodsIndex;                                // ��Ʒ����Ʒ�ı��

    int   nItemTypeID;                                // ��Ʒ����ID
    int   nItemLevel;                                 // ��Ʒ����(����Ʒ����IDһ��Ψһ��λ��Ʒ)
    int   nUseType;                                   // ʹ������(enumIB_ItemUseType)
    int   nPrice;                                     // ����۸�
    DWORD dwOverdueTime;                              // ������(��ֵ)
};

#define MAX_SD_UNIQUEID_SIZE 33
struct KIBAccountBuyItemSD : public KIBAccountBuyItem
{
    char szSDUniqueId[MAX_SD_UNIQUEID_SIZE];
};

struct KIBAccountBuyMultiItem : public KAccountUser
{
    int   nPlayerDataIndex;                           // �������Ϸ����ı��
    int   nGoodsIndex;                                // ��Ʒ����Ʒ�ı��

    int   nItemTypeID;                                // ��Ʒ����ID
    int   nItemLevel;                                 // ��Ʒ����(����Ʒ����IDһ��Ψһ��λ��Ʒ)
    int   nUseType;                                   // ʹ������(enumIB_ItemUseType)
    int   nPrice;                                     // ����۸�
    DWORD dwOverdueTime;                              // ������(��ֵ)

    int   nItemCount;                                 // �������Ʒ����
    BYTE  byUseItemNow;                               // �����ͬʱʹ�õ���Ʒ
};

struct KIBAccountBuyMultiItemSD : public KIBAccountBuyMultiItem
{
    char szSDUniqueId[MAX_SD_UNIQUEID_SIZE];
};

struct KIBAccountUseItem : public KAccountUser
{
    int       nPlayerDataIndex;                           // �������Ϸ����ı��

    int       nItemTypeID;                                // ��Ʒ����ID
    int       nItemLevel;                                 // ��Ʒ����(����Ʒ����IDһ��Ψһ��λ��Ʒ)
    long long llItemGUID;                                 // ��Ʒ�����ݿ��Ψһ���
};

struct KIBAccountUseMultiItem : public KAccountUser
{
    int       nPlayerDataIndex;                           // �������Ϸ����ı��

    int       nItemTypeID;                                // ��Ʒ����ID
    int       nItemLevel;                                 // ��Ʒ����(����Ʒ����IDһ��Ψһ��λ��Ʒ)
    int       nItemCount;                                 // �������Ʒ����
    long long llItemGUID[MAX_ITEM_COUNT_IN_PACKAGE_TO_PAYSYS];  // ��Ʒ�����ݿ��Ψһ���
};

struct KIBAccountBuyItemRet : public KAccountUser
{
    int       nPlayerDataIndex;                            // �������Ϸ����ı��
    int       nGoodsIndex;                                 // ��Ʒ����Ʒ�ı��

    int       nItemTypeID;                                 // ��Ʒ����ID
    int       nItemLevel;                                  // ��Ʒ����(����Ʒ����IDһ��Ψһ��λ��Ʒ)
    int       nPrice;                                      // ����۸�
    long long llItemGUID;                                  // ��Ʒ�����ݿ��Ψһ���
    
    int       nResult;                                     // ���������
};

struct KIBAccountBuyItemRetSD : public KIBAccountBuyItemRet
{
    char      szSDUniqueId[MAX_SD_UNIQUEID_SIZE];
};

struct KIBAccountBuyMultiItemRet : public KAccountUser
{
    int       nPlayerDataIndex;                            // �������Ϸ����ı��
    int       nGoodsIndex;                                 // ��Ʒ����Ʒ�ı��

    int       nItemTypeID;                                 // ��Ʒ����ID
    int       nItemLevel;                                  // ��Ʒ����(����Ʒ����IDһ��Ψһ��λ��Ʒ)
    int       nPrice;                                      // ����۸�
    int       nItemCount;                                  // �������Ʒ����
    long long llItemGUID[MAX_ITEM_COUNT_IN_PACKAGE_TO_PAYSYS];   // ��Ʒ�����ݿ��Ψһ���

    int       nResult;                                     // ���������
};

struct KIBAccountBuyMultiItemRetSD : public KIBAccountBuyMultiItemRet
{
    char      szSDUniqueId[MAX_SD_UNIQUEID_SIZE];
};

struct KIBAccountUseItemRet : public KAccountUser
{
    int       nPlayerDataIndex;                             // �������Ϸ����ı��

    int       nItemTypeID;                                  // ��Ʒ����ID
    int       nItemLevel;                                   // ��Ʒ����(����Ʒ����IDһ��Ψһ��λ��Ʒ)
    long long llItemGUID;                                   // ��Ʒ�����ݿ��Ψһ���

    int       nResult;                                      // ���������
};

struct KIBAccountUseMultiItemRet : public KAccountUser
{
    int       nPlayerDataIndex;                             // �������Ϸ����ı��

    int       nItemTypeID;                                  // ��Ʒ����ID
    int       nItemLevel;                                   // ��Ʒ����(����Ʒ����IDһ��Ψһ��λ��Ʒ)
    int       nItemCount;                                   // �������Ʒ����
    long long llItemGUID[MAX_ITEM_COUNT_IN_PACKAGE_TO_PAYSYS];   // ��Ʒ�����ݿ��Ψһ���

    int       nResult;                                      // ���������
};

struct KAccountUserReturnExtIB : public KAccountUserReturn    // Paysys ==> Bishop, ר����IBģʽ����չЭ�顣
{
    union
    {
        struct
        {
            DWORD nExtPoint0;        //���õĸ��͵�0
            DWORD nExtPoint1;        //���õĸ��͵�1
            DWORD nExtPoint2;        //���õĸ��͵�2
            DWORD nExtPoint3;        //���õĸ��͵�3
            DWORD nExtPoint4;        //���õĸ��͵�4
            DWORD nExtPoint5;        //���õĸ��͵�5
            DWORD nExtPoint6;        //���õĸ��͵�6
            DWORD nExtPoint7;        //���õĸ��͵�7
        };
        DWORD nExtPointArray[ACCOUNT_MAX_EXT_POINT_COUNT];
    };

    // ���ʣ��ʱ���Ϊ��ʱ�͵��������ִ�����
    DWORD dwEndOfDayTime;            // ��Ұ�ʱ(����,���µ�)�Ľ�ֹʱ��, time_t, ��λ��
    DWORD dwLeftTimeOfPoint;         // ʣ�����
    DWORD dwLastLoginTime;           // ����ϴε�½��ʱ��
    DWORD dwLastLoginIP;             // ����ϴε�½��IP
    DWORD dwLeftMoney;               // ������ҵĽ����ͨ���˷�ʽ����������ͳ�Ʒ���IBģʽ���ݡ�
    DWORD dwOnlineSecond;            // ����ۼ�����ʱ��

    union
    {
        struct
        {
            DWORD dwLimitPlayTimeFlag;   // byReserve[0]  .. Reserve[3]
            DWORD dwLimitOnlineSecond;   // byReserve[4]  .. Reserve[7] 
            DWORD dwLimitOfflineSecond;  // byReserve[8]  .. Reserve[11]
            int   nChargeFlag;           // byReserve[12] .. Reserve[15]
            unsigned int  uAccountState; // byReserve[16] .. Reserve[19] 
            char  szPhoneNumber[20];     // byReserve[20] .. byReserve[39]
            DWORD dwGatewayID;           // byReserve[40] .. byReserve[43]
            BYTE  byPasspodVersion;      // byReserve[44] .. byReserve[44]�ܱ��汾
            BYTE  byPasspodMode;         // byReserve[45] .. byReserve[45]�ܱ���֤��ʽ
            char  szMatrixPosition[9];   // byReserve[46] .. byReserve[54]��Ҫ�û�����ľ��������λ��
        };
        BYTE  byReserve[64];
    };
};
//////////////////////////  IB Mode End  ///////////////////////////////////////

// �ʺ�״̬�ı�֪ͨЭ��
struct KChangeAccountState : public KAccountUser
{
    int nStateType;
    int nStateValue;
};
struct KChangeAccountStateRet : public KAccountUser
{
    int nResult;
};

//���ᣬ�ⶳ�Ʒѱ�־
enum Freeze_Fee_Flag
{
    FREEZE   = 1,      //����
    UNFREEZE = 2       //����
};

//���ᣬ�ⶳ�Ʒ�����
enum Freeze_Fee_Type
{
    FREEZE_SECOND   = 1, //�Ƶ�
    FREEZE_COIN     = 2, //���
    FREEZE_EXTPOINT = 3  //��չ��
};

//���ᣬ�ⶳЭ��
struct KAccountFreezeFee : public KAccountUser
{
    long long llFreezeGUID;
    DWORD  dwFreezeFlag;
    DWORD  dwFreezeType;
    DWORD  dwExtPoint;   //������չ�㶳�ᣬ���ֶ�Ϊ��չ������0��7��
    DWORD  dwFreezeAmount;
};
struct KAccountFreezeFeeRet : public KAccountUser
{
    long long llFreezeGUID;
    DWORD  dwFreezeFlag;
    DWORD  dwFreezeType;
    DWORD  dwExtPoint;   //������չ�㶳�ᣬ���ֶ�Ϊ��չ������0��7��
    DWORD  dwFreezeAmount;
    
    int    nResult;
};


//ת�ʱ�־
enum Transfer_Flag
{
    TRANSFER_FREEZE_FEE    = 1, //ת�ʶ���Ľ��
    TRANSFER_UNFREEZE_FEE  = 2  //ת��δ����Ľ��
};

//ת������
enum Transfer_Type
{
    TRANSFER_SECOND   = 1, //�Ƶ�
    TRANSFER_COIN     = 2, //���
    TRANSFER_EXTPOINT = 3  //��չ��
};
// ���ת��Э��
struct KAccountTransfer : public KAccountHead
{
    long long llTransferGUID; //���ײ�����Ψһ���,����Ϸ���紫��Paysys.�������ѯ������
    char      AccountDest[LOGIN_USER_ACCOUNT_MAX_LEN]; 
    char      AccountSrc[LOGIN_USER_ACCOUNT_MAX_LEN]; 
    DWORD     dwTransferFlag;
    DWORD     dwTransferType;
    DWORD     dwExtPoint;       //������չ�㶳�ᣬ���ֶ�Ϊ��չ������0��7��
    DWORD     dwTransferAmount;
};
struct KAccountTransferRet : public KAccountHead
{
    long long llTransferGUID; //���ײ�����Ψһ���,����Ϸ���紫��Paysys.�������ѯ������
    char      AccountDest[LOGIN_USER_ACCOUNT_MAX_LEN]; 
    char      AccountSrc[LOGIN_USER_ACCOUNT_MAX_LEN]; 
    DWORD     dwTransferFlag;
    DWORD     dwTransferType;
    DWORD     dwExtPoint;       //������չ�㶳�ᣬ���ֶ�Ϊ��չ������0��7��
    DWORD     dwTransferAmount;
   
    int       nResult;
};


//ת�ʲ�ѯЭ��
//����Э�鲻��Account
struct KAccountQueryTransfer : public KAccountHead
{
    long long llTransferGUID; //���ײ�����Ψһ���,����Ϸ���紫��Paysys
};
struct KAccountQueryTransferRet : public KAccountHead
{
    long long llTransferGUID; //���ײ�����Ψһ���,����Ϸ���紫��Paysys
    DWORD     dwTransferTime;
    char      AccountDest[LOGIN_USER_ACCOUNT_MAX_LEN]; 
    char      AccountSrc[LOGIN_USER_ACCOUNT_MAX_LEN]; 
    DWORD     dwTransferFlag;
    DWORD     dwTransferType;
    DWORD     dwExtPoint;        //������չ�㶳�ᣬ���ֶ�Ϊ��չ������0��7��
    DWORD     dwTransferAmount;
    DWORD     dwTransferResult;

    int       nResult;
};

//�һ�����
enum Exchange_Type
{
    COIN_EXCHANGE_SECOND  = 1, //��Ҷһ��Ƶ�
    COIN_EXCHANGE_DATE    = 2  //��Ҷһ���ʱ

};

//��Ҷһ�
struct KAccountExchange : public KAccountUser
{
    DWORD  dwExchangeType; 
    DWORD  dwDestAmount; //�һ��ɵ���Ŀ
    DWORD  dwSrcAmount;  //���һ�����Ŀ
};
struct KAccountExchangeRet : public KAccountUser
{
    DWORD  dwExchangeType; 
    DWORD  dwDestAmount; //�һ��ɵ���Ŀ
    DWORD  dwSrcAmount;  //���һ�����Ŀ
    
    int    nResult;
};

//��ȡ�ʺ���Ϣ    
struct KAccountUserInfo : public KAccountHead
{
    char      Account[LOGIN_USER_ACCOUNT_MAX_LEN]; 
};

struct KAccountUserInfoRet : public KAccountUserReturn
{
    union
    {
        struct
        {
            DWORD nExtPoint0;        //���õĸ��͵�0
            DWORD nExtPoint1;        //���õĸ��͵�1
            DWORD nExtPoint2;        //���õĸ��͵�2
            DWORD nExtPoint3;        //���õĸ��͵�3
            DWORD nExtPoint4;        //���õĸ��͵�4
            DWORD nExtPoint5;        //���õĸ��͵�5
            DWORD nExtPoint6;        //���õĸ��͵�6
            DWORD nExtPoint7;        //���õĸ��͵�7
        };
        DWORD nExtPointArray[ACCOUNT_MAX_EXT_POINT_COUNT];
    };
    DWORD     dwEndDate;
    DWORD     dwLeftSecond;
    DWORD     dwLastLoginTime;
    DWORD     dwLastLoginIP;
    DWORD     dwLeftCoin;            //ʣ����
    DWORD     dwLastLogoutTime;
    DWORD     dwActiveIP;
    DWORD     dwActiveTime;
    DWORD     dwActiveType;
};

struct KAccountUserPasspodVerify : public KAccountUser // Bishop ==> Paysys
{
    BYTE byPasspodVersion;    // �ܱ��汾
    BYTE byPasspodMode;       // �ܱ���֤��ʽ
    char szTokenPassword[10]; // ��������
    char szMatrixPosition[9]; // ��Ҫ�û�����ľ��������λ��
    char szMatrixPassword[9]; // ��Ӧ����λ�õ�����
};

struct KAccountUserPasspodVerifyRet : public KAccountUser // Paysys ==>Bishop
{
    BYTE byPasspodVersion;    // �ܱ��汾
    BYTE byPasspodMode;       // �ܱ���֤��ʽ
    char szMatrixPosition[9]; // ��Ҫ�û�����ľ��������λ��
    
    int nReturn;
};

// ��ȡ���շѱ�־
struct KGetZoneChargeFlag : public KAccountHead
{
    char  szGatewayName[32];    // �������ƣ���gateway01...
    BYTE  byReserve[128];
};

struct KGetZoneChargeFlagRet : public KAccountHead
{
    char  szGatewayName[32];    // ��������
    int   nZoneChargeFlag;      // 0:���,1:�շ�
	union
	{
		struct  
		{
			int  nZoneID;        // byReserve[0] .. byReserve[3]  ��ID
			char szZoneName[32]; // byReserve[4] .. byReserve[35] ������
		};
		BYTE byReserve[128];
	};
    int   nResult;
};


struct KGameworld2Paysys : public KAccountHead
{
    unsigned    uDataSize;
    BYTE        byData[0];
};

struct KAccountActivePresentCode : public tagProtocolHeader
{
	char		szAccount[32];
	char		szPresentCode[32];
	DWORD		dwActiveIP;
};

struct KPaysys2Gameworld : public KAccountHead
{
    unsigned    uDataSize;
    BYTE        byData[0];
};

struct KAccountActivePresentCodeRet : KAccountActivePresentCode
{
	DWORD		dwPresentType;
	int			nResult;
};

enum Exchange_Ex_Type
{
    COIN_EXCHANGE_DATE_EX   = 1,
    COIN_EXCHANGE_SECOND_EX = 2,

};

//����
struct KAccountExchangeEx : public KAccountHead
{
    char   szSrcAccount[LOGIN_USER_ACCOUNT_MAX_LEN];
    char   szDestAccount[LOGIN_USER_ACCOUNT_MAX_LEN];
    DWORD  dwExchangeType; 
    DWORD  dwDestAmount; //�һ��ɵ���Ŀ
    DWORD  dwSrcAmount;  //���һ�����Ŀ
};
struct KAccountExchangeExRet : public KAccountHead
{
    char   szSrcAccount[LOGIN_USER_ACCOUNT_MAX_LEN];
    char   szDestAccount[LOGIN_USER_ACCOUNT_MAX_LEN];
    DWORD  dwExchangeType; 
    DWORD  dwDestAmount; //�һ��ɵ���Ŀ
    DWORD  dwSrcAmount;  //���һ�����Ŀ

    int    nResult;
};

// �����ӵ�¼����Э�飬֧�ּ���
struct KAccountUserLoginInfoExt : public KAccountUserPassword  // Bishop ==> Paysys, ��������֤!
{
    DWORD UserIP;
    DWORD UserPort;
    BYTE  byMachineID[16];      // ��ͬ��MachineID�����ӱ���Ϊ��ͬһ̨���Զ࿪
    BYTE  nLogout;              // 1��ʾloginʱҪ��logout��0��ʾ������¼
    char  szActivateCode[LOGIN_USER_ACCOUNT_MAX_LEN];

    union
    {
        struct
        {
            BYTE  byPasspodVersion;     // �ܱ��汾
            BYTE  byPasspodMode;        // �ܱ���֤��ʽ
            char  szTokenPassword[10];  // ��������
            char  szMatrixPosition[9];  // ��Ҫ�û�����ľ��������λ��
            char  szMatrixPassword[9];  // ��Ӧ����λ�õ�����
        };
        BYTE  byReserve[128];
    };
};
struct KAccountUserLoginReturnExt : public KAccountUserReturn    // Paysys ==> Bishop, ר����IBģʽ����չЭ�顣
{
    union
    {
        struct   
        {
            DWORD nExtPoint0;        //���õĸ��͵�0
            DWORD nExtPoint1;        //���õĸ��͵�1
            DWORD nExtPoint2;        //���õĸ��͵�2
            DWORD nExtPoint3;        //���õĸ��͵�3
            DWORD nExtPoint4;        //���õĸ��͵�4
            DWORD nExtPoint5;        //���õĸ��͵�5
            DWORD nExtPoint6;        //���õĸ��͵�6
            DWORD nExtPoint7;        //���õĸ��͵�7
        };
        DWORD nExtPointArray[ACCOUNT_MAX_EXT_POINT_COUNT];
    };

    // ���ʣ��ʱ���Ϊ��ʱ�͵��������ִ�����
    DWORD dwEndOfDayTime;            // ��Ұ�ʱ(����,���µ�)�Ľ�ֹʱ��, time_t, ��λ��
    DWORD dwLeftTimeOfPoint;         // ʣ�����
    DWORD dwLastLoginTime;           // ����ϴε�½��ʱ��
    DWORD dwLastLoginIP;             // ����ϴε�½��IP
    DWORD dwLeftMoney;               // ������ҵĽ����ͨ���˷�ʽ����������ͳ�Ʒ���IBģʽ���ݡ�
    DWORD dwOnlineSecond;            // ����ۼ�����ʱ��

    union
    {
        struct
        {
            DWORD dwLimitPlayTimeFlag;   // byReserve[0]  .. Reserve[3]
            DWORD dwLimitOnlineSecond;   // byReserve[4]  .. Reserve[7] 
            DWORD dwLimitOfflineSecond;  // byReserve[8]  .. Reserve[11]
            int   nChargeFlag;           // byReserve[12] .. Reserve[15]
            unsigned int  uAccountState; // byReserve[16] .. Reserve[19] 
            char  szPhoneNumber[20];     // byReserve[20] .. byReserve[39]
            DWORD dwGatewayID;           // byReserve[40] .. byReserve[43]
            BYTE  byPasspodVersion;      // byReserve[44] .. byReserve[44]�ܱ��汾
            BYTE  byPasspodMode;         // byReserve[45] .. byReserve[45]�ܱ���֤��ʽ
            char  szMatrixPosition[9];   // byReserve[46] .. byReserve[54]��Ҫ�û�����ľ��������λ��
            DWORD nLeftTimeOfDay;        // byReserve[55] .. byReserve[58]����ģʽ��ʣ�������
            DWORD dwEndTimeOfFee;        // byReserve[59] .. byReserve[62]����շѵĽ�ֹ����
            DWORD dwLoginTime;           // byReserve[63] .. byReserve[66]��ұ��ε�½��ʱ��
            DWORD dwLastLogoutTime;      // byReserve[67] .. byReserve[70]����ϴεǳ���ʱ��
            struct 
            {
                WORD wYear;
                BYTE byMonth;
                BYTE byDay;
            } Birthday;                           // byReserve[71] .. byReserve[74]��ҵĳ������ڣ����ڷ���3���տ�
        };
        BYTE  byReserve[128];
    };
};

// �������û���Ϣ��ѯ�ķ���Э�飬֧�ּ���
struct KAccountUserInfoExt : public KAccountHead
{
    char      Account[LOGIN_USER_ACCOUNT_MAX_LEN]; 
    BYTE      byReserve[128];
};
struct KAccountUserInfoRetExt : public KAccountUserReturn
{
    union
    {
        struct
        {
            DWORD nExtPoint0;        //���õĸ��͵�0
            DWORD nExtPoint1;        //���õĸ��͵�1
            DWORD nExtPoint2;        //���õĸ��͵�2
            DWORD nExtPoint3;        //���õĸ��͵�3
            DWORD nExtPoint4;        //���õĸ��͵�4
            DWORD nExtPoint5;        //���õĸ��͵�5
            DWORD nExtPoint6;        //���õĸ��͵�6
            DWORD nExtPoint7;        //���õĸ��͵�7
        };
        DWORD nExtPointArray[ACCOUNT_MAX_EXT_POINT_COUNT];
    };
    DWORD     dwEndDate;
    DWORD     dwLeftSecond;
    DWORD     dwLastLoginTime;
    DWORD     dwLastLoginIP;
    DWORD     dwLeftCoin;            //ʣ����
    DWORD     dwLastLogoutTime;
    DWORD     dwActiveIP;
    DWORD     dwActiveTime;
    DWORD     dwActiveType;
    union
    {
        struct  
        {
            DWORD     nLeftTimeOfDay; // byReserve[0] .. byReserve[3]����ģʽ�е�ʣ������
            DWORD     dwEndTimeOfFee; // byReserve[4] .. byReserve[7]
        };
        BYTE byReserve[128];
    };
};

// �������ܱ��ķ���Э�飬֧���µ��ܱ���¼����
struct KAccountUserPasspodVerifyExt : public KAccountUser // Bishop ==> Paysys
{
    BYTE byPasspodVersion;    // �ܱ��汾
    BYTE byPasspodMode;       // �ܱ���֤��ʽ
    char szTokenPassword[10]; // ��������
    char szMatrixPosition[9]; // ��Ҫ�û�����ľ��������λ��
    char szMatrixPassword[9]; // ��Ӧ����λ�õ�����
    union
    {	
        struct
        {
            BYTE byLogoutIfFailed;    // ��֤ʧ�����Ƿ�ǳ�
            BYTE byLogoutDeductFlag;  // �ǳ��Ƿ�۷�
        };
        BYTE byReserve[128];
    };
};
struct KAccountUserPasspodVerifyRetExt : public KAccountUser // Paysys ==>Bishop
{
    BYTE byPasspodVersion;    // �ܱ��汾
    BYTE byPasspodMode;       // �ܱ���֤��ʽ
    char szMatrixPosition[9]; // ��Ҫ�û�����ľ��������λ��
    BYTE byReserve[128];
    int nReturn;
};

#pragma    pack(pop)

#endif // __ACCOUNTLOGINDEF_H__
