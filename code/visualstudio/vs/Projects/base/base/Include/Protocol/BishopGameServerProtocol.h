#ifndef _BISHOP_GAME_SERVER_PROTOCOL_H_
#define _BISHOP_GAME_SERVER_PROTOCOL_H_

#include "../ProtocolBasic.h"

enum B2G_PROTOCOL_ID // Bishop ==> Game server
{
    B2G_PROTOCOL_BEGIN = PROTOCOL_BIG_PACKAGE_BEGIN,
    B2G_PLAYER_LOGIN_REQUEST,                   // ������������Ϸ�����ݽ�ɫ���ݵ�Game server,ref : tagGuidableInfo + role data
    B2G_QUERY_SERVER_INFO = PROTOCOL_NORMAL_PACKAGE_BEGIN + 1,  // ��ѯgame server������Ϣ, ref : tagQueryGameSvrInfo
    B2G_QUERY_MAP_INFO,                         // ��ѯ��ͼ������Ϣ, ref : tagQueryMapInfo
    B2G_EXT_POINTS_OPERATION_RESULT,            // ���ӵ�������
    B2G_OFFLINE_LIVE_KICK_ACCOUNT_REQUEST,      // ���߹һ��������ߺ�!
    B2G_PRE_TRANSFER_SERVER_RET,                // ���ӵ�����Ľ������, ref :tagReturnChangeExtPoint
    B2G_ACCOUNT_FREE_TIME_CLEANING_RESULT,      // ��������ʺŵ����ʱ������Ľ��, ref : TRYOUT_TIMEOUT_RES
    B2G_GATEWAY_BROADCAST,                      // ����ϵͳ�㲥, ref : tagGatewayBroadCast
    B2G_PING,                                   // ��ping��, ref: PING_COMMAND
    B2G_USE_SPREADER_CDKEY_RET,                 // �������ƹ�CDKEY����Ľ��, ref: tagUseSpreaderCDKey
    B2G_CONFIRM_ACCOUNT_OFFLINE_REQUEST,        // ȷ������ʺ�û������Ϸ������, ref : CONFIRM_ACCOUNT_OFFLINE_REQUEST
    B2G_IB_PLAYER_BUY_ITEM_RESULT,              // �����IBģʽ�¹�����Ʒ�Ļ�Ӧ����
    B2G_IB_PLAYER_USE_ITEM_RESULT,              // �����IBģʽ��ʹ����Ʒ�Ļ�Ӧ����
    B2G_PLAYER_SET_CHARGE_FLAG_RET,             // �޸��û�Charge_Flag���
    B2G_ACCOUNT_TRANSFER_RESULT,                // �ʺ�֮��ת�˽��
    B2G_ACCOUNT_USER_EXCHANGE_RESULT,           // ��ҽ�Ҷһ�ʱ��Ӧ���
    B2G_PLAYER_QUERY_TRANSFER_RESULT,           // ���ת�ʲ�ѯ�Ļ�Ӧ��
    B2G_PLAYER_FREEZE_FEE_RESULT,               // ��Ҷ�����û�Ӧ��
    B2G_PAYSYS_2_GAMEWORLD,                     // ���Ǹ�ͨ��Э��: Paysys����Ϸ����
	B2G_SERVER_CONNECTEDINIT_READY,				// ���ض�GameServer���ӵĳ�ʼ�����
    B2G_IB_PLAYER_BUY_MULTI_ITEM_RESULT,        // �����IBģʽ�¹�������Ʒ�Ļ�Ӧ��
    B2G_IB_PLAYER_USE_MULTI_ITEM_RESULT,        // �����IBģʽ��ʹ�ö����Ʒ�Ļ�Ӧ��
    B2G_PLAYER_INFO_RESULT,                     // ��ȡ�ʺ���Ϣ����
    B2G_IB_PLAYER_BUY_ITEM_RESULT_SD,           // ʢ�������IBģʽ�¹�����Ʒ�ķ���
    B2G_IB_PLAYER_BUY_MULTI_ITEM_RESULT_SD,     // ʢ�������IBģʽ�¹�������Ʒ�ķ���
};

enum G2B_PROTOCOL_ID // Game server ==> Bishop
{
    G2B_PROTOCOL_BEGIN = PROTOCOL_NORMAL_PACKAGE_BEGIN,
    G2B_UPDATE_SERVER_INFO,                 // ����server��Ϣ, ref : tagGameSvrInfo
    G2B_UPDATE_MAP_INFO,                    // ���µ�ͼ��Ϣ, ref : tagUpdateMapID
    G2B_PLAYER_LOGIN_PERMISSION,            // ��ҵ�½��������Ϣ!
    G2B_PLAYER_ENTER_GAME,                  // ��ҽ�����Ϸ, ref : tagEnterGame
    G2B_PLAYER_LEAVE_GAME,                  // ����뿪��Ϸ, ref : tagLeaveGame
    G2B_PRE_TRANSFER_SERVER,                // ���֪ͨ(�����Ҽ����絽����������), ref : tagRegisterAccount (��: + RELAY_DATA + tagPermitPlayerExchange)
    G2B_EXT_POINTS_OPERATION,               // ���󸽼ӵ����, ref : tagChangeExtPoint
    G2B_ADD_PLAYER_TO_BLACK_LIST,           // ��ָ���ʺż��������, ref : TDenyAccount
    G2B_DYNAMIC_UPDATE_MAP_INFO,            // ��̬���µ�ͼ, ref : tagDynamicUpdateMapID
    G2B_PLAYER_OFFLINE_LIVE_NOTIFY,         // ֪ͨBishop,���ʺ����߹һ�, ref : tagOfflineRequestAsk
    G2B_PLAYER_OFFLINE_LIVE_TIMEOUT,        // ��ҵ����߹һ�ʱ��������, ref : tagOfflineTimeoutRes
    G2B_OFFLINE_LIVE_KICK_ACCOUNT_RESULT,   // ���߹һ��ߺŵĽ��, ref : tagOfflineKickoutRes
    G2B_CLEANUP_ACCOUNT_FREE_TIME,          // ��������ʺŵ����ʱ��, ref : TRYOUT_TIMEOUT_REQ
    G2B_PING,                               // ping����ref : PING_COMMAND
    G2B_USE_SPREADER_CDKEY,                 // ���������ƹ�CDKEY��PaySys, ref: tagUseSpreaderCDKeyRet
    G2B_CONFIRM_ACCOUNT_OFFLINE_RESPOND,    // ȷ�����û������Ϸ����, ref : CONFIRM_ACCOUNT_OFFLINE_RESPOND
    G2B_IB_PLAYER_BUY_ITEM,                 // �����IBģʽ�¹�����Ʒ��
    G2B_IB_PLAYER_USE_ITEM,                 // �����IBģʽ��ʹ����Ʒ��
    G2B_DYNAMIC_UPDATE_SERVER_INFO,         // ��̬����server��Ϣ ref : tagDynamicUpdateSvrInfo
    G2B_PLAYER_SET_CHARGE_FLAG_REQ,         // �޸��û�Charge_Flag����
    G2B_ACCOUNT_TRANSFER_REQUEST,           // �ʺ�֮��ת������
    G2B_ACCOUNT_USER_EXCHANGE,              // ��ҽ�Ҷһ�ʱ��
    G2B_PLAYER_QUERY_TRANSFER,              // ���ת�ʲ�ѯ
    G2B_PLAYER_FREEZE_FEE,                  // ��Ҷ������
    G2B_GAMEWORLD_2_PAYSYS,                 // ���Ǹ�ͨ��Э��: ��Ϸ���絽Paysys������
    G2B_IB_PLAYER_BUY_MULTI_ITEM,           // �����IBģʽ�¹�������Ʒ
    G2B_IB_PLAYER_USE_MULTI_ITEM,           // �����IBģʽ��ʹ�ö����Ʒ
    G2B_QUERY_PLAYER_INFO,                  // ��ȡ�ʺ���Ϣ
    G2B_IB_PLAYER_BUY_ITEM_SD,              // ʢ�������IBģʽ�¹�����Ʒ
    G2B_IB_PLAYER_BUY_MULTI_ITEM_SD,        // ʢ�������IBģʽ�¹�������Ʒ
    G2B_NOTIFY_SVR_FUNC_TYPE,				// ֪ͨbishop�����ߵ�����
};

enum SvrFuncNotifyType
{
	SFNT_FUNCTYPE = 0,
	SFNT_FUNCLIST,
	SFNT_FUNCALL,
};

#pragma	pack(push, 1)

#define	AP_WARNING_ALL_PLAYER_QUIT			1
#define	AP_NOTIFY_GAMESERVER_SAFECLOSE		2
#define	AP_NOTIFY_ALL_PLAYER				3
#define	AP_NOTIFY_PLAYER_KICKOUT			4
#define	MAX_GATEWAYBROADCAST_LEN	260
struct tagGatewayBroadCast : public tagProtocolHeader2
{
    UINT	uCmdType;
    char	szData[MAX_GATEWAYBROADCAST_LEN];
};


struct tagQueryGameSvrInfo : public tagProtocolHeader
{	
	int nZoneID;
};

struct tagGameSvrFuncTypeInfo : public tagProtocolHeader
{	
	BYTE		byNotifyType;		//֪ͨ�޸ĵ����ͣ��������ö��SvrFuncNotifyType
	WORD		wSvrFuncType;
	DWORD		dwSvrFuncList;
};

struct tagGameSvrInfo : public tagProtocolHeader
{
    UINT			nIPAddr_Intraner;
    UINT			nIPAddr_Internet;

    unsigned short	nPort;
    WORD			wCapability;
    int				nGameWorldLowerVersion; // ��Ϸ�߼� <--> �ͻ���Э����Ͱ汾��
    int				nGameWorldUpperVersion; // ��Ϸ�߼� <--> �ͻ���Э����߰汾��
};

struct tagPermitPlayerLogin : public tagProtocolHeader2
{
    GUID guid;
    char szAccountName[_NAME_LEN];
    char szRoleName[_NAME_LEN];
    bool bPermit;
};




struct tagEnterGame : public tagProtocolHeader
{
    char szAccountName[_NAME_LEN];
};

#define NORMAL_LEAVEGAME	0x0		// lock account
#define HOLDACC_LEAVEGAME	0x1A	// clear resource but don't to unlock account 

struct tagLeaveGame : public tagProtocolHeader
{
    BYTE cCmdType;
    WORD nExtPoint;        //��Ҫ�۳��ĸ��͵�
    char szAccountName[_NAME_LEN];
};


struct tagRegisterAccount : public tagProtocolHeader
{
    char szAccountName[_NAME_LEN];
};


#define CHANGE_EXT_POINT_SILVER	0x1

struct tagChangeExtPoint : public tagProtocolHeader
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

struct tagReturnChangeExtPoint : public tagProtocolHeader
{
    int nResult;
    char szAccountName[_NAME_LEN];
    unsigned uFlag;
    int      nPlayerDataIndex;  // ������ݵ������ţ�����������Э��
};

struct tagDynamicUpdateMapID : public tagProtocolHeader
{
    BOOL	bRelay;	//�����relay����1�������gameserver����0
    int		nMapId;
    int		nMapCopyId;
    int		nAction;	//1��ʾע�ᣬ0��ʾע��
};

struct tagDynamicUpdateSvrInfo : public tagProtocolHeader
{
    int nPlayerCount;
};

struct tagOfflineRequestReq : public ProtocolHeader//PROTOCOL_MSG_HEADER
{
    char szAccount[_NAME_LEN];	// �˺���������������
    char szRole[_NAME_LEN];		// ��ɫ��������������
};

struct tagOfflineRequestAsk : public tagOfflineRequestReq
{
    DWORD dwMapId;				// ������ڵĵ�ͼID
    int	  nIndex;				// GameServer�е��������
};

struct tagOfflineRequestRes : public tagOfflineRequestReq
{
    BYTE	nResult;			// �����1���ɹ���0��ʧ��
    BYTE	nReason;			// ʧ��ԭ�򣺳ɹ�ʱΪ0
    DWORD	dwLeftTime;			// ʣ�����߹һ�ʱ�䣬��λ�Ƿ���
};

// ���߹һ��ߺ�����
struct tagOfflineKickoutAsk : public ProtocolHeader2 //PROTOCOL_MSG_HEADER
{
    char szAccount[_NAME_LEN];	// �˺���������������
    int	 nIndex;				// GameServer�е��������
};

// ���߹һ��ߺŽ��
struct tagOfflineKickoutRes : public ProtocolHeader2 //PROTOCOL_MSG_HEADER
{
    char szAccount[_NAME_LEN];	// �˺���������������
    BYTE nResult;				// 1��ʾ���̳ɹ���0��ʾ����ʧ��
    WORD wExtPoint;				// ��չ��
};

// ���߹һ���ʱ���
struct tagOfflineTimeoutRes : public tagOfflineRequestReq
{
    WORD	wExtPoint;			// ��չ��
};

struct TDenyAccount : public tagProtocolHeader
{
    char	szAccount[_NAME_LEN];	// �˺���
    DWORD	dwTimeout;				// ��ֹ��¼��ʱ����(s)
};

/**
* @description δ��ֵ�������˺ŵ���20�������趨��ʱ����ʹ��ѵ�10Сʱδʹ���꣬
Ҳ��������Ϸ�������߳���ͬʱ��paysys����Э�齫��ʹ��ʱ������Ϊ0
* @protocol	c2s_tryout_timeout_req GameServer=>Bishop
* @author		wangbin
* @datetime	2004-12-28 09:57
*/
struct TRYOUT_TIMEOUT_REQ
{
    BYTE	ProtocolType;
    BYTE	nReason;				// ԭ�򣨱�����
    char	szAccount[_NAME_LEN];	// �˺���
    int		nPlayerIndex;			// �����������
};

/**
* @description δ��ֵ�������˺ŵ���20�������趨��ʱ����ʹ��ѵ�10Сʱδʹ���꣬
Ҳ��������Ϸ�������߳���ͬʱ��paysys����Э�齫��ʹ��ʱ������Ϊ0��
�����������ߺ�Ҳ�����Э�顣
* @protocol	s2c_tryout_timeout_res Bishop=>GameServer
* @author		wangbin
* @datetime	2004-12-28 09:57
*/
struct TRYOUT_TIMEOUT_RES
{
    BYTE	ProtocolType;
    BYTE	nResult;				// ��������1Ϊ�ɹ���0Ϊʧ��
    char	szAccount[_NAME_LEN];	// �˺���
    int		nPlayerIndex;			// �����������
};

struct tagUseSpreaderCDKey : public ProtocolHeader
{
    char szAccountName[_NAME_LEN];
    char szCDKey[_NAME_LEN];
    int  nPlayerDataIndex;	
};

struct tagUseSpreaderCDKeyRet : public ProtocolHeader
{
    char szAccountName[_NAME_LEN];
    int  nPlayerDataIndex;
    int  nResult;
};

struct CONFIRM_ACCOUNT_OFFLINE_REQUEST : public ProtocolHeader2
{
    char szAccountName[_NAME_LEN];
};

struct CONFIRM_ACCOUNT_OFFLINE_RESPOND : public ProtocolHeader2
{
    int nReserve;   // ����λ����0����
};

#define MAX_ITEM_COUNT_IN_PACKAGE_FROM_SERVER 16

struct KG2BAccountBuyItem : public ProtocolHeader2
{
    char        szAccount[_NAME_LEN];
    int         nPlayerDataIndex;                                  // �������Ϸ����ı��
    int         nGoodsIndex;                                       // ��Ʒ����Ʒ�ı��
    int         nItemTypeID;                                       // ��Ʒ����ID
    int         nItemLevel;                                        // ��Ʒ����(����Ʒ����IDһ��Ψһ��λ��Ʒ)
    int         nUseType;                                          // ʹ������(enumIB_ItemUseType)
    int         nPrice;                                            // ����۸�
    DWORD       dwOverdueTime;                                     // ������(��ֵ)
};

#define MAX_SD_UNIQUEID_SIZE 33
struct KG2BAccountBuyItemSD : public KG2BAccountBuyItem
{
    char        szSDUniqueId[MAX_SD_UNIQUEID_SIZE];
};

struct KG2BAccountBuyMultiItem : public ProtocolHeader2
{
    char        szAccount[_NAME_LEN];
    int         nPlayerDataIndex;                                  // �������Ϸ����ı��
    int         nGoodsIndex;                                       // ��Ʒ����Ʒ�ı��
    int         nItemTypeID;                                       // ��Ʒ����ID
    int         nItemLevel;                                        // ��Ʒ����(����Ʒ����IDһ��Ψһ��λ��Ʒ)
    int         nUseType;                                          // ʹ������(enumIB_ItemUseType)
    int         nPrice;                                            // ����۸�
    DWORD       dwOverdueTime;                                     // ������(��ֵ)
    int         nItemCount;                                        // �������Ʒ����
    BYTE        byUseItemNow;                                      // �����ͬʱʹ�õ���Ʒ
};

struct KG2BAccountBuyMultiItemSD : public KG2BAccountBuyMultiItem
{
    char        szSDUniqueId[MAX_SD_UNIQUEID_SIZE];
};

struct KG2BAccountUseItem : public ProtocolHeader2
{
    char        szAccount[_NAME_LEN];
    int         nPlayerDataIndex;                                   // �������Ϸ����ı��
    int         nItemTypeID;                                        // ��Ʒ����ID
    int         nItemLevel;                                         // ��Ʒ����(����Ʒ����IDһ��Ψһ��λ��Ʒ)
    long long   llItemGUID;                                         // ��Ʒ�����ݿ��Ψһ���
};

struct KG2BAccountUseMultiItem : public ProtocolHeader2
{
    char        szAccount[_NAME_LEN];
    int         nPlayerDataIndex;                                   // �������Ϸ����ı��
    int         nItemTypeID;                                        // ��Ʒ����ID
    int         nItemLevel;                                         // ��Ʒ����(����Ʒ����IDһ��Ψһ��λ��Ʒ)
    int         nItemCount;                                         // �������Ʒ����
    long long   llItemGUID[MAX_ITEM_COUNT_IN_PACKAGE_FROM_SERVER];  // ��Ʒ�����ݿ��Ψһ���
};

struct KB2GAccountBuyItemRet : public ProtocolHeader2
{
    char         szAccount[_NAME_LEN];
    int          nPlayerDataIndex;                                  // �������Ϸ����ı��
    int          nGoodsIndex;                                       // ��Ʒ����Ʒ�ı��
    int          nItemTypeID;                                       // ��Ʒ����ID
    int          nItemLevel;                                        // ��Ʒ����(����Ʒ����IDһ��Ψһ��λ��Ʒ)
    int          nPrice;                                            // ����۸�
    long long    llItemGUID;                                        // ��Ʒ�����ݿ��Ψһ���
    int          nResult;                                           // ���������
};

struct KB2GAccountBuyItemRetSD : public KB2GAccountBuyItemRet
{
    char        szSDUniqueId[MAX_SD_UNIQUEID_SIZE];
};

struct KB2GAccountBuyMultiItemRet : public ProtocolHeader2
{
    char         szAccount[_NAME_LEN];
    int          nPlayerDataIndex;                                  // �������Ϸ����ı��
    int          nGoodsIndex;                                       // ��Ʒ����Ʒ�ı��
    int          nItemTypeID;                                       // ��Ʒ����ID
    int          nItemLevel;                                        // ��Ʒ����(����Ʒ����IDһ��Ψһ��λ��Ʒ)
    int          nPrice;                                            // ����۸�
    int          nItemCount;                                        // �������Ʒ����
    long long    llItemGUID[MAX_ITEM_COUNT_IN_PACKAGE_FROM_SERVER]; // ��Ʒ�����ݿ��Ψһ���
    int          nResult;                                           // ���������
};

struct KB2GAccountBuyMultiItemRetSD : public KB2GAccountBuyMultiItemRet
{
    char        szSDUniqueId[MAX_SD_UNIQUEID_SIZE];
};

struct KB2GAccountUseItemRet : public ProtocolHeader2
{
    char        szAccount[_NAME_LEN];
    int         nPlayerDataIndex;                                   // �������Ϸ����ı��
    int         nItemTypeID;                                        // ��Ʒ����ID
    int         nItemLevel;                                         // ��Ʒ����(����Ʒ����IDһ��Ψһ��λ��Ʒ)
    long long   llItemGUID;                                         // ��Ʒ�����ݿ��Ψһ���
    int         nResult;                                            // ���������
};

struct KB2GAccountUseMultiItemRet : public ProtocolHeader2
{
    char        szAccount[_NAME_LEN];
    int         nPlayerDataIndex;                                   // �������Ϸ����ı��
    int         nItemTypeID;                                        // ��Ʒ����ID
    int         nItemLevel;                                         // ��Ʒ����(����Ʒ����IDһ��Ψһ��λ��Ʒ)
    int         nItemCount;                                         // �������Ʒ����
    long long   llItemGUID[MAX_ITEM_COUNT_IN_PACKAGE_FROM_SERVER];  // ��Ʒ�����ݿ��Ψһ���
    int         nResult;                                            // ���������
};

struct KB2GPlayerSetChargeFlagReq : public ProtocolHeader2
{
    char    szAccount[_NAME_LEN];
    DWORD   dwLastLoginIP;
    int     nChargeFlag;                                    // 0:���,1:�շ�
};

struct KB2GPlayerSetChargeFlagRet : public ProtocolHeader2
{
    char    szAccount[_NAME_LEN];
    int     nChargeFlag;                                    // 0:���,1:�շ�
    int     nResult;
};

struct KG2BAccountTransferRequest : public ProtocolHeader2
{
    long long   llTransferGUID;                             // ���ײ�����Ψһ���,����Ϸ���紫��Paysys.�������ѯ������
    char        szAccountDest[_NAME_LEN];                   // Ŀ���˻�
    char        szAccountSrc[_NAME_LEN];                    // Դ�˻�
    DWORD       dwTransferFlag;
    DWORD       dwTransferType;                             // 1: �Ƶ�ת��; 2: ���ת��; 3: ��չ��ת��
    DWORD       dwExtPoint;                                 // ��չ��ת��ʱ����չ������
    DWORD       dwTransferAmount;                           // ת�ʵ���Ŀ
};

struct KB2GAccountTransferResult : public ProtocolHeader2
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

struct KG2BAccountUserExchange : public ProtocolHeader2
{
    char   szAccount[_NAME_LEN];
    DWORD  dwExchangeType; 
    DWORD  dwDestAmount;                                    // �һ��ɵ���Ŀ
    DWORD  dwSrcAmount;                                     // ���һ�����Ŀ
};

struct KB2GAccountUserExchangeResult : public ProtocolHeader2
{
    char   szAccount[_NAME_LEN];
    DWORD  dwExchangeType; 
    DWORD  dwDestAmount;                                    // �һ��ɵ���Ŀ
    DWORD  dwSrcAmount;                                     // ���һ�����Ŀ
    
    int    nResult;
};


struct KG2BAccountQueryTransfer : ProtocolHeader2
{
    long long llTransferGUID;                               // ���ײ�����Ψһ���,����Ϸ���紫��Paysys
};

struct KB2GAccountQueryTransferResult : ProtocolHeader2
{
    long long llTransferGUID;                               // ���ײ�����Ψһ���,����Ϸ���紫��Paysys
    DWORD     dwTransferTime;
    char      szAccountDest[_NAME_LEN]; 
    char      szAccountSrc[_NAME_LEN]; 
    DWORD     dwTransferFlag;
    DWORD     dwTransferType;
    DWORD     dwExtPoint;                                   // ������չ�㶳�ᣬ���ֶ�Ϊ��չ������0��7��
    DWORD     dwTransferAmount;
    DWORD     dwTransferResult;

    int       nResult;
};

struct KG2BPlayerFreezeFee : ProtocolHeader2
{
    long long   llFreezeGUID;
    char        szAccount[_NAME_LEN];
    DWORD       dwFreezeFlag;
    DWORD       dwFreezeType;
    DWORD       dwExtPoint;                                // ������չ�㶳�ᣬ���ֶ�Ϊ��չ������0��7��
    DWORD       dwFreezeAmount;
};

struct KB2GPlayerFreezeFeeResult : ProtocolHeader2
{
    long long   llFreezeGUID;
    char        szAccount[_NAME_LEN];
    DWORD       dwFreezeFlag;
    DWORD       dwFreezeType;
    DWORD       dwExtPoint;                                // ������չ�㶳�ᣬ���ֶ�Ϊ��չ������0��7��
    DWORD       dwFreezeAmount;

    int         nResult;
};

struct KG2BGameworld2Paysys : ProtocolHeader2
{
    unsigned uDataSize;
    BYTE     byData[0];
};

struct KB2GPaysys2Gameworld : ProtocolHeader2
{
    unsigned uDataSize;
    BYTE     byData[0];
};

struct KG2BQueryPlayerInfo : ProtocolHeader2
{
    char     szAccount[_NAME_LEN]; 
};

struct KB2GPlayerInfoResult : ProtocolHeader2
{
    int               nResult;
    char              szAccount[_NAME_LEN];
    tagExtPointInfo   ExtPointInfo;
    DWORD             dwEndDate;
    DWORD             dwLeftSecond;
    DWORD             dwLastLoginTime;
    DWORD             dwLastLoginIP;
    DWORD             dwLeftCoin;            //ʣ����
    DWORD             dwLastLogoutTime;
    DWORD             dwActiveIP;
    DWORD             dwActiveTime;
    DWORD             dwActiveType;
};

#pragma pack(pop)

#endif
